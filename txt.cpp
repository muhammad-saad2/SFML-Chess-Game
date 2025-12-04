#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void setupPawns(Sprite pawns[8], Texture& pawnTexture, float boardStartX, float boardStartY, float squareSize, int row);
void setuprooks(Sprite rook[8], Texture& rookTexture, float boardStartX, float boardStartY, float squareSize, int row);
void setupbishops(Sprite bishop[8], Texture& bishopTexture, float boardStartX, float boardStartY, float squareSize, int row);
void setupknights(Sprite knight[8], Texture& knightTexture, float boardStartX, float boardStartY, float squareSize, int row);
void setupqueen(Sprite queen[8], Texture& queenTexture, float boardStartX, float boardStartY, float squareSize, int row);
void setupking(Sprite king[8], Texture& kingTexture, float kingStartX, float boardStartY, float squareSize, int row);
Vector2i getBoardPos(Vector2f pos);
bool isLegalPawnMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isLegalRookMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isLegalBishopMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isLegalKnightMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isLegalQueenMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isLegalKingMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite);

// ----- New prototypes for check/checkmate -----
bool isSquareAttacked(int board[8][8], Vector2i square, bool byWhite);
Vector2i findKing(int board[8][8], bool isWhite);
bool isKingInCheck(int board[8][8], bool isWhite);
bool isMoveLegalAvoidingCheck(int board[8][8], Vector2i from, Vector2i to, bool isWhite);
bool isCheckmate(int board[8][8], bool isWhite);

// ----------------------------------------------
Vector2i kingInCheck(-1, -1);

