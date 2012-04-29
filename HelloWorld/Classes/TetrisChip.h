#ifndef __TETRIS_CHIP_H__
#define __TETRIS_CHIP_H__
#include "cocos2d.h"
using namespace cocos2d;

namespace TetrisGame
{
	class Chip
	{
	public:
		Chip();
		Chip(int x, int y);
		virtual ~Chip();
		void init();
		virtual void setTile(int x, int y);
		int getTileX();
		int getTileY();
	protected:
		int m_tileX;
		int m_tileY;
		bool m_isValid;
	};
	class TetrisChip : public Chip
	{
	public:
		TetrisChip(CCNode * layer);
		virtual ~TetrisChip();
		void setTile(int x, int y);
		void tileDown(void);
		void tileLeft(void);
		void tileRight(void);
	private:
		void updatePosition(void);
	private:
		CCSprite * m_sprite;
		CCNode * m_layer;

	};
}
#endif