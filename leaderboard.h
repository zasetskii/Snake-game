#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

#include "app.h"

class Leaderboard : public QWidget
{
    Q_OBJECT
public:
    explicit Leaderboard(QWidget *parent = nullptr);

    QGroupBox* group_box;
    QVBoxLayout* layout;
    QVBoxLayout* main_layout;
    QPushButton* back_to_menu_btn;

    void addScore(QString score);
    void clearBoard();

signals:

};

#endif // LEADERBOARD_H
