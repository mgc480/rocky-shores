//Loader.h / Loader.cpp
//used as a universal loading system to loader every file type
//-mgc480

#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iostream>
#include "Defaults.h"
#include <gl\glew.h>
#include <gl\glfw.h>

class Loader{
public:
	Loader(void);
	~Loader(void);

	Defaults::Status loadRes(std::string path);    //load a .res file (file that lists resourses) and load each

	Defaults::Status loadTga(std::string path);    //load a tga and put it in the loader texture map
	static Defaults::Status loadTga(std::string path, GLuint * index);    //load a tga file and puts its index in the second param

	//Defaults::Status loadBmp(std::string path);    //load a bmp image file into opengl and add its index to the texture list
	static Defaults::Status loadBmp(std::string path, GLuint * index);	//load a bmp image into opengl and set var index to its index

	void setMipmap(GLenum min, GLenum max);    //sets the mipmap for all textures loaded

private:
	std::map<std::string, GLuint> textures;

	//static GLenum minFilter, maxFilter;

};

