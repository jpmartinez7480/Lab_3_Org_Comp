class Block
{
	public:
		Block();
		void set_value_block(int);
		void set_age_block(int);
		int get_value_block();
		int get_age_block();
	private:
		int value;
		int age;
};