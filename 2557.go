package main

import (
	"fmt"
	"io"
	"strconv"
	"strings"
)

func parseExpression(expression string) (string, string, string) {
	plusSignalIndex := strings.Index(expression, "+");
	equalSignalIndex := strings.Index(expression, "=")

	firstElement := expression[0:plusSignalIndex]
	secondElement := expression[plusSignalIndex + 1:equalSignalIndex]
	thirdElement := expression[equalSignalIndex + 1:len(expression)]

	return firstElement, secondElement, thirdElement
}

func isLetter(s string) bool{
	if s == "J" || s == "L" || s == "R" {
		return true
	}
	return false
}

func main() {
	for {
		var expression string
		_, err := fmt.Scanln(&expression)
		if err == io.EOF { break }

		firstElement, secondElement, thirdElement := parseExpression(expression)
		
		a, _ := strconv.Atoi(firstElement)
		b, _ := strconv.Atoi(secondElement)
		c, _ := strconv.Atoi(thirdElement)

		if isLetter(thirdElement) {
			fmt.Printf("%d\n", a + b);
		} else if isLetter(secondElement) {
			fmt.Printf("%d\n", c - a);
		} else {
			fmt.Printf("%d\n", c - b);
		}

 	}
}