#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>

using namespace std;

class Present {
    private:
        int width, height, length;
    public:
        int id, size;

        Present(int id, int width, int height, int length) {
            this->id = id;
            this->width = width;
            this->height = height;
            this->length = length;
            this->size = width * height * length;
        }
};

bool bigger_size_cmp(Present a, Present b) {
    return a.size > b.size || (a.size == b.size && a.id < b.id);
}


bool id_cmp(Present a, Present b) {
    return a.id < b.id;
}

vector<Present> slice(vector<Present> presents, int max) {
    vector<Present> result;
    for (int i = 0; i < max; i++) {
        result.push_back(presents[i]);
    }
    return result;
}

void print_presents(vector<Present> presents) {
    for (auto present : presents) {
        printf("%d -> %d\n", present.id, present.size);
    }
}

int main() {

    Present p = Present(1, 2, 3, 4);
    assert(p.id == 1);
    assert(p.size == 24);

    int t; scanf("%d", &t);
    while (t--) {
        int total_presents, present_bob_will_receive;
        scanf("%d%d", &total_presents, &present_bob_will_receive);
        
        vector<Present> presents;
        for (int i = 0; i < total_presents; i++) {
            int id, h, w, l; scanf("%d%d%d%d", &id, &h, &w, &l);
            presents.push_back(Present(id, w, h, l));
        }

        sort(presents.begin(), presents.end(), bigger_size_cmp);
        vector<Present> bigger = slice(presents, present_bob_will_receive);
        sort(bigger.begin(), bigger.end(), id_cmp);


        for (int i = 0; i < present_bob_will_receive; i++) {
            if (i == present_bob_will_receive - 1) printf("%d\n", bigger[i].id);
            else printf("%d ", bigger[i].id);
        }
    }

    return 0;
}