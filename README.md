# C++ Socket Chat Application

## Overview

This repository contains the source code for a simple chat application where multiple clients can communicate with each other through a server using TCP sockets. The server listens on port 8080 and uses multithreading to handle client messages concurrently. 

### Files:
- **Client-side**: Client code that sends and receives messages to/from the server.
- **Server-side**: Server code that manages multiple clients and facilitates message broadcasting.

## Prerequisites

- C++17 or later
- Linux-based system for socket programming (e.g., Ubuntu)
- Basic understanding of TCP/IP sockets and threading in C++

## Client Code

The client connects to the server, sends messages, and receives messages from other clients.

### Key Features
- **Socket Creation**: Initializes a socket for communication.
- **Message Sending**: Allows the user to send messages that are broadcasted to all connected clients.
- **Multithreading**: One thread for sending messages and another for receiving messages.
  
