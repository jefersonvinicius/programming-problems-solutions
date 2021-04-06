package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)

func readInts() (int, int) {
	s, _, _ := reader.ReadLine();
	line := strings.TrimRight(string(s), "\r\n");
	splited := strings.Split(line, " ");
	n, _ := strconv.Atoi(splited[0]);

	var m int
	if len(splited) > 1 {
		m, _ = strconv.Atoi(splited[1]);
	}

	return n, m
}

func main() {
	writer := bufio.NewWriter(os.Stdout)
	n, _ := readInts()

	for ; n > 0; n-- {
		richardCards, vicentCards := readInts()
		initialIndex := int(math.Min(float64(richardCards), float64(vicentCards)))
		
		answer := 0
		for i := initialIndex; i > 0; i-- {
			if richardCards%i == 0 && vicentCards%i == 0 {
				answer = i;
				break
			}
		}

		fmt.Fprintf(writer, "%d\n", answer)
	}

	writer.Flush()
}