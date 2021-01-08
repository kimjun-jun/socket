#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#define BUFFER_SIZE 100

//STEP1	同端末通信	OK
//STEP2	LAN通信		
//STEP3	WAN通信	

using namespace std;


//////////////////////////////////////////////////////////

int NetClientSocketCreate();
void Packet();
void SendPacket(int i);
void ReceivePacket();

//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
/* IP アドレス、ポート番号、ソケット */
char destination[80];
unsigned short port = 27015;
int dstSocket;

/* sockaddr_in 構造体 */
struct sockaddr_in dstAddr;

/* 各種パラメータ */
int numrcv;
char buffer[BUFFER_SIZE]; //送られてくるデータ内容
char toSendText[1024] = "1";
int status;
//////////////////////////////////////////////////////////


int main() 
{

	NetClientSocketCreate();
		
	//マルチスレッドで受信プログラム(受信関数)起動　細かく通信する　1/60じゃない　関数一つで出来る
	//マルチスレッド開始
	std::thread t1(Packet);

	while (1)
	{

	}

	/* Windows 独自の設定 */
	closesocket(dstSocket);
	WSACleanup();

	return 0;
}

int NetClientSocketCreate(void)
{
	/* Windows 独自の設定 */
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* 相手先アドレスの入力 */
	//printf("Connect to ? : (name or IP address) ");
	//gets_s(destination);

	sprintf_s(destination, "192.168.11.3");

	/* sockaddr_in 構造体のセット */
	memset(&dstAddr, 0, sizeof(dstAddr));
	inet_pton(AF_INET, destination, &dstAddr.sin_addr);
	dstAddr.sin_port = htons(port);
	dstAddr.sin_family = AF_INET;

	/* ソケット生成 */
	dstSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* 接続 */
	printf("Trying to connect to %s: \n", destination);
	connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));

	// ここで、ノンブロッキングに設定しています。
	 // val = 0でブロッキングモードに設定できます。
	 // ソケットの初期設定はブロッキングモードです。
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
	/* パケット送出 */
	printf("Send回数%d\n",i+1);
	send(dstSocket, toSendText, strlen(toSendText) + 1, 0);
	numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
	if (numrcv < 1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// まだ来ない。
			//printf("ただ今の接続人数%s\n", buffer);
		}
		else
		{
			printf("error : 0x%x\n", WSAGetLastError());
		}
	}
	else
	{
		printf("received: ただ今の接続人数%s\n", buffer);
	}
	Sleep(1000);
}

void ReceivePacket(void)
{
	char RMsg[BUFFER_SIZE] = { NULL }; //送られてくるデータ内容

	//常時受け取りをする。データの変更があった時のみアクセス許可を取り、対象データに書き込みを行う。
	numrcv = recv(dstSocket, RMsg, BUFFER_SIZE, 0);
	if (numrcv < 1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// まだ来ない。
			//printf("ただ今の接続人数%s\n", buffer);
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
