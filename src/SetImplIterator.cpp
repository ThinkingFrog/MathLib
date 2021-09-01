#include <cmath>
#include <map>
#include <vector>
#include "ISet.h"
#include "ISetControlBlock.h"
#include "SetImpl.h"

/*
* Create iterator associated with next/previous position
*
* @param [in] indexInc Quantity of steps forward
*/
ISet::IIterator* SetImpl::IteratorImpl::getNext(size_t indexInc) const { return nullptr; }
ISet::IIterator* SetImpl::IteratorImpl::getPrevious(size_t indexInc) const { return nullptr; }
ISet::IIterator* SetImpl::IteratorImpl::clone() const { return nullptr; }

RC SetImpl::IteratorImpl::setLogger(ILogger * const pLogger) { 
    if (pLogger == nullptr)
        return RC::NULLPTR_ERROR;
    
    logger = pLogger;
    return RC::SUCCESS;
}

/*
* Moves iterator forward/backward
*/
RC SetImpl::IteratorImpl::next(size_t indexInc)  { return RC::SUCCESS; }
RC SetImpl::IteratorImpl::previous(size_t indexInc)  { return RC::SUCCESS; }

bool SetImpl::IteratorImpl::isValid() const { return false; }

RC SetImpl::IteratorImpl::makeBegin() { return RC::SUCCESS; }
RC SetImpl::IteratorImpl::makeEnd() { return RC::SUCCESS; }

/*
* Getter of value (same semantic as ISet::getCopy)
*/
RC SetImpl::IteratorImpl::getVectorCopy(IVector *& val) const { return RC::SUCCESS; }
/*
* Getter of value (same semantic as ISet::getCoords)
*/
RC SetImpl::IteratorImpl::getVectorCoords(IVector * const& val) const { return RC::SUCCESS; }

SetImpl::IteratorImpl::~IteratorImpl()  = default;
ISet::IIterator::~IIterator()  = default;

size_t SetImpl::IteratorImpl::getIndex() const { return 0; }
SetImpl::IteratorImpl::IteratorImpl() {}

ISet::IIterator* SetImpl::getIterator(size_t index) const { return nullptr; }
ISet::IIterator* SetImpl::getBegin() const { return nullptr; }
ISet::IIterator* SetImpl::getEnd() const { return nullptr; }