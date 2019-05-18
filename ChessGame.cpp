#include <limits>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>


#include "../HeaderFiles/ChessGame.hpp"

#define INPUTWAY 1

using namespace std;

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}


void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;

}


/*
 * ektypwsh x,y arithmwn kai pioniwn
 */
void Board::printBoard() {
	using namespace std;
	cout << " y:  0  1  2  3  4  5  6  7 " << endl << "x:" << endl; //typwse tous arithmous twn sthlwn
	//8X8 diplo for loop gia na gemisoume ton pinaka square me plhroforia gia kathe thesh ths skakieras
	for (int i = 0; i < 8; i++) {
		cout << " " << i << "   "; //typwse tous arithmous twn grammwn
		for (int j = 0; j < 8; j++) {
			Piece p = square[i][j].getPiece(); //kaloume thn methodo getPiece gia na mathoume to eidos tou pioniou
			Color c = square[i][j].getColor();

			if (KING == p) {
				if (WHITE == c) {
					cout << " K ";
				} else {
					cout << " k ";
				}

			} else if (QUEEN == p) {
				if(WHITE == c) {
					cout << " Q ";
				} else {
					cout << " q ";
				}
			} else if (BISHOP == p) {
				if(WHITE == c) {
					cout << " B ";
				} else {
					cout << " b ";
				}
			} else if (KNIGHT == p) {
				if(WHITE == c) {
					cout << " H ";
				} else {
					cout << " h ";
				}
			} else if (ROOK == p) {
				if(WHITE == c) {
					cout << " R ";
				} else {
					cout << " r ";
				}
			} else if (PAWN == p) {
				if(WHITE == c) {
					cout << " P ";
				} else {
					cout << " p ";
				}
			} else if(EMPTY == p) {
				cout << " " << "_" << " ";
			} else {
				cout << "Lathos";
			}
		//}

/*
			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
				break;
			case BISHOP:(c == WHITE) ? cout << " B " : cout << " b ";
				break;
			case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h ";
				break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
				break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
				break;
			case EMPTY: cout << " " << "_" << " "; // ASCII kwdikos gia to symvolo twn tetragwnwn
				break;
			default: cout << "XXX";
				break;
			}
*/
		}
		cout << endl;
	}


}


void loop(int &x, int &y) {
	using namespace std;
	int columnCounter = 0;
	int rowCounter = 0;
	while(1	){
		system ("cls");
		//system("pause");
		if(GetAsyncKeyState(VK_DOWN)) {
			rowCounter++;
			cout << "VK-DOWN" << endl;
		}
		if(GetAsyncKeyState(VK_UP)){
			cout << "VK-UP" << endl;
			rowCounter--;
		}
		if(GetAsyncKeyState(VK_LEFT)) {
			cout << "VK-LEFT" << endl;
			columnCounter--;
		}
		if(GetAsyncKeyState(VK_RIGHT)) {
			cout << "VK-RIGHT" << endl;
			columnCounter++;
		}
		if (GetAsyncKeyState('\r')) {
			break;
		}
		cout << "\nx = " << rowCounter << "\ty = " << columnCounter << endl;
	}
	x = rowCounter;
	y = columnCounter;
}






/*
 * H methodos doMove ypologizei tis
 * syntetagmenes ths arxikhs theshs
 * kai tou proorismou
 */
bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;

	do {
		if (WHITE == turn) {
			 cout << "Κίνηση ’σπρο" << endl;
		} else {
			cout << "Κίνηση Μαύρο" << endl;
		}

		cout << "Πληκτολόγησε την κίνηση σαν ένα string 4 χαρακτήρων ως προς τους άξονες χ και y." << endl;


		//gist.github.com/jpkrause/4a1aa400d45197ca3253
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//http://www.cplusplus.com/articles/4z18T05o/
		system("CLS");
		/*
		 * H akeraia timh tou ASCII xarakthra 0 einai 48.
		 * Oi ASCII times mesa sto string move anamenetai na einai
		 * metaksy tou xarakthra '0' kai tou xarakthra '9'.
		 * H akeraia timh tou ASCII xarakthra tou 1 einai 49.
		 * 49-48=1
		 */



		if (INPUTWAY) {
			cin >> move; //pairnoume thn kinhsh apo to plhktrologio
			x1 = move[0] - 48;
			y1 = move[1] - 48;
			x2 = move[2] - 48;
			y2 = move[3] - 48;
		} else if (!INPUTWAY) {
			loop(x1, y1);
			system ("cls");
			system("pause");
			loop(x2, y2);
		}




		//Elegkse an dialegoume pioni tou swstou xrwmatos, swsth seira.
		if (getSquare(x1, y1)->getColor() == turn)
		{

			//Elegxos an h kinhsh einai valid.Kai h makeMove ektelei thn kinhsh.
			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Λάθος Κίνηση" << endl;
			}
			else
			{
				Square* src = getSquare(x1, y1);
				Square* dest = getSquare(x2, y2);
				//elegkse an exoume Roua Mat
				if (getSquare(x2, y2)->getPiece() == KING) // an ekei pou katalhksame einai o vasilias
				{
					if (getSquare(x1, y1)->getColor() == WHITE) // kai an emeis eimaste WHITE tote ROUA MAT
					{
						cout << "ΝΙΚΗ ΛΕΥΚΟ" << endl;
						return false;
					}
					else if (getSquare(x1, y1)->getColor() == BLACK)
					{
						cout << "ΝΙΚΗ ΜΑΥΡΟ" << endl;
						return false;
					}
				}
				dest->setSpace(src);
				src->setEmpty();
				stop = true;
				saveToBinFile("./record.dat");
			}
		}
		else
			cout << "Λάθος πιόνι.Προσπάθησε ξανά" << endl;
	} while (!stop); //while(true)



	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;

}

/*
 * H methodos setBoard thetei tis times
 * twn pediwn tou kathe Square object
 * mesa ston 8X8 pinaka square
 */
void Board::setBoard()
{
	/*kingsPos[0][0].setPieceAndColor(KING, WHITE);
	kingsPos[0][0].setX(4);
	kingsPos[0][0].setY(0);
	kingsPos[0][1].setPieceAndColor(KING, BLACK);
	kingsPos[0][1].setX(4);
	kingsPos[0][1].setY(7);*/
	//Arxikopoioume ola ta Square objects pou einai color = WHITE AND piece = oxi stratiwths AND oxi EMPTY
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	//Arxikopoioume ola ta Square objects pou einai color = BLACK AND piece = oxi stratiwths AND oxi EMPTY
	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	////Arxikopoioume ola ta Square objects pou einai type = PAWN (stratiwths)
	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, WHITE); //vazoume mono tous asprous stratiwtes
		square[i][6].setPieceAndColor(PAWN, BLACK); //vazoume mono tous mavrous stratiwtes

	}
	//Arxikopoioume ola ta Square objects pou einai piece = EMPTY AND color = NONE
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
	//Arxikopoihsh twn x kai y pediwn tou kathe Square object mesa ston pinaka square
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			/*
			 *  se kathe square object dinw ena x to opoio einai mikrotero kata 1 apo to object
			 *  pou vrisketai amesws deksia tou. Omoiws kai gia ton aksona y.
			 */
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}

/*
 * H methodos playGame kalei thn methodo
 * pou typwnei thn skakiera kai thn
 * methodo pou einai ypeuthynh gia
 * tis kinhseis
 */
bool Board::playGame()
{
	system("cls"); //clear screen for everytime we make move
	printBoard(); //typwse thn skakiera
	return doMove();
}

/*
 * H moveKing eksasfalizei oti
 * o King tha kinhthei akrivws
 * mia thesh ston aksona ton x
 * AND mia thesh ston aksona ton y
 */
bool Board::checkIfKing(Square* thisKing, Square* thatSpace) {

	if (abs(thatSpace->getX() - thisKing->getX()) == 1 || abs(thatSpace->getX() - thisKing->getX()) == 0 )
		if (abs(thatSpace->getY() - thisKing->getY()) == 1 || abs(thatSpace->getY() - thisKing->getY()) == 0)
		{
			return true;
		} else return false;
	else return false;
}

