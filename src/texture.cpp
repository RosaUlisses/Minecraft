#include "texture.h"



Texture::Texture(const char* file_path) {
	unsigned char* data = stbi_load(file_path, &width, &height, &channel_count, 0);

	glGenTextures(1, &object_id);
	glBindTexture(GL_TEXTURE_2D, object_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	


	stbi_image_free(data);
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, object_id);
}

void Texture::bind(unsigned int texture) const {
	glActiveTexture(GL_TEXTURE0 + texture);
	glBindTexture(GL_TEXTURE_2D, object_id);
}

int Texture::get_width() const {
	return width;
}


int Texture::get_height() const {
	return height;
}


int Texture::get_channel_count() const {
	return channel_count;
}

unsigned int Texture::get_object_id() const {
	return object_id;
}

void Texture::destroy() {
	glDeleteTextures(1, &object_id);
	object_id = 0;
}


