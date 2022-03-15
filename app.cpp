#include "app.h"
#include "snake.h"
#include "menuscreen.h"
#include "settings.h"
#include "leaderboard.h"

App::App(QWidget *parent) : QMainWindow(parent), m_size(300, 350), m_settings("Organization", "Snake")
{
    m_game = new Snake(this);
    m_menu_screen = new MenuScreen(this);
    m_menu_screen->setObjectName("menu_screen");
    m_stacked_widget = new QStackedWidget;
    m_settings_screen = new Settings(this);
    m_settings_screen->setObjectName("settings_screen");
    m_leaderboard = new Leaderboard(this);
    m_leaderboard->setObjectName("leaderboard");

    resize(m_size);
    setMinimumSize(m_size);
    setMaximumSize(m_size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_stacked_widget->addWidget(m_menu_screen);
    m_stacked_widget->addWidget(m_settings_screen);
    m_stacked_widget->addWidget(m_game);
    m_stacked_widget->addWidget(m_leaderboard);
    setCentralWidget(m_stacked_widget);
    statusBar()->addWidget(m_game->m_score);
    statusBar()->setSizeGripEnabled(false);
    makeDifficultyMenu();
    makeColorMenu();

    setDifficulty(m_settings.value("difficulty", 1).toInt());
    setBackgroundColor(m_settings.value("background", 2).toInt());
    setSnakeColor(m_settings.value("snake", 0).toInt());
    setAppleColor(m_settings.value("apple", 0).toInt());

    showMenu();

    connect(m_menu_screen->m_start_game_btn, &QPushButton::clicked, this, &App::startGame);
    connect(m_menu_screen->m_open_leaderboard_btn, &QPushButton::clicked, this, &App::openLeaderboard);
    connect(m_menu_screen->m_open_settings_btn, &QPushButton::clicked, this, &App::openSettings);
    connect(m_menu_screen->m_quit_game_btn, &QPushButton::clicked, qApp, QApplication::quit);
    connect(m_menu_screen->m_continue_game_btn, &QPushButton::clicked, this, &App::continueGame);
    connect(m_settings_screen->m_difficulty_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &App::setDifficulty);
    connect(m_settings_screen->m_background_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &App::setBackgroundColor);
    connect(m_settings_screen->m_snake_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &App::setSnakeColor);
    connect(m_settings_screen->m_apple_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &App::setAppleColor);
    connect(m_settings_screen->m_back_to_menu_btn, &QPushButton::clicked, this, &App::showMenu);
    connect(m_leaderboard->m_back_to_menu_btn, &QPushButton::clicked, this, &App::showMenu);
    connect(m_game, &Snake::escPressed, this, &App::showMenu);
    connect(m_game, &Snake::gameIsOver, m_menu_screen->m_continue_game_btn, &QPushButton::hide);
}

void App::makeDifficultyMenu()
{
    QMenu* difficulty_menu = this->menuBar()->addMenu("&Сложность");
    QAction* easy = new QAction("Легко");
    easy->setCheckable(true);
    QAction* medium = new QAction("Средне");
    medium->setCheckable(true);
    QAction* hard = new QAction("Сложно");
    hard->setCheckable(true);
    m_difficulties = new QActionGroup(this);
    m_difficulties->addAction(easy);
    m_difficulties->addAction(medium);
    m_difficulties->addAction(hard);
    difficulty_menu->addAction(easy);
    difficulty_menu->addAction(medium);
    difficulty_menu->addAction(hard);
    setChecks(m_difficulties->actions(), m_settings.value("difficulty", 1).toInt());
    connect(easy, &QAction::triggered, [this](){ setDifficulty(0); });
    connect(medium, &QAction::triggered, [this](){ setDifficulty(1); });
    connect(hard, &QAction::triggered, [this](){ setDifficulty(2); });
}

void App::makeColorMenu()
{
    QMenu* color_menu = this->menuBar()->addMenu("&Цвет");
    QAction* gray_background = new QAction("Серый фон");
    QAction* blue_background = new QAction("Синий фон");
    QAction* red_background = new QAction("Красный фон");
    gray_background->setCheckable(true);
    blue_background->setCheckable(true);
    red_background->setCheckable(true);
    red_background->setChecked(true);
    color_menu->addActions({gray_background, blue_background, red_background});
    m_background_colors = new QActionGroup(this);
    m_background_colors->addAction(gray_background);
    m_background_colors->addAction(blue_background);
    m_background_colors->addAction(red_background);
    setChecks(m_background_colors->actions(), m_settings.value("background", 2).toInt());
    connect(gray_background, &QAction::triggered, [this](){ setBackgroundColor(0); });
    connect(blue_background, &QAction::triggered, [this](){ setBackgroundColor(1); });
    connect(red_background, &QAction::triggered, [this](){ setBackgroundColor(2); });

    color_menu->addSeparator();
    QAction* green_snake = new QAction("Зелёная змея");
    QAction* black_snake = new QAction("Чёрная змея");
    QAction* white_snake = new QAction("Белая змея");
    green_snake->setCheckable(true);
    black_snake->setCheckable(true);
    white_snake->setCheckable(true);
    green_snake->setChecked(true);
    color_menu->addActions({green_snake, black_snake, white_snake});
    m_snake_colors = new QActionGroup(this);
    m_snake_colors->addAction(green_snake);
    m_snake_colors->addAction(black_snake);
    m_snake_colors->addAction(white_snake);
    setChecks(m_snake_colors->actions(), m_settings.value("snake", 0).toInt());
    connect(green_snake, &QAction::triggered, [this](){ setSnakeColor(0); });
    connect(black_snake, &QAction::triggered, [this](){ setSnakeColor(1); });
    connect(white_snake, &QAction::triggered, [this](){ setSnakeColor(2); });

    color_menu->addSeparator();
    QAction* yellow_apple = new QAction("Жёлтое яблоко");
    QAction* green_apple = new QAction("Зелёное яблоко");
    yellow_apple->setCheckable(true);
    green_apple->setCheckable(true);
    yellow_apple->setChecked(true);
    color_menu->addActions({yellow_apple, green_apple});
    m_apple_types = new QActionGroup(this);
    m_apple_types->addAction(yellow_apple);
    m_apple_types->addAction(green_apple);
    setChecks(m_apple_types->actions(), m_settings.value("apple", 0).toInt());
    connect(yellow_apple, &QAction::triggered, [this](){ setAppleColor(0); });
    connect(green_apple, &QAction::triggered, [this](){ setAppleColor(1); });
}

void App::showMenu()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    m_stacked_widget->setCurrentWidget(m_menu_screen);
}

