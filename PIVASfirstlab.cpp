#include <iostream>
#include <windows.h>

using namespace std;

class Dictionary
{
private:
	string english_word;
	string russish_word;
	Dictionary* left;
	Dictionary* right;
public:
	Dictionary* tree = NULL;
	void AddElementInTree(string eng_word, string rus_word, Dictionary **t) {
		if ((*t) == NULL)
		{
			(*t) = new Dictionary;
			(*t)->english_word = eng_word;
			(*t)->russish_word = rus_word;
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

	Dictionary* SearchWord(string search_engl_word, Dictionary** t) {
		if ((*t) == NULL)
		{
			cout << "Упс! Данного слова нет в словаре :(" << endl;
			return NULL;
		}
		
		if (search_engl_word == (*t)->english_word)
		{
			cout << (*t)->english_word << " - " << (*t)->russish_word << endl;
		}
		if (search_engl_word > (*t)->english_word)
		{
			if ((*t)->right != NULL)
			{
				return SearchWord(search_engl_word, &(*t)->right);
			}
			else
			{
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
				return NULL;
			}
		}
	}

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
			}
			if ((*t)->left != NULL || (*t)->right != NULL)
			{

				if ((*t)->right != NULL)
				{
					(*t)->russish_word = (*t)->right->russish_word;
					(*t)->english_word = (*t)->right->english_word;
					(*t)->right = NULL;
				}
				if ((*t)->left != NULL)
				{
					(*t)->russish_word = (*t)->left->russish_word;
					(*t)->english_word = (*t)->left->english_word;
					(*t)->left = NULL;
				}
			}
			if ((*t)->left != NULL && (*t)->right != NULL)
			{

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

};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	string ew, rw, sew;
	Dictionary dict;
	Dictionary* tree = NULL; // залупа с инициализацией, подчеркивает ошибку на ссыль 
	int buff = 0;
	do
	{
		cout << "\tАнгло-русский словарь\n";
		cout << "1. Добавить слово в словарь\n";
		cout << "2. Поиск перевода слова\n";
		cout << "3. Удалить слово из словаря\n";
		cin >> buff;
		switch (buff)
		{
		case 1:
			cout << "Введите английское слово: ";
			cin >> ew;
			cout << "Введите русское слово: ";
			cin >> rw;
			dict.AddElementInTree(ew, rw, &tree);
			system("pause");
			system("cls");
			break;
		case 2: 
			cout << "Введите английское слово, перевод которого вы хотите узнать: ";
			cin >> sew;
			dict.SearchWord(sew, &tree);
			system("pause");
			system("cls");
			break;
		case 3: 
			cout << "Введите английское слово, котороe вы хотите удалить: ";
			cin >> sew;
			dict.DeleteList(sew, &tree);
			system("pause");
			system("cls");
			break;
		}
	} while (true);
}
