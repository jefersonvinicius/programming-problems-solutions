function lengthOfLongestSubstring(s: string): number {
  let greatestSize = 0;
  for (let i = 0; i < s.length; i++) {
    let lettersSelected = {},
      currentSize = 0;

    for (let j = i; j < s.length; j++) {
      const letter = s[j];
      if (lettersSelected[letter]) break;

      currentSize++;
      lettersSelected[letter] = true;
    }

    if (currentSize > greatestSize) {
      greatestSize = currentSize;
    }
  }

  return greatestSize;
}
