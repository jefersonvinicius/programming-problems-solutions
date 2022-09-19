package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
	"unicode"
)

var mapHexLetterToValue = map[rune]int {
	'A': 10,
	'B': 11,
	'C': 12,
	'D': 13,
	'E': 14,
	'F': 15,
}

var mapHexValueToLetter = map[int]rune {
	10: 'A',
	11: 'B',
	12: 'C',
	13: 'D',
	14: 'E',
	15: 'F',
}


func convertIntegerToHex(n int) string {
	
	if n < 10 {
		return strconv.Itoa(n);
	}

	if n >= 10 && n < 16 {
		return string(mapHexValueToLetter[n])
	}
	
	var hex []rune;
	for {
		quotient := n/16;
		remainder := n%16;

		if remainder < 10 {
			c := strconv.Itoa(remainder)
			hex = append([]rune{rune(c[0])}, hex...)
		} else {
			hex = append([]rune{mapHexValueToLetter[remainder]}, hex...)
		}

		if quotient == 0 { break }
		n = quotient;
	}

	return string(hex);
}

func convertHexToInteger(hex string) int {
	pow := len(hex) - 1;
	result := 0
	var n int
	for _, char := range hex {
		if unicode.IsDigit(char) {
			n, _ = strconv.Atoi(string(char));
		} else {
			n = mapHexLetterToValue[char];
		}

		result += (n*int(math.Pow(16, float64(pow))))
		pow--;
	}

	return result
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	var n string;
	for {
		n, _ = reader.ReadString('\n')
		n = strings.TrimRight(n, "\r\n")
		if n[0] == '-' { break }
 
		if strings.HasPrefix(n, "0x") {
			integer := convertHexToInteger(strings.ToUpper(n[2:]));
			fmt.Fprintf(writer, "%d\n", integer);
		} else {
			integer, _ := strconv.Atoi(n)
			hex := convertIntegerToHex(integer);
			fmt.Fprintf(writer, "0x%s\n", hex);
		}
	}
	writer.Flush()
}
