#include "settings.h"

Settings::Settings(QWidget *parent)
    : QWidget{parent}
{
    difficulty_cmb = new QComboBox;
    background_color_cmb = new QComboBox;
    snake_color_cmb = new QComboBox;
    apple_color_cmb = new QComboBox;
    back_to_menu_btn = new QPushButton("Вернуться в меню");
    form_layout = new QFormLayout;
    layout = new QVBoxLayout(this);

    form_layout->addRow("Сложность", difficulty_cmb);
    form_layout->addRow("Цвет фона", background_color_cmb);
    form_layout->addRow("Цвет змеи", snake_color_cmb);
    form_layout->addRow("Вид яблока", apple_color_cmb);
    difficulty_cmb->addItems({"Легко", "Средне", "Сложно"});
    difficulty_cmb->setCurrentIndex(1);
    background_color_cmb->addItems({"Серый", "Синий", "Красный"});
    background_color_cmb->setCurrentIndex(2);
    snake_color_cmb->addItems({"Зелёный", "Чёрный", "Белый"});
    snake_color_cmb->setCurrentIndex(0);
    apple_color_cmb->addItems({"Жёлтый", "Зелёный"});
    apple_color_cmb->setCurrentIndex(0);
    layout->addLayout(form_layout);
    layout->addWidget(back_to_menu_btn);
}
