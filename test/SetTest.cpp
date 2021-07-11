#include <array>
#include <memory>
#include <iostream>
#include <cassert>
#include "tests.hpp"


void SetTest::testCreate() {
    CREATE_LOGGER
    CREATE_SET_ONE
    
    assert(set1 != nullptr);

    CLEAR_SET_ONE
    CLEAR_LOGGER
}

void SetTest::testGetDim() {
    CREATE_LOGGER
    CREATE_SET_ONE

    assert(set1->getDim() == 0);

    CLEAR_LOGGER
    CLEAR_SET_ONE
}
void SetTest::testGetSize() {
    CREATE_LOGGER
    CREATE_SET_ONE

    assert(set1->getSize() == 0);

    CLEAR_LOGGER
    CLEAR_SET_ONE
}
void SetTest::testGetCopy() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE
    CREATE_VEC_TWO

    RC err;
    IVector* tmp;
    
    err = set1->insert(vec1, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    err = set1->insert(vec2, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->getCopy(0, tmp);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, tmp, IVector::NORM::FIRST, TOLERANCE));
    delete tmp;
    
    err = set1->getCopy(1, tmp);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec2, tmp, IVector::NORM::FIRST, TOLERANCE));
    delete tmp;

    CLEAR_VEC_TWO
    CLEAR_VEC_ONE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}
void SetTest::testGetCoords() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE
    CREATE_VEC_TWO

    RC err;

    err = set1->insert(vec1, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    
    err = set1->getCoords(0, vec2);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, vec2, IVector::NORM::FIRST, TOLERANCE));

    CLEAR_VEC_TWO
    CLEAR_VEC_ONE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}

void SetTest::testInsert() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE
    CREATE_VEC_TWO
    CREATE_VEC_THREE

    RC err;

    err = set1->insert(vec1, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    assert(set1->getSize() == 1);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec2, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec2, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::VECTOR_ALREADY_EXIST);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec3, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::MISMATCHING_DIMENSIONS);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    CLEAR_VEC_ONE
    CLEAR_VEC_TWO
    CLEAR_VEC_THREE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}
void SetTest::testRemoveByIndex() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE
    CREATE_VEC_TWO

    RC err;

    err = set1->insert(vec1, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    err = set1->insert(vec2, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->remove(1);
    assert(err = RC::SUCCESS);
    assert(set1->getSize() == 1);

    err = set1->remove(1);
    assert(err = RC::INDEX_OUT_OF_BOUND);
    assert(set1->getSize() == 1);

    CLEAR_VEC_TWO
    CLEAR_VEC_ONE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}
void SetTest::testRemoveByPattern() {}


void SetTest::testClone() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE

    RC err;

    err = set1->insert(vec1, IVector::NORM::FIRST, TOLERANCE);
    assert(err == RC::SUCCESS);
    ISet* set2 = set1->clone();

    delete set2;

    CLEAR_VEC_ONE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}

void SetTest::testFindFirst() {}
void SetTest::testFindFirstAndCopy() {}
void SetTest::testFindFirstAndCopyCoords() {}

void SetTest::testMakeIntersection() {}
void SetTest::testMakeUnion() {}
void SetTest::testSub() {}
void SetTest::testSymSub() {}
void SetTest::testEquals() {}
void SetTest::testSubSet() {}

void SetTest::testAll() {
    std::cout << "Running all Set tests" << std::endl;

    testCreate();
    testGetDim();
    testGetSize();
    testGetCopy();
    testGetCoords();
    testInsert();
    testRemoveByIndex();
    testRemoveByPattern();
    testClone();
    testFindFirst();
    testFindFirstAndCopy();
    testFindFirstAndCopyCoords();
    testMakeIntersection();
    testMakeUnion();
    testSub();
    testSymSub();
    testEquals();
    testSubSet();


    std::cout << "Successfully ran all Set tests" << std::endl;
}