#include "Screenshot.h"

char fillchar = '=';
// 00000000001111111111222222
// 01234567890123456789012345

static std::string cvt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// 22223333333333444444444455
// 67890123456789012345678901
"abcdefghijklmnopqrstuvwxyz"
// 555555556666
// 234567890123
"0123456789+/";

Screenshot::Screenshot(std::string dir) {
	dirPath = dir;
}

int Screenshot::GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
	using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;
	
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return 0;
}

void Screenshot::saveJpeg(std::string nameFile) {
	using namespace Gdiplus;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		nameFile = dirPath+"\\" + nameFile + ".jpeg";
		std::wstring wide_string = std::wstring(nameFile.begin(), nameFile.end());
		const wchar_t* result = wide_string.c_str();

		GetEncoderClsid(L"image/jpeg", &clsid);
		bitmap.Save(result, &clsid);

		SelectObject(memdc, hOldBitmap);
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0, scrdc);
	}

	GdiplusShutdown(gdiplusToken);
	std::cout << "Captura" << nameFile <<std::endl;
}

std::string Screenshot::getBase64(std::string nameFile) {
	Sleep(10);
	std::string getDirFile = dirPath + "\\" + nameFile + ".jpeg";
	try {
		std::cout << "Creando codificacion de la captura..." << std::endl;
		std::string encodedString = Screenshot::encodeFromFile(getDirFile);
		return encodedString;
	}
	catch (std::exception& e) {
		std::cout << std::endl << e.what() << std::endl;
	}
	return "empty";
}

std::string Screenshot::encodeFromFile(const std::string& inFileName)
{
	std::ifstream in;
	in.open(inFileName.c_str(), std::ios::binary);
	if (!in.good())
	{
		throw std::invalid_argument(std::string("can't open file ") + inFileName);
	}
	std::vector<char> fBytes;
	while (in.good())
		fBytes.push_back(in.get());
	fBytes.pop_back();
	in.close();

	return Screenshot::encode(fBytes);
}

std::string Screenshot::encode(const std::vector<char>& data)
{
	std::string::size_type  i;
	char               c;
	unsigned int       len = data.size();
	std::string             ret;

	for (i = 0; i < len; ++i)
	{
		c = (data[i] >> 2) & 0x3f;
		ret.append(1, cvt[c]);
		c = (data[i] << 4) & 0x3f;
		if (++i < len)
			c |= (data[i] >> 4) & 0x0f;

		ret.append(1, cvt[c]);
		if (i < len)
		{
			c = (data[i] << 2) & 0x3f;
			if (++i < len)
				c |= (data[i] >> 6) & 0x03;

			ret.append(1, cvt[c]);
		}
		else
		{
			++i;
			ret.append(1, fillchar);
		}

		if (i < len)
		{
			c = data[i] & 0x3f;
			ret.append(1, cvt[c]);
		}
		else
		{
			ret.append(1, fillchar);
		}
	}
	return(ret);
}