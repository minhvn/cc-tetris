#include "TileMap.h"
#include "Tetris.h"
#include "Tile.h"
#include "TetrisChip.h"

namespace TetrisGame
{
	TileMap::TileMap()
	{
		int x, y;
		tileArraySize(x,y);
		for(int i = 0; i < x; ++ i)
			for(int j = 0; j < y; ++ j)
				m_tiles[i][j] = 0;
		// use the empty tetris to help check collision
		for(int i = 0; i < y; ++ i)
		{
			m_tiles[0][i] = new Tile (new Chip(0,i));
			m_tiles[x-1][i] = new Tile(new Chip(x-1,i));
		}
		for(int i = 1; i < x - 1; ++ i)
			m_tiles[i][0] = new Tile (new Chip(i,0));
	}
	TileMap::~TileMap()
	{
		for(int i = 0; i < TILE_NUM_X + 2; ++ i)
			for(int j = 0; j < TILE_NUM_Y + 1; ++ j)
				if(m_tiles[i][j])
				{
					delete m_tiles[i][j];
					m_tiles[i][j] = NULL;
				}

	}
	Tile * TileMap::getTile(int x, int y)
	{
		return m_tiles[x][y];
	}
	bool TileMap::setTile(int x, int y, TetrisChip * chip)
	{
		if(m_tiles[x][y])
			return false;
		m_tiles[x][y] = new Tile(chip);
		return true;
	}
	void TileMap::delTile(int x, int y)
	{
		CCAssert(m_tiles[x][y], "");
		delete m_tiles[x][y];
		m_tiles[x][y] = NULL;
	}
	void TileMap::delTilesForLine(int y)
	{
		int w, h;
		tileArraySize(w, h);
		for(int i = 1; i < w - 1; ++ i)
			delTile(i, y);
	}
	void TileMap::moveLine(int from, int to)
	{
		int w, h;
		tileArraySize(w, h);
		for(int i = 1 ; i < w-1; ++ i)
		{
			m_tiles[i][to] = m_tiles[i][from];
			if(m_tiles[i][to])
				m_tiles[i][to]->getChip()->setTile(i, to);
			m_tiles[i][from] = NULL;
		}
	}
	float TileMap::getTileWidth(void)
	{
		return HVGA_SCREEN_WIDTH / TILE_NUM_X;
	}
	void TileMap::getBornTile(int & left, int & top)
	{
		left = TILE_NUM_X / 2;
		top = TILE_NUM_Y;
	}
	void TileMap::tileToPos(int left, int top, float & centerX, float & centerY)
	{
		centerX = (left  - 0.5) * getTileWidth();
		centerY = (top - 0.5) * getTileWidth();
	}
	void TileMap::posToTile(float centerX, float centerY, int & left, int & top)
	{
	}
	int TileMap::topTile(void)
	{
		return TILE_NUM_Y - 1;  
	}
	int TileMap::bottomtile(void)
	{
		return 0;
	}
	int TileMap::leftTile(void)
	{
		return 0;
	}
	int TileMap::rightTile(void)
	{
		return TILE_NUM_X - 1;
	}
	void TileMap::tileArraySize(int & x, int & y)
	{
		 x = TILE_NUM_X + 2;
		 y = TILE_NUM_Y + 1;
	}
	float TileMap::getScreenMidWidth()
	{
		return HVGA_SCREEN_WIDTH / 2;
	}
}