#include "ModelFile.h"

void ModelFile::parse()
{
	if (fileExtension == "CTM")
	{
		parseCTM();
	}

	else if (fileExtension == "OBJ")
	{
		parseCTM(convertToCTM());
	}

	else if (fileExtension == "FBX")
	{
		
	}

	else if (fileExtension == "DAE")
	{
		parseCTM(convertToCTM());
	}

	else if (fileExtension == "MD5")
	{
		
	}
}

void ModelFile::parseCTM()
{
	parseCTM(getFilePath().c_str());
}

void ModelFile::parseCTM(string path)
{
	CTMcontext cContext;
	cContext = ctmNewContext(CTM_IMPORT);
	ctmLoad(cContext, path.c_str());

	if (ctmGetError(cContext) == CTM_NONE)
	{
		CTMuint vertCount = ctmGetInteger(cContext, CTM_VERTEX_COUNT);
		CTMuint triCount = ctmGetInteger(cContext, CTM_TRIANGLE_COUNT);
		const CTMfloat *vertices = ctmGetFloatArray(cContext, CTM_VERTICES);
		const CTMfloat *normals = ctmGetFloatArray(cContext, CTM_NORMALS);
		const CTMfloat *uvs = ctmGetFloatArray(cContext, CTM_UV_MAP_1);
		const CTMuint *indices = ctmGetIntegerArray(cContext, CTM_INDICES);
		CTMuint onVert = 0;
		CTMuint onUv = 0;

		for (unsigned int i = 0; i < vertCount; i++)
		{
			Vertex v;
			v.position.x = vertices[onVert];
			v.position.y = vertices[onVert + 1];
			v.position.z = vertices[onVert + 2];
			v.normal.x = normals[onVert];
			v.normal.y = normals[onVert + 1];
			v.normal.z = normals[onVert + 2];
	 		v.uv.x = uvs[onUv];
			v.uv.y = uvs[onUv + 1];
			onVert += 3;
			onUv += 2;
			mData.vertices.push_back(v);
		}

		for (unsigned int i = 0; i < triCount * 3; i++)
		{
			mData.indices.push_back(indices[i]);
		}
	}

	else
	{
		MessageBox(NULL, ("Could not import model: " + getFilePath()).c_str(), "Model Loading Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	ctmFreeContext(cContext);
}

string ModelFile::convertToCTM()
{
	string filePathWithoutExtension = getFilePath();
	filePathWithoutExtension.erase(filePathWithoutExtension.end() - 3, filePathWithoutExtension.end());
	filePathWithoutExtension += "ctm";
	std::ifstream fin(filePathWithoutExtension.c_str());
	if (!fin.fail())
	{
		return filePathWithoutExtension;
	}
	system(("ctmconv " + getFilePath() + " " + filePathWithoutExtension).c_str());
	return filePathWithoutExtension;
}

ModelData ModelFile::loadFile(string path)
{
	load(path);
	fileExtension = getFileExtension();
	parse();
	return mData;
}

ModelFile::ModelFile()
{

}

ModelFile::ModelFile(string path)
{
	loadFile(path);
}
