// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header f�r die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
// TODO: F�gen Sie hier weitere ben�tigte Header-Dateien der
// Standard-Bibliothek ein z.B.
// #include <string>

using namespace std;	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.

#include "CNavigationSystem.h"

// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main (void)
{
    // TODO: F�gen Sie ab hier Ihren Programmcode ein
	cout << "ME3_NavigationSystem gestarted." << endl << endl;
	CNavigationSystem NSys1;
	NSys1.run();

	return 0;
}
