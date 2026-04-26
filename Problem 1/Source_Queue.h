#include <stdexcept>


#ifndef IMPLEMENTATION_SOURCE_QUEUE_H
#define IMPLEMENTATION_SOURCE_QUEUE_H


#define NMAX 100
template<typename T> class Queue {
private:
    T queueArray[NMAX];
    int head, tail;
public:
    void enqueue(T x) {
        if (tail >= NMAX) {
            std::cerr << "Queue is full!" << std::endl;
            return;
        }
        queueArray[tail] = x;
        tail++;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty!" << std::endl;
            return T();
        }
        T x = queueArray[head];
        head++;
        return x;
    }

    T peek() {
        if (isEmpty()) {
            std::cerr << "Error 103 - The queue is empty!" << std::endl;
            return T();
        }
        return queueArray[head];
    }

    bool isEmpty() {
        return (head == tail);
    }

    Queue() {
        head = tail = 0; // the queue is empty in the beginning
    }
};





#endif //IMPLEMENTATION_SOURCE_QUEUE_H