package main

import (
	"fmt"
	"io"
	"strconv"
)

func reverseString(str string) string {
	strLength := len(str)
	reversed := make([]rune, strLength)
	for index, char := range str {
		reversed[(strLength-1)-index] = char
	}
	return string(reversed)
}

func getMirrorNumber(number uint64) uint64 {
	numberAsString := strconv.FormatUint(number, 10)
	if len(numberAsString) == 1 {
		return number
	}
	converted, _ := strconv.ParseUint(reverseString(numberAsString), 10, 64)
	return converted
}

const MAX_SEQUENCE_ELEMENT = 60

func main() {

	var sequence [MAX_SEQUENCE_ELEMENT + 1]uint64
	for i := 0; i <= MAX_SEQUENCE_ELEMENT; i++ {
		if i <= 2 {
			sequence[i] = uint64(i)
			continue
		}
		sequence[i] = getMirrorNumber(sequence[i-1]) + getMirrorNumber(sequence[i-2])
	}

	for {
		var position int
		_, err := fmt.Scanln(&position)
		if err == io.EOF {
			break
		}

		fmt.Println(sequence[position])
	}
}
