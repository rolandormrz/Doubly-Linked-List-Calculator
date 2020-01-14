#include "CalcList.hpp"

CalcList::CalcList() {

   dnode* x = new dnode;                // create node that holds default value zero

   // create sentinel nodes
   head = new dnode;
   trailer = new dnode;
   
   // set defaults
   x->prevValue = 0;
   x->afterValue = 0;
   x->operandUsed = 0;
   x->operation = ADDITION;
   
   // connect head and trailer to default node
   x->prev = head;
   x->next = trailer;
   head->next = x;
   trailer->prev = x;
   
   // initialize total to zero
   currentTotal = 0;
   }

CalcList::~CalcList() {
  
    dnode* current = head;              // points to current node starting at head node
    dnode* temp;                        // used to hold current->next before deleting current

    // loops through and deletes all nodes except for trailer
    while (current != trailer) {

       temp = current->next;
       delete current;
       current = temp;
    }
    
    delete trailer;
}

// returns the current total
double CalcList::total() const {

    return currentTotal;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) {

    dnode* x = new dnode;
    dnode* lastNode = nullptr;          // points to node before trailer

    x->prevValue = currentTotal;        // grab previous value (store in new node)
    x->operandUsed = operand;           // grab operand (store in new node)

    // determine what operation must be done and perform it
    if (func == ADDITION) {

        currentTotal += operand;
        x->operation = ADDITION;
        }
    else if (func == SUBTRACTION) {

        currentTotal -= operand;
        x->operation = SUBTRACTION;
        }
    else if (func == MULTIPLICATION) {

        currentTotal *= operand;
        x->operation = MULTIPLICATION;
        }
    else if (func == DIVISION) {

        if (operand == 0) {

            delete x;
            throw std::invalid_argument("cannot divide by zero");
            return;
        }
        else {

            currentTotal /= operand;
            x->operation = DIVISION;
        }
    }
        
    x->afterValue = currentTotal;       // grab value after operation (store in new node)

    // find last node
    lastNode = trailer->prev;

    // link previous last node and trailer to the new operation node
    lastNode->next = x;
    x->prev = lastNode;
    x->next = trailer;
    trailer->prev = x;
}

void CalcList::removeLastOperation() {

    dnode* noOperations = head;
    dnode* prev = trailer->prev->prev;     // points to the node before the one we want to delete
    dnode* current = prev->next;           // points to node that will be deleted

    // does nothing if no operations have been done
    if (noOperations->next->next == trailer) {

        throw std::invalid_argument("no operations to remove");
        return;
    }

    currentTotal = prev->afterValue;       // removes last operation

    // unlink node and delete it
    prev->next = trailer;
    trailer->prev = prev;
    delete current;
}

std::string CalcList::toString(unsigned short precision) const {

    int num = 0;                            // number of nodes (doesn't count head, trailer or default node)

    // count number of nodes
    dnode* numNodes = head->next;
    while (numNodes->next != trailer) {

        numNodes = numNodes->next;
        num++;
    }

    // declare stringstream variable and set the number of decimal points
    std::stringstream s;
    s.precision(precision);
   
    dnode* ptr = trailer->prev;             // points to node before trailer

    // prints values in nodes starting at the last node to the buffer
    while (ptr->prev != head) {

        if (ptr->operation == ADDITION) {
            s << num << std::fixed << ": " << ptr->prevValue << "+" << ptr->operandUsed << "=" << ptr->afterValue << std::endl;
        }
        else if (ptr->operation == SUBTRACTION) {
            s << num << std::fixed << ": " << ptr->prevValue << "-" << ptr->operandUsed << "=" << ptr->afterValue << std::endl;
        }
        else if (ptr->operation == MULTIPLICATION) {
            s << num << std::fixed << ": " << ptr->prevValue << "*" << ptr->operandUsed << "=" << ptr->afterValue << std::endl;
        }
        else if (ptr->operation == DIVISION) {
            s << num << std::fixed << ": " << ptr->prevValue << "/" << ptr->operandUsed << "=" << ptr->afterValue << std::endl;
        }

        num--;
        ptr = ptr->prev;
    }

    return s.str();                         // returns string
} 
