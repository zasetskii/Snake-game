#include "app.h"
#include "snake.h"
#include "menuscreen.h"
#include "settings.h"
#include "leaderboard.h"

App::App(QWidget *parent) : QMainWindow(parent), m_size(300, 350)
{
    game = new Snake(this);
    menu_screen = new MenuScreen(this);
    stacked_widget = new QStackedWidget;
    settings_screen = new Settings(this);
    leaderboard = new Leaderboard(this);

    resize(m_size);
    setMinimumSize(m_size);
    setMaximumSize(m_size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    stacked_widget->addWidget(menu_screen);
    stacked_widget->addWidget(settings_screen);
    stacked_widget->addWidget(game);
    stacked_widget->addWidget(leaderboard);
    setCentralWidget(stacked_widget);
    statusBar()->addWidget(game->m_score);
    makeDifficultyMenu();
    makeColorMenu();
//    game->setDifficultyMedium();
//    game->setRedBackground();
//    game->setSnakeGreen();
//    game->setAppleYellow();

    showMenu();

    connect(menu_screen->start_game_btn, &QPushButton::pressed, this, &App::startGame);
    connect(menu_screen->open_leaderboard_btn, &QPushButton::pressed, this, &App::openLeaderboard);
    connect(menu_screen->open_settings_btn, &QPushButton::pressed, this, &App::openSettings);
    connect(menu_screen->quit_game_btn, &QPushButton::pressed, qApp, QApplication::quit);
    connect(menu_screen->continue_game_btn, &QPushButton::pressed, this, &App::continueGame);
    connect(settings_screen->difficulty_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), game, &Snake::setDifficulty);
    connect(settings_screen->background_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), game, &Snake::setBackgroundColor);
    connect(settings_screen->snake_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), game, &Snake::setSnakeColor);
    connect(settings_screen->apple_color_cmb, QOverload<int>::of(&QComboBox::currentIndexChanged), game, &Snake::setAppleColor);
    connect(settings_screen->back_to_menu_btn, &QPushButton::pressed, this, &App::showMenu);
    connect(leaderboard->back_to_menu_btn, &QPushButton::pressed, this, &App::showMenu);
    connect(game, &Snake::escPressed, this, &App::showMenu);
    connect(game, &Snake::gameIsOver, menu_screen->continue_game_btn, &QPushButton::hide);
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
    connect(easy, &QAction::triggered, game, &Snake::setDifficultyEasy);
    connect(medium, &QAction::triggered, game, &Snake::setDifficultyMedium);
    connect(hard, &QAction::triggered, game, &Snake::setDifficultyHard);
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
    connect(gray_background, &QAction::triggered, game, &Snake::setGrayBackground);
    connect(blue_background, &QAction::triggered, game, &Snake::setBlueBackground);
    connect(red_background, &QAction::triggered, game, &Snake::setRedBackground);
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
    connect(green_snake, &QAction::triggered, game, &Snake::setSnakeGreen);
    connect(black_snake, &QAction::triggered, game, &Snake::setSnakeBlack);
    connect(white_snake, &QAction::triggered, game, &Snake::setSnakeWhite);

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
    connect(yellow_apple, &QAction::triggered, game, &Snake::setAppleYellow);
    connect(green_apple, &QAction::triggered, game, &Snake::setAppleGreen);
}

void App::showMenu()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    stacked_widget->setCurrentWidget(menu_screen);
}

void App::continueGame()
{
    game->m_timer->start(game->delay);
    statusBar()->show();
    menuBar()->setVisible(true);
    stacked_widget->setCurrentWidget(game);
}

void App::startGame()
{
    menu_screen->continue_game_btn->setVisible(true);
    statusBar()->show();
    menuBar()->setVisible(true);
    stacked_widget->setCurrentWidget(game);
    game->startNewGame();
}

void App::openLeaderboard()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    leaderboard->m_table_view->setModel(game->getLeaderboardModel());
    stacked_widget->setCurrentWidget(leaderboard);
}

void App::openSettings()
{
    statusBar()->hide();
    menuBar()->setVisible(false);
    stacked_widget->setCurrentWidget(settings_screen);
}


void App::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}
