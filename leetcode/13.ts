function romanToInt(s: string): number {
    const symbolsValues = {
        I: 1,
        V: 5,
        X: 10,
        L: 50,
        C: 100,
        D: 500,
        M: 1000,
    };

    let integer = 0;
    for (let i = 0; i < s.length; i++) {
        const symbol = s[i];
        const nextSymbol = s[i + 1];
        if (nextSymbol && symbolsValues[symbol] < symbolsValues[nextSymbol]) {
            integer += symbolsValues[nextSymbol] - symbolsValues[symbol];
            i++;
        } else {
            integer += symbolsValues[symbol];
        }
    }

    return integer;
}
