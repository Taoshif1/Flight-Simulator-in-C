/**
 * @file crew.c
 * @brief Implementation of crew management functions.
 *
 * This file provides the concrete implementations for assigning crew members.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <string.h>

#include "crew.h"   // Include crew.h for the function prototype

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
 * @brief Assigns a crew member to a specific flight.
 *
 * This function prompts the user for the crew member's name and the flight ID
 * they are to be assigned to. In a more complex system, this would involve
 * checking flight existence and crew availability.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int assignCrew() {
    char crewName[MAX_NAME_LEN]; // Use MAX_NAME_LEN for consistency
    int flightID;

    printf("Enter crew name: ");
    GET_STRING(crewName, MAX_NAME_LEN); // Use the macro for input

    printf("Enter flight ID to assign: ");
    // Corner case: invalid integer input
    if (scanf("%d", &flightID) != 1 || flightID <= 0) {
        printf("Invalid Flight ID. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    // In a real system, you'd check if the flightID exists using searchFlight
    // For now, just print the assignment.
    printf("Crew member %s assigned to Flight ID %d.\n", crewName, flightID);
    return 1; // Success
}