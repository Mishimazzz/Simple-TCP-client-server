Simple TCP Client-Server (C, Linux)
This project implements a simple TCP client-server application in C on Linux.

Files
server.c — multi-client TCP echo server
client.c — TCP client that sends periodic messages

How to Compile
gcc server.c -o server
gcc client.c -o client

How to Run
./server 8080
./client 127.0.0.1 8080

Demo Steps
1.Compile both programs
2.Start the server on a port (e.g., 8080)
3.Start one or more clients connecting to the server
4.Each client sends a message every second
5.The server echoes the message back
6.The client prints the server’s response

Example client output:
send: message 1
reply: message 1
send: message 2
reply: message 2
...
