//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#pragma comment (lib, "Ws2_32.lib")
//
//////STEP1	���[���ʐM	OK
//////STEP2	LAN�ʐM		OK
//////STEP3	WAN�ʐM	
//
//
//int main()
//{
//	WSAData wsaData;
//	char destination[80];
//	SOCKET sock;
//	struct sockaddr_in addr;
//
//	WSAStartup(MAKEWORD(2, 0), &wsaData);
//	/* �����A�h���X�̓��� */
//	printf("Connect to ? : (name or IP address) ");
//	gets_s(destination);
//
//	memset(&addr, 0, sizeof(addr));
//	inet_pton(AF_INET,destination, &addr.sin_addr);
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(12345);
//
//	sock = socket(AF_INET, SOCK_DGRAM, 0);
//
//	sendto(sock, "HELLO", 5, 0, (struct sockaddr *)&addr, sizeof(addr));
//
//	closesocket(sock);
//
//	WSACleanup();
//	getchar();
//
//	return 0;
//}