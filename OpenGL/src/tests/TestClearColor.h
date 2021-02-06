#pragma once

#include "Test.h"

namespace test {

	class TestClearColor : public Test
	{
	public:
		TestClearColor(const char* name);
		~TestClearColor();

		inline const char* GetName() { return m_Name; };

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		const char* m_Name;
		float m_ClearColor[4];
	};
}