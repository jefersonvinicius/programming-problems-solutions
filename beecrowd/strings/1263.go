package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func calculateAlliterations(words []string) int {
	numberOfAlliterations := 0
	alreadyComputed := false

	for index, word := range words {
		if index == 0 { continue }

		currentFirstLetter := unicode.ToLower(rune(word[0]));
		previousFirstLetter := unicode.ToLower(rune(words[index - 1][0]))

		if previousFirstLetter == currentFirstLetter && !alreadyComputed  {
			numberOfAlliterations++
			alreadyComputed = true
		} else if previousFirstLetter != currentFirstLetter {
			alreadyComputed = false
		}
	}

	return numberOfAlliterations
}

func main() {

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		sentence := scanner.Text() 

		words := strings.Split(sentence, " ");
		result := calculateAlliterations(words);
		fmt.Println(result);
	}	

}