#include <cstddef>
#include "IVector.h"
#include "ISetControlBlock.h"
#include "ISet.h"


class SetImplControlBlock : public ISetControlBlock {
public:
    virtual RC getNext(IVector *const &vec, size_t &index, size_t indexInc = 1) const {

    }
    virtual RC getPrevious(IVector *const &vec, size_t &index, size_t indexInc = 1) const = 0;
    
    virtual RC getBegin(IVector *const &vec, size_t &index) const = 0;
    virtual RC getEnd(IVector *const &vec, size_t &index) const = 0;

private:
    ISet* set;
    size_t cur_idx;
protected:
    SetImplControlBlock(ISet* const& set) : set(set), cur_idx(0) {};
};

ISetControlBlock::~ISetControlBlock() = default;
