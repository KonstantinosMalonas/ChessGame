//============================================================================
// Name        : ChessMalonas.cpp
// Author      : Kwnstantinos Malwnas
// Version     : 4
// Copyright   : Your copyright notice
// Description : A chess programm in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <limits>

#include "../HeaderFiles/ChessGame.hpp" // https://stackoverflow.com/questions/13298550/eclipse-c-including-header-file-from-my-source-folder

using namespace std;





int main()
{
	Board b; //dhmiourghse Board object vale to turn = WHITE
	string s;
	bool newgame = true;
	cout << "  ΣΚΑΚΙ \n" << endl;
	cout << "Αντικειμενοστραφής Προγραμματισμός "<<endl;
	cout << "Πάτηστε πλήκτρο για συνέχεια" << endl;
	// www.cplusplus.com/forum/beginner/2624/
	int i;//cin.get(); //gia na mporeis na vazeis kai enter
	//gist.github.com/jpkrause/4a1aa400d45197ca3253
	cin.clear(); //petaei ta skoupidia
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> i;
	do {
		if (1 == i) { // 1 == i gia megalyterh asfaleia
			cout << "\nme in 1\n"<<endl;
			b.setBoard();
			b.readFromBinFile("./record.dat");
		} else {
			b.setBoard();
		}
		cin.clear(); //petaei ta skoupidia
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (;b.playGame();); //isodynamo me while(condition);
		cout << "Επανάληψη Παιχνιδιού? (y|Y|yes|Yes : συνέχισε) , (πάτα οποιοδήποτε πλήκτρο για έξοδο) ";
		cin >> s;
		//www.cplusplus.com/reference/string/string/compare/
		if (s.compare("y") != 0 && s.compare("Y") != 0 && s.compare("yes") != 0 && s.compare("Yes") != 0)
			newgame = false;
	} while(newgame);


	return 0;
}
