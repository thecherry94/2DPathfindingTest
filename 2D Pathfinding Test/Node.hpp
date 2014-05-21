#pragma once


#include "Tilemap.hpp"


class Node
{
	public:
		Tile* pTile;
		Node* pPreviousNode;
};