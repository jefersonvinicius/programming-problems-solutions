package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)

func readInts() (int, int) {
	text, _ := reader.ReadString('\n')
	textSplit := strings.Split(strings.TrimSpace(text), " ")

	n1, _ := strconv.ParseInt(textSplit[0], 10, 64)
	var n2 int64
	if len(textSplit) > 1 {
		n2, _ = strconv.ParseInt(textSplit[1], 10, 64)
	}
	return int(n1), int(n2)
}

func printProperties(properties []int) {
	amountEntryDisplayed := 0
	for average, residents := range properties {
		if residents == 0 {
			continue
		}
		if amountEntryDisplayed != 0 {
			fmt.Print(" ")
		}
		fmt.Printf("%d-%d", residents, average)
		amountEntryDisplayed++
	}
	fmt.Printf("\n")
}

func truncateTo2DecimalPlaces(n float64) float32 {
	return float32(int(n*100)) / 100
}

func main() {

	currentTown := 1
	for {
		n, _ := readInts()
		if n == 0 {
			break
		}

		totalConsumption := 0
		totalHabitants := 0

		properties := make([]int, 201)

		for i := 0; i < n; i++ {
			residents, consumption := readInts()
			totalHabitants += residents
			totalConsumption += consumption

			average := consumption / residents
			properties[average] += residents
		}

		if currentTown > 1 {
			fmt.Printf("\n")
		}
		fmt.Printf("Cidade# %d:\n", currentTown)
		printProperties(properties)

		average := float64(totalConsumption) / float64(totalHabitants)
		fmt.Printf("Consumo medio: %.2f m3.\n", truncateTo2DecimalPlaces(average))

		currentTown++
	}

}
