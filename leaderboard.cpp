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
    m_table_view->setFocusPolicy(Qt::NoFocus);
    m_table_view->setAlternatingRowColors(true);
    m_table_view->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->addSpacing(20);
    h_layout->addWidget(m_table_view);
    h_layout->addSpacing(20);

    QLabel* label = new QLabel("Доска рекордов");
    label->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
    main_layout->addWidget(label, 0, Qt::AlignCenter);
    main_layout->addLayout(h_layout);
    main_layout->addWidget(back_to_menu_btn);
}

void Leaderboard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
