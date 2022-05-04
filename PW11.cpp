#include <vector>
#include <iostream>
#include <list>
#include <bits/stdc++.h> 
using namespace std;

struct element{ //Структура элемен та множества 
	int number; //Переменная номера читательского билета(согласно варианта)
	string name; //Имя владельца билета 
	string adres; //Адрес владельца билета
	element(){ //Конструктор, рандомно заполняющий поля структуры
		srand(time(0)+rand()); //Инициализация генератора рандомных чисел
		number = 1 + rand() % 99999; //Запонение номера
		name = "Name_" + to_string(number); //Заполнение поля имени
		adres = "Adr_" + to_string(number); //Заполнение поля адреса
	}	
};
class aboniment{ //Класс множества
	public:
	element M[10000]; //Массив элементов
	int max_move = 0; //Переменная максимального сдвига(нужна для поиска в нескольких дублирующихся элементах)
	aboniment(){ //Конструктор множества, делает множество изначально пустым
		for(int i=0; i<10000;i++){ //Для каждой ячейкит множества
			M[i].number = 0; //Удаление номера
			M[i].name = ""; //Удаление имени
			M[i].adres = ""; //Удаление адреса
		}		
	}
	int hashFunc(int num){ //Метод создания хэш суммы из номера
		int hash;
		num = num/10;
		if(num%2){
			hash = num/2;
		} else {
			hash =  10000 - num/2;
		}
		return hash;
	}
	void add(element A){ //Метод добавления элемента к множеству
		int h = hashFunc(A.number); //Вычисление хэш суммы
		int place = 0; //Переменная для места в таблице
		if(M[h].name == ""){ //Поиск пустой ячейки в начале 
			M[h] = A; //Запись элемента в множество
		} else {
			for(int i=1; i<10000;i++){ //Поиск пустой ячейки
				if(h + i < 10000) {  //Поиск в ячейках ПОСЛЕ хэш номера
					if(M[h + i].name == ""){
						M[h+i] = A; //Запись элемента в множество
						max_move = i; //Заполним максимальное смещение при исправлении коллизии
						break;
					}
				} else {
					if(M[h + i].name == ""){ //Поиск в ячейках ДО хэш номера(с переносом из конца массива в начало)
						M[h+i-10000] = A; //Запись элемента в множество
						max_move = i; //Заполним максимальное смещение при исправлении коллизии
						break;
					}
				}								
			}	
		}
	}
	void list(){ //Метод для вывода элементов множества
		for(int i=0; i<10000;i++){ //Для всех ячеек в множества
			if(M[i].name != ""){ //Если ячейка НЕ пустая 
						cout<<"\tЭлемент: "<<i<<") "<<"\tНомер: "<<M[i].number<<"\tИмя: "<<M[i].name<<"\tАдрес: "<<M[i].adres<<endl;	//Выводим содержимое ячейки
					}			
		}		
	} 
	void rem(int num){ //Метод для удаления элемента по номеру
		int h = hashFunc(num); //Вычисляем хэш сумму по номеру элемента
				M[h].number = 0; M[h].name = ""; M[h].adres = ""; //Удаляем элемент испуользуя хэш сумму для прямого доступа
	}
	void find(int num){ //Мутод для поиска элемента множества по его номеру с использованием хэш суммы
		int h = hashFunc(num); //Вычисляем хэш сумму
				cout<<"\tЭлемент: "<<h<<") "<<"\tНомер: "<<M[h].number<<"\tИмя: "<<M[h].name<<"\tАдрес: "<<M[h].adres<<endl;	 //Удаляем элемент используя хэш сумму для прямого доступа ко множеству
	}	
};

int main()
{
	setlocale(LC_ALL, "Russian"); //Меняем язык вывода консоли
	aboniment N1; //Создаём объект множества
	element E1,E2,E3,E4,E5,E6; //Объявляем элементы, которые вставим в множество
	N1.add(E1); N1.add(E2); N1.add(E3); N1.add(E4); N1.add(E5); N1.add(E6);//Добавляем элементы во множество
	cout<<"Выведем изначальный список из трёх элементов, хэш сумма каждого элемента есть его номер ячейки массива, с поправкой на возникающие коллизии"<<endl;
	N1.list(); //Вывод множества
	cout<<"Добавим дубликат элемента, элемент с уже имеющимся номером, из которого получится поторяющаяся хэш сумма"<<endl;
	cout<<"В данном случае согдасно варианта (Хэширование с открытой адресацией) хэш сумма и номер ячейки увеличатся на 1"<<endl;
	E2.name = "Дубликат"; //Выделяем элемент - дубликат
	N1.add(E2); //Добавляем дубликат во множество
	N1.list(); //Вывод множества
	cout<<"Согласно задания удалим из списка элемент по его номеру"<<endl;
	N1.rem(E1.number); //Удалим элемент множества, т.к. номера элементов всегда разные, берём их из поля уже имеющегося объекта структуры элемента множества
	N1.list(); //Вывод множества
	cout<<"Согласно задания найдём элемент по номеру"<<endl;
	N1.find(E3.number); //Демонстрация поиска элемента
    return 0;
}