/*
    Name: Avery Zeiler
    Student Number: 400305001
    MacID: zeilera
    Date: March 10, 2022
*/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;
class Term
{
    public:
        Term(int c=0, int e=0) : coef(c), exp(e) {}
        int coef;
        int exp;
};

typedef Term Elem;				// list element type Term
class DNode {					    // doubly linked list node
    private:
        Elem elem;					// node element value
        DNode* prev;				// previous node in list
        DNode* next;				// next node in list
        friend class DLinkedList;	// allow DLinkedList access
        friend class Polynomial;
};

class DLinkedList {				// doubly linked list
    friend class Polynomial;
    public:
        DLinkedList();				// constructor
        ~DLinkedList();				// destructor
        bool empty() const;				// is list empty?
        const Elem& front() const;			// get front element
        const Elem& back() const;			// get back element
        void addFront(const Elem& e);		// add to front of list
        void addBack(const Elem& e);		// add to back of list
        void removeFront();				// remove from front
        void removeBack();				// remove from back
        
        //getters
        DNode* getHead() {
            return header;
        }
        DNode* getTail() {
            return trailer;
        }
    private:					// local type definitions
        DNode* header;				// list sentinels
        DNode* trailer;
    protected:					// local utilities
        void add(DNode* v, const Elem& e);		// insert new node before v
        void remove(DNode* v);			// remove node v
};

DLinkedList::DLinkedList() {			// constructor
    header = new DNode;				// create sentinels
    trailer = new DNode;
    header->next = trailer;			// have them point to each other
    trailer->prev = header;
}

bool DLinkedList::empty() const		// is list empty?
    { return (header->next == trailer); }

const Elem& DLinkedList::front() const	// get front element
    { return header->next->elem; }

const Elem& DLinkedList::back() const		// get back element
    { return trailer->prev->elem; }

DLinkedList::~DLinkedList() {			// destructor
    while (!empty()) removeFront();		// remove all but sentinels
    delete header;				// remove the sentinels
    delete trailer;
}

void DLinkedList::remove(DNode* v) {		// remove node v
    DNode* u = v->prev;				// predecessor
    DNode* w = v->next;				// successor
    u->next = w;				// unlink v from list
    w->prev = u;
    delete v;
}

void DLinkedList::removeFront()		// remove from font
    { remove(header->next); }
  
void DLinkedList::removeBack()		// remove from back
    { remove(trailer->prev); }

void DLinkedList::add(DNode* v, const Elem& e) { // insert new node before v
    DNode* u = new DNode;  
    u->elem = e;		// create a new node for e
    u->next = v;				// link u in between v
    u->prev = v->prev;				// ...and v->prev
    v->prev->next = u;
    v->prev = u;
  }

void DLinkedList::addFront(const Elem& e)	// add to front of list
    { add(header->next, e); }
  
void DLinkedList::addBack(const Elem& e)	// add to back of list
    { add(trailer, e); }


class Polynomial {
    public:
        void insertTerm(int c, int e);
        friend istream& operator>> (istream& stream, Polynomial& other);
        friend ostream& operator<< (ostream& stream, Polynomial& other);
        Polynomial operator+ (const Polynomial& p1);
        int eval(int x);
    private:
        DLinkedList expression;
        string toString();
};

void Polynomial::insertTerm(int c, int e) {
    //SPECIAL CASES
    if (expression.empty() || e > expression.header->next->elem.exp) {
        //if expression is empty or e is highest exponent
        expression.addFront(Term(c, e));
        return;
    } else if (e <= expression.trailer->prev->elem.exp) {
        //if e <= last exponent in expression
        if (expression.trailer->prev->elem.exp == e) {
            //if last element should be replaced
            expression.removeBack();
        }
        expression.addBack(Term(c, e));
        return;
    }

    //allocate memory for temporary variable to traverse thru list
    DNode* temp = new DNode;
    temp->elem = expression.header->next->elem;
    temp->prev = expression.header;
    temp->next = expression.header->next->next;
    while (0 == 0) {
        if (e > temp->elem.exp) {
            //if new e is greater than next e
            expression.add(temp, Term(c, e));
            break;
        } else if (e == temp->elem.exp) {
            //if new e is equal to next e
            expression.add(temp, Term(c, e));
            expression.remove(temp);
            break;
        }
        //if these cases do not occur, traverse to next element
        temp = temp->next;
        //in the case that this fails, break the loop
        if (temp == expression.trailer) {
            cout << "Failed to insert element." << endl;
            break;
        }
    }
    //delete temp;
    return;
}

