#include "Wave.h"

bool operator==(Cell c1, Cell c2)
{
	return c1.row == c2.row && c1.column == c2.column;
}

void Wave::CreateMap()
{
	ifstream file;
	file.open(this->fileMap, ios::in);

	int bufferSize{ 1024 };
	char* buffer = new char[bufferSize] {};

	vector<int> line;
	int row{};

	while (!file.eof())
	{
		file.getline(buffer, bufferSize);
		//cout << buffer << "\n";
		int i{};
		while (buffer[i] && i < bufferSize)
		{
			CellType type;

			switch (buffer[i])
			{
			case '#': type = CellType::Wall; break;
			case 's': 
			case 'S': 
				type = CellType::Start;
				cellStart = { row, i };
				break;
			case 'f':
			case 'F': 
				type = CellType::Finish; 
				cellFinish = { row, i };
				break;
			case ' ': type = CellType::Space; break;
			default:
				break;
			}
			line.push_back(static_cast<int>(type));
			i++;
		}
		map.push_back(line);
		line.clear();
		delete[]buffer;
		buffer = new char[bufferSize] {};
		row++;
	}
}

bool Wave::MoveWave()
{
	bool frontCurrent{ false };
	fronts[frontCurrent].push_back(cellStart);
	int frontNumber{};

	bool isFinish{ false };

	while (1)
	{
		fronts[!frontCurrent].clear();
		frontNumber++;

		for (auto cell : fronts[frontCurrent])
		{
			for (auto cellOff : Offset)
			{
				int row = cell.row + cellOff.row;
				int column = cell.column + cellOff.column;

				if (map[row][column] == static_cast<int>(CellType::Space) || 
					map[row][column] == static_cast<int>(CellType::Finish))
				{
					map[row][column] = frontNumber;
					fronts[!frontCurrent].push_back({ row, column });
				}
			}
		}
		if (!fronts[!frontCurrent].size()) break;

		for(auto cell : fronts[!frontCurrent])
			if (cell == cellFinish)
			{
				isFinish = true;
				break;
			}
		if (isFinish) break;
		frontCurrent = !frontCurrent;
	}
	return isFinish;
}

void Wave::CreateWay()
{
	//Cell cellCurrent = cellFinish;
	way.push_back(cellFinish);
	int numberCurrent = map[way.back().row][way.back().column];
	
	while (!(way.back() == cellStart))
	{
		for (auto cellOff : Offset)
		{
			int row = way.back().row + cellOff.row;
			int column = way.back().column + cellOff.column;
			if (map[row][column] == numberCurrent - 1)
			{
				way.push_back({ row, column });
				numberCurrent--;
				break;
			}
		}
	}

	reverse(way.begin(), way.end());

	cout << "\n";
	for (auto cell : way)
		cout << "[" << cell.row << "," << cell.column << "] ";
	cout << "\n";
}

void Wave::ShowMap()
{
	for (int row = 0; row < map.size(); row++)
	{
		for (int column = 0; column < map[0].size(); column++)
		{
			if (map[row][column] == (int)CellType::Start)
				cout << setw(2) << "S";
			if (map[row][column] == (int)CellType::Finish)
				cout << setw(2) << "F";
			if (map[row][column] == (int)CellType::Wall)
				cout << setw(2) << string(2, (char)178);
			if (map[row][column] == (int)CellType::Space)
				cout << setw(2) << " ";
			if (map[row][column] > 0)
			{
				if (way.size() > 0)
				{
					if (find(way.begin(), way.end(), Cell{ row, column }) != way.end())
						cout << setw(2) << map[row][column];
					else
						cout << setw(2) << "";
				}
				else
					cout << setw(2) << map[row][column];
			}
				
		}
		cout << "\n";
	}
}




