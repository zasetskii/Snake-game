#include "app.h"
#include "snake.h"
#include "menuscreen.h"
#include "settings.h"
#include "leaderboard.h"

App::App(QWidget *parent) : QMainWindow(parent), m_size(300, 350)
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

    showMenu();

    connect(m_menu_screen->m_start_game_btn, &QPushButton::clicked, this, &App::startGame);
    connect(m_menu_screen->m_open_leaderboard_btn, &QPushButton::clicked, this, &App::openLeaderboard);
    connect(m_menu_screen->m_open_settings_btn, &QPushButton::clicked, this, &App::openSettings);
    connect(m_menu_screen->m_quit_game_btn, &QPushButton::clicked, qApp, QApplication::quit);
    connect(m_menu_screen->m_continue_game_btn, &QPushButton::clicked, this, &App::continueGame);
    connect(m_settings_screen->m_difficulty_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), m_game, &Snake::setDifficulty);
    connect(m_settings_screen->m_background_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), m_game, &Snake::setBackgroundColor);
    connect(m_settings_screen->m_snake_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), m_game, &Snake::setSnakeColor);
    connect(m_settings_screen->m_apple_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), m_game, &Snake::setAppleColor);
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
    medium->setChecked(true);
    QAction* hard = new QAction("Сложно");
    hard->setCheckable(true);
    QActionGroup* difficulties = new QActionGroup(this);
    difficulties->addAction(easy);
    difficulties->addAction(medium);
    difficulties->addAction(hard);
    difficulty_menu->addAction(easy);
    difficulty_menu->addAction(medium);
    difficulty_menu->addAction(hard);
    connect(easy, &QAction::triggered, m_game, &Snake::setDifficultyEasy);
    connect(medium, &QAction::triggered, m_game, &Snake::setDifficultyMedium);
    connect(hard, &QAction::triggered, m_game, &Snake::setDifficultyHard);
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
    QActionGroup* background_colors = new QActionGroup(this);
    background_colors->addAction(gray_background);
    background_colors->addAction(blue_background);
    background_colors->addAction(red_background);
    connect(gray_background, &QAction::triggered, m_game, &Snake::setGrayBackground);
    connect(blue_background, &QAction::triggered, m_game, &Snake::setBlueBackground);
    connect(red_background, &QAction::triggered, m_game, &Snake::setRedBackground);

    color_menu->addSeparator();
    QAction* green_snake = new QAction("Зелёная змея");
    QAction* black_snake = new QAction("Чёрная змея");
    QAction* white_snake = new QAction("Белая змея");
    green_snake->setCheckable(true);
    black_snake->setCheckable(true);
    white_snake->setCheckable(true);
    green_snake->setChecked(true);
    color_menu->addActions({green_snake, black_snake, white_snake});
    QActionGroup* snake_colors = new QActionGroup(this);
    snake_colors->addAction(green_snake);
    snake_colors->addAction(black_snake);
    snake_colors->addAction(white_snake);
    connect(green_snake, &QAction::triggered, m_game, &Snake::setSnakeGreen);
    connect(black_snake, &QAction::triggered, m_game, &Snake::setSnakeBlack);
    connect(white_snake, &QAction::triggered, m_game, &Snake::setSnakeWhite);

    color_menu->addSeparator();
    QAction* yellow_apple = new QAction("Жёлтое яблоко");
    QAction* green_apple = new QAction("Зелёное яблоко");
    yellow_apple->setCheckable(true);
    green_apple->setCheckable(true);
    yellow_apple->setChecked(true);
    color_menu->addActions({yellow_apple, green_apple});
    QActionGroup* apple_types = new QActionGroup(this);
    apple_types->addAction(yellow_apple);
    apple_types->addAction(green_apple);
    connect(yellow_apple, &QAction::triggered, m_game, &Snake::setAppleYellow);
    connect(green_apple, &QAction::triggered, m_game, &Snake::setAppleGreen);
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
