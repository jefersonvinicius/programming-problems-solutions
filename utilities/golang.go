package utilities

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)

	stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
	checkError(err)

	defer stdout.Close()

	writer := bufio.NewWriterSize(stdout, 1024*1024)

	readLine(reader)

	// Resolve problem

	writer.Flush()
}

func readLine(reader *bufio.Reader) (string, error) {
	str, _, err := reader.ReadLine()
	return strings.TrimRight(string(str), "\r\n"), err
}

func checkError(err error) {
	if err != nil {
		panic(err)
	}
}
