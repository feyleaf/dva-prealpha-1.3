#include "globals.h"

GameFileClass::GameFileClass()
{
}

GameFileClass::~GameFileClass()
{
}

bool GameFileClass::saveGameState(const char* filename)
{
	char gameFile[64] = "";

	sprintf_s(gameFile, "saves/%s.txt", filename); 
	std::ofstream saver;
	saver.open("saves/testsave.tmp");  //extention .tmp in case there is failure saving, we
										//won't destroy/corrupt the original save file
	if(!saveHeaders(saver)) return false;
	if(!saveEther(saver)) return false;
	if(!saveTemplateState(saver)) return false;
	if(!saveActions(saver)) return false;
	if(!saveMaps(saver)) return false;
	saver.close();
	std::remove(gameFile);
	int success = std::rename("saves/testsave.tmp", gameFile);
	return (success==0);
}

bool GameFileClass::loadGameState(const char* filename)
{
//	sprintf_s(gameFileName, "/saves/%s.txt", filename);

	std::ifstream loader;
	loader.open(filename);
	if(loader.eof()) return false;
	loader.close();
	return true;
}

bool GameFileClass::saveActions(std::ofstream& fileHandle)
{
	fileHandle << "Actions saved\n";
	return true;
}

bool GameFileClass::saveEther(std::ofstream& fileHandle)
{
	fileHandle << "Ether saved\n";
	return true;
}

bool GameFileClass::saveHeaders(std::ofstream& fileHandle)
{
	//file headers
	fileHandle << fileHeader.startTime << " ";
	fileHandle << fileHeader.viewercursor_x << " ";
	fileHandle << fileHeader.viewercursor_y << "\n";

	fileHandle << fileHeader.gamemode << "\n";

	fileHandle << fileHeader.inv_cellcount << "\n";
	for (int i = 0; i < fileHeader.inv_cellcount; i++)
	{
		fileHandle << fileHeader.inventoryCells[i].template_idx << " ";
		fileHandle << fileHeader.inventoryCells[i].inv_itemcount << "\n";
		for (int t = 0; t < fileHeader.inventoryCells[i].inv_itemcount; t++)
		{
			fileHandle << fileHeader.inventoryCells[i].items[t].ether_index << " ";
		}
		fileHandle << "\n";
	}
	return true;
}

bool GameFileClass::saveMaps(std::ofstream& fileHandle)
{
	fileHandle << "Maps saved\n";
	return true;
}

bool GameFileClass::saveTemplateState(std::ofstream& fileHandle)
{
	fileHandle << "Templates saved\n";
	return true;
}
