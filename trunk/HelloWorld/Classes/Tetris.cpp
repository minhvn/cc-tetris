#include "Tetris.h"
#include "Tile.h"

namespace TetrisGame
{
	Tetris::Tetris(TetrisChip ** chipList, int left, int top)
		: m_shape(0)
		, m_left(left)
		, m_top(top)
	{
		for(int i = 0; i < CHIP_NUM; ++i)
			m_chips[i] = chipList[i];
	}
	Tetris::~Tetris()
	{

	}

	void Tetris::tileDown(void)
	{
		// I think every sub class must override these methods
		for(int i = 0; i < CHIP_NUM; ++ i)
		{
			CCAssert(m_chips[i]);
			m_chips[i]->tileDown();
		}
		-- m_top;
	}
	void Tetris::tileLeft(void)
	{
		for(int i = 0; i < CHIP_NUM; ++ i)
		{
			CCAssert(m_chips[i]);
			m_chips[i]->tileLeft();
		};
		-- m_left; 
	}
	void Tetris::tileRight(void)
	{
		for(int i = 0; i < CHIP_NUM; ++ i)
		{
			CCAssert(m_chips[i]);
			m_chips[i]->tileRight();
		}
		++ m_left;
	}
	int Tetris::checkCollision(Chip * chip)
	{
		int type = COLLISION_NONE;
		int x0 = chip->getTileX();
		int y0 = chip->getTileY();
		for(int i = 0; i < CHIP_NUM; ++ i)
		{
			int x1 = m_chips[i]->getTileX();
			int y1 = m_chips[i]->getTileY();
			// left
			// x0 x1
			if( x0 < x1 && y0 == y1 && x0 + 1 == x1)
				type |= COLLISION_LEFT;
			// right
			// x1 x0
			if(x1 < x0 && y0 == y1 && x1 + 1 == x0)
				type |= COLLISION_RIGHT;
			//top
			// y0
			// y1
			if(y0 > y1 && x1 == x0 && y1 + 1 == y0)
				type |= COLLISION_TOP;
			// bottom
			// y1
			// y0
			if(y1 > y0 && x1 == x0 && y0 + 1 == y1)
				type |= COLLISION_BOTTOM;
		}
		return type;
	}
	void Tetris::rotation(void)
	{
		if(++ m_shape >= CHIP_NUM)
			m_shape = 0;
		reShape();
	}
	void Tetris::unRotation(void)
	{
		if(-- m_shape < 0)
			m_shape = CHIP_NUM - 1;
		reShape();
	}

	HTetris::HTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void HTetris::reShape(void)
	{
		if(m_shape %2 == 0)
		{
			//	0 
			//	1	2
			//		3
			m_chips[0]->setTile(m_left, m_top);
			m_chips[1]->setTile(m_left, m_top - 1);
			m_chips[2]->setTile(m_left + 1, m_top - 1);
			m_chips[3]->setTile(m_left +1, m_top - 2);
		}
		else
		{
			//		0	1
			//	2	3
			m_chips[0]->setTile(m_left + 1, m_top);
			m_chips[1]->setTile(m_left + 2, m_top);
			m_chips[2]->setTile(m_left, m_top - 1);
			m_chips[3]->setTile(m_left +1, m_top - 1);
		}
	}
	AHTetris::AHTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void AHTetris::reShape(void)
	{
		if(m_shape % 2 == 0)
		{
			//		0
			//	1	2
			//	3
			m_chips[0]->setTile(m_left + 1, m_top);
			m_chips[1]->setTile(m_left , m_top - 1);
			m_chips[2]->setTile(m_left + 1, m_top - 1);
			m_chips[3]->setTile(m_left, m_top - 2);
		}
		else
		{
			// 0	1
			//		2	3
			m_chips[0]->setTile(m_left , m_top);
			m_chips[1]->setTile(m_left + 1, m_top);
			m_chips[2]->setTile(m_left + 1,  m_top - 1);
			m_chips[3]->setTile(m_left + 2, m_top - 1);
		}
	}

	BoxTetris::BoxTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void BoxTetris::reShape(void)
	{
		//	0	1
		//	2	3
		m_chips[0]->setTile(m_left , m_top);
		m_chips[1]->setTile(m_left + 1, m_top);
		m_chips[2]->setTile(m_left,  m_top - 1);
		m_chips[3]->setTile(m_left + 1, m_top - 1);
	}

