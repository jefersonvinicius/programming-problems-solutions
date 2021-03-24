package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func getFirstAndFinalLettersOfWords(words []string) ([]rune, []rune) {
	
	firstLetters := make([]rune, len(words))
	finalLetters := make([]rune, len(words))

	for _, word := range words {
		firstLetters = append(firstLetters, unicode.ToLower(rune(word[0])));
		finalLetters = append(finalLetters, unicode.ToLower(rune(word[len(word) - 1])))
	}

	return firstLetters, finalLetters
	
}

var LettersToFind = [...]rune{'c', 'o', 'b', 'o', 'l'}
var MaxLettersToFind = len(LettersToFind)


func main() {
	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		text := scanner.Text()
		words := strings.Split(text, "-")

		firstLetters, finalLetters := getFirstAndFinalLettersOfWords(words);

		currentIndexLetterToFind := 0
		for i, letter := range firstLetters{
			if currentIndexLetterToFind == MaxLettersToFind { break }
			
			currentLetterToFind := LettersToFind[currentIndexLetterToFind]
			if letter == currentLetterToFind || finalLetters[i] == currentLetterToFind {
				currentIndexLetterToFind++
			}
		}

		if currentIndexLetterToFind == MaxLettersToFind {
			fmt.Println("GRACE HOPPER")
		} else {
			fmt.Println("BUG")
		}
	}
}