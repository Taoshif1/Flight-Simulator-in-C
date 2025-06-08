/**
 * @file passenger.c
 * @brief Implementation of passenger management functions.
 *
 * This file provides the concrete implementations for adding, removing,
 * and viewing passenger data, adhering to the specified requirements
 * for dynamic memory management, pointers, and error handling. It also
 * includes functions for saving and loading passenger data to/from files.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <stdlib.h> // For malloc, realloc, free
#include <string.h>

#include "passenger.h"

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
 * @var globalPassengers
 * @brief Pointer to the dynamically allocated array of Passenger structures.
 */
Passenger *globalPassengers = NULL;
/**
 * @var globalPassengerCount
 * @brief Current number of passengers stored in the globalPassengers array.
 */
int globalPassengerCount = 0;
/**
 * @var globalPassengerCapacity
 * @brief Maximum capacity of the globalPassengers array before reallocation is needed.
 */
int globalPassengerCapacity = 0;

/**
 * @brief Initializes the global passenger array by allocating initial memory.
 *
 * This function must be called once at the start of the program to set up
 * the passenger storage.
 *
 * @return 1 on success, 0 on failure (e.g., memory allocation failed).
 */
int initializePassengers() {
    globalPassengers = (Passenger *)malloc(INITIAL_PASSENGER_CAPACITY * sizeof(Passenger));
    if (globalPassengers == NULL) {
        printf("Error: Could not allocate memory for passengers.\n");
        return 0; // Failure
    }
    globalPassengerCapacity = INITIAL_PASSENGER_CAPACITY;
    printf("Passenger system initialized with capacity %d.\n", globalPassengerCapacity);
    return 1; // Success
}

/**
 * @brief Adds a new passenger to the system.
 *
 * This function prompts the user for passenger details (name, age, passport),
 * validates input, checks for duplicate passport numbers, and dynamically
 * reallocates memory if the passenger list capacity is exceeded.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input, duplicate passport, memory reallocation failed).
 */
