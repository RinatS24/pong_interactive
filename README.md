Я реализовал Pong в интерактивном режиме (режим игры в реальном времени), используя дополнительные библиотеки для упрощения обработки действий игроков и отображения символьной графики (curses.h). Это программа, представляющую из себя игру для двух игроков, схожую с игрой «Pong». Для отображения графики использовал только символьную (ASCII) графику (с выводом в терминал).

Управление:
A/Z и K/M для перемещения ракеток.

Графика
Поле — прямоугольник 80 на 25 символов.
Размер ракетки — 3 символа.
размер мяча — 1 символ.

UI/UX
После достижения одним из игроков счета в 21 очко, игра выводит поздравление победителя и завершается.

Игра разработана на языке Си, в структурном стиле и работает из терминала;
