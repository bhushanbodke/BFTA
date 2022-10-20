#include "Pch.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define PORT 54000

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

SOCKET server(bool* IsConnected) {
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
		std::cout << "failed to intialize the winsock" << std::endl;
		return 1;
	}
	else 
	{
		std::cout << "winsock intialized sucessfully" << std::endl;
	}

	// open socket of the server
	SOCKET soc = socket(AF_INET, SOCK_STREAM, 0);

	// struct to store adress info of the server ip and port  
	struct sockaddr_in address;
	
	// AF_INET is connection over internet
	address.sin_family = AF_INET;

	// htons Host to Networking small  convertion function 
	address.sin_port = htons(PORT);
	// INADDR_ANY is Localhost
	address.sin_addr.S_un.S_addr = INADDR_ANY;

	//bind socket to ip and port 
	if (bind(soc, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		std::cout << "Binding failed" << std::endl;
		return 1; 
	}
	else
	{
		std::cout << "Binding sucessfully" << std::endl;
	}
	//Listen to requests on socket
	if (listen(soc, 5) < 0)
	{
		std::cout << "Listen failed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Listening sucessfully" << std::endl;
	}
	// new socket address struct  to store incoming 
	struct sockaddr_in cli_address;
	SOCKET cli_soc;
	int add_len = sizeof(cli_address);
	cli_soc = accept(soc, (sockaddr*)&cli_address, &add_len);
	if (cli_soc < 0)
	{
		std::cout << "accept failed" << std::endl;
		return 1;
	}
	else
	{
		*IsConnected = true;
		std::cout << "accept sucess" << std::endl;
	}
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&cli_address, add_len, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << "connected to port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &cli_address.sin_addr, host, NI_MAXHOST);
		std::cout << "connected on port " << ntohs(cli_address.sin_port) << std::endl;
	}
	return cli_soc;
}