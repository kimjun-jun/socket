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
#define DEFAULT_PORT "80"				//�l�b�g���[�N�n�̃|�[�g���w��



int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,				//����̃A�h���X���
		*ptr = NULL,							//�����̃A�h���X���
		hints;									//�ݒ�p�A�h���X
	const char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;								//�G���[�S�ʌ��o
	int recvbuflen = DEFAULT_BUFLEN;

	PCSTR ServerADDR;
	ServerADDR = "192.168.11.21";
	PCSTR ClientADDR;
	ClientADDR = "192.168.11.6";

	// Validate the parameters
	/*
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		printf("�R�}���h�v�����v�g������s���Ĉ����ɃT�[�o�[IP�A�h���X������Ă�������\n");
		printf("���s!!___enter�ŏI��\n");
		getchar();
		return 1;
	}
	*/

	// Initialize Winsock
	//WSAStartup(�o�[�W�����w��, WSADATA�̃A�h���X);
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		switch (iResult) {
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY\n");			//�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�
			break;
		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED\n");		//�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
			break;
		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS\n");			//�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			break;
		case WSAEPROCLIM:
			printf("WSAEPROCLIM\n");			//winsock�������ł���ő�v���Z�X���ɒB����
			break;
		case WSAEFAULT:
			printf("WSAEFAULT\n");				//�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
			break;
		}		
		printf("���s!!___enter�ŏI��\n");
		getchar();
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	/*
	��������
	hints.ai_family = AF_UNSPEC;
	AF_UNSPEC��unspecified
	AF_INET��nternetwork: UDP, TCP, etc.
	*/
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	// Resolve the server address and port
	//getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	//�������̓T�[�o�[��IP�A�h���X
	//�������̓T�[�o�[�̃|�[�g�A�h���X
	//iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	//�T�[�o�[����IP�A�h���X��v������getaddrinfo�֐�
	iResult = getaddrinfo(ServerADDR, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		printf("���s!!___enter�ŏI��\n");
		getchar();
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);


		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			printf("���s!!___enter�ŏI��\n");
			getchar();
			WSACleanup();
			return 1;
		}
		// Connect to server.
		printf("�T�[�o�[�ɐڑ������___enter�Őڑ�\n");
		getchar();
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("��΂�___enter�Ŏ���\n");
			getchar();
			continue;
		}
		break;
	}

	// result�J��
	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		printf("���s!!___enter�ŏI��\n");
		getchar();
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	printf("�T�[�o�[�ɐڑ�����___enter�����ă��b�Z�[�W�𑗐M\n");
	getchar();

	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("���b�Z�[�W���M����������!!\n");
//	printf("������IP�A�h���X(���M): %s\n",);
	printf("�T�[�o�[����̉�����҂��Ă��...\n\n");

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
			printf("�T�[�o�[����̉�������������!!\n");
			printf("���b�Z�[�W�����Ă�݂���__enter�����ă��b�Z�[�W���m�F\n");
			getchar();
			printf("Bytes received(��M): %d\n", iResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			printf("���s!!___enter�ŏI��\n");
			getchar();
		}
	} while (iResult > 0);

	printf("�ʐM����!!___enter�ŏI��\n");
	getchar();

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}