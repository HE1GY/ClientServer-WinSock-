#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>


int main()
{
	SOCKET client_socket,accept_socket;
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
		std::cout<<"Winsock dll  found!"<<std::endl;
		std::cout<<"Status: "<<wsa_data.szSystemStatus<<std::endl;
	}

	client_socket=INVALID_SOCKET;
	client_socket= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(client_socket==INVALID_SOCKET)
	{
		std::cout<<"Error socket "<< WSAGetLastError()<<std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout<<"socket OK!"<<std::endl;
	}

	sockaddr_in service;
	service.sin_family =AF_INET;
	InetPton(AF_INET,_T("127.0.0.1"),&service.sin_addr.s_addr);
	service.sin_port=htons(port);
	if(connect(client_socket,(SOCKADDR*)&service,sizeof(service))==SOCKET_ERROR)
	{
		std::cout<<"connect socket failed!"<<WSAGetLastError<<std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout<<"connect socket OK!"<<std::endl;
	}
	system("pause");
	WSACleanup();



	return 0;
}
