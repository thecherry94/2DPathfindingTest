#include "Tilemap.hpp"
#include "App.hpp"

Tilemap::Tilemap(clan::Size size)
{
	m_size = size;

	m_pTiles = new Tile**[m_size.width];
	for(int x = 0; x < m_size.width; x++)
	{
		m_pTiles[x] = new Tile*[m_size.height];
	}

	for(int x = 0; x < m_size.width; x++)
	{
		for(int y = 0; y < m_size.height; y++)
		{
			m_pTiles[x][y] = NULL;
		}
	}

	// Walls
	//
	m_pTiles[0][0] = new Tile(this, clan::Vec2i(0, 0), false);
	m_pTiles[1][0] = new Tile(this, clan::Vec2i(1, 0), false);
	m_pTiles[2][0] = new Tile(this, clan::Vec2i(2, 0), false);
	m_pTiles[3][0] = new Tile(this, clan::Vec2i(3, 0), false);
	m_pTiles[4][0] = new Tile(this, clan::Vec2i(4, 0), false);
	m_pTiles[5][0] = new Tile(this, clan::Vec2i(5, 0), false);
	m_pTiles[6][0] = new Tile(this, clan::Vec2i(6, 0), false);
	m_pTiles[7][0] = new Tile(this, clan::Vec2i(7, 0), false);
	m_pTiles[8][0] = new Tile(this, clan::Vec2i(8, 0), false);
	m_pTiles[9][0] = new Tile(this, clan::Vec2i(9, 0), false);
	m_pTiles[0][1] = new Tile(this, clan::Vec2i(0, 1), false);
	m_pTiles[0][2] = new Tile(this, clan::Vec2i(0, 2), false);
	m_pTiles[0][3] = new Tile(this, clan::Vec2i(0, 3), false);
	m_pTiles[0][4] = new Tile(this, clan::Vec2i(0, 4), false);
	m_pTiles[0][5] = new Tile(this, clan::Vec2i(0, 5), false);
	m_pTiles[0][6] = new Tile(this, clan::Vec2i(0, 6), false);
	m_pTiles[0][7] = new Tile(this, clan::Vec2i(0, 7), false);
	m_pTiles[0][8] = new Tile(this, clan::Vec2i(0, 8), false);
	m_pTiles[0][9] = new Tile(this, clan::Vec2i(0, 9), false);
	m_pTiles[9][1] = new Tile(this, clan::Vec2i(9, 1), false);
	m_pTiles[9][2] = new Tile(this, clan::Vec2i(9, 2), false);
	m_pTiles[9][3] = new Tile(this, clan::Vec2i(9, 3), false);
	m_pTiles[9][4] = new Tile(this, clan::Vec2i(9, 4), false);
	m_pTiles[9][5] = new Tile(this, clan::Vec2i(9, 5), false);
	m_pTiles[9][6] = new Tile(this, clan::Vec2i(9, 6), false);
	m_pTiles[9][7] = new Tile(this, clan::Vec2i(9, 7), false);
	m_pTiles[9][8] = new Tile(this, clan::Vec2i(9, 8), false);
	m_pTiles[9][9] = new Tile(this, clan::Vec2i(9, 9), false);
	m_pTiles[1][9] = new Tile(this, clan::Vec2i(1, 9), false);
	m_pTiles[2][9] = new Tile(this, clan::Vec2i(2, 9), false);
	m_pTiles[3][9] = new Tile(this, clan::Vec2i(3, 9), false);
	m_pTiles[4][9] = new Tile(this, clan::Vec2i(4, 9), false);
	m_pTiles[5][9] = new Tile(this, clan::Vec2i(5, 9), false);
	m_pTiles[6][9] = new Tile(this, clan::Vec2i(6, 9), false);
	m_pTiles[7][9] = new Tile(this, clan::Vec2i(7, 9), false);
	m_pTiles[8][9] = new Tile(this, clan::Vec2i(8, 9), false);

	// Obstacles
	//
	m_pTiles[3][1] = new Tile(this, clan::Vec2i(3, 1), false);
	m_pTiles[3][2] = new Tile(this, clan::Vec2i(3, 2), false);
	m_pTiles[3][3] = new Tile(this, clan::Vec2i(3, 3), false);
	m_pTiles[3][4] = new Tile(this, clan::Vec2i(3, 4), false);

	for(int x = 0; x < m_size.width; x++)
	{
		for(int y = 0; y < m_size.height; y++)
		{
			if(m_pTiles[x][y] == NULL)
				m_pTiles[x][y] = new Tile(this, clan::Vec2i(x, y));
		}
	}
}


void Tilemap::draw()
{
	clan::Canvas canvas(App::window);

	for(int x = 0; x < m_size.width; x++)
	{
		for(int y = 0; y < m_size.height; y++)
		{
			Tile* pT = m_pTiles[x][y];
			if(pT == NULL)
				continue;

			canvas.fill_rect(clan::Rect(x * TILE_SIZE, y * TILE_SIZE, clan::Size(TILE_SIZE, TILE_SIZE)), pT->get_background_color());
		}
	}
}


std::list<Tile*> Tilemap::get_neighbors(clan::Vec2i pos)
{
	std::list<Tile*> retval;

	retval.push_back(m_pTiles[pos.x][pos.y-1]);
	retval.push_back(m_pTiles[pos.x+1][pos.y]);
	retval.push_back(m_pTiles[pos.x][pos.y+1]);
	retval.push_back(m_pTiles[pos.x-1][pos.y]);

	return retval;
}


Tile* Tilemap::build_path_A(Tile* start, Tile* end)
{
	std::list<Tile*> reachable;
	reachable.push_back(start);

	std::list<Tile*> explored;

	
	while (!reachable.empty())
	{
		std::list<Tile*>::iterator itT = reachable.begin();
		Tile* pT = *itT;

		if (pT == end)
		{
			return end;
		}

		reachable.erase(itT);
		explored.push_back(pT);


		std::list<Tile*> new_reachable = get_neighbors(pT->get_pos());

		// Remove already explored tiles from the list		
		for (Tile* pExp : explored)
		{
			std::list<Tile*>::iterator itNR = new_reachable.begin();
			while (itNR != new_reachable.end())
			{
				if (*itNR == pExp)
				{
					new_reachable.erase(itNR);
					break;
				}
				else
				{
					itNR++;
				}
			}
		}

		// Remove impassable tiles
		std::list<Tile*>::iterator itWalk = new_reachable.begin();
		while (itWalk != new_reachable.end())
		{
			if (!(*itWalk)->is_walkable())
			{
				itWalk = new_reachable.erase(itWalk);			
			}
			else
			{
				itWalk++;
			}

		}

		for (Tile* pR : new_reachable)
		{
			if (std::find(reachable.begin(), reachable.end(), pR) == reachable.end())
			{
				pR->set_previous_tile(pT);
				reachable.push_back(pR);
			}
		}
	}


	return NULL;
}