package main

import (
	"fmt"
	"math"
)

func main() {
	var p, n int
	fmt.Scanf("%d%d", &p, &n)

	pipes := make([]int, n)
	var x int
	win := true
	for i := 0; i < n; i++ {
		fmt.Scanf("%d", &x)
		pipes[i] = x

		diff := -1
		if i > 0 {
			diff = int(math.Abs(float64(pipes[i-1]) - float64(x)))
		}

		if diff != -1 && diff > p {
			win = false
			break
		}
	}

	if win {
		fmt.Println("YOU WIN")
	} else {
		fmt.Println("GAME OVER")
	}

}
