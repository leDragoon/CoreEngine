#include "Scene.h"

void Scene::load()
{
	SceneFile sceneFile(filePath);
	vector<ObjectInstance> objectInstances = sceneFile.getObjectInstances();
	sceneName = sceneFile.getSceneName();

	for (unsigned int i = 0; i < objectInstances.size(); i++)
	{
		if (objectInstances[i].type == CORE_DRAWABLETYPE_MODEL)
		{
			Model toAdd;
			toAdd.setPosition(objectInstances[i].position);
			toAdd.setRotation(objectInstances[i].rotation);
			toAdd.setScale(objectInstances[i].scale);
			toAdd.setName(objectInstances[i].objectName);
			toAdd.setIdentifier(objectInstances[i].identifier);
			toAdd.setVertexShader("mainVertexShader");
			toAdd.setPixelShader("mainPixelShader");
			
			for (unsigned int j = 0; j < sceneAssetList.modelNames.size(); j++)
			{
				if (toAdd.getName() == sceneAssetList.modelNames[j])
				{
					toAdd.loadVertices(sceneAssetList.modelPaths[i]);
				}
			}

			sceneModels.push_back(toAdd);
		}
	}

	for (unsigned int i = 0; i < sceneAssetList.vertexShaderNames.size(); i++)
	{
		VertexShader shader;
		shader.setName(sceneAssetList.vertexShaderNames[i]);
		shader.setFilePath(sceneAssetList.vertexShaderPaths[i]);
		renderer.add(shader);
	}

	for (unsigned int i = 0; i < sceneAssetList.pixelShaderNames.size(); i++)
	{
		PixelShader shader;
		shader.setName(sceneAssetList.pixelShaderNames[i]);
		shader.setFilePath(sceneAssetList.pixelShaderPaths[i]);
		renderer.add(shader);
	}

	for (unsigned int i = 0; i < sceneModels.size(); i++)
	{
		renderer.add(&sceneModels[i]);
	}

	renderer.loadAllShaders();
	renderer.loadAllModels();
}

void Scene::load(string FilePath)
{
	filePath = FilePath;
	load();
}

void Scene::load(string FilePath, string assetListFilePath)
{
	filePath = FilePath;
	AssetListFile aListFile(assetListFilePath);
	sceneAssetList = aListFile.getAssetList();
	load();
}

void Scene::load(string FilePath, AssetList assetList)
{
	filePath = FilePath;
	sceneAssetList = assetList;
	load();
}

void Scene::load(string FilePath, AssetList assetList, AssetList * globalList)
{
	filePath = FilePath;
	sceneAssetList = assetList;
	globalAssetList = globalAssetList;
	load();
}

void Scene::load(string FilePath, string assetListFilePath, AssetList * globalList)
{
	filePath = FilePath;
	AssetListFile aListFile(assetListFilePath);
	sceneAssetList = aListFile.getAssetList();
	globalAssetList = globalList;
	load();
}

void Scene::unloadAssets()
{
	for (unsigned int i = 0; i < sceneModels.size(); i++)
	{
		sceneModels[i].close();
	}
}

void Scene::unload()
{
	for (unsigned int i = 0; i < sceneModels.size(); i++)
	{
		sceneModels[i].close();
	}
}

void Scene::setGlobalAssetList(AssetList * globalList)
{
	globalAssetList = globalList;
}

void Scene::setAssetList(AssetList toSet)
{
	sceneAssetList = toSet;
}

void Scene::setRenderer(Renderer *toSet)
{
	renderer = *toSet;
}

Renderer * Scene::getRenderer()
{
	return nullptr;
}

AssetList Scene::getAssetList()
{
	return AssetList();
}

void Scene::setFilePath(string filePath)
{
}

string Scene::getFilePath()
{
	return string();
}

void Scene::getModel(string modelName)
{

}

Model * Scene::getModelArray()
{
	return nullptr;
}

void Scene::setSceneType(int typeToSet)
{

}

int Scene::getSceneType()
{
	return 0;
}

void Scene::add(Drawable toAdd)
{

}

void Scene::add(Shader * toAdd)
{

}

Scene::Scene()
{

}

Scene::Scene(string filePath)
{
	load(filePath);
}

Scene::Scene(string filePath, string assetListFilePath)
{
	load(filePath, assetListFilePath);
}

Scene::Scene(string filePath, AssetList assetList)
{
	load(filePath, assetList);
}

Scene::Scene(string filePath, AssetList assetList, AssetList * globalList)
{
	load(filePath, assetList, globalList);
}

Scene::Scene(string filePath, string assetListFilePath, AssetList * globalList)
{
	load(filePath, assetListFilePath, globalList);
}

Scene::~Scene()
{

}
