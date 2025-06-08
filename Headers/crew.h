/**
 * @file crew.h
 * @brief Header file for crew management functions.
 *
 * This file contains function prototypes related to assigning crew members to flights.
 */

#ifndef CREW_H
#define CREW_H

/**
 * @brief Assigns a crew member to a specific flight.
 *
 * This function prompts the user for the crew member's name and the flight ID
 * they are to be assigned to. In a more complex system, this would involve
 * checking flight existence and crew availability.
 *
 * @return 1 on success, 0 on failure (e.g., invalid input).
 */
int assignCrew();

#endif // CREW_H