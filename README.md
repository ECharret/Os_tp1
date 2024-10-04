# Os_tp1 Segmentation mémoire et listes chaînées

# EX1 
# Memory Segments Visualization in C

This program demonstrates how to expose the memory segments in C using `printf` to display the addresses of different segments of memory. It utilizes the `%p` format specifier to print the memory addresses of various memory areas and also uses the `pmap` command to show the memory map of the process.

## Memory Segments Covered:
- **Data**: Global variables that are initialized.
- **BSS**: Global variables initialized to zero.
- **Str**: String constants.
- **Heap**: Dynamically allocated memory.
- **Stack**: Local variables stored on the stack.
- **Main Function**: The code of the main function.
- **LibC Function**: The address of a standard C library function.
- **Mmap**: Memory allocated by the `mmap` function.

## Code Explanation:

The program defines variables for each memory segment and prints their addresses using `printf`. It also spawns a child process to execute the `pmap -x PID` command to display the memory map of the process, where `PID` is the process ID of the running program.

### Key Functions:
- `malloc`: Allocates memory on the heap.
- `mmap`: Allocates memory using memory mapping.
- `execlp`: Executes the `pmap` command to view the memory map.
- `fork`: Creates a new process to execute the `pmap` command.

# EX2
# File Byte Reversal Using Memory Mapping in C

This program demonstrates how to reverse the contents of a file by mapping it into memory using `mmap`. Instead of using standard file I/O operations, we manipulate the file directly via memory mapping, which can improve performance when working with large files. After mapping the file, the program reverses the bytes in memory and writes the changes back to the file.

## Steps Performed:
1. **Create a file**: Start by creating a file (`test.txt`) and populate it with some text.
2. **Open the file**: The program opens the file using the `open` system call.
3. **Get the file size**: Using `stat`, it retrieves the size of the file.
4. **Memory mapping**: The entire file is mapped into memory using `mmap`.
5. **Reverse the file content**: The bytes in the file are reversed in-place (first byte to last, second to second last, etc.).
6. **End the mapping**: The memory mapping is closed using `munmap`.
7. **Verify the result**: You can use the `cat` command to check if the content of `test.txt` is reversed.

## Code Explanation:

The program uses several system calls to accomplish the task:
- `open`: Opens the file in read/write mode.
- `stat`: Retrieves the size of the file.
- `mmap`: Maps the file into memory.
- `munmap`: Unmaps the memory after modifications.
- `close`: Closes the file descriptor.
