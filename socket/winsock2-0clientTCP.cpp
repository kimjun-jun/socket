//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#pragma comment (lib, "Ws2_32.lib")
//
////STEP1	同端末通信	OK
////STEP2	LAN通信		
////STEP3	WAN通信	
//
//int main() 
//{
//	/* IP アドレス、ポート番号、ソケット */
//	char destination[80];
//	unsigned short port = 27015;
//	int dstSocket;
//
//	/* sockaddr_in 構造体 */
//	struct sockaddr_in dstAddr;
//
//	/* 各種パラメータ */
//	//int status;
//	//int numsnt;
//	char toSendText[1024] = "This is a test";
//
//	/************************************************************/
//
//	/* Windows 独自の設定 */
//	WSADATA data;
//	WSAStartup(MAKEWORD(2, 0), &data);
//
//	/* 相手先アドレスの入力 */
//	printf("Connect to ? : (name or IP address) ");
//	gets_s(destination);
//
//	/* sockaddr_in 構造体のセット */
//	memset(&dstAddr, 0, sizeof(dstAddr));
//	inet_pton(AF_INET,destination, &dstAddr.sin_addr);
//	dstAddr.sin_port = htons(port);
//	dstAddr.sin_family = AF_INET;
//
//	/* ソケット生成 */
//	dstSocket = socket(AF_INET, SOCK_STREAM, 0);
//
//	/* 接続 */
//	printf("Trying to connect to %s: \n", destination);
//	connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));
//
//	/* パケット送出 */
//	for (int i = 0; i < 10; i++) {
//		printf("sending...\n");
//		send(dstSocket, toSendText, strlen(toSendText) + 1, 0);
//		Sleep(1000);
//	}
//
//	/* Windows 独自の設定 */
//	closesocket(dstSocket);
//	WSACleanup();
//
//	return 0;
//}