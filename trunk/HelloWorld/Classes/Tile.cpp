#include "Tile.h"
#include "TetrisChip.h"
namespace TetrisGame
{
	Tile::Tile(Chip * chip)
		: m_chip(chip)
	{

	}
	Tile:: ~Tile()
	{
		delete m_chip;
		m_chip = NULL;
	}
	Chip * Tile::getChip()
	{
		return m_chip;
	}
}