/*
 * Ayth h methodos pragmatopoiei thn kinhsh ths vasilissas.
 * H vasilissa einai o syndiasmos tou pyrgou kai tou aksiwmatikou
 * giyato h ylopoihsh ths vasizetai stis methodous tou pyrgou kai
 * tou aksiwmatikou.
 *
 */
bool Board::checkIfQueen(Square* thisQueen, Square* thatSpace) {

	if (thisQueen->getX() != thatSpace->getX() || thisQueen->getY() != thatSpace->getY())
	{

		if ((thisQueen->getX() == thatSpace->getX()) || (thisQueen->getY() == thatSpace->getY()))
		{
			return checkIfRook(thisQueen, thatSpace);
		}
		else if (abs(thisQueen->getX() - thatSpace->getX()) == abs(thisQueen->getY() - thatSpace->getY()))
		{
			return checkIfBishop(thisQueen, thatSpace);
		}
		else
			return false;
	}
	return true;
}

/*
 * H methodos checkIfBishop kinei to alogo.
 * thisBishop : Square object, to Square object sthn thesh afethrias
 * thatSpace : Square object, to Square object sthn thesh proorismou
 */
bool Board::checkIfBishop(Square* thisBishop, Square* thatSpace)
{
	/*
	 * O aksiwmatikos kineitai me tropo tetoio wste
	 * h apolyth timh ths diaforas ths grammhs afethrias
	 * me thn grammh proorismou einai panta ish me thn
	 * apolyth timh ths diaforas ths sthlhs afethrias me
	 * thn sthlh proorismou.
	 */
	if (abs(thisBishop->getX() - thatSpace->getX()) == abs(thisBishop->getY() - thatSpace->getY()))
	{
			if (false == moveDiagonal(thisBishop,thatSpace))
				return false;
	}
	else
	{
		return false;
	}
	return true;
}

/*
 * H methodos checkIfKnight kinei to alogo.
 * thisKnight : Square object, to Square object sthn thesh afethrias
 * thatSpace : Square object, to Square object sthn thesh proorismou
 * H methodos epistrefei mia bool timh
 *
 */
