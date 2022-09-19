#include <stdio.h>
#include <queue>
#include <stack>
#include <string>

using namespace std;

int main() {

    int amountOfActions, actionType, value;
    while (scanf("%d", &amountOfActions) != EOF) {
        stack<int> stack;
        queue<int> queue;
        priority_queue<int> priorityQueue;

        bool isImpossible = false, isStack = true, isQueue = true, isPriorityQueue = true;
        for (int i = 0; i < amountOfActions; i++) {

            scanf("%d%d", &actionType, &value);

            if (actionType == 1) {
                stack.push(value);
                queue.push(value);
                priorityQueue.push(value);
            }

            if (actionType == 2) {
                int stackPopped = stack.empty() ? -1 : stack.top();
                int queuePopped = queue.empty() ? -2 : queue.front();
                int priorityQueuePopped = priorityQueue.empty() ? -3 : priorityQueue.top();

                if (stackPopped == value) stack.pop();
                else isStack = false;
                
                if (queuePopped == value) queue.pop();
                else isQueue = false;
                
                if (priorityQueuePopped == value) priorityQueue.pop();
                else isPriorityQueue = false;
                
            }

        }

        if ((isStack && isQueue) || (isStack && isPriorityQueue) || (isQueue && isPriorityQueue)) printf("not sure\n");
        else if (isStack && !isQueue && !isPriorityQueue) printf("stack\n");
        else if (isQueue && !isStack && !isPriorityQueue) printf("queue\n");
        else if (isPriorityQueue && !isStack && !isQueue) printf("priority queue\n");
        else printf("impossible\n");
        
    }

    return 0;
}