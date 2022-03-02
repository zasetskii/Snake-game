#include "menuscreen.h"

MenuScreen::MenuScreen(QWidget *parent)
    : QWidget{parent}
{
    m_continue_game_btn = new QPushButton("Продолжить");
    m_continue_game_btn->setVisible(false);
    m_start_game_btn = new QPushButton("Начать игру");
    m_open_leaderboard_btn = new QPushButton("Доска рекордов");
    m_open_settings_btn = new QPushButton("Настройки");
    m_quit_game_btn = new QPushButton("Выйти");
    QVBoxLayout* v_layout = new QVBoxLayout(this);
    v_layout->addWidget(m_continue_game_btn);
    v_layout->addWidget(m_start_game_btn);
    v_layout->addWidget(m_open_leaderboard_btn);
    v_layout->addWidget(m_open_settings_btn);
    v_layout->addWidget(m_quit_game_btn);
}

void MenuScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
