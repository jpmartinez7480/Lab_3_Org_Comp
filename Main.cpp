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
using std::atoi;

int main(int argc, char **argv)
{
	if(argc == 5){
		string pause;
		string cad;
		int ans;
		string file;
		string exit_file_cache;
		string exit_file_hit;
		Procesor procesor = Procesor(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
		if(procesor.valid_config_cache(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[1]))
		{
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
						if (procesor.read_file(file))
							cout << "La lectura fue realizada correctamente..." << endl;	
						else{
							file = "";
							cout << "El archivo no existe o formato no valido" << endl;
						}
						cout << "Presione cualquier tecla para continuar...";
						cin >> pause; 
					break;
					case 2:
						system("cls");
						cout << "*** Caracteristicas del cache ***" << endl;
						if(procesor.get_replacement_scheme() == 'L') cout << "Politica de reemplazo: LRU " << endl;
						else if(procesor.get_replacement_scheme() == 'F') cout << "Politica de reemplazo: FIFO " << endl;
						else if(procesor.get_replacement_scheme() == 'M') cout << "Politica de reemplazo: MRU " << endl;
						cout << "n-vias: " << procesor.get_associativity() << endl;
						cout <<  "Cantidad de palabras: " << procesor.get_amount_words() << endl;
						cout << "Cantidad de bloques: " << procesor.get_number_of_blocks() << endl;
						cout << "Presione cualquier tecla para continuar...";
						cin >> pause; 
					break;
					case 3:
						system("cls");
						cout << "Ingrese nombre del archivo de salida de cache: ";
						cin >> exit_file_cache;
						cout << "Ingrese nombre del archviod de salida para tasa de hit y miss: ";
						cin >> exit_file_hit;
						procesor.ejecutar();
						procesor.show_cache();
						if(procesor.write_exit_file_cache(exit_file_cache))
							cout << "El archivo " << exit_file_cache << " fue creado con exito" << endl;
						else cout << "Error al escribir archivo" << endl;
						if(procesor.write_exit_file_hit(exit_file_hit))
							cout << "El archivo " << exit_file_hit << " fue creado con exito" << endl;
						else cout << "Error al escribir el archivo" << endl;
						cout << "Presione cualquier tecla para continuar...";
						cin >> pause; 
					break;
					case 4:
						cout << "Gracias por su preferencia" << endl; 
				}
				if(ans > 0 && ans <= 3) ans = 0;
			}while(ans!=4);
		}
		else cout << "No ha ingresado una configuracion valida para el cache" << endl;
	}
	else{
		cout << "No ha ingresado correctamente los parametros de ejecucion."<< endl;	
		cout << "Intente nuevamente" << endl;
	}
	
	return 0;
}


