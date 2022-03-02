#include "settings.h"

Settings::Settings(QWidget *parent)
    : QWidget{parent}, m_settings("Organization", "Snake")
{
    m_difficulty_cmb = new QComboBox;
    m_background_color_cmb = new QComboBox;
    m_snake_color_cmb = new QComboBox;
    m_apple_color_cmb = new QComboBox;
    m_back_to_menu_btn = new QPushButton("Вернуться в меню");
    m_form_layout = new QFormLayout;
    m_layout = new QVBoxLayout(this);

    m_form_layout->addRow("Сложность", m_difficulty_cmb);
    m_form_layout->addRow("Цвет фона", m_background_color_cmb);
    m_form_layout->addRow("Цвет змеи", m_snake_color_cmb);
    m_form_layout->addRow("Вид яблока", m_apple_color_cmb);
    m_difficulty_cmb->addItems({"Легко", "Средне", "Сложно"});
    m_difficulty_cmb->setCurrentIndex(m_settings.value("difficulty", 1).toInt());
    m_background_color_cmb->addItems({"Серый", "Синий", "Красный"});
    m_background_color_cmb->setCurrentIndex(m_settings.value("background", 2).toInt());
    m_snake_color_cmb->addItems({"Зелёный", "Чёрный", "Белый"});
    m_snake_color_cmb->setCurrentIndex(m_settings.value("snake", 0).toInt());
    m_apple_color_cmb->addItems({"Жёлтый", "Зелёный"});
    m_apple_color_cmb->setCurrentIndex(m_settings.value("apple", 0).toInt());
    m_layout->addLayout(m_form_layout);
    m_layout->addWidget(m_back_to_menu_btn);
}

void Settings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
