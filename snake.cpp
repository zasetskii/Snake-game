#include "snake.h"
#include <QDebug>

#define DELAY 100
#define DOT_SIZE 10 //размер одной клетки поля
#define LEADERBOARD_SIZE 10

Snake::Snake(QWidget *parent)
    : QWidget(parent), m_size(300, 300)
{
    m_head.load(":/images/images/head.png");

    m_timer = new QTimer(this);
    m_score = new QLabel("0");

    m_leaderboard_model = new RecordListModel(this);

    setLeaderboard();

    setAutoFillBackground(true);
    resize(m_size);
    setMinimumSize(m_size);
    setMaximumSize(m_size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //setDifficulty(m_settings.value("difficulty", 1).toInt());
    //setBackgroundColor(m_settings.value("background", 2).toInt());
    //setSnakeColor(m_settings.value("snake", 0).toInt());
    //setAppleColor(m_settings.value("apple", 0).toInt());

    connect(m_timer, &QTimer::timeout, this, &Snake::onTimer);
}

void Snake::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(m_coordinates[0], m_head);
    for (int i = 1; i < m_coordinates.size(); ++i)
    {
        painter.drawImage(m_coordinates[i], m_dot);
    }
    painter.drawImage(m_apple_coordinates, m_apple);
}

void Snake::onTimer()
{
    processKeyPressed();

    if (m_is_growing)
    {
        m_coordinates.push_back(m_coordinates[m_coordinates.size() - 1]);
        for (int i = m_coordinates.size() - 2; i != 0; --i)
        {
            m_coordinates[i] = m_coordinates[i - 1];
        }
        m_is_growing = false;
    }
    else
    {
        for (int i = m_coordinates.size() - 1; i != 0; --i)
        {
            m_coordinates[i] = m_coordinates[i - 1];
        }
    }

    if (m_cur_direction == DIRECTION_UP)
    {
        m_coordinates[0].ry() -= DOT_SIZE;
    }
    else if (m_cur_direction == DIRECTION_DOWN)
    {
        m_coordinates[0].ry() += DOT_SIZE;
    }
    else if (m_cur_direction == DIRECTION_LEFT)
    {
        m_coordinates[0].rx() -= DOT_SIZE;
    }
    else if (m_cur_direction == DIRECTION_RIGHT)
    {
        m_coordinates[0].rx() += DOT_SIZE;
    }
    else
        return;

    checkBorders();
    checkApple();
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        m_timer->stop();
        emit escPressed();
        return;
    case Qt::Key_Space:
        startNewGame();
        return;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_key_q.enqueue(event->key());
        break;
    default:
        break;
    }
}

void Snake::processKeyPressed()
{
    if (m_key_q.isEmpty())
        return;
    switch(m_key_q.dequeue())
    {
    case Qt::Key_Up:
        if (m_cur_direction != DIRECTION_DOWN)
            m_cur_direction = DIRECTION_UP;
        break;
    case Qt::Key_Down:
        if (m_cur_direction != DIRECTION_UP)
            m_cur_direction = DIRECTION_DOWN;
        break;
    case Qt::Key_Left:
        if (m_cur_direction != DIRECTION_RIGHT)
            m_cur_direction = DIRECTION_LEFT;
        break;
    case Qt::Key_Right:
        if (m_cur_direction != DIRECTION_LEFT)
            m_cur_direction = DIRECTION_RIGHT;
        break;
    default:
        break;
    }
}

void Snake::checkBorders()
{
    if (m_coordinates[0].x() < 0 || m_coordinates[0].x() > this->width() - DOT_SIZE ||
        m_coordinates[0].y() < 0 || m_coordinates[0].y() > this->height() - DOT_SIZE)
    {
        gameOver();
    }
    for (int i = 1; i < m_coordinates.size(); ++i)
    {
        if (m_coordinates[0] == m_coordinates[i])
        {
            gameOver();
            break;
        }
    }
}

void Snake::gameOver()
{
    m_timer->stop();
    if (m_leaderboard_model->rowCount() > 0 && m_score->text().toInt() < m_leaderboard_model->score(m_leaderboard_model->rowCount() - 1))
    {
        showLoseMessage();
    }
    else
    {
        bool ok;
        QString name = QInputDialog::getText(this, "Новый рекорд!", "Введите имя", QLineEdit::Normal, QString(),
                                             &ok, Qt::WindowTitleHint | Qt::WindowSystemMenuHint| Qt::WindowCloseButtonHint);
        if (ok)
            saveResult(name);
        emit escPressed();
    }
    emit gameIsOver();
}

void Snake::showLoseMessage()
{
    QMessageBox lose_message;
    lose_message.setWindowTitle("Вы проиграли");
    lose_message.setText("Хотите сыграть снова?");
    QAbstractButton* play_again_btn = lose_message.addButton("Играть снова", QMessageBox::AcceptRole);
    QAbstractButton* to_menu_btn = lose_message.addButton("В меню", QMessageBox::RejectRole);
    lose_message.exec();
    if (lose_message.clickedButton() == play_again_btn)
        startNewGame();
    else if (lose_message.clickedButton() == to_menu_btn)
        emit escPressed();
}

