/**
 * @file payment.c
 * @brief Implementation of payment handling functions.
 *
 * This file provides the concrete implementations for processing payments.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <string.h> // For strtok if using GET_STRING

#include "payment.h"

/**
 * @brief Clears the input buffer.
 *
 * This function reads and discards characters from stdin until a newline
 * character or EOF is encountered. This is crucial for preventing issues
 * when mixing scanf with fgets.
 */
static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Handles a payment transaction.
 *
 * This function prompts the user for the payment method and amount.
 * In a real system, this would involve more complex payment processing logic.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int handlePayment() {
    char method[MAX_NAME_LEN]; // Use MAX_NAME_LEN for consistency

    printf("Enter payment method (Cash/Card/Online): ");
    GET_STRING(method, MAX_NAME_LEN); // Use the macro for input

    float amount; // Declare amount here
    printf("Enter amount to pay: ");
    // Corner case: invalid float input or negative amount
    if (scanf("%f", &amount) != 1 || amount <= 0.0) {
        printf("Invalid amount. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    printf("Payment of %.2f via %s completed successfully.\n", amount, method);
    return 1; // Success
}