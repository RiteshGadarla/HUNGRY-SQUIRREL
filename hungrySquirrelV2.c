#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

#define HEIGHT 20
#define WIDTH  40
#define MAX_TAIL 200

// Colors
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define CYAN    "\x1B[36m"
#define MAGENTA "\x1B[35m"
#define RESET   "\x1B[0m"

// Game variables
int gameover, score, highScore;
int x, y, fruitx, fruity;
int powerx = -1, powery = -1, powerTimer = 0;
int flag;
int delay;

int tailX[MAX_TAIL], tailY[MAX_TAIL];
int tailLength;

FILE *record;

#ifndef _WIN32
// ---------- Linux Keyboard Handling ----------
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// ---------- Utility ----------
void clearScreen() {
    printf("\033[H\033[J");
}

void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// ---------- Game Functions ----------
void intro() {
    clearScreen();
    printf(YELLOW "HUNGRY SQUIRREL\n" RESET);
    printf("Use W A S D keys\n");
    printf("Eat nuts, avoid walls and your tail\n");
    printf("Press SPACE to start\n");

    while (getch() != ' ');
}

void fruit() {
    fruitx = rand() % (WIDTH - 2) + 1;
    fruity = rand() % (HEIGHT - 2) + 1;

    if (rand() % 5 == 0) {
        powerx = rand() % (WIDTH - 2) + 1;
        powery = rand() % (HEIGHT - 2) + 1;
        powerTimer = 50;
    }
}

void setup() {
    gameover = 0;
    score = 0;
    delay = 120;
    tailLength = 0;

    x = WIDTH / 2;
    y = HEIGHT / 2;
    flag = 3;

    fruit();
}

void draw() {
    clearScreen();

    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {

            if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1)
                printf(RED "#" RESET);

            else if (i == x && j == y)
                printf(YELLOW "Q" RESET);

            else if (i == fruitx && j == fruity)
                printf(CYAN "@" RESET);

            else if (i == powerx && j == powery)
                printf(MAGENTA "$" RESET);

            else {
                int printed = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf(GREEN "o" RESET);
                        printed = 1;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }

    printf("Score: %d | High Score: %d | Level: %d\n",
           score, highScore, score/25 + 1);
}

void input() {
    if (kbhit()) {
        int ch = getch();

        if ((ch == 'a' || ch == 'A') && flag != 3) flag = 1;
        if ((ch == 'd' || ch == 'D') && flag != 1) flag = 3;
        if ((ch == 'w' || ch == 'W') && flag != 2) flag = 4;
        if ((ch == 's' || ch == 'S') && flag != 4) flag = 2;
    }
}

void logic() {
    sleep_ms(delay);

    int prevX = x;
    int prevY = y;

    switch(flag) {
        case 1: x--; break;
        case 2: y++; break;
        case 3: x++; break;
        case 4: y--; break;
    }

    for (int i = tailLength - 1; i > 0; i--) {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    if (tailLength > 0) {
        tailX[0] = prevX;
        tailY[0] = prevY;
    }

    if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1)
        gameover = 1;

    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    if (x == fruitx && y == fruity) {
        score += 5;
        tailLength++;
        fruit();
        if (delay > 50) delay -= 5;
    }

    if (x == powerx && y == powery) {
        score += 15;
        powerx = -1;
    }

    if (powerTimer > 0) powerTimer--;
    else powerx = -1;
}

void outro() {
    printf(RED "Game Over!\n" RESET);

    if (score > highScore) {
        highScore = score;
        printf(MAGENTA "New High Score!\n" RESET);
    }

    record = fopen("HungryGameRecord.txt", "w");
    if (record) {
        fprintf(record, "%d", highScore);
        fclose(record);
    }

    printf("Press R to restart or X to exit\n");

    char ch;
    while (1) {
        ch = getch();
        if (ch == 'r' || ch == 'R') {
            setup();
            break;
        }
        if (ch == 'x' || ch == 'X') {
            exit(0);
        }
    }
}

int main() {
    srand(time(NULL));

    record = fopen("HungryGameRecord.txt", "r");
    if (record) {
        fscanf(record, "%d", &highScore);
        fclose(record);
    }

    intro();
    setup();

    while (1) {
        while (!gameover) {
            draw();
            input();
            logic();
        }
        outro();
    }
}
