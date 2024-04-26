function twoSum(nums: number[], target: number): number[] {
  const numsIndexes = {};
  for (let i = 0; i < nums.length; i++) {
    const missing = target - nums[i];
    if (numsIndexes[missing] !== undefined) {
      return [numsIndexes[missing], i];
    }
    numsIndexes[nums[i]] = i;
  }
  return [];
}
