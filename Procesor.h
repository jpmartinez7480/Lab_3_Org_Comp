#include <string>
#include <list>
#include <iterator>

#include "Block.cpp"

using std::string;
using std::list;


class Procesor
{
	public:
		Procesor();
		Procesor(string r,int v,int p,int t);
		void set_associativity(int);
		void set_replacement_scheme(string);
		void set_amount_words(int);
		void set_number_of_blocks(int);
		void set_cache(int,int);
		void set_cnt_words_per_block(int);
		void LRU(int,int,int);
		void MRU(int,int,int);
		void FIFO(int,int,int);
		void ejecutar();
		void show_cache();

		int get_associativity();
		int get_amount_words();
		int get_number_of_blocks();
		int get_address();
		int get_cnt_words_per_block();
		char get_replacement_scheme();
		bool read_file(string);
		bool direct_mapped(int);
		bool Set_associativity(int);
		bool valid_config_cache(int,int,int,string);
		bool write_exit_file_cache(string);
		bool write_exit_file_hit(string);


	private:
		int cnt_it;
		int age;
		float hit;
		int cant_elem_cache;
		int associativity;
		int amount_words;
		int number_of_blocks;
		int cnt_words_per_block;
		char replacement_scheme;
		list<int> data;
		list<int>::iterator it;
		Block **cache;

};

