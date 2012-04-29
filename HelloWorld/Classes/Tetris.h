#ifndef __TETRIS_H__
#define __TETRIS_H__
#include "cocos2d.h"
#include "TetrisChip.h"
using namespace cocos2d;
namespace TetrisGame
{
	class Tetris
	{
	public:
		enum eCollisionType
		{
			COLLISION_NONE = 0,
			COLLISION_LEFT = 1,
			COLLISION_RIGHT = 2,
			COLLISION_TOP = 4, 
			COLLISION_BOTTOM = 8,
		};
		enum 
		{
			CHIP_NUM = 4,
		};
	public:
		Tetris(TetrisChip ** chipList, int left, int top);
		virtual ~Tetris();
	public:
		void tileDown(void);
		void tileLeft(void);
		void tileRight(void);
		virtual int checkCollision(Chip * chip);
		void rotation(void); 
		void unRotation(void);
		virtual void reShape(void) = 0;
	
	protected:
		TetrisChip * m_chips[CHIP_NUM];
		int m_shape;
		int m_left;
		int m_top;
	};
	//	*
	//	*	*
	//		*
	class HTetris : public Tetris
	{
	public:
		HTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//		*
	//	*	*
	//	*
	class AHTetris : public Tetris
	{
	public:
		AHTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//	*	*
	//	*	*
	class BoxTetris : public Tetris
	{
	public:
		BoxTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//	*	*	*
	//		*
	class TTetris : public Tetris
	{
	public:
		TTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//	*
	//	*
	//	*	*
	class LTetris : public Tetris
	{
	public:
		LTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//		*
	//		*
	//	*	*
	class ALTetris : public Tetris
	{
	public:
		ALTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	//	*	*	*	*
	class LineTetris : public Tetris
	{
	public:
		LineTetris(TetrisChip ** chipList, int left, int top);
		void reShape(void);
	};
	class TetrisFactory
	{
	public:
		static Tetris * generateATetris(TetrisChip ** chipList, int left, int top);
	};
}
#endif