bool Board::checkIfKnight(Square* thisKnight, Square* thatSpace)
{
	/*
	 * (An h apolyth timh ths diaforas ths grammhs afethrias me thn
	 * grammh proorismou einai 2 AND h apolyth timh ths diaforas
	 * ths sthlhs afethrias me thn sthlh proorismou einai 1) OR
	 * (h apolyth timh ths diaforas ths grammhs afethrias me thn
	 * grammh proorismou einai 1 AND h apolyth timh ths diaforas
	 * ths sthlhs afethrias me thn sthlh proorismou einai 2) tote
	 * metakinhse to alogo alliws return false.
	 */
	if ((abs(thisKnight->getX() - thatSpace->getX()) == 2 && abs(thisKnight->getY() - thatSpace->getY()) == 1) ||
		(abs(thisKnight->getX() - thatSpace->getX()) == 1 && abs(thisKnight->getY() - thatSpace->getY()) == 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Board::moveDiagonal(Square *src, Square *dest)
{
	int xIncrement = (dest->getX() - src->getX()) / (abs(dest->getX() - src->getX()));
	int yIncrement = (dest->getY() - src->getY()) / (abs(dest->getY() - src->getY()));

	for (int i = 1; i < abs(src->getX() - dest->getX()); i++)
	{
		if (square[src->getX() + xIncrement*i][src->getY() + yIncrement*i].getColor() != NONE)
			return false;
	}
	return true;
}

bool Board::moveBackwards(Square *src, Square *dest)
{
	int yDecrement = -1;
	for (int i = src->getY() + yDecrement; i != dest->getY(); i += yDecrement)
		{

			if (square[src->getX()][i].getColor() != NONE)
				return false;
		}
		return true;
}


bool Board::moveForward(Square *src, Square *dest)
{
	int yIncrement = 1;
	for (int i = src->getY() + yIncrement; i != dest->getY(); i += yIncrement)
		{

			if (square[src->getX()][i].getColor() != NONE)
				return false;
		}
		return true;
}


bool Board::moveForwardOrBackwards(Square *src, Square *dest)
{
	int yIncrement = (dest->getY() - src->getY()) / (abs(dest->getY() - src->getY()));
	if (-1 == yIncrement)
	{
		return moveBackwards(src, dest);
	}
	return moveForward(src, dest);

}

bool Board::moveUp(Square *src, Square *dest)
{
	int xDecrement = -1;
	for (int i = src->getX() + xDecrement; i != dest->getX(); i += xDecrement)
	{
		if (square[i][dest->getY()].getColor() != NONE)
			return false;
	}
	return true;
}

bool Board::moveDown(Square *src, Square *dest)
{
	int xIncrement = 1;
	for (int i = src->getX() + xIncrement; i != dest->getX(); i += xIncrement)
	{
		if (square[i][dest->getY()].getColor() != NONE)
			return false;
	}
	return true;
}

bool Board::moveUpDown(Square *src, Square *dest)
{
	int xIncrement = (dest->getX() - src->getX()) / (abs(dest->getX() - src->getX()));
	if (-1 == xIncrement)
	{
		return moveUp(src, dest);
	}
	return moveDown(src, dest);
}








/*
 * H checkIfRook ektelei thn kinhsh tou pyrgou.
 * thisRook : Square object, to Square object sthn thesh afethrias
 * thatSpace : Square object, to Square object sthn thesh proorismou
 * H methodos epistrefei mia bool timh
 * H moveRook arxika pairnei thn thesh afethrias kai thn thesh proorismou
 * Arxika elegxoume an paramenoume sthn idia grammh AND allazei h sthlh h'
 * an paramenoume sthn idia sthlh AND allazei h grammh.
 */
bool Board::checkIfRook(Square* thisRook, Square* thatSpace)
{
	if (((thisRook->getX() == thatSpace->getX()) && (thisRook->getY() != thatSpace->getY())))
	{
		if (false == moveForwardOrBackwards(thisRook, thatSpace))
			return false;
	}
	else if ((thisRook->getY() == thatSpace->getY()) && (thisRook->getX() != thatSpace->getX()))
	{
		if (false == moveUpDown(thisRook, thatSpace))
			return false;
	}
	else
		return false;
	return true;
}

bool Board::checkIfPawn(Square* thisPawn, Square* thatSpace) {

	//Elegxos an einai kinhsh leukou stratiwth
	if (thisPawn->getColor() == WHITE)
	{
		/*
		 * Kinhsh leukou stratiwth mono eutheia se adeia thesh
		 * 1 h' 2 theseis mprosta
		 * To if statement einai to ekshs :
		 * An h grammh afethrias einai ish me thn
		 * grammh proorismou - dld x1=x2 - AND
		 * ((h sthlh proorismou isoutai me
		 * thn sthlh afethrias + 1 - y2=y1+1 -) OR
		 * ((An h sthlh proorismou isoutai me thn sthlh afethrias + 2 ) AND (h sthlh afethrias isoutai me 1))
		 *  AND to tetragwno proorismou einai adeio
		 * tote o leukos stratiwths mporei na kinhthei mia h' dyo theseis mprosta.
		 */
		if ((thisPawn->getX() == thatSpace->getX()) &&
		    ((thatSpace->getY() == thisPawn->getY() + 1) || ((thatSpace->getY() == thisPawn->getY() + 2) && (thisPawn->getY() == 1))) &&
			(thatSpace->getColor() == NONE))
		{
			return true;
		}
		/*
		 * O leukos stratiwths trwei ton mayro.
		 * (An h grammh proorismou einai ish me thn
		 * grammh afethrias + 1 - dld x2=x1+1(mia grammh katw) - OR ish me thn grammh afethrias - 1 - dld x2=x1-1(mia grammh panw) -)
		 * AND (sthlh proorismou einai ish me thn sthlh afethrias + 1)
		 * AND (tetragwno proorismou isoutai me mayro)
		 */
		else if ((thisPawn->getX() + 1 == thatSpace->getX() || thisPawn->getX() - 1 == thatSpace->getX()) && thisPawn->getY() + 1 == thatSpace->getY()  && thatSpace->getColor() == BLACK)
		{
			return true;
		}
		else
			return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			if  ((thisPawn->getX() == thatSpace->getX()) &&
				    ((thatSpace->getY() == thisPawn->getY() - 1) || ((thatSpace->getY() == thisPawn->getY() - 2) && (thisPawn->getY() == 6))) &&
					(thatSpace->getColor() == NONE))
			{
				return true;
			}
			else
				if ((thisPawn->getX() + 1 == thatSpace->getX() || thisPawn->getX() - 1 == thatSpace->getX()) && thisPawn->getY() - 1 == thatSpace->getY()  && thatSpace->getColor() == WHITE)
				{
					return true;
				}
				else
					return false;
		}
		else
			return false;
}

/*
 * H makeMove elegxei an h kinhsh pou edwse
 * o xrhsths einai entos twn oriwn tou pinaka square.
 * Epishs elegxei an ekei pou theloume na pame
 * yparxei pioni idiou xrwmatos kai emfanizei
 * mhnyma lathous. Alliws kalei thn ekastote synarthsh
 * gia na pragmatopoihsei thn kinhsh tou pioniou pou
 * exei epileksei o xrhsths
 */
bool Board::makeMove(int x1, int y1, int x2, int y2) {
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8) //elegxoume an einai entos twn oriwn tou pinaka 8X8
	{
		std::cout << "Κίνηση εκτός ορίων" << std::endl;
		return false;
	}
	//pointers stis dieuthynseis twn Square objects elements tou pinaka square (arxikh thesh/telikh thesh)
	Square* src = getSquare(x1, y1);
	Square* dest = getSquare(x2, y2);

	//den prepei na yparxei diko mas pioni ekei pu theloume na pame
	if (src->getColor() == dest->getColor()) // && dest->getColor() != NONE)
	{
		std::cout << "Πιόνια ίδιου χρώματος" << std::endl;
		return false;
	}

	// epistrefei to piece tou object ston pinaka square sthn dieuthinsh pou deixnei to src
	switch (src->getPiece())
	{
	case KING: return checkIfKing(src, dest);
		break;
	case QUEEN: return checkIfQueen(src, dest);
		break;
	case BISHOP: return checkIfBishop(src, dest);
		break;
	case KNIGHT: return checkIfKnight(src, dest);
		break;
	case ROOK: return checkIfRook(src, dest);
		break;
	case PAWN: return checkIfPawn(src, dest);
		break;
	case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
		break;
	default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
		break;
	}
	return false;
}


void Board :: saveToBinFile(string strFile)
{
	using namespace std;
	ofstream fs;	//The ofstream class provides a member function named write that allows for information to be written in binary form to the stream. http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
	fs.open(strFile, ios::out | ios::binary);
	if (!fs.is_open()) {
		cout << "cannot open file" << strFile << endl;
	} else {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				fs.write(reinterpret_cast<char*>(&square[i][j]), sizeof(square));
			}


		}
	}
	fs.close();
}


void Board::readFromBinFile(string strFile)
{
	ifstream binaryFile;
	int size = 0;

	binaryFile.open(strFile, ios::in | ios::binary);
	binaryFile.seekg(0, ios::end); // elegxos pou teleiwnei to arxeio
	size = (int)binaryFile.tellg();
	binaryFile.seekg(0, ios::beg); //vazoume ton pointer sthn arxh tou arxeiou

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (binaryFile.tellg() >= size)
			{
				break;
			}
			binaryFile.read((char*)(&square[i][j]), sizeof(square));
		}
		if (binaryFile.tellg() >= size)
		{
			break;
		}
	}
	binaryFile.close();
}


