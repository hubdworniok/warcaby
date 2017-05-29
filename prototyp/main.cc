#include <iostream>
#include <cstdlib>
#define SIZE 8  //Rozmiar planszy
#define ABS(x) ((x)<0 ? (-(x)) : (x))

using namespace std;

  
int main(int agrc, char *argv[]){

    //Tablica przechowujaca dane na temat gry.
    //@ - pionki gracza A
    //O - pionki gracza B
    //  - Puste pola
    //. - pola możliwe do ruchu pionków
    char plansza[8][8]={ {',','@',',','@',',','@',',','@'},
                         {'@',',','@',',','@',',','@',','},
                         {',','@',',','@',',','@',',','@'},
                         {'.',',','.',',','.',',','.',','},
                         {',','.',',','.',',','.',',','.'},
                         {'O',',','O',',','O',',','O',','},
                         {',','O',',','O',',','O',',','O'},
                         {'O',',','O',',','O',',','O',','} };
    
    int runda=0;    //Licznik rund. Pozwoli określić który gracz ma być następny.
    int GraczA=0;   //Punktacja dla gracza A
    int GraczB=0;   //Punktacja dla gracza B
    int Pos1x, Pos1y, Pos2x, Pos2y;     //Zmienne do przechwycenia wejscia
    
    //Głowna pętla gry
    while(GraczA < 12 && GraczB < 12){
    	//Czyscimy ekran
    	printf("\033[2J");
        //system("pause");
        
    	//Rysowanie ekranu gry
    	//Dodajemy pasek ABC
    	cout << "  |";    //Dla kolumny 1,2,3...
    	for(char c='A'; c<(char('A'+SIZE)); c++){
        	cout << c;
        	//Odstep pomiedzy kolumnami
        	if(!(c+1 < (char('A'+SIZE)))){ cout << "|"; }
    	}
    	cout << endl;
    	cout << "|";
    	for(int i=0; i<SIZE; i++){
        	cout << i+1 << "|";
        	for(int j=0; j<SIZE; j++){
            	cout << plansza[i][j];
            	//Odstep pomiedzy kolumnami
            	if(!(j+1 < SIZE)){ cout << "|"; }
        	}
       	 
        	//Odstep pomiedzy wersami
        	if(i+1 < SIZE){
                	/*for(int j=0; j<SIZE; j++){
                    	if(j%2 == 0){ cout << "-"; }
                    	else { cout << "+"; }
                	}*/
            	cout << "\n|";
        	}
    	}
   	 
    	//Wyswietlamy dane o grze
    	cout << "\n\n";
    	cout << "Punkty gracza A (@): " << GraczA << endl;
    	cout << "Punkty gracza B (O): " << GraczB << endl;
    	cout << "Runda: " << runda+1 << endl;
    	cout << "\n\n";
    	if(runda%2 == 0){ cout << "Tura gracza A (@).\n"; }
    	else{ cout << "Tura gracza B (O).\n"; } 
    	cin.get();
    	cout << "Podaj swoj ruch (odziel każdy znak spacją): ";
        
        //Input ruchu
       	//cin >> Pos1x >> Pos1y >> Pos2x >> Pos2y;
        Pos1x = int(cin.get());
        cin.ignore();
        cin >> Pos1y;
        cin.ignore();
        Pos2x = int(cin.get());
        cin >> Pos2y;
        cout << "\nPodano: " << "( " << char(Pos1x) << " ," << Pos1y << " ) " << "( " << char(Pos2x) << " ," << Pos2y << " )" << endl;
        
        //Sprawdzenie czy ruch dozwolony
        //1. Dekodowanie wartośći
        Pos1x -= int('A');
        Pos1y -= 1;
        Pos2x -= int('A');
        Pos2y -= 1;
        cout << "\nZdekodowano: " << "( " << Pos1x << " ," << Pos1y << " ) " << "( " << Pos2x << " ," << Pos2y << " )" << endl;
        //2. Sprawdzanie czy są dodatnie
        if(Pos1x < 0 || Pos1y < 0 || Pos2x < 0 || Pos2y < 0){
            cout << "Błąd wprowadzonych danych - wartości ujemne!" << endl;
            cin.get();
            cin.get();
            continue;
        }
        //3. Sprawdzamy czy drugie pole jest puste
        if(plansza[Pos2y][Pos2x] != '.'){
            cout << "Błąd wprowadzonych danych - pole docelowe nieprawidłowe!" << endl;
            cin.get();
            cin.get();
            continue;
        }
        //4. Sprawdzamy czy jest pionek jest aktualnego gracza
        if(!(plansza[Pos1y][Pos1x] == '@' && runda%2 ==0) && !(plansza[Pos1y][Pos1x] == 'O' && runda%2==1)){
            cout << "Błąd wprowadzonych danych - pole źródłowe nie jest pionkiem gracza!" << endl;
            cin.get();
            cin.get();
            continue;
        }
        //5. Sprawdzamy zasięg ruchu. ODL: 1 - normalny skok. 2 - bicie.
        if(ABS(Pos2x-Pos1x)>2 || ABS(Pos2y-Pos1y)>2){
            cout << "Niedozwolony ruch!" << endl;
            cin.get();
            cin.get();
            continue;
        }
        
        //Wykonujemy ruch
        //Zwykly skok
        if(ABS(Pos2x-Pos1x) != 2){
            plansza[Pos2y][Pos2x] = plansza[Pos1y][Pos1x];
            plansza[Pos1y][Pos1x] = '.';
        }
        //Bicie gracza
        else{
            plansza[int(Pos1y+(Pos2y-Pos1y)/2)][int(Pos1x+(Pos2x-Pos1x)/2)] = '.';
            plansza[Pos2y][Pos2x] = plansza[Pos1y][Pos1x];
            plansza[Pos1y][Pos1x] = '.';
            if(runda%2==0){GraczA +=1;}
            else{GraczB +=1;}
        }
        
        
        //Kolejna runda
        runda+=1;
    
    }
    cout << "\n\n\n";
    return 1;
}

