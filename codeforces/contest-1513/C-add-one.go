package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

const Mod = 1000000007

func readLine() string {
	text, _ := reader.ReadString('\n')
	return strings.TrimRight(text, "\r\n")
}

func readInt() uint64 {
	text := readLine()
	integer, _ := strconv.ParseUint(text, 10, 64)
	return integer
}

func readTestData() (string, uint64) {
	text := readLine()
	pieces := strings.Split(text, " ")
	integer, _ := strconv.ParseUint(pieces[1], 10, 64)
	return pieces[0], integer
}

func applyMaxOperationsOnAlgorism(algorism int, operations uint64) (string, uint64) {
	maxOperations := uint64(10 - algorism)
	algorismUint := uint64(algorism)
	if maxOperations > operations {
		algorismUint += operations
		operations = 0
	} else {
		algorismUint += maxOperations
		operations -= uint64(maxOperations)
	}

	resultString := strconv.FormatUint(algorismUint, 10)

	return resultString, operations
}

func addOneToAllAlgorisms(number string, operations uint64) string {
	for {

		var numberBuffer bytes.Buffer
		nextOperations := uint64(0)
		for _, algorism := range number {
			result, restOperations := applyMaxOperationsOnAlgorism(int(algorism-'0'), operations)
			if restOperations < nextOperations || nextOperations == 0 {
				nextOperations = restOperations
			}
			numberBuffer.WriteString(result)
		}

		number = numberBuffer.String()

		if nextOperations == 0 {
			break
		}
		operations = nextOperations
	}

	return number
}

func main() {

	t := readInt()

	for t > 0 {

		n, operations := readTestData()

		number := addOneToAllAlgorisms(n, operations)

		fmt.Fprintf(writer, "%d\n", len(number)%Mod)

		t--
	}

	writer.Flush()
}
