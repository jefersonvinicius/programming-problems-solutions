package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
	"unicode"
)

var writer = bufio.NewWriter(os.Stdout)
var reader = bufio.NewReader(os.Stdin)

func readLine() (string, error) {
	text, _, err := reader.ReadLine()
	return strings.TrimRight(string(text), "\r\n"), err
}

func isValidPassword(password string) bool {
	if len(password) < 6 || len(password) > 32 {
		return false
	}

	hasUpper := false
	hasLower := false
	hasDigit := false
	foundInvalidChar := false
	for _, char := range password {
		if unicode.IsSpace(char) || unicode.IsPunct(char) || char > unicode.MaxASCII {
			foundInvalidChar = true
			break
		}
		if unicode.IsLower(char) {
			hasLower = true
		}
		if unicode.IsUpper(char) {
			hasUpper = true
		}
		if unicode.IsDigit(char) {
			hasDigit = true
		}
	}

	return hasLower && hasDigit && hasUpper && !foundInvalidChar
}

func main() {
	for {
		password, err := readLine()
		if err == io.EOF {
			break
		}

		isValid := isValidPassword(password)

		if isValid {
			fmt.Fprintln(writer, "Senha valida.")
		} else {
			fmt.Fprintln(writer, "Senha invalida.")
		}
	}

	writer.Flush()
}
