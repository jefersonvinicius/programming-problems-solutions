package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

const RemixWord = "WUB"

func main() {
	reader := bufio.NewReader(os.Stdin)
	text, _ := reader.ReadString('\n')

	processed := strings.ReplaceAll(text, RemixWord, " ")
	processed = strings.TrimSpace(processed)

	var initialMusic bytes.Buffer
	processedLength := len(processed)
	for index, char := range processed {
		if index < processedLength-1 && char == ' ' && processed[index+1] == ' ' {
			continue
		}
		initialMusic.WriteRune(rune(char))
	}

	fmt.Println(initialMusic.String())

}
