<?php
function calculatePIDigitsAndGetInterval(int $digits): int {
    $time_start = microtime(true);

    $reminders = array_fill(0, intdiv(10 * $digits, 3) ,2);
    $piDigits = array_fill(0, $digits, 0);

    $tempInvalid = 0; //counter for temporary invalid digits
    $carryOver = 0;

    for ($i = 0; $i < $digits; $i++) {//next number calculation
        for ($k = count($reminders) - 1; $k > 0; $k--) {
            $_sumOfCarryOver = $reminders[$k] * 10 + $carryOver;
            $carryOver = intdiv($_sumOfCarryOver , (2 * $k + 1)) * $k;
            $reminders[$k] = $_sumOfCarryOver % (2 * $k + 1);
        }
        //last step: k=0
        $sumOfCarryOver = $reminders[0] * 10 + $carryOver;
        $nextNumber = intdiv($sumOfCarryOver, 10); //calculated i-th number of pi
        $reminders[0] = $sumOfCarryOver % 10;
        if ($nextNumber === 9) {
            $tempInvalid++;
        } else if ($nextNumber === 10) {
            for ($h = $i - $tempInvalid; $h < $i; $h++) {
                if ($piDigits[$h] === 9)
                    $piDigits[$h] = 0;
                else
                    $piDigits[$h] += 1;
            }
            $tempInvalid = 1;
            $nextNumber = 0;
        } else {
            $tempInvalid = 1;
        }
        $piDigits[$i] = $nextNumber; //write new digit to result
    }
    $endTime = microtime(true);
    return intval(round($endTime - $time_start));
}

function CalculatePIDigitsAndGetIntervals(int $digits, int $iterations): CalculationResult {
    $iterationResult = array();
    for ($i = 0; $i < $iterations; $i++) {
        $iterationResult[] = calculatePIDigitsAndGetInterval($digits);
    }
    asort($iterationResult);
    return new CalculationResult(
        $digits, $iterationResult[0], $iterationResult[intdiv(count($iterationResult), 2)], $iterationResult[count($iterationResult) - 1]
    );
}
/**
 * @return array<CalculationResult>
 */
function CalculatePIDigitsInRange($maxDigits, $iterations): array {
    $results = array();
    for ($digits = 10; $digits <= $maxDigits; $digits *= 10) {
        $result = CalculatePIDigitsAndGetIntervals($digits, $iterations);
        $results[] = $result;
        //$result->println();
    }
    return $results;
}

const DEFAULT_MAX_DIGITS = 100000;
const DEFAULT_ITERATIONS = 11;
$results = CalculatePIDigitsInRange(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS);
foreach ($results as $res) {
    $res->println();
}


class CalculationResult
{
    public int $Digits;
    public int $Best;
    public int $Median;
    public int $Worst;

    function __construct(int $digits, int $best, int $median, int $worst)
    {
        $this->Digits = $digits;
        $this->Best = $best;
        $this->Median = $median;
        $this->Worst = $worst;
    }

    function println(): void {
        echo "{$this->Digits} best: {$this->Best}, median: {$this->Median}, worst: {$this->Worst}\n";
    }
}

?>
