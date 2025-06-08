/**
 * @file flight.c
 * @brief Implementation of flight management functions.
 *
 * This file provides the concrete implementations for adding, listing,
 * searching, deleting, and sorting flight data, adhering to the specified
 * requirements for memory efficiency, pointers, and error handling. It also
 * includes functions for saving and loading flight data to/from files.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For qsort, malloc, realloc, free

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
 * @brief Compares two DateTime structures.
 *
 * This helper function compares two DateTime structures chronologically.
 * It is used primarily for sorting flights by departure or arrival time.
 *
 * @param dt1 A pointer to the first DateTime structure.
 * @param dt2 A pointer to the second DateTime structure.
 * @return An integer less than, equal to, or greater than zero if dt1 is found,
 * respectively, to be less than, to match, or be greater than dt2.
 */
int compareDateTime(const DateTime *dt1, const DateTime *dt2) {
    if (dt1->year != dt2->year) return (int)dt1->year - (int)dt2->year;
    if (dt1->month != dt2->month) return (int)dt1->month - (int)dt2->month;
    if (dt1->day != dt2->day) return (int)dt1->day - (int)dt2->day;
    if (dt1->hour != dt2->hour) return (int)dt1->hour - (int)dt2->hour;
    if (dt1->minute != dt2->minute) return (int)dt1->minute - (int)dt2->minute;
    return 0;
}

/**
 * @brief Comparison function for qsort to sort flights by departure time.
 *
 * This function is a callback for the qsort standard library function.
 * It casts the void pointers to Flight pointers and uses compareDateTime.
 *
 * @param a A pointer to the first Flight structure.
 * @param b A pointer to the second Flight structure.
 * @return The result of compareDateTime for the departure times of the two flights.
 */
int compareFlightsByDeparture(const void *a, const void *b) {
    const Flight *flightA = (const Flight *)a;
    const Flight *flightB = (const Flight *)b;
    return compareDateTime(&flightA->departure, &flightB->departure);
}

/**
 * @brief Adds a new flight to the flight list.
 *
 * This function prompts the user to enter flight details, including
 * flight ID, name, origin, destination, departure time, arrival time
 * and available seats. It then adds the flight to the given array.
 * It handles input validation and checks for duplicate flight IDs.
 *
 * @param flights A pointer to the array of Flight structures where the new flight will be added.
 * @param flightCount A pointer to the current flight count, which will be incremented on success.
 * @return 1 on success, 0 on failure (e.g., flight limit reached, invalid input, duplicate ID).
 */
