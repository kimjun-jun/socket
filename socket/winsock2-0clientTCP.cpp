//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#pragma comment (lib, "Ws2_32.lib")
//
////STEP1	���[���ʐM	OK
////STEP2	LAN�ʐM		
////STEP3	WAN�ʐM	
//
//int main() 
//{
//	/* IP �A�h���X�A�|�[�g�ԍ��A�\�P�b�g */
//	char destination[80];
//	unsigned short port = 27015;
//	int dstSocket;
//
//	/* sockaddr_in �\���� */
//	struct sockaddr_in dstAddr;
//
//	/* �e��p�����[�^ */
//	//int status;
//	//int numsnt;
//	char toSendText[1024] = "This is a test";
//
//	/************************************************************/
//
//	/* Windows �Ǝ��̐ݒ� */
//	WSADATA data;
//	WSAStartup(MAKEWORD(2, 0), &data);
//
//	/* �����A�h���X�̓��� */
//	printf("Connect to ? : (name or IP address) ");
//	gets_s(destination);
//
//	/* sockaddr_in �\���̂̃Z�b�g */
//	memset(&dstAddr, 0, sizeof(dstAddr));
//	inet_pton(AF_INET,destination, &dstAddr.sin_addr);
//	dstAddr.sin_port = htons(port);
//	dstAddr.sin_family = AF_INET;
//
//	/* �\�P�b�g���� */
//	dstSocket = socket(AF_INET, SOCK_STREAM, 0);
//
//	/* �ڑ� */
//	printf("Trying to connect to %s: \n", destination);
//	connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));
//
//	/* �p�P�b�g���o */
//	for (int i = 0; i < 10; i++) {
//		printf("sending...\n");
//		send(dstSocket, toSendText, strlen(toSendText) + 1, 0);
//		Sleep(1000);
//	}
//
//	/* Windows �Ǝ��̐ݒ� */
//	closesocket(dstSocket);
//	WSACleanup();
//
//	return 0;
//}