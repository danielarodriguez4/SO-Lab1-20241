# Reverse Utility - Operating Systems Lab

Made by:
Estiven Ospina González
María Daniela Rodríguez Chacón

This laboratory practice focuses on the development of a reverse utility program in C as part of the Operating Systems course. The main objective is to strengthen programming skills in file handling, dynamic memory management, and error control, while also exploring key system concepts such as:

- File descriptors and metadata (using the `stat` system call).
- Environment variables for configurable error prefixes (`error` or `reverse`).
- Linked lists for dynamic data structures.
- Input/Output redirection between standard streams and external files.
- 
The program reads the contents of an input file and writes them in reverse order to an output file. If no input is specified, it reads from `stdin`, and if no output is given, it writes to `stdout`.

Through this practice, we gain hands-on experience with:

1. Implementing error handling that follows precise specifications.
2. Using inodes via stat to detect when input and output files are the same.
3. Managing command-line arguments for different execution cases.
4. Automating testing with shell scripts (`test-reverse.sh`).
5. 
This work not only develops technical coding abilities but also emphasizes the importance of reliability, robustness, and clarity in system-level programming.


## How to compile

Use `clang` to compile the program:
```c 
clang -Wall -Wextra -std=c11 -o reverse reverse.c
```
This generates an executable named `reverse`.

## How to run

The program accepts the following formats:

## Case 1: input and output
```c 
./reverse input.txt output.txt
```
## Case 2: only input, output goes to stdout
```c 
./reverse input.txt
```
## Case 3: no args, reads stdin and writes to stdout          
```c 
./reverse                    
```
- input.txt: file to read from
- output.txt: file where the reversed content will be written

NOTE: if the input and output files are the same, the program will print an error and exit.

---
## Running tests

All tests are included in the tests/ folder. Run the test script:
```c 
./test-reverse.sh
```
You will see an output like the one below:

```c 
test 1: passed
test 2: passed
test 3: passed
...
```

## Use of stat

The program uses the stat system call to check whether two filenames refer to the same file. This prevents accidental overwriting when the user tries to use the same file as both input and output:

```c
struct stat st1, st2;
stat(argv[1], &st1);
stat(argv[2], &st2);

if (st1.st_ino == st2.st_ino) {
    fprintf(stderr, "reverse: input and output file must differ\n");
    exit(1);
}

- `st_ino` is the inode number: unique identifier of a file within a filesystem.
- If both files have the same inode, they are the same file.
```
# Example section

## How to Build and Run the Reverse Utility

Follow these steps to compile the program, run examples, and execute the test suite.

### 1. Clone or copy the project files
Make sure you have the following files in your working directory:
- `reverse.c` (the source code)
- `test-reverse.sh` (the test runner script)
- `tests/` (folder with input, expected `.err` and `.rc` files)

### 2. Compile the program
Use clang to compile the C source:
```c
clang -Wall -Wextra -std=c11 -o reverse reverse.c
```
### 3. Run a quick example
```c
./reverse input.txt
```
Expected output:
```bash
a file
is 
this
hello
```
### 4. Run all tests
```c
./test-reverse.sh
```



