// PiCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <array>
#include <algorithm>
#include <vector>
#include <string>

using namespace std::chrono;


long CalculatePIDigitsAndGetInterval(const int digits) {
	const auto startTime = system_clock::now();

	
	const int remindersLength = 10 * digits / 3;
	int* reminders = new int[remindersLength]; //reminders array required for calculation with size of reminders length
	int* piDigits = new int[digits]; //result array
	for (int i = 0; i < remindersLength; i++) {
		reminders[i] = 2; //data initialization
	}


	int tempInvalid = 0; //counter for temporary invalid digits
	int carryOver = 0;

	//main iteration
	for (int i = 0; i < digits; i++) {//next number calculation
		for (int k = remindersLength - 1; k > 0; k--) {
			int _sumOfCarryOver = reminders[k] * 10 + carryOver;
			carryOver = (_sumOfCarryOver / (2 * k + 1)) * k;
			reminders[k] = _sumOfCarryOver % (2 * k + 1);
		}
		//last step: k=0
		int sumOfCarryOver = reminders[0] * 10 + carryOver;
		int nextNumber = sumOfCarryOver / 10; //calculated i-th number of pi
		reminders[0] = sumOfCarryOver % 10;
		if (nextNumber == 9) {
			tempInvalid++;
		} else if (nextNumber == 10) {
			for (int h = i - tempInvalid; h < i; h++) {
				if (piDigits[h] == 9)
					piDigits[h] = 0;
				else
					piDigits[h] += 1;
			}
			tempInvalid = 1;
			nextNumber = 0;
		}
		else {
			tempInvalid = 1;
		}
		piDigits[i] = nextNumber; //write new digit to result
	}

	delete[] reminders;
	delete[] piDigits;

	const auto endTime = system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	return (long)(elapsed.count());
}

class CalculationResult {
public:
	int Digits;
	long Best;
	long Median;
	long Worst;
	CalculationResult(int digits, long best, long median, long worst) {
		Digits = digits;
		Best = best;
		Median = median;
		Worst = worst;
	}

	void print() {
		std::cout << Digits << ", best: " << Best << ", median: " << Median << ", worst: " << Worst;
	}
	void println() {
		print();
		std::cout << std::endl;
	}
};

CalculationResult CalculatePIDigitsAndGetIntervals(const int digits, const int iterations) {
	std::vector<long> iterationResult; //result array
	for (int i = 0; i < iterations; i++) {
		iterationResult.push_back(CalculatePIDigitsAndGetInterval(digits));
	}
	std::sort(iterationResult.begin(), iterationResult.end());
	return CalculationResult(digits, iterationResult[0], iterationResult[iterationResult.size() / 2], iterationResult[iterationResult.size() - 1]);
}


std::vector<CalculationResult> CalculatePIDigitsInRange(const int maxDigits, const int iterations) {
	std::vector<CalculationResult> results;
	for (int digits = 10; digits <= maxDigits; digits *= 10) {
		CalculationResult result =  CalculatePIDigitsAndGetIntervals(digits, iterations);
		//result.println();
		results.push_back(result);
	}
	return results;
}

const int DEFAULT_MAX_DIGITS = 100000;
const int DEFAULT_ITERATIONS = 11;

int main(int argc, char** argv)
{
	/*
	if (argc <= 1) {
		std::cerr << "Missing arguments. Use -? or to get help!" << std::endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < argc; ++i) {
		if (sizeof(argv[i]) <= 1 || argv[i][0] != '-') {
			std::cerr << "Illegal argument " << argv[i] << std::endl;
			return EXIT_FAILURE;
		}
		if (argv[i][0] == '?') {
			std::cout << "-d !\n";
		}
		std::cout << argv[i] << "\n";
	}
	*/

	std::vector<CalculationResult> results = CalculatePIDigitsInRange(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS);

	for (unsigned int i = 0; i < results.size(); i++) {
		results[i].println();
	}
	return EXIT_SUCCESS;
}
