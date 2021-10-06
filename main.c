/**
 * | Author: Elmar Blume (ETIV1.B)
 * | Description: Simple Calculator
 * | Date: 06-10-2021
 */

#include <stdio.h>

typedef enum {
    SUCCESS,
    DIVIDE_BY_ZERO,
    MODULO_ZERO,
    EXIT,
    UNKNOWN_ERROR
} ResultType;

typedef enum {
    POWER_ON,
    POWER_OFF
} CalculatorState;

/**
 * A calculation result represents a successful calculation process,
 * this means it is possible to have an error {@see ResultType}
 */
typedef struct CalculationResult {
    ResultType resultType;
    float output;
    char operatorStr;
} CalculationResult;

/**
 * Create a new calculation result structure
 *
 * @param type the result resultType of the calculation
 * @param output the output value of the calculation
 * @return the newly created calculation result
 */
CalculationResult createCalculationResult(ResultType type, float output, char operatorStr) {
    CalculationResult calculationResult = {
            .resultType = type,
            .output = output,
            .operatorStr = operatorStr
    };

    return calculationResult;
}

/**
 * Perform a addition calculation with 2 values
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return the outcome of the equation
 */
CalculationResult addValues(float first, float second) {
    float output = first + second;
    return createCalculationResult(SUCCESS, output, '+');
}

/**
 * Perform a subtraction calculation with 2 values
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return the outcome of the equation
 */
CalculationResult subtractValues(float first, float second) {
    float output = first - second;
    return createCalculationResult(SUCCESS, output, '-');
}

/**
 * Perform a multiplication calculation with 2 values
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return the outcome of the equation
 */
CalculationResult multiplyValues(float first, float second) {
    float output = first * second;
    return createCalculationResult(SUCCESS, output, '*');
}

/**
 * Perform a division calculation with 2 values
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return the outcome of the equation
 */
CalculationResult divideValues(float first, float second) {
    if (second == 0) return createCalculationResult(DIVIDE_BY_ZERO, -1, '?');

    float output = first / second;
    return createCalculationResult(SUCCESS, output, '/');
}

/**
 * Perform a modulus calculation with 2 values
 * NOTE: ResultType will be MODULO_ZERO if first argument is 0
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return the outcome of the equation
 */
CalculationResult modulusValues(float first, float second) {
    if (first == 0) return createCalculationResult(MODULO_ZERO, -1, '?');

    float output = (float) ((int) first % (int) second);
    return createCalculationResult(SUCCESS, output, '%');
}

/**
 * Prompt the console user a floating point input
 *
 * @param question the question to prompt the user with
 * @return the given floating point input
 */
float promptInput(char question[]) {
    float input = 0;

    printf("%s", question);
    scanf("%f", &input);

    return input;
}

/**
 * Perform the calculation with the given choice of equation type with the two given values
 *
 * @param choice the equation option
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @return a new calculation result
 */
CalculationResult performCalculation(int choice, float first, float second) {
    switch (choice) {
        case 0:
            return createCalculationResult(EXIT, 0, '?');
        case 1:
            return addValues(first, second);
        case 2:
            return subtractValues(first, second);
        case 3:
            return multiplyValues(first, second);
        case 4:
            return divideValues(first, second);
        case 5:
            return modulusValues(first, second);
        default:
            return createCalculationResult(UNKNOWN_ERROR, 0, '?');
    }
}

/**
 * Print the calculator menu with all the possible input options
 */
void printCalculatorMenu() {
    printf("\n");
    printf("MENU\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Modulus\n");
    printf("0. Exit\n\n");
}

/**
 * Print the result of the calculation
 *
 * @param first the first argument of the equation
 * @param second the second argument of the equation
 * @param calculationResult the calculation result of the equation
 */
void printCalculationOutput(float first, float second, CalculationResult calculationResult) {
    printf(">> Result: %.1f %c %.1f = %.1f\n", first, calculationResult.operatorStr,
           second, calculationResult.output);
}

/**
 * The main program
 */
int main() {
    CalculatorState calculatorState = POWER_ON;
    while (calculatorState == POWER_ON) {
        // Start the program with printing the calculator menu
        printCalculatorMenu();

        int choice = 0;

        printf("Enter your choice:");
        scanf("%d", &choice);

        if (choice < 0 || choice > 5) {
            printf("!! ERROR: Please choose one of the options in the menu!\n");
            continue;
        }

        float first = promptInput("\nEnter first operand:");
        float second = promptInput("Enter second operand:");
        CalculationResult calculationResult = performCalculation(choice, first, second);

        ResultType resultType = calculationResult.resultType;
        switch (resultType) {
            case SUCCESS:
                printCalculationOutput(first, second, calculationResult);
                break;

            case DIVIDE_BY_ZERO:
                printf("!! ERROR: You are not allowed to divide by 0 !!\n");
                break;

            case MODULO_ZERO:
                printf("!! ERROR: You are not allowed to get the modulo of 0 !!\n");
                break;

            case EXIT:
            case UNKNOWN_ERROR:
            default:
                calculatorState = POWER_OFF;
                break;
        }
    }

    return 0;
}
