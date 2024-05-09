const MAX_STRING = 200;

function longestCommonPrefix(strs: string[]): string {
    let longestPrefix = '';
    for (let i = 0; i < MAX_STRING; i++) {
        const shouldAddToPrefix = strs.every(
            (str, index) => !!str[i] && (index === 0 || str[i] === strs[index - 1][i])
        );
        if (shouldAddToPrefix) longestPrefix += strs[0][i];
        else break;
    }
    return longestPrefix;
}
