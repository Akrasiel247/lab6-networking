// SingleClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <thread>
#include <vector>
#include "Actor.h"
#include "Serialize.h"



using namespace std;



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
	const int id = 123;
	Actor z(id, 12, 34, true, true, false);

	while (1)
	{
		
		z.setLife();
		
		char* t = convert(z);

		send(ClientSocket, t, sizeof(z), 0);


		Sleep(500);

		//This is hardcoded in- how can I allocate the mem without knowig the size of the incoming vector?
		char UxBuffer[9001];
		//char* buff = (char*)malloc(sizeof(Actor));

		//vector<Actor> gameScene;
		Actor* gameScene=new Actor[1];
		int num_actors;

		int n = recv(ClientSocket, UxBuffer, sizeof(UxBuffer), 0);
		if (n > 0) {
			num_actors = n / sizeof(Actor);
			gameScene = new Actor[num_actors];

			char* buff = (char*)malloc(sizeof(Actor)*num_actors);
			

			Actor* act = (Actor*)buff;
			//memcpy(act, , sizeof(Actor));


			cout << num_actors << "This is the number of actors received" << endl;

			for (int i = 0; i < num_actors; ++i) {
				Actor a;
				act++;
				gameScene[i]=a;
			}

		}
		else {
			cout << "Receive failed!!" << endl;
		}

		for (int i = 0; i < num_actors;++i) {
			cout << gameScene[i] << endl;
		}

	}

	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();

	std::cout << "Successful Run\n";
}
