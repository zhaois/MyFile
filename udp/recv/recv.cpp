#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
/*

HANDLE hr,hl,hbusy;

  struct  thrpar
  {
	SOCKET s;
  };

  struct recpar
  {
	  SOCKET srec;
	  struct sockaddr_in addr;
  };


 UINT recthread(LPVOID pp)
  {
	  SOCKET srec,s2;
	  struct recpar *prec=(struct recpar *)pp;
      sockaddr_in recaddr;

	  srec=prec->srec;
	  recaddr=prec->addr;
	  char buf[256];
	  DWORD ret;

      printf("recv thread start!");
	  ret=recv(srec,buf,256,0);
	  if(ret==0)
	  {
		  printf("connect close!");
		  closesocket(srec);
		  return 0;
	  }
	  else if(ret==SOCKET_ERROR)
	  {
		  printf("connect error!");
		  closesocket(srec);
		  return 0;
	  }
   printf("recv data:%s",buf);
     return 0;
  }

	  
   DWORD WINAPI listhread(LPVOID pp)
  {
	   ::MessageBox(NULL,"enter the listhread","KK",MB_OK);
	  struct thrpar *pthr=(struct thrpar*)pp;
	  SOCKET sl,saccept;
	  sockaddr_in here, there;
	  char name[256];
	  struct hostent *phost;
	  int ret;
       
	  gethostname(name,256);
	  phost=gethostbyname(name);

	  here.sin_family=AF_INET;
	  here.sin_port=htons(1024);
	  here.sin_addr.S_un.S_un_b.s_b1=phost->h_addr_list[0][0];
	  here.sin_addr.S_un.S_un_b.s_b2=phost->h_addr_list[0][1];
	  here.sin_addr.S_un.S_un_b.s_b3=phost->h_addr_list[0][2];
	  here.sin_addr.S_un.S_un_b.s_b4=phost->h_addr_list[0][3];
      
      sl=pthr->s;
	  
	  ret=bind(sl,(struct sockaddr *)&here,sizeof(here));
	  if(ret!=0)
	  {
		  printf("bind error");
		  return 0;
	  }
	  ret=listen(sl,5);
	  if(ret!=0)
	  {
		   printf("listen error");
		  return 0;
	  }
	  while(true)
	  {
		  int nlen=sizeof(there);
		  saccept=accept(sl,(struct sockaddr *)&there,&nlen);
		  if(saccept==INVALID_SOCKET)
		  {
			  printf("accept socket invalid");
		  }
		  DWORD wret=WaitForSingleObject(hbusy,500);
		  if(wret==WAIT_TIMEOUT)
		  {
			 send(saccept,"\0",1,0);
			closesocket(saccept);
			continue ;
		 }
		 DWORD recid;
		  struct recpar *prec;
		  prec->addr=there;
		  prec->srec=saccept;
		   
		  hr=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&listhread,prec,0,&recid);
		 return 1;
	  }
	   return 1;
  }

void main(void)
{
	SOCKET s;
	sockaddr_in addrin;
	WSADATA wsdata;
	BOOL bsocket;
	char *smsg="this is a test";
	
	  WSAStartup(0x0202,&wsdata);
	  
		s=WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
		hbusy=CreateSemaphore(NULL,0,2,NULL);
		struct  thrpar *psc;
		psc=new struct thrpar;
		DWORD lisid;
		psc->s=s;
		
		  hr=CreateThread(NULL,0,listhread,psc,0,&lisid);
		  DWORD ret=WaitForSingleObject(hr,10000);
		  if(ret==WAIT_OBJECT_0)printf("thread time out%d\r\n",lisid);
		  
}*/
void main(void)
{
	SOCKET s;
	sockaddr_in from,a;
	WSADATA wsdata;
	BOOL optval;
	//启动SOCKET库，版本为2.0
	WSAStartup(0x0202,&wsdata);
	optval=TRUE;
	//然后赋值给两个地址，一个用来绑定套接字，一个用来从网络上的广播地址接收消息；
	a.sin_family=AF_INET;
	a.sin_addr.s_addr=0;
	a.sin_port=htons(5050);

	from.sin_family=AF_INET;
	from.sin_addr.s_addr=INADDR_BROADCAST;
	from.sin_port=htons(5050);
	
	int fromlength=sizeof(SOCKADDR);
	//用UDP初始化套接字
	s=socket(AF_INET,SOCK_DGRAM,0);
	  //设置该套接字为广播类型，
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char FAR *)&optval,sizeof(optval));
	bind(s,(sockaddr *)&a,sizeof(sockaddr_in));
	char buf[256];
	while(1)
	{//从广播地址接收消息，注意用来绑定的地址和接收消息的地址是不一样的
		recvfrom(s,buf,256,0,(struct sockaddr FAR *)&from,(int FAR *)&fromlength);
		//Sleep(2000);
		printf("%s\n",buf);
		ZeroMemory(buf,256);
	}
}
