#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QKeyEvent>
#include <QApplication>
#include <QRandomGenerator>
#include <QTimer>
#include <QLabel>
#include <QStatusBar>
#include <QQueue>
#include <QMenu>
#include <QMenuBar>
#include <QTextStream>
#include <QFile>
#include <QMap>

#include "app.h"

class Snake : public QWidget
{
    Q_OBJECT

    friend App;

    QImage head;
    QImage dot;
    QImage apple;
    QVector<QPoint> coordinates;
    QPoint apple_coordinates;
    QLabel* score;
    int delay;

    enum Directions
    {
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_LEFT,
        DIRECTION_RIGHT
    };

    Directions cur_direction;
    QTimer* timer;
    bool is_game_over = false;
    bool is_growing = false;
    QQueue<int> key_q;
    QMap<int, QString> leaderboard;

    void startNewGame();
    void checkBorders();
    void checkApple();
    void gameOver(QPainter&);
    void saveResult();
    void setLeaderboard();
    QMap<int, QString> getLeaderboard();
    void generateApple();
    void processKeyPressed();


public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

signals:
    void escPressed();
    void gameIsOver();

private slots:
    void onTimer();
    void setDifficulty(int index);
    void setDifficultyEasy();
    void setDifficultyMedium();
    void setDifficultyHard();
    void setBackgroundColor(int index);
    void setGrayBackground();
    void setBlueBackground();
    void setRedBackground();
    void setSnakeColor(int index);
    void setSnakeGreen();
    void setSnakeBlack();
    void setSnakeWhite();
    void setAppleColor(int index);
    void setAppleYellow();
    void setAppleGreen();

protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
};
#endif // SNAKE_H