void App::continueGame()
{
    m_game->m_timer->start(m_game->m_delay);
    statusBar()->show();
    menuBar()->setVisible(true);
    m_stacked_widget->setCurrentWidget(m_game);
}

void App::startGame()
{
    m_menu_screen->m_continue_game_btn->setVisible(true);
    statusBar()->show();
    menuBar()->setVisible(true);
    m_stacked_widget->setCurrentWidget(m_game);
    m_game->startNewGame();
}

void App::openLeaderboard()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    m_leaderboard->m_table_view->setModel(m_game->getLeaderboardModel());
    m_stacked_widget->setCurrentWidget(m_leaderboard);
}

void App::openSettings()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    m_stacked_widget->setCurrentWidget(m_settings_screen);
}


void App::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}

void App::setChecks(const QList<QAction *> &action_list, int checked_index)
{
    int i = 0;
    for(QAction* action : action_list)
    {
        if (i == checked_index)
            action->setChecked(true);
        else
            action->setChecked(false);
        ++i;
    }
}

void App::setDifficulty(int index)
{
    if(sender() == m_settings_screen->m_difficulty_cmb)
    {
        setChecks(m_difficulties->actions(), index);
    }
    else
    {
        m_settings_screen->m_difficulty_cmb->setCurrentIndex(index);
    }
    switch (index)
    {
    case 0:
        m_game->setDifficultyEasy();
        break;
    case 1:
        m_game->setDifficultyMedium();
        break;
    case 2:
        m_game->setDifficultyHard();
        break;
    }
    m_settings.setValue("difficulty", index);
}

void App::setBackgroundColor(int index)
{
    if(sender() == m_settings_screen->m_background_color_cmb)
    {
        setChecks(m_background_colors->actions(), index);
    }
    else
    {
        m_settings_screen->m_background_color_cmb->setCurrentIndex(index);
    }
    switch (index)
    {
    case 0:
        m_game->setGrayBackground();
        break;
    case 1:
        m_game->setBlueBackground();
        break;
    case 2:
        m_game->setRedBackground();
        break;
    }
    m_settings.setValue("background", index);
}

void App::setSnakeColor(int index)
{
    if(sender() == m_settings_screen->m_snake_color_cmb)
    {
        setChecks(m_snake_colors->actions(), index);
    }
    else
    {
        m_settings_screen->m_snake_color_cmb->setCurrentIndex(index);
    }
    switch (index)
    {
    case 0:
        m_game->setSnakeGreen();
        break;
    case 1:
        m_game->setSnakeBlack();
        break;
    case 2:
        m_game->setSnakeWhite();
        break;
    }
    m_settings.setValue("snake", index);
}

void App::setAppleColor(int index)
{
    if(sender() == m_settings_screen->m_apple_color_cmb)
    {
        setChecks(m_apple_types->actions(), index);
    }
    else
    {
        m_settings_screen->m_apple_color_cmb->setCurrentIndex(index);
    }
    switch (index)
    {
    case 0:
        m_game->setAppleYellow();
        break;
    case 1:
        m_game->setAppleGreen();
        break;
    }
    m_settings.setValue("apple", index);
}
