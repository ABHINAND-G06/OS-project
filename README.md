# 🍳 Kitchen Resource Synchronization (Producer-Consumer Problem)

## 📌 Overview

This project simulates a real-world kitchen scenario where multiple **order takers (producers)** generate food orders and multiple **chefs (consumers)** process them.

It demonstrates the **Producer-Consumer synchronization problem** using:

* POSIX Threads (`pthread`)
* Semaphores (`sem_t`)

---

## ⚙️ System Configuration

* Producers (Order Takers): 3
* Consumers (Chefs): 4
* Buffer Size: 10 (Shared Queue)

---

## 🧠 Concepts Used

* Multithreading
* Semaphores (`empty`, `full`, `mutex`)
* Critical Section Handling
* Circular Queue
* Synchronization

---

## 🛠️ Dependencies

Make sure the following are installed:

* GCC Compiler
* POSIX Threads Library (pthread)

On Ubuntu / WSL:

```bash
sudo apt update
sudo apt install build-essential
```

---

## ▶️ Compilation & Execution

### Compile:

```bash
gcc kitchen_sync.c -o kitchen -lpthread
```

### Run:

```bash
./kitchen
```

---

## 🔄 Working Explanation

### Producer (Order Taker)

* Generates orders
* Waits if buffer is full
* Adds order to buffer safely

### Consumer (Chef)

* Waits if buffer is empty
* Removes order from buffer
* Processes it

---

## 🧪 Sample Output

```
Order Taker 3 produced order at position 0
Buffer: 1 _ _ _ _ _ _ _ _ _

Order Taker 2 produced order at position 1
Buffer: 1 1 _ _ _ _ _ _ _ _

Order Taker 1 produced order at position 2
Buffer: 1 1 1 _ _ _ _ _ _ _

Chef 4 consumed order from position 0
Buffer: _ 1 1 _ _ _ _ _ _ _
Chef 4 is preparing the order

Chef 3 consumed order from position 1
Buffer: _ _ 1 _ _ _ _ _ _ _
Chef 3 is preparing the order
```

---

## ✅ Key Features

✔ No data loss
✔ No race conditions
✔ Proper synchronization
✔ Real-time buffer tracking
✔ Circular queue implementation

---

## ⚠️ Notes

* Program runs infinitely for simulation
* Can be modified to run for fixed number of orders

---

## 🚀 Possible Improvements

* Add GUI visualization
* Add priority-based orders
* Logging system for analytics
* Graceful thread termination

---