string Polynomial::toString() {
    string s = "";  //create initial string to append to
    //create temp node to traverse through list
    DNode* temp = new DNode;
    temp->elem = expression.header->next->elem;
    temp->prev = expression.header;
    temp->next = expression.header->next->next;
    //repeats until end of list is reached
    while (temp != expression.trailer) {
        if (temp->elem.coef != 0) {
            if (temp->elem.coef > 0) {
                //if coefficient is positive + not the first element
                if (temp->prev != expression.header) {
                    s += " + ";
                }
                if (temp->elem.coef > 1) {
                    s += to_string(temp->elem.coef);
                }
            } else {
                //if coefficient is negative
                s += " - ";
                if (temp->elem.coef < -1) {
                    s += to_string(abs(temp->elem.coef));
                }
            }
            //this part controls how exponent is appended
            if (temp->elem.exp > 1) {
                s += "x^";
                s += to_string(temp->elem.exp);
            } else if (temp->elem.exp == 1) {
                s += "x";
            }
        }
        temp = temp->next;      //traverse to next element of list
    }
    //delete temp;
    return s;
}

istream& operator>> (istream& stream, Polynomial& other) {
    int nodes, c_temp, e_temp;
    stream >> nodes;
    for (int i = 0; i < nodes; i++) {
        stream >> c_temp >> e_temp;
        other.insertTerm(c_temp, e_temp);
    }
    return stream;
}

ostream& operator<< (ostream& stream, Polynomial& other) {
    stream << other.toString();
    return stream;
}

Polynomial Polynomial::operator+ (const Polynomial& p1) {
    if (p1.expression.empty()) {
        return *this;      //returns p2 if p1 is empty
    }
    if (expression.empty()) {
        return p1;      //returns p1 if p2 is empty
    }
    //create 2 pointers to go through p1 and p2
    DNode* tmp1 = new DNode;
    DNode* tmp2 = new DNode;
    //create a new Polynomial object to store result
    Polynomial *result = new Polynomial;
    //initialize pointer 1
    tmp1->elem = p1.expression.header->next->elem;       //element of tmp1 = first elem
    tmp1->next = p1.expression.header->next->next;       //next of tmp1 = 3rd section of DLL
    //initialize pointer 2
    tmp2->elem = expression.header->next->elem;       //element of tmp2 = first elem
    tmp2->next = expression.header->next->next;       //next of tmp2 = 3rd section of DLL
    while (tmp1 != p1.expression.trailer || tmp2 != expression.trailer) {
    //will run until both pointers reach the end of the polynomials
        if (tmp1 == p1.expression.trailer) {
            //if end of p1 has been reached
            while (tmp2 != expression.trailer) {
                //add all remaining values in p2 to result
                result->expression.addBack(tmp2->elem);
                tmp2 = tmp2->next;
            }
        } else if (tmp2 == expression.trailer) {
            //if end of p2 has been reached
            while (tmp1 != p1.expression.trailer) {
                //add all remaining values in p1 to result
                result->expression.addBack(tmp1->elem);
                tmp1 = tmp1->next;
            }
        } else if (tmp1->elem.exp == tmp2->elem.exp) {
            //if exponents are equal, add elements + add to result
            result->expression.addBack(Term(tmp1->elem.coef + tmp2->elem.coef, tmp1->elem.exp));
            //traverse to next values
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        } else if (tmp1->elem.exp > tmp2->elem.exp) {
            //if p1 exponent is greater, add p1 element to result
            result->expression.addBack(tmp1->elem);
            //traverse to next value in p1
            tmp1 = tmp1->next;
        } else if (tmp1->elem.exp < tmp2->elem.exp) {
            //if p2 exponent is greater, add p2 element to result
            result->expression.addBack(tmp2->elem);
            //traverse to next value in p2
            tmp2 = tmp2->next;
        }
    }
    //delete tmp1;
    //delete tmp2;
    return *result;
}

int Polynomial::eval(int x) {
    if (expression.header->next == expression.trailer) {
        //if polynomial is empty
        return 0;
    }
    //create temp to traverse through list
    DNode* temp = new DNode;
    temp->elem = expression.header->next->elem;
    temp->prev = expression.header;
    temp->next = expression.header->next->next;
    //create sum variable
    int sum = 0;
    //repeats until end of list is reached
    while (temp != expression.trailer) {
        sum += temp->elem.coef*pow(x, temp->elem.exp);      //add Ci*X^Ei to sum
        temp = temp->next;      //traverse to next element of list
    }
    delete temp;
    return sum;
}

int main() {
    //test code here
}