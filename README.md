# TP4 - Client-Server Communication via Shared Memory and Semaphores

## Description

This project demonstrates client-server communication using shared memory protected by semaphores. The objective is to implement a client process capable of interacting with a server while concurrently accessing a shared resource. The client sends arrays of random values to the server and receives calculated results, with access control ensured through semaphores.

## Program Structure

The program consists of the following components:

segdef.h: Header file with necessary includes and structure definitions, specifically for segment, representing the shared data structure.
libseg.a: Library containing functions for semaphore handling and random value generation.
segserv: Precompiled server program that processes client requests.
Client (this file): Client code responsible for initialization, sending requests, and verifying results from the server.

 ##Key Functions

initialisation(): Initializes segment and semaphore IDs, attaches the shared memory segment, and initializes the random number generator.
clientprocess(): Manages the client process, making 100 concurrent requests for memory access, calculating results, and comparing them with those provided by the server.
Semaphores Used

seg_dispo: Ensures only one process accesses the shared segment at a time.
seg_init: Notifies the server that the segment has been initialized.
res_ok: Signals the client that the server has calculated and stored the result in the shared segment.

## Client-Server Dialogue

The communication flow is as follows:

The client acquires seg_dispo to access the memory segment.
The client initializes the segment, calculates its own average, and then acquires seg_init to notify the server that the segment is ready.
The server responds, and the client waits on the res_ok semaphore to read the result.
The client releases seg_init and seg_dispo, and compares the result with its own calculation.

## Dependencies

This program requires the following files:

segdef.h
libseg.a
segserv

## Data Structure

The shared memory segment is structured as follows:

int pid: PID of the client.
int req: Request number.
long tab[maxval]: Array of random values.
long result: Result calculated by the server.
