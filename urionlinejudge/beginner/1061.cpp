#include <stdio.h>

const int DayInSeconds = 86400;
const int HourInSeconds = 3600;
const int MinuteInSeconds = 60;

int getSecondsFromDays(int days) {
	return days * DayInSeconds;
}

int getSecondsFromHours(int hours) {
	return hours * HourInSeconds;
}

int getSecondsFromMinutes(int minutes) {
	return minutes * MinuteInSeconds;
}

int main() {
	int initialDay, finalDay, initialHour, finalHour, initialMinutes, finalMinutes, initialSeconds, finalSeconds;

    char dayLabel[3];
	scanf("%s %d", dayLabel, &initialDay);
	scanf("%d : %d : %d", &initialHour, &initialMinutes, &initialSeconds);

	int totalInitialSeconds = getSecondsFromDays(initialDay) + getSecondsFromHours(initialHour) + getSecondsFromMinutes(initialMinutes) + initialSeconds;

	scanf("%s %d", dayLabel, &finalDay);
	scanf("%d : %d : %d", &finalHour, &finalMinutes, &finalSeconds);
	int totalFinalSeconds = getSecondsFromDays(finalDay) + getSecondsFromHours(finalHour) + getSecondsFromMinutes(finalMinutes) + finalSeconds;	

	int diffSeconds = totalFinalSeconds - totalInitialSeconds;

	int days = diffSeconds / DayInSeconds;
	printf("%d dia(s)\n", days);
	
	int rest = diffSeconds % DayInSeconds;
	int hours = rest / HourInSeconds;
	printf("%d hora(s)\n", hours);

	rest = diffSeconds % HourInSeconds;
	int minutes = rest / MinuteInSeconds;
	printf("%d minuto(s)\n", minutes);

	rest = diffSeconds % MinuteInSeconds;
	printf("%d segundo(s)\n", rest);

    return 0;
}
