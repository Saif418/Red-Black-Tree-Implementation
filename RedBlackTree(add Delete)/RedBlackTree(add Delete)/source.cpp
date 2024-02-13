#include<iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

struct Node
{
	int value = 0;
	char color = 'r';
	Node* left = NULL;
	Node* right = NULL;

};



class RedBlack
{
private:
	int redCount = 0;
	Node* root = NULL;
	bool doubleBack = false;

	void insertNode(int value, Node*& trav)
	{
		if (trav == NULL)
		{
			trav = new Node;
			trav->value = value;
			trav->color = 'r';  // red node
			redCount = 1;
			return;
		}

		if (value < trav->value) //Left
		{
			insertNode(value, trav->left);

			if (redCount == 2)
			{
				// case 1
				if (trav->right && trav->right->color == 'r')
				{
					//color swap
					trav->color = 'r';
					trav->left->color = 'b';
					trav->right->color = 'b';
					redCount = 1;

				}
				else if (trav->left->left && trav->left->left->color == 'r')
				{  // rotate right
					rightRotate(trav);
					trav->right->color = 'r';
					trav->left->color = 'r';
					trav->color = 'b';
					redCount = 0;
				}
				else {
					// left rotate, right rotate        // uncle is black                              
					leftRotate(trav->left);
					rightRotate(trav);
					trav->right->color = 'r';
					trav->left->color = 'r';
					trav->color = 'b';
					redCount = 0;

				}

			}
			else if (redCount == 1) // keeps track of the red
			{
				if (trav->color == 'b')
				{
					redCount = 0;
				}
				else {
					redCount = 2;
				}
			}
			else
			{
				if (trav->color == 'b')
				{
					redCount = 0;
				}
				else {
					redCount = 1;
				}


			}

			return;

		}
		else if (value >= trav->value) //Right
		{
			insertNode(value, trav->right);

			if (redCount == 2)
			{
				// cases
				if (trav->left && trav->left->color == 'r')
				{
					//color swap
					trav->color = 'r';
					trav->left->color = 'b';
					trav->right->color = 'b';
					redCount = 1;

				}
				else if (trav->right->right && trav->right->right->color == 'r')
				{  // rotate right
					leftRotate(trav);
					trav->right->color = 'r';
					trav->left->color = 'r';
					trav->color = 'b';
					redCount = 0;
				}
				else {
					// right rotate, left rotate        // uncle is black                              
					rightRotate(trav->right);
					leftRotate(trav);
					trav->right->color = 'r';
					trav->left->color = 'r';
					trav->color = 'b';
					redCount = 0;

				}


			}
			else if (redCount == 1) // keeps track of the red
			{
				if (trav->color == 'b')
				{
					redCount = 0;
				}
				else {
					redCount = 2;
				}
			}
			else
			{
				if (trav->color == 'b')
				{
					redCount = 0;
				}
				else {
					redCount = 1;
				}


			}

		}

		/*if (redCount == 1 && trav->color == 'r')
		{
			redCount = 2;
			colorSwap(trav);
		}*/

	}


	void leftRotate(Node*& trav)
	{
		Node* temp = trav;
		trav = temp->right;
		temp->right = trav->left;
		trav->left = temp;
	}

	void rightRotate(Node*& trav)
	{
		Node* temp = trav;
		trav = temp->left;
		temp->left = trav->right;
		trav->right = temp;

	}


	bool searchForNode(Node*& trav, int value)
	{
		if (trav == NULL) return false;

		else if (trav->value == value) return true;
		else if (value < trav->value)
		{

			if (searchForNode(trav->left, value)) return true;
			else return false;

		}
		else {
			if (searchForNode(trav->right, value)) return true;
			else return false;

		}

	}

	void printInOrder(Node* currentNode)  // (Left Root Right)
	{
		if (currentNode == NULL) return;

		printInOrder(currentNode->left);
		cout << currentNode->value << " ";
		printInOrder(currentNode->right);

	}

	void clearTree(Node*& trav)
	{
		if (trav)
		{
			clearTree(trav->left);
			clearTree(trav->right);
			delete trav;
			trav = NULL;

		}
	}

	void printTree(Node* trav, int low, int high, int row)
	{

		if (trav)
		{
			int mid = (low + high) / 2;

			printTree(trav->left, low, mid, row + 1);
			printTree(trav->right, mid, high, row + 1);

			goTo(mid, row);
			cout << trav->value << "(" << trav->color << " )";

		}


	}

