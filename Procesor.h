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
		void LRU(int);
		//void MRU(int);
		//void FIFO(int);
		void ejecutar();
		void show_cache();

		int get_associativity();
		int get_amount_words();
		int get_number_of_blocks();
		int get_address();
		char get_replacement_scheme();
		bool read_file(string);
		bool direct_mapped(int,char);
		bool valid_config_cache(int,int,int);

	private:
		int cnt;
		int cant_elem_cache;
		int associativity;
		int amount_words;
		int number_of_blocks;
		char replacement_scheme;
		list<int> data;
		list<int>::iterator it;
		Block **cache;

};

