#include "Word.h"

Word::Word()
{
	value = 0;
	age = 0;
}

void Word::set_value(int v){
	value = v;
}

void Word::set_age(int a){
	age = a;
}

int Word::get_value(){
	return value;
}

int Word::get_age(){
	return age;
}

