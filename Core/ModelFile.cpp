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
		parseCTM(convertToCTM());
	}

	else if (fileExtension == "DAE")
	{
		parseCTM(convertToCTM());
	}

	else if (fileExtension == "MD5")
	{
		parseCTM(convertToCTM());
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
		const CTMfloat *tangents = ctmGetFloatArray(cContext, CTM_ATTRIB_MAP_1);
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

	/*
	Assimp::Importer importer = Assimp::Importer();
	const aiScene *scene = importer.ReadFile(getFilePath(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FindDegenerates);

	if (!scene)
	{
		MessageBox(NULL, ("Error loading model: " + getFilePath() + ": " + importer.GetErrorString()).c_str(), "Model loading error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (scene->HasMeshes())
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			Vertex v;
			const aiVector3D *vertices = scene->mMeshes[i]->mVertices;
			const aiVector3D *texcoords = scene->mMeshes[i]->mTextureCoords[0];
			const aiVector3D *normals = scene->mMeshes[i]->mNormals;
			const aiVector3D *tangents = scene->mMeshes[i]->mTangents;
			const aiFace *faces = scene->mMeshes[i]->mFaces;

			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
			{
				v.position = DirectX::XMFLOAT3(vertices[j].x, vertices[j].y, vertices[j].z);
				v.normal = DirectX::XMFLOAT3(normals[j].x, normals[j].y, normals[j].z);
				v.tangent = DirectX::XMFLOAT3(tangents[j].x, tangents[j].y, tangents[j].z);
				v.uv = DirectX::XMFLOAT2(texcoords[j].x, texcoords[j].y);
			}

			for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; j += 3)
			{
				unsigned int *indices = faces[j].mIndices;
				for (unsigned int k = 0; k < faces[j].mNumIndices; k++)
				{
					mData.indices.push_back(indices[k]);
				}
			}

			mData.vertices.push_back(v);
		}
	}

	CTMuint vCount = mData.vertices.size();
	CTMuint tCount = mData.indices.size() * 3;
	vector<CTMfloat> vert;
	vector<CTMfloat> tan;
	vector<CTMfloat> norm;
	vector<CTMfloat> uv;
	vector<CTMuint> ind;

	for (unsigned int i = 0; i < mData.vertices.size(); i++)
	{
		vert.push_back(mData.vertices[i].position.x);
		vert.push_back(mData.vertices[i].position.y);
		vert.push_back(mData.vertices[i].position.z);
		norm.push_back(mData.vertices[i].normal.x);
		norm.push_back(mData.vertices[i].normal.y);
		norm.push_back(mData.vertices[i].normal.z);
		tan.push_back(mData.vertices[i].tangent.x);
		tan.push_back(mData.vertices[i].tangent.y);
		tan.push_back(mData.vertices[i].tangent.z);
		tan.push_back(0);
		uv.push_back(mData.vertices[i].uv.x);
		uv.push_back(mData.vertices[i].uv.y);
	}

	for (unsigned int i = 0; i < mData.indices.size(); i++)
	{
		ind.push_back(mData.indices[i]);
	}

	CTMcontext ccontext = ctmNewContext(CTM_EXPORT);
	ctmDefineMesh(ccontext, vert.data(), vCount, ind.data(), tCount, norm.data());

	ctmAddUVMap(ccontext, uv.data(), "mainuvmap", NULL);
	ctmAddAttribMap(ccontext, tan.data(), "maintangents");
	ctmSave(ccontext, filePathWithoutExtension.c_str());
	ctmFreeContext(ccontext);
	*/

	system(("ctmconv.exe " + getFilePath() + " " + filePathWithoutExtension).c_str());
	return filePathWithoutExtension;
}

ModelData ModelFile::loadFile(string path)
{
	setFilePath(path);
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
