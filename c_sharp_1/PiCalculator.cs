using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace PiCalculation1
{
    class PiCalculator
    {
        private static long CalculatePIDigitsAndGetInterval(int digits)
        {
            long startTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();

            int[] reminders = new int[10 * digits / 3]; //reminders array required for calculation with size of reminders length
            Array.Fill(reminders, 2); //data initialization
            int[] piDigits = new int[digits]; //result array


            int tempInvalid = 0; //counter for temporary invalid digits
            int carryOver = 0;
            //main iteration
            for (int i = 0; i < digits; i++)
            {//next number calculation
                for (int k = reminders.Length - 1; k > 0; k--)
                {
                    int _sumOfCarryOver = reminders[k] * 10 + carryOver;
                    carryOver = (_sumOfCarryOver / (2 * k + 1)) * k;
                    reminders[k] = _sumOfCarryOver % (2 * k + 1);
                }
                //last step: k=0
                int sumOfCarryOver = reminders[0] * 10 + carryOver;
                int nextNumber = sumOfCarryOver / 10; //calculated i-th number of pi
                reminders[0] = sumOfCarryOver % 10;
                if (nextNumber == 9)
                {
                    tempInvalid++;
                }
                else if (nextNumber == 10)
                {
                    for (int h = i - tempInvalid; h < i; h++)
                    {
                        if (piDigits[h] == 9)
                            piDigits[h] = 0;
                        else
                            piDigits[h] += 1;
                    }
                    tempInvalid = 1;
                    nextNumber = 0;
                }
                else
                {
                    tempInvalid = 1;
                }
                piDigits[i] = nextNumber; //write new digit to result
            }
            long endTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
            return endTime - startTime;
        }

        protected class CalculationResult
        {
	        readonly int Digits;
            readonly long Best;
            readonly long Median;
            readonly long Worst;

            public CalculationResult(int digits, long best, long median, long worst)
            {
                Digits = digits;
                Best = best;
                Median = median;
                Worst = worst;
            }

            public void print()
            {
                Console.Write($"{Digits} best: {Best}, median: {Median}, worst: {Worst}");
            }
            public void println()
            {
                print();
                Console.WriteLine();
            }
        };

        static CalculationResult CalculatePIDigitsAndGetIntervals(int digits, int iterations)
        {
            long[] iterationResult = new long[iterations];
            for (int i = 0; i < iterationResult.Length; i++)
            {
                iterationResult[i] = CalculatePIDigitsAndGetInterval(digits);
            }
            Array.Sort(iterationResult);
            return new CalculationResult(digits, iterationResult[0], iterationResult[iterationResult.Length / 2], iterationResult[iterationResult.Length - 1]);
        }

        static CalculationResult[] CalculatePIDigitsInRange(int maxDigits, int iterations) {
            IList<CalculationResult> results = new List<CalculationResult>();
            for (int digits = 10; digits <= maxDigits; digits *= 10) {
                CalculationResult result = CalculatePIDigitsAndGetIntervals(digits, iterations);
                //result.println();
                results.Add(result);
	        }
            return Enumerable.Range(0, results.Count).Select(i => results[i]).ToArray();

        }

        private static readonly int DEFAULT_MAX_DIGITS = 100000;
        private static readonly int DEFAULT_ITERATIONS = 11;

        static void Main(string[] args)
        {
            CalculationResult[] results = CalculatePIDigitsInRange(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS);
            for (int i = 0; i < results.Length; i++)
            {
                results[i].println();
            }
        }
    }
}
