#pragma once

#include <functional>
#include <vector>
#include <iostream>

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual const char* GetName() = 0;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}		
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();	

		inline const char* GetName() override { return "Testing Framework"; };

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const char* name)
		{
			std::cout << "Registering test " << name << '\n';
			m_Tests.push_back(std::make_pair(name, [name]() { return new T(name); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}