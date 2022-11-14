#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <conio.h>
#include <cstring>
#include <stdio.h>

using namespace std;

int key;
int VR = 1;
int HR = 1;
int num = 1;

class base
{

public:


	struct Data_el
	{
		char FIO[30];
		unsigned short int sum[1];
		char date[10];
		char FIOad[22];
	};

	struct element
	{
		struct element* next;
		union
		{
			Data_el data;
			unsigned char digit[sizeof(Data_el)];
		};
	};


	struct Queue {
		element* head;
		element* tail;
	};

	void makeQ(struct element** tail, int n)
	{
		element* p;
		for (int i = n; i > 0; i--)
		{
			p = new element;
			//p = (element*)malloc(sizeof(element));
			(*tail)->next = p;
			*tail = p;
		}
		(*tail)->next = NULL;
	}

	void printbase(element* Head)
	{
		int r;
		int k = 0;
		cout << " \t depositor's FIO \t\t Sum   date     advocate's FIO\n" << endl;
		do
		{
			for (int i = 0; i < 20; i++)
			{
				cout << k + 1 << ")\t ";
				cout << Head->data.FIO << "   ";
				cout << Head->data.sum[0] << " ";
				cout << Head->data.date << " ";
				cout << Head->data.FIOad << endl;

				Head = Head->next;
				k++;
			}
			cout << "\n press 0, to stop printing, or any digit to continue" << endl;
			cin >> r;
			if (r == 0)
				break;

		} while (1);
	}

	void load_base(element* head)
	{
		FILE* gr_ppl = fopen("testBase3.dat", "rb");
		for (int i = 0; i < 4000; i++)
		{

			fread(head->data.FIO, sizeof(char), 30, gr_ppl);
			fread(head->data.sum, sizeof(unsigned short int), 1, gr_ppl);
			fread(head->data.date, sizeof(char), 10, gr_ppl);
			fread(head->data.FIOad, sizeof(char), 22, gr_ppl);


			head = head->next;
		}
		fclose(gr_ppl);
	}

	void printallbase(element* head) {
		int k = 0;
		cout << " \t depositor's FIO \t\t Sum   date     advocate's FIO\n" << endl;
		for (int i = 0; i < 4000; i++)
		{
			cout << k + 1 << ")\t ";
			cout << head->data.FIO << "   ";
			cout << head->data.sum[0] << " ";
			cout << head->data.date << " ";
			cout << head->data.FIOad << endl;
			head = head->next;
			k++;
		}
	}
	void makeInd(element* head, element* pbase[]) {
		element* p = head;
		for (int i = 0; i < 4000; i++)
		{
			pbase[i] = p;
			p = p->next;
		}
	}

	int LessOrEqual(element* a, element* b) {

		if (a->data.sum[0] < b->data.sum[0]) return 1;
		if (a->data.sum[0] > b->data.sum[0]) return -1;
		if (strcmp(a->data.date, b->data.date) < 0) return 1;
		if (strcmp(a->data.date, b->data.date) > 0) return -1;
		return 0;
	}

	void hoarasort(element* pdata[], int first, int last)
	{
		int i = first, j = last;
		element* tmp;
		int x = (i + j) / 2;
		element* p = pdata[x];

		do {
			while (LessOrEqual(pdata[i], p) == 1)
				i++;
			while (LessOrEqual(pdata[j], p) == -1)
				j--;

			if (i <= j)
			{
				if (i < j)
				{
					tmp = pdata[i];
					pdata[i] = pdata[j];
					pdata[j] = tmp;
				}
				i++;
				j--;
			}
		} while (i <= j);

		if (i < last)
			hoarasort(pdata, i, last);
		if (first < j)
			hoarasort(pdata, first, j);

	}
	element* PostSort(element* head, element* pdata[])
	{
		element* p;
		p = pdata[0];
		head = p;
		for (int i = 0; i < 4000 - 1; i++)
		{
			p->next = pdata[i + 1];
			p = p->next;
		}
		return head;
	}

