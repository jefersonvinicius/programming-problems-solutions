package main

import (
	"bufio"
	"fmt"
	"io"
	"math"
	"os"
	"strconv"
	"strings"
)

// Complete the funnyString function below.
func funnyString(s string) string {
	sLength := len(s)

	asciiValues := make([]int, sLength)

	for index, char := range s {
		asciiValues[index] = int(char)
	}

	reversed := make([]int, sLength)
	for i := sLength - 1; i >= 0; i-- {
		reversed[sLength-i-1] = asciiValues[i]
	}

	isFunnyLabel := "Funny"
	for index, value := range asciiValues {
		if index == sLength-1 {
			continue
		}

		sDiff := math.Abs(float64(value - asciiValues[index+1]))
		rDiff := math.Abs(float64(reversed[index] - reversed[index+1]))

		if sDiff != rDiff {
			isFunnyLabel = "Not Funny"
			break
		}
	}

	return isFunnyLabel
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)

	writer := bufio.NewWriterSize(os.Stdout, 1024*1024)

	qTemp, err := strconv.ParseInt(readLine(reader), 10, 64)
	checkError(err)
	q := int32(qTemp)

	for qItr := 0; qItr < int(q); qItr++ {
		s := readLine(reader)

		result := funnyString(s)

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