	void deleteNode(Node*& trav,int targetValue)
	{
		// find node,check if its a leaf node, if leaf node and red than just delete.
		if (trav->value == targetValue)
		{
			// not a leaf node
			if (trav->left)
			{
				Node* temp = trav->left;
				int newValue = temp->value;
				while (temp->right)
				{
					
					temp = temp->right;
					newValue = temp->value;
			
				}
				trav->value = newValue;
				deleteNode(trav->left, newValue);
				leftCases(trav);

			}
			else if (trav->right)
			{
				Node* temp = trav->right;
				int newValue = temp->value;
				while (temp->left)
				{

					temp = temp->left;
					newValue = temp->value;
	
				}
				trav->value = newValue;
				deleteNode(trav->right, newValue);
				rightCases(trav);
			}
			else {   // leaf nodes
				if (trav->color == 'b')
				{
					doubleBack = true;
				}
				
				delete trav;
				trav = nullptr;
				
			}
		}

		else {
			if (trav->value < targetValue)
			{
				deleteNode(trav->right, targetValue);
				rightCases(trav);
			}
			else {
				deleteNode(trav->left, targetValue);
				leftCases(trav);
			}
		}
	}

	void leftCases(Node*& trav) // class notes
	{
		if (doubleBack)
		{
			if (case2Left(trav))
			{
				adjust2Left(trav);
				if (case5Left(trav->left))
				{
					adjust5Left(trav->left);
					adjust6Left(trav->left);
				}
				else if(case4Left(trav->left))
				{
					adjust4Left(trav->left);
				}
			}
			else if (case3Left(trav))
			{
				adjust3Left(trav);

			}
			else if (case4Left(trav))
			{
				adjust4Left(trav);
			}
			else if (case5Left(trav))
			{
				adjust5Left(trav);
				adjust6Left(trav);
			}
			else if (case6Left(trav))
			{
				adjust6Left(trav);
			}
			
		

		}
	}
	void rightCases(Node*& trav)  //to right
	{
		if (doubleBack)
		{
			if (case2Right(trav))
			{
				adjust2Right(trav);
				if (case5Right(trav->right))
				{
					adjust5Right(trav->right);
					adjust6Right(trav->right);
				}
				else if (case4Right(trav->right))
				{
					adjust4Right(trav->right);
				}
			}
			else if (case3Right(trav))
			{
				adjust3Right(trav);

			}
			else if (case4Right(trav))
			{
				adjust4Right(trav);
			}
			else if (case5Right(trav))
			{
				adjust5Right(trav);
				adjust6Right(trav);
			}
			else if (case6Right(trav))
			{
				adjust6Right(trav);
			}
		}
	}

	void adjust2Left(Node*& trav)  // case2
	{
		leftRotate(trav);
		trav->color = 'b';
		trav->left->color = 'r';
	}
	void adjust3Left(Node*& trav)
	{
		trav->right->color = 'r';
	}
	void adjust4Left(Node*& trav)
	{
		trav->color = trav->right->color;
		trav->right->color = 'r';
		doubleBack = false;
	}
	void adjust5Left(Node*& trav)
	{
		rightRotate(trav->right);
		trav->right->color = 'b';
		trav->right->right->color = 'r';
	}
	void adjust6Left(Node*& trav)
	{
		leftRotate(trav);
		trav->right->color = 'b';
		trav->color = trav->left->color;
		trav->left->color = 'b';
		doubleBack = false;
	}

	void adjust2Right(Node*& trav)
	{
		rightRotate(trav);
		trav->color = 'b';
		trav->right->color = 'r';
	}
	void adjust3Right(Node*& trav)
	{
		trav->left->color = 'r';
	}
	void adjust4Right(Node*& trav)
	{
		trav->color = trav->left->color;
		trav->left->color = 'r';
		doubleBack = false;
	}
	void adjust5Right(Node*& trav)
	{
		leftRotate(trav->left);
		trav->left->color = 'b';
		trav->left->left->color = 'r';
	}
	void adjust6Right(Node*& trav)
	{
		rightRotate(trav);
		trav->left->color = 'b';
		trav->color = trav->right->color;
		trav->right->color = 'b';
		doubleBack = false;
	}

