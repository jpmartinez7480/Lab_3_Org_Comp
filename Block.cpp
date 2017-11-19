#include "Block.h"

Block::Block(){}

Block::Block(int s)
{
	words = new Word[s];
	for(int i = 0; i < s; i++)
		words[i] = Word();
	cnt_words_per_block = 0;
}

void Block::set_words_amount(int s){
	words_amount = s;
}

void Block::set_cnt_words_per_block(int c){
	cnt_words_per_block = c;
}

void Block::set_value_word(int pos, int value){
	words[pos].set_value(value);
}

void Block::set_age_word(int pos, int age){
	words[pos].set_age(age);
}

int Block::get_words_amount(){
	return words_amount;
}

int Block::get_value_in_word(int pos){
	return words[pos].get_value();
}

int Block::get_age_in_word(int pos){
	return words[pos].get_age();
}

int Block::get_cnt_words_per_block(){
	return cnt_words_per_block;
}
