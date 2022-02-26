#include "settings.h"

Settings::Settings(QWidget *parent)
    : QWidget{parent}, difficulty(new QComboBox), background_color(new QComboBox), snake_color(new QComboBox),
      apple_color(new QComboBox), layout(new QVBoxLayout(this)), back_to_menu(new QPushButton("Вернуться в меню")),
      form_layout(new QFormLayout)
{
    form_layout->addRow("Сложность", difficulty);
    form_layout->addRow("Цвет фона", background_color);
    form_layout->addRow("Цвет змеи", snake_color);
    form_layout->addRow("Вид яблока", apple_color);
    difficulty->addItems({"Легко", "Средне", "Сложно"});
    difficulty->setCurrentIndex(1);
    background_color->addItems({"Серый", "Синий", "Красный"});
    background_color->setCurrentIndex(2);
    snake_color->addItems({"Зелёный", "Чёрный", "Белый"});
    snake_color->setCurrentIndex(0);
    apple_color->addItems({"Жёлтый", "Зелёный"});
    apple_color->setCurrentIndex(0);
    layout->addLayout(form_layout);
    layout->addWidget(back_to_menu);
}
