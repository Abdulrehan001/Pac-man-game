#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define H 15  // this is playfield height
#define W 40  // this is playfield width

char playfield[H][W+1] = {
    "**************",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "* .....................................*",
    "**************"
}; // this is our playfield

int food_collect = 0, game_end = 0;
int py = 1, px = 1; // these variables represent pacman coordinates
int gy1 = 1, gx1 = 38, gy2 = 13, gx2 = 1; // these variables represent ghost coordinates

void game_result() {
    // this function checks if you won the game or not
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    if (food_collect == 500) {
        outtextxy(200, 200, "Congratulation!");
        outtextxy(200, 230, "You won the game!");
    } else {
        outtextxy(200, 200, "Better luck next time!");
        outtextxy(200, 230, "You lost the game!");
    }
    char score[50];
    sprintf(score, "Your total score is %d", food_collect);
    outtextxy(200, 260, score);
    getch();
}

void move_ghosts() {
    if (gy1 == 1 && gx1 > 1) {
        gx1--; // this statement moves the 1st ghost coordinate to the left side
    } else if (gx1 == 1 && gy1 < 7) {
        gy1++; // this statement moves the 1st ghost coordinate down
    } else if (gy1 == 7 && gx1 < 38) {
        gx1++; // this statement moves the 1st ghost coordinate to the right side
    } else if (gx1 == 38 && gy1 > 1) {
        gy1--; // this statement moves the 1st ghost coordinate up
    }

    if (gy2 == 13 && gx2 < 38) {
        gx2++; // this statement moves the 2nd ghost coordinate to the right side
    } else if (gx2 == 38 && gy2 > 7) {
        gy2--; // this statement moves the 2nd ghost coordinate up
    } else if (gy2 == 7 && gx2 > 1) {
        gx2--; // this statement moves the 2nd ghost coordinate to the left side
    } else if (gx2 == 1 && gy2 < 13) {
        gy2++; // this statement moves the 2nd ghost coordinate down
    }
}

void user_input() {
    // this function is used to take user input
    if (kbhit()) {
        char ch = getch();
        switch (ch) {
            case 'w': if (py > 1) py -= 1; break;
            case 's': if (py < H - 2) py += 1; break;
            case 'a': if (px > 1) px -= 1; break;
            case 'd': if (px < W - 2) px += 1; break;
            case 27: game_end = 1; break; // Escape key to exit
        }
    }
}

void setup() {
    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            if (playfield[i][j] == '#') {
                playfield[i][j] = ' ';
            }
            if (playfield[i][j] == '@') {
                playfield[i][j] = '.';
            }
        }
    }
    if (playfield[py][px] == '.') {
        food_collect++;
    }
    if (playfield[py][px] == '*') {
        py = 1;
        px = 1;
    }
    playfield[py][px] = '#';
    playfield[gy1][gx1] = '@';
    playfield[gy2][gx2] = '@';

    if (playfield[py][px] == '@') {
        game_end = 1;
    }
}

void draw_playfield() {
    // this function is used to print the playfield
    cleardevice();
    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            int x = j * 16, y = i * 16;
            if (playfield[i][j] == '*') {
                setfillstyle(SOLID_FILL, RED); // Red for walls
                bar(x, y, x + 16, y + 16);
            } else if (playfield[i][j] == '.') {
                setfillstyle(SOLID_FILL, WHITE); // White for dots
                fillellipse(x + 8, y + 8, 2, 2);
            } else if (playfield[i][j] == '#') {
                setfillstyle(SOLID_FILL, YELLOW); // Yellow for Pac-Man
                bar(x, y, x + 16, y + 16);
            } else if (playfield[i][j] == '@') {
                setfillstyle(SOLID_FILL, BLUE); // Blue for ghosts
                bar(x, y, x + 16, y + 16);
            }
        }
    }

    setcolor(WHITE);
    char score[50];
    sprintf(score, "Score: %d", food_collect);
    outtextxy(10, 10, score);
    delay(200);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (game_end != 1) {
        setup();
        user_input();
        move_ghosts();
        draw_playfield();
    }

    game_result();
    closegraph();

    return 0;
}
