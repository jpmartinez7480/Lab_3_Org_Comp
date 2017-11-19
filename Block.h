#include "Word.cpp"

class Block
{
	public:
		Block();
		Block(int s);
		void set_words_amount(int);
		void set_value_word(int,int);
		void set_age_word(int,int);
		void set_cnt_words_per_block(int);
		int get_words_amount();
		int get_value_in_word(int);
		int get_age_in_word(int);
		int get_cnt_words_per_block();
	private:
		int words_amount;
		int cnt_words_per_block;
		Word *words;

};