	int Search(element* a[], int n, element** tail, int x)
	{
		int L, R, m, r = -1;
		L = 0;
		R = n - 1;
		while (L < R)
		{
			m = (L + R) / 2;
			if (a[m]->data.sum[0] < x)
				L = m + 1;
			else R = m;
		}
		if (a[R]->data.sum[0] == x) {
			puts("\n\n Found notes: \n");
			r = R;
		}
		else puts("Notes weren't found");
		return r;
	}

	element* printsearchlist(element*& head, int k, element* base[], int key, element*& tail, element*& head2, element*& tail2)
	{
		head = base[k];
		element* p = head;
		head2 = p;
		k = 0;
		while (p != NULL && p->data.sum[0] == key)
		{
			cout << k + 1 << ")\t ";
			cout << p->data.FIO << "   ";
			cout << p->data.sum[0] << " ";
			cout << p->data.date << " ";
			cout << p->data.FIOad << endl;
			tail = p;
			tail2 = p;
			p = p->next;
			k++;
		}
		return tail2;
	}



	struct BSTreeNode {
		Data_el* data;
		int Bal;
		struct BSTreeNode* left{};
		struct BSTreeNode* right{};
		struct BSTreeNode* next{};
	};

	void insertNode(BSTreeNode*& root, Data_el* data) {
		if (root == nullptr) {
			root = new BSTreeNode;
			root->data = data;
			root->left = nullptr;
			root->right = nullptr;
		}
		else {
			if (data->FIO < root->data->FIO)
				insertNode(root->left, data);
			else
				insertNode(root->right, data);
		}
	}

	BSTreeNode* findNode(BSTreeNode* root, char* n) {
		if (root == nullptr)
			return nullptr;

		if (strncmp(n, root->data->FIO, 1) == 1)
			return root;

		if (strncmp(n, root->data->FIO, 3) > 0)
			return findNode(root->left, n);
		else
			return findNode(root->right, n);
	}

	void printNode(BSTreeNode* n) {
		if (n != nullptr) {
			cout << n->data->FIO << endl;
		}
		else {
			cout << "Not a valid node!" << endl;
		}
	}

	void INfix_PrintTree(BSTreeNode* p)
	{
		if (p == nullptr)
			return;

		if (p->left != nullptr)
			INfix_PrintTree(p->left);

		cout << num << ")\t ";
		cout << p->data->FIO << "   ";
		cout << p->data->sum[0] << " ";
		cout << p->data->date << " ";
		cout << p->data->FIOad << endl;
		num++;
		INfix_PrintTree(p->right);
	}

	void TreeSearch(BSTreeNode* p, char* FIOd)
	{
		int c = 0;
		
		if (p != NULL) {
			c++;
			if ((strncmp(p->data->FIO, FIOd, 3) < 0) || (c == 3))
			{
				puts("\n\n Found notes: \n");
				cout << num << ")\t ";
				cout << p->data->FIO << "   ";
				cout << p->data->sum[0] << " ";
				cout << p->data->date << " ";
				cout << p->data->FIOad << endl;
				num++;
			}
			else if (strncmp(p->data->FIO, FIOd, 3) < 0)
				TreeSearch(p->right, FIOd);
			else if (strncmp(p->data->FIO, FIOd, 3) > 0)
				TreeSearch(p->left, FIOd);
		}
		else {
			puts("\nNotes not found");
			puts("press any digit('0', '1'...etc) and press ENTER");
			scanf("%d", &key);
		}
	}
	struct sym {
		sym* next;
		float P;	// вероятность символа
		unsigned char data;// сам символ
		int num = 0;	//количество символа в файле	
	};

	struct queue {
		sym* head;
		sym* tail;
	};

	struct s {//тоже структура для кодирования . туда перекачаются записи из очереди sym 
		float P;
		char data;
		int num;
		int L = 0;// длина кодового слова
		char* C; // матрица элементарных кодов.
	};

