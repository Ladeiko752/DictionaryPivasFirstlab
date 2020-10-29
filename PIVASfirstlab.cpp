#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

class Dictionary
{
public:
	string russian_word;
	string english_word;
	Dictionary* left;
	Dictionary* right;
	Dictionary* tree = NULL;
	/*
	Добавление эллемента в дерево. Производится проверка на наличие элементов в дереве. Если таковых нет, создается корневой элемент
	в левое и правое поддерево помещается NULL. Если дерево не пустое текущий элемент сравнивается с родительским, если больше - помещается
	в правое поддерево, иначе в левое. 
	*/
	void AddElementInTree(string eng_word, string rus_word, Dictionary** t) {
		if ((*t) == NULL)
		{
			(*t) = new Dictionary;
			(*t)->english_word = eng_word;
			(*t)->russian_word = rus_word;
			(*t)->left = NULL;
			(*t)->right = NULL;
			return;
		}
		else
		{
			if (eng_word <= (*t)->english_word)
			{
				AddElementInTree(eng_word, rus_word, &(*t)->left);
			}
			if (eng_word > (*t)->english_word)
			{
				AddElementInTree(eng_word, rus_word, &(*t)->right);
			}
		}
	}
	/*
	Происходит поиск слова по заданному ключу. Вводимый пользователем ключ сравнивается с элементами дерава, тем самым образом обходя элементы.
	После нахождения в консоль вводится искомое слово вместе с переводом на русский язык.
	*/
	Dictionary* SearchWord(string search_engl_word, Dictionary** t) {
	
		if ((*t) == NULL)
		{
			cout << "Упс! Вашего слова нет в словаре :(" << endl;
			return NULL;
		}

		if (search_engl_word == (*t)->english_word)
		{
			cout << (*t)->english_word << " - " << (*t)->russian_word << endl;
		}

		if (search_engl_word > (*t)->english_word)
		{
			if ((*t)->right != NULL)
			{
				return SearchWord(search_engl_word, &(*t)->right);
			}
			else
			{
				cout << "Упс! Вашего слова нет в словаре :(" << endl;
				return NULL;
			}
		}
		if (search_engl_word < (*t)->english_word)
		{
			if ((*t)->left != NULL)
			{
				return SearchWord(search_engl_word, &(*t)->left);
			}
			else
			{
				cout << "Упс! Вашего слова нет в словаре :(" << endl;
				return NULL;
			}
		}
	}
	/*
	Функция работает аналогично функции поиска, только найденное значение очищается по таковым принципам:
	1. Если заданный элемент не имеет поддеревьев его значение просто очищается 
	2. Если заданный элемент имеет одно из двух возможныз поддеревьев его значение заменяется на ближайшее.
	3. Если заданный элемент имеет два поддерева его значение заменяется на ближайшее к нему (самый малый элемент его правого поддерева)
	*/
	Dictionary* DeleteList(string search_engl_word, Dictionary** t) {
		if ((*t) == NULL)
		{
			cout << "Упс! Данного слова нет в словаре :(" << endl;
			return NULL;
		}
		if (search_engl_word == (*t)->english_word)
		{
			if ((*t)->left == NULL && (*t)->right == NULL)
			{
				(*t)->english_word = "";
				(*t)->russian_word = "";
			}

			if ((*t)->left != NULL && (*t)->right != NULL)
			{

			}

			if ((*t)->left != NULL || (*t)->right != NULL)
			{

				if ((*t)->right != NULL)
				{
					(*t)->russian_word = (*t)->right->russian_word;
					(*t)->english_word = (*t)->right->english_word;
					(*t)->right = NULL;
				}
				if ((*t)->left != NULL)
				{
					(*t)->russian_word = (*t)->left->russian_word;
					(*t)->english_word = (*t)->left->english_word;
					(*t)->left = NULL;
				}
			}
		}

		if (search_engl_word < (*t)->english_word)
		{
			if ((*t)->left != NULL)
			{
				return DeleteList(search_engl_word, &(*t)->left);
			}
			else
			{
				return NULL;
			}
		}
		if (search_engl_word > (*t)->english_word)
		{
			if ((*t)->right != NULL)
			{
				return DeleteList(search_engl_word, &(*t)->right);
			}
			else
			{
				return NULL;
			}
		}
	}
	/*
	Функция работает аналогично функции поиска. Пользователем задается два слово: перевод которого он хотел бы заменить и
	слово на которое он хотел бы его заменить
	*/
	Dictionary* ChangeWord(string search_russ_word, string new_russ_word, Dictionary** t) {
		if ((*t) == NULL)
		{
			return NULL;
		}

		if (search_russ_word == (*t)->russian_word)
		{
			(*t)->russian_word = new_russ_word;
			cout << "Замена перевода проведена успешно!" << endl;
		}

		if (search_russ_word > (*t)->russian_word)
		{
			if ((*t)->right != NULL)
			{
				return ChangeWord(search_russ_word, new_russ_word, &(*t)->right);
			}
			else
			{
				return NULL;
			}
		}
		if (search_russ_word < (*t)->russian_word)
		{
			if ((*t)->left != NULL)
			{
				return ChangeWord(search_russ_word, new_russ_word, &(*t)->left);
			}
			else
			{
				return NULL;
			}
		}
	}

