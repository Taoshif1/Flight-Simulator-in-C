/**
 * @file ticket.c
 * @brief Implementation of ticket management functions.
 *
 * This file provides the concrete implementations for booking, canceling,
 * viewing tickets, and managing seat assignments, adhering to the specified
 * requirements for dynamic memory management, pointers, and error handling.
 * It also includes functions for saving and loading ticket data to/from files.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <stdlib.h> // For malloc, realloc, free
#include <string.h>

#include "ticket.h"

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
 * @var globalTickets
 * @brief Pointer to the dynamically allocated array of Ticket structures.
 */
Ticket *globalTickets = NULL;
/**
 * @var globalTicketCount
 * @brief Current number of tickets stored in the globalTickets array.
 */
int globalTicketCount = 0;
/**
 * @var globalTicketCapacity
 * @brief Maximum capacity of the globalTickets array before reallocation is needed.
 */
int globalTicketCapacity = 0;

/**
 * @brief Initializes the global ticket array by allocating initial memory.
 *
 * This function must be called once at the start of the program to set up
 * the ticket storage.
 *
 * @return 1 on success, 0 on failure (e.g., memory allocation failed).
 */
int initializeTickets() {
    globalTickets = (Ticket *)malloc(INITIAL_TICKET_CAPACITY * sizeof(Ticket));
    if (globalTickets == NULL) {
        printf("Error: Could not allocate memory for tickets.\n");
        return 0; // Failure
    }
    globalTicketCapacity = INITIAL_TICKET_CAPACITY;
    printf("Ticket system initialized with capacity %d.\n", globalTicketCapacity);
    return 1; // Success
}

/**
 * @brief Books a new ticket for a passenger on a specific flight and seat.
 *
 * This function prompts for passenger name, flight ID, and seat number.
 * It assigns a unique ticket ID and dynamically reallocates memory if needed.
 *
 * @return 1 on success, 0 on failure (e.g., ticket limit reached, invalid input, memory reallocation failed).
 */