	bool case2Left(Node* trav)
	{
		return (trav->right && trav->right->color == 'r' && trav->right->left && trav->right->left->color == 'b' && trav->right->right && trav->right->right->color == 'b');
	}
	bool case3Left(Node* trav)
	{
		return (trav->color == 'b' && trav->right && trav->right->color == 'b' &&  (trav->right->left == NULL || trav->right->left->color == 'b' ) && (trav->right->right == NULL || trav->right->right->color == 'b'));
	}
	bool case4Left(Node* trav)
	{
		return (trav->color == 'r' && trav->right && trav->right->color == 'b' && (trav->right->left == NULL || trav->right->left->color == 'b') && (trav->right->right == NULL || trav->right->right->color == 'b'));
	}
	bool case5Left(Node* trav)
	{
		return (trav->right && trav->right->color == 'b' && trav->right->left && trav->right->left->color == 'r' && (trav->right->right == NULL || trav->right->right->color == 'b'));
	}
	bool case6Left(Node* trav)
	{
		return (trav->right && trav->right->color == 'b' && trav->right->right && trav->right->right->color == 'r' && trav->right->left);
	}
		 
	bool case2Right(Node* trav)
	{
		return (trav->left && trav->left->color == 'r' && trav->left->right && trav->left->right->color == 'b' && trav->left->left && trav->left->left->color == 'b');
	}
	bool case3Right(Node* trav)
	{
		return (trav->color == 'b' && trav->left && trav->left->color == 'b' && (trav->left->right == NULL || trav->left->right->color == 'b') && (trav->left->left || trav->left->left->color == 'b'));
	}
	bool case4Right(Node* trav)
	{
		return (trav->color == 'r' && trav->left && trav->left->color == 'b' && (trav->left->right == NULL || trav->left->right->color == 'b') && (trav->left->left == NULL || trav->left->left->color == 'b'));
	}
	bool case5Right(Node* trav)
	{
		return (trav->left && trav->left->color == 'b' && trav->left->right && trav->left->right->color == 'r' && (trav->left->left == NULL || trav->left->left->color == 'b'));
	}
	bool case6Right(Node* trav)
	{
		return (trav->left && trav->left->color == 'b' && trav->left->left && trav->left->left->color == 'r' && trav->left->right);
	}

public:
	
	void addNode(int value)
	{
		insertNode(value, root);
		root->color = 'b';
	}

	void printTree()
	{

		printTree(root, 0, 80, 1);

	}
	void printInOrder()
	{
		printInOrder(root);
	}

	void Search(int value)
	{
		bool answer;
		answer = searchForNode(root, value);
		if (answer)
		{
			cout << "Node Found!" << endl;
		}
		else {
			cout << "Node does not exist" << endl;
		}
	}
	void clear()
	{
		clearTree(root);
		root = NULL;
		cout << "Tree cleared";
	}

	void deleteTarget(int value)
	{
		if (searchForNode(root, value))
		{
			deleteNode(root, value);
			root->color = 'b';
			doubleBack = false;
		}
		else {
			cout << "Node does not exist";
		}
		
	}

	void goTo(int x, int y)   // Used to draw the tree 
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x; //Column
		pos.Y = y; //Row
		SetConsoleCursorPosition(hConsole, pos);
	}
};

void menu()
{
	cout << endl;
	cout << "1.)Add node: " << endl;
	cout << "2.)Search node: " << endl;
	cout << "3.)Clear: " << endl;
	cout << "4.)InOrder print: " << endl;
	cout << "5.)Display Tree: " << endl;
	cout << "6.)Delete node" << endl;
	cout << "7.)Press to exit: " << endl;

}
int main()
{
	RedBlack tree;

	menu();


	char s;
	int enter;

	cout << "Enter option: ";
	cin >> s;



	while (s != '7')
	{

		switch (s)
		{

		case '1':
			cout << "Enter a value: " << endl;
			cin >> enter;
			
			break;
		case '2':
			cout << "Search value" << endl;
			int search;
			cin >> search;
			tree.Search(search);
			break;
		case '3':
			tree.clear();
			break;
		case '4':
			tree.printInOrder();
			cout << endl;
			break;
		case '5':
			system("cls");
			tree.printTree();
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			system("pause");

			break;

		case '6':
			int num;
			cout << "Delete Node number: ";
			cin >> num;
			tree.deleteTarget(num);
			break;
		default:
			exit(0);
			break;
		}

		menu();
		cin >> s;
	}


	return 0;


}