	void LoadToList(sym*& head, unsigned char ch, int& size)
	{
		if (head == NULL) {
			head = new sym;
			head->data = ch;
			head->num++;
			size++;
			head->next = NULL;

		}
		else if (head->data == ch)
			head->num++;
		else LoadToList(head->next, ch, size);
	}

	void p_calc(sym* head, int size, int count)
	{
		while (head != NULL)
		{
			head->P = (float)head->num / count;
			head = head->next;
		}
	}

	void StackToQueue(struct sym** head, struct sym** tail) {
		(*tail)->next = *head;
		*tail = *head;
		*head = (*head)->next;
		(*tail)->next = NULL;
	}

	void MergeS(sym** head_a, sym** head_b, sym** tail, int q, int r) {
		while (q != 0 && r != 0) {

			if ((*head_a)->P <= (*head_b)->P) {
				StackToQueue(head_a, tail);
				q--;
			}
			else {
				StackToQueue(head_b, tail);
				r--;
			}
		}
		while (q > 0) {
			StackToQueue(head_a, tail);
			q--;
		}
		while (r > 0) {
			StackToQueue(head_b, tail);
			r--;
		}
	}

	void Split(sym** head, sym** head_a, sym** head_b) {
		sym* k, * p;
		*head_a = *head;
		*head_b = (*head)->next;
		k = *head_a;
		p = *head_b;
		while (p != NULL) {
			k->next = p->next;
			k = p;
			p = p->next;
		}
	}

	void MergeSort(sym** head, sym** tail, int n) {
		int i, m, q, p = 1, r;
		sym* a = NULL, * b = NULL;
		queue c[2];
		Split(head, &a, &b);
		while (p < n) {
			c[0].tail = (sym*)&c[0].head;
			c[1].tail = (sym*)&c[1].head;
			i = 0;
			m = n;
			while (m > 0) {
				if (m >= p) q = p;
				else q = m;
				m -= q;
				if (m >= p) r = p;
				else r = m;
				m -= r;
				MergeS(&a, &b, &c[i].tail, q, r);
				i = 1 - i;
			}
			a = c[0].head;
			b = c[1].head;
			p *= 2;
		}
		c[0].tail->next = NULL;
		*head = c[0].head;
	}

	sym* to_reverse(sym* head)
	{
		sym* new_head = NULL;
		while (head)
		{
			sym* next = head->next;
			head->next = new_head;
			new_head = head;
			head = next;
		}
		return new_head;
	}

	void to_array(s charac[], sym* head1, int size)
	{
		for (int i = 0; i < size; i++)
		{
			charac[i].data = head1->data;
			charac[i].num = head1->num;
			charac[i].P = head1->P;
			charac[i].C = new char[size];
			head1 = head1->next;
		}
	}

	int Up(int n, float  q, s charac[])
	{
		int j = 0;
		for (int i = n - 1; i > 0; i--)
		{
			if (charac[i - 1].P <= q)
				charac[i].P = charac[i - 1].P;
			else
			{
				j = i;
				break;
			}
		}
		charac[j].P = q;
		return j;
	}

	void Down(int n, int j, s charac[], int size)
	{
		char* S = new char[size];
		strcpy(S, charac[j].C);
		int L = charac[j].L;
		for (int i = j; i <= n - 2; i++)
		{
			strcpy(charac[i].C, charac[i + 1].C);
			charac[i].L = charac[i + 1].L;
		}
		strcpy(charac[n - 1].C, S);
		strcpy(charac[n].C, S);
		charac[n - 1].C[L] = '0';
		charac[n].C[L] = '1';
		charac[n - 1].L = L + 1;
		charac[n].L = L + 1;
		delete S;
	}

	int Med(s charac[], int L, int R)
	{
		float S_l = 0, S_r; int m;
		for (int i = L; i < R; i++)
			S_l += charac[i].P;
		S_r = charac[R].P;
		m = R;
		while (S_l >= S_r)
		{
			m = m - 1;
			S_l = S_l - charac[m].P;
			S_r = S_r + charac[m].P;
		}
		return m;
	}

