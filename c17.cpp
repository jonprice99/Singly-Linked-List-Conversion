/* Name: Jonathan Price
   Date: 11/15/2019
   Course: CIT-245-Z02B
   
   The purpose of this file is to take the code for a singly linked list from
   the list of assignments, then change it into a working doubly linked list. */


//Set up libraries with console input and output facilities
#include <iostream>
#include <string>
using namespace std;

//Define a node for storage and linking
class node 
{
	public:
		string name;
		node *next;
		node *prev; // to be implemented by student
};

/*Create the linkedList class based on assignment list code with a call to a method
to print the list in reverse */
class linkedList 
{
	public:
		linkedList() :top(NULL) {}
		bool empty() { return top == NULL; }
		node *getTop() { return top; }
		void setTop(node *n) { top = n; }
		void add(string);
		int menu();
		void remove(string);
		~linkedList();
		void reversePrint(); // to be implemented by student
		friend ostream& operator << (ostream&, const linkedList&); // default output is in-order print.
	private:
		node *top;
		node *end; // to be used for reverse print and implemented by students
};

//Create method to print the list in reverse order
void linkedList::reversePrint()
{
	//Use the end node created in linkedList to get the first name from original list
	end = getTop();

	//Go through each entry of list
	while (end->next != NULL)
	{
		end = end->next;
	}

	//Print list in reverse order
	while (end != NULL)
	{
		cout << end->name << endl;
		end = end->prev;
	}



}

//Create the main program
int main() 
{
	linkedList l;
	cout << l.empty() << endl;
	int option = 0;
	string s;
	bool go = true;
	while (go) 
	{
		//Display the program's menu
		option = l.menu();
		switch (option) 
		{
			case 1: cout << "enter a name: "; cin >> s; l.add(s); break;
			case 2: cout << "enter name to be deleted: "; cin >> s; l.remove(s); break;
			case 3: cout << l; break;
			case 4: l.reversePrint(); cout << endl; break;
			case 5: cout << "exiting" << endl; go = false; break;
		}
	}
	// l goes out of scope and calls ~linkedList()
}

//Create method to delete names from the list
// can not call this method "delete" - "delete" is a reserved keyword.
void linkedList::remove(string s) 
{
	bool found = false;
	node *curr = getTop(), *prev = NULL;
	while (curr != NULL) 
	{

		// match found, delete
		if (curr->name == s) 
		{
			found = true;

			// found at top
			if (prev == NULL) 
			{
				node *temp = getTop();
				setTop(curr->next);

				delete(temp);
				//set head prev to null
				temp = getTop();
				if (temp != NULL)
				{
					temp->prev = NULL;
				}
			}
			// found in list - not top
			else 
			{

				prev->next = curr->next;
				if (curr->next != NULL)
				{
					(curr->next)->prev = prev;
				}
				delete(curr);
			}
		}

		// not found, advance pointers
		if (!found) 
		{
			prev = curr;
			curr = curr->next;
		}

		// found, exit loop
		else curr = NULL;
	}
	
	if (found)
	{
		cout << "Deleted " << s << endl;
	}
	else
	{
		cout << s << " Not Found " << endl;
	}
}

//Create method to add items to list
void linkedList::add(string s) 
{
	node *n = new node();
	n->name = s;
	n->next = NULL;
	n->prev = NULL;

	// take care of empty list case
	if (empty()) 
	{
		top = n;
	}
	// take care of node belongs at beginning case
	else if (getTop()->name > s) 
	{
		node *p = getTop();
		n->next = p;
		p->prev = n;
		setTop(n);
	}
	// take care of inorder and end insert
	else 
	{

		// insert in order case
		node *curr = getTop(), *prev = curr;
		while (curr != NULL) 
		{
			if (curr->name > s)break;
			prev = curr;
			curr = curr->next;
		}
		// search found insert point
		if (curr != NULL) 
		{ 
			n->next = curr;
			prev->next = n;
			n->prev = prev;
			curr->prev = n;
		}

		// take care of end of list insertion
		else if (curr == NULL) 
		{
			// search did not find insert point
			prev->next = n;
			n->prev = prev;
		}
	}
}

//Overload the << operator
ostream& operator << (ostream& os, const linkedList& ll) 
{
	//linkedList x = ll; // put this in and the code blows up - why?
	node *n = ll.top;
	if (n == NULL)
	{
		cout << "List is empty." << endl;
	}
	else
	{
		while (n != NULL)
		{
			os << n->name << endl;
			n = n->next;
		}
	}
	return os;
}

// return memory to heap
linkedList::~linkedList() 
{
	cout << "~linkedList called." << endl;
	node *curr = getTop(), *del;
	while (curr != NULL) {
		del = curr;
		curr = curr->next;
		delete(del);
	}
	
	//End the program
	system("PAUSE");
}

//Create the menu method
int linkedList::menu() 
{
	int choice = 0;
	while (choice < 1 || choice > 5) 
	{
		cout << "\nEnter your choice" << endl;
		cout << " 1. Add a name." << endl;
		cout << " 2. Delete a name." << endl;
		cout << " 3. Show list." << endl;
		cout << " 4. Show reverse list. " << endl; // to be implemented by students
		cout << " 5. EXIT " << endl;
		cin >> choice;
	}
	return choice;
}
