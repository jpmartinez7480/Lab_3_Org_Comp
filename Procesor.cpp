#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "Procesor.h"

using std::cout;
using std::endl;
using std::fstream;
using std::ios;


Procesor::Procesor(){}

Procesor::Procesor(string r, int v, int p, int t)
{
	set_replacement_scheme(r);
	set_associativity(v);
	set_amount_words(p);
	set_number_of_blocks(t);
}

void Procesor::set_associativity(int v){
	associativity = v;
}

void Procesor::set_replacement_scheme(string r){
	if(r == "LRU") replacement_scheme = 'L';
	else if(r == "MRU") replacement_scheme = 'M';
	else if(r == "FIFO") replacement_scheme = 'F';
}

void Procesor::set_amount_words(int p){
	amount_words = p;
}

void Procesor::set_number_of_blocks(int t){
	number_of_blocks = t;
}

void Procesor::set_cache(int v, int t)
{
	cache = new Block*[t];
	for(int i = 0; i < t; i++){
		cache[i] = new Block[v];		
	}
	for(int i = 0; i < t; i++){
		for(int j = 0; j < v; j++)
			cache[i][j] = Block();
	} 
	
}

int Procesor::get_associativity(){
	return associativity;
}

int Procesor::get_amount_words(){
	return amount_words;
}

int Procesor::get_number_of_blocks(){
	return number_of_blocks;
}

char Procesor::get_replacement_scheme(){
	return replacement_scheme;
}

bool Procesor::read_file(string nfile){
	fstream FILE;
	int value;
	FILE.open(nfile.c_str(),ios::in);
	if(!FILE) return false;
	else{
		while(FILE >> value) data.push_back(value);
		FILE.close();
		return true;
	}
}

void Procesor::contenido(){
	list<int>::iterator aux;
	aux = data.begin();
	int dato;
	while(aux!=data.end()){
		dato = *aux;
		cout << "valor: " << dato << endl;
		aux++;
	}
}









