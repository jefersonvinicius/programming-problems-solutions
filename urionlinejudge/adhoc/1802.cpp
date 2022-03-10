#include <stdio.h>

#define MAX_BOOKS 11

int main() {

    int portuguese[MAX_BOOKS], math[MAX_BOOKS], physics[MAX_BOOKS], chemistry[MAX_BOOKS], biology[MAX_BOOKS];
    int portuguese_qty, math_qty, physics_qty, chemistry_qty, biology_qty;
    int portuguese_current = 0, math_current = 0, physics_current = 0, chemistry_current = 0, biology_current = 0;
    
    scanf("%d", &portuguese_qty);
    for (int i = 0; i < portuguese_qty; i++) scanf("%d", &portuguese[i]);

    scanf("%d", &math_qty);
    for (int i = 0; i < math_qty; i++) scanf("%d", &math[i]);

    scanf("%d", &physics_qty);
    for (int i = 0; i < physics_qty; i++) scanf("%d", &physics[i]);

    scanf("%d", &chemistry_qty);
    for (int i = 0; i < chemistry_qty; i++) scanf("%d", &chemistry[i]);
    
    scanf("%d", &biology_qty);
    for (int i = 0; i < biology_qty; i++) scanf("%d", &biology[i]);

    

    return 0;
}