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

    Snake* m_game;
    QStackedWidget* m_stacked_widget;
    MenuScreen* m_menu_screen;
    Settings* m_settings_screen;
    Leaderboard* m_leaderboard;

public:
    explicit App(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    QSize m_size;

};

#endif // APP_H
