//#include <stdio.h>
//#include <stdio.h>
//#include <winsock.h>//Windows のソケット関連の定義ファイル
//#pragma comment (lib, "Ws2_32.lib")
//
////STEP1	同端末通信	OK
////STEP2	LAN通信		OK
////STEP3	WAN通信	
//
//char message[1024];
//int main()
//{
//	int sock;
//	struct sockaddr_in sinhim;
//	short port = 27015;
//	//char IPaddress[1024] = { "192.168.11.26" };
//	char IPaddress[1024] = { "202.231.97.24" };
//	//以下 2 行は WindowsOS でのみ必要となる部分:socket 利用の宣言（DLL 利用の宣言）
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(1, 1), &wsaData);
//	//アドレス情報の設定
//	sinhim.sin_family = AF_INET;
//	sinhim.sin_port = htons(port);						//ポート番号の指定
//	sinhim.sin_addr.s_addr = inet_addr(IPaddress);		//宛先指定
//
//	//ソケット生成 UDP
//	sock = socket(AF_INET, SOCK_DGRAM, 0);
//	//送信宛先のアドレス・ポート指定、UDP の場合には接続処理が行われるわけではない。
//	connect(sock, (struct sockaddr*)&sinhim,sizeof(struct sockaddr_in));
//	printf("Input Message:");
//	gets_s(message);
//	//message 文字列（ヌル文字含む）の送信
//	send(sock, message, strlen(message) + 1, 0);
//	getchar();
//	return 0;
//}