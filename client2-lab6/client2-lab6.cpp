// SingleClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <thread>
#include <vector>
#include "Actor.h"



using namespace std;


template <typename T>
char* convert(T& input) {

	char* t = (char*)malloc(sizeof(input));
	memcpy(t, &input, sizeof(input));

	return t;
}
char* convert(std::vector<Actor>& input) {

	int size_Actors = sizeof(Actor) * input.size();
	char* t = (char*)malloc(size_Actors);
	memcpy(t, &input, size_Actors);

	return t;
}


int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return -1;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address

	if ((connect(ClientSocket, (struct sockaddr*) & SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		cout << "Connecting to server failed!!!\n";
		return -1;
	}
	const int id = 567;
	Actor z(id, 12, 34, true, true, false);

	while (1)
	{

		z.setLife();

		char* t = convert(z);

		cout << z << endl;


		send(ClientSocket, t, sizeof(z), 0);


		Sleep(500);

		char* UxBuffer = (char*)malloc(sizeof(Actor));

		vector<Actor> gameScene;
		Actor a;

		int n = recv(ClientSocket, UxBuffer, sizeof(Actor), 0);
		if (n > 0) {

		//	for (int i = 0; i < 2; ++i) {
				memcpy(&a, UxBuffer, sizeof(Actor));
				cout << "TTTTTT" << a << endl;
				gameScene.push_back(a);

		//	}

		}

	}

	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();

	std::cout << "Successful Run\n";
}
