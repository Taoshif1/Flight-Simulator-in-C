/**
 * @file passenger.h
 * @brief Header file for passenger management functions.
 *
 * This file contains function prototypes for managing passenger
 * operations, including adding, removing, viewing and updating
 * passenger information in the flight simulator project. It also
 * declares functions for saving and loading passenger data.
 */

#ifndef PASSENGER_H
#define PASSENGER_H

#include "common.h" // For MAX_NAME_LEN and other common definitions

/**
 * @struct Passenger
 * @brief Represents a single passenger with their personal and flight details.
 */
typedef struct Passenger {
    char name[MAX_NAME_LEN];    /**< Name of the passenger. */
    int age;                    /**< Age of the passenger. */
    char passport[20];          /**< Passport number of the passenger (unique identifier). */
    int assignedFlightID;       /**< ID of the flight the passenger is assigned to (0 if none). */
    int assignedSeatNo;         /**< Seat number assigned to the passenger (0 if none). */
} Passenger;

/**
 * @var globalPassengers
 * @brief Pointer to the dynamically allocated array of Passenger structures.
 */
extern Passenger *globalPassengers;
/**
 * @var globalPassengerCount
 * @brief Current number of passengers stored in the globalPassengers array.
 */
extern int globalPassengerCount;
/**
 * @var globalPassengerCapacity
 * @brief Maximum capacity of the globalPassengers array before reallocation is needed.
 */
extern int globalPassengerCapacity;

/**
 * @def INITIAL_PASSENGER_CAPACITY
 * @brief Initial number of passenger slots allocated when the system starts.
 */
#define INITIAL_PASSENGER_CAPACITY 10

/**
 * @brief Initializes the global passenger array by allocating initial memory.
 *
 * This function must be called once at the start of the program to set up
 * the passenger storage.
 *
 * @return 1 on success, 0 on failure (e.g., memory allocation failed).
 */
int initializePassengers();

/**
 * @brief Adds a new passenger to the system.
 *
 * This function prompts the user for passenger details (name, age, passport),
 * validates input, checks for duplicate passport numbers, and dynamically
 * reallocates memory if the passenger list capacity is exceeded.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input, duplicate passport, memory reallocation failed).
 */
int addPassenger();

/**
 * @brief Removes an existing passenger from the system.
 *
 * This function prompts for a passport number, searches for the corresponding
 * passenger, and removes them from the list by shifting subsequent elements.
 *
 * @return 1 on success, 0 on failure (e.g., no passengers, passenger not found).
 */
int removePassenger();

/**
 * @brief Displays a list of all registered passengers.
 *
 * This function prints the details of all passengers currently in the system,
 * including their name, age, passport number, and assigned flight/seat if any.
 *
 * @return 1 on success, 0 on failure (e.g., no passengers to display).
 */
int viewPassengers();

/**
 * @brief Frees the dynamically allocated memory used by the global passenger array.
 *
 * This function should be called before the program exits to prevent memory leaks.
 */
void cleanupPassengers();

/**
 * @brief Saves all passenger data to a specified file.
 *
 * This function writes the current state of all passengers to a text file.
 *
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int savePassengers(const char *filename);

/**
 * @brief Loads passenger data from a specified file.
 *
 * This function reads passenger data from a text file and populates the
 * global passenger array. It reallocates memory as needed.
 *
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadPassengers(const char *filename);


#endif // PASSENGER_H