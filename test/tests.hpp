#pragma once
#include "ICompact.h"
#include "ILogger.h"
#include "IMultiIndex.h"
#include "ISet.h"
#include "IVector.h"

#define TOLERANCE 1e-6
#define DEFAULT_NORM IVector::NORM::SECOND

#define CREATE_LOGGER                                                                                                  \
    ILogger *logger = ILogger::createLogger();                                                                         \
    IVector::setLogger(logger);                                                                                        \
    ISet::setLogger(logger);                                                                                           \
    IMultiIndex::setLogger(logger);                                                                                    \
    ICompact::setLogger(logger);
#define CREATE_VEC_ONE                                                                                                 \
    std::array<double, 4> data1({1, 5.5, 6, 8.5});                                                                     \
    IVector *vec1 = IVector::createVector(data1.size(), data1.data());
#define CREATE_VEC_TWO                                                                                                 \
    std::array<double, 4> data2({5, 3, 9, 7});                                                                         \
    IVector *vec2 = IVector::createVector(data2.size(), data2.data());
#define CREATE_VEC_THREE                                                                                               \
    std::array<double, 3> data3({1, 10, 100});                                                                         \
    IVector *vec3 = IVector::createVector(data3.size(), data3.data());
#define CREATE_VEC_FOUR                                                                                                \
    std::array<double, 4> data4({67, 45, 10, 2});                                                                      \
    IVector *vec4 = IVector::createVector(data4.size(), data4.data());
#define CREATE_SET_ONE ISet *set1 = ISet::createSet();
#define CREATE_SET_TWO ISet *set2 = ISet::createSet();
#define CREATE_SET_THREE ISet *set3 = ISet::createSet();
#define CREATE_INDEX_ONE                                                                                               \
    std::array<size_t, 4> idata1({34, 17, 42, 2});                                                                     \
    IMultiIndex *index1 = IMultiIndex::createMultiIndex(idata1.size(), idata1.data());
#define CREATE_INDEX_TWO                                                                                               \
    std::array<size_t, 4> idata2({12, 76, 44, 89});                                                                    \
    IMultiIndex *index2 = IMultiIndex::createMultiIndex(idata2.size(), idata2.data());
#define CREATE_COM_ONE ICompact *com1 = ICompact::createCompact(vec1, vec2, index1);
#define CREATE_ALL                                                                                                     \
    CREATE_LOGGER CREATE_VEC_ONE CREATE_VEC_TWO CREATE_VEC_THREE CREATE_SET_ONE CREATE_SET_TWO CREATE_SET_THREE        \
        CREATE_VEC_FOUR CREATE_INDEX_ONE CREATE_INDEX_TWO CREATE_COM_ONE

#define CLEAR_LOGGER delete logger;
#define CLEAR_VEC_ONE delete vec1;
#define CLEAR_VEC_TWO delete vec2;
#define CLEAR_VEC_THREE delete vec3;
#define CLEAR_VEC_FOUR delete vec4;
#define CLEAR_SET_ONE delete set1;
#define CLEAR_SET_TWO delete set2;
#define CLEAR_SET_THREE delete set3;
#define CLEAR_INDEX_ONE delete index1;
#define CLEAR_INDEX_TWO delete index2;
#define CLEAR_COM_ONE delete com1;
#define CLEAR_ALL                                                                                                      \
    CLEAR_LOGGER CLEAR_VEC_ONE CLEAR_VEC_TWO CLEAR_VEC_THREE CLEAR_SET_ONE CLEAR_SET_TWO CLEAR_SET_THREE               \
        CLEAR_VEC_FOUR CLEAR_INDEX_ONE CLEAR_INDEX_TWO CLEAR_COM_ONE

namespace VecTest {
void testCreate();

void testCopy();
void testMove();

void testClone();
void testGetData();
void testSetData();

void testGetCord();
void testSetCord();
void testScale();
void testGetDim();

void testInc();
void testDec();

void testAdd();
void testSub();

void testDot();
void testEquals();

void testFirstNorm();
void testSecondNorm();
void testChebyshevNorm();

void testApplyFunc();
void testForeach();

void testAll();
}; // namespace VecTest

namespace SetTest {
void testCreate();

void testGetDim();
void testGetSize();
void testGetCopy();
void testGetCoords();

void testInsert();
void testRemoveByIndex();
void testRemoveByPattern();

void testClone();

void testFindFirst();
void testFindFirstAndCopy();
void testFindFirstAndCopyCoords();

void testMakeIntersection();
void testMakeUnion();
void testSub();
void testSymSub();
void testEquals();
void testSubSet();

void testAll();
}; // namespace SetTest

namespace MultiIndexTest {
void testCreate();
void testClone();

void testGetDim();
void testGetAxisIndex();
void testGetData();

void testSetData();
void testSetAxisIndex();
void testIncAxisIndex();

void testAll();
}; // namespace MultiIndexTest

namespace CompactTest {
void testCreate();
void testClone();

void testGetDim();
void testGetGrid();
void testGetLeftBoundary();
void testGetRightBoundary();

void testGetVectorCoords();
void testGetVectorCopy();
void testIsInside();

void testAll();
}; // namespace CompactTest