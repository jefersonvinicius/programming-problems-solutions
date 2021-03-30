//
// For some reason this code in Golang got TLE, but the C++ solution has accepted
//

package main

import "fmt"

const DayInSeconds = 86400
const HourInSeconds = 3600
const MinuteInSeconds = 60

func getSecondsFromDays(days int) int {
	return days * DayInSeconds
}

func getSecondsFromHours(hours int) int {
	return hours * HourInSeconds;
}

func getSecondsFromMinutes(minutes int) int {
	return minutes * MinuteInSeconds
}

func main() {
	var initialDay, finalDay, initialHour, finalHour, initialMinutes, finalMinutes, initialSeconds, finalSeconds int;

	var dayLabel string
	fmt.Scanf("%s %d", &dayLabel, &initialDay);
	fmt.Scanf("%d : %d : %d",&initialHour, &initialMinutes, &initialSeconds)

	totalInitialSeconds := getSecondsFromDays(initialDay) + getSecondsFromHours(initialHour) + getSecondsFromMinutes(initialMinutes) + initialSeconds	

	fmt.Scanf("%s %d", &dayLabel, &finalDay);
	fmt.Scanf("%d : %d : %d", &finalHour, &finalMinutes, &finalSeconds)	
	totalFinalSeconds := getSecondsFromDays(finalDay) + getSecondsFromHours(finalHour) + getSecondsFromMinutes(finalMinutes) + finalSeconds	

	diffSeconds := totalFinalSeconds - totalInitialSeconds;

	days := diffSeconds / DayInSeconds
	fmt.Println(days, "dia(s)")
	
	rest := diffSeconds % DayInSeconds
	hours := rest / HourInSeconds
	fmt.Println(hours, "hora(s)")

	rest = diffSeconds % HourInSeconds
	minutes := rest / MinuteInSeconds
	fmt.Println(minutes, "minuto(s)")

	rest = diffSeconds % MinuteInSeconds
	fmt.Println(rest, "segundo(s)")

}
