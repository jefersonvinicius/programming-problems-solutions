package main

import "fmt"

func main() {
	var n int
	fmt.Scanln(&n);
	for c := 0; c < n; c++ {
		var numberOfShots int;
		var shots[] int;
		var sequenceMovements string;

		fmt.Scanln(&numberOfShots);
		for i := 0; i < numberOfShots; i++ {
			var shot int;
			fmt.Scanf("%d", &shot);
			shots = append(shots, shot);
		}
		fmt.Scanln(&sequenceMovements);

		totalHit := 0
		for index, movement := range(sequenceMovements) {
			currentShot := shots[index];
			if currentShot <= 2 && movement == 'S' || currentShot > 2 && movement == 'J' {
				totalHit++
			}
		}

		fmt.Println(totalHit)
	}
}