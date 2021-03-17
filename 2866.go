package main

import (
	"fmt"
	"unicode"
)

func main() {
	var cases int
	fmt.Scanln(&cases)
	for i := 0; i < cases; i++ {
		var str string
		fmt.Scanln(&str)

		var answer []rune
		for c := len(str) - 1; c >= 0; c-- {
			letter := rune(str[c])
			if unicode.IsLower(letter) {
				answer = append(answer, letter)
			}
		}
		fmt.Println(string(answer))
	}
}
