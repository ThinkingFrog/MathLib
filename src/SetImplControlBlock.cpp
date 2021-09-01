#include <cstddef>
#include "IVector.h"
#include "ISetControlBlock.h"
#include "ISet.h"
#include "SetImpl.h"


RC SetImplControlBlock::getNext(IVector *const &vec, size_t &index, size_t indexInc) const {
    return set->getByUniqueIndex(vec, index, indexInc);
}
RC SetImplControlBlock::getPrevious(IVector *const &vec, size_t &index, size_t indexInc) const {
    return set->getByUniqueIndex(vec, index, -indexInc);
}

RC SetImplControlBlock::getBegin(IVector *const &vec, size_t &index) const {
    return set->getFirstByUniqueIndex(vec, index);
}
RC SetImplControlBlock::getEnd(IVector *const &vec, size_t &index) const {
    return set->getLastByUniqueIndex(vec, index);
}
SetImplControlBlock* SetImplControlBlock::createControlBlock(SetImpl* const& set) {
    return new (std::nothrow) SetImplControlBlock(set);
}

SetImplControlBlock::SetImplControlBlock(SetImpl* const& set) : set(set) {};

ISetControlBlock::~ISetControlBlock() = default;
