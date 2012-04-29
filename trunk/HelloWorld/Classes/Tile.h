#ifndef __TILE_H__
#define __TILE_H__
#include "cocos2d.h"
using namespace cocos2d;
namespace TetrisGame
{
	class Chip;
	class Tile
	{
	public:
		Tile(Chip * chip);
		virtual ~Tile();
	public:
		bool isAvailable() const;
		Chip * getChip();
	private:
		Chip * m_chip;
	};
}
#endif