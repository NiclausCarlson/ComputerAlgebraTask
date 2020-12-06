//
// Created by Nik Carlson on 04.12.2020.
//

#ifndef COMPUTERALGEBRATASK_OPERATION_H
#define COMPUTERALGEBRATASK_OPERATION_H


template <typename T> class Operation {
public:
    virtual T compute() = 0;
    virtual ~Operation() = 0;
};


#endif //COMPUTERALGEBRATASK_OPERATION_H