int bookTicket() {
    // Check if reallocation is needed
    if (globalTicketCount >= globalTicketCapacity) {
        int newCapacity = globalTicketCapacity * 2; // Double the capacity
        Ticket *temp = (Ticket *)realloc(globalTickets, newCapacity * sizeof(Ticket));
        if (temp == NULL) {
            printf("Error: Could not reallocate memory for tickets.\n");
            return 0; // Failure
        }
        globalTickets = temp;
        globalTicketCapacity = newCapacity;
        printf("Ticket list capacity increased to %d.\n", globalTicketCapacity);
    }

    Ticket *t = globalTickets + globalTicketCount; // Pointer to new ticket location
    t->ticketID = globalTicketCount + 1; // Simple ID generation

    printf("Enter passenger name for ticket: ");
    GET_STRING(t->passengerName, MAX_NAME_LEN);

    printf("Enter flight ID for ticket: ");
    // Corner case: invalid integer input
    if (scanf("%d", &t->flightID) != 1 || t->flightID <= 0) {
        printf("Invalid Flight ID. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    printf("Enter seat number for ticket: ");
    // Corner case: invalid integer input or negative seat number
    if (scanf("%d", &t->seatNo) != 1 || t->seatNo <= 0) {
        printf("Invalid seat number. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    // In a real system, you would check if the flight exists and if the seat is available
    // For now, assume it's valid.

    globalTicketCount++;
    printf("Ticket booked successfully. Ticket ID: %d\n", t->ticketID);
    return 1; // Success
}

/**
 * @brief Cancels an existing ticket based on its ticket ID.
 *
 * This function prompts for a ticket ID, searches for the ticket, and removes
 * it from the list by shifting subsequent elements.
 *
 * @return 1 on success, 0 on failure (e.g., no tickets, ticket not found).
 */
int cancelTicket() {
    if (globalTicketCount == 0) {
        printf("No tickets to cancel.\n");
        return 0; // Failure
    }

    int ticketID;
    printf("Enter ticket ID to cancel: ");
    // Corner case: invalid integer input
    if (scanf("%d", &ticketID) != 1 || ticketID <= 0) {
        printf("Invalid Ticket ID. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    int foundIndex = -1;
    for (int i = 0; i < globalTicketCount; i++) {
        if ((globalTickets + i)->ticketID == ticketID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Ticket ID %d not found.\n", ticketID);
        return 0; // Failure
    }

    // Shift elements to fill the gap (using pointer arithmetic)
    for (int i = foundIndex; i < globalTicketCount - 1; i++) {
        *(globalTickets + i) = *(globalTickets + i + 1);
    }

    globalTicketCount--;
    printf("Ticket ID %d cancelled successfully. Total tickets: %d\n", ticketID, globalTicketCount);
    return 1; // Success
}

/**
 * @brief Displays a list of all booked tickets.
 *
 * This function prints the details of all tickets currently in the system.
 *
 * @return 1 on success, 0 on failure (e.g., no tickets to display).
 */
int showAllTickets() {
    if (globalTicketCount == 0) {
        printf("No tickets booked to display.\n");
        return 0; // Failure
    }

    printf("\n---- All Booked Tickets ----\n");
    for (int i = 0; i < globalTicketCount; i++) {
        Ticket *t = globalTickets + i; // Pointer arithmetic
        printf("Ticket ID: %d | Passenger: %s | Flight ID: %d | Seat: %d\n",
               t->ticketID, t->passengerName,
               t->flightID, t->seatNo);
    }
    return 1; // Success
}

/**
 * @brief Provides basic seat management for a given flight.
 *
 * This function prompts for a flight ID and lists all seats currently booked
 * for that flight, along with the passenger's name.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int seatManagement() {
    int flightID;
    printf("Enter flight ID to check seats: ");
    // Corner case: invalid integer input
    if (scanf("%d", &flightID) != 1 || flightID <= 0) {
        printf("Invalid Flight ID. Please enter a positive number.\n");
        clearInputBuffer();
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    printf("Seats booked on Flight %d:\n", flightID);
    int count = 0;
    for (int i = 0; i < globalTicketCount; i++) {
        Ticket *t = globalTickets + i; // Pointer arithmetic
        if (t->flightID == flightID) {
            printf("Seat No: %d (Passenger: %s)\n", t->seatNo, t->passengerName);
            count++;
        }
    }
    if (count == 0) {
        printf("No seats booked for this flight.\n");
    }
    return 1; // Success (even if no seats are booked, the operation was successful)
}

/**
 * @brief Frees the dynamically allocated memory used by the global ticket array.
 *
 * This function should be called before the program exits to prevent memory leaks.
 */
void cleanupTickets() {
    if (globalTickets != NULL) {
        free(globalTickets);
        globalTickets = NULL;
        globalTicketCount = 0;
        globalTicketCapacity = 0;
        printf("Ticket memory freed.\n");
    }
}

/**
 * @brief Saves all ticket data to a specified file.
 *
 * This function writes the current state of all tickets to a text file.
 * Each ticket's data is written on a new line, with components separated by commas.
 *
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int saveTickets(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return 0; // Failure
    }

    // Write the number of tickets as the first line
    fprintf(fp, "%d\n", globalTicketCount);

    for (int i = 0; i < globalTicketCount; i++) {
        const Ticket *t = globalTickets + i; // Pointer arithmetic
        fprintf(fp, "%d,%s,%d,%d\n",
                t->ticketID, t->passengerName, t->flightID, t->seatNo);
    }

    fclose(fp);
    printf("Tickets saved to %s successfully.\n", filename);
    return 1; // Success
}

/**
 * @brief Loads ticket data from a specified file.
 *
 * This function reads ticket data from a text file and populates the
 * global ticket array. It reallocates memory as needed. It expects the first
 * line to be the ticket count, followed by one ticket per line.
 *
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadTickets(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No ticket data file found (%s). Starting with empty ticket list.\n", filename);
        globalTicketCount = 0; // Ensure count is zero if file doesn't exist
        return 0; // Not a critical failure, just means no data to load
    }

    int loadedCount = 0;
    // Read the number of tickets from the first line
    if (fscanf(fp, "%d\n", &loadedCount) != 1) {
        printf("Error reading ticket count from %s. File might be corrupted.\n", filename);
        fclose(fp);
        return 0;
    }

    // Reallocate memory for tickets if current capacity is insufficient
    if (globalTickets != NULL) {
        free(globalTickets);
        globalTickets = NULL; // Defensive programming
    }
    globalTickets = (Ticket *)malloc(loadedCount * sizeof(Ticket));
    if (globalTickets == NULL) {
        printf("Error: Could not allocate memory for loading tickets.\n");
        fclose(fp);
        return 0;
    }
    globalTicketCapacity = loadedCount; // Set capacity to loaded count for now

    globalTicketCount = 0; // Reset count before loading

    char line_buffer[256]; // Buffer to read each line
    while (globalTicketCount < loadedCount && fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
        Ticket *t = globalTickets + globalTicketCount; // Pointer to current ticket location
        char *token;
        char *rest = line_buffer;

        // ticketID
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading ticketID.\n"); break; }
        t->ticketID = atoi(token);
        rest = NULL; // For subsequent strtok calls on the same line

        // passengerName
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading passengerName.\n"); break; }
        strncpy(t->passengerName, token, MAX_NAME_LEN - 1);
        t->passengerName[MAX_NAME_LEN - 1] = '\0';

        // flightID
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading flightID.\n"); break; }
        t->flightID = atoi(token);

        // seatNo
        token = strtok(rest, "\n"); // Read till newline
        if (token == NULL) { printf("Error reading seatNo.\n"); break; }
        t->seatNo = atoi(token);

        globalTicketCount++;
    }

    fclose(fp);
    printf("Loaded %d tickets from %s.\n", globalTicketCount, filename);
    return 1; // Success
}