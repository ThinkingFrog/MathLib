#include "tests.hpp"
#include <cassert>
#include <iostream>

void CompactTest::testCreate() {
    CREATE_ALL

    assert(com1 != nullptr);

    CLEAR_ALL
}
void CompactTest::testClone() {
    CREATE_ALL
    ICompact *tmp = com1->clone();

    assert(tmp != nullptr);

    delete tmp;
    CLEAR_ALL
}

void CompactTest::testGetDim() {
    CREATE_ALL

    assert(com1->getDim() == vec1->getDim());

    CLEAR_ALL
}
void CompactTest::testGetGrid() {
    CREATE_ALL
    IMultiIndex *tmp = com1->getGrid();

    const size_t *tmp_data = tmp->getData();
    const size_t *index_data = index1->getData();
    for (size_t idx = 0; idx < com1->getDim(); ++idx)
        assert(tmp_data[idx] == index_data[idx]);

    delete tmp;
    CLEAR_ALL
}
void CompactTest::testGetLeftBoundary() {
    CREATE_ALL
    IVector *left = nullptr;

    RC err = com1->getLeftBoundary(left);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, left, DEFAULT_NORM, TOLERANCE));

    delete left;
    CLEAR_ALL
}
void CompactTest::testGetRightBoundary() {
    CREATE_ALL
    IVector *right = nullptr;

    RC err = com1->getRightBoundary(right);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec2, right, DEFAULT_NORM, TOLERANCE));

    delete right;
    CLEAR_ALL
}
void CompactTest::testGetVectorCoords() {
    CREATE_ALL
    double *empty_data = new double[com1->getDim()];
    IVector *tmp = IVector::createVector(com1->getDim(), empty_data);

    //    RC err = com1->getVectorCoords();

    delete[] empty_data;
    delete tmp;
    CLEAR_ALL
}
void CompactTest::testGetVectorCopy() {}

void CompactTest::testIsInside() {}

void CompactTest::testAll() {
    std::cout << "Running all Compact tests" << std::endl;

    testCreate();
    testClone();
    testGetDim();
    testGetGrid();
    testGetLeftBoundary();
    testGetRightBoundary();
    testGetVectorCoords();
    testGetVectorCopy();
    testIsInside();

    std::cout << "Successfully ran all Compact tests" << std::endl;
}