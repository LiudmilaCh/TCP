 

// receiving_bytes.cpp : main project file.

 

#include "stdafx.h"

#ifndef UNICODE

#define UNICODE

#endif

 

#define WIN32_LEAN_AND_MEAN

 

#include <winsock2.h>

#include <Ws2tcpip.h>

#include <stdio.h>

#include "conio.h"

 

// Link with ws2_32.lib

#pragma comment(lib, "Ws2_32.lib")

 

using namespace System;

 

int main(array<System::String ^> ^args)

{

 

/*------------------------------------------------------

 

            The initialization of the socket, vars&so on

------------------------------------------------------*/

 

    int iResult = 0;

 

    WSADATA wsaData;

 

    SOCKET RecvSocket;

    sockaddr_in RecvAddr;

 

    unsigned short Port = 1001;

 

    char RecvBuf[1024];

    int BufLen = 1024;

 

    sockaddr_in SenderAddr;

    int SenderAddrSize = sizeof (SenderAddr);

/*------------------------------------------------------

 

                  Starting information show

------------------------------------------------------*/

      Console::WriteLine(L"WILLKOMMEN!");

      wprintf(L"The sender's address is %d\n",SenderAddr);

      wprintf(L"The Port is %d\n",Port);

      wprintf(L"The receiver's address is %d\n",RecvAddr);

            _getch();

    //-----------------------------------------------

    // Initialize Winsock

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != NO_ERROR) {

        wprintf(L"WSAStartup failed with error %d\n", iResult);

        return 1;

    }

    //-----------------------------------------------

    // Create a receiver socket to receive datagrams

    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (RecvSocket == INVALID_SOCKET) {

        wprintf(L"socket failed with error %d\n", WSAGetLastError());

        return 1;

    }

    //-----------------------------------------------

    // Bind the socket to any address and the specified port.

    RecvAddr.sin_family = AF_INET;

    RecvAddr.sin_port = htons(Port);

//    RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

      RecvAddr.sin_addr.s_addr = inet_addr( "169.254.140.91" );

    // The sockaddr_in structure specifies the address family,

    // IP address, and port of the server to be connected to.

            wprintf(L"The IP address is %d\n", inet_addr);

 

    iResult = bind(RecvSocket, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));

    if (iResult != 0) {

        wprintf(L"bind failed with error %d\n", WSAGetLastError());

        return 1;

    }

/*------------------------------------------------------

 

                  Here the receiving is starting

------------------------------------------------------*/

   

    // Call the recvfrom function to receive datagrams

    // on the bound socket.

    wprintf(L"Receiving datagrams...\n");

    iResult = recvfrom(RecvSocket,

                       RecvBuf, BufLen, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);

      wprintf(L"The recvsocket is %d\n",RecvSocket);

    if (iResult == SOCKET_ERROR) {

        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());

    }

     

    //-----------------------------------------------

    // Close the socket when finished receiving datagrams

    wprintf(L"Finished receiving. Closing socket.\n");

    iResult = closesocket(RecvSocket);

    if (iResult == SOCKET_ERROR) {

        wprintf(L"closesocket failed with error %d\n", WSAGetLastError());

        return 1;

    }

 

    //-----------------------------------------------

    // Clean up and exit.

    wprintf(L"Exiting.\n");

    WSACleanup();

 

      _getch();

 

    return 0;

}
