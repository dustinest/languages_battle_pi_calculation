package ee.fj.picalc;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

/**
 * calculate pi using Spigot algorithm
 * Realization of spigout algorighm: for explanation see
 * http://cut-the-knot.org/Curriculum/Algorithms/SpigotForPi.shtml
 */

class PiCalculator {
	private static final int DEFAULT_MAX_DIGITS = 100000;
	private static final int DEFAULT_ITERATIONS = 11;

	private static long calculatePIDigitsAndGetInterval(int digits) {
		final long startTime = System.currentTimeMillis();

		final int[] reminders = new int[10 * digits / 3]; //reminders array required for calculation with size of reminders length
		Arrays.fill(reminders, 2); //data initialization
		final int[] piDigits = new int[digits]; //result array


		int tempInvalid = 0; //counter for temporary invalid digits
		int carryOver = 0;

		//main iteration
		for (int i = 0; i < digits; i++) {//next number calculation
			for (int k = reminders.length - 1; k > 0; k--) {
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
			} else {
				tempInvalid = 1;
			}
			piDigits[i] = nextNumber; //write new digit to result
		}
		final long endTime = System.currentTimeMillis();
		return endTime - startTime;
	}

	static CalculationResult CalculatePIDigitsAndGetIntervals(final int digits, final int iterations) {
		final long[] iterationResult = new long[iterations];
		for (int i = 0; i < iterations; i++) {
			iterationResult[i] = calculatePIDigitsAndGetInterval(digits);
		}
		Arrays.sort(iterationResult);
		return new CalculationResult(digits, iterationResult[0], iterationResult[iterationResult.length / 2], iterationResult[iterationResult.length - 1]);
	}

	static CalculationResult[] CalculatePIDigitsInRange(final int maxDigits, final int iterations) {
		List<CalculationResult> results = new ArrayList<>();
		for (int digits = 10; digits <= maxDigits; digits *= 10) {
			CalculationResult result = CalculatePIDigitsAndGetIntervals(digits, iterations);
			//result.println();
			results.add(result);
		}
		return results.toArray(new CalculationResult[0]);
	}

	public static void main(String... args) {
		Stream.of(CalculatePIDigitsInRange(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS)).forEach(CalculationResult::println);
	}

	static class CalculationResult {
		public final int Digits;
		public final long Best;
		public final long Median;
		public final long Worst;

		CalculationResult(int digits, long best, long median, long worst) {
			Digits = digits;
			Best = best;
			Median = median;
			Worst = worst;
		}

		void print() {
			System.out.printf("%d best: %d, median: %d, worst: %d", Digits, Best, Median, Worst);
		}

		void println() {
			print();
			System.out.println();
		}
	}
}
