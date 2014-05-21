#include "Tile.hpp"


Tile::Tile(Tilemap* pMap, clan::Vec2i pos, const bool walkable, const int cost)
{
	m_pMap = pMap;
	m_pos = pos;
	m_walkable = walkable;
	m_cost = cost;
}