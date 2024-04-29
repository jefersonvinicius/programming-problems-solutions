#include <vector>
#include "stdio.h"

using namespace std;

#define MAX 105

struct Position {
    int col, row;
};

class Grid {
    private:
        int walkedCells[MAX][MAX];
        vector<struct Position> steps;

        struct Position nextPosition() {
            vector<struct Position> positions;
            positions.push_back(left(this->current()));
            positions.push_back(right(this->current()));
            positions.push_back(up(this->current()));
            positions.push_back(down(this->current()));
            struct Position* lower = NULL;
            for (struct Position position : positions) {
                if (lower == NULL && !this->hasWalked(position)) {
                    lower = &position;
                } else if (lower != NULL && this->cell(position) < this->cell(*lower) && !this->hasWalked(position)) {
                    lower = &position;
                }
            }
            return *lower;
        }

        int cell(struct Position position) {
            return this->grid[position.row][position.col];
        }

        bool hasWalked(struct Position position) {
            return this->walkedCells[position.row][position.col] == 1;
        }
    public:
        int size;
        int grid[MAX][MAX];

        Grid(int size) {
            this->size = size;
            this->steps.push_back(Position { .row = 0, .col = 0 });
        }

        void set(int row, int col, int value) {
            grid[row][col] = value;
        }

        void walk() {
            while (true) {
                
            }
        }

        struct Position current() {
            return this->steps.back();
        }

        struct Position right(struct Position position) {
            if (position.col == this->size) return position;
            return Position { .col = position.col + 1, .row = position.row };
        }

        struct Position left(struct Position position) {
            if (position.col == 0) return position;
            return Position { .col = position.col - 1, .row = position.row };
        }

        struct Position up(struct Position position) {
            if (position.row == 0) return position;
            return Position { .col = position.col, .row = position.row - 1 };
        }

        struct Position down(struct Position position) {
            if (position.row == this->size) return position;
            return Position { .col = position.col, .row = position.row + 1 };
        }
};

int main() {

    int n;
    while (true) {
        scanf("%d", &n); if (n == 0) break;
        Grid* grid = new Grid(n);
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                int x; scanf("%d", &x);
                grid->set(row, col, x);
            }
        }
    }

    return 0;
}