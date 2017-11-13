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
		
		int get_associativity();
		int get_amount_words();
		int get_number_of_blocks();
		char get_replacement_scheme();
		bool read_file(string);

		void contenido();

	private:
		int associativity;
		int amount_words;
		int number_of_blocks;
		char replacement_scheme;
		list<int> data;
		list<int>::iterator it;
		Block **cache;

};

