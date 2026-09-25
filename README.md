# CS3 Assignment 2

This repository contains a `TimeCode` class (Part1) along with three programs that use it:

- **`tct`** — the `TimeCode` class's test file (Part 1)
- **`nasa`** — reads NASA/SpaceX launch data from a CSV file and computes the average launch time of day (Part 2)
- **`pdt`** — an interactive paint drying timer for batches of spheres (Part 2)

## Files
| File | Purpose |
|---|---|
| `TimeCode.h` / `TimeCode.cpp` | The `TimeCode` class itself. It stores a duration as total seconds, with getters and setters, arithmetic operators, and comparison operators. |
| `TimeCodeTests.cpp` | Tests for every function in `TimeCode`. |
| `NasaLaunchAnalysis.cpp` | Uses `Space_Corrected.csv`, extracts each launch's UTC time of day, and prints the average using `TimeCode`'s own operators. |
| `Space_Corrected.csv` | Space launch dataset used by `NasaLaunchAnalysis`. |
| `PaintDryTimer.cpp` | Interactive program that tracks paint drying time for batches of spheres, based on elapsed time. |
| `Makefile` | Builds all three programs. |

## Building

From the project directory, run:
```bash
make
```

This builds all three executables — `tct`, `nasa`, and `pdt`.

To remove all built executables:
```bash
make clean
```

Debug builds are also available.


## Running

### `tct` — TimeCode Tests

```bash
./tct
```

Runs every unit test for the `TimeCode` class and prints `PASSED ALL TESTS!!!` if everything succeeds. No input required.

### `nasa` — NASA Launch Analysis

```bash
./nasa
```

Requires `Space_Corrected.csv` to be present in the same directory you run it from. Prints the total number of valid records along with the average launch time of day:

```
4198 data points.
AVERAGE: 12:7:56
```


### `pdt` — Paint Dry Timer

```bash
./pdt
```

Runs internal tests first and prints `ALL TESTS PASSED!!!`, then starts an interactive menu:

- **(A)dd** — enter a sphere's radius (in cm) to start a new batch drying. Drying time in seconds equals the sphere's surface area.
- **(V)iew Current Items** — shows every batch currently drying along with its remaining time based on elapsed time since it was added. A batch that has finished shows `DONE!` instead, and is removed from tracking.
- **(Q)uit** — exits the program.


Note: ChatGPT was used for README.md formatting