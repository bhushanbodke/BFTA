#pragma once
#include"Pch.h"

SOCKET server(bool* IsConnected);
void SendFile(FILE* fp, SOCKET in_soc, float* SendData,int* is_send);
const char* FileSelect(GLFWwindow* window);