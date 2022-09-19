#include <stdio.h>
#include <string.h>

int main() {
	int numberOfLabels, numberOfCandyTypes;
	scanf("%d%d", &numberOfLabels, &numberOfCandyTypes);

	int numberOfCandysTypes[numberOfCandyTypes + 1];

	memset(numberOfCandysTypes, 0, sizeof(numberOfCandysTypes));

	for (int i = 0; i < numberOfLabels; i++) {
		int n;
		scanf("%d", &n);
		numberOfCandysTypes[n]++;
	}
	
	int answer = -1;
	for (int i = 1; i < numberOfCandyTypes + 1; i++) {
		if (numberOfCandysTypes[i] < answer || answer == -1) {
			answer = numberOfCandysTypes[i] ;
		} 
	}

	printf("%d\n", answer);
}