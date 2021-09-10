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

    assert(com1->getDim() == left_bound->getDim());

    CLEAR_ALL
}
void CompactTest::testGetGrid() {
    CREATE_ALL
    IMultiIndex *tmp = com1->getGrid();

    const size_t *tmp_data = tmp->getData();
    const size_t *index_data = grid->getData();
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
    assert(IVector::equals(left_bound, left, DEFAULT_NORM, TOLERANCE));

    delete left;
    CLEAR_ALL
}
void CompactTest::testGetRightBoundary() {
    CREATE_ALL
    IVector *right = nullptr;

    RC err = com1->getRightBoundary(right);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(right_bound, right, DEFAULT_NORM, TOLERANCE));

    delete right;
    CLEAR_ALL
}
void CompactTest::testGetVectorCoords() {
    CREATE_ALL
    double *empty_data = new double[com1->getDim()];
    IVector *tmp = IVector::createVector(com1->getDim(), empty_data);
    std::array<size_t, 2> index_data({3, 3});
    IMultiIndex *test_idx = IMultiIndex::createMultiIndex(index_data.size(), index_data.data());

    std::array<double, 2> expected_vec_data({3, 3});
    RC err = com1->getVectorCoords(test_idx, tmp);
    for (size_t idx = 0; idx < expected_vec_data.size(); ++idx)
        assert(tmp->getData()[idx] == expected_vec_data[idx]);

    delete[] empty_data;
    delete tmp;
    delete test_idx;
    CLEAR_ALL
}
void CompactTest::testGetVectorCopy() {
    CREATE_ALL
    IVector *tmp;
    std::array<size_t, 2> index_data({3, 3});
    IMultiIndex *test_idx = IMultiIndex::createMultiIndex(index_data.size(), index_data.data());

    std::array<double, 2> expected_vec_data({3, 3});
    RC err = com1->getVectorCopy(test_idx, tmp);
    for (size_t idx = 0; idx < expected_vec_data.size(); ++idx)
        assert(tmp->getData()[idx] == expected_vec_data[idx]);

    delete tmp;
    delete test_idx;
    CLEAR_ALL
}

void CompactTest::testIsInside() {
    CREATE_COM_ONE
    std::array<double, 2> tmp_vec_data({2.5, 4.3});
    IVector *tmp = IVector::createVector(tmp_vec_data.size(), tmp_vec_data.data());

    assert(com1->isInside(tmp));

    delete tmp;
    CLEAR_COM_ONE
}

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