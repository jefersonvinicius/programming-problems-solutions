const DIRECTIONS = {
    UP: 1,
    DOWN: 2,
};

function convert(s: string, numRows: number): string {
    if (numRows === 1) return s;

    const columns = 1005;
    const matrix: (null | string)[][] = Array.from({ length: numRows + 1 }, () =>
        Array.from({ length: columns }, () => null)
    );
    let sIndex = 0,
        row = 0,
        column = 0;
    let direction = DIRECTIONS.DOWN;
    while (sIndex < s.length) {
        const character = s[sIndex];
        matrix[row][column] = character;

        if (direction === DIRECTIONS.DOWN) {
            if (row === numRows - 1) {
                // reaches bottom
                row--;
                column++;
                direction = DIRECTIONS.UP;
            } else {
                row++;
            }
        } else {
            if (row === 0) {
                // reaches top
                row++;
                direction = DIRECTIONS.DOWN;
            } else {
                row--;
                column++;
            }
        }

        sIndex++;
    }

    let answer = '';
    for (const row of matrix) {
        const line = row.filter((element) => element !== null).join('');
        answer += line;
    }

    return answer;
}
