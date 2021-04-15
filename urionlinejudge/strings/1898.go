package main

import (
	"bytes"
	"fmt"
	"strconv"
	"strings"
	"unicode"
)

func extractNumberFromString(str string) string {
	var buffer bytes.Buffer

	decimalPointHasFound := false
	amountNumberAfterDecimalPoint := 0
	for _, char := range str {
		if (unicode.IsNumber(char) || char == '.') && amountNumberAfterDecimalPoint < 2 {
			buffer.WriteRune(char)
		}

		if char == '.' {
			decimalPointHasFound = true
		} else if unicode.IsNumber(char) && decimalPointHasFound {
			amountNumberAfterDecimalPoint++
		}
	}
	return buffer.String()
}

func parseIntAndGetFloatPart(str string) (uint64, float64) {
	pieces := strings.Split(str, ".");
	n, _ := strconv.ParseUint(pieces[0], 10, 64)

	f := 0.0
	if len(pieces) > 1 {
		f, _ = strconv.ParseFloat("0."+pieces[1], 64)
	}

	return n, f
}

func main() {
	var firstLine,secondLine string
	fmt.Scanln(&firstLine)
	fmt.Scanln(&secondLine)

	number1AsString := extractNumberFromString(firstLine)
	number2AsString := extractNumberFromString(secondLine);

	number1Int, number1FlotPart := parseIntAndGetFloatPart(number1AsString[11:]);
	number2Int, number2FlotPart := parseIntAndGetFloatPart(number2AsString);

	totalInt := number1Int + number2Int
	totalFloat := number1FlotPart + number2FlotPart

	cpf := number1AsString[0:11]
	
	fmt.Println("cpf", cpf)
	fmt.Printf("%.2f\n", float64(totalInt) + totalFloat)
}