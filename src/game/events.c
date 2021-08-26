////////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
// 
// Copyright (c) 2021 Tarek Sherif
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////////

#include "events.h"

static bool enabled(EventsEvent* event) {
    return event->start != 0;
}

static void disable(EventsEvent* event) {
    event->start = 0;
}

void events_start(uint32_t currentTick, EventsEvent* event, uint32_t delay) {
    event->start = currentTick + 1 + delay;
}

void events_transition(uint32_t currentTick, EventsEvent* endEvent, EventsEvent* startEvent, uint32_t delay) {
    disable(endEvent);
    events_start(currentTick, startEvent, delay);
}

bool events_entering(uint32_t currentTick, EventsEvent* event) {
    return enabled(event) && event->start == currentTick;
} 

bool events_during(uint32_t currentTick, EventsEvent* event) {
    return enabled(event) && currentTick >= event->start && currentTick <= event->start + event->duration;
}

bool events_exiting(uint32_t currentTick, EventsEvent* event) {
    return enabled(event) && currentTick == event->start + event->duration;
}