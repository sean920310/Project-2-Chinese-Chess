#include "GameManager.h"

//function

//mouse postion is on coord that choice to move
bool isChoiceToMove(sf::Vector2i mouseCoord, Coord coord) {

	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	sf::IntRect circle(x, y, 60, 60);
	return circle.contains(mouseCoord);
}

//open file dialog to choice file
void openFile(std::fstream& file) {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
						std::fstream file(pszFilePath, std::ios::in | std::ios::out);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
}


//class
GameManager::GameManager() :board(), viewer()
{
	onBoard = board.getAllChess();
	currentPlayer = Team::Red;
}

GameManager::~GameManager()
{
	file.close();
}

int GameManager::menu()	//0:exit game 1:start new game 2:select a file
{
	while (viewer.windowIsOpen())
	{
		viewer.update();
		viewer.clear();
		if (viewer.mouseClick(sf::Mouse::Left)) {
			switch (viewer.showMenu())
			{
			case 0:
				viewer.close();
				return 0;
				break;
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			default:
				break;
			}
		}
		else {
			viewer.showMenu();
		}
		viewer.display();
	}
	return 0;
}

void GameManager::inGame(InGameState state)
{

	std::vector<Coord> canMovePosCoord;
	Coord coordChoiseChess, coordChoiseToMove;
	bool isCheck = false , oneSurrender = false;
	Team teamCheck , teamWin;

	while (viewer.windowIsOpen())
	{
		onBoard = board.getAllChess();

		switch (state)
		{
			//======================================================start====================================================	**start a new game
		case InGameState::start:
			this->file.close();
			this->board.newBoard();
			onBoard = board.getAllChess();
			currentPlayer = Team::Red;
			isCheck = false;
			oneSurrender = false;
			state = InGameState::selectChess;
			break;

			//====================================================inputFile==================================================	**start a game with input file
		case InGameState::inputFile:
			state = InGameState::oneSideWin;
			break;
			//====================================================selectChess================================================	**wait for press a object
		case InGameState::selectChess:
			for (auto& chess : onBoard) {
				chess->showSelect(viewer.getMousePosition(), currentPlayer);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && chess->isChoice() && currentPlayer == chess->getTeam()) {
					state = InGameState::pressChess;
					break;
				}
			}
			for (auto& coord : canMovePosCoord) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isChoiceToMove(viewer.getMousePosition(), coord)) {
					coordChoiseToMove = coord;
					state = InGameState::choiceMove;
					break;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && state != InGameState::pressChess) {
				canMovePosCoord.clear();
			}
			break;

			//====================================================pressChess================================================	**show the coord can move to
		case InGameState::pressChess:
			for (auto& chess : onBoard) {
				if (chess->isChoice()) {
					coordChoiseChess = chess->getCoord();
					std::cout << chess->getCoord().x << " " << chess->getCoord().y << " is press.\n";
					canMovePosCoord.clear();
					canMovePosCoord = chess->coordCanMove(board);
					chess->removeWillCheckCoord(board,canMovePosCoord);
					state = InGameState::selectChess;
					break;
				}
			}
			break;

			//====================================================choiceMove================================================	**move the chess
		case InGameState::choiceMove:
			//board.getChess(coordChoiseChess)->move(board,coordChoiseToMove);
			this->logFile(coordChoiseChess, coordChoiseToMove);
			board.moveChess(coordChoiseChess, coordChoiseToMove);
			state = InGameState::oneSideWin;
			break;

			//====================================================isCheck===================================================	**judge if one side is check or win
		case InGameState::isCheck:
			teamCheck = currentPlayer;
			if (board.oneSideIsCheck(teamCheck)) {
				isCheck = true;
			}
			else
			{
				isCheck = false;
			}
			state = InGameState::selectChess;

			if (currentPlayer == Team::Red)
				currentPlayer = Team::Black;
			else
				currentPlayer = Team::Red;
			break;

			//==================================================oneSideWin==================================================	**decide to play anthor game
		case InGameState::oneSideWin:
			if (oneSurrender) {
				if (this->endGame(teamWin))
					state = InGameState::start;
				else
					return;
				continue;
			}

			teamWin = currentPlayer;
			if (board.oneSideIsWin(teamWin)) {
				if (this->endGame(teamWin))
					state = InGameState::start;
				else
					return;
				continue;
			}
			else
			{
				state = InGameState::isCheck;
			}
			break;
		}

		//update
		switch (viewer.update()) 
		{
		case 0:
			break;
		case 1:
			std::cout << "windows close\n";
			return;
			break;
		case 2:
			std::cout << "pause\n";

			switch (this->pause())
			{
			case 0:
				std::cout << "windows close\n";
				return;
				break;
			case 1:
				std::cout << "continue\n";
				break;
			case 2:
				std::cout << "back to menu\n";
				return;
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}

		//draw
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawCanMovePos(canMovePosCoord);
		viewer.drawRightSideObject(currentPlayer);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			switch (viewer.showSurrender(true, currentPlayer))
			{
			case 0:
				if (this->confirmSurrender()) {
					teamWin = Team::Red;
					oneSurrender = true;
					state = InGameState::oneSideWin;
				}
				break;
			case 1:
				if (this->confirmSurrender()) {
					teamWin = Team::Black;
					oneSurrender = true;
					state = InGameState::oneSideWin;
				}
				break;
			default:
				break;
			}
		}
		else
			viewer.showSurrender(true,currentPlayer);

		if (isCheck)
			viewer.showCheck(teamCheck);
		viewer.display();
	}

}

