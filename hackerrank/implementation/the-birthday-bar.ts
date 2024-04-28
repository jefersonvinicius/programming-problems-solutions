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
 * Complete the 'birthday' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY s
 *  2. INTEGER d
 *  3. INTEGER m
 */

function birthday(segments: number[], targetValue: number, maxSegmentLength: number): number {
  let answer = 0;
  for (let i = 0; i < segments.length; i++) {
    let sum = 0;

    for (let j = i; j < segments.length; j++) {
      sum += segments[j];
      const currentSegmentLength = j - i + 1;

      if (sum === targetValue && currentSegmentLength === maxSegmentLength) {
        answer++;
        break;
      }

      if (sum > targetValue || currentSegmentLength > maxSegmentLength) break;
    }
  }

  return answer;
}

function main() {
  const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

  const n: number = parseInt(readLine().trim(), 10);

  const s: number[] = readLine()
    .replace(/\s+$/g, '')
    .split(' ')
    .map((sTemp) => parseInt(sTemp, 10));

  const firstMultipleInput: string[] = readLine().replace(/\s+$/g, '').split(' ');

  const d: number = parseInt(firstMultipleInput[0], 10);

  const m: number = parseInt(firstMultipleInput[1], 10);

  const result: number = birthday(s, d, m);

  ws.write(result + '\n');

  ws.end();
}
