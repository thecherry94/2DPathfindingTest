#include "Tile.hpp"


Tile::Tile(Tilemap* pMap, clan::Vec2i pos, const bool walkable, const int cost)
{
	m_pMap = pMap;
	m_pos = pos;
	m_walkable = walkable;
	m_cost = cost;

	m_pPreviousTile = NULL;

	if (m_walkable)
	{
		m_backgroundColor = clan::Colorf::darkgreen;
	}
	else
	{
		m_backgroundColor = clan::Colorf::red;
	}
}

void Tile::mark_previous_tiles_recursive()
{
	m_backgroundColor = clan::Colorf::white;

	if (m_pPreviousTile != NULL)
	{		
		m_pPreviousTile->mark_previous_tiles_recursive();
	}	
}