# Os_tp2 Allocateur de mémoire sécurisé

## Description

This project implements a custom memory allocator to replace the standard malloc and free functions. The goal is to enhance memory management by reusing free blocks, handling fragmentation through merging adjacent blocks, and detecting memory overflows using magic_numbers.

## Objectives

The developed allocator allows:

Dynamic memory allocation and deallocation.
Detection of memory corruption through magic_numbers surrounding each memory block.
Management of free blocks with a linked list, ordered by memory address.
Optimized memory management through merging of contiguous blocks and splitting large blocks when necessary.
## Features

Memory Allocation (malloc_3is):
Searches for a sufficiently large free block in the list.
If no block is available, the heap is expanded using sbrk().
Magic_numbers are placed before and after each block to detect overflows.
Memory Deallocation (free_3is):
Verifies the integrity of the memory block using magic_numbers.
Inserts the freed block back into the list of free blocks, sorted by increasing address.
Merges adjacent free blocks to reduce fragmentation.
Overflow Detection:
Each allocated block is enclosed by magic_numbers (0x0123456789ABCDEF). If these numbers are altered, the program detects a memory overflow and exits.
## Progress

The project has been implemented and tested up to Question 4.
Question 5 (splitting large blocks) is thought to be functional, but further testing is required.
Question 6 (merging adjacent free blocks) is implemented but untested. The magic number does not need to be re-checked during merging, as it was verified during the overflow check.
Question 7 (pre-allocation of large memory blocks) is not fully understood, and no specific implementation was added.
Question 8 (random magic number generation) is not implemented. It could be done using rand() and converting the result to hexadecimal.
Question 9 (renaming functions to replace malloc and free) has not been done due to potential risks.

