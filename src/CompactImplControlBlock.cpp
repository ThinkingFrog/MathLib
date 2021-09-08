#include "CompactImplControlBlock.h"

CompactImplControlBlock::CompactImplControlBlock(CompactImpl *compact) : compact(compact) {}

RC CompactImplControlBlock::get(IMultiIndex *const &currentIndex, IMultiIndex const *const &bypassOrder) const {}

RC CompactImplControlBlock::get(IMultiIndex const *const &currentIndex, IVector *const &val) const {}

ICompactControlBlock::~ICompactControlBlock() = default;