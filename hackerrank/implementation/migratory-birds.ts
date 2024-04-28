'use strict';

import { WriteStream, createWriteStream } from 'fs';
process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString: string = '';
let inputLines: string[] = [];
let currentLine: number = 0;

process.stdin.on('data', function (inputStdin: string): void {
  inputString += inputStdin;
});

process.stdin.on('end', function (): void {
  inputLines = inputString.split('\n');
  inputString = '';

  main();
});

function readLine(): string {
  return inputLines[currentLine++];
}

/*
 * Complete the 'migratoryBirds' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

function migratoryBirds(birds: number[]): number {
  const frequencies = Array.from({ length: 6 }, () => 0);
  for (const bird of birds) frequencies[bird]++;

  let mostFrequency = 0,
    answer = 0;
  for (let bird = 1; bird < frequencies.length; bird++) {
    const frequency = frequencies[bird];
    if (frequency > mostFrequency) {
      mostFrequency = frequency;
      answer = bird;
    }
  }

  return answer;
}

function main() {
  const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

  const arrCount: number = parseInt(readLine().trim(), 10);

  const arr: number[] = readLine()
    .replace(/\s+$/g, '')
    .split(' ')
    .map((arrTemp) => parseInt(arrTemp, 10));

  const result: number = migratoryBirds(arr);

  ws.write(result + '\n');

  ws.end();
}
