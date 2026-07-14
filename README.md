# philosophers-42 🍝

## What is philosophers ⁉️

The **philosophers** project at 42 is a concurrency and synchronization challenge based on the classic **Dining Philosophers Problem**. The goal is to simulate philosophers sitting around a table, alternating between eating, sleeping, and thinking while sharing a limited number of forks. This project introduces important concepts such as multithreading, mutexes, synchronization, race conditions, and resource management.

---

## Key points 🔑

### Multithreading

Each philosopher is represented by an independent thread running concurrently, performing its own cycle of eating, sleeping, and thinking.

### Mutex Synchronization

Forks are protected using **mutexes**, ensuring that only one philosopher can hold a fork at a time. This prevents data races and guarantees thread-safe execution.

### Dining Philosophers Problem

The implementation must avoid common concurrency issues such as:

- Deadlocks
- Race conditions
- Starvation

while ensuring that philosophers can continue their routine correctly.

### Time Management

The simulation accurately tracks:

- Time to die
- Time to eat
- Time to sleep

A philosopher dies if they fail to eat before the configured time limit.

### Monitoring

A dedicated monitoring routine continuously checks the philosophers' state to determine if one has died or if every philosopher has eaten the required number of meals (when specified).

### Input and Validation

The program validates all input arguments, ensuring:

- Positive integer values only
- Correct number of arguments
- Valid simulation parameters

---

## Conclusion ✅

The **philosophers** project is an excellent introduction to concurrent programming. It teaches synchronization techniques, mutex handling, thread management, timing accuracy, and how to solve resource-sharing problems safely and efficiently.

---

# How to run

### 1 - Clone

```bash
git clone https://github.com/Daviddm03/philosophers-42.git
```

### 2 - Navigate to the directory

```bash
cd philosophers-42
```

### 3 - Compile the program

```bash
make
```

### 4 - Run the simulation

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```

or

```bash
./philo 5 800 200 200 7
```

---

## Example Output

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```
