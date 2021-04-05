package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)

func readLine() (string, error) {
	text, err := reader.ReadString('\n')
	return strings.TrimSpace(text), err
}

func getParenthesis(text string) string {
	var buffer bytes.Buffer
	for _, char := range text {
		if char == ')' || char == '(' {
			buffer.WriteRune(rune(char))
		}
	}
	return buffer.String()
}

func main() {
	for {
		text, err := readLine()
		if err == io.EOF {
			break
		}

		onlyParenthesis := getParenthesis(text)

		for len(onlyParenthesis) > 0 {
			top := len(onlyParenthesis) - 1
			parenthesis := onlyParenthesis[top]
			onlyParenthesis = onlyParenthesis[:top]
			fmt.Printf("%c", parenthesis)
		}
		fmt.Println()

	}
}
