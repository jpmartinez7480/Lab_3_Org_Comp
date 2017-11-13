class Block
{
	public:
		Block();
		void setValueBlock(int);
		void setAccessStatus(bool);
		int getValueBlock();
		bool getAccessStatus();
	private:
		int value;
		bool status;
};