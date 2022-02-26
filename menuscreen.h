#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "app.h"

class MenuScreen : public QWidget
{
    Q_OBJECT

    friend App;

    QPushButton* continue_game;
    QPushButton* start_game;
    QPushButton* open_settings;
    QPushButton* open_leaderboard;
    QPushButton* quit_game;

public:
    explicit MenuScreen(QWidget *parent = nullptr);

};

#endif // MENUSCREEN_H
