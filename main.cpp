#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;

template<typename T>
struct Node{
	T data;
	Node<T> * sons[2];
	/*sons[0] left
	sons[1] rigth*/
	Node<T>(){
		sons[0] = NULL;
		sons[1] = NULL;
	} 
	Node<T>( T data_ ){
		data = data_;
		sons[0] = NULL;
		sons[1] = NULL;
	}
};


template<typename T>
class binTree{
public:
	Node<T> * head;
	binTree(){
		head = NULL;
	}

	bool find ( T data_, Node<T> ** & p ){
		for(p = &head; *p && data_ !=(*p)->data ; p = &(*p)->sons[data_ > (*p)->data]);
		return *p && (*p)->data == data_ ;
	} 

	bool insert( T data_ ){
		Node<T> ** p = &head;
		if ( find(data_,p) ){
			return false;
		}
		*p = new Node<T> (data_);
		return true;
	}

	Node<T> ** findYoungestSon(Node<T> ** & p){
		Node<T> ** tmp = p;
		tmp = &(*tmp)->sons[0];
		while(!!(*tmp)->sons[1]){
			tmp = &(*tmp)->sons[1];
		}
		return tmp;
	}

	bool remove(T data_){
		Node<T> ** p = &head;
		Node<T> * deleted;
		if ( !(find (data_,p) ) ){
			return false;
		}
		bool left, rigth;
		left = !!(*p)->sons[0];
		rigth = !!(*p)->sons[1];
		if ( left & rigth ){
			Node<T> ** tmp = findYoungestSon( p );
			(*p)->data = (*tmp)->data;
			p = tmp;
			left = !!(*p)->sons[0];
			rigth = !!(*p)->sons[1];
		}
		deleted = *p;
		*p = (*p)->sons[rigth>left];
		delete deleted;
		return true;
	}

	void _display (Node<T>** current, int ident) {
		if (*current) {
			_display( &(*current)->sons[0], ident+1 );
			for (int i=0; i<ident; i++) {
				cout << "    ";
			}
			cout << (*current)->data << endl;
			_display( &(*current)->sons[1], ident+1 );
		}
	}

	void display () {
		_display(&head, 0);
	}
	

	Node<T> * binTreeToSimpleList (Node<T> ** current) {
		if ( !(*current) )
			return *current;
		//Guarda el hijo derecho en un temporal.
		Node<T> * tmp = (*current)->sons[1];
		//Reorganiza los nodos empezando por el hijo izquiero izquierda.
		if( (*current)->sons[0] ){
			(*current)->sons[1] = (*current)->sons[0];
			(*current)->sons[0] = NULL;
			(*current) = binTreeToSimpleList ( &((*current)->sons[1]) );
		}
		//Una vez que termina de reorganizar todos los nodos que estan a la izquierda de la cabeza (head)
		//Empieza a reorganizar los hijos de la derecha de la cabeza (head) añadiendolos al hijo derecho
		//del último nodo de la rama izquierda.
		if( tmp ){
			(*current)->sons[1] = tmp;
			(*current) = binTreeToSimpleList ( &((*current)->sons[1]) );
		}
		return (*current);
	}
	//Al final todos los nodos hijos izquierdos serán NULL y la lista estará en los hijos derechos.

	Node<T> * binTreeToSimpleList (){
		Node<T>** p = &head;
		binTreeToSimpleList(p);
	}

	~binTree(){}
	
};


int main(){
	binTree<int> a;
	srand (time(NULL));
	for (int i = 0; i < 10; ++i){
		a.insert(rand() % 20 + 1);
		//a.insert(i);
	}
	cout<<a.remove(5);


	a.display();
	cout<<endl<<endl<<endl;
	Node<int> * newList = a.binTreeToSimpleList ();

	a.display();

	cout<<"hello world!"<<endl;
	return 0;
}