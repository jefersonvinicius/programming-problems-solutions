package main

import (
	"fmt"
)

const Max = 100

func getBiggerIntFromArray(array []int)  int{
	bigger := -1
	for i, v := range array {
		if i == 0 || v > bigger {
			bigger = v
		}
	}
	return bigger
}

func main() {
	var numberOfCols, numberOfRows int;
	
	fmt.Scanf("%d%d", &numberOfRows, &numberOfCols)

	colsSums := make([]int, numberOfCols)
	rowsSums := make([]int, numberOfRows)
	
	for r := 0; r < numberOfRows; r++ {
		for c := 0; c < numberOfCols; c++ {
			var n int
			fmt.Scanf("%d", &n)
			colsSums[c] += n
			rowsSums[r] += n
		}
	}

	merged := append(colsSums, rowsSums...)

	answer := getBiggerIntFromArray(merged);

	fmt.Println(answer)

}