bool GameManager::endGame(Team teamWin)
{
	int oneMore;
	while (viewer.windowIsOpen()) {
		viewer.update();
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.showWinner(teamWin);
		if (viewer.mouseClick(sf::Mouse::Left)) {
			switch (viewer.showOneMoreGame())
			{
			case -1:
				break;
			case 0:
				return false;
			case 1:
				return true;
			default:
				break;
			}
		}
		else
			viewer.showOneMoreGame();
		viewer.display();
	}
	return false;
}

int GameManager::pause()
{
	while (viewer.windowIsOpen())
	{

		//update
		switch (viewer.update())
		{
		case 0:
			break;
		case 1:
			return 0;
			break;
		case 2:
			return 1;
			break;
		default:
			break;
		}

		//draw
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawRightSideObject(currentPlayer);
		viewer.showSurrender(false,currentPlayer);
		if (viewer.mouseClick(sf::Mouse::Left)) {
			switch (viewer.showPause())
			{
			case 0:
				return 1;
				break;
			case 1:
				return 2;
				break;
			default:
				break;
			}
		}
		else
			viewer.showPause();
		viewer.display();
	}
	return 0;
}

bool GameManager::confirmSurrender()
{
	while (viewer.windowIsOpen())
	{
		//update
		switch (viewer.update())
		{
		case 0:
			break;
		case 1:
			return false;
			break;
		case 2:
			return false;
			break;
		}

		//draw
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawRightSideObject(currentPlayer);
		viewer.showSurrender(false, currentPlayer);
		if (viewer.mouseClick(sf::Mouse::Left)) {
			switch (viewer.showConfirmSurrender())
			{
			case 0:
				return false;
				break;
			case 1:
				return true;
				break;
			default:
				break;
			}
		}
		else
			viewer.showConfirmSurrender();
		viewer.display();

	}
	return false;
}

void GameManager::readFile() {
	this->board.newBoard();
	//open file
	if (this->file.is_open())
		this->file.close();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
						this->file.open(pszFilePath, std::ios::in );	//need to convert everything to wchar_t!!!!!!!!!!
						this->filePath = pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	if (this->file.peek() == std::ifstream::traits_type::eof()) {
		throw "File open error";
	}

	//read file
	file.seekp(0);
	std::string dump, player, x1, y1, x2, y2;	//ex. Player: 1, Action: Cannon (7, 7) -> (7, 5)

	while (!file.eof())
	{
		file >> dump >> player >> dump >> dump >> x1 >> y1 >> dump >> x2 >> y2;
		if (file.eof()) {
			return;
		}
		std::cout << player << std::endl << x1 << std::endl << y1 << std::endl << x2 << std::endl << y2 << std::endl;

		Coord from(int(x1[1] - '0'), int(y1[0] - '0')), to(int(x2[1] - '0'), int(y2[0] - '0'));
		board.moveChess(from, to);
		if (player[0] == '1')
			currentPlayer = Team::Red;
		else
			currentPlayer = Team::Black;
	}
}

void GameManager::logFile(Coord from,Coord to) {
	if (!file.is_open()) {
		std::wstring filePathName;
		char nowTime[100];
		time_t now = time(nullptr);
		struct tm tm_info;
		localtime_s(&tm_info,&now);
		strftime(nowTime, 100, "%Y%m%d%H%M%S", &tm_info);
		std::string str(nowTime);
		
		filePathName = L"./log_" + std::wstring(str.begin(),str.end())+L".txt";
		
		file.open(filePathName, std::ios::out);
		filePath = filePathName;
	}
	else
	{
		file.close();
		file.open(filePath, std::ios::app);
	}
	int player;
	if (this->currentPlayer == Team::Red)
		player = 1;
	else
		player = 2;

	std::string character;
	switch (this->board.getChess(from)->getCharacter())
	{
	case Characters::General:
		character = "General";
		break;
	case Characters::Advisor:
		character = "Advisor";
		break;
	case Characters::Elephant:
		character = "Elephant";
		break;
	case Characters::Horse:
		character = "Horse";
		break;
	case Characters::Chariot:
		character = "Chariot";
		break;
	case Characters::Cannon:
		character = "Cannon";
		break;
	case Characters::Soldier:
		character = "Soldier";
		break;
	default:
		break;
	}

	file << "Player: " << player << ", Action: " << character << " (" << from.x << ", " << from.y << ") -> (" << to.x << ", " << to.y << ")\n";
}