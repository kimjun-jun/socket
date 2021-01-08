#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#define BUFFER_SIZE 100

//STEP1	���[���ʐM	OK
//STEP2	LAN�ʐM		
//STEP3	WAN�ʐM	

using namespace std;


//////////////////////////////////////////////////////////

int NetClientSocketCreate();
void Packet();
void SendPacket(int i);
void ReceivePacket();

//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
/* IP �A�h���X�A�|�[�g�ԍ��A�\�P�b�g */
char destination[80];
unsigned short port = 27015;
int dstSocket;

/* sockaddr_in �\���� */
struct sockaddr_in dstAddr;

/* �e��p�����[�^ */
int numrcv;
char buffer[BUFFER_SIZE]; //�����Ă���f�[�^���e
char toSendText[1024] = "1";
int status;
//////////////////////////////////////////////////////////


int main() 
{

	NetClientSocketCreate();
		
	//�}���`�X���b�h�Ŏ�M�v���O����(��M�֐�)�N���@�ׂ����ʐM����@1/60����Ȃ��@�֐���ŏo����
	//�}���`�X���b�h�J�n
	std::thread t1(Packet);

	while (1)
	{

	}

	/* Windows �Ǝ��̐ݒ� */
	closesocket(dstSocket);
	WSACleanup();

	return 0;
}

int NetClientSocketCreate(void)
{
	/* Windows �Ǝ��̐ݒ� */
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* �����A�h���X�̓��� */
	//printf("Connect to ? : (name or IP address) ");
	//gets_s(destination);

	sprintf_s(destination, "192.168.11.3");

	/* sockaddr_in �\���̂̃Z�b�g */
	memset(&dstAddr, 0, sizeof(dstAddr));
	inet_pton(AF_INET, destination, &dstAddr.sin_addr);
	dstAddr.sin_port = htons(port);
	dstAddr.sin_family = AF_INET;

	/* �\�P�b�g���� */
	dstSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* �ڑ� */
	printf("Trying to connect to %s: \n", destination);
	connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	 // val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	 // �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(dstSocket, FIONBIO, &val);

	return 0;
}

void Packet(void)
{
	/*
	while (1)
	{
		SendPacket();
		ReceivePacket();
	}
	*/

	for(int i=0;i<10;i++)
	{
		SendPacket(i);
		ReceivePacket();
	}

}


void SendPacket(int i)
{
	/* �p�P�b�g���o */
	printf("Send��%d\n",i+1);
	send(dstSocket, toSendText, strlen(toSendText) + 1, 0);
	numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
	if (numrcv < 1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// �܂����Ȃ��B
			//printf("�������̐ڑ��l��%s\n", buffer);
		}
		else
		{
			printf("error : 0x%x\n", WSAGetLastError());
		}
	}
	else
	{
		printf("received: �������̐ڑ��l��%s\n", buffer);
	}
	Sleep(1000);
}

void ReceivePacket(void)
{
	char RMsg[BUFFER_SIZE] = { NULL }; //�����Ă���f�[�^���e

	//�펞�󂯎�������B�f�[�^�̕ύX�����������̂݃A�N�Z�X�������A�Ώۃf�[�^�ɏ������݂��s���B
	numrcv = recv(dstSocket, RMsg, BUFFER_SIZE, 0);
	if (numrcv < 1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// �܂����Ȃ��B
			//printf("�������̐ڑ��l��%s\n", buffer);
		}
		else
		{
			//printf("error : 0x%x\n", WSAGetLastError());
		}
	}
	else
	{
			printf("Receive %s\n", RMsg);
	}
}
