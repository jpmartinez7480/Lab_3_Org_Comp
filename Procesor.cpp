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
	cnt = 0;
	cant_elem_cache = 0;
	set_cache(v,t);
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
		for(int j = 0; j < v; j++){
			//cache[i][j].set_age_block(0);
			//cache[i][j].set_value_block(0);
			cache[i][j] = Block();
		}	
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

bool Procesor::valid_config_cache(int v, int t, int p)
{
	
	return true;
}

void Procesor::LRU(int v)
{
	int min_age = cache[0][0].get_age_block();
	int pos_min_age_i = 0;
	int pos_min_age_j = 0;
	int cnt = 0;
	for(int i = 1; cnt < cant_elem_cache; i++){
		for(int j = 0; j < get_associativity(); j++){
			if(cache[i][j].get_age_block() != 0 && cache[i][j].get_age_block() <= min_age){
				min_age = cache[i][j].get_age_block();
				pos_min_age_i = i;
				pos_min_age_j = j;
			}
		}
	}
	cnt++;
	cache[pos_min_age_i][pos_min_age_j].set_value_block(v);
	cache[pos_min_age_i][pos_min_age_j].set_age_block(cnt);

}

bool Procesor::direct_mapped(int v, char scheme)
{
	int aux = v%get_number_of_blocks();
	if(cache[aux][0].get_value_block() == v){
		cnt++;
		cache[aux][0].set_age_block(cnt);
		return true;
	}
	else if(cache[aux][0].get_age_block() != 0 && cache[aux][0].get_value_block() != v){
		//if(scheme == 'L')	LRU(v);
		//else if(scheme == 'M') MRU(v);
		//else if(scheme == 'F') FIFO(v);
		cnt++;
		cache[aux][0].set_value_block(v);
		cache[aux][0].set_age_block(cnt);
		return false;
	}
	else if(cache[aux][0].get_age_block() == 0){
		cnt++;
		cache[aux][0].set_value_block(v);
		cache[aux][0].set_age_block(cnt);
		return false;
	}
}

void Procesor::ejecutar()
{
	list<int>::iterator aux;
	aux = data.begin();
	int dato;
	int hit = 0;
	if(get_associativity() == 1){
		while(aux!=data.end()){
			dato = *aux;
			if(direct_mapped(dato,get_replacement_scheme())) hit++;
			aux++;
		}	
	}
	//otr caso
}

void Procesor::show_cache()
{
	cout << "*** Contenido cache ***" << endl;
	for(int i = 0; i < get_number_of_blocks(); i++){
		for(int j = 0; j < get_associativity(); j++){
			if(cache[i][j].get_age_block() != 0) cout << "valor: " << cache[i][j].get_value_block() << endl;
			else cout << "valor:-" << endl;
		}
	}
}