void Snake::saveResult(const QString& name)
{
    m_leaderboard_model->addRecord(name, m_score->text().toInt());
    m_leaderboard_model->sort(1, Qt::DescendingOrder);
    if (m_leaderboard_model->rowCount() > LEADERBOARD_SIZE)
        m_leaderboard_model->removeRecord(m_leaderboard_model->rowCount() - 1);
    const int size_of_board = std::min(m_leaderboard_model->rowCount(), LEADERBOARD_SIZE);
    QJsonArray j_arr;
    for(int i = 0; i < size_of_board; ++i)
    {
        QJsonObject jRecord;
        jRecord["name"] = m_leaderboard_model->name(i);
        jRecord["score"] = m_leaderboard_model->score(i);
        j_arr.append(jRecord);
    }
    QJsonDocument j_document(j_arr);
    QFile file("scoreboard.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.write(j_document.toJson());
    }
    else
    {
        qWarning("Could not open file");
    }
    file.close();
}

void Snake::setLeaderboard()
{
    QFile scoreboard("scoreboard.txt");
    if (scoreboard.open(QIODevice::ReadWrite))
    {
        QByteArray data = scoreboard.readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonArray j_arr = document.array();
        for(int i = 0; i < j_arr.size(); ++i)
        {
            QString name = j_arr.at(i)["name"].toString();
            int score = j_arr.at(i)["score"].toInt();
            m_leaderboard_model->addRecord(name, score);
        }
        m_leaderboard_model->sort(1, Qt::DescendingOrder);
    }
    else
    {
        qWarning("Could not open file");
    }
    scoreboard.close();
}

RecordListModel* Snake::getLeaderboardModel() const
{
    return m_leaderboard_model;
}

void Snake::generateApple()
{
    QPoint position;
    while(1)
    {
        position.rx() = QRandomGenerator::global()->bounded((width() - DOT_SIZE) / DOT_SIZE ) * DOT_SIZE;
        position.ry() = QRandomGenerator::global()->bounded((height() - DOT_SIZE) / DOT_SIZE ) * DOT_SIZE;
        bool intersects = false;
        for (int i = 0; i < m_coordinates.size(); ++i)
        {
            if (m_coordinates[i] == position)
            {
                intersects = true;
                break;
            }
        }
        if (!intersects)
            break;
    }
    m_apple_coordinates = position;
}

void Snake::checkApple()
{
    if (m_coordinates[0] == m_apple_coordinates)
    {
        generateApple();
        m_is_growing = true;
        m_score->setNum(m_score->text().toInt() + 1);
    }
}

void Snake::startNewGame()
{
    m_key_q.erase(m_key_q.begin(), m_key_q.end());
    m_coordinates.erase(m_coordinates.begin(), m_coordinates.end());
    m_coordinates.push_back({width() / 2, height() / 2});
    m_coordinates.push_back({width() / 2 + DOT_SIZE, height() / 2});
    m_coordinates.push_back({width() / 2 + (2 * DOT_SIZE), height() / 2});
    m_coordinates.push_back({width() / 2 + (3 * DOT_SIZE), height() / 2});
    m_score->setNum(m_coordinates.size());
    generateApple();

    m_cur_direction = DIRECTION_LEFT;
    m_timer->start(m_delay);
}

void Snake::setDifficultyEasy()
{
    m_delay = 150;
}

void Snake::setDifficultyMedium()
{
    m_delay = 100;
}

void Snake::setDifficultyHard()
{
    m_delay = 50;
}

//void Snake::setDifficulty(int index)
//{
//    switch (index)
//    {
//    case 0:
//        setDifficultyEasy();
//        break;
//    case 1:
//        setDifficultyMedium();
//        break;
//    case 2:
//        setDifficultyHard();
//        break;
//    }
//    m_settings.setValue("difficulty", index);
//}

void Snake::setGrayBackground()
{
    setPalette(QPalette(QPalette::Background, Qt::lightGray));
}

void Snake::setBlueBackground()
{
    setPalette(QPalette(QPalette::Background, Qt::darkBlue));
}

void Snake::setRedBackground()
{
    setPalette(QPalette(QPalette::Background, Qt::darkRed));
}

//void Snake::setBackgroundColor(int index)
//{
//    switch (index)
//    {
//    case 0:
//        setGrayBackground();
//        break;
//    case 1:
//        setBlueBackground();
//        break;
//    case 2:
//        setRedBackground();
//        break;
//    }
//    m_settings.setValue("background", index);
//}

void Snake::setSnakeGreen()
{
    m_dot.load(":/images/images/dot_green.png");
}

void Snake::setSnakeBlack()
{
    m_dot.load(":/images/images/dot_black.png");
}

void Snake::setSnakeWhite()
{
    m_dot.load(":/images/images/dot_white.png");
}

//void Snake::setSnakeColor(int index)
//{
//    switch (index)
//    {
//    case 0:
//        setSnakeGreen();
//        break;
//    case 1:
//        setSnakeBlack();
//        break;
//    case 2:
//        setSnakeWhite();
//        break;
//    }
//    m_settings.setValue("snake", index);
//}

void Snake::setAppleYellow()
{
    m_apple.load(":/images/images/apple_yellow.png");
}

void Snake::setAppleGreen()
{
    m_apple.load(":/images/images/apple_green.png");
}

//void Snake::setAppleColor(int index)
//{
//    switch (index)
//    {
//    case 0:
//        setAppleYellow();
//        break;
//    case 1:
//        setAppleGreen();
//        break;
//    }
//    m_settings.setValue("apple", index);
//}

Snake::~Snake()
{
}

