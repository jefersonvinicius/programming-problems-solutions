function intToRoman(num: number): string {
    const unitToSymbols: [number, string][] = [
        [1, 'I'],
        [4, 'IV'],
        [5, 'V'],
        [9, 'IX'],
        [10, 'X'],
        [40, 'XL'],
        [50, 'L'],
        [90, 'XC'],
        [100, 'C'],
        [400, 'CD'],
        [500, 'D'],
        [900, 'CM'],
        [1000, 'M'],
    ];
    let unitIndex = unitToSymbols.length - 1;

    let result = '';
    while (unitIndex >= 0 && num !== 0) {
        const [unit, symbol] = unitToSymbols[unitIndex];

        const unitWithinNum = Math.floor(num / unit);
        if (unitWithinNum >= 1) {
            result += Array.from({ length: unitWithinNum }, () => symbol).join('');
            num %= unitWithinNum * unit;
        }
        unitIndex--;
    }

    return result;
}
