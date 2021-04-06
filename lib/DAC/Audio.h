/**
 * Audio.h
 * Devices: LM4F120; TM4C123
 * Description: Middle level drivers to produce sounds in tandem with duration.
 * Authors: Matthew Yu.
 * Last Modified: 03/10/21
 **/
#pragma once

/** General imports. */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/** Device specific imports. */
#include "Sound.h"

/** TODO: convert into frequency instead of period. */
#define C1	33
#define Cs1	35
#define Df1	35
#define D1	37
#define Ds1	39
#define Ef1	39
#define E1	41
#define F1	44
#define Fs1	46
#define Gf1	46
#define G1	49
#define Gs1	52
#define Af1	52
#define A1	55
#define As1	58
#define Bf1	58
#define B1	62

#define C2	65
#define Cs2	69
#define Df2	69
#define D2	73
#define Ds2	78
#define Ef2	78
#define E2	82
#define F2	87
#define Fs2	93
#define Gf2	93
#define G2	98
#define Gs2	104
#define Af2	104
#define A2	110
#define As2	117
#define Bf2	117
#define B2	123

#define C3	131
#define Cs3	139
#define Df3	139
#define D3	147
#define Ds3	156
#define Ef3	156
#define E3	165
#define F3	175
#define Fs3	185
#define Gf3	185
#define G3	196
#define Gs3	208
#define Af3	208
#define A3	220
#define As3	233
#define Bf3	233
#define B3	245

#define C4	262 
#define Cs4	277
#define Df4	277
#define D4	294
#define Ds4	311
#define Ef4	311
#define E4	330
#define F4	349
#define Fs4	370
#define Gf4	370
#define G4	392
#define Gs4	415
#define Af4	415
#define A4	440
#define As4	466
#define Bf4	466
#define B4	494

#define C5	523




enum NoteLength { 
	REST, 
	sixteenth, 
	eighth, 
	quarter, 
	half, 
	whole
};

typedef struct Note {
	uint32_t frequency;
	uint16_t waveform;
	enum NoteLength length;
} Note_t;


/* .c file */
struct AudioStorage {
	// array of notes with array of size SIZE
	// remaining time (say sixteenth =1, eighth =2, quarter =4, and so on)
	// track ID
};

static struct AudioStorage audioTracks[] = {
	{ [], ID = 0 },
	{ [], ID = 1 },
	{ [], ID = 2 }
};



/**
 * global variables corresponding to a set of tracks
 * SIZE = 20
 * track0[SIZE]
 * track1[SIZE]
 * track2[SIZE]
 * track3[SIZE]
 * 
 * void InitAudio(TimerConfig_t tConfig, minPeriod) { setup timer, give it a handler }
 * void timerHandler(void) {
 *	timer activates every 16th note, which is the length of minPeriod
 *	when it activates, take the first note in each of the queues, and check how long they have left
 *		if remaining time in timer iterations is 0
 *			pop from queue, play next note in queue with playSound, set remaining time to time of the note
 *		decrement remaining time of all notes
 * }
 * void playNote(int id, Note_t t) { add note t to queue with ID - only if there is space }
 * bool isQueueFull(int id) { check if queue with ID cannot fit any more notes }
 * bool isQueueEmpty(int id) { check if queue with ID has notes left in it }
 * void clearQueue(int id) { for specific queue ID, pop notes for that queue and call stopSound for that ID }
 * void clearQueues(void) { for each queue ID, pop all notes and call stopSound for ID }
 */

/** 
 * playNote
 */
void playNote(int id, Note_t t);

/**
 * trackqueue1 note1 note2 note3
 * trackqueue2 note4
 * trackqueue3 note5
 */
bool isQueueFull(Note_t track[]);
bool isQueueEmpty(Note_t track[]);

