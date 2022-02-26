#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>

#include "app.h"

class Settings : public QWidget
{
    Q_OBJECT

    QComboBox* difficulty;
    QComboBox* background_color;
    QComboBox* snake_color;
    QComboBox* apple_color;
    QPushButton* back_to_menu;
    QVBoxLayout* layout;
    QFormLayout* form_layout;

    friend App;

public:
    explicit Settings(QWidget *parent = nullptr);

};

#endif // SETTINGS_H