	void coding_Fano(s charac[], int L, int R, int k)
	{
		int m;
		if (L < R)
		{
			k++;
			m = Med(charac, L, R);
			for (int i = L; i <= R; i++)
			{
				if (i <= m)
				{
					charac[i].C[k] = '0';
					charac[i].L = charac[i].L + 1;
				}
				else {
					charac[i].C[k] = '1';
					charac[i].L = charac[i].L + 1;
				}
			}
			coding_Fano(charac, L, m, k);
			coding_Fano(charac, m + 1, R, k);
		}
	}

	float totalP(s symbols[], float P, int size)
	{
		int i = 0;
		while (i < size)
		{
			P += symbols[i].P;
			i++;
		}
		return P;
	}

	int readingfile(int& size, int& count, sym*& head1)
	{
		FILE* p = fopen("testBase3.dat", "rb");
		unsigned char ch;
		if (p == NULL) {
			printf("Can't open file");
			return 0;
		}
		while (fread(&ch, sizeof(unsigned char), 1, p) != 0)
		{
			count++;
			LoadToList(head1, ch, size);
		}
		fclose(p);
		return 1;
	}

	void printingcodes(float L_av, float H, s charac[], int size, float Ptotal)
	{
		printf("\ni      Char\tP\t\t L\tCode\n");
		for (int i = 0; i < size; i++) {
			printf("%d\t%c\t%.6f\t%2d\t", i + 1, charac[i].data, charac[i].P, charac[i].L);
			for (int j = 0; j < charac[i].L; j++)
				printf("%c", charac[i].C[j]);
			puts("");
		}
		for (int i = 0; i < size; i++) {
			H += -charac[i].P * log2f(charac[i].P);
			L_av += charac[i].P * charac[i].L;
		}
		printf("\n\nH: %.2f\nL_av: %.2f\nPtotal: %.2f\n", H, L_av, totalP(charac, Ptotal, size));
		puts("\n\npress any digit('0', '1'...etc) and press ENTER");
		scanf("%d", &key);
	}

	struct Tree
	{
		Data_el* data;
		int Bal;
		Tree* left;
		Tree* right;
		Tree* next;
	};

	void B2Next(Tree*& p, element* D) {
		if (p == NULL) {
			p = new Tree;
			p->data = &D->data;
			p->next = NULL;
		}
		else B2Next(p->next, D);
	}

	void B2Insert(element *D, Tree*& p) {
		Tree* q;
		if (p == NULL) {
			p = (Tree*)malloc(sizeof(Tree));
			p->data = &D->data;
			p->left = p->right = p->next = NULL;
			p->Bal = 0;
			VR = 1;
		}
		else if (strncmp(p->data->FIO, D->data.FIO, 3) > 0) {
			B2Insert(D, p->left);
			if (VR == 1) {
				if (p->Bal == 0) {
					q = p->left;
					p->left = q->right;
					q->right = p;
					p = q;
					q->Bal = 1;
					VR = 0;
					HR = 1;
				}
				else {
					p->Bal = 0;
					VR = 1;
					HR = 0;
				}
			}
			else
				HR = 0;
		}
		else if (strncmp(p->data->FIO, D->data.FIO, 3) < 0) {
			B2Insert(D, p->right);
			if (VR == 1) {
				p->Bal = 1;
				HR = 1;
				VR = 0;
			}
			else if (HR == 1) {
				if (p->Bal == 1) {
					q = p->right;
					p->Bal = 0;
					q->Bal = 0;
					p->right = q->left;
					q->left = p;
					p = q;
					VR = 1;
					HR = 0;
				}
				else
					HR = 0;
			}
		}
		else if (strncmp(p->data->FIO, D->data.FIO, 3) == 0) {
			B2Next(p, D);
		}
	}


	void B2(element* list, element* tail, Tree*& p)
	{
		if (list != NULL) {
			while (list != tail) {
				B2Insert(list, p);
				list = list->next;
			}
			B2Insert(list, p);
		}
	}

