#include <fstream>
#include <iostream>
using namespace std;

int  main(int argc, const char *argv[])
{
	if (argc!=2) { //controllo che il numero di parametri sia giusto
		cerr << "Numero di files da inserire errato \n";
		return 1;
	}
	string filename = argv[1]; // attribuisco il nome dato in input al nome del file da aprire già presente nelal cartella
	ifstream ifs(filename);
	if (ifs.is_open() ) { // verifico che sia correttamente aperto
		while( !ifs.eof() ) { // leggo il file da inizio a fine
			string location;
			double t1,t2,t3,t4; // metto le 4 temperature per ogni città, qui ho usato AI per capire che si potesse fare un solo double invece che 4 separati
			ifs >> location >> t1 >> t2 >> t3 >> t4; 
			double miu = (t1 + t2 + t3 + t4)/4.0;
			cout << location << " " << miu << "\n";
		}
	}
	else {
		cerr << "errore nell'apertura del file \n"; // nel caso che il file non sia aperto correttamente
		return 2;
	} 
	return 0;
}
