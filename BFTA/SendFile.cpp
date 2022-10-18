#include "Pch.h"
/* ------------ - Send File to Client-------- */
#define SIZE 1024000
int bytesRead;
char buffer[SIZE];
int send_result;
float s; 
void SendFile(FILE* fp,SOCKET in_soc , float* SendData,int* is_send) {
	if (fp != NULL)
	{
		do
		{
			ZeroMemory(buffer,SIZE);
			bytesRead = fread(buffer, 1, sizeof(buffer), fp);
			if (bytesRead <= 0) {
				break;
			}
			send_result = send(in_soc, buffer, sizeof(buffer), 0);
			s = (bytesRead / (1024000.0));
			*SendData += floorf(s * 100) / 100;

		} while (bytesRead > 0);
		*is_send = 1;
	}
	else
	{
		*is_send = 2;
	}
}