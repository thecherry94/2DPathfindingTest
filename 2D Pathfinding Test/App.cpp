#include "App.hpp"

#include "Tilemap.hpp"

int App::main(const std::vector<std::string>& args)
{
	// Main Code here
	bool quit = false;
	Tilemap map(clan::Size(10, 10));

	Tile* path = map.build_path_A(map.get_tile(clan::Vec2i(1, 1)), map.get_tile(clan::Vec2i(8, 1)));
	path->mark_previous_tiles_recursive();

	clan::DisplayWindowDescription desc;
	desc.set_position(clan::Rect(-800, 100, clan::Size(800, 600)), false);
	desc.set_title("2D Pathfinding Test");
	desc.set_allow_resize(false);

	window = clan::DisplayWindow(desc);

	while(!quit)
	{
		window.get_gc().clear();

		map.draw();

		window.flip(1);
		clan::KeepAlive::process();
	}

	return 0;
}

clan::DisplayWindow App::window;