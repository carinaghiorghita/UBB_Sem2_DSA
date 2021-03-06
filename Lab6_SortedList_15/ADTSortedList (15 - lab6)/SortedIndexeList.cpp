#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	this->R = r;
	this->root = NULL;
	this->sizeBST = 0;
}

int SortedIndexedList::size() const {
	if (root == NULL) return 0;
	return this->sizeBST;
}

bool SortedIndexedList::isEmpty() const {
	if (this->sizeBST ==0) return true;
	return false;
}

TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= this->sizeBST)
	{
		exception myex;
		throw(myex);
	}
	node* current=this->root;
	int position=0;
	while (current != NULL)
	{
		if (i == position + current->nrLeft)return current->info;
		if (i < position + current->nrLeft)
		{
			current = current->left;
		}
		else
		{
			position = position + current->nrLeft + 1;
			current = current->right;
		}
	}
}


/*
TComp SortedIndexedList::remove(int i) {
	
	if (i < 0 || i >= this->size())
	{
		exception myex;
		throw(myex);
	}
	if (this->size() == 1)
	{
		int info = root->info;
		root=NULL;
		return info;
	}
	node *current,*prev;
	char dir;
	int position = 0;
	current = this->root;
	prev = this->root;
	while (current != NULL)
	{
		if (i == position + current->nrLeft)
		{
			if (current->left == NULL && current->right == NULL)
			{
				if (dir == 'L')prev->left = NULL;
				else prev->right = NULL;
				return current->info;
			}
			else if (current->left && current->right==NULL)
			{
				if (dir == 'L')prev->left = current->left;
				else prev->right = current->left;
				return current->info;

			}
			else if (current->left == NULL && current->right)
			{
				if (dir == 'L')prev->left = current->right;
				else prev->right = current->right;
				return current->info;

			}
			else
			{
				if (current->left)
				{
					node* maximum = current->left,*prevmax=current;
					while (maximum->right)
					{
						prevmax = maximum;
						maximum = maximum->right;
					}
					//if (dir == 'L')prev->left = maximum;
					//else prev->right = maximum;
					TComp info = current->info;
					current=maximum;
					if (prevmax == current)prevmax->left = NULL;
					else prevmax->right = NULL;
					maximum = NULL;
					//delete[] maximum;
					return info;
				}
				
			}
		}
		if (i < position + current->nrLeft)
		{
			current->nrLeft--;
			current = current->left;
			dir = 'L';
		}
		else
		{
			position = position + current->nrLeft + 1;
			//current->nrRight--;
			current = current->right;
			dir = 'R';
		}
	}

}



TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= this->size())
	{
		exception myex;
		throw(myex);
	}
	node* current;
	char dir;
	int position = 0;
	current = this->root;
	while (current != NULL)
	{
		if (i == position + current->nrLeft)
		{
			if (current->left == NULL && current->right == NULL)
			{
				TComp info = current->info;
				if (current == root)root = NULL;
				//delete[] current;
				current = NULL;
				return info;
			}
			else if (current->left && current->right == NULL)
			{
				TComp info = current->info;
				node* temp = current;
				if (current == root)root = root->left;
				current = current->left;
				//delete[] temp;
				temp = NULL;
				return info;
			}
			else if (current->left == NULL && current->right)
			{
				TComp info = current->info;
				node* temp=current;
				if (current == root)root = root->right;
				current = current->right;
				//delete[] temp;
				temp = NULL;
				return info;
			}
			else
			{
				
				TComp info = current->info;
				node* minimum = current->right;
				while (minimum->left)
				{
					minimum = minimum->left;
				}
				//if (dir == 'L')prev->left = maximum;
				//else prev->right = maximum;
				current->info = minimum->info;
				current->nrRight = current->nrLeft - 1;
				current = minimum;
				//delete[] minimum;
				minimum = NULL;
				return info;
				
			}
		}
		if (i < position + current->nrLeft)
		{
			current->nrLeft--;
			current = current->left;
		}
		else
		{
			position = position + current->nrLeft + 1;
			current->nrRight--;
			current = current->right;
		}
	}


}
*/

TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= this->sizeBST)
	{
		exception myex;
		throw(myex);
	}
	node* prev = NULL;
	node* current = this->root;
	int position = 0;
	while (current)
	{
		if (i == position + current->nrLeft) break;
		if (i < position + current->nrLeft)
		{
			prev = current;
			current = current->left;
		}
		else
		{
			prev = current;
			position = position + current->nrLeft + 1;
			current = current->right;

		}
	}
	int deleted = current->info; 
	if (current->left == NULL && current->right == NULL)
	{
		decrease(i);
		if (prev == NULL)
		{
			this->root == NULL;
		}
		else
		{
			if (this->R(current->info, prev->info)) prev->left = NULL;
			else prev->right = NULL;
			delete[] current;
		}
		this->sizeBST--;
	}
	else
	{
		if (current->left == NULL || current->right == NULL)
		{
			decrease(i);

			node* descendant;
			if (current->left == NULL)
				descendant = current->right;
			else
				descendant = current->left;

			if (prev == NULL)
			{
				//root
				this->root = descendant;
			}
			else
			{
				//not root
				if (this->R(current->info, prev->info))
				{
					//on left
					prev->left = descendant;
				}
				else
				{
					//on right
					prev->right = descendant;
				}
				delete[] current;

			}
			this->sizeBST--;
		}
		else
		{
			TComp ssuccessor = this->successor(current->info);
			int index = this->search(ssuccessor);

			this->remove(index);

			

			current->info = ssuccessor;
		}
	}
	return deleted;
}

TComp SortedIndexedList::parent(TComp e)
{
	if (this->root->info == e)	
		return -1;
	node* current = this->root;

	while (current && current->left->info != e && current->right->info != e)
	{
		if (!this->R(current->info, e))
			current = current->left;
		else
			current = current->right;
	}

	return current->info;
	
}

void SortedIndexedList::decrease(int i) const
{
	if (i >= this->sizeBST || i < 0)
		throw(exception());

	node* current = this->root;
	int position = 0;
	while (current)
	{
		if (i == position + current->nrLeft)
			return;
		if (i < position + current->nrLeft)
		{
			//left
			current->nrLeft--;
			current = current->left;
		}
		else
		{
			//right
			position = position + current->nrLeft + 1;
			current = current->right;
		}
	}

}

int SortedIndexedList::getRange() const
{
	if (this->sizeBST == 0) return -1;
	TComp min, max;
	node* current=this->root;
	while (current->left) current = current->left;
	min = current->info;
	current = this->root;
	while (current->right) current = current->right;
	max = current->info;
	return max - min;
}

TComp SortedIndexedList::successor(TComp e)
{
	node* current = this->root;
	while (current->info!=e)
	{
		
		if (this->R(e, current->info)) current = current->left;
		else current = current->right;
		
	}
	if (current->right)
	{
		current = current->right;
		while (current->left)
			current = current->left;
		return current->info;
	}
	else
	{
		int p = this->parent(current->info);
		node* parent = this->root;

		while (parent->info != p)
		{

			if (this->R(p, current->info)) current = current->left;
			else current = current->right;

		}

		while (parent && parent->left != current)
		{
			current = parent;
			int p = this->parent(current->info);
			node* parent = this->root;

			while (parent->info != p)
			{

				if (this->R(p, current->info)) current = current->left;
				else current = current->right;

			}
		}
		return p;
	}
}


int SortedIndexedList::search(TComp e) const {
	node* current = this->root;
	int position = 0;
	while (current != NULL)
	{
		//return position
		if (current->info == e)return position+current->nrLeft;
		if (this->R(e,current->info)) current = current->left;
		else
		{
			position = position+current->nrLeft+1;
			current = current->right;
		}
	}
	return -1;
}

void SortedIndexedList::add(TComp e) {
	node* newNode = new node;
	newNode->info = e;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->nrLeft = 0;
	//newNode->nrRight = 0;
	if (root == NULL)root = newNode;
	else
	{
		node* current = this->root;
		while (current)
		{
			if (this->R(e,current->info))
			{
				current->nrLeft++;
				if (current->left == NULL)
				{
					
					current->left = newNode;
					current = NULL;
				}
				else current = current->left;
			}
			else
			{
				//current->nrRight++;
				if (current->right == NULL)
				{
					current->right = newNode;
					current = NULL;
				}
				else current = current->right;
			}
		}
	}
	this->sizeBST++;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	while (!this->isEmpty())this->remove(0);
}
