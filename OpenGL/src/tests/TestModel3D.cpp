#include "TestModel3D.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "imgui/imgui.h"
#include "GLFW/glfw3.h"

namespace test {
	TestModel3D::TestModel3D(const char* name)
		: m_Name(name), m_Move(0.0f, 0.0f, -100.0f), m_Scale(5.0f)
	{
		std::vector<std::array<float, 3>> vertices;
		std::vector<std::array<unsigned int, 3>> triangles;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		objFile mesh = LoadFromOBJ("res/models/ico.obj");

		m_VAO = std::make_unique<VertexArray>();

		int vertexSize = sizeof(std::array<float, 3>);

		m_VBO = std::make_unique<VertexBuffer>(&mesh.vertices[0][0],
			mesh.vertices.size() * vertexSize);

		VertexBufferLayout layout;
		layout.Push<float>(3);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(&mesh.triangles[0][0],			
			mesh.triangles.size() * 3);

		m_Shader = std::make_unique<Shader>("res/shaders/Model3D.shader");
		m_Shader->Bind();		

		float width = 1280.0f;
		float height = 960.0f;

		float fov = 110.0f;
		float zNear = 0.1f;
		float zFar = 200.0f;
		
		m_Projection = glm::perspective(glm::radians(fov), (float)width / (float)height, zNear, zFar);
	}

	TestModel3D::~TestModel3D()
	{
	}


	objFile TestModel3D::LoadFromOBJ(const char* filename)

	{
		FILE* filePointer;
		errno_t err = fopen_s(&filePointer, filename, "r");

		struct objFile model = { {}, {} };
		if (err)
			return model;

		const int bufferLength = 255;
		char buffer[bufferLength];

		if (filePointer)
		{			
			char* next_token = NULL;

			std::array<float, 3> vertex{ 0, 0, 0 };
			std::array<unsigned int, 3> triangle{ 0, 0, 0 };

			while (fgets(buffer, bufferLength, filePointer)) {

				char* token = strtok_s(&buffer[2], " ", &next_token);

				switch (buffer[0])
				{
				case 'v':
					for (int i = 0; token && i < 3; i++)
					{
						float coord = (float)atof(token);
						vertex[i] = coord;
						token = strtok_s(NULL, " ", &next_token);
					}
					
					model.vertices.push_back(vertex);
					break;

				case 'f':
					for (int i = 0; token && i < 3; i++)
					{
						unsigned int index = atoi(token);
						triangle[i] = index - 1;
						token = strtok_s(NULL, " ", &next_token);
					}
					
					model.triangles.push_back(triangle);
					break;
				}				
			}			

			fclose(filePointer);

		}
		return model;
	}

	void TestModel3D::OnUpdate(float deltaTime)
	{

	}

	void TestModel3D::OnRender()
	{		
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 trans(1.0f);
		trans = glm::scale(trans, glm::vec3(m_Scale, m_Scale, m_Scale));
		trans = glm::rotate(trans, glm::radians(m_Rotate.x), glm::vec3(1.0, 0.0, 0.0));
		trans = glm::rotate(trans, glm::radians(m_Rotate.y), glm::vec3(0.0, 1.0, 0.0));
		m_Model = glm::rotate(trans, glm::radians(m_Rotate.z), glm::vec3(0.0, 0.0, 1.0));
		
		m_View = glm::translate(glm::mat4(1.0f), m_Move);

		glm::mat4 mvp = m_Projection * m_View * m_Model;
		
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void TestModel3D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Move", &m_Move.x, -100.0f, 100.0f);
		ImGui::SliderFloat3("Rotate", &m_Rotate.x, 0.00f, 360.0f);
		ImGui::SliderFloat("Scale", &m_Scale, 0.01f, 50.0f);
	}
}