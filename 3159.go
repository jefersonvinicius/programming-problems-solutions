package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

var KeyboardNumbers = map[string]map[string]int {
	"a": {"key": 2, "amount": 1},
	"b": {"key": 2, "amount": 2},
	"c": {"key": 2, "amount": 3},
	"d": {"key": 3, "amount": 1},
	"e": {"key": 3, "amount": 2},
	"f": {"key": 3, "amount": 3},
	"g": {"key": 4, "amount": 1},
	"h": {"key": 4, "amount": 2},
	"i": {"key": 4, "amount": 3},
	"j": {"key": 5, "amount": 1},
	"k": {"key": 5, "amount": 2},
	"l": {"key": 5, "amount": 3},
	"m": {"key": 6, "amount": 1},
	"n": {"key": 6, "amount": 2},
	"o": {"key": 6, "amount": 3},
	"p": {"key": 7, "amount": 1},
	"q": {"key": 7, "amount": 2},
	"r": {"key": 7, "amount": 3},
	"s": {"key": 7, "amount": 4},
	"t": {"key": 8, "amount": 1},
	"u": {"key": 8, "amount": 2},
	"v": {"key": 8, "amount": 3},
	"w": {"key": 9, "amount": 1},
	"x": {"key": 9, "amount": 2},
	"y": {"key": 9, "amount": 3},
	"z": {"key": 9, "amount": 4},
}

func charsBelongsSameKey(char1 rune, char2 rune) bool {
	charInfo1 := KeyboardNumbers[string(unicode.ToLower(char1))]
	charInfo2 := KeyboardNumbers[string(unicode.ToLower(char2))]
	
	if charInfo1["key"] == charInfo2["key"] {
		return true
	}
	return false
}

func getKeySequence(char string)  string {
	charInfo := KeyboardNumbers[char]
	var sequence bytes.Buffer

	for i := 0; i < charInfo["amount"]; i++ {
		keyAsString := strconv.Itoa(charInfo["key"])
		sequence.WriteString(keyAsString)
	}

	return sequence.String()
}


func getKeyboardSequence(sentence string) string {
	var sequenceBuffer bytes.Buffer
	for index, char := range sentence {

		lowerChar := string(unicode.ToLower(char))

		if char == '1'  {
			sequenceBuffer.WriteRune('1')
			continue
		}

		if char == ' ' {
			sequenceBuffer.WriteRune('0');
			continue
		}

		if unicode.IsUpper(char) {
			sequenceBuffer.WriteRune('#')
			sequenceBuffer.WriteString(getKeySequence(lowerChar))
			continue
		}
		
		if unicode.IsLower(char) {
			if index > 0 && charsBelongsSameKey(char, rune(sentence[index - 1])) {
				sequenceBuffer.WriteRune('*')
			}
			sequenceBuffer.WriteString(getKeySequence(lowerChar))
			continue
		} 
	}

	return sequenceBuffer.String()
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var n int
	fmt.Scanln(&n)
	for i := 0; i<n; i++ {

		scanner.Scan()
		sentence := scanner.Text()

		result := getKeyboardSequence(sentence);

		fmt.Println(result);

	}
}

