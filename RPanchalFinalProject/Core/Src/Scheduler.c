/*
 * Scheduler.c
 *
 *  Created on: Jan 28, 2025
 *      Author: ReneshPanchal
 */

#include "Scheduler.h"

static uint32_t scheduledEvents = 0;

uint32_t getScheduledEvents() {
	return scheduledEvents;
}

void addScheduledEvent(uint32_t addEvent) {
	scheduledEvents |= addEvent;
}

void removeScheduledEvent(uint32_t removeEvent) {
	scheduledEvents &= ~removeEvent;
}

