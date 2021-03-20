import time


def calculate_pi_digits_and_get_interval(digits: int, try_nr: int, total_tries: int) -> int:
    start_time = int(time.time() * 1000)
    reminder_length = 10 * digits // 3
    reminders = []
    pi_digits = []
    for i in range(reminder_length):
        reminders.append(2)
        if i < digits:
            pi_digits.append(0)

    temp_invalid = 0  # counter for temporary invalid digits
    carry_over = 0

    # main iteration
    for i in range(digits):  # next number calculation
        # current = (trynr * digits) + i;
        # total = (totaltries * digits)
        # print("\r{:.2f}% [{}/{}]".format(100 * current / total, current, total), end="")
        for k in range(reminder_length - 1, 0, -1):  # next number calculation
            _sumOfCarryOver = reminders[k] * 10 + carry_over
            carry_over = _sumOfCarryOver // (2 * k + 1) * k
            reminders[k] = _sumOfCarryOver % (2 * k + 1)
        # last step: k=0
        sum_of_carry_over = reminders[0] * 10 + carry_over
        next_number = sum_of_carry_over // 10  # calculated i-th number of pi
        reminders[0] = sum_of_carry_over % 10
        if next_number == 9:
            temp_invalid += 1
        elif next_number == 10:
            for h in range(i - temp_invalid, i):
                if pi_digits[h] == 9:
                    pi_digits[h] = 0
                else:
                    pi_digits[h] += 1
            temp_invalid = 1
            next_number = 0
        else:
            temp_invalid = 1
        pi_digits[i] = next_number  # write new digit to result

    end_time = int(time.time() * 1000)
    return end_time - start_time


class CalculationResult:
    Digits: int
    Best: int
    Median: int
    Worst: int

    def __init__(self, digits: int, best: int, median: int, worst: int):
        self.Digits = digits
        self.Best = best
        self.Median = median
        self.Worst = worst

    def println(self):
        print("\r%d, best: %d, median: %d, worst: %d" % (self.Digits, self.Best, self.Median, self.Worst))


def calculate_pi_digits_and_get_intervals(digits: int, iterations: int) -> CalculationResult:
    iteration_result = []
    for i in range(iterations):
        iteration_result.append(calculate_pi_digits_and_get_interval(digits, i, iterations))
    iteration_result.sort()
    return CalculationResult(digits, iteration_result[0], iteration_result[len(iteration_result) // 2],
                             iteration_result[len(iteration_result) - 1])


def calculate_pi_digits_in_range(max_digits, iterations):
    results = []

    digits = 10
    while digits <= max_digits:
        result = calculate_pi_digits_and_get_intervals(digits, iterations)
        result.println()
        results.append(result)
        digits *= 10
    return results


DEFAULT_MAX_DIGITS = 100000
DEFAULT_ITERATIONS = 11


def main():
    results = calculate_pi_digits_in_range(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS)

    for result in results:
        result.println()


if __name__ == "__main__":
    main()
