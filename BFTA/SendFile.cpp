#include "Pch.h"
/* ------------ - Send File to Client-------- */
#define SIZE 1024000


int bytesRead;
char buffer[SIZE];
char FNbuffer[1024];
int send_result;
float s;
bool send_filename = false;

void SendFile(FILE* fp,SOCKET in_soc , float* SendData,int* is_send,std::string filename,long int FS) {

	std::string file_size = std::to_string(FS);
	std::string FNFS = filename + "&$&" + file_size;

	if (fp != NULL)
	{
		send(in_soc, FNFS.c_str(), FNFS.size() + 1, 0);
		do
		{
			ZeroMemory(buffer,SIZE);
			bytesRead = fread(buffer, 1, sizeof(buffer), fp);
			send_result = send(in_soc, buffer, bytesRead, 0);
			if (bytesRead == 0) {
				break;
			}
			s = (bytesRead / (1024000.0));
			*SendData += 1;

		} while (bytesRead > 0);
		closesocket(in_soc);
		*is_send = 1;
	}
	else
	{
		*is_send = 2;
	}
}