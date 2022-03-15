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
#include <QSettings>

class Snake;
class MenuScreen;
class Settings;
class Leaderboard;

class App : public QMainWindow
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

private:
    void makeDifficultyMenu();
    void makeColorMenu();
    void showStartScreen();
    void startGame();
    void continueGame();
    void openLeaderboard();
    void openSettings();
    void showMenu();
    void setChecks(const QList<QAction*>& action_list, int checked_index);

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void setDifficulty(int index);
    void setBackgroundColor(int index);
    void setSnakeColor(int index);
    void setAppleColor(int index);

private:
    QSize m_size;
    Snake* m_game;
    QStackedWidget* m_stacked_widget;
    MenuScreen* m_menu_screen;
    Settings* m_settings_screen;
    Leaderboard* m_leaderboard;
    QSettings m_settings;

    QActionGroup* m_difficulties;
    QActionGroup* m_background_colors;
    QActionGroup* m_snake_colors;
    QActionGroup* m_apple_types;

};

#endif // APP_H
