#include "TextureFile.h"

ID3D11ShaderResourceView *TextureFile::loadTexture(string path, ID3D11Device **dev, int textureType)
{
	if (getFileExtension(path) == "DDS")
	{
		if (DirectX::CreateDDSTextureFromFile(*dev, wstring(path.begin(), path.end()).c_str(), NULL, &sv, NULL, NULL) != S_OK)
		{
			MessageBox(NULL, ("Could not load texture: " + path).c_str(), "Texture Load Error", MB_ICONERROR | MB_OK);
			exit(0);
		}
	}

	else
	{
		string fExtension = getFileExtension(path);
		string pathWithoutExtention = path;
		pathWithoutExtention.erase(pathWithoutExtention.end() - 3, pathWithoutExtention.end());
		
		if (GetFileAttributes((pathWithoutExtention + "dds").c_str()) != INVALID_FILE_ATTRIBUTES)
		{
			pathWithoutExtention += "dds";
			if (DirectX::CreateDDSTextureFromFile(*dev, wstring(pathWithoutExtention.begin(), pathWithoutExtention.end()).c_str(), NULL, &sv, NULL, NULL) != S_OK)
			{
				MessageBox(NULL, ("Could not load texture: " + path).c_str(), "Texture Load Error", MB_ICONERROR | MB_OK);
				exit(0);
			}
		}

		else
		{
			if (textureType == CORE_TEXTURETYPE_2D_BW)
			{
				system(("texconv.exe -f BC4_UNORM_SRGB -ft dds " + path).c_str());
			}

			else if (textureType == CORE_TEXTURETYPE_2D_COLOR)
			{
				system(("texconv.exe -f BC1_UNORM_SRGB -ft dds " + path).c_str());
			}

			else if (textureType == CORE_TEXTURETYPE_2D_NORMAL)
			{
				system(("texconv.exe -f BC1_UNORM_SRGB -ft dds " + path).c_str());
			}

			else if (textureType == CORE_TEXTURETYPE_CUBE)
			{
				system(("texconv.exe -f BC3_UNORM_SRGB -ft dds " + path).c_str());
			}

			if (GetFileAttributes((pathWithoutExtention + "dds").c_str()) != INVALID_FILE_ATTRIBUTES)
			{
				pathWithoutExtention += "dds";
				if (DirectX::CreateDDSTextureFromFile(*dev, wstring(pathWithoutExtention.begin(), pathWithoutExtention.end()).c_str(), NULL, &sv, NULL, NULL) != S_OK)
				{
					MessageBox(NULL, ("Could not load texture: " + path).c_str(), "Texture Load Error", MB_ICONERROR | MB_OK);
					exit(0);
				}
			}
		}
	}

	loaded = true;
	return sv;
}

ID3D11ShaderResourceView * TextureFile::getShaderResourceView()
{
	return sv;
}

TextureFile::TextureFile()
{

}

TextureFile::TextureFile(string path, ID3D11Device **dev, int textureType)
{
	loadTexture(path, dev, textureType);
}

TextureFile::~TextureFile()
{
}
