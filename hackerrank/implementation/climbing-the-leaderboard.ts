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
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

function climbingLeaderboard(ranked: number[], gamesScores: number[]): number[] {
    let rank = 1;
    const leadboard = ranked.map((score, index) => {
        const previousScore = ranked[index - 1];
        if (index === 0 || (previousScore && score === previousScore)) return { rank, score };
        if (previousScore > score) return { rank: ++rank, score };
    });

    const leadboardSteps: number[] = [];
    let scoreIndex = 0;
    let leadboardIndex = leadboard.length - 1;
    while (scoreIndex < gamesScores.length && leadboardIndex >= 0) {
        const leadboardPlayer = leadboard[leadboardIndex]!;
        const nextLeadboardPlayer = leadboard[leadboardIndex - 1];
        const playerScore = gamesScores[scoreIndex];

        if (nextLeadboardPlayer && playerScore >= nextLeadboardPlayer.score) {
            leadboardIndex--;
        } else {
            if (playerScore >= leadboardPlayer.score) {
                leadboardSteps.push(leadboardPlayer.rank);
            } else {
                leadboardSteps.push(leadboardPlayer.rank + 1);
            }
            scoreIndex++;
        }
    }

    return leadboardSteps;
}

function main() {
    const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

    const rankedCount: number = parseInt(readLine().trim(), 10);

    const ranked: number[] = readLine()
        .replace(/\s+$/g, '')
        .split(' ')
        .map((rankedTemp) => parseInt(rankedTemp, 10));

    const playerCount: number = parseInt(readLine().trim(), 10);

    const player: number[] = readLine()
        .replace(/\s+$/g, '')
        .split(' ')
        .map((playerTemp) => parseInt(playerTemp, 10));

    const result: number[] = climbingLeaderboard(ranked, player);

    ws.write(result.join('\n') + '\n');

    ws.end();
}
