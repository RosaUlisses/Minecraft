#ifndef  TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>


class Texture {
	// Image dimensions and data.
	int width, height, channel_count;
	// The texture ID, used in OpenGL functions.
	unsigned int object_id;

	public:
		// Constructor that reads a texture from a file.
		Texture(const char* file_path);

		// Bind this texture as GL_TEXTURE0.
		void bind() const;
		// Bind this texture to the specified texture unit.
		void bind(unsigned int texture) const;
		// Get image width
		int get_width() const;
		// Get image height
		int get_height() const;
		// Get number of 8-bit channels per pixel
		int get_channel_count() const;
		// Get this object's ID
		unsigned int get_object_id() const;
		// Destroy this texture.
		void destroy();
};

#endif