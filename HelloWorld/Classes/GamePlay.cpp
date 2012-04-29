#include "GamePlay.h"
#include "Tetris.h"
#include "TileMap.h"
#include "Tile.h"

USING_NS_CC;
namespace TetrisGame
{
	CCScene* GamePlay::scene()
	{
		// 'scene' is an autorelease object
		CCScene *scene = CCScene::node();
	
		// 'layer' is an autorelease object
		GamePlay *layer = GamePlay::node();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	// on "init" you need to initialize your instance
	bool GamePlay::init()
	{
		m_curDownTick = DOWN_INTERNAL;
		m_curTetris = NULL;
		m_curChips = NULL;
		m_state = GAME_NONE;
		if ( !CCLayer::init() )
		{
			return false;
		}
		return true;
	}
	void GamePlay::onEnter()
	{
		CCLayer::onEnter();
		scheduleUpdate();
		setIsTouchEnabled(true);
		m_state = GAME_START;
		m_curChips = new TetrisChip*[Tetris::CHIP_NUM];
	}
	void GamePlay::onExit()
	{
		destroyTetris();
		destroyChips();
	}
	void GamePlay::update(ccTime dt)
	{
		int tick = (int)(dt * 1000);
		if(m_state == GAME_START || m_state == GAME_RUN_TETRIS_STICK)
		{
			generateTetris();
			m_state = GAME_RUN_TETRIS_MOVE;
			m_collisionType = Tetris::COLLISION_NONE;
		}
		else if(m_state ==GAME_RUN_TETRIS_MOVE )
		{
			if(m_curDownTick > 0)
			{
				m_curDownTick -= tick;
				return;
			}
			m_curDownTick = DOWN_INTERNAL;
			m_collisionType = checkCollision();
			if(m_collisionType & Tetris::COLLISION_BOTTOM)
			{
				if(addTileToMap() && ! checkGameOver())
				{
					m_state = GAME_RUN_TETRIS_STICK;
				}
				else
				{
					m_state = GAME_OVER;
				}
			}
			else
				normalDown();
		}
	}
	void GamePlay::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
	{
		CCSetIterator it = pTouches->begin();
		CCTouch* touch = (CCTouch*)(*it);
		m_touchBeginPos = touch->locationInView( touch->view() );
		m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );
		m_touchMove = false;
	}
	void GamePlay::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
	{
		m_touchMove = true;
	}
	void GamePlay::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
	{
		CCSetIterator it = pTouches->begin();
		CCTouch* touch = (CCTouch*)(*it);
		m_touchEndPos = touch->locationInView( touch->view() );
		m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );
		if(!m_touchMove)
		{
			if(m_touchBeginPos.x < TileMap::getScreenMidWidth())
				normalLeft();
			else
				normalRight();
		}
		else
		{
			if(m_touchBeginPos.y + 50< m_touchEndPos.y)
			{
				rotation();
			}
			else if(m_touchBeginPos.y - 50> m_touchEndPos.y)
			{
				quickDown();
			}
		}
		m_touchMove = false;
	}
	void GamePlay::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
	{
	}
	void GamePlay::generateTetris(void)
	{
		// TODO: random
		int left, top;
		TileMap::getBornTile(left, top);
		for(int i = 0; i < Tetris::CHIP_NUM; ++ i)
		{
			m_curChips[i] = new TetrisChip(this);
		}
		m_curTetris = TetrisFactory::generateATetris(m_curChips, left, top);
		CCAssert(m_curTetris);
	}
	void  GamePlay::destroyTetris(void)
	{
		if(m_curTetris)
			delete m_curTetris;
	}
	void  GamePlay::destroyChips(void)
	{
		for(int i = 0; i < Tetris::CHIP_NUM; ++ i)
			if(m_curChips[i])
				delete m_curChips[i];
		delete [] m_curChips;
	}
	int GamePlay::checkCollision(void)
	{
		int collisionType = 0;
		int x, y;
		TileMap::tileArraySize(x, y);
		for(int i =0; i < x; ++ i)
		{
			for(int j = 0; j < y; ++ j)
			{
				Tile * tile = m_tileMap.getTile(i, j);
				if(tile)
					collisionType |= m_curTetris->checkCollision(tile->getChip());
			}
		}
		return collisionType;
	}
	bool GamePlay::addTileToMap(void)
	{
		delete m_curTetris;
		m_curTetris = NULL;
		for(int i = 0; i < Tetris::CHIP_NUM; ++ i)
		{
			TetrisChip * p = m_curChips[i];
			int x = p->getTileX();
			int y = p->getTileY();
			if(m_tileMap.setTile(x, y, p))
				m_curChips[i] = NULL; // tileMap will destroy it
			else
				return false;
		}
		clearfullTiles();
		return true;
	}
	void GamePlay::clearfullTiles(void)
	{
		int x, y;
		TileMap::tileArraySize(x, y);
		for(;;)
		{
			bool finished = true;
			for(int v = y - 1; v > 0; -- v)
			{
				bool full = true;
				for(int h = 1; h < x - 1; ++ h)
				{
					if(!m_tileMap.getTile(h, v))
						full = false;
				}
				if(full)
				{
					m_tileMap.delTilesForLine(v);
					finished = false;
					for(int i = v + 1; i < y; ++ i)
						m_tileMap.moveLine(i, i - 1);
					break;
				}
			}
			if(finished)
				return;
		}
	}
	bool GamePlay::checkGameOver(void)
	{
		int x, y;
		TileMap::tileArraySize(x, y);
		for(int i = 1; i < x - 1; ++ i)
		{
			if(m_tileMap.getTile(i, y - 1))
				return true;
		}
		return false;
	}
	void  GamePlay::normalDown(void)
	{
		CCAssert(m_curTetris);
		m_curTetris->tileDown();
	}
	void  GamePlay::quickDown(void)
	{
		CCAssert(m_curTetris);
		for(;;)
		{
			m_collisionType = checkCollision();
			if(m_collisionType & Tetris::COLLISION_BOTTOM)
				return;
			normalDown();
		}
	}
	void  GamePlay::normalLeft(void)
	{
		CCAssert(m_curTetris);
		m_collisionType = checkCollision();
		if(m_collisionType & Tetris::COLLISION_LEFT)
			return;
		m_curTetris->tileLeft();
	}
	void GamePlay::normalRight(void)
	{
		CCAssert(m_curTetris);
		m_collisionType = checkCollision();
		if(m_collisionType & Tetris::COLLISION_RIGHT)
			return;
		m_curTetris->tileRight();
	}
	void GamePlay::rotation(void)
	{
		CCAssert(m_curTetris);
		m_curTetris->rotation();
		if(rotationCollision())
			m_curTetris->unRotation();
	}
	bool GamePlay::rotationCollision(void)
	{
		int x, y;
		TileMap::tileArraySize(x, y);
		for(int i =0; i < x; ++ i)
		{
			for(int j = 0; j < y; ++ j)
			{
				Tile * tile = m_tileMap.getTile(i, j);
				if(tile)
				{
					for(int k = 0; k < Tetris::CHIP_NUM; ++ k)
					{
						TetrisChip * chip = m_curChips[k];
						CCAssert(chip);
						if(chip->getTileX() == i && chip->getTileY() == j)
							return true;
					}
				}
			}
		}
		return false;
	}
}