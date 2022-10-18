#include "Pch.h"
#include"glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Usegui.h"
#include "Core.h"
#include <future>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>



std::string getFileName(const char* file_path)
{
	std::experimental::filesystem::path p (file_path);
	std::string fn = p.filename().string();
	return fn;
}


int main() {
	glfwInit();
	// specify version of opengl 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// which set of function pointers
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create window
	GLFWwindow* window = glfwCreateWindow(500, 900, "GLFW", NULL, NULL);
	// check window was created
	if (window == NULL) {
		std::cout << "failed to intialize window" << std::endl;
		return 1;
	}
	// make use of that window

	glfwMakeContextCurrent(window);

	// load opend gl pointers 
	// always after make context current 

	gladLoadGL();
	// Glad stuff to change the color
	Usegui I;
	I.init(window);
	glViewport(0, 0, 800, 800);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// ----------------------- Variables -----------------------------
	float spacing = 25.0f;
	float SendData = 0;
	std::future<SOCKET> t1;
	std::future<void> t2;
	bool StartServer = false;
	bool SelectFile = false;
	bool IsConnected = false;
	std::string fileName;
	SOCKET in_soc = NULL;
	FILE* fp = NULL;
	int is_send = 0;

	//--------------------------- Main Loop ---------------------------

	while (!glfwWindowShouldClose(window))
	{
		// which buffer Bit to use 
		glClear(GL_COLOR_BUFFER_BIT);

		// ImGui creating new frame 
		I.Frame();
		ImGui::SetNextWindowSize(ImVec2(500, 900));
		ImGui::SetNextWindowPos(ImVec2(0,0));

		//File handel ;
		const char* file_path = "";

		//  ------------------ Start ImGui Window -----------------------
		ImGui::Begin("Start server", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Dummy(ImVec2(0.0f, 15));

		if (!StartServer) {
			ImGui::Text("1 ) Start Server First Before Opening File ");
		}
		else {
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f),"1 ) Server Started :)");
		}
		ImGui::SetCursorPos(ImVec2(150,125));
		if (ImGui::Button("Start Server"))
		{
			std::cout << "[+] Server Started" << std::endl;
			t1 = std::async(std::launch::async, server,&IsConnected);
			StartServer = true;
		};
		ImGui::Dummy(ImVec2(0.0f, spacing));

		if (!IsConnected) {
			ImGui::Text("2 ) Connect client device");
		}
		else {
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f), "2 ) Connected :)");
		}
		ImGui::Dummy(ImVec2(0.0f, spacing));

		if (SelectFile) {
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f), "3 ) Selected File :) ");
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f), fileName.c_str());
		}
		else {
			ImGui::Text("3 ) Select File");
		}

		ImGui::SetCursorPos(ImVec2(150,355));

		if (ImGui::Button("Openfile") && StartServer)
		{
			// Open File Select dialog
			file_path = FileSelect(window);
			//get File name form path 
			if (file_path != "") {
				errno_t err = fopen_s(&fp, file_path, "rb");
				std::cout << fp << std::endl;
				if (err != 0) {
					std::cerr << "[-] Error in reading the file" << std::endl;
					return 1;
				}
				else
				{
					std::cout << "[+] File opend" << std::endl;
				}
				fileName = getFileName(file_path);
				std::cout << fileName.c_str() << std::endl;
				SelectFile = true;
			}
		};
		ImGui::Dummy(ImVec2(0.0f, spacing));

		
		ImGui::Dummy(ImVec2(0.0f, spacing));
		ImGui::Text("4 ) Select File");

		ImGui::SetCursorPos(ImVec2(150, 500));

		if(ImGui::Button("SendFile")&&SelectFile)
		{
			in_soc = t1.get();
			t2 = std::async(std::launch::async , SendFile,fp,in_soc,&SendData,&is_send);
			std::cout << "SendFile " << send << std::endl;
		}
		ImGui::Dummy(ImVec2(0.0f, spacing));
		if (SendData > 0.0000) {
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f),std::to_string(SendData).c_str());
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.027f, 0.988f, 0.11f, 1.0f),"  Mb Send");
		}
		if (is_send == 1) {
			ImGui::TextColored(ImVec4(0.027f,0.988f,0.11f,1.0f), "File Send Succesfully");
		}
		if (is_send == 2) {
			ImGui::Text("some error in sending");

		}


		ImGui::End();

		// Render ImGui 
		I.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// shut down GLFW and ImGui
	I.destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}
