# Page Replacement in C++
This repository contains implementation of page replacement algorithms (FIFO, Optimal, LFU) in C++, executable in ubuntu based systems.

## Getting Started

The following page replacement algorithms have been implemented in the code.
1. FIFO algorithm
2. Optimal algorithm
3. Least Frequently Used (LFU) Algorithm

In the input file `input.txt` you will find the reference string, each page on a different line. When user starts your application he/she will be asked to choose which algorithm to use. Then the code will ask how many frames to use (between 3 to 6). Based upon the selected choice, the code will execute the algorithm over the reference string and store the output in `output_[Algorithm-Name].txt` file.  An example input reference string `input.txt` and it's relevant output files (with 3 frames to use), is attached with the repository. Following is an example run:

```
Size of reference string is: 20

Please enter how many frames to use (range: 3-6): 3

--- Please choose which algorithm to use ---
1. FIFO Rule
2. Optimal Rule
3. LFU Rule

1

___Applying Page Replacement Algorithm___
7   :   | 7 | | - | | - | 
0   :   | 7 | | 0 | | - | 
1   :   | 7 | | 0 | | 1 | 
2   :   | 0 | | 1 | | 2 | 
0   :   NO Page fault
3   :   | 1 | | 2 | | 3 | 
0   :   | 2 | | 3 | | 0 | 
4   :   | 3 | | 0 | | 4 | 
2   :   | 0 | | 4 | | 2 | 
3   :   | 4 | | 2 | | 3 | 
0   :   | 2 | | 3 | | 0 | 
3   :   NO Page fault
2   :   NO Page fault
1   :   | 3 | | 0 | | 1 | 
2   :   | 0 | | 1 | | 2 | 
0   :   NO Page fault
1   :   NO Page fault
7   :   | 1 | | 2 | | 7 | 
0   :   | 2 | | 7 | | 0 | 
1   :   | 7 | | 0 | | 1 | 

```
#### Before you Start
You must have `g++` compiler and `make` installed on your system before testing.


## Install G++ and make on Ubuntu
Start by updating the packages list:
```
sudo apt update
````

Install the `build-essential` package by typing:
```
sudo apt install build-essential
```

The command installs a bunch of new packages including `gcc`, `g++` and `make`.

You may also want to install the manual pages about using GNU/Linux for development:
```
sudo apt-get install manpages-dev
```

To validate that the G++ compiler is successfully installed, use the `g++ --version` command which prints the G++ version:
```
g++ --version
```

## How to Build and Install
Just run `make` from the root of this repository. A binary called `exec.out` will be produced. To run this file, enter the following:
```
./exec.out
```

## License
Copyright (c) 2021 Ahmad Ashfaq

Permission is hereby granted, free of charge, to any person obtaining a copy of this code, to deal in any Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.
