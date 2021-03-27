package main

import (
	"fmt"
	"strings"
)

func main() {
	var text string
	fmt.Scanln(&text);

	if strings.Contains(strings.ToLower(text), "zelda") {
		fmt.Println("Link Bolado")
	} else {
		fmt.Println("Link Tranquilo")
	}
}