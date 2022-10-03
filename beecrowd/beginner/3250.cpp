#include "stdio.h"
#include "string.h"

#define MAX_FLOORS 1000002

int main() {

    int floors, start, goal, up, down; scanf("%d%d%d%d%d", &floors, &start, &goal, &up, &down);

    int press = 0, current = start;
    int visited[MAX_FLOORS]; for (int i = 0; i < MAX_FLOORS; i++) visited[i] = 0;
    
    while (true) {
        if (visited[current] == 1) {
            press = -1;
            break;
        }

        if (current == goal) break;

        visited[current] = 1;
        if (current < goal && current + up <= floors) {
            current += up;
            press++;
        } else if (current - down >= 0) {
            current -= down;
            press++;
        }
    }   

    if (press == -1) {
        printf("use the stairs\n");
    } else {
        printf("%d\n", press);
    }

    return 0;
}