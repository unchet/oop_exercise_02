#ifndef __POSITION_CLASS__
#define __POSITION_CLASS__

class Position{
	private:
		int longitude, latitide; 
	public:
		Position();
		Position(int a, int b);

		friend std::ostream& operator<<(std::ostream &out, const Position &a);
		friend bool Check(Position a);
		void operator=(Position a);
		Position operator+(Position a);
		Position operator-(Position a);
		Position operator*(Position a);
		Position operator/(Position a);

		bool operator<(Position a);
		bool operator<=(Position a);
		bool operator>(Position a);
		bool operator>=(Position a);
		bool operator!=(Position a);
		bool operator==(Position a);
};


int operator "" _lat(unsigned long long a);
int operator "" _long(unsigned long long a);
Position Parse(const char *str);

#endif