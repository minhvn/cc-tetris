#ifndef __GAME_PLAY_H__
#define __GAME_PLAY_H__
#include "cocos2d.h"
#include "TileMap.h"

using namespace cocos2d;
namespace TetrisGame
{
	class Tetris;
	class TetrisChip;
	class GamePlay : public CCLayer
	{
	public:
		enum eGameState
		{
			GAME_NONE = 0,
			GAME_START,
			GAME_RUN_TETRIS_MOVE,
			GAME_RUN_TETRIS_STICK,
			GAME_OVER,
		};
		enum 
		{
			DOWN_INTERNAL = 300,
		};
	public:
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  
		virtual void onEnter();
		virtual void onExit();
		// there's no 'id' in cpp, so we recommand to return the exactly class pointer
		static cocos2d::CCScene* scene();

		// implement the "static node()" method manually
		LAYER_NODE_FUNC(GamePlay);
	public:
		void update(ccTime dt);
		virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
		virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
		virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
		virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	private:
		void generateTetris(void);
		void destroyTetris(void);
		void destroyChips(void);
		int checkCollision(void);
		bool checkGameOver(void);
		bool addTileToMap(void);
		void clearfullTiles(void);

		void normalDown(void);
		void quickDown(void);
		void normalLeft(void);
		void normalRight(void);
		void rotation(void);
		bool rotationCollision(void);
	private:
		eGameState m_state;
		Tetris * m_curTetris;
		TetrisChip * *m_curChips;
		int m_curDownTick;
		int m_collisionType;
		TileMap m_tileMap;
		CCPoint m_touchBeginPos;
		CCPoint m_touchEndPos;
		bool m_touchMove;
	};

}
#endif