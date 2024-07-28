#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
using namespace std;
int alphabet[26] = { 0 };
char ch_arr[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
void calculate_freq(string s)
{
	int i = 0, j = 0;
	while (s[i] != '\0') {
		if (s[i] >= 'a' && s[i] <= 'z' || (s[i]>='A' && s[i]<='Z')) {
			if (s[i] >= 'A' && s[i] <= 'Z')
				s[i] += 32;
			j = s[i] - 'a';
			++alphabet[j];
		}
		++i;
	}
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i] == 0)
		{
			alphabet[i] = -1;
		}
	}
}
class charNode
{
public:
	int count;
	char ch, bit;
	charNode* next;
	charNode* left;
	charNode* right;
	charNode()
	{
		count = 0;
		ch = ' ';
		bit = '0';
		next = left = right = NULL;
	}
	charNode(char ch1, int freq)
	{
		ch = ch1;
		count = freq;
		bit = '0';
		next = left = right = NULL;
	}
	~charNode() {}
	void inorder(charNode* root)
	{
		if (root)
		{
			cout << root->count << root->ch << root->bit << " ";
			inorder(root->left);
			inorder(root->right);
		}
	}
};
class priorQueue {
public:
	charNode* front;
	charNode* rear;
	int size;
	priorQueue()
	{
		front = rear = NULL;
		size = 0;
	}
	~priorQueue() {}
	bool isEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}
	void enque(charNode* newNode)
	{
		if (isEmpty())
		{
			front = newNode;
			rear = newNode;
			size++;
			return;
		}
		charNode* temp = front->next, * prev = front;
		if (newNode->count < front->count)
		{
			newNode->next = front;
			front = newNode;
			size++;
			return;
		}
		while (temp)
		{
			if (newNode->count < temp->count)
			{
				newNode->next = prev->next;
				prev->next = newNode;
				size++;
				return;
			}
			prev = prev->next;
			temp = temp->next;
		}
		prev->next = newNode;
		newNode->next = NULL;
		size++;
	}
	void deque(charNode*& newNode1)
	{
		charNode* temp;
		if (isEmpty())
			return;
		temp = front->next;
		newNode1 = front;
		front = temp;
		size--;
	}
	void display()
	{
		charNode* curr = front;
		while (curr)
		{
			/*cout << curr->ch << curr->count */cout << "( ";
			curr->inorder(curr);
			cout << ") ";
			curr = curr->next;
		}
	}
};
class huffTree
{
	priorQueue hufQue;

public:
	charNode* root;
	huffTree()
	{
		root = NULL;
	}
	void huffmanEncoding()
	{
		charNode* newNode, * newNode1, * newNode3;
		for (int i = 0; i < 26; i++)
		{
			if (alphabet[i] != -1)
			{
				charNode* newNode4 = new charNode(ch_arr[i], alphabet[i]);
				hufQue.enque(newNode4);
			}
		}
		while (hufQue.size > 1)
		{
			hufQue.deque(newNode);//get first element of que
			hufQue.deque(newNode1);//get second elemnt of que
			newNode->bit = '0';
			newNode1->bit = '1';
			int sumFreq = newNode->count + newNode1->count;
			newNode3 = new charNode('*', sumFreq);
			newNode3->left = newNode;
			newNode3->right = newNode1;
			hufQue.enque(newNode3);
			newNode = newNode1 = NULL;
			cout << endl;
		}
		root = hufQue.front;
	}
	void compressingText(charNode* root, string bit, string sent[])
	{
		if (root != NULL)
		{
			if (root->ch != '*')
			{
				sent[root->ch - 'a'] = bit;
				return;
			}
			string bit_copy = bit;
			if (root->left)
			{
				bit += '0';
				compressingText(root->left, bit, sent);
			}
			if (root->right)
			{
				bit = bit_copy;
				bit += '1';
				compressingText(root->right, bit, sent);
			}
		}
	}
	void decode(string bit, string& userText)
	{
		charNode* curr = root;
		for (int i = 0; i < bit.length(); i++)
		{
			if (bit[i] == ' ' || bit[i]=='.')
			{
				cout << bit[i];
				userText += bit[i];
				curr = root;
			}
			else if (bit[i] == '0')
				curr = curr->left;
			else
				curr = curr->right;
			if (curr->left == NULL && curr->right == NULL)
			{
				cout << curr->ch;
				userText += curr->ch;
				curr = root;
			}

		}
	}
	charNode* getRoot()
	{
		return root;
	}
	void writeTreetoFile(charNode* root, fstream& myfile)
	{
		if (root)
		{
			myfile << root->ch << root->bit << endl;
			writeTreetoFile(root->left, myfile);
			writeTreetoFile(root->right, myfile);
		}
		else
			myfile << "$" << endl;
	}
	void readFromTextFile(charNode*& root, fstream& myfile, string word)
	{
		if (!myfile.eof())
		{
			getline(myfile, word);
			if (word[0] != '$')
			{
				root = new charNode(word[0], 0);
				root->bit = word[1];
				readFromTextFile(root->left, myfile, word);
				readFromTextFile(root->right, myfile, word);
			}
		}

	}
};
class treeNode {
public:
	char value;
	bool isEnd;
	treeNode* alphabets[26];
	treeNode()
	{
		value = '-';
		isEnd = 0;
		for (int i = 0; i < 26; i++)
			alphabets[i] = NULL;
	}
};
class TrieTree {
	treeNode* root;
public:
	TrieTree()
	{
		root = new treeNode;
	}
	void insertInTree(string word)
	{
		int index = 0;
		treeNode* current = root;
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
				word[i] = word[i] + 32;
			index = word[i] - 'a';
			if (current->alphabets[index] == NULL)
			{
				current->alphabets[index] = new treeNode;
				current->alphabets[index]->value = word[i];
			}
			current = current->alphabets[index];
		}
		current->isEnd = 1;
	}
	void getSuggestionQueue(treeNode* curr, string word, queue<string>& suggestions)
	{
		if (curr->isEnd == 1)
			suggestions.push(word);
		for (int i = 97; i < 123; i++)
		{
			string word_copy = word;
			treeNode* traverse = curr->alphabets[i - 'a'];
			if (traverse != NULL)
			{
				word += ch_arr[i - 'a'];
				getSuggestionQueue(traverse, word, suggestions);
				word = word_copy;
			}
		}
	}
	void getSuggestion(string word, queue<string>& suggestions)
	{
		treeNode* curr = root;
		if (root == NULL)
			return;
		bool flag = 1;
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
				word[i] = word[i] + 32;
			if (curr->alphabets[word[i] - 'a'] != NULL)
				curr = curr->alphabets[word[i] - 'a'];//point current to last character of given word
			else
			{
				flag = 0;
				break;
			}

		}
		if (flag == 1)
			getSuggestionQueue(curr, word, suggestions);//call the suggestion function

	}
};
void printText(string userText, string suggest, string suggArr[], int ind)
{
	if (ind >= 10)
		cout << userText << " " << suggest;
	else
		cout << userText << " " << suggest << "\t" << suggArr[ind];
}
void saveUserText(string userText)
{
	fstream myFile;
	huffTree ht2;
	string bit = "", sent[26];
	calculate_freq(userText);
	ht2.huffmanEncoding();
	ht2.compressingText(ht2.root, bit, sent);
	bit = "";
	for (int i = 0; i < userText.length(); i++)
	{
		if (userText[i] == ' ' || userText[i] == '.')
			bit += userText[i];
		else
		{
			if (userText[i] >= 'A' && userText[i] <= 'Z')
				userText[i] += 32;
			bit += sent[userText[i] - 'a'];
		}

	}
	myFile.open("userText.txt");
	cout << endl;
	myFile << bit << endl;
	myFile.close();
	myFile.open("HuffTree.txt");
	ht2.writeTreetoFile(ht2.root, myFile);
	myFile.close();
}
int main()
{
	bool cptl = 0, saveFlag = 0;
	int choice, i = 0;
	fstream myFile;
	myFile.open("dictionary.txt");
	queue<string> suggestions;
	TrieTree obj;
	string word;
	string userText = "", suggest = "";
	string* suggestionArr = new string[10];
	huffTree ht1;
	for (int i = 0; i < 10; i++)
		suggestionArr[i] = " ";
	while (!myFile.eof())
	{
		getline(myFile, word);
		obj.insertInTree(word);
	}
	myFile.close();
	char ch1;
	cout << "\t Welcome to Text Editior\n\n";
	cout << " What you want to do\n 1. Enter new Text.\n 2. Load a saved Text and start editing.\n";
	cout << " Enetr your choice: ";
	cin >> choice;
	system("cls");
	if (choice == 2)
	{
		string bit, word;
		myFile.open("userText.txt");
		getline(myFile, bit);
		myFile.close();
		myFile.open("HuffTree.txt");
		ht1.readFromTextFile(ht1.root, myFile, word);
		myFile.close();
		ht1.decode(bit, userText);
	}
	system("cls");
	cout << userText << " ";
	do {
		ch1 = _getch();
		if ((ch1 >= 'a' && ch1 <= 'z') || (ch1 >= 'A' && ch1 <= 'Z'))
		{
			saveFlag = 0;
			suggest += ch1;
			obj.getSuggestion(suggest, suggestions);
			int k = 0;
			while (!suggestions.empty())
			{
				if (k < 10)
					suggestionArr[k] = suggestions.front();
				suggestions.pop();
				k++;
			}
		}
		else if (ch1 == '.')// if usser enters '.' then just append it and make capital flag=1
		{
			saveFlag = 0;
			if (ch1 == '.')
				cptl = 1;
			if (userText == "")//for capitalising the first letter
			{
				suggest[0] -= 32;
				userText += suggest;
			}
			else
			{
				userText += suggest;
				userText += ch1;
			}
			suggest = "";
			for (int i = 0; i < 10; i++)
				suggestionArr[i] = " ";
			i = 0;
		}
		else if (ch1 == ' ')
		{
			saveFlag = 0;
			if (cptl == 1)// if capital flag==1 then we will make first letter cpaital
			{
				suggest[0] -= 32;
				cptl = 0;
			}
			if (userText == "")//for capitalising the first letter
			{
				suggest[0] -= 32;
				userText += suggest;
			}
			else
			{
				userText += suggest;
				userText += ch1;
			}
			suggest = "";
			for (int i = 0; i < 10; i++)
				suggestionArr[i] = " ";
			i = 0;
		}
		else if (ch1 == '/')
		{
			saveFlag = 0;
			i++;
		}
		else if (ch1 == ';')// if user press ';' then we will append suggestion to userText
		{
			saveFlag = 0;
			if (userText == "")//if user text is smpty then we make capital flag=1
				cptl = 1;
			if (i < 10)// if capital flag==1 then we will make first letter cpaital
			{
				suggest = suggestionArr[i];
				if (cptl == 1)
				{
					suggest[0] -= 32;
				}
				userText += suggest;
				cptl = 0;
			}
			else
				userText += " ";
			suggest = "";
			for (int j = 0; j < 10; j++)
				suggestionArr[j] = " ";
			i = 0;
		}
		else if (ch1 == '=')
		{
			saveUserText(userText);// save the user text
			saveFlag = 1;
		}
		system("cls");
		printText(userText, suggest, suggestionArr, i);
	} while (ch1 != 13);//if user presses enter program will terminate
	system("cls");
	if (saveFlag == 0)// text is not save so we will aks the user if wanna save the text or not
	{
		cout << " Do you wanna save your text\n 1. Save & Exit\n 2. Not Save & Exit\n Enter your choice: ";
		cin >> choice;
		if (choice == 1)
		{
			saveUserText(userText);// save the user text
		}
	}
	system("pause");
}