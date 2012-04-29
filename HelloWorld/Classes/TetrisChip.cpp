#include "TetrisChip.h"
#include "TileMap.h"

namespace TetrisGame
{
	Chip::Chip()
	{
		init();
	}
	Chip::Chip(int x, int y)
	{
		init();
		setTile(x, y);
	}
	Chip::~Chip()
	{
	}
	void Chip::init()
	{
		m_isValid = false;
	}
	void Chip::setTile(int x, int y)
	{
		m_tileX = x;
		m_tileY = y;
	}
	int Chip::getTileX()
	{
		return m_tileX;
	}
	int Chip::getTileY()
	{
		return m_tileY;
	}


	TetrisChip::TetrisChip(CCNode * layer)
	{
		CCAssert(layer);
		m_sprite = CCSprite::spriteWithFile("HelloWorld.png", CCRect(220,100, 20,20));
		CCAssert(m_sprite);
		layer->addChild(m_sprite);
		m_layer = layer;
	}
	TetrisChip::~TetrisChip()
	{
		m_layer->removeChild(m_sprite, true);
	}
	void TetrisChip::setTile(int x, int y)
	{
		Chip::setTile(x, y);
		updatePosition();
	}
	void TetrisChip::tileDown(void)
	{
		-- m_tileY;
		updatePosition();
	}
	void TetrisChip::tileLeft(void)
	{
		-- m_tileX;
		updatePosition();
	}
	void TetrisChip::tileRight(void)
	{
		++m_tileX;
		updatePosition();
	}
	void TetrisChip::updatePosition(void)
	{
		float posX, posY;
		TileMap::tileToPos(m_tileX, m_tileY, posX, posY);
		CCAssert(m_sprite);
		m_sprite->setPosition(CCPointMake(posX, posY));
	}
}