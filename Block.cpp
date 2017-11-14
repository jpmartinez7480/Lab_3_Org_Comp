#include "Block.h"

Block::Block(){
	value = 0;
	age = 0;
}

void Block::set_value_block(int v){
	value = v;
}

void Block::set_age_block(int a){
	age = a;
}

int Block::get_value_block(){
	return value;
}

int Block::get_age_block(){
	return age;
}