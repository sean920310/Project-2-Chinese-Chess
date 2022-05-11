#include "GameManager.h"

//function
bool isChoiceToMove(sf::Vector2i mouseCoord, Coord coord) {

	float x, y;
	x = CHECKBOARD_SCALE_SIZE * (coord.x * 233.75 + 34) + 35.0625 - CHESS_SCALE_SIZE * (606.0 / 2);
	y = CHECKBOARD_SCALE_SIZE * (coord.y * 233.75 + 34) + 58.05 - CHESS_SCALE_SIZE * (606.0 / 2);
	sf::IntRect circle(x,y,60,60);
	return circle.contains(mouseCoord);
}

bool oneSideIsCheck(Board& board,Team& team) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.getChess({ i,j }) != nullptr) {
				auto canMovePosCoord =  board.getChess({ i,j })->coordCanMove(board);
				for (const auto& coord : canMovePosCoord) {
					if (board.getChess(coord) != nullptr) {
						if (board.getChess(coord)->getCharacter() == Characters::General) {
							team = board.getChess({ i,j })->getTeam();
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool oneSideIsWin(Board& board, Team& team) {
	bool redAlive = false;
	bool blackAlive = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.getChess({ i,j }) != nullptr) {
				if (board.getChess({ i,j })->getCharacter() == Characters::General) {
					if (board.getChess({ i,j })->getTeam() == Team::Red) {
						team = Team::Red;
						redAlive = true;
					}
					else
					{
						team = Team::Black;
						blackAlive = true;
					}
				}			
			}
		}
	}
	return !(redAlive && blackAlive);
}

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
						std::fstream file(pszFilePath, std::ios::in);
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
GameManager::GameManager():board(),viewer()
{
	onBoard = board.getAllChess();
	currentPlayer = Team::Red;
}

int GameManager::menu()	//0:exit game 1:start new game 2:select a file
{
	while (viewer.windowIsOpen())
	{
		viewer.update();
		viewer.clear();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			switch (viewer.showMenu())
			{
			case 0:
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

void GameManager::readFile() {
	//open file
	std::fstream file;

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
						file.open(pszFilePath, std::ios::in);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	
	//read file
	std::string dump,player,x1,y1,x2,y2;	//Player: 1, Action: Cannon (7, 7) -> (7, 5)
	
	while (!file.eof())
	{
		file >> dump >> player >> dump >> dump >> x1 >> y1 >> dump >> x2 >> y2;
		if (file.eof())
			return;
		std::cout << player << std::endl << x1 << std::endl << y1 << std::endl << x2 << std::endl << y2<< std::endl;
		Coord from(int(x1[1] - '0'), int(y1[0] - '0')), to(int(x2[1] - '0'), int(y2[0] - '0'));
		board.moveChess(from, to);
	}
	if (player[0] == '1')
		currentPlayer = Team::Red;
	else
		currentPlayer = Team::Black;
}

void GameManager::inGame(InGameState state)
{

	std::vector<Coord> canMovePosCoord;
	Coord coordChoiseChess,coordChoiseToMove;
	bool isCheck=false;
	Team teamCheck=Team::Black,teamWin = Team::Black;

	while (viewer.windowIsOpen())
	{
		onBoard = board.getAllChess();

		switch (state)
		{
		//======================================================start====================================================	**start a new game
		case InGameState::start: 
			this->board.newBoard();
			onBoard = board.getAllChess();
			currentPlayer = Team::Red;
			isCheck = false;
			state = InGameState::selectChess;
			break;

		//====================================================inputFile==================================================	**start a game with input file
		case InGameState::inputFile:
			state = InGameState::oneSideWin;
			break;
		//====================================================selectChess================================================	**wait for press a object
		case InGameState::selectChess:
			for (auto& chess : onBoard) {
				chess->showSelect(viewer.getMousePosition(),currentPlayer);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&chess->isChoice()&&currentPlayer==chess->getTeam()) {
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
					state = InGameState::selectChess;
					break;
				}
			}
			break;

		//====================================================choiceMove================================================	**move the chess
		case InGameState::choiceMove:
			//board.getChess(coordChoiseChess)->move(board,coordChoiseToMove);
			board.moveChess(coordChoiseChess, coordChoiseToMove);
			state = InGameState::oneSideWin;
			break;

		//====================================================isCheck===================================================	**judge if one side is check or win
		case InGameState::isCheck:
			if (oneSideIsCheck(board, teamCheck)) {
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
			if (oneSideIsWin(board, teamWin)) {
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


		//draw
		viewer.update();
		viewer.clear();
		auto boardSprites = this->board.getAllSprite();
		viewer.drawSprite(boardSprites);
		viewer.drawCanMovePos(canMovePosCoord);
		viewer.drawRightSideObject(currentPlayer);
		if(isCheck)
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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