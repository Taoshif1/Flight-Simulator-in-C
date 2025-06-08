/**
 * @file common.h
 * @brief Common definitions, macros, and structures used throughout the Flight Management System.
 *
 * This file centralizes global constants, enumerations, and shared data structures
 * like DateTime and Flight, ensuring consistency across different modules.
 */

#ifndef COMMON_H
#define COMMON_H

#include <string.h> // Required for strtok in GET_STRING macro

/**
 * @def MAX_FLIGHTS
 * @brief Maximum number of flights the system can manage.
 */
#define MAX_FLIGHTS 100

/**
 * @def MAX_NAME_LEN
 * @brief Maximum length for names (flight, origin, destination, passenger, crew, payment method).
 */
#define MAX_NAME_LEN 100

/**
 * @def MAX_PASSENGERS_PER_FLIGHT
 * @brief Maximum number of passengers a single flight can accommodate for seat mapping.
 */
#define MAX_PASSENGERS_PER_FLIGHT 250 // Example: Max passengers per flight for bitfield seats

/**
 * @enum FlightStatus
 * @brief Represents the current status of a flight.
 */
typedef enum {
    ON_TIME,    /**< Flight is on schedule. */
    DELAYED,    /**< Flight is delayed. */
    CANCELLED   /**< Flight has been cancelled. */
} FlightStatus;

/**
 * @struct DateTime
 * @brief Represents a date and time using bit-fields for memory efficiency.
 *
 * Members are packed into a smaller memory footprint.
 */
typedef struct {
    unsigned int day : 5;    /**< Day of the month (1-31). */
    unsigned int month : 4;  /**< Month of the year (1-12). */
    unsigned int year : 12;  /**< Year (e.g., 0-4095, sufficient for near future). */
    unsigned int hour : 5;   /**< Hour of the day (0-23). */
    unsigned int minute : 6; /**< Minute of the hour (0-59). */
} DateTime;

/**
 * @struct Flight
 * @brief Represents a single flight with its details.
 */
typedef struct {
    int flightID;                           /**< Unique identifier for the flight. */
    char flightName[MAX_NAME_LEN];          /**< Name or code of the flight (e.g., "Airbus 320"). */
    char origin[MAX_NAME_LEN];              /**< Departure airport. */
    char destination[MAX_NAME_LEN];         /**< Arrival airport. */
    DateTime departure;                     /**< Scheduled departure date and time. */
    DateTime arrival;                       /**< Scheduled arrival date and time. */
    FlightStatus status;                    /**< Current status of the flight (ON_TIME, DELAYED, CANCELLED). */
    int availableSeats;                     /**< Number of seats currently available on the flight. */
    /**
     * @var seatMap
     * @brief Bit array representing seat availability.
     * Each bit corresponds to a seat (0 = free, 1 = booked).
     * Size calculated to hold MAX_PASSENGERS_PER_FLIGHT bits.
     */
    unsigned char seatMap[(MAX_PASSENGERS_PER_FLIGHT + 7) / 8];
} Flight;

/**
 * @def GET_STRING(buffer, size)
 * @brief Macro for safe string input using fgets and strtok.
 *
 * Reads a line of text from stdin into a buffer, ensuring buffer overflow
 * is prevented and the trailing newline character is removed.
 *
 * @param buffer The character array to store the input string.
 * @param size The maximum size of the buffer.
 */
#define GET_STRING(buffer, size) do { \
    fgets(buffer, size, stdin);       \
    strtok(buffer, "\n");             \
} while (0)

#endif // COMMON_H