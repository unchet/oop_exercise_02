#include <iostream>
#include "Position.h"
#include <stack>

Position::Position(){
	longitude = 0;
	latitide = 0;
}

Position::Position(int a, int b){
	latitide = a;
	longitude = b;
	while(longitude < -180){
		longitude += 360;
	}
	while(longitude > 180){
		longitude -= 360;
	}
	while(latitide < -90 ){
		latitide += 180;
	}
	while(latitide > 90){
		latitide -= 180;
	}
}

std::ostream& operator<<(std::ostream &out, const Position &a){
	out << "(" << a.latitide << "," << a.longitude<< ")" << std::endl;
	return out;
}

bool Check(Position a){
	return (a.latitide && a.longitude);
}

int operator "" _lat(unsigned long long a){
	return a;
}

int operator "" _long(unsigned long long a){
	return a;
}

void Position::operator=(Position a){
	this->longitude = a.longitude;
	this->latitide = a.latitide;
}

Position Position::operator+(Position a){
	Position res;
	res.longitude = this->longitude + a.longitude;
	res.latitide = this->latitide + a.latitide;
	res = Position(res.latitide, res.longitude);
	return res;
}

Position Position::operator-(Position a){
	Position res;
	res.longitude = this->longitude - a.longitude;
	res.latitide = this->latitide - a.latitide;
	res = Position(res.latitide, res.longitude);
	return res;
}

Position Position::operator*(Position a){
	Position res;
	res.longitude = this->longitude * a.longitude;
	res.latitide = this->latitide * a.latitide;
	res = Position(res.latitide, res.longitude);
	return res;
}

Position Position::operator/(Position a){
	Position res;
	res.longitude = this->longitude / a.longitude;
	res.latitide = this->latitide / a.latitide;
	res = Position(res.latitide, res.longitude);
	return res;
}

bool Position::operator!=(Position a){
	return(this->longitude != a.longitude || this->latitide != a.latitide);
}

bool Position::operator==(Position a){
	return(this->longitude == a.longitude && this->latitide == a.latitide);
}

Position Parse(const char *str){
	int arr[2] = {0};
	int cur = 0, minus = 0, brackets = 0, check = 0;
	std::stack <char> operations;
	std::stack <Position> tmp;
	Position a,b;

	for(size_t i = 0; ; ++i){
		if((str[i]>=34 && str[i]<=39) || (str[i]>=62 && str[i]!= 58 && str[i]!=59))
			break;
		if(str[i] == '-' && brackets){
			minus = 1;
			continue;
		}
		if(str[i] == '+' || (str[i] == '-' && !brackets)
		|| str[i] == '*' || str[i] == '/' || str[i] == '='
		|| str[i] == '!'){
			if(!cur)
				break;
			operations.push(str[i]);
			for(int i = 0; i < 2; ++i)
				arr[i] = 0;
			cur = 0;
			minus = 0;
			continue;
		}

		if(str[i] == '('){
			check = 1;
			++brackets;
			continue;
		}
		if(str[i] == ')'){
			if(minus){
				arr[cur] *= -1;
				minus = 0;
			}
			tmp.push(Position(arr[0], arr[1]));
			--brackets;
			continue;
		}
		if(str[i] == ','){
			if(minus){
				arr[cur] *= -1;
				minus = 0;
			}
			if(cur)
				break;
			cur++;
			continue;
		}
		if(str[i] == ' ' || str[i] == '\t'){
			continue;
		}

		if(str[i] == '\n'){
			if(cur == 1 && !brackets && check){
				if(minus)
					arr[cur] *= -1;
				while(!operations.empty()){
					char c = operations.top();
					operations.pop();
					switch (c){
						case '+':
							a = tmp.top();
							tmp.pop();
							b = tmp.top();
							tmp.pop();
							tmp.push(a+b);
							break;
						case '-':
							a = tmp.top();
							tmp.pop();
							b = tmp.top();
							tmp.pop();
							tmp.push(b-a);
							break;
						case '*':
							a = tmp.top();
							tmp.pop();
							b = tmp.top();
							tmp.pop();
							tmp.push(a*b);
							break;
						case '/':
							a = tmp.top();
							tmp.pop();
							b = tmp.top();
							tmp.pop();
							if(Check(a))
								tmp.push(b/a);
							else {
								std::cout << "Нельзя делить на ноль! Выставлены координаты по умолчанию:" << std::endl;
								return Position();
							}
							break;
					}
				}
				a = tmp.top();
				tmp.pop();
				return a;
			}
			else
				break;
		}
		arr[cur] *= 10;
		arr[cur] += str[i] - '0';
	}
	std::cout << "Неправильная запись! Выставлены координаты по умолчанию:" << std::endl;
	return Position();
}