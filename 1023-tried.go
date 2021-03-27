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

func printProperties(properties []Property) {
	propertiesLength := len(properties)
	for index, property := range properties {
		if index == propertiesLength-1 {
			fmt.Printf("%d-%d\n", property.NumberOfResidents, property.AverageConsumption)
			continue
		}
		fmt.Printf("%d-%d ", property.NumberOfResidents, property.AverageConsumption)
	}
}

func removePropertiesIndex(properties []Property, index int) []Property {
	return append(properties[:index], properties[index+1:]...)
}

func groupPropertiesByAverage(properties []Property) []Property {
	if len(properties) == 1 {
		return properties
	}

	currentAverage := properties[0].AverageConsumption
	currentPropertyIndex := 1
	for currentPropertyIndex < len(properties) {
		currentProperty := properties[currentPropertyIndex]

		if currentAverage == currentProperty.AverageConsumption {
			properties[currentPropertyIndex-1].NumberOfResidents += currentProperty.NumberOfResidents
			properties = removePropertiesIndex(properties, currentPropertyIndex)
		}

		currentPropertyIndex++
	}
	return properties
}

func truncateTo2DecimalPlaces(n float64) float64 {
	return float64(int(n*100)) / 100
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
		properties := make([]Property, 0, n)

		for i := 0; i < n; i++ {
			var residents, consumption int
			fmt.Scanf("%d%d", &residents, &consumption)
			totalHabitants += residents
			totalConsumption += consumption

			property := Property{NumberOfResidents: residents, TotalConsumption: consumption, AverageConsumption: consumption / residents}
			properties = append(properties, property)
		}

		sort.SliceStable(properties, func(i, j int) bool {
			return properties[i].AverageConsumption < properties[j].AverageConsumption
		})

		properties = groupPropertiesByAverage(properties)

		if currentTown > 1 {
			fmt.Println()
		}
		fmt.Printf("Cidade# %d:\n", currentTown)
		printProperties(properties)

		average := float64(totalConsumption) / float64(totalHabitants)
		fmt.Printf("Consumo medio: %.2f m3.\n", truncateTo2DecimalPlaces(average))

		currentTown++
	}

}
