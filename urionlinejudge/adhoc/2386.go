package main

import "fmt"

const PhotonsToBeAbleSeeStar = 40000000;

func main() {
	var telescopeArea, amountStars int
	fmt.Scanln(&telescopeArea)
	fmt.Scanln(&amountStars)

	amountStarsSeen := 0
	for i := 0; i < amountStars; i++ {
		var photons int;
		fmt.Scanln(&photons)

		if (photons * telescopeArea >= PhotonsToBeAbleSeeStar) {
			amountStarsSeen++
		}
	}

	fmt.Println(amountStarsSeen)
}