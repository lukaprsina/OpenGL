#include "Test.h"
#include "imgui/imgui.h"
#include "Renderer.h"
#include <iostream>

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
		std::cout << "Creating TestMenu\n";
	}

	TestMenu::~TestMenu()
	{
	}


	void TestMenu::OnImGuiRender()
	{
		GLCall(glClearColor(0, 0, 0, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}	
}