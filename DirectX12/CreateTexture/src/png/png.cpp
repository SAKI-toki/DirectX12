#include "png.h"

//Pngファイルの読み込み
bool PngApp(const char* path)
{
	ConsoleComment("Png");
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	int  x, y;
	int width, height;
	png_structp png = NULL;
	png_infop info = NULL;
	png_bytep row;
	png_bytepp rows;
	png_byte sig_bytes[PNG_SIG_SIZE];
	//ファイルの読み込み
	if (fread(sig_bytes, sizeof(sig_bytes), 1, fp) != 1)
	{
		return false;
	}
	//PNGかどうか判定
	if (png_sig_cmp(sig_bytes, 0, sizeof(sig_bytes)))
	{
		return false;
	}
	try
	{
		png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (png == NULL)
		{
			throw 0;
		}
		info = png_create_info_struct(png);
		if (info == NULL)
		{
			throw 0;
		}
		if (setjmp(png_jmpbuf(png)))
		{
			throw 0;
		}
		png_init_io(png, fp);
		png_set_sig_bytes(png, sizeof(sig_bytes));
		png_read_png(png, info, PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, NULL);
		width = png_get_image_width(png, info);
		height = png_get_image_height(png, info);
		rows = png_get_rows(png, info);
		png_byte color_type = png_get_color_type(png, info);
		if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGB_ALPHA)
		{
			ConsoleComment("カラータイプが対応していません");
			throw 0;
		}
		ConsoleComment("幅:", width, "px");
		ConsoleComment("高さ:", height, "px");
		OutputType color(height, std::vector<Color4>(width));
		std::cout << "カラータイプ:";
		//画像形式に応じて詰め込み
		switch (png_get_color_type(png, info))
		{
		case PNG_COLOR_TYPE_RGB:  // RGB
			ConsoleComment("RGB");
			for (y = 0; y < height; y++)
			{
				row = rows[y];
				for (x = 0; x < width; x++)
				{
					color[y][x].b = *row++;
					color[y][x].g = *row++;
					color[y][x].r = *row++;
					color[y][x].a = 0xff;
				}
			}
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:  // RGBA
			ConsoleComment("RGB_ALPHA");
			for (y = 0; y < height; y++)
			{
				row = rows[y];
				for (x = 0; x < width; x++)
				{
					color[y][x].b = *row++;
					color[y][x].g = *row++;
					color[y][x].r = *row++;
					color[y][x].a = *row++;
				}
			}
			break;
		}

		OutputFile(color, width, height);
	}
	catch (...)
	{
		png_destroy_read_struct(&png, &info, NULL);
		return false;
	}
	png_destroy_read_struct(&png, &info, NULL);


	return true;
}