package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

/*
 * Complete the timeConversion function below.
 */
func timeConversion(s string) string {
	pieces := strings.Split(s[:len(s)-2], ":")
	hours, _ := strconv.Atoi(pieces[0])
	period := s[len(s)-2:]

	if period == "PM" && hours != 12 {
		hours += 12
	} else if period == "AM" && hours == 12 {
		hours = 0
	}

	answer := fmt.Sprintf("%02d:%s:%s\n", hours, pieces[1], pieces[2])
	return answer
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)

	writer := bufio.NewWriterSize(os.Stdout, 1024*1024)

	s := readLine(reader)

	result := timeConversion(s)

	fmt.Fprintf(writer, "%s\n", result)

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
