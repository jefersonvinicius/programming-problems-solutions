package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)

func readInts() []int {
	text, _ := reader.ReadString('\n')
	textSplit := strings.Split(strings.TrimSpace(text), " ")
	intArray := make([]int, len(textSplit))
	for index, char := range textSplit {
		converted, _ := strconv.Atoi(char)
		intArray[index] = converted
	}
	return intArray
}

func main() {
	var n int
	fmt.Scanln(&n)

	quadradonia := readInts()
	nlogonia := readInts()

	sort.Ints(quadradonia)
	sort.Ints(nlogonia)

	currentNlogoniaSoldierIndex := n - 1
	numberOfVictories := 0
	for i := n - 1; i >= 0; i-- {
		if nlogonia[currentNlogoniaSoldierIndex] > quadradonia[i] {
			numberOfVictories++
			currentNlogoniaSoldierIndex--

			if currentNlogoniaSoldierIndex < 0 {
				break
			}
		}
	}

	fmt.Println(numberOfVictories)
}
