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
	const int id = 456;
	Actor actor(id, 12, 34, true, true, false);

	while (1)
	{

		actor.setLife();

		char* t = convert(actor);

		send(ClientSocket, t, sizeof(actor), 0);


		Sleep(500);

		char UxBuffer[9001];

		//vector<Actor> gameScene;
		Actor* gameScene = new Actor[1];
		int num_actors =0;

		int n = recv(ClientSocket, UxBuffer, sizeof(UxBuffer), 0);
		if (n > 0) {
			num_actors = n / sizeof(Actor);
			gameScene = new Actor[num_actors];

			char* buff = (char*)malloc(sizeof(Actor) * num_actors);
			buff = UxBuffer;

			Actor* act = (Actor*)buff;


			for (int i = 0; i < num_actors; ++i) {

				Actor a = (*act);
				act++;
				gameScene[i] = a;

			}

		}
		else {
			cout << "Receive failed!!" << endl;
		}

		for (int i = 0; i < num_actors; ++i) {
			cout << gameScene[i] << endl;
		}

	}

	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();

	std::cout << "Successful Run\n";
}
