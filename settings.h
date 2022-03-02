#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSettings>
#include <QPainter>

#include "app.h"

class Settings : public QWidget
{
    Q_OBJECT

    friend App;

public:
    explicit Settings(QWidget *parent = nullptr);

private:
    QSettings m_settings;
    QComboBox* m_difficulty_cmb;
    QComboBox* m_background_color_cmb;
    QComboBox* m_snake_color_cmb;
    QComboBox* m_apple_color_cmb;
    QPushButton* m_back_to_menu_btn;
    QVBoxLayout* m_layout;
    QFormLayout* m_form_layout;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // SETTINGS_H
