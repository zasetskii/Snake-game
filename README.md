# Snake-game

## Описание
Игра «Змейка». Размер поля фиксированный, выходить за его пределы запрещено. Игра имеет 3 уровня сложности, позволяет выбрать цвет поля, змеи, яблока из нескольких вариантов. Доска рекордов отображает 10 лучших результатов. Новые рекорды сохраняются в `scoreboard.txt` файл в формате JSON.
<p align="center">
<img src="https://github.com/zasetskii/Snake-game/blob/main/readme_images/snake-game.gif"> </p>

## Описание классов
[`App`](https://github.com/zasetskii/Snake-game/blob/main/app.h) – главный виджет приложения, содержащий в себе все последующие виджеты и связывающий их между собой. Управление отображением дочерних виджетов осуществляется с помощью экземпляра класса QStackedWidget. Наследуется от `QMainWindow`.<br>
[`Snake`](https://github.com/zasetskii/Snake-game/blob/main/snake.h) – виджет, реализующий рабочую логику игры. Наследуется от `QWidget`.<br>
[`MenuScreen`](https://github.com/zasetskii/Snake-game/blob/main/menuscreen.h) – виджет главного экрана. Наследуется от `QWidget`.<br>
[`Leaderboard`](https://github.com/zasetskii/Snake-game/blob/main/leaderboard.h) – виджет доски рекордов. Наследуется от `QWidget`.<br>
[`Settings`](https://github.com/zasetskii/Snake-game/blob/main/settings.h) – виджет настроек. Наследуется от `QWidget`.<br>
[`RecordListModel`](https://github.com/zasetskii/Snake-game/blob/main/recordlistmodel.h) – модель данных, используемая для хранения рекордов. Наследуется от `QAbstractListModel`.

## Логика работы игры
Поле разбивается на клетки размером 10x10. Координаты каждого сегмента змеи хранятся в векторе `m_coordinates`. Работу приложения задаёт таймер, интервал срабатывания которого задаётся уровнем сложности. В слоте на сгенерированный таймером сигнал происходят обработка нажатых клавиш `processKeyPressed()`, проверка на выход за пределы поля `checkBorders()`, проверка совпадения координат головы змеи и координат яблока `checkApple()`, вызывается событие перерисовки виджета `repaint()`.
Нажатые клавиши стрелок добавляются в очередь `m_key_q` и обрабатываются в слоте таймера по одной за раз.

## Скачать
https://disk.yandex.ru/d/F0PbKKBRXOhXKQ
1. Распаковать
2. Запустить game.exe
