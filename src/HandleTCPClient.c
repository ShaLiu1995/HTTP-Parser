#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include "CalcServer.h"
#include "CalcFramer.hpp"
#include "CalcParser.hpp"

using namespace std;

void HandleTCPClient(int clntSocket)
{
    // PUT YOUR CODE HERE
    char buffer[BUFSIZE] = {0};
    CalcFramer framer;
    uint64_t val = 0;
    // uint64_t cnt = 1;

    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
        DieWithError("recv() failed");
    framer.append(buffer);

    // printf("Buffer:%sEndOfBuffer\n", buffer);
    // send and receive again
    // while (numBytesRcvd > 0) {
    while (numBytesRcvd > 0) {
        // cnt = 1;
        while (framer.hasMessage()) {

            string message = framer.topMessage();
            // printf("Message is:%send\n", message.c_str());
            framer.popMessage();

            if (message == "break") {
                break;
            }

            if (message.length() == 0) {
                const char* ans = to_string(val).append("\r\n").c_str();

                ssize_t numBytesSent = send(clntSocket, ans, strlen(ans), 0);
                if (numBytesSent < 0) 
                    DieWithError("send() failed");
                val = 0;
                continue;
            }

            CalcInstruction ci = CalcParser::parse(message);
            // printf("Opcode is: %s\n", ci.opcode.c_str());
            // printf("Operand is: %lu\n", ci.operand);
            // printf("Current Val is: %lu\n", val);

            // if (ci.operand != cnt++) {
            //     printf("Opcode is: %s\n", ci.opcode.c_str());
            //     printf("Operand is: %lu\n", ci.operand);
            //     printf("cnt is: %lu\n", cnt);
            // }

            // if (ci.opcode != "ADD") {
                //printf("Message is:%send\n", message.c_str());
                //printf("Opcode is: %s\n", ci.opcode.c_str());
                //printf("Operand is: %lu\n", ci.operand);
            //}

            if (ci.opcode == "SET") {
                val = ci.operand;
            } else if (ci.opcode == "ADD") {
                val += ci.operand;
            } else if (ci.opcode == "SUB") {
                val -= ci.operand;
            } else {
                // const char* ans = to_string(val).c_str();
                // ssize_t numBytesSent = send(clntSocket, ans, sizeof(ans), 0);
                // if (numBytesSent < 0) 
                //     DieWithError("send() failed");
                continue;
            }
        }
        
        // printf("Final Val is: %lu\n", val);
        // const char* ans = to_string(val).c_str();

        // ssize_t numBytesSent = send(clntSocket, ans, sizeof(ans), 0);
        // if (numBytesSent < 0) 
        //     DieWithError("send() failed");
        // else if (numBytesSent != numBytesRcvd)
        //     DieWithError("Unexpected number of bytes sent");

        // if more data to receive
        // memset(buffer, 0, BUFSIZE);
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
        if (numBytesRcvd < 0) 
            //DieWithError("recv() failed");
            break;  
        framer.append(buffer);
    }



    close(clntSocket);    /* Close client socket */
}
