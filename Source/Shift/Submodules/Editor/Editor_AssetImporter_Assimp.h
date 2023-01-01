#pragma once

class Editor_AssetImporter_Assimp
{
public:
	Editor_AssetImporter_Assimp();
	~Editor_AssetImporter_Assimp();

	bool ImportScene(const std::string& aFilename);

private:
};

