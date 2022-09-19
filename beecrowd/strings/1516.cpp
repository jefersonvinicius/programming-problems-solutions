#include <stdio.h>
#include <string.h>

using namespace std;

void printRowResized(char row[], int width, int factor) {
    for (int c = 0; c < width; c++) {
        for (int f = 0; f < factor; f++) {
            printf("%c", row[c]);
        }
    }
}

int main() {

    int height, width, heightDesired, widthDesired;
    while (true) {
        scanf("%d%d", &height, &width);
        if (height == 0 && width == 0) break;

        char image[height][width];
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                scanf(" %c", &image[r][c]);
            }
        }

        scanf("%d%d", &heightDesired, &widthDesired);

        int rowFactor = widthDesired / width;
        int columnFactor = heightDesired / height;
        for (int r = 0; r < height; r++) {
            for (int cf = 0; cf < columnFactor; cf++) {
                printRowResized(image[r], width, rowFactor);
                printf("\n");
            }
        }
        printf("\n");
    } 

    return 0;
}