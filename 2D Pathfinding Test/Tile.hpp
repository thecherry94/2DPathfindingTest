#pragma once

#include "precomp.hpp"
#include "Tilemap.hpp"

class Tilemap;
class Tile
{
	private:

		// Variables
		//

		Tilemap* m_pMap;
		Tile* m_pPreviousTile;
		clan::Vec2i m_pos;

		int m_cost;
		bool m_walkable;

	public:
		
		// Methods
		//
		Tile();
		Tile(Tilemap*, clan::Vec2i, const bool walkable = true, const int cost = 1);

		bool is_walkable() { return m_walkable; }
		Tile* get_previous_tile() { return m_pPreviousTile; }

		clan::Vec2i get_pos() { return m_pos; }

		void set_previous_tile(Tile* pT) { m_pPreviousTile = pT; }
};