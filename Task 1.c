#include <stdio.h>

double calculateRepayment(double loan, double interestRate, int years) {
    
	if (years == 0 || loan <= 0){
	return 0;
	}
    
	loan = loan + (loan * interestRate);
    
	double installment = loan / years;
    
	double remaining = loan - installment;
    printf("Year %d: Remaining loan = %.2f\n", years, remaining);
    return installment + calculateRepayment(remaining, interestRate, years - 1);
}

int main() {
    double total = calculateRepayment(100000, 0.05, 3);
    printf("Total repayment = %.2f\n", total);
    return 0;
}

