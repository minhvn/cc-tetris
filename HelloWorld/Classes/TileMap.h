#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__
#include "cocos2d.h"
using namespace cocos2d;
namespace TetrisGame
{
	class Tile;
	class TetrisChip;
	class TileMap
	{
	public:
		enum
		{
			TILE_NUM_X = 16,
			TILE_NUM_Y = 24,
		};
		enum
		{
			HVGA_SCREEN_WIDTH = 320,
			HVGA_SCREEN_HEIGHT = 480,
		};
	public:
		TileMap();
		~TileMap();
		Tile * getTile(int x, int y);
		bool setTile(int x, int y, TetrisChip * chip);
		void delTile(int x, int y);
		void delTilesForLine(int y);
		void moveLine(int from, int to);
	public:
		static float getTileWidth(void);
		static void getBornTile(int & left, int & top);
		static void tileToPos(int left, int top, float & centerX, float & centerY);
		static void posToTile(float centerX, float centerY, int & left, int & top);
		static int topTile(void);
		static int bottomtile(void);
		static int leftTile(void);
		static int rightTile(void);
		static void tileArraySize(int & x, int & y);
		static float getScreenMidWidth(void);
	private:
		Tile * m_tiles[TILE_NUM_X + 2][TILE_NUM_Y + 1];
};
}
#endif