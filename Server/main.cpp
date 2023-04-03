#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>


int main()
{
	SOCKET server_socket,accept_socket;
	int port = 55555;
	WSADATA wsa_data;
	int wsa_eer;
	WORD wVersion_requested = MAKEWORD(2,2);
	wsa_eer= WSAStartup(wVersion_requested,&wsa_data);
	if(wsa_eer!=0)
	{
		std::cout<<"Winsock dll not found!"<<std::endl;
		return 0;
	}
	else
	{
		std::cout<<"Winsock dll found!"<<std::endl;
	}

	server_socket=INVALID_SOCKET;
	server_socket= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server_socket==INVALID_SOCKET)
	{
		std::cout<<"Error socket "<< WSAGetLastError()<<std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout<<"Socket created"<<std::endl;
	}

	sockaddr_in service;
	service.sin_family =AF_INET;
	InetPton(AF_INET,_T("127.0.0.1"),&service.sin_addr.s_addr);
	service.sin_port=htons(port);
	if(bind(server_socket,(SOCKADDR*)&service,sizeof(service))==SOCKET_ERROR)
	{
		std::cout<<"bind socket failed!"<<WSAGetLastError<<std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout<<"Bind socket: "<<"127.0.0.1 "<<port<<std::endl;
	}

	if(listen(server_socket,1)==SOCKET_ERROR)
	{
		std::cout<<"Error listenning on socket"<<WSAGetLastError<<std::endl;
		return 0;
	}
	else
	{
		std::cout<<"Waiting for connection..."<<std::endl;
	}

	accept_socket=accept(server_socket,NULL,NULL);
	if(accept_socket==INVALID_SOCKET)
	{
		std::cout<<"Accept failed"<<WSAGetLastError<<std::endl;
		WSACleanup();
		return -1;
	}
	std::cout<<"Accept connection!"<<std::endl;

	char receive_buffer[200]{};
	int byte_count = recv(accept_socket,receive_buffer,200,0);
	if(byte_count<0)
	{
		std::cout<<"Server error "<<WSAGetLastError<<std::endl;
	}
	else
	{
		std::cout<<"Client: "<<receive_buffer<<std::endl;
	}

	char confirmation[200] ="Message Received!";
	byte_count = send(accept_socket,confirmation,200,0);
	if(byte_count<0)
	{
		std::cout<<"Server error "<<WSAGetLastError<<std::endl;
	}
	else
	{
		std::cout<<"Server: "<<confirmation<<std::endl;
	}

	system("pause");
	WSACleanup();

	return 0;
}
