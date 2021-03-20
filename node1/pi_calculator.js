function calculatePIDigitsAndGetInterval(digits) {
    const startTime = new Date().getTime();

    const reminders = new Array(Math.floor(10 * digits / 3)).fill(2); //reminders array required for calculation with size of reminders length
    const piDigits = new Array(digits);

    let tempInvalid = 0; //counter for temporary invalid digits
    let carryOver = 0;

    for (let i = 0; i < digits; i++) {//next number calculation
        for (let k = reminders.length - 1; k > 0; k--) {
            let _sumOfCarryOver = reminders[k] * 10 + carryOver;
            carryOver = Math.floor(_sumOfCarryOver / (2 * k + 1)) * k;
            reminders[k] = _sumOfCarryOver % (2 * k + 1);
        }
        //last step: k=0
        let sumOfCarryOver = reminders[0] * 10 + carryOver;
        let nextNumber = Math.floor(sumOfCarryOver / 10); //calculated i-th number of pi
        reminders[0] = sumOfCarryOver % 10;
        if (nextNumber === 9) {
            tempInvalid++;
        } else if (nextNumber === 10) {
            for (let h = i - tempInvalid; h < i; h++) {
                if (piDigits[h] === 9)
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
    const endTime = new Date().getTime();
    return endTime - startTime;
}

function CalculatePIDigitsAndGetIntervals(digits, iterations) {
    const iterationResult = new Array(iterations);
    for (let i = 0; i < iterations; i++) {
        iterationResult[i] = calculatePIDigitsAndGetInterval(digits);
    }
    iterationResult.sort();
    return {
        Digits: digits,
        Best: iterationResult[0],
        Median: iterationResult[Math.floor(iterationResult.length / 2)],
        Worst: iterationResult[iterationResult.length - 1],
        println: function() {
            console.log(`${this.Digits} best: ${this.Best}, median: ${this.Median}, worst: ${this.Worst}`);
        }
    };
}

function CalculatePIDigitsInRange(maxDigits, iterations) {
    const results = [];
    for (let digits = 10; digits <= maxDigits; digits *= 10) {
        const result = CalculatePIDigitsAndGetIntervals(digits, iterations);
        //result.println();
        results.push(result);
    }
    return results;
}

const DEFAULT_MAX_DIGITS = 100000;
const DEFAULT_ITERATIONS = 11;
(function(){
    const results = CalculatePIDigitsInRange(DEFAULT_MAX_DIGITS, DEFAULT_ITERATIONS);
    results.forEach((res) => {
        res.println();
    });
})();

