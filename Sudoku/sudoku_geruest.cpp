#include <iostream>
#include <string>
using namespace std;

const int sudoku_groesse = 9;
const int eingabe_groesse = 11;

bool arrayContains(int arr[], int element) {
    for (int i = 0; i < sudoku_groesse; i++)
    {
        if(arr[i] == element) {
            return true;
        }
    }
    return false;
}

bool duplicate(int arr[], int element) {
    bool firstFound = false;
    for (int i = 0; i < sudoku_groesse; i++)
    {
        if(arr[i] == element) {
            if(!firstFound) {
                firstFound = true;
            }else{
                return true;
            }
        }
    }
    return false;
}

bool pruefe_spalten(int sudoku[][sudoku_groesse])
{
    bool spalteKorrekt = true;
    for (int i = 0; i < sudoku_groesse; i++)
    {
        int spalte[sudoku_groesse];
        for (int j = 0; j < sudoku_groesse; j++)
        {
            spalte[j] = sudoku[j][i];
        }
        for (int j = 1; j <= sudoku_groesse; j++)
        {
            if(!arrayContains(spalte, j)){
                cout << "Spalte " << i << ": Zahl " << j << " kommt nicht vor." << endl;
                spalteKorrekt = false;
            }
            if(duplicate(spalte, j)){
                cout << "Spalte " << i << ": Zahl " << j << " kommt mehrfach vor." << endl;
                spalteKorrekt = false;
            }
        }
        
        
    }
    return spalteKorrekt;
}

bool pruefe_zeilen(int sudoku[][sudoku_groesse])
{
    bool zeileKorrekt = true;
    for (int i = 0; i < sudoku_groesse; i++)
    {
        int zeile[sudoku_groesse];
        for (int j = 0; j < sudoku_groesse; j++)
        {
            zeile[j] = sudoku[i][j];
        }
        for (int j = 1; j <= sudoku_groesse; j++)
        {
            if(!arrayContains(zeile, j)){
                cout << "Zeile " << i << ": Zahl " << j << " kommt nicht vor." << endl;
                zeileKorrekt = false;
            }
            if(duplicate(zeile, j)){
                cout << "Zeile " << i << ": Zahl " << j << " kommt mehrfach vor." << endl;
                zeileKorrekt = false;
            }
        }
    }
    return zeileKorrekt;
}

bool pruefe_bloecke(int sudoku[][sudoku_groesse])
{
    bool blockKorrekt = true;
    int bloecke[sudoku_groesse][sudoku_groesse];
    for (int i = 0; i < sudoku_groesse; i++)
    {
        int block[sudoku_groesse];
        int blockZaehler = 0;
        for (int z = 0; i/3*3+z <= i/3*3+2; z++)
        {
            for (int s = 0; i%3*3+s <= i%3*3+2; s++)
        {
            bloecke[i][blockZaehler] = sudoku[i/3*3+z][i%3*3+s];
            blockZaehler++;
        }
        }

    }
    for (int i = 0; i < sudoku_groesse; i++)
    {
        for (int j = 1; j <= sudoku_groesse; j++)
        {
         if(!arrayContains(bloecke[i], j)){
                cout << "Block " << i << ": Zahl " << j << " kommt nicht vor." << endl;
                blockKorrekt = false;
            }
            if(duplicate( bloecke[i], j)){
                cout << "Block " << i << ": Zahl " << j << " kommt mehrfach vor." << endl;
                blockKorrekt = false;
            }
        }
    }
    return blockKorrekt;
}

void konvertiere(string eingabe[], int sudoku[][sudoku_groesse])
{
    for (int zeile = 0, y = 0; zeile < 11; zeile++)
    {
        for (int pos = 0, x = 0; pos <= 21; pos++)
        {
            // Damit die Zeile mit - nicht benutzt wird.
            if (eingabe[zeile].at(pos) == 45)
            {
                y--;
                break;
            }
            if (eingabe[zeile].at(pos) > 48 && eingabe[zeile].at(pos) < 58)
            {
                sudoku[y][x] = eingabe[zeile].at(pos) - 48;
                ++x;
            }
        }
        y++;
    }
}

void printSudoku(int sudoku[][sudoku_groesse]) {
    cout << endl
         << "Das Sudoku lautet:" << endl;
    for (int ausgabe_y = 0; ausgabe_y < sudoku_groesse; ausgabe_y++)
    {
        if (ausgabe_y == 3 || ausgabe_y == 6)
        {
            cout << "=======//=======//=======" << endl;
        }
        for (int ausgabe_x = 0; ausgabe_x < sudoku_groesse; ausgabe_x++)
        {
            if (ausgabe_x == 3 || ausgabe_x == 6)
            {
                cout << ";//";
            }

            cout << ";" << sudoku[ausgabe_y][ausgabe_x];
        }
        cout << endl;
    }
    
}



int main() 
{
    int sudoku[sudoku_groesse][sudoku_groesse] = { 0 };
    string eingabe[eingabe_groesse];

    cout << "Bitte geben Sie das Sudoku ein:" << endl;
    for (int i = 0; i < eingabe_groesse; i++)
        getline(cin, eingabe[i]);

    konvertiere(eingabe, sudoku);

    bool ps = pruefe_spalten(sudoku);
    bool pz = pruefe_zeilen(sudoku);
    bool pb = pruefe_bloecke(sudoku); 

    if (ps && pz && pb)
        cout << "Das Sudoku ist gueltig." << endl;

    system("PAUSE");
    return 0;
}
