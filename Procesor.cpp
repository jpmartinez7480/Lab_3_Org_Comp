#include <iostream>
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
	cnt_it = 0;
	age = 0;
	cant_elem_cache = 0;
	hit = 0;
	set_cache(v,t);
	cnt_words_per_block = v*p;

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
	cache = new Block*[t/v];
	for(int i = 0; i < t; i++)	cache[i] = new Block[v];		
	for(int i = 0; i < t/v; i++){
		for(int j = 0; j < v; j++)	cache[i][j] = Block(get_amount_words());
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

bool Procesor::write_exit_file_cache(string nfile)
{
	fstream FILE;
	int aux = get_number_of_blocks()/get_associativity();
	FILE.open(nfile.c_str(),ios::out);
	if(FILE){
		for(int i = 0; i < aux; i++){
			for(int j = 0; j < get_associativity(); j++){
				for(int k = 0; k < get_amount_words(); k++){ 
					if(cache[i][j].get_age_in_word(k) != 0)
						FILE << "s" << i << ": "<< "b" << j << ": " << "w" << k << ":" << cache[i][j].get_value_in_word(k)<< endl;
					else if(cache[i][j].get_age_in_word(k) == 0)
						FILE << "s" << i << ": "<< "b" << j << ": " << "w" << k << ":-" << endl;
				}
			}
		}
		FILE.close();
		return true;
	}
	return false;
}

bool Procesor::write_exit_file_hit(string nfile)
{
	fstream FILE;
	FILE.open(nfile.c_str(),ios::out);
	if(FILE){
		FILE << "Tasa de hit: " << hit*100/cnt_it << '%' << endl;
		FILE << "Tasa de miss: " << 100 - hit*100/cnt_it << '%' << endl;
		return true;
	}
	return false;
}

bool Procesor::valid_config_cache(int v, int p, int t, string s)
{
	if(s != "FIFO" && v == 1)	return false;	
	else if((v != 1 && v%2!= 0) || (p !=1 && p%2 != 0) || t%2!=0) return false;
	return true;
}

void Procesor::FIFO(int set_pos, int s, int e)
{
	int older = cache[set_pos][0].get_age_in_word(0);
	int pos_block_older = 0;
	for(int i = 0; i < get_associativity(); i++){
		for(int j = 0; j < get_amount_words(); j++){
			if(cache[set_pos][i].get_age_in_word(j) <= older){
				older = cache[set_pos][i].get_age_in_word(j);
				pos_block_older = i;
			}
		}
	}
	for(int j = s,i=0; j <= e; j++,i++){
		cache[set_pos][pos_block_older].set_value_word(i,j);
		cache[set_pos][pos_block_older].set_age_word(i,age);
		age++;
	}
	cnt_it++;
}

void Procesor::LRU(int set_pos, int s, int e)
{
	int older = cache[set_pos][0].get_age_in_word(0);
	int pos_block_older = 0;
	for(int i = 0; i < get_associativity(); i++){
		for(int j = 0; j < get_amount_words(); j++){
			if(cache[set_pos][i].get_age_in_word(j) <= older){
				older = cache[set_pos][i].get_age_in_word(j);
				pos_block_older = i;
			}	
		}
	}
	for(int j = s, i = 0; j <=e; j++,i++){
		cache[set_pos][pos_block_older].set_value_word(i,j);
		cache[set_pos][pos_block_older].set_age_word(i,age);
		age++;
	}
	cnt_it++;
}

void Procesor::MRU(int set_pos, int s, int e)
{
	int younger = cache[set_pos][0].get_age_in_word(0);
	int pos_block_younger = 0;
	for(int i = 0; i < get_associativity(); i++){
		for(int j = 0; j < get_amount_words(); j++){
			if(cache[set_pos][i].get_age_in_word(j) >= younger){
				younger = cache[set_pos][i].get_age_in_word(j);
				pos_block_younger = i;
			}
		}
	}
	for(int j = s, i = 0; j <= e; j++,i++){
		cache[set_pos][pos_block_younger].set_value_word(i,j);
		cache[set_pos][pos_block_younger].set_age_word(i,age);
		age++;
	}
	cnt_it++;

}

bool Procesor::direct_mapped(int v)
{
	age++;
	int cnt = 0;
	int aux = v%get_number_of_blocks();
	int initial_range = ((v*4)/(4*get_amount_words()))*(4*get_amount_words())/4;
	int end_range = ((((v*4)/(4*get_amount_words()))*(4*get_amount_words())) + ((4*get_amount_words()) - 1))/4;
	if(cache[aux][0].get_age_in_word(0) == 0){
		for(int j = initial_range,pos=0;j<=end_range;j++){
			cache[aux][0].set_value_word(pos,j);
			cache[aux][0].set_age_word(pos,age);
			age++;
		}
		cnt_it++;
		return false;
	} 
	
	else if(cache[aux][0].get_age_in_word(0) != 0){
		for(int j = 0; j < get_amount_words(); j++){
			if(cache[aux][0].get_value_in_word(j) == v){
				//hit
				age++;
				cnt_it++;
				return true;
			}
			else cnt++;
		}
	}
	if(cnt == get_amount_words()){
		FIFO(aux,initial_range,end_range);
		return false;
	}
}

bool Procesor::Set_associativity(int v)
{
	age++;
	int aux;
	int cnt = 0;
	int set = (v*4/(4*get_amount_words()))%(get_number_of_blocks()/get_associativity());
	int initial_range = ((v*4)/(4*get_amount_words()))*(4*get_amount_words())/4;
	int end_range = ((((v*4)/(4*get_amount_words()))*(4*get_amount_words())) + ((4*get_amount_words()) - 1))/4;
	for(int i = 0; i < get_associativity(); i++)
	{
		if(cache[set][i].get_age_in_word(0) == 0)
		{
			for(int j = initial_range,pos = 0; j <= end_range; j++,pos++){
				cache[set][i].set_value_word(pos,j);
				cache[set][i].set_age_word(pos,age);
				age++;	
			}
			cnt_it++;
			return false;
		}
		else if(cache[set][i].get_age_in_word(0) != 0)
		{
			for(int j = 0; j < get_amount_words(); j++)
			{
				if(cache[set][i].get_value_in_word(j) == v){
					for(int k = 0; k < get_amount_words(); k++){
						if(get_replacement_scheme() != 'F')	cache[set][i].set_age_word(k,age);	
						age++;
					}
					cnt_it++;
					return true;
				}
				else cnt++;
			}
		}
		if(cnt == cnt_words_per_block)
		{
			switch(get_replacement_scheme())
			{
				case 'L':
					LRU(set,initial_range,end_range);
					break;
				case 'M':
					MRU(set,initial_range,end_range);
					break;
				case 'F':
					FIFO(set,initial_range,end_range);
					break;
			}
			return false;
		}
	}
}


void Procesor::ejecutar()
{
	list<int>::iterator aux;
	aux = data.begin();
	int dato;
	if(get_associativity() == 1){
		while(aux!=data.end()){
			dato = *aux;
			if(direct_mapped(dato)) hit++;
			aux++;
		}	
	}
	else if(get_associativity() > 1){
		while(aux!=data.end()){
			dato = *aux;
			if(Set_associativity(dato)) hit++;
			aux++;
		}
	}
}

void Procesor::show_cache()
{
	int aux = get_number_of_blocks()/get_associativity();
	cout << "*** Contenido cache ***" << endl;
	for(int i = 0; i < aux; i++){
		for(int j = 0; j < get_associativity(); j++){
			for(int k = 0; k < get_amount_words(); k++){
				if(cache[i][j].get_age_in_word(k) != 0)
					cout << "s" << i << ": "<< "b" << j << ": " << "w" << k << ":" << cache[i][j].get_value_in_word(k)<< endl;
				else if(cache[i][j].get_age_in_word(k) == 0)
					cout << "s" << i << ": "<< "b" << j << ": " << "w" << k << ":-" << endl;
			}
		}
	}
}