	void WordCount(Dictionary* t, int& count) {
		if (t != NULL) {
			WordCount(t->left, count);
			WordCount(t->right, count);
			cout << t->english_word << " - " << t->russian_word << endl;
			count++;
		}
		
	}
};

class FileDictionary : public Dictionary{
private:
	ofstream dict_file_output;
	string path = "Dictionary.txt";
public:
	void PrintDictionary(Dictionary* t) {
		if (t != NULL) {
			PrintDictionary(t->left);
			PrintDictionary(t->right);
			dict_file_output << t->english_word << " - " << t->russian_word << endl;
		}
	}
	void File_ouput(Dictionary* t) {
		dict_file_output.open(path);
		if (!dict_file_output.is_open())
		{
			cout << "Ошибка. Словарь не выгружен в файл" << endl;
		}
		else
		{
			PrintDictionary(t);
		}
	}

};

class DictionaryMenu : public FileDictionary {
private:
	int buff = 0;
	string eng_word, rus_word, search_eng_word, new_russian_word;
	int count = 0;
	Dictionary dict;
	FileDictionary file;
	Dictionary* tree = NULL;
public:
	int PrintMenu() {
		do
		{
			cout << "\tАнгло-русский словарь\n";
			cout << "1. Добавить слово в словарь\n";
			cout << "2. Поиск перевода слова\n";
			cout << "3. Удалить слово из словаря\n";
			cout << "4. Замена слова, переведенного на русский язык\n";
			cout << "5. Узнать количество слов в словаре\n";
			cout << "6. Загрузка в файл\n";
			cout << "Выберете пункт меню и нажмите Enter: ";
			cin >> buff;
			switch (buff)
			{
			case 1: {
				cout << "Введите английское слово: ";
				cin >> eng_word;
				cout << "Введите русское слово: ";
				cin >> rus_word;
				dict.AddElementInTree(eng_word, rus_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				cout << "Введите английское слово, перевод которого вы хотите узнать: ";
				cin >> search_eng_word;
				dict.SearchWord(search_eng_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				cout << "Введите английское слово, котороe вы хотите удалить: ";
				cin >> search_eng_word;
				dict.DeleteList(search_eng_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 4: {
				cout << "Введите ошибочно введенное вами русское слово: ";
				cin >> rus_word;
				cout << "Введите верный перевод: ";
				cin >> new_russian_word;
				dict.ChangeWord(rus_word, new_russian_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 5: {
				dict.WordCount(tree, count);
				cout << endl;
				cout << "Итого, в словаре " << count << " слов(а)";
				count = 0;
				system("pause");
				system("cls");
				break;
			}
			case 6: {
				file.File_ouput(tree);
				cout << "Словарь успешно загружен в файл!" << endl;
				system("pause");
				system("cls");
				break;
			}
			}
		} while (true);
	}

};

	int main()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "Russian");
		string eng_word, rus_word, search_eng_word, new_russian_word;
		int count = 0;
		Dictionary dict;
		FileDictionary file;
		DictionaryMenu menu;
		Dictionary* tree = NULL; // проблемы с инициализацией, подчеркивает ошибку на ссыль 
		int buff = 0;
		do
		{
			menu.PrintMenu();
			/*
			cout << "\tАнгло-русский словарь\n";
			cout << "1. Добавить слово в словарь\n";
			cout << "2. Поиск перевода слова\n";
			cout << "3. Удалить слово из словаря\n";
			cout << "4. Замена слова, переведенного на русский язык\n";
			cout << "5. Узнать количество слов в словаре\n";
			cout << "6. Загрузка в файл\n";
			cout << "Выберете пункт меню и нажмите Enter: ";
			cin >> buff;
			menu.PrintMenu();
			switch (buff)
			{
			case 1: {
				cout << "Введите английское слово: ";
				cin >> eng_word;
				cout << "Введите русское слово: ";
				cin >> rus_word;
				dict.AddElementInTree(eng_word, rus_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				cout << "Введите английское слово, перевод которого вы хотите узнать: ";
				cin >> search_eng_word;
				dict.SearchWord(search_eng_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				cout << "Введите английское слово, котороe вы хотите удалить: ";
				cin >> search_eng_word;
				dict.DeleteList(search_eng_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 4: {
				cout << "Введите ошибочно введенное вами русское слово: ";
				cin >> rus_word;
				cout << "Введите верный перевод: ";
				cin >> new_russian_word;
				dict.ChangeWord(rus_word, new_russian_word, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 5: {
				dict.WordCount(tree, count);
				cout << endl;
				cout << "Итого, в словаре " << count << " слов(а)";
				count = 0;
				system("pause");
				system("cls");
				break;
			}
			case 6: { 
				file.File_ouput(tree);
				cout << "Словарь успешно загружен в файл!" << endl;
				system("pause");
				system("cls");
				break;
			}
			}
			*/
		} while (true);
	}

