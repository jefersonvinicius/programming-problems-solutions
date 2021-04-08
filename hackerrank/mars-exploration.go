package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

// Complete the marsExploration function below.
func marsExploration(s string) int32 {
	differentLetter := 0
	for i := 0; i < len(s); i += 3 {
		if s[i] != 'S' {
			differentLetter++
		}
		if s[i+1] != 'O' {
			differentLetter++
		}
		if s[i+2] != 'S' {
			differentLetter++
		}
	}

	return int32(differentLetter)
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)

	writer := bufio.NewWriterSize(os.Stdout, 1024*1024)

	s := readLine(reader)

	result := marsExploration(s)

	fmt.Fprintf(writer, "%d\n", result)

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
