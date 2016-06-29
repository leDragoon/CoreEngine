#include "Scene.h"

void Scene::load()
{
	SceneFile sceneFile(filePath);
	vector<ObjectInstance> objectInstances = sceneFile.getObjectInstances();
	sceneName = sceneFile.getSceneName();

	Model skyModel;
	skyModel.setPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	skyModel.setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	skyModel.setScale(XMFLOAT3(100.0f, 100.0f, 100.0f));
	skyModel.setName("skyModel");
	skyModel.setVertexShader("mainVertexShader");
	skyModel.setPixelShader("skyPixelShader");
	skyModel.loadData("Data//Models//cube.obj");

	quadModel.setPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	quadModel.setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	quadModel.setScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
	quadModel.setName("quadModel");
	quadModel.setVertexShader("quadVertexShader");
	quadModel.setPixelShader("postFXPixelShader");
	quadModel.loadData("Data//Models//quad.obj");
	
	sceneModels.push_back(skyModel);
	
	backBuffer.setResource(NULL);
	backBuffer.setName("backBuffer");

	for (unsigned int i = 0; i < sceneAssetList.cameraNames.size(); i++)
	{
		Camera camera;

		for (unsigned int j = 0; j < objectInstances.size(); j++)
		{
			if (objectInstances[j].objectName == sceneAssetList.cameraNames[i])
			{
				camera.setPosition(objectInstances[j].position);
				camera.setRotation(objectInstances[j].rotation);
				camera.setName(objectInstances[j].objectName);
				camera.setFieldOfView(45);
			}
		}

		vector<int> c;
		c.push_back(0);
		sceneCamera = camera;
	}

	renderer->add(&sceneCamera);
	renderer->resize(renderer->getSize().x, renderer->getSize().y);

	WindowStyle ws;

	for (unsigned int i = 0; i < objectInstances.size(); i++)
	{
		if (objectInstances[i].type == CORE_OBJECTTYPE_MODEL)
		{
			Model toAdd;
			toAdd.setPosition(objectInstances[i].position);
			toAdd.setRotation(objectInstances[i].rotation);
			toAdd.setScale(objectInstances[i].scale);
			toAdd.setName(objectInstances[i].objectName);

			toAdd.setIdentifier(objectInstances[i].identifier);
			toAdd.setVertexShader("mainVertexShader");
			toAdd.setPixelShader("mainPixelShader");
			toAdd.setScripts(objectInstances[i].scripts);
			
			for (unsigned int j = 0; j < sceneAssetList.modelNames.size(); j++)
			{
				if (toAdd.getName() == sceneAssetList.modelNames[j])
				{
					toAdd.loadData(sceneAssetList.modelPaths[j]);
				}
			}

			sceneModels.push_back(toAdd);
		}

		else if (objectInstances[i].type == CORE_OBJECTTYPE_LIGHTPROBE)
		{
			if (GetFileAttributes(("Data//Textures//" + objectInstances[i].objectName + ".DDS").c_str()) == INVALID_FILE_ATTRIBUTES)
			{
				renderer->captureLightProbe(256, objectInstances[i].position, "Data//Textures//" + objectInstances[i].objectName + ".DDS");
			}
		}
	}

	for (unsigned int i = 0; i < sceneAssetList.vertexShaderNames.size(); i++)
	{
		VertexShader shader;
		shader.setName(sceneAssetList.vertexShaderNames[i]);
		shader.setFilePath(sceneAssetList.vertexShaderPaths[i]);
		renderer->add(shader);
	}
	
	for (unsigned int i = 0; i < sceneAssetList.pixelShaderNames.size(); i++)
	{
		PixelShader shader;
		shader.setName(sceneAssetList.pixelShaderNames[i]);
		shader.setFilePath(sceneAssetList.pixelShaderPaths[i]);
		renderer->add(shader);
	}

	for (unsigned int i = 0; i < sceneAssetList.lightNames.size(); i++)
	{
		LightFile lData;
		Light light = lData.loadLightFile(sceneAssetList.lightPaths[i]);
		renderer->add(light);
	}

	for (unsigned int i = 0; i < sceneAssetList.textureNames.size(); i++)
	{
		Texture tex;
		tex.loadFromFile(sceneAssetList.texturePaths[i], renderer->getDevice());
		tex.setName(sceneAssetList.textureNames[i]);
		renderer->add(tex);

		if (tex.getName() == "windowEdge")
		{
			ws.verticalEdge = tex;
		}
	}

	for (unsigned int i = 0; i < sceneAssetList.materialNames.size(); i++)
	{
		Material mat;
		mat.loadMaterial(sceneAssetList.materialPaths[i], renderer->getDevice());
		renderer->add(mat);
	}

	for (unsigned int i = 0; i < sceneAssetList.soundNames.size(); i++)
	{
		audioHandler->addSound(sceneAssetList.soundPaths[i], sceneAssetList.soundNames[i]);
	}

	for (unsigned int i = 0; i < sceneAssetList.scriptNames.size(); i++)
	{
		scriptHandler->addScriptFromFile(sceneAssetList.scriptNames[i], sceneAssetList.scriptPaths[i]);
	}

	for (unsigned int i = 0; i < sceneAssetList.guiLayoutNames.size(); i++)
	{
		GuiLayout gLayout;
		UserInterfaceFile guiFile;
		gLayout = guiFile.loadUserInterfaceLayout(sceneAssetList.guiLayoutPaths[i]);

		for (unsigned int j = 0; j < sceneAssetList.fontNames.size(); j++)
		{
			GuiFont fnt;
			fnt.setName(sceneAssetList.fontNames[j]);

			for (unsigned int k = 0; k < sceneAssetList.fontTextures[j].size(); k++)
			{
				fnt.addFontSheet(sceneAssetList.fontTextures[j][k]);
			}

			fnt.loadFromFile(sceneAssetList.fontFiles[j]);
			gLayout.fonts.push_back(fnt);
		}

		for (unsigned int j = 0; j < gLayout.windows.size(); j++)
		{
			gLayout.windows[j].addTexture(&backBuffer);
			gLayout.windows[j].setCurrentTexture("backBuffer");

			for (unsigned int k = 0; k < sceneAssetList.textureNames.size(); k++)
			{
				if (sceneAssetList.textureNames[k] == gLayout.windows[j].getWindowStyle()->topLeftCorner.getName())
				{
					gLayout.windows[j].getWindowStyle()->topLeftCorner = *renderer->getTexture(sceneAssetList.textureNames[k]);
				}

				if (sceneAssetList.textureNames[k] == gLayout.windows[j].getWindowStyle()->verticalEdge.getName())
				{
					gLayout.windows[j].getWindowStyle()->verticalEdge = *renderer->getTexture(sceneAssetList.textureNames[k]);
				}

				for (unsigned int l = 0; l < gLayout.windows[j].getNumberOfHudElements(); l++)
				{
					for (unsigned int m = 0; m < gLayout.windows[j].getHudElement(l)->getTexturesToBeLoaded().size(); m++)
					{
						if (sceneAssetList.textureNames[k] == gLayout.windows[j].getHudElement(l)->getTexturesToBeLoaded()[m])
						{
							gLayout.windows[j].getHudElement(l)->addTexture(renderer->getTexture(gLayout.windows[j].getHudElement(l)->getTexturesToBeLoaded()[m]));
						}
					}
				}
			}

			for (unsigned int k = 0; k < gLayout.windows[j].getNumberOfTextElements(); k++)
			{
				for (unsigned int l = 0; l < gLayout.fonts.size(); l++)
				{
					if (gLayout.fonts[l].getName() == gLayout.windows[j].getTextElement(k)->getFontName())
					{
						gLayout.windows[j].getTextElement(k)->setFont(gLayout.fonts[l]);
					}
				}
			}
		}

		renderer->getGuiManager()->addGuiLayout(gLayout);
	}

	for (unsigned int i = 0; i < sceneModels.size(); i++)
	{
		renderer->add(&sceneModels[i]);

		for (unsigned int j = 0; j < sceneModels[i].getScripts().size(); j++)
		{
			scriptHandler->addScriptToObject(sceneModels[i].getName(), sceneModels[i].getScripts()[j]);
		}
	}

	for (unsigned int i = 0; i < objectInstances.size(); i++)
	{
		if (objectInstances[i].type = CORE_OBJECTTYPE_SKYMAP)
		{
			renderer->setBackGroundCubeMap(objectInstances[i].objectName);
		}
	}
	
	renderer->loadAllShaders();
	renderer->loadAllMaterials();
	renderer->setQuadModel(&quadModel);
	renderer->loadAllModels();
	renderer->updateGuiTextures();
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
	renderer = toSet;
}

void Scene::setAudioHandler(AudioHandler *toSet)
{
	audioHandler = toSet;
}

void Scene::setPhysicsHandler(PhysicsHandler *toSet)
{
	physicsHandler = toSet;
}

void Scene::setScriptHandler(ScriptHandler *toSet)
{
	scriptHandler = toSet;
}

Renderer *Scene::getRenderer()
{
	return nullptr;
}

AudioHandler *Scene::getAudioHandler()
{
	return nullptr;
}

PhysicsHandler *Scene::getPhysicsHandler()
{
	return physicsHandler;
}

ScriptHandler *Scene::getScriptHandler()
{
	return scriptHandler;
}

AssetList Scene::getAssetList()
{
	return AssetList();
}

Camera *Scene::getCamera()
{
	return &sceneCamera;
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

void Scene::add(Camera *toAdd)
{

}

void Scene::add(Drawable *toAdd)
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
