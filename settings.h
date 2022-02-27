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

    QComboBox* difficulty_cmb;
    QComboBox* background_color_cmb;
    QComboBox* snake_color_cmb;
    QComboBox* apple_color_cmb;
    QPushButton* back_to_menu_btn;
    QVBoxLayout* layout;
    QFormLayout* form_layout;

    friend App;

public:
    explicit Settings(QWidget *parent = nullptr);

};

#endif // SETTINGS_H
