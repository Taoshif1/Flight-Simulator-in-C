/**
 * @file flight.h
 * @brief Header file for flight management functions.
 *
 * This file contains function prototypes for managing flight information,
 * including adding, listing, searching, deleting and sorting flights.
 * It also declares functions for saving and loading flight data to/from files.
 * It relies on the common structures defined in common.h.
 */

#ifndef FLIGHT_H
#define FLIGHT_H

#include "common.h" // Ensure common.h is included here for Flight structure and macros

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
int addFlight(Flight *flights, int *flightCount);

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
int listFlights(const Flight *flights, int flightCount);

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
Flight *searchFlight(const Flight *flights, int flightCount, int flightID);

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
int deleteFlight(Flight *flights, int *flightCount, int flightID);

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
int sortFlightsByDeparture(Flight *flights, int flightCount);

/**
 * @brief Saves all flight data to a specified file.
 *
 * This function writes the current state of all flights to a text file.
 *
 * @param flights A pointer to the array of Flight structures to save.
 * @param flightCount The current number of flights in the array.
 * @param filename The name of the file to save to.
 * @return 1 on success, 0 on failure (e.g., file cannot be opened).
 */
int saveFlights(const Flight *flights, int flightCount, const char *filename);

/**
 * @brief Loads flight data from a specified file.
 *
 * This function reads flight data from a text file and populates the
 * flights array. It reallocates memory as needed.
 *
 * @param flights A pointer to a pointer to the Flight array. This allows the function
 * to update the base address of the dynamically allocated array.
 * @param flightCount A pointer to the current flight count, which will be updated
 * with the number of loaded flights.
 * @param filename The name of the file to load from.
 * @return 1 on success, 0 on failure (e.g., file not found, read error, memory allocation error).
 */
int loadFlights(Flight **flights, int *flightCount, const char *filename);


#endif // FLIGHT_H