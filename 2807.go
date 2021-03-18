package main

import "fmt"

func main() {
	var n int
	fmt.Scanln(&n)
	sequence := make([]int, n) ;

	if (n == 1) {
		fmt.Println(1)
		return;
	}

	sequence[n-1] = 1
	sequence[n-2] = 1

	for i := n - 3 ; i >= 0; i-- {
		sequence[i] = sequence[i+1] + sequence[i+2];
	}

	for index, value := range sequence {
		if (index == n-1) {
			fmt.Printf("%d\n", value);
		} else {
			fmt.Printf("%d ", value);
		}
	}
}