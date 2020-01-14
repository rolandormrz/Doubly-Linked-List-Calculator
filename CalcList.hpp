#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

class CalcList : public CalcListInterface {
public:
    CalcList();
    ~CalcList();

    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();

    std::string toString(unsigned short precision) const;

private:

    // struct for doubly linked list
    struct dnode {
        double prevValue;       // holds value before operation
        double afterValue;      // holds value after operation
        double operandUsed;     // value used in operation
        FUNCTIONS operation;    // operation used
        dnode* prev = nullptr;
        dnode* next = nullptr;
    };

    double currentTotal;      
    dnode* head;
    dnode* trailer;
};

#endif /* CALCLIST_H */