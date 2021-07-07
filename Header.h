#pragma once
#include <vector>
#include <string>
#include <fstream>

GLuint _textureID;
using namespace std;
GLuint LoadTGA_custom(const char* tgaPath)
{
	struct PixelData
	{
		uint32_t clr;
		struct
		{
			uint8_t R, G, B, A;
		};
	};

	vector<uint8_t> pixels;
	uint32_t w, h, size, bpp;
	fstream inFile(tgaPath, ios::in | ios::binary);
	if (!inFile.is_open())
	{	//Fungsi Jika File tidak ada
		printf("File Tidak Dapat Ditemukan");
		return 0;
	}
	uint8_t hdr[18] = { 0 };

	vector<uint8_t> colorData;
	inFile.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));	//Fungsi Untuk Menyesuaikan File TGA 
	bpp = hdr[16];
	w = hdr[13] * 256 + hdr[12];
	h = hdr[15] * 256 + hdr[14];
	size = size = ((w * bpp + 31) / 32) * 4 * h;

	if ((bpp != 24) && (bpp != 32))
	{
		inFile.close(); //Fungsi Jika File TGA tidak sesuai
		printf("File TGA Salah");
		return 0;
	}

	colorData.resize(size);
	inFile.read(reinterpret_cast<char*>(colorData.data()), size);
	inFile.close();
	pixels = colorData;
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels.data());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return (0);
}