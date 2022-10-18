#include "Pch.h"
#include "Usegui.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

 void Usegui::init(GLFWwindow* window) {

	// begin ImGui 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// change font 
	io.Fonts->AddFontFromFileTTF("Poppins-Bold.ttf", 30);

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// this is version of Glad i.e openGL
	ImGui_ImplOpenGL3_Init("#version 330");
	// Setup Dear ImGui style

}
 void Usegui::Frame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
 void Usegui::render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
 void Usegui::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}