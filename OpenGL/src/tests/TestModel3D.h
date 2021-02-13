#pragma once

#include <memory>
#include <array>
#include "glm/gtc/matrix_transform.hpp"

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

struct objFile
{
	std::vector<std::array<float, 3>> vertices;
	std::vector<std::array<unsigned int, 3>> triangles;
};

namespace test {

	class TestModel3D : public Test
	{
	public:
		TestModel3D(const char* name);
		~TestModel3D();

		objFile LoadFromOBJ(const char* filename);

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

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Projection;

		glm::vec3 m_Move;
		glm::vec3 m_Rotate;
		float m_Scale;

		Renderer m_Renderer;
	};
}
