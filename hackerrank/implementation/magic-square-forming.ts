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
 * Complete the 'formingMagicSquare' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY s as parameter.
 */

const MAGIC_CONSTANT = 15;

const sum = (array: number[]) => {
  return array.reduce((total, element) => total + element, 0);
};

function formingMagicSquare(magicSquare: number[][]): number {
  let answer = 0;
  for (const line of magicSquare) {
    const currentLineValue = sum(line);
    const cost = Math.abs(currentLineValue - MAGIC_CONSTANT);
    answer += cost;
  }
  return answer;
}

function main() {
  const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

  let s: number[][] = Array(3);

  for (let i: number = 0; i < 3; i++) {
    s[i] = readLine()
      .replace(/\s+$/g, '')
      .split(' ')
      .map((sTemp) => parseInt(sTemp, 10));
  }

  const result: number = formingMagicSquare(s);

  ws.write(result + '\n');

  ws.end();
}
