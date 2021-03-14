package main

import "fmt"

func main() {
	var first, second, third rune
	fmt.Scanf("%c\n", &first);
	fmt.Scanf("%c\n", &second);
	fmt.Scanf("%c\n", &third)

	fmt.Printf("A = %c, B = %c, C = %c\n", first, second, third);
	fmt.Printf("A = %c, B = %c, C = %c\n", second, third, first);
	fmt.Printf("A = %c, B = %c, C = %c\n", third, first, second);
}