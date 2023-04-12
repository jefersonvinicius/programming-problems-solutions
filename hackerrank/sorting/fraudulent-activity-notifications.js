'use strict';

const fs = require('fs');

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', function(inputStdin) {
    inputString += inputStdin;
});

process.stdin.on('end', function() {
    inputString = inputString.split('\n');

    main();
});

function readLine() {
    return inputString[currentLine++];
}

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */

function activityNotifications(expenditure, loockbackDays) {
    let noficiations = 0
    const medians = createMedians(expenditure, loockbackDays)
    for (let day = loockbackDays; day < expenditure.length; day++) {
        const dayExpenditure = expenditure[day]
        const median = medians[day]
        if (dayExpenditure >= median * 2) noficiations++
    }
    return noficiations
}

function createMedians(expenditure, loockbackDays) {
    const medians = Array.from({length: expenditure.length}).fill(0)
    let trailingWindow = null
    for (let day = loockbackDays; day < expenditure.length; day++) { 
        if (trailingWindow) {
            console.log(trailingWindow)
            trailingWindow.shift()
            console.log(trailingWindow)

            insertSorted(trailingWindow, expenditure[day]);
        } else {
            const trailingExpenses = getExpenditureTrailingNumbers(expenditure, {loockbackDays, day})
            trailingWindow = quickSort(trailingExpenses)
        }
        medians[day] = calculateMedian(trailingWindow);
    }
    return medians;
}

function calculateMedian(values) {
    const sorted = quickSort(values)
    if (isOdd(sorted.length)) return sorted[Math.floor(sorted.length/2)]
    return (sorted[Math.floor(sorted.length/2)] + sorted[Math.ceil(sorted.length/2)]) / 2
}

function getExpenditureTrailingNumbers(expenditure, {loockbackDays, day}) {
    const startIndex = day - loockbackDays
    return expenditure.slice(startIndex, startIndex + loockbackDays)
}

function isOdd(value) { return value % 2 !== 0 }

function insertSorted(sortedArray, value) {
    let index = null
    for (let i = 0; i < sortedArray.length - 1; i++) {
        if (sortedArray[i+1] > value) {
            index = i;
            break
        }
    }
    if (index === null) {
        sortedArray.push(value);
    } else {
        sortedArray.splice(index, 1, value);
    }
}

function quickSort(values) {
    const sorted = Array.from(values)
    quickSortAlgorithm(sorted, 0, sorted.length - 1);
    return sorted;
}

function quickSortAlgorithm(values, left, right) {
    if (left >= right) return;
    const index = quickSortPartition(values, left, right)
    quickSortAlgorithm(values, left, index - 1)
    quickSortAlgorithm(values, index + 1, right)
}  

function quickSortPartition(values, left, right) {
    const pivotIndex = Math.floor((left + right) / 2)
    const pivot = values[pivotIndex]
    const leftElements = [], rightElements = []
    for (let index = left; index <= right; index++) {
        if (index === pivotIndex) continue
        if (values[index] > pivot) rightElements.push(values[index])
        else leftElements.push(values[index])
    }
    let valuesIndex = left
    for (const value of leftElements) values[valuesIndex++] = value
    values[valuesIndex++] = pivot
    for (const value of rightElements) values[valuesIndex++] = value
    return left + leftElements.length
}

function main() {
    const ws = fs.createWriteStream(process.env.OUTPUT_PATH)
    const firstMultipleInput = readLine().replace(/\s+$/g, '').split(' ')
    const n = parseInt(firstMultipleInput[0], 10)
    const d = parseInt(firstMultipleInput[1], 10)
    const expenditure = readLine().replace(/\s+$/g, '').split(' ').map(expenditureTemp => parseInt(expenditureTemp, 10))
    const result = activityNotifications(expenditure, d)
    ws.write(result + '\n')
    ws.end()
}
