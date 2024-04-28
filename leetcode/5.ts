function longestPalindrome(s: string): string {
  let largestSubstring = '';
  for (let i = 0; i < s.length; i++) {
    let regularSubstring = '',
      palindromicSubstring = '';
    for (let j = i; j < s.length; j++) {
      const letter = s[j];
      regularSubstring = `${regularSubstring}${letter}`;
      palindromicSubstring = `${letter}${palindromicSubstring}`;
      if (regularSubstring === palindromicSubstring && regularSubstring.length > largestSubstring.length) {
        largestSubstring = regularSubstring;
      }
    }
  }
  return largestSubstring;
}