	void INfix_PrintTree(Tree* p)
	{
		if (p == NULL)
			return;

		if (p->left != NULL)
			INfix_PrintTree(p->left);

		cout << num << ")\t ";
		cout << p->data->FIO << "   ";
		cout << p->data->sum[0] << " ";
		cout << p->data->date << " ";
		cout << p->data->FIOad << endl;
		num++;
		if (p->next != NULL)
			INfix_PrintTree(p->next);
		if (p->right != NULL)
			INfix_PrintTree(p->right);
	}



};








int main()
{
	
	base database;
	base::element* head, * head2, * tail, * tail2;
	head = NULL;
	head2 = NULL;
	tail2 = NULL;
	tail = (base::element*)&head;
	database.makeQ(&tail, 4000);
	database.load_base(head);

	base::element* pbase[4000];
	database.makeInd(head, pbase);

	base::BSTreeNode* root = NULL;

	int count = 0, size = 0; float H = 0, L_av = 0, Ptotal = 0;//count- колво всех символов в файле size количество всех разных 
												//символов h-энтропия l_av-средняя длина слова 
												//Ptotal-сумма всех вероятностей символов 6 часть 
	base::sym* head1 = NULL, * tail1 = (base::sym*)&head1;	// создаем очередь. там будут храниться символы из файла и параметры символов 
										//	для кодирования 6 часть

	char ch;
	while (1)
	{
		cout << "1 - Print base " << endl;
		cout << "2 - Print all base " << endl;
		cout << "3 - Sort base " << endl;
		cout << "4 - Search" << endl;//перед поиском нужно сделать'Sort base'
		cout << "5 - Show tree " << endl;//перед деревом нужно сделать 'Search'
		cout << "6 - Find note in tree " << endl;//перед поиском в дереве нужно сделать 'Show tree'
		cout << "7 - coding Fano" << endl;
		cout << "q - Exit " << endl;
		cin >> ch;

		int key{ 0 };

		if (ch == '1') {
			database.printbase(head);
		}
		if (ch == '2') 
		{
			database.printallbase(head);
		}
		if (ch == '3') 
		{
			database.hoarasort(pbase, 0, 3999);
			head = database.PostSort(head, pbase);
		}
		if (ch == '4') 
		{
			cout << "Enter sum to search" << endl;
			cin >> key;
			tail2 = database.printsearchlist(head, database.Search(pbase, 4000, &tail, key), pbase, key, tail, head2, tail2);
			head2 = pbase[0];
		}
		if (ch == '5')
		{
			base::BSTreeNode *head3 = NULL;
			base::element* p = head2;
			while (p != tail2)
			{
				database.insertNode(root,&p->data);
				p = p->next;
			}
			cout << "Builded tree:" << endl;
			puts("");
			database.INfix_PrintTree(root);
		}
		if (ch == '6')
		{
			char n;
			cin >> n;
			database.TreeSearch(root, &n);
			
		}
		if (ch == '7') 
		{
			if (database.readingfile(size, count, head1) == 0)//считываем файл и заносим символы в очередь, заодно считаем размер файла при помощи переменной count
				return 0;
			base::s *charac = new base::s[size];// объявляем массив структур
			database.p_calc(head1, size, count);//вычисляем вероятности для каждого символа	
			database.MergeSort(&head1, &tail1, size);//сортируем очередь по вероятностям
			head1 = database.to_reverse(head1);// переворачиваем очередь так как для кода Хаффмена нада чтобы символы стояли по убыванию вероятностей		
			database.to_array(charac, head1, size);//заливаем очередь в массив структур
			database.coding_Fano(charac, 0, size - 1, -1);// само кодирование
			database.printingcodes(L_av, H, charac, size, Ptotal);// вывод кодовых слов и прочего после кодирования
		}
		if (ch == 'q') 
		{
			break;
		}
		
	}
	return 0;
}
