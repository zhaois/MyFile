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
	//����SOCKET�⣬�汾Ϊ2.0
	WSAStartup(0x0202,&wsdata);
	
	s=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	bsocket=TRUE;
   	//Ȼ��ֵ����ַ�������������ϵĹ㲥��ַ������Ϣ��
	addrto.sin_family=AF_INET;
    addrto.sin_addr.s_addr=INADDR_BROADCAST;
	addrto.sin_port=htons(5050);
	bool opt=true;
	//���ø��׽���Ϊ�㲥���ͣ�
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char FAR *)&opt,sizeof(opt));
	int nlen=sizeof(addrto);
	while(1)
	{
		Sleep(5000);
		//�ӹ㲥��ַ������Ϣ
		int ret=sendto(s,smsg,256,0,(sockaddr*)&addrto,nlen);
		if(ret==SOCKET_ERROR)
			cout<<WSAGetLastError()<<endl;
		else
		{		
			printf("ok");	
		}
	}
}