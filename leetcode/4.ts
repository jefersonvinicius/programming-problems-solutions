function findMedianSortedArrays(nums1: number[], nums2: number[]): number {
  const mergedArray: number[] = [];
  let indexNums1 = 0,
    indexNums2 = 0;
  while (indexNums1 < nums1.length || indexNums2 < nums2.length) {
    if (indexNums1 >= nums1.length) {
      mergedArray.push(nums2[indexNums2]);
      indexNums2++;
    } else if (indexNums2 >= nums2.length) {
      mergedArray.push(nums1[indexNums1]);
      indexNums1++;
    } else if (nums1[indexNums1] <= nums2[indexNums2]) {
      mergedArray.push(nums1[indexNums1]);
      indexNums1++;
    } else {
      mergedArray.push(nums2[indexNums2]);
      indexNums2++;
    }
  }

  const length = mergedArray.length;
  const median =
    length % 2 === 0
      ? (mergedArray[length / 2 - 1] + mergedArray[length / 2]) / 2
      : mergedArray[Math.floor(length / 2)];

  return median;
}
