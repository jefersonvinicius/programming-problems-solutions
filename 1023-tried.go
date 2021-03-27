package main

import (
	"fmt"
	"sort"
)

type Property struct {
	NumberOfResidents  int
	TotalConsumption   int
	AverageConsumption int
}

func printProperties(properties map[int]Property, keys []int) {
	propertiesLength := len(properties)
	for index, key := range keys {
		property := properties[key]
		if index == propertiesLength-1 {
			fmt.Printf("%d-%d\n", property.NumberOfResidents, property.AverageConsumption)
			continue
		}
		fmt.Printf("%d-%d ", property.NumberOfResidents, property.AverageConsumption)
	}
}

func truncateTo2DecimalPlaces(n float64) float64 {
	return float64(int(n*100)) / 100
}

func getOrderedMapKeys(properties map[int]Property) []int {
	keys := make([]int, len(properties))
	index := 0
	for key, _ := range properties {
		keys[index] = key
		index++
	}
	sort.Ints(keys)
	return keys
}

func main() {

	var n int
	currentTown := 1
	for {
		fmt.Scanln(&n)
		if n == 0 {
			break
		}

		totalConsumption := 0
		totalHabitants := 0
		properties := make(map[int]Property)

		for i := 0; i < n; i++ {
			var residents, consumption int
			fmt.Scanf("%d%d", &residents, &consumption)
			totalHabitants += residents
			totalConsumption += consumption

			average := consumption / residents
			property := Property{NumberOfResidents: residents, TotalConsumption: consumption, AverageConsumption: average}

			previousProperty, exists := properties[average]
			if exists {
				property.NumberOfResidents += previousProperty.NumberOfResidents
			}
			properties[average] = property
		}

		if currentTown > 1 {
			fmt.Println()
		}
		fmt.Printf("Cidade# %d:\n", currentTown)
		printProperties(properties, getOrderedMapKeys(properties))

		average := float64(totalConsumption) / float64(totalHabitants)
		fmt.Printf("Consumo medio: %.2f m3.\n", truncateTo2DecimalPlaces(average))

		currentTown++
	}

}
