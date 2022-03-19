# INF01151-BroadcastFeed
As an Operating Systems II assignment, this project aims to develop a Twitter-like Cli application in C++ practicing Concurrent Programming concepts.

## Development and Runtime Environment
The whole development environment as well as testing and execution environments was Linux Based Distributions 


## Dependencies:
 - CMake 3.16.3+
 - POSIX Threads 
 - POSIX User Datagram Protocol library

## Compiling

There are two main directories here:
- Client 
- Server

Into the both directories, there are a CMakeList Files, then you can build the both projects as well:
```bash
 > .../client/
 cmake .
 make
 
  > .../server/
 cmake .
 make
```

### Execution
As already compiled binaries for both projects, the execution is simple.
First, verifies if the client and the server binary has execution permission.
However, you can execute:

```bash
> .../client
chmod +x client
```

And then you can just execute both of the binaries with their arguments as illustrated above:

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
 