int addFlight(Flight *flights, int *flightCount) {
    if (*flightCount >= MAX_FLIGHTS) {
        printf("Flight limit reached! Cannot add more flights.\n");
        fflush(stdout); // Flush output
        return 0; // Failure
    }

    Flight *newFlight = flights + *flightCount; // Pointer to the new flight location

    printf("Enter flight ID: ");
    fflush(stdout); // Flush output before scanf
    // Corner case: invalid integer input
    if (scanf("%d", &newFlight->flightID) != 1) {
        printf("Invalid Flight ID. Please enter a number.\n");
        fflush(stdout); // Flush output
        clearInputBuffer(); // Clear input buffer
        return 0; // Failure
    }
    clearInputBuffer(); // Consume newline after scanf

    // Corner case: check for duplicate flight ID
    for (int i = 0; i < *flightCount; i++) {
        if ((flights + i)->flightID == newFlight->flightID) {
            printf("Error: Flight with ID %d already exists.\n", newFlight->flightID);
            fflush(stdout); // Flush output
            return 0; // Failure
        }
    }

    printf("Enter flight name: ");
    fflush(stdout); // Flush output before GET_STRING
    GET_STRING(newFlight->flightName, MAX_NAME_LEN);

    printf("Enter origin: ");
    fflush(stdout); // Flush output before GET_STRING
    GET_STRING(newFlight->origin, MAX_NAME_LEN);

    printf("Enter destination: ");
    fflush(stdout); // Flush output before GET_STRING
    GET_STRING(newFlight->destination, MAX_NAME_LEN);

    // Use temporary variables for scanf to read into, then assign to bit-fields
    unsigned int temp_day, temp_month, temp_year, temp_hour, temp_minute;

    printf("Enter departure (DD MMYYYY HH MM): ");
    fflush(stdout); // Flush output before scanf
    if (scanf("%u %u %u %u %u",
              &temp_day, &temp_month, &temp_year, &temp_hour, &temp_minute) != 5) {
        printf("Invalid departure date/time format.\n");
        fflush(stdout); // Flush output
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer(); // Consume newline after scanf

    // Assign from temporary variables to bit-fields
    newFlight->departure.day = temp_day;
    newFlight->departure.month = temp_month;
    newFlight->departure.year = temp_year;
    newFlight->departure.hour = temp_hour;
    newFlight->departure.minute = temp_minute;

    printf("Enter arrival (DD MMYYYY HH MM): ");
    fflush(stdout); // Flush output before scanf
    if (scanf("%u %u %u %u %u",
              &temp_day, &temp_month, &temp_year, &temp_hour, &temp_minute) != 5) {
        printf("Invalid arrival date/time format.\n");
        fflush(stdout); // Flush output
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer(); // Consume newline after scanf

    // Assign from temporary variables to bit-fields
    newFlight->arrival.day = temp_day;
    newFlight->arrival.month = temp_month;
    newFlight->arrival.year = temp_year;
    newFlight->arrival.hour = temp_hour;
    newFlight->arrival.minute = temp_minute;

    // Corner case: arrival before departure
    if (compareDateTime(&newFlight->departure, &newFlight->arrival) > 0) {
        printf("Error: Arrival time cannot be before departure time.\n");
        fflush(stdout); // Flush output
        return 0;
    }

    printf("Enter status (0 = ON_TIME, 1 = DELAYED, 2 = CANCELLED): ");
    fflush(stdout); // Flush output before scanf
    int statusInput;
    // Corner case: invalid enum input
    if (scanf("%d", &statusInput) != 1 || statusInput < ON_TIME || statusInput > CANCELLED) {
        printf("Invalid status input. Please enter 0, 1, or 2.\n");
        fflush(stdout); // Flush output
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer(); // Consume newline after scanf

    printf("Enter available seats: ");
    fflush(stdout); // Flush output before scanf
    // Corner case: invalid integer input for seats
    if (scanf("%d", &newFlight->availableSeats) != 1 || newFlight->availableSeats <= 0) {
        printf("Invalid number of available seats. Must be a positive integer.\n");
        fflush(stdout); // Flush output
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer(); // Consume newline after scanf

    // Initialize seat map (all seats available)
    for (int i = 0; i < (MAX_PASSENGERS_PER_FLIGHT + 7) / 8; i++) {
        newFlight->seatMap[i] = 0; // All bits to 0, indicating seats are free
    }

    (*flightCount)++;
    printf("Flight added successfully.\n");
    fflush(stdout); // Flush output
    return 1; // Success
}

/**
 * @brief Lists all the available flights.
 *
 * This function prints a detailed list of all flights, including
 * flight ID, name, origin, destination, status and available seats.
 *
 * @param flights A pointer to the array of Flight structures to list.
 * @param flightCount The current number of flights in the array.
 * @return 1 on success, 0 if no flights are available to list.
 */
int listFlights(const Flight *flights, int flightCount) {
    if (flightCount == 0) {
        printf("No flights available to list.\n");
        fflush(stdout); // Flush output
        return 0; // Failure (no flights to list)
    }

    printf("\n---- All Available Flights ----\n");
    for (int i = 0; i < flightCount; i++) {
        const Flight *f = flights + i; // Pointer arithmetic instead of array indexing
        printf("\nFlight ID      : %d\n", f->flightID);
        printf("Name           : %s\n", f->flightName);
        printf("From           : %s\n", f->origin);
        printf("To             : %s\n", f->destination);
        printf("Departure      : %02hu-%02hu-%04hu %02hu:%02hu\n",
               f->departure.day, f->departure.month, f->departure.year,
               f->departure.hour, f->departure.minute);
        printf("Arrival        : %02hu-%02hu-%04hu %02hu:%02hu\n",
               f->arrival.day, f->arrival.month, f->arrival.year,
               f->arrival.hour, f->arrival.minute);

        printf("Status         : ");
        switch (f->status) {
            case ON_TIME:
                printf("On Time\n");
                break;
            case DELAYED:
                printf("Delayed\n");
                break;
            case CANCELLED:
                printf("Cancelled\n");
                break;
            default:
                printf("Unknown\n");
                break;
        }

        printf("Seats Available: %d\n", f->availableSeats);
    }
    fflush(stdout); // Flush output
    return 1; // Success
}

/**
 * @brief Searches for a flight by its ID.
 *
 * This function searches for a flight using the flight ID and
 * returns a pointer to the relevant Flight structure if found.
 *
 * @param flights A pointer to the array of Flight structures to search within.
 * @param flightCount The current number of flights in the array.
 * @param flightID The ID of the flight to search for.
 * @return A pointer to the found Flight structure, or NULL if not found or no flights exist.
 */
Flight *searchFlight(const Flight *flights, int flightCount, int flightID) {
    if (flightCount == 0) {
        printf("No flights to search.\n");
        fflush(stdout); // Flush output
        return NULL;
    }
    for (int i = 0; i < flightCount; i++) {
        if ((flights + i)->flightID == flightID) {
            return (Flight *)(flights + i); // Return pointer to found flight
        }
    }
    printf("Flight with ID %d not found.\n", flightID);
    fflush(stdout); // Flush output
    return NULL;
}

/**
 * @brief Deletes a flight by its ID.
 *
 * This function removes a flight from the list based on the
 * provided flight ID, updating the flight count accordingly.
 *
 * @param flights A pointer to the array of Flight structures from which to delete.
 * @param flightCount A pointer to the current number of flights, which will be decremented on success.
 * @param flightID The ID of the flight to delete.
 * @return 1 on success, 0 on failure (e.g., flight not found or no flights to delete).
 */
int deleteFlight(Flight *flights, int *flightCount, int flightID) {
    if (*flightCount == 0) {
        printf("No flights to delete.\n");
        fflush(stdout); // Flush output
        return 0;
    }

    int foundIndex = -1;
    for (int i = 0; i < *flightCount; i++) {
        if ((flights + i)->flightID == flightID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Flight with ID %d not found.\n", flightID);
        fflush(stdout); // Flush output
        return 0; // Failure
    }

    // Shift elements to fill the gap (using pointer arithmetic)
    for (int i = foundIndex; i < *flightCount - 1; i++) {
        *(flights + i) = *(flights + i + 1);
    }

    (*flightCount)--;
    printf("Flight ID %d deleted successfully.\n", flightID);
    fflush(stdout); // Flush output
    return 1; // Success
}

/**
 * @brief Sorts the flights by their departure time.
 *
 * This function sorts the array of flights based on the
 * departure time, arranging them in ascending order.
 *
 * @param flights A pointer to the array of Flight structures to sort.
 * @param flightCount The current number of flights in the array.
 * @return 1 on success, 0 on failure (e.g., not enough flights to sort).
 */
int sortFlightsByDeparture(Flight *flights, int flightCount) {
    if (flightCount <= 1) {
        printf("Not enough flights to sort.\n");
        fflush(stdout); // Flush output
        return 0; // Failure
    }
    // Use qsort for efficient sorting
    qsort(flights, flightCount, sizeof(Flight), compareFlightsByDeparture);
    printf("Flights sorted by departure time.\n");
    fflush(stdout); // Flush output
    return 1; // Success
}

/**
 * @brief Saves all flight data to a specified file.
 *
 * This function writes the current state of all flights to a text file.
 * Each flight's data is written on a new line, with components separated by commas.
 * The seatMap is saved as a hexadecimal string.
 *
 * @param flights A pointer to the array of Flight structures to save.
 * @param flightCount The current number of flights in the array.
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int saveFlights(const Flight *flights, int flightCount, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        fflush(stdout); // Flush output
        return 0; // Failure
    }

    // Write the number of flights as the first line
    fprintf(fp, "%d\n", flightCount);

    for (int i = 0; i < flightCount; i++) {
        const Flight *f = flights + i; // Pointer arithmetic
        fprintf(fp, "%d,%s,%s,%s,",
                f->flightID, f->flightName, f->origin, f->destination);
        fprintf(fp, "%u %u %u %u %u,",
                f->departure.day, f->departure.month, f->departure.year,
                f->departure.hour, f->departure.minute);
        fprintf(fp, "%u %u %u %u %u,",
                f->arrival.day, f->arrival.month, f->arrival.year,
                f->arrival.hour, f->arrival.minute);
        fprintf(fp, "%d,%d,", f->status, f->availableSeats);

        // Save seatMap as hex string
        for (int j = 0; j < (MAX_PASSENGERS_PER_FLIGHT + 7) / 8; j++) {
            fprintf(fp, "%02X", f->seatMap[j]); // Print each byte as two hex characters
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Flights saved to %s successfully.\n", filename);
    fflush(stdout); // Flush output
    return 1; // Success
}

/**
 * @brief Loads flight data from a specified file.
 *
 * This function reads flight data from a text file and populates the
 * flights array. It reallocates memory as needed. It expects the first
 * line to be the flight count, followed by one flight per line.
 *
 * @param flights A pointer to a pointer to the Flight array. This allows the function
 * to update the base address of the dynamically allocated array.
 * @param flightCount A pointer to the current flight count, which will be updated
 * with the number of loaded flights.
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadFlights(Flight **flights, int *flightCount, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No flight data file found (%s). Starting with empty flight list.\n", filename);
        fflush(stdout); // Flush output
        *flightCount = 0; // Ensure count is zero if file doesn't exist
        return 0; // Not a critical failure, just means no data to load
    }

    int loadedCount = 0;
    // Read the number of flights from the first line
    if (fscanf(fp, "%d\n", &loadedCount) != 1) {
        printf("Error reading flight count from %s. File might be corrupted.\n", filename);
        fflush(stdout); // Flush output
        fclose(fp);
        return 0;
    }

    // Reallocate memory for flights if current capacity is insufficient
    if (loadedCount > MAX_FLIGHTS) {
        printf("Warning: Loaded flight count (%d) exceeds MAX_FLIGHTS (%d). Truncating.\n", loadedCount, MAX_FLIGHTS);
        fflush(stdout); // Flush output
        loadedCount = MAX_FLIGHTS;
    }

    // Free existing memory if any, and allocate for loaded data
    if (*flights != NULL) {
        free(*flights);
        *flights = NULL; // Defensive programming
    }
    *flights = (Flight *)malloc(loadedCount * sizeof(Flight));
    if (*flights == NULL) {
        printf("Error: Could not allocate memory for loading flights.\n");
        fflush(stdout); // Flush output
        fclose(fp);
        return 0;
    }

    *flightCount = 0; // Reset count before loading

    char line_buffer[512]; // Buffer to read each line
    while (*flightCount < loadedCount && fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
        Flight *f = *flights + *flightCount; // Pointer to current flight location
        char *token;
        char *rest = line_buffer;

        // flightID
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading flightID.\n"); fflush(stdout); break; }
        f->flightID = atoi(token);
        rest = NULL; // For subsequent strtok calls on the same line

        // flightName
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading flightName.\n"); fflush(stdout); break; }
        strncpy(f->flightName, token, MAX_NAME_LEN - 1);
        f->flightName[MAX_NAME_LEN - 1] = '\0';

        // origin
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading origin.\n"); fflush(stdout); break; }
        strncpy(f->origin, token, MAX_NAME_LEN - 1);
        f->origin[MAX_NAME_LEN - 1] = '\0';

        // destination
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading destination.\n"); fflush(stdout); break; }
        strncpy(f->destination, token, MAX_NAME_LEN - 1);
        f->destination[MAX_NAME_LEN - 1] = '\0';

        // departure (DD MMYYYY HH MM)
        unsigned int temp_day, temp_month, temp_year, temp_hour, temp_minute;
        token = strtok(rest, ","); // This token contains the entire date/time string
        if (token == NULL || sscanf(token, "%u %u %u %u %u",
                                    &temp_day, &temp_month, &temp_year, &temp_hour, &temp_minute) != 5) {
            printf("Error reading departure DateTime.\n"); fflush(stdout); break;
        }
        f->departure.day = temp_day; f->departure.month = temp_month; f->departure.year = temp_year;
        f->departure.hour = temp_hour; f->departure.minute = temp_minute;

        // arrival (DD MMYYYY HH MM)
        token = strtok(rest, ",");
        if (token == NULL || sscanf(token, "%u %u %u %u %u",
                                    &temp_day, &temp_month, &temp_year, &temp_hour, &temp_minute) != 5) {
            printf("Error reading arrival DateTime.\n"); fflush(stdout); break;
        }
        f->arrival.day = temp_day; f->arrival.month = temp_month; f->arrival.year = temp_year;
        f->arrival.hour = temp_hour; f->arrival.minute = temp_minute;

        // status
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading status.\n"); fflush(stdout); break; }
        f->status = (FlightStatus)atoi(token);

        // availableSeats
        token = strtok(rest, ",");
        if (token == NULL) { printf("Error reading availableSeats.\n"); fflush(stdout); break; }
        f->availableSeats = atoi(token);

        // seatMap (hex string)
        token = strtok(rest, "\n"); // Read till newline
        if (token == NULL) { printf("Error reading seatMap.\n"); fflush(stdout); break; }

        for (int j = 0; j < (MAX_PASSENGERS_PER_FLIGHT + 7) / 8; j++) {
            unsigned int byte_val;
            // Read two hex characters and convert to byte
            if (sscanf(token + (j * 2), "%2x", &byte_val) != 1) {
                printf("Error reading seatMap byte %d.\n", j);
                fflush(stdout); // Flush output
                // Handle partial read or error, maybe initialize remaining to 0
                f->seatMap[j] = 0;
            } else {
                f->seatMap[j] = (unsigned char)byte_val;
            }
        }
        (*flightCount)++;
    }

    fclose(fp);
    printf("Loaded %d flights from %s.\n", *flightCount, filename);
    fflush(stdout); // Flush output
    return 1; // Success
}