//
// For some reason this code in Golang got TLE, but the C++ solution has accepted
//

package main

import (
	"bufio"
	"fmt"
	"os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)
func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{}) { fmt.Fscanf(reader, f, a...) }

func main() {
	defer writer.Flush()

	var numberOfLabels, numberOfCandyTypes int
	scanf("%d %d", &numberOfLabels, &numberOfCandyTypes)

	numberOfCandysTypes := make([]int, numberOfCandyTypes + 1);

	for i := 0; i < numberOfLabels; i++ {
		var n int;
		scanf("%d", &n)
		numberOfCandysTypes[n]++
	}
	
	answer := -1
	for index, candy := range numberOfCandysTypes {
		if index == 0 { continue }
		if candy < answer || answer == -1 {
			answer = candy
		} 
	}

	printf("%d\n", answer)
}