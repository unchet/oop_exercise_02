#include <iostream>
#include "Position.h"

int main(){
	char c = ' ', r;
	char *str = new char[50];
	int comp = 0;
	Position a, b;

	std::cout << "Это было выведено с помощью пользовательского литерала:" << std::endl;
	std::cout << "Широта: " << 12_lat << std::endl;
	std::cout << "Долгота: " << 30_long << std::endl;

	while(1){
		std::cout << "Введите выражение: (для выхода введите q)" << std::endl;
		for(int i = 0;; ++i){
			c = getchar();
			if(c == '=' || c == '!'){
				comp = 1;
				if(c == '!')
					getchar();
				r = c;
				str[i] = '\n';
				a = Parse(str);
				for(; i >= 0; i--)
					str[i]='0';
				continue;
			}
			if(c == 'q'){
				delete[] str;
				return 0;
			}
			str[i] = c;
			if(c == '\n')
				break;
		}
		b = Parse(str);
		if(comp){
			switch (r){
				case '=':
					if(a==b)
						std::cout << "Да" << std::endl;
					else	
						std::cout << "Нет" << std::endl;
					break;
				case '!':
					if(a!=b)
						std::cout << "Да" << std::endl;
					else	
						std::cout << "Нет" << std::endl;
					break;
			}
			comp = 0;
		} else
			std::cout << b;
	}
}