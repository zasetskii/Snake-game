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
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "app.h"
#include "recordlistmodel.h"

class Snake : public QWidget
{
    Q_OBJECT

    friend App;

    enum Directions
    {
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_LEFT,
        DIRECTION_RIGHT
    };

    void startNewGame();
    void checkBorders();
    void checkApple();
    void gameOver(QPainter&);
    void saveResult();
    void setLeaderboard();
    RecordListModel* getLeaderboardModel();
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

private:
    QImage m_head;
    QImage m_dot;
    QImage m_apple;
    QVector<QPoint> m_coordinates;
    QPoint m_apple_coordinates;
    QLabel* m_score;
    QTimer* m_timer;
    QQueue<int> m_key_q;

    RecordListModel* m_leaderboard_model;

    int delay;
    Directions cur_direction;
    bool is_game_over = false;
    bool is_growing = false;
    QSize m_size;
};
#endif // SNAKE_H
