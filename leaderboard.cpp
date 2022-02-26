#include "leaderboard.h"

Leaderboard::Leaderboard(QWidget *parent)
    : QWidget{parent}, group_box(new QGroupBox("Доска рекордов")), layout(new QVBoxLayout), main_layout(new QVBoxLayout(this))
{
    back_to_menu = new QPushButton("Вернуться в меню");
    group_box->setLayout(layout);
    main_layout->addWidget(group_box);
    main_layout->addWidget(back_to_menu);
}

void Leaderboard::addScore(QString score)
{
    layout->addWidget(new QLabel(score));
}

void Leaderboard::clearBoard()
{
    QLayoutItem* item;
    while((item = layout->takeAt(0)) != 0)
    {
        delete item->widget();
        delete item;
    }
}
