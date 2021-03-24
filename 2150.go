package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func calculateAmountVowelsInSentence(vowels string, sentence string) int {
	amount := 0
	for _, char := range sentence {
		if (strings.ContainsRune(vowels, char)) {
			amount++
		}
	}
	return amount
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	for scanner.Scan() {
		vowels := scanner.Text()
		if vowels == "" { break } 

		scanner.Scan()
		sentence := scanner.Text()


		result := calculateAmountVowelsInSentence(vowels, sentence)

		fmt.Println(result);
	}
}