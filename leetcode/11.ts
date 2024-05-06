function maxArea(height: number[]): number {
    let left = 0,
        right = height.length - 1;
    let maximumWater = 0;
    while (left < right) {
        const container = Math.min(height[left], height[right]) * (right - left);
        if (container > maximumWater) maximumWater = container;

        if (height[left] < height[right]) left++;
        else right--;
    }

    return maximumWater;
}
