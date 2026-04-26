# Big Homework 1

## Problem 1

### Used headers

- ##### Source_Queue.h

### Methods
```cpp
void add_task(Queue<Task> &processed,Task t); // adds a task to the queue
bool pop_task(Queue<Task> &processed, Task &t); // removes and returns a task through the t argument, if it fails to do so, it will return false
void print_task(Task t); // prints a task to the console
bool check_duplicates(Queue<Task> waiting, Queue<Task> processed, int id); // checks for already existing task ids
void display_tasks(Queue<Task> tasks); // prints all tasks
void add_option(Queue<Task> &waiting,Queue<Task> &processed); // adds a task to the waiting queue
void next_task(Queue<Task> &waiting, Queue<Task> &processed) // processes the next task
void undo_task(Queue<Task> &waiting, Queue<Task> &processed,int &undo_count) // undoes a task and increases the counter
void display_waiting(Queue<Task> &waiting); // displays tasks awaiting processing
void display_history(Queue<Task> &processed); // displays processed tasks
void process_k(Queue<Task> &waiting, Queue<Task> &processed); // processes the next K tasks
void search_task(Queue<Task> &waiting, Queue<Task> &processed); // searches for a task id
void display_stats(Queue<Task> waiting, Queue<Task> processed, int undo_count); // displays the stats which include the current status, number of undo operations, and the number of the waiting and processed tasks 
```
### Usage

```
Interactive Task Flow Manager
-----------------------------
-          Options          -
-1.Add Task                 -
-2.Process Next Task        -
-3.Undo Last Proc. Task     -
-4.Display Waiting Task     -
-5.Display Proc. History    -
-6.Process Next k tasks     -
-7.Search Task by ID        -
-8.Display Stats            -
-0.Exit                     -
-                           -
- Pick Option:              -
-----------------------------
```
The user can pick an option from the list printed in the console

## Problem 2

### Used headers
- ##### LinkedList.h

### Methods
```cpp
void recordAncientEvent(Event e); // appends an event to the start of the timeline
void recordRecentEvent(Event e); // appends an event to the end of the timeline
void insertEventBetween(int leftId, int rightId, Event e); // appends an event between 2 events if they exist and are consecutive in the timeline
void eraseCorruptedEvent(int id); // erases the event with the specified id from the timeline
void relocateEvent(int idToMove, int newNeighborId, bool before); // moves an event before or after the specified event in the timeline
uint32_t computeTotalImpact(); // computes and returns the total impact of the events in the timeline
void displayChronology(); // prints the timeline to the console
void stabilizeTimeline(int threshold); // moves important events to the beginning of the timeline based on the threshold provided
```

### Usage
```cpp
// Example
recordRecentEvent({1, "Quantum Energy", 2300, 90});
recordRecentEvent({2, "Mars Colonization", 2350, 70});
recordAncientEvent({0, "First Contact", 2200, 100});

printf("Initial timeline:\n");
displayChronology();
/*
[0 | First Contact | 2200 | 100]
[1 | Quantum Energy | 2300 | 90]
[2 | Mars Colonization | 2350 | 70]
*/

insertEventBetween(1, 2, {3, "Temporal crisis", 2400, 95}); // will insert the new event between 1 and 2

printf("After insert:\n");
displayChronology();
/*
[0 | First Contact | 2200 | 100]
[1 | Quantum Energy | 2300 | 90]
[3 | Temporal crisis | 2400 | 95]
[2 | Mars Colonization | 2350 | 70]
*/
```