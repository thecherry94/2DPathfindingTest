#pragma once

#include "precomp.hpp"
#include "Tile.hpp"

class Tile;
class Tilemap
{
	private:

		// Variables
		//

		clan::Size m_size;
		Tile*** m_pTiles;

		static const  int TILE_SIZE = 32;

	public:

		// Methods
		//

		Tilemap(clan::Size);

		Tile** get_neighbors(clan::Vec2i);
		Tile* get_tile(clan::Vec2i pos) { return m_pTiles[pos.x][pos.y]; }

		void draw();
		Tile* build_path_A(Tile*, Tile*);
};


