#include "leaderboard.h"

Leaderboard::Leaderboard(QWidget *parent)
    : QWidget{parent}
{
    back_to_menu_btn = new QPushButton("Вернуться в меню");
    main_layout = new QVBoxLayout(this);

    m_table_view = new QTableView;
    m_table_view->setShowGrid(false);
    m_table_view->horizontalHeader()->hide();
    m_table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table_view->setSelectionMode(QAbstractItemView::NoSelection);

    QLabel* label = new QLabel("Доска рекордов");
    label->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
    main_layout->addWidget(label, 0, Qt::AlignCenter);
    main_layout->addWidget(m_table_view);
    main_layout->addWidget(back_to_menu_btn);
}