	TTetris::TTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void TTetris::reShape(void)
	{
		switch(m_shape)
		{
		case 0:
			{
				//	0	1	2
				//		3
				m_chips[0]->setTile(m_left , m_top);
				m_chips[1]->setTile(m_left + 1, m_top);
				m_chips[2]->setTile(m_left + 2,  m_top);
				m_chips[3]->setTile(m_left + 1, m_top - 1);
				break;
			}
		case 1:
			{
				//		0
				//	1	2
				//		3
				m_chips[0]->setTile(m_left + 1, m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left + 1, m_top - 2);
				break;
			}
		case 2:
			{
				//		0
				//	1	2	3
				m_chips[0]->setTile(m_left + 1, m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left + 2, m_top - 1);
				break;

			}
		case 3:
			{
				//	0
				//	1	2
				//	3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left, m_top - 2);
				break;
			}
		};
	}

	LTetris::LTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void LTetris::reShape(void)
	{
		switch(m_shape)
		{
		case 0:
			{
				//	0
				//	1
				//	2	3
				m_chips[0]->setTile(m_left , m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left,  m_top - 2);
				m_chips[3]->setTile(m_left + 1, m_top - 2);
				break;
			}
		case 1:
			{
				//	0	1	2
				//	3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left + 1, m_top);
				m_chips[2]->setTile(m_left + 2,  m_top);
				m_chips[3]->setTile(m_left , m_top - 1);
				break;
			}
		case 2:
			{
				//	0	1
				//		2	
				//		3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left + 1, m_top);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left + 1, m_top - 2);
				break;

			}
		case 3:
			{
				//			0
				//	1	2	3
				m_chips[0]->setTile(m_left + 2, m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left + 2, m_top - 1);
				break;
			}
		}
	}

	ALTetris::ALTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void ALTetris::reShape(void)
	{
		switch(m_shape)
		{
		case 0:
			{
				//		0
				//		1
				//	2	3
				m_chips[0]->setTile(m_left + 1, m_top);
				m_chips[1]->setTile(m_left + 1, m_top - 1);
				m_chips[2]->setTile(m_left,  m_top - 2);
				m_chips[3]->setTile(m_left + 1, m_top - 2);
				break;
			}
		case 1:
			{
				//	0	
				//	1	2	3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left, m_top - 1);
				m_chips[2]->setTile(m_left + 1,  m_top - 1);
				m_chips[3]->setTile(m_left + 2, m_top - 1);
				break;
			}
		case 2:
			{
				//	0	1
				//	2	
				//	3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left + 1, m_top);
				m_chips[2]->setTile(m_left,  m_top - 1);
				m_chips[3]->setTile(m_left, m_top - 2);
				break;

			}
		case 3:
			{
				//	0	1	2	
				//			3
				m_chips[0]->setTile(m_left, m_top);
				m_chips[1]->setTile(m_left + 1, m_top);
				m_chips[2]->setTile(m_left + 2,  m_top);
				m_chips[3]->setTile(m_left + 2, m_top - 1);
				break;
			}
		}
	}

	LineTetris::LineTetris(TetrisChip ** chipList, int left, int top)
		: Tetris(chipList, left, top)
	{
		reShape();
	}
	void LineTetris::reShape(void)
	{
		// The collision check can not work for LineTetris
		if(m_shape % 2 == 0)
		{
			//	0	1	2	3
			m_chips[0]->setTile(m_left - 1, m_top);
			m_chips[1]->setTile(m_left, m_top);
			m_chips[2]->setTile(m_left + 1, m_top);
			m_chips[3]->setTile(m_left + 2, m_top);
		}
		else
		{
				// 0	
				//	1
				//	2
				//	3
			m_chips[0]->setTile(m_left, m_top + 1);
			m_chips[1]->setTile(m_left, m_top);
			m_chips[2]->setTile(m_left,  m_top - 1);
			m_chips[3]->setTile(m_left, m_top - 2);
		}
	}

	Tetris * TetrisFactory::generateATetris(TetrisChip ** chipList, int left, int top)
	{
		int index = rand() % 7;
		switch(index)
		{
		case 0:
			return new LineTetris(chipList, left, top);
		case 1:
			return new ALTetris(chipList, left, top);
		case 2:
			return new LTetris(chipList, left, top);
		case 3:
			return new TTetris(chipList, left, top);
		case 4:
			return new BoxTetris(chipList, left, top);
		case 5:
			return new AHTetris(chipList, left, top); 
		case 6:
			return new HTetris(chipList, left, top);
		default:
			CCAssert(false);
		}
		return NULL;
	}
}