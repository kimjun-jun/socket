//#include <stdio.h>
//#include <stdio.h>
//#include <winsock.h>//Windows �̃\�P�b�g�֘A�̒�`�t�@�C��
//#pragma comment (lib, "Ws2_32.lib")
//
////STEP1	���[���ʐM	OK
////STEP2	LAN�ʐM		OK
////STEP3	WAN�ʐM	
//
//char message[1024];
//int main()
//{
//	int sock;
//	struct sockaddr_in sinhim;
//	short port = 27015;
//	//char IPaddress[1024] = { "192.168.11.26" };
//	char IPaddress[1024] = { "202.231.97.24" };
//	//�ȉ� 2 �s�� WindowsOS �ł̂ݕK�v�ƂȂ镔��:socket ���p�̐錾�iDLL ���p�̐錾�j
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(1, 1), &wsaData);
//	//�A�h���X���̐ݒ�
//	sinhim.sin_family = AF_INET;
//	sinhim.sin_port = htons(port);						//�|�[�g�ԍ��̎w��
//	sinhim.sin_addr.s_addr = inet_addr(IPaddress);		//����w��
//
//	//�\�P�b�g���� UDP
//	sock = socket(AF_INET, SOCK_DGRAM, 0);
//	//���M����̃A�h���X�E�|�[�g�w��AUDP �̏ꍇ�ɂ͐ڑ��������s����킯�ł͂Ȃ��B
//	connect(sock, (struct sockaddr*)&sinhim,sizeof(struct sockaddr_in));
//	printf("Input Message:");
//	gets_s(message);
//	//message ������i�k�������܂ށj�̑��M
//	send(sock, message, strlen(message) + 1, 0);
//	getchar();
//	return 0;
//}