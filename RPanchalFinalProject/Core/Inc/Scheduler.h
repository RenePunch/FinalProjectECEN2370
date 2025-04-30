/*
 * Scheduler.h
 *
 *  Created on: Jan 28, 2025
 *      Author: ReneshPanchal
 */
#include <stdint.h>
#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#define APP_DELAY_FLAG_EVENT (1 << 1)

#define DEVICE_ID_AND_TEMP_EVENT ( 1 << 2)

uint32_t getScheduledEvents();

void addScheduledEvent(uint32_t addEvent);

void removeScheduledEvent(uint32_t removeEvent);



#endif /* SCHEDULER_H_ */
