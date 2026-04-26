#include <cstdint>
#include <iostream>
#include "LinkedList.h"
using namespace std;

struct Event {
    uint32_t id;
    char description[32];
    uint16_t year;
    uint8_t impact;
};

LinkedList<Event> eventList;

void recordAncientEvent(Event e) {
    eventList.addFirst(e);
}

void recordRecentEvent(Event e) {
    eventList.addLast(e);
}

void insertEventBetween(int leftId, int rightId, Event e) {
    Node<Event>* selected = eventList.pfirst;
    while (selected && selected->info.id != leftId) selected = selected->next;
    if (!selected || !selected->next || selected->next->info.id != rightId) return;

    eventList.addLast(e);
    Node<Event>* inserted = eventList.plast;
    inserted->prev->next = nullptr;
    inserted->next = selected->next;
    inserted->prev = selected;

    selected->next->prev = inserted;
    selected->next = inserted;
}

void eraseCorruptedEvent(int id) {
    Node<Event>* selected = eventList.pfirst;
    while (selected && selected->info.id != id) selected = selected->next;
    if (!selected) return;

    if (selected->prev) selected->prev->next = selected->next;
    if (selected->next) selected->next->prev = selected->prev;
    if (selected == eventList.plast) eventList.plast = selected->prev;
    if (selected == eventList.pfirst) eventList.pfirst = selected->next;
    delete selected;
}

void relocateEvent(int idToMove, int newNeighborId, bool before) {
    Node<Event>* selected = nullptr, *neighbor = nullptr;
    for (Node<Event>* iter = eventList.pfirst; iter; iter = iter->next) {
        int idReached = iter->info.id;
        if (idReached == newNeighborId) neighbor = iter;
        if (idReached == idToMove) selected = iter;
    }
    if (!selected || !neighbor) return;

    if (selected->prev) selected->prev->next = selected->next;
    if (selected->next) selected->next->prev = selected->prev;

    if (before) {
        selected->next = neighbor;
        selected->prev = neighbor->prev;
        if (neighbor->prev) neighbor->prev->next = selected;
        neighbor->prev = selected;
    } else {
        selected->prev = neighbor;
        selected->next = neighbor->next;
        if (neighbor->next) neighbor->next->prev = selected;
        neighbor->next = selected;
    }
}

uint32_t computeTotalImpact() {
    uint32_t totalImpact = 0;
    for (Node<Event>* iter = eventList.pfirst; iter; iter = iter->next)
        totalImpact += iter->info.impact;

    return totalImpact;
}

void displayChronology() {
    Node<Event>* selected = eventList.pfirst;
    if (!selected) return;

    do {
        Event& info = selected->info;
        printf("[%i | %s | %i | %i]\n", info.id, info.description, info.year, info.impact);

        selected = selected->next;
    } while (selected);
    printf("\n");
}

void stabilizeTimeline(int threshold) {
    for (Node<Event>* iter = eventList.pfirst; iter; iter = iter->next) {
        uint8_t impact = iter->info.impact;
        if (impact > threshold && iter != eventList.pfirst) {
            uint8_t previousImpact = iter->prev->info.impact;
            if (impact > previousImpact || (impact == previousImpact && iter->info.year < iter->prev->info.year)) {
                Node<Event>* prev = iter->prev;
                if (prev->prev) prev->prev->next = iter;
                if (iter->next) iter->next->prev = prev;
                prev->next = iter->next;
                iter->prev = prev->prev;
                prev->prev = iter;
                iter->next = prev;
                if (eventList.pfirst == prev) eventList.pfirst = iter;
            }
        }
    }
}

int main() {
    recordRecentEvent({1, "Quantum Energy", 2300, 90});
    recordRecentEvent({2, "Mars Colonization", 2350, 70});
    recordAncientEvent({0, "First Contact", 2200, 100});
    printf("Initial timeline:\n");
    displayChronology();
    insertEventBetween(1, 2, {3, "Temporal crisis", 2400, 95});
    printf("After insert:\n");
    displayChronology();
    relocateEvent(3, 0, false);
    printf("After relocate:\n");
    displayChronology();
    eraseCorruptedEvent(1);
    printf("After removal:\n");
    displayChronology();
    printf("Total impact: %i\n\n", computeTotalImpact());
    stabilizeTimeline(80);
    printf("After stabilization:\n");
    displayChronology();
}