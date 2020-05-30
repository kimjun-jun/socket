#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	const char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Validate the parameters
	/*
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}
	*/

	// Initialize Winsock
	//WSAStartup(バージョン指定, WSADATAのアドレス);
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		switch (iResult) {
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY\n");			//ネットワークサブシステムがネットワークへの接続を準備できていない
			break;
		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED\n");		//要求されたwinsockのバージョンがサポートされていない
			break;
		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS\n");			//ブロッキング操作の実行中であるか、 またはサービスプロバイダがコールバック関数を処理している
			break;
		case WSAEPROCLIM:
			printf("WSAEPROCLIM\n");			//winsockが処理できる最大プロセス数に達した
			break;
		case WSAEFAULT:
			printf("WSAEFAULT\n");				//第二引数であるlpWSAData は有効なポインタではない
			break;
		}		
		printf("失敗!!___enterで終了\n");
		getchar();
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		printf("失敗!!___enterで終了\n");
		getchar();
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		printf("サーバーに接続します\n");

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			printf("失敗!!___enterで終了\n");
			getchar();
			WSACleanup();
			return 1;
		}
		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		printf("失敗!!___enterで終了\n");
		getchar();
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	printf("サーバーに接続成功___enter押してメッセージを送信\n");
	getchar();
	printf("送信しました\n");

	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("メッセージ送信成功したよ!!\n");
	printf("Bytes Sent(送信): %ld\n", iResult);
	printf("サーバーからの応答を待ってるよ...\n\n");

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("サーバーからの応答があったよ!!\n");
			printf("メッセージが来てるみたい__enter押してメッセージを確認\n");
			getchar();
			printf("Bytes received(受信): %d\n", iResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			printf("失敗!!___enterで終了\n");
			getchar();
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			printf("失敗!!___enterで終了\n");
			getchar();
		}
	} while (iResult > 0);

	printf("通信成功!!___enterで終了\n");
	getchar();

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}