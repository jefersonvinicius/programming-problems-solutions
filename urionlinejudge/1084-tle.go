package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin);

func readLine() string {
	text, _ := reader.ReadString('\n');
	return strings.TrimSpace(text)
}

func readInts() (int, int){
	text, _ := reader.ReadString('\n');
	splited := strings.Split(strings.TrimSpace(text), " ");
	n, _ := strconv.Atoi(splited[0])
	m, _ := strconv.Atoi(splited[1])
	return n, m
}

func getBiggerNumberIndex(text string) int {
	bigger := '.'
	indexResult := -1  
	for index, char := range text {
		if char > bigger {
			bigger = char
			indexResult = index
		}
	}
	return indexResult;
}

func markIndexWithPoint(str string, index int) string {
	runes := []rune(str);
	runes[index] = '.'
	return string(runes)
}

func main() {
	for {
		n, amountErase := readInts()
		if n == 0 && amountErase == 0 { break }
		number := readLine()

		prizeSize := n - amountErase;

		answer := make([]byte, n);
		biggerNumberIndex := getBiggerNumberIndex(number);
		firstBiggerNumberIndex := biggerNumberIndex
		

		answerCounter := 0
		finalPart := number[firstBiggerNumberIndex:]
		shouldIgnoreFinalPart := false

		for answerCounter < prizeSize {

			if biggerNumberIndex < firstBiggerNumberIndex && !shouldIgnoreFinalPart {
				biggerNumberIndex = getBiggerNumberIndex(finalPart)
				if biggerNumberIndex == -1 {
					biggerNumberIndex = getBiggerNumberIndex(number)
					answer[biggerNumberIndex] = number[biggerNumberIndex];
					shouldIgnoreFinalPart = true
				} else {
					answer[biggerNumberIndex+firstBiggerNumberIndex] = finalPart[biggerNumberIndex];
					biggerNumberIndex += firstBiggerNumberIndex
				}
			} else {
				answer[biggerNumberIndex] = number[biggerNumberIndex];
			}

			answerCounter++;
			number = markIndexWithPoint(number, biggerNumberIndex);
			finalPart = number[firstBiggerNumberIndex:]
			biggerNumberIndex = getBiggerNumberIndex(number)			
		}

		fmt.Println(string(answer));

	}	
}