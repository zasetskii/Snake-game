#include "menuscreen.h"

MenuScreen::MenuScreen(QWidget *parent)
    : QWidget{parent}
{
    continue_game = new QPushButton("Продолжить");
    continue_game->setVisible(false);
    start_game = new QPushButton("Начать игру");
    open_leaderboard = new QPushButton("Доска рекордов");
    open_settings = new QPushButton("Настройки");
    quit_game = new QPushButton("Выйти");
    QVBoxLayout* v_layout = new QVBoxLayout(this);
    v_layout->addWidget(continue_game);
    v_layout->addWidget(start_game);
    v_layout->addWidget(open_leaderboard);
    v_layout->addWidget(open_settings);
    v_layout->addWidget(quit_game);
}
