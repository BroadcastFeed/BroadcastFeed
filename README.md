# INF01151-BroadcastFeed
As an Operating Systems II assignment, this project aims to develop a Twitter-like Cli application in C++, practicing Concurrent Programming concepts.

## Development and Runtime Environment
The whole development environment as well as testing and execution environments were Linux Based Distributions.

The following setups were used:
 - Ubuntu 21.04 com kernel: 5.13.0-35-generic. Notebook Dell Inspiron 5448 com processador Intel i5-5200U @ 2.700GHz (2 Cores/4 Threads), 12 GB RAM. GCC 11.2.0.
 - Pop!_OS 20.04 LTS: Intel® Core™ i7-8750H CPU @ 2.20GHz × 12 GCC 11.2.0.
 - Arch Linux, kernel: 5.16.13-arch1-1, processador Intel i3-6100 @ 3.700GHz (2 Cores/4 Threads), 8GB RAM.  Compilador GCC 11.2.0

### Source
The both source projects can be found into "server/src/" and "client/src/".

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
./client [client_username] [server_ipaddress] [server_port] 
```


```bash
> .../server
./server [server_ipaddress] [server_port] 
```

### Authors
- Ernesto Vaz de Oliveira
- Maria Flávia Tondo
- Ricco Vasconcellos Constante Soares
- Wellington Machado de Espindula
 
