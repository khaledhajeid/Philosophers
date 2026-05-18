*This project has been created as part of the 42 curriculum by kal-haj-.*

# Philosophers

## Description
The "Philosophers" project is a simulation of the classic Dining Philosophers problem, designed to introduce the basics of threading a process and utilizing mutexes in C. 

In this simulation, a specified number of philosophers sit at a round table with a bowl of spaghetti in the middle. They alternate between eating, sleeping, and thinking. To eat, a philosopher requires two forks (one on the left, one on the right). The core challenge is to manage these shared resources (forks) among concurrent threads (philosophers) without causing a deadlock or data races, ensuring that no philosopher starves to death. 

This implementation utilizes **Dijkstra's Resource Hierarchy Algorithm** to prevent deadlocks. By assigning a consistent order in which the forks (mutexes) are requested (always locking the lower-indexed fork first), circular wait conditions are mathematically eliminated.

## Instructions

### Compilation
To compile the project, navigate to the `philo/` directory and run:
```bash
make
```

This will generate the `philo` executable using `cc` with the required flags (`-Wall -Wextra -Werror -pthread`).

### Execution
Run the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* **`number_of_philosophers`**: The number of philosophers and forks.
* **`time_to_die`** *(in ms)*: Maximum time a philosopher can go without starting a meal before starving.
* **`time_to_eat`** *(in ms)*: The time it takes for a philosopher to eat (holding two forks).
* **`time_to_sleep`** *(in ms)*: The time a philosopher spends sleeping after eating.
* **`number_of_times_each_philosopher_must_eat`** *(optional)*: The simulation stops if all philosophers have eaten at least this many times. If not provided, the simulation runs until a philosopher dies.

### Example
```bash
./philo 5 800 200 200
```

## Resources
* **Operating Systems: Three Easy Pieces (OSTEP)** - Chapters on Concurrency, Locks, and the Dining Philosophers Problem.
* **POSIX Threads Programming** - Documentation on `pthread_create`, `pthread_join`, and `pthread_mutex`.
* **Dijkstra's Resource Hierarchy Solution** - Research on breaking circular wait conditions to prevent deadlocks.

### AI Usage
AI was used during the development of this project primarily as a brainstorming and debugging partner. Specifically, it was used to:

1.  Discuss and select the most efficient algorithm to avoid deadlocks (Resource Hierarchy) instead of relying on arbitrary `usleep` delays.
2.  Refine the precision of the sleep function (`ft_msleep`) to ensure the death message is printed within the strict 10ms requirement.
3.  Analyze terminal logs to identify and resolve a "Lock Convoy" edge case by implementing a slight staggering mechanism for even-numbered threads at the start of the simulation.