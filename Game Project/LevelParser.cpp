#include "LevelParser.h"
#include "Game.h"
#include "TileLayer.h"
#include "base64decoder\base64.h"
#include <zlib.h>

Level* LevelParser::parseLevel(const char *levelFile)
{
	//create a TinyXML document & loadd the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	//create level object
	Level* pLevel = new Level();

	//get root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);
	if (pRoot->Attribute("backgroundcolor") != NULL){
		std::string bgstr = pRoot->Attribute("backgroundcolor");
		bgstr = bgstr.substr(1);
		for (int i = 0; i < 3; i++)
		{
			std::stringstream str;
			switch (i){
			case 0: str << bgstr.substr(0, 2);
				str >> std::hex >> m_bgR;
				break;
			case 1: str << bgstr.substr(2, 2);
				str >> std::hex >> m_bgG;
				break;
			case 2: str << bgstr.substr(4, 2);
				str >> std::hex >> m_bgB;
				break;
			}
		}
	}
	else
	{
		m_bgR = 255;
		m_bgG = 255;
		m_bgB = 255;
	}
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), m_bgR, m_bgG, m_bgB, m_bgA);
	//parse the tilesets

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}
	//parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	std::string src = pTilesetRoot->FirstChildElement()->Attribute("source");
	//first add tileset to texture manager
	TheTextureManager::Instance()->load("assets\\" + src, pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());
	std::cout << "loading asset: " << pTilesetRoot->FirstChildElement()->Attribute("source") << " id: " << pTilesetRoot->Attribute("name") << std::endl;
	//create tileset object
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	pTilesetRoot->Attribute("opacity", &tileset.alpha);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}
void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	//tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* pDataNode = 0;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	//uncompress zlib compression

	uLongf numGids = m_width*m_height*sizeof(int);
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	pTileLayer->setTileIDs(data);

	pLayers->push_back(pTileLayer);
}