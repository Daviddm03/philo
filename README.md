# Philosophers

An implementation of the Dining Philosophers problem using threads and mutexes.

Developed as part of the 42 curriculum, the project explores concurrency, synchronization, shared resources, and race conditions.

## About

A group of philosophers sits around a table with one fork between each philosopher.

Each philosopher repeatedly needs to:

```text
eat → sleep → think
```

To eat, a philosopher must acquire two forks.

Because the philosophers run concurrently, access to shared resources must be synchronized correctly to prevent race conditions and avoid invalid states.

Each philosopher is represented by a thread and the shared forks are protected using mutexes.

## Getting Started

### Requirements

- GCC or Clang
- Make
- POSIX threads
- A Unix-like environment

Clone the repository:

```bash
git clone git@github.com:Daviddm03/philo.git
cd philo
cd "philo (copy)"
```

Compile:

```bash
make
```

## Usage

The program accepts:

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Times are provided in milliseconds.

Example:

```bash
./philo 5 800 200 200
```

With an optional meal limit:

```bash
./philo 5 800 200 200 7
```

The simulation stops when a philosopher dies or when the required number of meals has been completed.

Clean or rebuild:

```bash
make clean
make fclean
make re
```

## What I Learned

This project was mainly about synchronization.

Working with multiple threads accessing the same resources made race conditions much more concrete than they had been in previous projects.

It also required careful handling of mutexes, timing, thread lifecycle, and shared state so that the simulation remained consistent while several philosophers were running at the same time.

## Tech

C · POSIX Threads · Mutexes · Concurrency · Makefile
