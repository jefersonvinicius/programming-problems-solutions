#include "stdio.h"
#include "stdlib.h"

enum Directions {
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4,
    NO_DIRECTION = 5
};

struct Position {
    int x, y;
};

struct Position* create_position(int x, int y) {
    struct Position* pos = (struct Position*) malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}

void move(struct Position* position, Directions to) {
    if (to == LEFT) {
        position->x--;
    } else if (to == RIGHT) {
        position->x++;
    } else if (to == UP) {
        position->y--;
    } else if (to == DOWN) {
        position->y++;
    }
}

bool is_out_of_map(struct Position* position, int width, int height) {
    return position->x >= width || position->x < 0 || position->y >= height || position->y < 0;
}

int main() {

    int width; scanf("%d", &width);
    int height; scanf("%d", &height);
    
    char map[height][width];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            char c; scanf(" %c", &c);
            map[row][col] = c;
        }
    }

    Directions dir = NO_DIRECTION;
    struct Position* position = create_position(0, 0);
    bool found_chest = false;
    int walked_map[height][width];
    for (int r = 0; r < height; r++) for (int c = 0; c < width; c++) walked_map[r][c] = 0;

    while (true) {
        if (is_out_of_map(position, width, height) || walked_map[position->y][position->x] == 1) {
            break;
        }

        if (map[position->y][position->x] == '*') {
            found_chest = true;
            break;
        }
        
        if (map[position->y][position->x] == '<') {
            dir = LEFT;
        } else if (map[position->y][position->x] == '>') {
            dir = RIGHT;
        } else if (map[position->y][position->x] == '^') {
            dir = UP;
        } else if (map[position->y][position->x] == 'v') {
            dir = DOWN;
        }
        walked_map[position->y][position->x] = 1;
        move(position, dir);
    }

    if (found_chest) printf("*\n"); 
    else printf("!\n");

    return 0;
}