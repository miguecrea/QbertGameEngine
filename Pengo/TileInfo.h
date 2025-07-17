#pragma once

namespace dae
{
	struct TileInfo
	{

		TileInfo() = default;
		TileInfo(int newrow, int newcolumns)
		{
			row = newrow;
			column = newcolumns;

		}
		Direction direction;
		bool m_hasSomething = false;
		int row;
		int column;
	};

}