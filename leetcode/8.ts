const INT_MAX = 2 ** 31 - 1;
const INT_MIN = 2 ** 31 * -1;

function isDigit(char: string) {
    return char >= '0' && char <= '9';
}

function isSign(char: string) {
    return char === '+' || char === '-';
}

function myAtoi(s: string): number {
    let value = '';
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (char === ' ' && value.length === 0) continue;
        if ((!isDigit(char) && !isSign(char)) || (isSign(char) && value.length > 0)) break;

        value += char;
    }

    const valueAsNumber = Number(value);
    if (isNaN(valueAsNumber)) return 0;

    if (valueAsNumber < INT_MIN) return INT_MIN;
    if (valueAsNumber > INT_MAX) return INT_MAX;
    return valueAsNumber;
}
