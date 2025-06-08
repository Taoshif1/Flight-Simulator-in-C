/**
 * @file ticket.h
 * @brief Header file for ticket management functions.
 *
 * This file contains function prototypes and structures for handling
 * ticket booking, cancellation, viewing, and seat management. It also
 * declares functions for saving and loading ticket data.
 */

#ifndef TICKET_H
#define TICKET_H

#include "common.h" // Ensure common.h is included here for MAX_NAME_LEN

/**
 * @struct Ticket
 * @brief Represents a single flight ticket.
 */
typedef struct {
    int ticketID;                   /**< Unique identifier for the ticket. */
    char passengerName[MAX_NAME_LEN]; /**< Name of the passenger holding this ticket. */
    int flightID;                   /**< ID of the flight this ticket is for. */
    int seatNo;                     /**< Seat number assigned on the flight. */
} Ticket;

/**
 * @var globalTickets
 * @brief Pointer to the dynamically allocated array of Ticket structures.
 */
extern Ticket *globalTickets;
/**
 * @var globalTicketCount
 * @brief Current number of tickets stored in the globalTickets array.
 */
extern int globalTicketCount;
/**
 * @var globalTicketCapacity
 * @brief Maximum capacity of the globalTickets array before reallocation is needed.
 */
extern int globalTicketCapacity;

/**
 * @def INITIAL_TICKET_CAPACITY
 * @brief Initial number of ticket slots allocated when the system starts.
 */
#define INITIAL_TICKET_CAPACITY 10

/**
 * @brief Initializes the global ticket array by allocating initial memory.
 *
 * This function must be called once at the start of the program to set up
 * the ticket storage.
 *
 * @return 1 on success, 0 on failure (e.g., memory allocation failed).
 */
int initializeTickets();

/**
 * @brief Books a new ticket for a passenger on a specific flight and seat.
 *
 * This function prompts for passenger name, flight ID, and seat number.
 * It assigns a unique ticket ID and dynamically reallocates memory if needed.
 *
 * @return 1 on success, 0 on failure (e.g., ticket limit reached, invalid input, memory reallocation failed).
 */
int bookTicket();

/**
 * @brief Cancels an existing ticket based on its ticket ID.
 *
 * This function prompts for a ticket ID, searches for the ticket, and removes
 * it from the list by shifting subsequent elements.
 *
 * @return 1 on success, 0 on failure (e.g., no tickets, ticket not found).
 */
int cancelTicket();

/**
 * @brief Displays a list of all booked tickets.
 *
 * This function prints the details of all tickets currently in the system.
 *
 * @return 1 on success, 0 on failure (e.g., no tickets to display).
 */
int showAllTickets();

/**
 * @brief Provides basic seat management for a given flight.
 *
 * This function prompts for a flight ID and lists all seats currently booked
 * for that flight, along with the passenger's name.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int seatManagement();

/**
 * @brief Frees the dynamically allocated memory used by the global ticket array.
 *
 * This function should be called before the program exits to prevent memory leaks.
 */
void cleanupTickets();

/**
 * @brief Saves all ticket data to a specified file.
 *
 * This function writes the current state of all tickets to a text file.
 *
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int saveTickets(const char *filename);

/**
 * @brief Loads ticket data from a specified file.
 *
 * This function reads ticket data from a text file and populates the
 * global ticket array. It reallocates memory as needed.
 *
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadTickets(const char *filename);

#endif // TICKET_H