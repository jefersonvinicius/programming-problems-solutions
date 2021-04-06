package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
	"unicode"
)

func isSpecialCharacter(char rune) bool {
    return strings.ContainsRune("!@#$%^&*()-+", char);
}

// Complete the minimumNumber function below.
func minimumNumber(n int32, password string) int32 {
    // Return the minimum number of characters to make the password strong
    incorrect := 4
    lowerIsFound := false
    upperIsFound := false 
    digitIsFound := false
    specialCharFound := false
    
    for _, char := range password {
        if unicode.IsLower(char) && !lowerIsFound {
            incorrect--
            lowerIsFound = true
        }
        
        if unicode.IsUpper(char) && !upperIsFound {
            incorrect--
            upperIsFound = true
        }
        
        if unicode.IsDigit(char) && !digitIsFound {
            incorrect--
            digitIsFound = true
        }
        
        if isSpecialCharacter(char) && !specialCharFound {
            incorrect--
            specialCharFound = true
        }
    }
    
    if len(password) < 6 && incorrect < (6 - len(password)) {
        incorrect = (6 - len(password))
    }
    
    return int32(incorrect);
}

func main() {
    reader := bufio.NewReaderSize(os.Stdin, 1024 * 1024)

    stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
    checkError(err)

    defer stdout.Close()

    writer := bufio.NewWriterSize(stdout, 1024 * 1024)

    nTemp, err := strconv.ParseInt(readLine(reader), 10, 64)
    checkError(err)
    n := int32(nTemp)

    password := readLine(reader)

    answer := minimumNumber(n, password)

    fmt.Fprintf(writer, "%d\n", answer)

    writer.Flush()
}

func readLine(reader *bufio.Reader) string {
    str, _, err := reader.ReadLine()
    if err == io.EOF {
        return ""
    }

    return strings.TrimRight(string(str), "\r\n")
}

func checkError(err error) {
    if err != nil {
        panic(err)
    }
}
