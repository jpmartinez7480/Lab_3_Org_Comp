#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Procesor.cpp"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::stringstream;

int main()
{
	string pause;
	string cad;
	int ans;
	string file;
	Procesor procesor;
	do
	{
		system("cls");
		cout << endl;
		cout << "****** ORGANIZACION DE COMPUTADORES ******" << endl;
		cout << "        ****** laboratorio 3 ******" << endl;
		cout << "Menu de opciones" << endl;
		cout << "1.Leer archivo de datos" << endl;
		cout << "2.Ver caracteristicas Cache" << endl;
		cout << "3.Ejecutar" << endl;
		cout << "4.Salir" << endl;
		cout << "Ingrese opcion: ";
		getline(cin,cad);
		stringstream mystream(cad);
		string msje = mystream >> ans ? "entrada valida\n": "entrada invalida\n";
		cout << msje;
		switch(ans)
		{
			case 1:
				system("cls");
				cout << "*** Lectura de archivo de datos ***" << endl;
				cout << "Ingrse el nombre del archivo junto a su extension(ejemplo.ext): ";
				cin >> file;
				if (procesor.read_file(file)){
					cout << "La lectura fue realizada correctamente..." << endl;
					procesor.contenido();
					cout << endl;	
				}
				else{
					file = "";
					cout << "El archivo no existe o formato no valido" << endl;
				} 
				cout << "Presione cualquier tecla para continuar...";
				cin >> pause; 
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
				cout << "Gracias por su preferencia" << endl; 
		}
		if(ans > 0 && ans <= 3) ans = 0;
	}while(ans!=4);
	return 0;
}


