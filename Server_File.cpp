#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#define BUF_SIZE 1024
#define VERSION 1
int main() {
    double num = 1;
    while(true)
    {
        printf("%d\n",num);
       char *filename = "PlaneGame.exe";  //
	FILE *fp = fopen(filename, "rb");  //�Զ����Ʒ�ʽ���ļ�
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	  WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	sockAddr.sin_port = htons(5656);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

        //�ȼ���ļ��Ƿ����


    listen(servSock, 20);
        SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//ѭ���������ݣ�ֱ���ļ���β
	char buffer[BUF_SIZE] = { 0 };  //������
	int nCount;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		send(clntSock, buffer, nCount, 0);
	}
	shutdown(clntSock, SD_SEND);  //�ļ���ȡ��ϣ��Ͽ����������ͻ��˷���FIN��
	recv(clntSock, buffer, BUF_SIZE, 0);  //�������ȴ��ͻ��˽������
	closesocket(clntSock);
    closesocket(servSock);
    fclose(fp);
    printf("You have get one \n");
    num++;
    }






	WSACleanup();

    exit(0);
	return 0;
}