int main() {
	int board[8][8] = { 0 };

	float startX = 85;
	float startY = 50;
	float squareSize = 102;

	RenderWindow window(VideoMode({ 1000,1000 }), "chess", Style::Close);
	RectangleShape Rectangle(Vector2f(100.f, 100.f));
	Rectangle.setPosition(5.f, 5.f);
	Rectangle.setFillColor(Color::Black);
	Rectangle.setOutlineColor(Color::Black);
	Rectangle.setOutlineThickness(1.f);

	//getiing white pawns
	Texture pawnTexture;
	if (!pawnTexture.loadFromFile("images/white-pawn.png")) {
		cout << "fail";
		return -1;
	}
	Sprite whitePawns[8];
	setupPawns(whitePawns, pawnTexture, startX, startY, squareSize, 1);

	//getting black pawn
	Texture blackpawnTexture;
	if (!blackpawnTexture.loadFromFile("images/black-pawn.png")) {
		cout << "black pawn path not found";
		return -1;
	}
	Sprite blackpawn[8];
	setupPawns(blackpawn, blackpawnTexture, startX, startY, squareSize, 6);

	//getting white rook
	Texture whiterookTexture;
	if (!whiterookTexture.loadFromFile("images/white-rook.png")) {
		cout << "rock not found";
		return -1;
	}
	Sprite whiterook[8];
	setuprooks(whiterook, whiterookTexture, startX, startY, squareSize, 0);

	//geting black rook
	Texture blackrookTexture;
	if (!blackrookTexture.loadFromFile("images/black-rook.png")) {
		cout << "rock not found";
		return -1;
	}
	Sprite blackrook[8];
	setuprooks(blackrook, blackrookTexture, startX, startY, squareSize, 7);

	//getting white bishop
	Texture whitebishopTexture;
	if (!whitebishopTexture.loadFromFile("images/white-bishop.png")) {
		cout << "bishop not found";
		return -1;
	}
	Sprite whitebishop[8];
	setupbishops(whitebishop, whitebishopTexture, startX, startY, squareSize, 0);

	//geting black bishop
	Texture blackbishopTexture;
	if (!blackbishopTexture.loadFromFile("images/black-bishop.png")) {
		cout << "bishop not found";
		return -1;
	}
	Sprite blackbishop[8];
	setupbishops(blackbishop, blackbishopTexture, startX, startY, squareSize, 7);

	//getting white knight
	Texture whiteknightTexture;
	if (!whiteknightTexture.loadFromFile("images/white-knight.png")) {
		cout << "knight not found";
		return -1;
	}
	Sprite whiteknight[8];
	setupknights(whiteknight, whiteknightTexture, startX, startY, squareSize, 0);
	//getting black knight
	Texture blackknightTexture;
	if (!blackknightTexture.loadFromFile("images/black-knight.png")) {
		cout << "knight not found";
		return -1;
	}
	Sprite blackknight[8];
	setupknights(blackknight, blackknightTexture, startX, startY, squareSize, 7);
	//geting white queen
	Texture whitequeenTexture;
	if (!whitequeenTexture.loadFromFile("images/white-queen.png")) {
		cout << "queen not found";
		return -1;
	}
	Sprite whitequeen[8];
	setupqueen(whitequeen, whitequeenTexture, startX, startY, squareSize, 0);
	//geting black queen
	Texture blackqueenTexture;
	if (!blackqueenTexture.loadFromFile("images/black-queen.png")) {
		cout << "queen not found";
		return -1;
	}
	Sprite blackqueen[8];
	setupqueen(blackqueen, blackqueenTexture, startX, startY, squareSize, 7);
	//geting white king
	Texture whitekingTexture;
	if (!whitekingTexture.loadFromFile("images/white-king.png")) {
		cout << "queen not found";
		return -1;
	}
	Sprite whiteking[8];
	setupking(whiteking, whitekingTexture, startX, startY, squareSize, 0);
	//geting black king
	Texture blackkingTexture;
	if (!blackkingTexture.loadFromFile("images/black-king.png")) {
		cout << "queen not found";
		return -1;
	}
	Sprite blackking[8];
	setupking(blackking, blackkingTexture, startX, startY, squareSize, 7);

	//linking to array
	// Fill board with white pawns
	for (int i = 0; i < 8; i++)
		board[1][i] = 1;

	// Black pawns
	for (int i = 0; i < 8; i++)
		board[6][i] = -1;

	// Rooks
	board[0][0] = board[0][7] = 2;
	board[7][0] = board[7][7] = -2;

	// Knights
	board[0][1] = board[0][6] = 3;
	board[7][1] = board[7][6] = -3;

	// Bishops
	board[0][2] = board[0][5] = 4;
	board[7][2] = board[7][5] = -4;

	// Queens
	board[0][3] = 5;
	board[7][3] = -5;

	// Kings
	board[0][4] = 6;
	board[7][4] = -6;

	// Load font for labels
	Font font;
	if (!font.loadFromFile("fonts/arial.ttf")) {
		cout << "Font not found!";
		return -1;
	}

	// Create reusable text objects
	Text colLabel;
	colLabel.setFont(font);
	colLabel.setCharacterSize(24);
	colLabel.setFillColor(Color::Black);

	Text rowLabel;
	rowLabel.setFont(font);
	rowLabel.setCharacterSize(24);
	rowLabel.setFillColor(Color::Black);

	

	Vector2i selectedSquare(-1, -1);
	bool squareSelected = false;

	//draging;
	bool isDragging = false;
	int dragGroup = -1;
	int dragIndex = -1;
	Vector2f dragOffset;
	//final drop
	Vector2i lastDropped(-1, -1);
	bool hasLastDropped = false;

	Vector2f originalPos;
	Vector2i originalSquare(-1, -1);

	bool whiteTurn = true;

	bool gameOver = false;
	string statusStr = "";

	//main logic
	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			// if gameOver, ignore mouse interactions (except close)
			if (gameOver) continue;

			// Mouse pressed
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePosF = window.mapPixelToCoords(Mouse::getPosition(window));

				// check white pawns
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whitePawns[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whitePawns[i].getPosition().x - 50) / 102);
						int row = (int)((whitePawns[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 0; dragIndex = i;
							dragOffset = mousePosF - whitePawns[i].getPosition();
							originalPos = whitePawns[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// check black pawns
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackpawn[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackpawn[i].getPosition().x - 50) / 102);
						int row = (int)((blackpawn[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 1; dragIndex = i;
							dragOffset = mousePosF - blackpawn[i].getPosition();
							originalPos = blackpawn[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// white rooks
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whiterook[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whiterook[i].getPosition().x - 50) / 102);
						int row = (int)((whiterook[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 2; dragIndex = i;
							dragOffset = mousePosF - whiterook[i].getPosition();
							originalPos = whiterook[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// black rooks
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackrook[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackrook[i].getPosition().x - 50) / 102);
						int row = (int)((blackrook[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 3; dragIndex = i;
							dragOffset = mousePosF - blackrook[i].getPosition();
							originalPos = blackrook[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// white bishops
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whitebishop[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whitebishop[i].getPosition().x - 50) / 102);
						int row = (int)((whitebishop[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 4; dragIndex = i;
							dragOffset = mousePosF - whitebishop[i].getPosition();
							originalPos = whitebishop[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// black bishops
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackbishop[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackbishop[i].getPosition().x - 50) / 102);
						int row = (int)((blackbishop[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 5; dragIndex = i;
							dragOffset = mousePosF - blackbishop[i].getPosition();
							originalPos = blackbishop[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// white knights
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whiteknight[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whiteknight[i].getPosition().x - 50) / 102);
						int row = (int)((whiteknight[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 6; dragIndex = i;
							dragOffset = mousePosF - whiteknight[i].getPosition();
							originalPos = whiteknight[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// black knights
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackknight[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackknight[i].getPosition().x - 50) / 102);
						int row = (int)((blackknight[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 7; dragIndex = i;
							dragOffset = mousePosF - blackknight[i].getPosition();
							originalPos = blackknight[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// white queens
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whitequeen[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whitequeen[i].getPosition().x - 50) / 102);
						int row = (int)((whitequeen[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 8; dragIndex = i;
							dragOffset = mousePosF - whitequeen[i].getPosition();
							originalPos = whitequeen[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// black queens
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackqueen[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackqueen[i].getPosition().x - 50) / 102);
						int row = (int)((blackqueen[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 9; dragIndex = i;
							dragOffset = mousePosF - blackqueen[i].getPosition();
							originalPos = blackqueen[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// white kings
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (whiteking[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((whiteking[i].getPosition().x - 50) / 102);
						int row = (int)((whiteking[i].getPosition().y - 50) / 102);
						if (board[row][col] > 0 && whiteTurn) {
							isDragging = true; dragGroup = 10; dragIndex = i;
							dragOffset = mousePosF - whiteking[i].getPosition();
							originalPos = whiteking[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}

				// black kings
				for (int i = 0; i < 8 && !isDragging; i++) {
					if (blackking[i].getGlobalBounds().contains(mousePosF)) {
						int col = (int)((blackking[i].getPosition().x - 50) / 102);
						int row = (int)((blackking[i].getPosition().y - 50) / 102);
						if (board[row][col] < 0 && !whiteTurn) {
							isDragging = true; dragGroup = 11; dragIndex = i;
							dragOffset = mousePosF - blackking[i].getPosition();
							originalPos = blackking[i].getPosition();
							originalSquare = getBoardPos(originalPos);
						}
					}
				}
			}

			// Mouse moved
			if (event.type == Event::MouseMoved && isDragging) {
				Vector2f mousePosF = window.mapPixelToCoords(Mouse::getPosition(window));
				switch (dragGroup) {
				case 0: whitePawns[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 1: blackpawn[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 2: whiterook[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 3: blackrook[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 4: whitebishop[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 5: blackbishop[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 6: whiteknight[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 7: blackknight[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 8: whitequeen[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 9: blackqueen[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 10: whiteking[dragIndex].setPosition(mousePosF - dragOffset); break;
				case 11: blackking[dragIndex].setPosition(mousePosF - dragOffset); break;
				default: break;
				}
			}


			// Mouse released
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && isDragging) {
				Vector2f mousePosF = window.mapPixelToCoords(Mouse::getPosition(window));
				int col = (mousePosF.x - 50) / 102;
				int row = (mousePosF.y - 50) / 102;
				Vector2i to(col, row);
				Vector2i from = originalSquare;

				int piece = 0;
				if (from.x >= 0 && from.x < 8 && from.y >= 0 && from.y < 8) piece = board[from.y][from.x];
				bool isWhite = (piece > 0);

				bool valid = false;

				// check bounds
				if (to.x >= 0 && to.x < 8 && to.y >= 0 && to.y < 8) {
					int target = board[to.y][to.x];
					// cannot capture own piece
					if ((target > 0 && isWhite) || (target < 0 && !isWhite)) {
						valid = false;
					}
					else {
						int absPiece = abs(piece);
						bool baseValid = false;
						if (absPiece == 1) baseValid = isLegalPawnMove(board, from, to, isWhite);
						else if (absPiece == 2) baseValid = isLegalRookMove(board, from, to, isWhite);
						else if (absPiece == 3) baseValid = isLegalKnightMove(board, from, to, isWhite);
						else if (absPiece == 4) baseValid = isLegalBishopMove(board, from, to, isWhite);
						else if (absPiece == 5) baseValid = isLegalQueenMove(board, from, to, isWhite);
						else if (absPiece == 6) baseValid = isLegalKingMove(board, from, to, isWhite);

						// Now ensure move doesn't leave own king in check
						if (baseValid) {
							if (isMoveLegalAvoidingCheck(board, from, to, isWhite)) valid = true;
							else valid = false;
						}
					}
				}

				// finalize move
				if (valid) {
					// capture: move captured sprite off-screen
					if (board[to.y][to.x] != 0) {
						int captured = board[to.y][to.x];
						// find and hide the sprite belonging to captured piece at that square
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whitePawns[i].getPosition().x - 50) / 102);
							p.y = (int)((whitePawns[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whitePawns[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackpawn[i].getPosition().x - 50) / 102);
							p.y = (int)((blackpawn[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackpawn[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whiterook[i].getPosition().x - 50) / 102);
							p.y = (int)((whiterook[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whiterook[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackrook[i].getPosition().x - 50) / 102);
							p.y = (int)((blackrook[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackrook[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whitebishop[i].getPosition().x - 50) / 102);
							p.y = (int)((whitebishop[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whitebishop[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackbishop[i].getPosition().x - 50) / 102);
							p.y = (int)((blackbishop[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackbishop[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whiteknight[i].getPosition().x - 50) / 102);
							p.y = (int)((whiteknight[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whiteknight[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackknight[i].getPosition().x - 50) / 102);
							p.y = (int)((blackknight[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackknight[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whitequeen[i].getPosition().x - 50) / 102);
							p.y = (int)((whitequeen[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whitequeen[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackqueen[i].getPosition().x - 50) / 102);
							p.y = (int)((blackqueen[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackqueen[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((whiteking[i].getPosition().x - 50) / 102);
							p.y = (int)((whiteking[i].getPosition().y - 50) / 102);
							if (p == to && captured > 0) { whiteking[i].setPosition(-200, -200); break; }
						}
						for (int i = 0; i < 8; i++) {
							Vector2i p;
							p.x = (int)((blackking[i].getPosition().x - 50) / 102);
							p.y = (int)((blackking[i].getPosition().y - 50) / 102);
							if (p == to && captured < 0) { blackking[i].setPosition(-200, -200); break; }
						}
					}

					board[to.y][to.x] = piece;
					board[from.y][from.x] = 0;

					// move sprite to final snapped position
					int finalX = to.x * 102 + 50;
					int finalY = to.y * 102 + 50;
					switch (dragGroup) {
					case 0: whitePawns[dragIndex].setPosition(finalX, finalY); break;
					case 1: blackpawn[dragIndex].setPosition(finalX, finalY); break;
					case 2: whiterook[dragIndex].setPosition(finalX, finalY); break;
					case 3: blackrook[dragIndex].setPosition(finalX, finalY); break;
					case 4: whitebishop[dragIndex].setPosition(finalX, finalY); break;
					case 5: blackbishop[dragIndex].setPosition(finalX, finalY); break;
					case 6: whiteknight[dragIndex].setPosition(finalX, finalY); break;
					case 7: blackknight[dragIndex].setPosition(finalX, finalY); break;
					case 8: whitequeen[dragIndex].setPosition(finalX, finalY); break;
					case 9: blackqueen[dragIndex].setPosition(finalX, finalY); break;
					case 10: whiteking[dragIndex].setPosition(finalX, finalY); break;
					case 11: blackking[dragIndex].setPosition(finalX, finalY); break;
					}


					whiteTurn = !whiteTurn;


					// after move, check if opponent is in check or checkmate
					bool opponentIsWhite = !whiteTurn;



					// reset
					kingInCheck = Vector2i(-1, -1);

					// check for check on side that must move
					bool inCheck = isKingInCheck(board, whiteTurn);

					if (inCheck) {
						Vector2i k = findKing(board, whiteTurn);  // get king position
						kingInCheck = k;

						cout << "CHECK!\n";

						if (isCheckmate(board, whiteTurn)) {
							cout << "CHECKMATE!\n";
							cout << "game over!\n";
							gameOver = true;
						}
					}


				}
				else {
					// revert to original position if invalid
					switch (dragGroup) {
					case 0: whitePawns[dragIndex].setPosition(originalPos); break;
					case 1: blackpawn[dragIndex].setPosition(originalPos); break;
					case 2: whiterook[dragIndex].setPosition(originalPos); break;
					case 3: blackrook[dragIndex].setPosition(originalPos); break;
					case 4: whitebishop[dragIndex].setPosition(originalPos); break;
					case 5: blackbishop[dragIndex].setPosition(originalPos); break;
					case 6: whiteknight[dragIndex].setPosition(originalPos); break;
					case 7: blackknight[dragIndex].setPosition(originalPos); break;
					case 8: whitequeen[dragIndex].setPosition(originalPos); break;
					case 9: blackqueen[dragIndex].setPosition(originalPos); break;
					case 10: whiteking[dragIndex].setPosition(originalPos); break;
					case 11: blackking[dragIndex].setPosition(originalPos); break;
					}
				}

				lastDropped = to;
				hasLastDropped = true;

				isDragging = false;
				dragGroup = -1;
				dragIndex = -1;


			}
		}



		window.clear(Color::White);

		// draw board
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				Rectangle.setPosition(50 + col * 102, 50 + row * 102);
				if ((row + col) % 2 == 0)
					Rectangle.setFillColor(Color::White);
				else
					Rectangle.setFillColor(Color(118, 150, 86));
				window.draw(Rectangle);
			}
		}

		//  draw highlight
		if (squareSelected) {
			RectangleShape highlight(Vector2f(102.f, 102.f));
			highlight.setPosition(50 + selectedSquare.x * 102, 50 + selectedSquare.y * 102);
			highlight.setFillColor(Color(255, 255, 0, 100));
			window.draw(highlight);
		}
		//final position
		if (hasLastDropped) {
			RectangleShape redHighlight(Vector2f(102.f, 102.f));
			redHighlight.setPosition(50 + lastDropped.x * 102, 50 + lastDropped.y * 102);
			redHighlight.setFillColor(Color(255, 0, 0, 120));  // semi-transparent red
			window.draw(redHighlight);
		}


		// draw pieces
		for (int i = 0; i < 8; i++) {
			window.draw(whitePawns[i]);
			window.draw(blackpawn[i]);
			window.draw(whiterook[i]);
			window.draw(blackrook[i]);
			window.draw(whitebishop[i]);
			window.draw(blackbishop[i]);
			window.draw(whiteknight[i]);
			window.draw(blackknight[i]);
			window.draw(whitequeen[i]);
			window.draw(blackqueen[i]);
			window.draw(whiteking[i]);
			window.draw(blackking[i]);
		}

		// draw labels
		for (int i = 0; i < 8; i++) {
			colLabel.setString(string(1, 'A' + i));
			colLabel.setPosition(95 + i * 102, 880);
			window.draw(colLabel);
		}
		for (int i = 0; i < 8; i++) {
			rowLabel.setString(to_string(8 - i));
			rowLabel.setPosition(30, 70 + i * 102);
			window.draw(rowLabel);
		}
		if (kingInCheck.x != -1) {
			RectangleShape redBox(Vector2f(102.f, 102.f));
			redBox.setPosition(50 + kingInCheck.x * 102,
				50 + kingInCheck.y * 102);
			redBox.setFillColor(Color(255, 0, 0, 130)); // transparent red
			window.draw(redBox);
		}

		
		

		window.display();
	}



	return 0;
}


void setupPawns(Sprite pawns[], Texture& pawnTexture, float boardStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	for (int i = 0; i < 8; ++i) {
		pawns[i].setTexture(pawnTexture);
		pawns[i].setScale(scale, scale);
		pawns[i].setPosition(i * squareSize + 50, row * squareSize + 50);
	}

}
void setuprooks(Sprite rook[], Texture& rookTexture, float boardStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	rook[0].setTexture(rookTexture);
	rook[0].setScale(scale, scale);
	rook[0].setPosition(0 * squareSize + 50, row * squareSize + 50);

	rook[7].setTexture(rookTexture);
	rook[7].setScale(scale, scale);
	rook[7].setPosition(7 * squareSize + 50, row * squareSize + 50);
}

void setupbishops(Sprite bishop[], Texture& bishopTexture, float boardStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	bishop[2].setTexture(bishopTexture);
	bishop[2].setScale(scale, scale);
	bishop[2].setPosition(2 * squareSize + 50, row * squareSize + 50);

	bishop[5].setTexture(bishopTexture);
	bishop[5].setScale(scale, scale);
	bishop[5].setPosition(5 * squareSize + 50, row * squareSize + 50);
}
void setupknights(Sprite knight[], Texture& knightTexture, float boardStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	knight[1].setTexture(knightTexture);
	knight[1].setScale(scale, scale);
	knight[1].setPosition(1 * squareSize + 50, row * squareSize + 50);

	knight[6].setTexture(knightTexture);
	knight[6].setScale(scale, scale);
	knight[6].setPosition(6 * squareSize + 50, row * squareSize + 50);
}
void setupqueen(Sprite queen[], Texture& queenTexture, float boardStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	queen[3].setTexture(queenTexture);
	queen[3].setScale(scale, scale);
	queen[3].setPosition(3 * squareSize + 50, row * squareSize + 50);
}

void setupking(Sprite king[], Texture& kingTexture, float kingStartX, float boardStartY, float squareSize, int row) {
	float scale = 0.7f;

	king[4].setTexture(kingTexture);
	king[4].setScale(scale, scale);
	king[4].setPosition(4 * squareSize + 50, row * squareSize + 50);
}

Vector2i getBoardPos(Vector2f pos) {
	int col = (pos.x - 50) / 102;
	int row = (pos.y - 50) / 102;
	return Vector2i(col, row);
}

bool isLegalPawnMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	int direction = isWhite ? 1 : -1;
	int startRow = isWhite ? 1 : 6;
	int dx = to.x - from.x;
	int dy = to.y - from.y;

	if (to.x < 0 || to.x >= 8 || to.y < 0 || to.y >= 8) return false;

	// forward one step
	if (dx == 0 && dy == direction && board[to.y][to.x] == 0) return true;

	// first double step
	if (dx == 0 && dy == 2 * direction && from.y == startRow &&
		board[from.y + direction][from.x] == 0 && board[to.y][to.x] == 0)
		return true;

	// diagonal capture
	if (abs(dx) == 1 && dy == direction && board[to.y][to.x] != 0 &&
		(board[to.y][to.x] > 0) != isWhite)
		return true;

	return false;
}

bool isLegalRookMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	if (from.x == to.x && from.y == to.y) return false;
	if (from.x != to.x && from.y != to.y) return false;

	int dx = (to.x > from.x) ? 1 : (to.x < from.x) ? -1 : 0;
	int dy = (to.y > from.y) ? 1 : (to.y < from.y) ? -1 : 0;

	int x = from.x + dx, y = from.y + dy;
	while (x != to.x || y != to.y) {
		if (board[y][x] != 0) return false;
		x += dx; y += dy;
	}
	return true;
}

bool isLegalBishopMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	if (from.x == to.x && from.y == to.y) return false;

	int dx = to.x - from.x;
	int dy = to.y - from.y;
	if (abs(dx) != abs(dy)) return false;

	int sx = (dx > 0) ? 1 : -1;
	int sy = (dy > 0) ? 1 : -1;

	int x = from.x + sx, y = from.y + sy;
	while (x != to.x && y != to.y) {
		if (board[y][x] != 0) return false;
		x += sx; y += sy;
	}
	return true;
}

bool isLegalKnightMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1)) return true;
	return false;
}

bool isLegalQueenMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	//queen = rook + bishop;
	return isLegalRookMove(board, from, to, isWhite) || isLegalBishopMove(board, from, to, isWhite);
}

bool isLegalKingMove(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	if (dx <= 1 && dy <= 1) return true;
	return false;
}

// ---------------- New functions: attack/check/mate detection ----------------

Vector2i findKing(int board[8][8], bool isWhite) {
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if (isWhite && board[r][c] == 6) return Vector2i(c, r);
			if (!isWhite && board[r][c] == -6) return Vector2i(c, r);
		}
	}
	return Vector2i(-1, -1); // not found (shouldn't happen)
}

// Checks if 'square' (col,row) is attacked by ANY piece of color 'byWhite'
bool isSquareAttacked(int board[8][8], Vector2i square, bool byWhite) {
	// scan all squares for a piece of byWhite color that can move to 'square' (capture)
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			int p = board[r][c];
			if (p == 0) continue;
			bool pieceIsWhite = (p > 0);
			if (pieceIsWhite != byWhite) continue;

			Vector2i from(c, r);
			int absP = abs(p);

			// For pawns we need to check attack pattern (diagonals) separately because isLegalPawnMove checks occupancy and direction (but that is OK too)
			if (absP == 1) {
				int dir = pieceIsWhite ? 1 : -1;
				// pawn attacks one step diagonally forward
				if ((square.x == c + 1 || square.x == c - 1) && (square.y == r + dir)) return true;
				continue;
			}
			if (absP == 2) { // rook
				if (isLegalRookMove(board, from, square, pieceIsWhite)) return true;
			}
			else if (absP == 3) { // knight
				if (isLegalKnightMove(board, from, square, pieceIsWhite)) return true;
			}
			else if (absP == 4) { // bishop
				if (isLegalBishopMove(board, from, square, pieceIsWhite)) return true;
			}
			else if (absP == 5) { // queen
				if (isLegalQueenMove(board, from, square, pieceIsWhite)) return true;
			}
			else if (absP == 6) { // king - adjacent squares
				if (isLegalKingMove(board, from, square, pieceIsWhite)) return true;
			}
		}
	}
	return false;
}

// returns true if the named side's king is in check
bool isKingInCheck(int board[8][8], bool isWhite) {
	Vector2i kingPos = findKing(board, isWhite);
	if (kingPos.x == -1) return false; // problem, but treat as no check
	return isSquareAttacked(board, kingPos, !isWhite);
}

// simulate the move and check whether it leaves own king in check
bool isMoveLegalAvoidingCheck(int board[8][8], Vector2i from, Vector2i to, bool isWhite) {
	// copy board
	int tmp[8][8];
	for (int r = 0; r < 8; ++r)
		for (int c = 0; c < 8; ++c)
			tmp[r][c] = board[r][c];

	int piece = tmp[from.y][from.x];
	// make move on temp board
	tmp[to.y][to.x] = piece;
	tmp[from.y][from.x] = 0;

	// if moving the king, king position changed -- but isKingInCheck checks the board directly
	return !isKingInCheck(tmp, isWhite);
}

// returns true if side is checkmated (king in check AND no legal move to escape)
bool isCheckmate(int board[8][8], bool isWhite) {
	// if king not in check, not checkmate
	if (!isKingInCheck(board, isWhite)) return false;

	// try every move by every piece of that color; if any legal move avoids check, not checkmate
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			int p = board[r][c];
			if (p == 0) continue;
			bool pieceIsWhite = (p > 0);
			if (pieceIsWhite != isWhite) continue;

			Vector2i from(c, r);

			// brute force candidate destinations
			for (int tr = 0; tr < 8; ++tr) {
				for (int tc = 0; tc < 8; ++tc) {
					Vector2i to(tc, tr);
					// skip same square
					if (from.x == to.x && from.y == to.y) continue;

					// cannot capture own piece
					int target = board[to.y][to.x];
					if ((target > 0 && pieceIsWhite) || (target < 0 && !pieceIsWhite)) continue;

					bool baseValid = false;
					int absP = abs(p);
					if (absP == 1) baseValid = isLegalPawnMove(board, from, to, pieceIsWhite);
					else if (absP == 2) baseValid = isLegalRookMove(board, from, to, pieceIsWhite);
					else if (absP == 3) baseValid = isLegalKnightMove(board, from, to, pieceIsWhite);
					else if (absP == 4) baseValid = isLegalBishopMove(board, from, to, pieceIsWhite);
					else if (absP == 5) baseValid = isLegalQueenMove(board, from, to, pieceIsWhite);
					else if (absP == 6) baseValid = isLegalKingMove(board, from, to, pieceIsWhite);

					if (!baseValid) continue;

					// if move is legal in base sense, check if it avoids check
					if (isMoveLegalAvoidingCheck(board, from, to, pieceIsWhite)) return false;
				}
			}
		}
	}

	// no legal move found to avoid check -> checkmate
	return true;
}
