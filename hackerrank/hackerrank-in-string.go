package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

var targetWord = "hackerrank"

// Complete the hackerrankInString function below.
func hackerrankInString(s string) string {
	currentSearchingLetterIndex := 0
	for _, char := range s {
		if char == rune(targetWord[currentSearchingLetterIndex]) {
			currentSearchingLetterIndex++
			if currentSearchingLetterIndex == len(targetWord) {
				break
			}
		}
	}

	if currentSearchingLetterIndex == len(targetWord) {
		return "YES"
	}

	return "NO"
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)

	writer := bufio.NewWriterSize(os.Stdout, 1024*1024)

	qTemp, err := strconv.ParseInt(readLine(reader), 10, 64)
	checkError(err)
	q := int32(qTemp)

	for qItr := 0; qItr < int(q); qItr++ {
		s := readLine(reader)

		result := hackerrankInString(s)

		fmt.Fprintf(writer, "%s\n", result)
	}

	writer.Flush()
}

func readLine(reader *bufio.Reader) string {
	str, _, err := reader.ReadLine()
	if err == io.EOF {
		return ""
	}

	return strings.TrimRight(string(str), "\r\n")
}

func checkError(err error) {
	if err != nil {
		panic(err)
	}
}
