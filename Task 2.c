#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    
	if (fuel <= 0 || planet > totalPlanets){
	 return fuel;
	}
	
	fuel = fuel - consumption + recharge;
    
	if (planet % 4 == 0) {
	fuel += solarBonus;
	}
	
	printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int finalFuel = calculateFuel(500, 40, 15, 30, 1, 10);
    printf("Final Fuel = %d\n", finalFuel);
    return 0;
}

