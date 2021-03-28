package main

import (
	"fmt"
	"io"
)

type Building struct {
	LeftCoordinate  int
	Height          int
	RightCoordinate int
}

func (this Building) Width() int {
	return this.RightCoordinate - this.LeftCoordinate
}

func (this Building) isInner(building Building) bool {
	if this.LeftCoordinate > building.LeftCoordinate && this.RightCoordinate <= building.RightCoordinate && this.Height < building.Height {
		return true
	}
	return false
}

func separateBuildingsInBlocks(buildings []Building) [][]Building {
	buildingsLength := len(buildings)
	var blocks [][]Building
	var block []Building
	shouldResolveBlock := false
	currentBiggerRight := 0
	shouldAddLastBuildAsPending := false
	isLastBuilding := false

	for index, building := range buildings {
		if index == buildingsLength-1 {
			isLastBuilding = true
		}

		if index > 0 && building.LeftCoordinate > currentBiggerRight {
			shouldResolveBlock = true
		}

		if isLastBuilding {
			if building.LeftCoordinate <= currentBiggerRight {
				block = append(block, building)
			} else {
				shouldAddLastBuildAsPending = true
			}
			shouldResolveBlock = true
		}

		if shouldResolveBlock {
			if len(block) > 0 {
				blocks = append(blocks, block)
			}
			block = nil
			shouldResolveBlock = false
			if shouldAddLastBuildAsPending {
				block = append(block, building)
			}
		}

		if !isLastBuilding {
			block = append(block, building)
		}
		if building.RightCoordinate > currentBiggerRight {
			currentBiggerRight = building.RightCoordinate
		}
	}

	if shouldAddLastBuildAsPending {
		fmt.Println("Block: ", block)
		blocks = append(blocks, block)
	}

	return blocks
}

func findBiggerRightCoordinate(block []Building) int {
	biggerRight := 0
	for _, building := range block {
		if building.RightCoordinate > biggerRight {
			biggerRight = building.RightCoordinate
		}
	}
	return biggerRight
}

func resolveBlock(block []Building) []int {
	if len(block) == 1 {
		return []int{block[0].LeftCoordinate, block[0].Height, 0}
	}
	// TODO: make function to resolve buildings block
	return []int{block[0].LeftCoordinate, block[0].Height, 0}
}

func main() {
	var buildings []Building

	for {
		var l, h, r int
		_, err := fmt.Scanf("%d%d%d", &l, &h, &r)
		if err == io.EOF {
			break
		}
		buildings = append(buildings, Building{LeftCoordinate: l, Height: h, RightCoordinate: r})
	}

	var result []int

	blocks := separateBuildingsInBlocks(buildings)
	for _, block := range blocks {
		blockResult := resolveBlock(block)
		result = append(result, blockResult...)
	}

	resultLength := len(result)
	for i := 0; i < resultLength; i++ {
		if i == resultLength-1 {
			fmt.Println(result[i])
			continue
		}
		fmt.Printf("%d ", result[i])
	}
}
