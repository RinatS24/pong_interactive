#include <curses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define WIN_SCORE 21
#define DELAY 150000

void menu() {
    printw(
        "|--------------------------------------------------------------------"
        "------------|\n");
    printw(
        "|                             Welcome to Pong!           "
        "                        |\n");
    printw(
        "|                     Control keys for left player: A/Z"
        "                          |\n");
    printw(
        "|                     Control keys for right player: K/M"
        "                         |\n");
    printw(
        "|                           For exit the game press Q "

        "                           |\n");
    printw(
        "|                               Press enter.                         "
        "            |\n");
    printw(
        "|--------------------------------------------------------------------"
        "------------|\n");

    while (getch() != '\n') {
    }
}

void drawfield(int leftPaddleY, int rightPaddleY, int leftScore, int rightScore, int BallX, int BallY) {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == WIDTH / 2) printw("|");
            if ((x == 0 || x == WIDTH - 1)) {
                mvprintw(y, x, "|");
            } else if (y == 0 || y == HEIGHT - 1) {
                mvprintw(y, x, "-");
            } else if (x == 2 && y >= leftPaddleY && y < leftPaddleY + 3) {
                mvprintw(y, x, "]");
            } else if (x == WIDTH - 3 && y >= rightPaddleY && y < rightPaddleY + 3) {
                mvprintw(y, x, "[");
            } else if (x == BallX && y == BallY) {
                mvprintw(y, x, "*");
            } else
                printw(" ");
        }
        printw("\n");
    }
    mvprintw(HEIGHT, 0, "Score: %02d %02d\n", leftScore, rightScore);
    refresh();
}

int movePaddle(int PaddleY, int coord) {
    PaddleY += coord;
    if (PaddleY < 1) PaddleY = 1;
    if (PaddleY > HEIGHT - 4) PaddleY = HEIGHT - 4;
    return PaddleY;
}

int main() {
    int leftPaddleY = HEIGHT / 2 - 1;
    int rightPaddleY = HEIGHT / 2 - 1;
    int leftScore = 0, rightScore = 0;
    int BallX = WIDTH / 2, BallY = HEIGHT / 2;
    int dx = -1, dy = -1;
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    menu();
    while (leftScore < WIN_SCORE && rightScore < WIN_SCORE) {
        drawfield(leftPaddleY, rightPaddleY, leftScore, rightScore, BallX, BallY);
        int ch = getch();
        if (ch != ERR) {
            if (ch == 'q') {
                endwin();
                printf("You closed the game\n");
                return 0;
            }
            if (ch == 'a') leftPaddleY = movePaddle(leftPaddleY, -1);
            if (ch == 'z') leftPaddleY = movePaddle(leftPaddleY, 1);
            if (ch == 'k') rightPaddleY = movePaddle(rightPaddleY, -1);
            if (ch == 'm') rightPaddleY = movePaddle(rightPaddleY, 1);
        }
        BallX += dx;
        BallY += dy;
        if (BallY <= 1 || BallY >= HEIGHT - 2) dy = -dy;
        if (BallX == 3 && BallY >= leftPaddleY && BallY < leftPaddleY + 3) dx = -dx;
        if (BallX == WIDTH - 4 && BallY >= rightPaddleY && BallY < rightPaddleY + 3) dx = -dx;
        if (BallX <= 0) {
            (rightScore)++;
            BallX = WIDTH / 2;
            BallY = HEIGHT / 2;
            dx = -1, dy = -1;
        }
        if (BallX >= WIDTH - 1) {
            (leftScore)++;
            BallX = WIDTH / 2;
            BallY = HEIGHT / 2;
            dx = 1, dy = 1;
        }
        usleep(DELAY);
    }
    endwin();
    if (leftScore >= 21) printf("Congratulations to left player!");
    if (rightScore >= 21) printf("Congratulations to right player!");
    return 0;
}