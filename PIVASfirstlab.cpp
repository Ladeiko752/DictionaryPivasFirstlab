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
	void AddElementInTree(string eng_word, string rus_word, Dictionary** t) {
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
		bool find = true;
		if ((*t) == NULL)
		{
			cout << "Упс! Вашего слова нет в словаре :(" << endl;
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
				(*t)->russish_word = "";
			}

			if ((*t)->left != NULL && (*t)->right != NULL)
			{

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

	Dictionary* ChangeWord(string search_russ_word, string new_russ_word, Dictionary** t) {
		if ((*t) == NULL)
		{
			return NULL;
		}

		if (search_russ_word == (*t)->russish_word)
		{
			(*t)->russish_word = new_russ_word;
			cout << "Замена перевода проведена успешно!" << endl;
		}

		if (search_russ_word > (*t)->russish_word)
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
		if (search_russ_word < (*t)->russish_word)
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
			cout << t->english_word << " - " << t->russish_word << endl;
			count++;
		}
		
	}
};


	int main()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "Russian");
		string ew, rw, sew, new_russian_word;
		int count = 0;
		Dictionary dict;
		Dictionary* tree = NULL; // проблемы с инициализацией, подчеркивает ошибку на ссыль 
		int buff = 0;
		do
		{
			cout << "\tАнгло-русский словарь\n";
			cout << "1. Добавить слово в словарь\n";
			cout << "2. Поиск перевода слова\n";
			cout << "3. Удалить слово из словаря\n";
			cout << "4. Замена слова, переведенного на русский язык\n";
			cout << "5. Узнать количество слов в словаре\n";
			cin >> buff;
			switch (buff)
			{
			case 1: {
				cout << "Введите английское слово: ";
				cin >> ew;
				cout << "Введите русское слово: ";
				cin >> rw;
				dict.AddElementInTree(ew, rw, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				cout << "Введите английское слово, перевод которого вы хотите узнать: ";
				cin >> sew;
				dict.SearchWord(sew, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				cout << "Введите английское слово, котороe вы хотите удалить: ";
				cin >> sew;
				dict.DeleteList(sew, &tree);
				system("pause");
				system("cls");
				break;
			}
			case 4: {
				cout << "Введите ошибочно введенное вами русское слово: ";
				cin >> rw;
				cout << "Введите верный перевод: ";
				cin >> new_russian_word;
				dict.ChangeWord(rw, new_russian_word, &tree);
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
			}
		} while (true);
	}

