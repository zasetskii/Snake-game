#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPainter>

#include "app.h"

class Leaderboard : public QWidget
{
    Q_OBJECT
public:
    explicit Leaderboard(QWidget *parent = nullptr);

    QVBoxLayout* main_layout;
    QPushButton* back_to_menu_btn;

    QTableView* m_table_view;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);

};

#endif // LEADERBOARD_H
