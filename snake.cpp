#include "snake.h"

#define DELAY 100
#define DOT_SIZE 10

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    head.load("../game/images/head.png");

    timer = new QTimer(this);
    score = new QLabel("0");

    setLeaderboard();

    setAutoFillBackground(true);
    resize(300, 300);
    setMinimumSize(300, 300);
    setMaximumSize(300, 300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(timer, &QTimer::timeout, this, &Snake::onTimer);
}

void Snake::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(coordinates[0], head);
    for (int i = 1; i < coordinates.size(); ++i)
    {
        painter.drawImage(coordinates[i], dot);
    }
    painter.drawImage(apple_coordinates, apple);
    if (is_game_over)
        gameOver(painter);
}

void Snake::onTimer()
{
    processKeyPressed();

    if (is_growing)
    {
        coordinates.push_back(coordinates[coordinates.size() - 1]);
        for (int i = coordinates.size() - 2; i != 0; --i)
        {
            coordinates[i] = coordinates[i - 1];
        }
        is_growing = false;
    }
    else
    {
        for (int i = coordinates.size() - 1; i != 0; --i)
        {
            coordinates[i] = coordinates[i - 1];
        }
    }

    if (cur_direction == DIRECTION_UP)
    {
        coordinates[0].ry() -= DOT_SIZE;
    }
    else if (cur_direction == DIRECTION_DOWN)
    {
        coordinates[0].ry() += DOT_SIZE;
    }
    else if (cur_direction == DIRECTION_LEFT)
    {
        coordinates[0].rx() -= DOT_SIZE;
    }
    else if (cur_direction == DIRECTION_RIGHT)
    {
        coordinates[0].rx() += DOT_SIZE;
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
        timer->stop();
        emit escPressed();
        return;
    case Qt::Key_Space:
        startNewGame();
        return;
    default:
        break;
    }

    key_q.enqueue(event->key());
}

void Snake::processKeyPressed()
{
    if (key_q.isEmpty())
        return;
    switch(key_q.dequeue())
    {
    case Qt::Key_Up:
        if (cur_direction != DIRECTION_DOWN)
            cur_direction = DIRECTION_UP;
        break;
    case Qt::Key_Down:
        if (cur_direction != DIRECTION_UP)
            cur_direction = DIRECTION_DOWN;
        break;
    case Qt::Key_Left:
        if (cur_direction != DIRECTION_RIGHT)
            cur_direction = DIRECTION_LEFT;
        break;
    case Qt::Key_Right:
        if (cur_direction != DIRECTION_LEFT)
            cur_direction = DIRECTION_RIGHT;
        break;
    default:
        break;
    }
}

void Snake::checkBorders()
{
    if (coordinates[0].x() < 0 || coordinates[0].x() > this->width() - DOT_SIZE ||
        coordinates[0].y() < 0 || coordinates[0].y() > this->height() - DOT_SIZE)
    {
        is_game_over = true;
    }
    for (int i = 1; i < coordinates.size(); ++i)
    {
        if (coordinates[0] == coordinates[i])
        {
            is_game_over = true;
            break;
        }
    }
}

void Snake::gameOver(QPainter& painter)
{
    painter.drawText(width()/2, height()/2, "Game over!");
    timer->stop();
    saveResult();
    emit gameIsOver();
}

void Snake::saveResult()
{
    leaderboard[score->text().toInt()] = "Name";
    QFile file("../game/scoreboard.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out_stream(&file);
        QMap<int, QString>::const_iterator it = leaderboard.constEnd();
        --it;
        const int size_of_board = std::min(leaderboard.size(), 10);
        for (int i = 0; i < size_of_board; ++i, --it)
        {
            out_stream << it.key() << " " << it.value() << endl;
        }
    }
    else
    {
        qWarning("Could not open file");
    }
    file.close();
}

void Snake::setLeaderboard()
{
    QFile scoreboard("../game/scoreboard.txt");
    if (scoreboard.open(QIODevice::ReadOnly))
    {
        QTextStream file_stream(&scoreboard);
        while(!file_stream.atEnd())
        {
            QString cur_line = file_stream.readLine();
            QStringList key_and_value = cur_line.split(' ', QString::SkipEmptyParts);
            int key = key_and_value.at(0).toInt();
            QString value = key_and_value.at(1);
            leaderboard.insert(key, value);
        }
    }
    else
    {
        qWarning("Could not open file");
    }
    scoreboard.close();
}

QMap<int, QString> Snake::getLeaderboard()
{
    return leaderboard;
}

void Snake::generateApple()
{
    QPoint position;
    while(1)
    {
        position.rx() = QRandomGenerator::global()->bounded((width() - DOT_SIZE) / DOT_SIZE ) * DOT_SIZE;
        position.ry() = QRandomGenerator::global()->bounded((height() - DOT_SIZE) / DOT_SIZE ) * DOT_SIZE;
        bool intersects = false;
        for (int i = 0; i < coordinates.size(); ++i)
        {
            if (coordinates[i] == position)
            {
                intersects = true;
                break;
            }
        }
        if (!intersects)
            break;
    }
    apple_coordinates = position;
}

void Snake::checkApple()
{
    if (coordinates[0] == apple_coordinates)
    {
        generateApple();
        is_growing = true;
        score->setNum( score->text().toInt() + 1);
    }
}

void Snake::startNewGame()
{
    key_q.erase(key_q.begin(), key_q.end());
    coordinates.erase(coordinates.begin(), coordinates.end());
    coordinates.push_back({width() / 2, height() / 2});
    coordinates.push_back({width() / 2 + DOT_SIZE, height() / 2});
    coordinates.push_back({width() / 2 + (2 * DOT_SIZE), height() / 2});
    coordinates.push_back({width() / 2 + (3 * DOT_SIZE), height() / 2});
    score->setNum(coordinates.size());
    generateApple();

    cur_direction = DIRECTION_LEFT;
    is_game_over = false;
    timer->start(delay);
}

void Snake::setDifficultyEasy()
{
    delay = 150;
}

void Snake::setDifficultyMedium()
{
    delay = 100;
}

void Snake::setDifficultyHard()
{
    delay = 50;
}

void Snake::setDifficulty(int index)
{
    switch (index)
    {
    case 0:
        setDifficultyEasy();
        break;
    case 1:
        setDifficultyMedium();
        break;
    case 2:
        setDifficultyHard();
        break;
    }
}

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

void Snake::setBackgroundColor(int index)
{
    switch (index)
    {
    case 0:
        setGrayBackground();
        break;
    case 1:
        setBlueBackground();
        break;
    case 2:
        setRedBackground();
        break;
    }
}

void Snake::setSnakeGreen()
{
    dot.load("../game/images/dot_green.png");
}

void Snake::setSnakeBlack()
{
    dot.load("../game/images/dot_black.png");
}

void Snake::setSnakeWhite()
{
    dot.load("../game/images/dot_white.png");
}

void Snake::setSnakeColor(int index)
{
    switch (index)
    {
    case 0:
        setSnakeGreen();
        break;
    case 1:
        setSnakeBlack();
        break;
    case 2:
        setSnakeWhite();
        break;
    }
}

void Snake::setAppleYellow()
{
    apple.load("../game/images/apple_yellow.png");
}

void Snake::setAppleGreen()
{
    apple.load("../game/images/apple_green.png");
}

void Snake::setAppleColor(int index)
{
    switch (index)
    {
    case 0:
        setAppleYellow();
        break;
    case 1:
        setAppleGreen();
        break;
    }
}

Snake::~Snake()
{
}