int addPassenger() {
    // Check if reallocation is needed
    if (globalPassengerCount >= globalPassengerCapacity) {
        int newCapacity = globalPassengerCapacity * 2; // Double the capacity
        Passenger *temp = (Passenger *)realloc(globalPassengers, newCapacity * sizeof(Passenger));
        if (temp == NULL) {
            printf("Error: Could not reallocate memory for passengers.\n");
            return 0; // Failure
        }
        globalPassengers = temp;
        globalPassengerCapacity = newCapacity;
        printf("Passenger list capacity increased to %d.\n", globalPassengerCapacity);
    }

    Passenger *p = globalPassengers + globalPassengerCount; // Pointer to new passenger location

    printf("Enter passenger name: ");
    GET_STRING(p->name, MAX_NAME_LEN);

    printf("Enter age: ");
    // Corner case: invalid age input
    if (scanf("%d", &p->age) != 1 || p->age <= 0) {
        printf("Invalid age! Age must be a positive integer.\n");
        clearInputBuffer(); // Clear input buffer
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    printf("Enter passport number: ");
    GET_STRING(p->passport, sizeof(p->passport));

    // Corner case: Duplicate check for passport number
    for (int i = 0; i < globalPassengerCount; i++) {
        if (strcmp((globalPassengers + i)->passport, p->passport) == 0) {
            printf("Error: Passenger with passport number %s already exists!\n", p->passport);
            return 0; // Failure
        }
    }

    p->assignedFlightID = 0; // Initialize, no flight assigned yet
    p->assignedSeatNo = 0;   // Initialize, no seat assigned yet

    globalPassengerCount++;
    printf("Passenger added successfully. Total passengers: %d\n", globalPassengerCount);
    return 1; // Success
}

/**
 * @brief Removes an existing passenger from the system.
 *
 * This function prompts for a passport number, searches for the corresponding
 * passenger, and removes them from the list by shifting subsequent elements.
 *
 * @return 1 on success, 0 on failure (e.g., no passengers, passenger not found).
 */
int removePassenger() {
    if (globalPassengerCount == 0) {
        printf("No passengers to remove.\n");
        return 0; // Failure
    }

    char passportToRemove[20];
    printf("Enter passport number of passenger to remove: ");
    GET_STRING(passportToRemove, sizeof(passportToRemove));

    int foundIndex = -1;
    for (int i = 0; i < globalPassengerCount; i++) {
        if (strcmp((globalPassengers + i)->passport, passportToRemove) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Passenger with passport number %s not found.\n", passportToRemove);
        return 0; // Failure
    }

    // Shift elements to fill the gap (using pointer arithmetic)
    for (int i = foundIndex; i < globalPassengerCount - 1; i++) {
        *(globalPassengers + i) = *(globalPassengers + i + 1);
    }

    globalPassengerCount--;
    printf("Passenger with passport number %s removed successfully. Total passengers: %d\n",
           passportToRemove, globalPassengerCount);
    return 1; // Success
}

/**
 * @brief Displays a list of all registered passengers.
 *
 * This function prints the details of all passengers currently in the system,
 * including their name, age, passport number, and assigned flight/seat if any.
 *
 * @return 1 on success, 0 on failure (e.g., no passengers to display).
 */
int viewPassengers() {
    if (globalPassengerCount == 0) {
        printf("No passengers found to display.\n");
        return 0; // Failure
    }

    printf("\n---- All Registered Passengers ----\n");
    for (int i = 0; i < globalPassengerCount; i++) {
        Passenger *p = globalPassengers + i; // Pointer arithmetic
        printf("Passenger %d:\n", i + 1);
        printf("  Name       : %s\n", p->name);
        printf("  Age        : %d\n", p->age);
        printf("  Passport   : %s\n", p->passport);
        if (p->assignedFlightID != 0) {
            printf("  Flight ID  : %d\n", p->assignedFlightID);
            printf("  Seat No    : %d\n", p->assignedSeatNo);
        } else {
            printf("  Flight ID  : Not assigned\n");
            printf("  Seat No    : Not assigned\n");
        }
        printf("----------------------------\n");
    }
    return 1; // Success
}

/**
 * @brief Frees the dynamically allocated memory used by the global passenger array.
 *
 * This function should be called before the program exits to prevent memory leaks.
 */
void cleanupPassengers() {
    if (globalPassengers != NULL) {
        free(globalPassengers);
        globalPassengers = NULL;
        globalPassengerCount = 0;
        globalPassengerCapacity = 0;
        printf("Passenger memory freed.\n");
    }
}

/**
 * @brief Saves all passenger data to a specified file.
 *
 * This function writes the current state of all passengers to a text file.
 * Each passenger's data is written on a new line, with components separated by commas.
 *
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int savePassengers(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return 0; // Failure
    }

    // Write the number of passengers as the first line
    fprintf(fp, "%d\n", globalPassengerCount);

    for (int i = 0; i < globalPassengerCount; i++) {
        const Passenger *p = globalPassengers + i; // Pointer arithmetic
        fprintf(fp, "%s,%d,%s,%d,%d\n",
                p->name, p->age, p->passport, p->assignedFlightID, p->assignedSeatNo);
    }

    fclose(fp);
    printf("Passengers saved to %s successfully.\n", filename);
    return 1; // Success
}

/**
 * @brief Loads passenger data from a specified file.
 *
 * This function reads passenger data from a text file and populates the
 * global passenger array. It reallocates memory as needed. It expects the first
 * line to be the passenger count, followed by one passenger per line.
 *
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadPassengers(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No passenger data file found (%s). Starting with empty passenger list.\n", filename);
        globalPassengerCount = 0; // Ensure count is zero if file doesn't exist
        return 0; // Not a critical failure, just means no data to load
    }

    int loadedCount = 0;
    // Read the number of passengers from the first line
    if (fscanf(fp, "%d\n", &loadedCount) != 1) {
        printf("Error reading passenger count from %s. File might be corrupted.\n", filename);
        fclose(fp);
        return 0;
    }

    // Reallocate memory for passengers if current capacity is insufficient
    // or if it's the first load
    if (globalPassengers != NULL) {
        free(globalPassengers);
        globalPassengers = NULL; // Defensive programming
    }
    globalPassengers = (Passenger *)malloc(loadedCount * sizeof(Passenger));
    if (globalPassengers == NULL) {
        printf("Error: Could not allocate memory for loading passengers.\n");
        fclose(fp);
        return 0;
    }
    globalPassengerCapacity = loadedCount; // Set capacity to loaded count for now

    globalPassengerCount = 0; // Reset count before loading

    char line_buffer[256]; // Buffer to read each line
    while (globalPassengerCount < loadedCount && fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
        Passenger *p = globalPassengers + globalPassengerCount; // Pointer to current passenger location
        char *token;
        char *rest = line_buffer;

        // name
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading passenger name.\n"); break; }
        strncpy(p->name, token, MAX_NAME_LEN - 1);
        p->name[MAX_NAME_LEN - 1] = '\0';
        rest = NULL; // For subsequent strtok calls on the same line

        // age
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading passenger age.\n"); break; }
        p->age = atoi(token);

        // passport
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading passenger passport.\n"); break; }
        strncpy(p->passport, token, 19);
        p->passport[19] = '\0';

        // assignedFlightID
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading assignedFlightID.\n"); break; }
        p->assignedFlightID = atoi(token);

        // assignedSeatNo
        token = strtok(rest, "\n"); // Read till newline
        if (token == NULL) { printf("Error reading assignedSeatNo.\n"); break; }
        p->assignedSeatNo = atoi(token);

        globalPassengerCount++;
    }

    fclose(fp);
    printf("Loaded %d passengers from %s.\n", globalPassengerCount, filename);
    return 1; // Success
}