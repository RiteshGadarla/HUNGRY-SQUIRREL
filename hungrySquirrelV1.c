#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

// For Boundary
short height = 15, width = 25;
// Game Logics
short gameover, score, h_score = 0, key, flag, START, EXIT;
// Squirrel and Nut
short x, y, fruitx, fruity;
// For Speed of Squirrel
int delay;

FILE *record; // For saving high score into a file

// Text Colours
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
// Background Colours
#define YELLOW_BG "\x1B[43m"
// Reset to Original Colour
#define RESET "\x1B[0m"

// Game Functions
short intro();    // Intro
void setup();     // Generating base of Game
void fruit();     // Generate Random Fruit
void draw();      // Generating Each Frame
void input();     // For Input
void logic();     // Game Logics
short outro();    // Outro

int main() {
    record = fopen("HungryGameRecord.txt", "r");
    fscanf(record, "%hd", &h_score);
    fclose(record);
    printf("\e[?25l"); // To hide cursor in the terminal
    intro();
    start:
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
    }
    if (outro() == 1)
        goto start;
}

short intro() { // Introduction to game
    system("cls"); // To clear terminal
    printf("\n                 " YELLOW_BG BLUE " HUNGRY SQUIRREL " RESET);
    usleep(750000);
    printf("\n\n Welcome to the game!!!\n");
    printf(" Your goal is to guide the Squirrel to munch on nuts\n without hitting wall.\n");
    printf(" Fast reflexes and precision are your keys to a high\n score in this game!\n\n");
    printf(" Instructions to play game:\n");
    printf(" >>> Use Arrow (or) WASD keys for movement.\n >>> Avoid hitting wall.\n");
    printf(" >>> Speed of squirrel increases as you eat more nuts!\n");
    printf(" >>> Each nut consumed gives 5 points.\n\n");
    printf(YELLOW " 'Q'" RESET "-> Squirrel   " CYAN "'@'" RESET "-> Nut\n\n");
    printf(" Press " MAGENTA "SPACE" RESET " key to start game");
    come_again:
    START = getch();
    if (START == ' ') {
        Beep(500, 500);
        system("cls");
        printf(GREEN "\n\n\n\n\n\n        Good Luck!!" RESET);
        sleep(1);
        return 0;
    } else
        goto come_again;
}

void setup() { // Function to generate the squirrel & nut
    gameover = 0;
    x = (short) (width * 0.5);
    y = (short) (height * 0.75);
    fruit();
    flag = 4;
    delay = 133000; // 133000 μs ~ 0.13 sec
    score = 0;
}

void fruit() {
    srand(time(NULL)); // To increase randomness of rand function
    respawn: // Generating new fruit
    fruitx = rand() % (width - 2) + 1;
    fruity = rand() % (height - 2) + 1;
    if (fruitx == x || fruity == y)
        goto respawn;
}

void draw() { // Function to draw the boundaries
    system("cls"); // To refresh screen each time
    printf("\n");
    for (short j = 0; j < height; j++) {
        for (short i = 0; i < width; i++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
                printf("X");
            else {
                if (i == x && j == y)
                    printf(YELLOW "Q" RESET);
                else if (i == fruitx && j == fruity)
                    printf(CYAN "@" RESET);
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("\nScore: %d\n", score);
    if (score <= h_score)
        printf("(High Score: %d)\n", h_score);
    else
        printf("New High Score!\n");
}

void input() { // Function to take the input
    if (kbhit()) { // To see if any input is there
        key = getch();
        if (key == 0xE0) { // Check for arrow key input
            switch (getch()) {
                case 72: // Up arrow key
                    if (flag != 2)
                        flag = 4;
                    break;
                case 75: // Left arrow key
                    if (flag != 3)
                        flag = 1;
                    break;
                case 80: // Down arrow key
                    if (flag != 4)
                        flag = 2;
                    break;
                case 77: // Right arrow key
                    if (flag != 1)
                        flag = 3;
                    break;
            }
        } else {
            switch (key) {
                case 'W': // Up arrow key
                case 'w':
                    if (flag != 2)
                        flag = 4;
                    break;
                case 'A': // Left arrow key
                case 'a':
                    if (flag != 3)
                        flag = 1;
                    break;
                case 'S': // Down arrow key
                case 's':
                    if (flag != 4)
                        flag = 2;
                    break;
                case 'D': // Right arrow key
                case 'd':
                    if (flag != 1)
                        flag = 3;
                    break;
            }
        }
    }
}

void logic() { // Function for the logic behind each movement
    usleep(delay); // Speed control, less the value of delay more the speed
    switch (flag) {
        case 1:
            x--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x++;
            break;
        case 4:
            y--;
            break;
        default:
            break;
    }
    // If the game is over
    if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1) {
        Beep(1200, 500);
        gameover = 1;
    }
    // If squirrel reaches the nut then update the score and speed
    if (x == fruitx && y == fruity) {
        Beep(800, 50);
        score += 5;
        fruit();
        if (delay > 0)
            delay -= 7000;
    }
}

short outro() { // Outro for the game
    printf(RED "\nThe Squirrel hit the wall and fainted!\nGame Over!\n" RESET);
    if (score > h_score) {
        usleep(750000);
        printf(MAGENTA "\nCongrats!!! New High Score!" RESET);
        printf("\n(Previous High Score: %d)\n", h_score);
        h_score = score;
    }
    printf("\nPress 'R' to restart (or) 'X' to exit");
    again:
    EXIT = getch();
    if (EXIT == 'R' || EXIT == 'r') {
        return 1;
    } else if (EXIT == 'X' || EXIT == 'x') {
        printf(RED "\n\nClosing Terminal...\n");
        record = fopen("HungryGameRecord.txt", "w");
        fprintf(record, "%d", h_score);
        fclose(record);
        sleep(1);
        return 0;
    } else
        goto again;
}