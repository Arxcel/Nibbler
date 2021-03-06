#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(std::shared_ptr<Shader> aShader)
{
	mShader = aShader;
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &mQuadVAO);
}

void SpriteRenderer::drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	mShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	mShader->setMat4("model", model);
	mShader->setVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glBindVertexArray(mQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;
	GLfloat vertices[] = {
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &mQuadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(mQuadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::SpriteRenderer()
{

};
SpriteRenderer::SpriteRenderer(SpriteRenderer const &)
{

};
SpriteRenderer &SpriteRenderer::operator=(SpriteRenderer const &)
{
	return *this;
};