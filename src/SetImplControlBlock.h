#pragma once
#include "ISetControlBlock.h"

class SetImpl;

class SetImplControlBlock : public ISetControlBlock {
public:
    RC getNext(IVector *const &vec, size_t &index, size_t indexInc = 1) const;
    RC getPrevious(IVector *const &vec, size_t &index, size_t indexInc = 1) const;
    
    RC getBegin(IVector *const &vec, size_t &index) const;
    RC getEnd(IVector *const &vec, size_t &index) const;
    static SetImplControlBlock* createControlBlock(SetImpl* const& set);

private:
    SetImpl* set;
protected:
    SetImplControlBlock(SetImpl* const& set);
};
