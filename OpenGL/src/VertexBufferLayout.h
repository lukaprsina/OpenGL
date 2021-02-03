#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalised;

	static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<float>(unsigned int count);

	template<>
	void Push<unsigned int>(unsigned int count);

	template<>
	void Push<unsigned char>(unsigned int count);

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }

private:

	unsigned int m_Stride;
	
	std::vector<VertexBufferElement> m_Elements;
};