#pragma once

#include "Test.h"
#include <memory>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D(const char* name);
		~TestTexture2D();

		inline const char* GetName() { return m_Name; };

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		const char* m_Name;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
}