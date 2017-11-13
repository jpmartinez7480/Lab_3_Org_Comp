#include "Block.h"

Block::Block(){
	value = 0;
	status = false;
}

void Block::setValueBlock(int v){
	value = v;
}

void Block::setAccessStatus(bool s){
	status = s;
}

int Block::getValueBlock(){
	return value;
}

bool Block::getAccessStatus(){
	return status;
}