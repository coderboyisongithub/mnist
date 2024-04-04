#pragma once
#include <string>
#include <vector>
#include <filesystem>



/*
*....LABLE FILE.idx1
* [offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number (MSB first)
0004     32 bit integer  60000            number of items
0008     unsigned byte   ??               label
0009     unsigned byte   ??               label
........
xxxx     unsigned byte   ??               label
The labels values are 0 to 9.
	*/



class synapse_mnist
{

	std::vector<unsigned char*>images,lables;
	int magic_number, total_images, row, col;
	int lable_magic_number, total_lables;


	static int big2little(int big)
	{
		int little = (big & 0xFF000000) >> 24;
		little = (big & 0x00FF0000) >> 8 | little;
		little = (big & 0x0000FF00) << 8 | little;
		little = (big & 0x000000FF) << 24 | little;
		return little;
	}
public:
	synapse_mnist()
	{

	}

	void load(std::string imagepath, std::string lablepath);
	std::pair<unsigned char*, unsigned char*>operator [] (long int idx);
	std::pair<int, int> getsize();
	
};


void synapse_mnist::load(std::string imagepath, std::string lablepath)
{
	FILE* fp = 0;

	fopen_s(&fp, imagepath.c_str(), "rb");
	_ASSERT(fp != NULL);
	fread(&magic_number, sizeof(int), 1, fp);
	fread(&total_images, sizeof(int), 1, fp);
	fread(&row, sizeof(int), 1, fp);
	fread(&col, sizeof(int), 1, fp);

	magic_number = big2little(magic_number);
	total_images = big2little(total_images);
	row = big2little(row);
	col = big2little(col);

	while (1)
	{
		if (!feof(fp))
		{
			unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * 784);
			fread(buffer, sizeof(unsigned char), 784, fp);
			images.push_back(buffer);

		}
		else
			break;


	}

	images.pop_back();//remove last extra, buggy
	//_ASSERT(images.size() == total_images);//there is one extra image?

	fclose(fp);

	fopen_s(&fp, lablepath.c_str(), "rb");
	_ASSERT(fp != NULL);
	fread(&lable_magic_number, sizeof(int), 1, fp); lable_magic_number = big2little(lable_magic_number);
	fread(&total_lables, sizeof(int), 1, fp); total_lables = big2little(total_lables);
	while (1)
	{
		if (!feof(fp))
		{
			unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char));
			fread(buffer, sizeof(unsigned char), 1, fp);

			lables.push_back(buffer);
			

		}
		else
			break;

	}
	lables.pop_back();
	fclose(fp);





}
std::pair<unsigned char*, unsigned char*>synapse_mnist::operator [] (long int idx)
{
	return std::pair(images[idx], lables[idx]);
}
/// <returns>total data samples.</returns>
std::pair<int, int>synapse_mnist::getsize()
{
	return std::pair(images.size(),lables.size());
}


