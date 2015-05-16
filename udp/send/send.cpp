#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#include<windows.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
int main()
{
	SOCKET s;
	sockaddr_in addrto;
	WSADATA wsdata;
	BOOL bsocket;
	char *smsg="this is a test";
	//启动SOCKET库，版本为2.0
	WSAStartup(0x0202,&wsdata);
	
	s=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	bsocket=TRUE;
   	//然后赋值给地址，用来从网络上的广播地址接收消息；
	addrto.sin_family=AF_INET;
    addrto.sin_addr.s_addr=INADDR_BROADCAST;
	addrto.sin_port=htons(5050);
	bool opt=true;
	//设置该套接字为广播类型，
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char FAR *)&opt,sizeof(opt));
	int nlen=sizeof(addrto);
	while(1)
	{
		Sleep(5000);
		//从广播地址发送消息
		int ret=sendto(s,smsg,256,0,(sockaddr*)&addrto,nlen);
		if(ret==SOCKET_ERROR)
			cout<<WSAGetLastError()<<endl;
		else
		{		
			printf("ok");	
		}
	}
}