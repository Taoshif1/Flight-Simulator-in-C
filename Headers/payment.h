/**
 * @file payment.h
 * @brief Header file for payment handling functions.
 *
 * This file contains function prototypes related to processing payments.
 */

#ifndef PAYMENT_H
#define PAYMENT_H

/**
 * @brief Handles a payment transaction.
 *
 * This function prompts the user for the payment method and amount.
 * In a real system, this would involve more complex payment processing logic.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int handlePayment();

#endif // PAYMENT_H