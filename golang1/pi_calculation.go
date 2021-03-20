package main

import (
	"fmt"
	"sort"
	"time"
)

const DefaultMaxDigits = 100000
const DefaultIterations = 11

func calculatePIDigitsAndGetInterval(digits int) int64 {
	startTime := time.Now().UnixNano() / int64(time.Millisecond)
	reminders := make([]int, 10*digits/3)
	piDigits := make([]int, digits)

	for i := 0; i < cap(reminders); i++ {
		reminders[i] = 2
	}

	tempInvalid := 0 //counter for temporary invalid digits
	carryOver := 0

	//main iteration
	for i := 0; i < digits; i++ { //next number calculation
		for k := cap(reminders) - 1; k > 0; k-- {
			_sumOfCarryOver := reminders[k]*10 + carryOver
			carryOver = (_sumOfCarryOver / (2*k + 1)) * k
			reminders[k] = _sumOfCarryOver % (2*k + 1)
		}
		//last step: k=0
		sumOfCarryOver := reminders[0]*10 + carryOver
		nextNumber := sumOfCarryOver / 10 //calculated i-th number of pi
		reminders[0] = sumOfCarryOver % 10
		if nextNumber == 9 {
			tempInvalid++
		} else if nextNumber == 10 {
			for h := i - tempInvalid; h < i; h++ {
				if piDigits[h] == 9 {
					piDigits[h] = 0
				} else {
					piDigits[h] += 1
				}
			}
			tempInvalid = 1
			nextNumber = 0
		} else {
			tempInvalid = 1
		}
		piDigits[i] = nextNumber //write new digit to result
	}
	endTime := time.Now().UnixNano() / int64(time.Millisecond)
	return endTime - startTime
}

type CalculationResult struct {
	Digits int
	Best   int64
	Median int64
	Worst  int64
}

func printCalculation(value CalculationResult) {
	fmt.Printf("%d best: %d, median: %d, worst: %d\n", value.Digits, value.Best, value.Median, value.Worst)
}

func CalculatePIDigitsAndGetIntervals(digits int, iterations int) CalculationResult {
	iterationResult := make([]int64, iterations)
	for i := 0; i < iterations; i++ {
		iterationResult[i] = calculatePIDigitsAndGetInterval(digits)
	}
	sort.Slice(iterationResult, func(i, j int) bool {
		return iterationResult[i] < iterationResult[j]
	})
	return CalculationResult{
		Digits: digits,
		Best:   iterationResult[0],
		Median: iterationResult[cap(iterationResult)/2],
		Worst:  iterationResult[cap(iterationResult)-1],
	}
}

func CalculatePIDigitsInRange(maxDigits int, iterations int) []CalculationResult {
	var results []CalculationResult
	for digits := 10; digits <= maxDigits; digits *= 10 {
		result := CalculatePIDigitsAndGetIntervals(digits, iterations)
		//printCalculation(result)
		results = append(results, result)
	}
	return results
}

func main() {
	var results = CalculatePIDigitsInRange(DefaultMaxDigits, DefaultIterations)
	for i := 0; i < len(results); i++ {
		printCalculation(results[i])
	}
}
