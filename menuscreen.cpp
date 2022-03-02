#include "menuscreen.h"

MenuScreen::MenuScreen(QWidget *parent)
    : QWidget{parent}
{
    continue_game_btn = new QPushButton("Продолжить");
    continue_game_btn->setVisible(false);
    start_game_btn = new QPushButton("Начать игру");
    open_leaderboard_btn = new QPushButton("Доска рекордов");
    open_settings_btn = new QPushButton("Настройки");
    quit_game_btn = new QPushButton("Выйти");
    QVBoxLayout* v_layout = new QVBoxLayout(this);
    v_layout->addWidget(continue_game_btn);
    v_layout->addWidget(start_game_btn);
    v_layout->addWidget(open_leaderboard_btn);
    v_layout->addWidget(open_settings_btn);
    v_layout->addWidget(quit_game_btn);
}

void MenuScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
