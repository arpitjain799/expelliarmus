#ifndef EVENTS_H 
#define EVENTS_H

#include <stdlib.h>
#include <stdint.h>

// Data types used for the event data structure fields.
typedef int64_t timestamp_t;  
typedef int16_t address_t; 
typedef uint8_t polarity_t; 

/** Structure of an event in a recording.
 *
 *  @field  t   Timestamp.
 *  @field  x   X address of the pixel.
 *  @field  y   Y address of the pixel.
 *  @field  p   Polarity of the event.
 */
typedef struct event_s {
	timestamp_t t; 
	address_t x; 
	address_t y; 
	polarity_t p; 
} event_t; 

/** Structure that holds additional information about the event stream.
 *
 *  @field  dim             The number of events in the recording.
 *  @field  is_chunk        A flag to indicate that the file is being read in
 *                          chunks and not all at once.
 *  @field  time_window     The time window duration expressed in milliseconds
 *                          when the file is read in recordings of fixed 
 *                          duration.
 *  @field  is_time_window  Flag to indicate that the file is being read in 
 *                          time windows and not all at once to an array.
 *  @field  start_byte      Number of bytes with respect to file beginning to
 *                          be used with fseek() to reopen the file from the 
 *                          point where it was left off.
 *  @field  finished        Flag to indicate that the entire file has been read.
 */
typedef struct {
	size_t dim;
	uint8_t is_chunk; 
	size_t time_window; 
	uint8_t is_time_window; 
	size_t start_byte;
	uint8_t finished; 
} event_cargo_t; 

// Macro to check that the event stream is monotonic in the timestamps.
#define CHECK_TIMESTAMP_MONOTONICITY(t, prev_t){\
	if ((t) < (prev_t))\
		fprintf(stderr, "WARNING: the timestamps are not monotonic.\n");\
        fprintf(stderr, "Current: %ld; previous:%ld.\n", t, prev_t);\
}	

#endif
