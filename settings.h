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
    QComboBox* difficulty_cmb;
    QComboBox* background_color_cmb;
    QComboBox* snake_color_cmb;
    QComboBox* apple_color_cmb;
    QPushButton* back_to_menu_btn;
    QVBoxLayout* layout;
    QFormLayout* form_layout;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // SETTINGS_H
