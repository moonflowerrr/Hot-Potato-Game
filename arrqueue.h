//
//  arrqueue.h
//  CSS342A Assignment4
//
//  Created by Jayda  on 11/15/25.
//

#ifndef _ARRQUEUE_H_
#define _ARRQUEUE_H_

#include <iostream>
#include <stdexcept>

using namespace std;

namespace aqueue { // Use a different namespace to avoid conflicts
    template <typename T>
    class ArrQueue {
    private:
        T* data;
        int capacity;
        int frontIndex; // Index of the first element
        int rearIndex;  // Index where the next element will be inserted
        int currentSize;

        // Helper function to increase array size when full
        void resize();

    public:
        // Constructor, Destructor
        ArrQueue(int initialCapacity = 10);
        ~ArrQueue();

        // Required Queue ADT methods
        int size() const;
        bool empty() const;
        T front() const;
        void enqueue(const T& e);
        T dequeue();
        void printQueue() const;
    };

    template <typename T>
    ArrQueue<T>::ArrQueue(int initialCapacity)
        : capacity(initialCapacity), frontIndex(0), rearIndex(0), currentSize(0) {
        // Allocate the dynamic array
        data = new T[capacity];
    }

    template <typename T>
    ArrQueue<T>::~ArrQueue() {
        delete[] data;
    }

    template <typename T>
    int ArrQueue<T>::size() const {
        return currentSize;
    }

    template <typename T>
    bool ArrQueue<T>::empty() const {
        return currentSize == 0;
    }

    template <typename T>
    T ArrQueue<T>::front() const {
        if (empty()) {
            throw std::out_of_range("ArrQueue is empty. Cannot get front.");
        }
        // The front element is always at frontIndex
        return data[frontIndex];
    }

    template <typename T>
    void ArrQueue<T>::resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        
        // Copy elements from the old array to the new one, starting from the frontIndex.
        for (int i = 0; i < currentSize; ++i) {
            
            newData[i] = data[(frontIndex + i) % capacity];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;           // Reset front to the beginning of the new array
        rearIndex = currentSize;  // Set rear to the end of the data in the new array
    }

    template <typename T>
    void ArrQueue<T>::enqueue(const T& e) {
        // 1. Check if full and resize if necessary
        if (currentSize == capacity) {
            resize();
        }
        
        // 2. Insert at the current rear position
        data[rearIndex] = e;
        
        // 3. Move rear index circularly
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }

    template <typename T>
    T ArrQueue<T>::dequeue() {
        if (empty()) {
            throw std::out_of_range("ArrQueue is empty. Cannot dequeue.");
        }
        
        // 1. Store the value to be returned (at the current front)
        T result = data[frontIndex];
        
        // 2. Move front index circularly
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
        
        // 3. Return the element
        return result;
    }

    template <typename T>
    void ArrQueue<T>::printQueue() const {
        if (empty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        // Iterate from frontIndex to rearIndex, handling the wrap-around
        for (int i = 0; i < currentSize; ++i) {
            cout << data[(frontIndex + i) % capacity] << " ";
        }
        cout << endl;
    }
} // end of namespace aqueue
#endif

