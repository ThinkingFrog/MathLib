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
    CREATE_ALL

    RC err;
    IVector* tmp;
    
    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->getCopy(0, tmp);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, tmp, DEFAULT_NORM, TOLERANCE));
    delete tmp;
    
    err = set1->getCopy(1, tmp);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec2, tmp, DEFAULT_NORM, TOLERANCE));
    delete tmp;

    CLEAR_ALL
}
void SetTest::testGetCoords() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    
    err = set1->getCoords(0, vec2);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, vec2, DEFAULT_NORM, TOLERANCE));

    CLEAR_ALL
}

void SetTest::testInsert() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    assert(set1->getSize() == 1);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::VECTOR_ALREADY_EXIST);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    err = set1->insert(vec3, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::MISMATCHING_DIMENSIONS);
    assert(set1->getSize() == 2);
    assert(set1->getDim() == vec1->getDim());

    CLEAR_ALL
}
void SetTest::testRemoveByIndex() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->remove(1);
    assert(err = RC::SUCCESS);
    assert(set1->getSize() == 1);

    err = set1->remove(1);
    assert(err = RC::INDEX_OUT_OF_BOUND);
    assert(set1->getSize() == 1);

    CLEAR_ALL
}
void SetTest::testRemoveByPattern() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->remove(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err = RC::SUCCESS);
    assert(set1->getSize() == 1);

    err = set1->remove(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err = RC::SUCCESS);
    assert(set1->getSize() == 0);

    err = set1->remove(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err = RC::SOURCE_SET_EMPTY);

    CLEAR_ALL
}

void SetTest::testClone() {
    CREATE_LOGGER
    CREATE_SET_ONE
    CREATE_VEC_ONE

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);
    ISet* set2 = set1->clone();

    delete set2;

    CLEAR_VEC_ONE
    CLEAR_SET_ONE
    CLEAR_LOGGER
}

void SetTest::testFindFirst() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->findFirst(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->findFirst(nullptr, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::NULLPTR_ERROR);

    err = set1->findFirst(vec3, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::MISMATCHING_DIMENSIONS);

    err = set1->remove(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->findFirst(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::VECTOR_NOT_FOUND);

    CLEAR_ALL
}
void SetTest::testFindFirstAndCopy() {
    CREATE_ALL

    IVector* test;
    RC err;

    err = set1->insert(vec1, DEFAULT_NORM, TOLERANCE);
    assert(err = RC::SUCCESS);
    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->findFirstAndCopy(vec2, DEFAULT_NORM, TOLERANCE, test);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(test, vec2, DEFAULT_NORM, TOLERANCE));

    delete test;
    CLEAR_ALL
}
void SetTest::testFindFirstAndCopyCoords() {
    CREATE_ALL

    RC err;

    err = set1->insert(vec2, DEFAULT_NORM, TOLERANCE);
    assert(err == RC::SUCCESS);

    err = set1->findFirstAndCopyCoords(vec2, DEFAULT_NORM, TOLERANCE, vec1);
    assert(err == RC::SUCCESS);
    assert(IVector::equals(vec1, vec2, DEFAULT_NORM, TOLERANCE));

    CLEAR_ALL
}

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