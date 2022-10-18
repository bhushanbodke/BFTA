#include"Pch.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#pragma comment (lib ,"comdlg32.lib")

const char* FileSelect(GLFWwindow* window)
{
	const char* a = "error in opening file dialog";
	const char* filter = "All\0*.*\0Text\0*.TXT\0";
	OPENFILENAMEA ofn;
	CHAR szfile[4096] = {0};
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize= sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window(window);
	ofn.lpstrFile = szfile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szfile);
	ofn.lpstrFilter = filter; 
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR; 
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile; 
	}
	return a;
}
