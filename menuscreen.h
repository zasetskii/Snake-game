#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>

#include "app.h"

class MenuScreen : public QWidget
{
    Q_OBJECT

    friend App;

    QPushButton* m_continue_game_btn;
    QPushButton* m_start_game_btn;
    QPushButton* m_open_settings_btn;
    QPushButton* m_open_leaderboard_btn;
    QPushButton* m_quit_game_btn;

public:
    explicit MenuScreen(QWidget *parent = nullptr);


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // MENUSCREEN_H
