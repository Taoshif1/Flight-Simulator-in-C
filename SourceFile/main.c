/**
 * @file main.c
 * @brief Entry point for the Flight Management System.
 *
 * This file contains the main application loop, presenting a menu
 * to the user for various flight, passenger, crew, ticket, and payment
 * management operations. It initializes and cleans up system resources,
 * including loading data at startup and saving data on exit.
 */

#include "common.h" // MUST BE FIRST for shared macros/definitions
#include <stdio.h>
#include <stdlib.h> // For exit

#include "flight.h"
#include "passenger.h"
#include "crew.h"
#include "ticket.h"
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
 * @brief Main function of the Flight Management System.
 *
 * Initializes the system, loads data from files, presents a menu-driven
 * interface to the user, and calls appropriate functions based on user input.
 * Handles system cleanup and saves data to files upon exit.
 *
 * @return 0 on successful program termination, 1 on initialization failure.
 */
int main() {
    // Dynamically allocated array for flights
    Flight *flights = NULL; // Initialize to NULL for loadFlights
    int flightCount = 0;
    int choice;

    // Initialize passenger and ticket systems (allocates initial memory)
    if (!initializePassengers() || !initializeTickets()) {
        printf("System initialization failed. Exiting.\n");
        // No need to free flights here, as it's still NULL if malloc hasn't happened.
        // cleanupPassengers and cleanupTickets will handle their own NULL checks.
        cleanupPassengers();
        cleanupTickets();
        return 1;
    }

    // Load existing data from files
    loadFlights(&flights, &flightCount, "flights.txt");
    loadPassengers("passengers.txt");
    loadTickets("tickets.txt");

    while (1) {
        printf("\n========== Flight Management System ==========\n");
        printf("1. Add New Flight\n");
        printf("2. List All Flights\n");
        printf("3. Add/Remove/View Passenger\n");
        printf("4. Assign Crew\n");
        printf("5. Ticket Management\n");
        printf("6. Payment Handling\n");
        printf("7. Sort Flights by Departure Time\n");
        printf("8. Delete Flight\n");
        printf("9. Search Flight\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        // Corner case: invalid input for choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer(); // Clear input buffer
            continue; // Go back to menu
        }
        clearInputBuffer(); // Consume newline after scanf

        switch (choice) {
            case 1:
                addFlight(flights, &flightCount);
                break;

            case 2:
                listFlights(flights, flightCount);
                break;

            case 3: {
                int subChoice;
                printf("\n--- Passenger Management ---\n");
                printf("1. Add Passenger\n");
                printf("2. Remove Passenger\n");
                printf("3. View Passengers\n");
                printf("Enter your choice: ");
                // Corner case: invalid input for subChoice
                if (scanf("%d", &subChoice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer(); // Consume newline after scanf

                switch (subChoice) {
                    case 1: addPassenger(); break;
                    case 2: removePassenger(); break;
                    case 3: viewPassengers(); break;
                    default: printf("Invalid passenger option!\n"); break;
                }
                break;
            }

            case 4:
                assignCrew();
                break;

            case 5: {
                int subChoice;
                printf("\n--- Ticket Management ---\n");
                printf("1. Book Ticket\n");
                printf("2. Cancel Ticket\n");
                printf("3. Show All Tickets\n");
                printf("4. Seat Management\n");
                printf("Enter your choice: ");
                // Corner case: invalid input for subChoice
                if (scanf("%d", &subChoice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer(); // Consume newline after scanf

                switch (subChoice) {
                    case 1: bookTicket(); break;
                    case 2: cancelTicket(); break;
                    case 3: showAllTickets(); break;
                    case 4: seatManagement(); break;
                    default: printf("Invalid ticket option!\n"); break;
                }
                break;
            }

            case 6:
                handlePayment();
                break;

            case 7: { // Case for sorting flights
                sortFlightsByDeparture(flights, flightCount);
                break;
            }
            case 8: { // Case for deleting flights
                int flightIDToDelete;
                printf("Enter Flight ID to delete: ");
                if (scanf("%d", &flightIDToDelete) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer(); // Consume newline after scanf

                deleteFlight(flights, &flightCount, flightIDToDelete);
                break;
            }
            case 9: { // Case for searching flights
                int flightIDToSearch;
                printf("Enter Flight ID to search: ");
                if (scanf("%d", &flightIDToSearch) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer(); // Consume newline after scanf

                Flight *foundFlight = searchFlight(flights, flightCount, flightIDToSearch);
                if (foundFlight != NULL) {
                    printf("\n--- Flight Found ---\n");
                    printf("Flight ID      : %d\n", foundFlight->flightID);
                    printf("Name           : %s\n", foundFlight->flightName);
                    printf("From           : %s\n", foundFlight->origin);
                    printf("To             : %s\n", foundFlight->destination);
                    printf("Departure      : %02hu-%02hu-%04hu %02hu:%02hu\n",
                           foundFlight->departure.day, foundFlight->departure.month, foundFlight->departure.year,
                           foundFlight->departure.hour, foundFlight->departure.minute);
                    printf("Arrival        : %02hu-%02hu-%04hu %02hu:%02hu\n",
                           foundFlight->arrival.day, foundFlight->arrival.month, foundFlight->arrival.year,
                           foundFlight->arrival.hour, foundFlight->arrival.minute);
                    printf("Status         : ");
                    switch (foundFlight->status) {
                        case ON_TIME: printf("On Time\n"); break;
                        case DELAYED: printf("Delayed\n"); break;
                        case CANCELLED: printf("Cancelled\n"); break;
                        default: printf("Unknown\n"); break;
                    }
                    printf("Seats Available: %d\n", foundFlight->availableSeats);
                    printf("--------------------\n");
                }
                break;
            }
            case 0:
                printf("Exiting system. Goodbye!\n");
                // Save data before exiting
                saveFlights(flights, flightCount, "flights.txt");
                savePassengers("passengers.txt");
                saveTickets("tickets.txt");

                // Clean up dynamically allocated memory
                free(flights); // Free flights array
                cleanupPassengers();
                cleanupTickets();
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}