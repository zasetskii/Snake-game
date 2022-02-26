#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QMap>

class Snake;
class MenuScreen;
class Settings;
class Leaderboard;

class App : public QMainWindow
{
    Q_OBJECT

    void makeDifficultyMenu();
    void makeColorMenu();
    void showStartScreen();
    void startGame();
    void continueGame();
    void openLeaderboard();
    void openSettings();
    void showMenu();

    //Сделать синглтоны
    Snake* game;
    QStackedWidget* stacked_widget;
    MenuScreen* menu_screen;
    Settings* settings_screen;
    Leaderboard* leaderboard;

public:
    explicit App(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);

};

#endif // APP_H
