# INF01151-BroadcastFeed
As an Operating Systems II assignment, this project aims to develop a Twitter-like Cli application in C++, practicing Concurrent Programming concepts.

## Development and Runtime Environment
The whole development environment as well as testing and execution environments were Linux Based Distributions.

The following setups were used:
 - Ubuntu 21.04, kernel: 5.13.0-35-generic. Notebook Dell Inspiron 5448 com processador Intel i5-5200U @ 2.700GHz (2 Cores/4 Threads), 12 GB RAM. GCC 11.2.0.
 - Pop!_OS 20.04 LTS: Intel® Core™ i7-8750H CPU @ 2.20GHz × 12 GCC 11.2.0.
 - Arch Linux, kernel: 5.16.13-arch1-1, processador Intel i3-6100 @ 3.700GHz (2 Cores/4 Threads), 8GB RAM.  Compilador GCC 11.2.0

### Source
Source projects can be found in "server/src/" and "client/src/".

## Dependencies
 - CMake 3.16.3+
 - POSIX Threads library
 - POSIX User Datagram Protocol library

## Compiling

There are two main directories here:
- Client 
- Server

There is a CMakeLists.txt file in each of the directories. You can build each project as so:
```bash
 > .../client/
 cmake .
 make
 
  > .../server/
 cmake .
 make
```

### Execution
Having compiled binaries for each project, the execution is simple.
First, verify if the client and server binaries have execution permission.
However, you can execute:

```bash
> .../client
chmod +x client
```

Then you can execute both of the binaries with their arguments as illustrated below:

```bash
> .../client
./client <username> <server_ip> <server_port> 
```


```bash
> .../server
./server <server_ip> <server_port> [optional:<primary_server_ip> <primary_server_port>]
```
When given the optional parameters <primary_server_ip> and <primary_server_port> the server will start as a backup to the primary server that is specified.
 
### Authors
- Ernesto Vaz de Oliveira
- Maria Flávia Tondo
- Ricco Vasconcellos Constante Soares
- Wellington Machado de Espindula
 
