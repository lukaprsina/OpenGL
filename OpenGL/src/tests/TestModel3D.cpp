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
		: m_Name(name)
	{
		std::vector<double> vertices;
		std::vector<std::array<unsigned int, 3>> triangles;

		GLCall(glEnable(GL_DEPTH_TEST));

		unsigned int vertexCount, triangleCount;

		bool loadedOBJ = LoadFromObjectFile("res/models/custom.obj", vertices, vertexCount,
			triangles, triangleCount);

		if (!loadedOBJ)
		{
			std::cout << "CANNOT LOAD THE OBJECT!\n";
		}

		m_VAO = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(&vertices[0],
			vertexCount * sizeof(std::array<double, 3>));

		VertexBufferLayout layout;
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(&triangles[0][0],
			triangleCount * sizeof(std::array<int, 3>));

		m_Shader = std::make_unique<Shader>("res/shaders/Model3D.shader");
		m_Shader->Bind();

		/* float width = 1280.0f;
		float height = 960.0f;
		
		m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		m_Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); */

		m_Projection = glm::ortho(0.0f, 1280.0f, 0.0f, 960.0f, -1.0f, 1.0f);
	}

	TestModel3D::~TestModel3D()
	{
	}


	bool TestModel3D::LoadFromObjectFile(
		const char* filename,
		std::vector<double>& vertices,
		unsigned int& vertexCount,
		std::vector<std::array<unsigned int, 3>>& triangles,
		unsigned int& triangleCount
	)

	{
		FILE* filePointer;
		errno_t err = fopen_s(&filePointer, filename, "r");

		if (err)
			return false;

		const int bufferLength = 255;
		char buffer[bufferLength];

		if (filePointer)
		{			
			char* next_token = NULL;

			std::array<double, 3> vertex{ 0, 0, 0 };
			std::array<unsigned int, 3> triangle{ 0, 0, 0 };

			vertexCount = 0;
			triangleCount = 0;

			while (fgets(buffer, bufferLength, filePointer)) {

				char* token = strtok_s(&buffer[2], " ", &next_token);

				switch (buffer[0])
				{
				case 'v':
					for (int i = 0; token && i < 3; i++)
					{
						double coord = atof(token);
						vertex[i] = coord;
						token = strtok_s(NULL, " ", &next_token);
						vertexCount++;
					}
					
					vertices.push_back(vertex);
					break;

				case 'f':
					for (int i = 0; token && i < 3; i++)
					{
						unsigned int index = atoi(token);
						triangle[i] = index - 1;
						token = strtok_s(NULL, " ", &next_token);
						triangleCount++;
					}
					
					triangles.push_back(triangle);
					break;
				}				
			}			

			fclose(filePointer);

		}
		return true;
	}

	void TestModel3D::OnUpdate(float deltaTime)
	{

	}

	void TestModel3D::OnRender()
	{		
		 GLCall(glClear(GL_DEPTH_BUFFER_BIT));

		/* const float radius = 40.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		
		m_View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); */

		glm::mat4 mvp = m_Projection; // *m_View* m_Model;
		
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void TestModel3D::OnImGuiRender()
	{
		
	}
}