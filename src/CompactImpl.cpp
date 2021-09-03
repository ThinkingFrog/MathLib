#include "CompactImpl.h"

ICompact* CompactImpl::createCompact(IVector const * vec1, IVector const * vec2, IMultiIndex const *nodeQuantities) {
    
}


ICompact* ICompact::createCompact(IVector const * vec1, IVector const * vec2, IMultiIndex const *nodeQuantities) {
    return CompactImpl::createCompact(vec1, vec2, nodeQuantities);
}

RC ICompact::setLogger(ILogger* const logger) {
    return CompactImpl::setLogger(logger);
}

ILogger* ICompact::getLogger() {
    return CompactImpl::getLogger();
}

ICompact* ICompact::createIntersection(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid, double tol) {}

ICompact* ICompact::createCompactSpan(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid) {}

RC ICompact::IIterator::setLogger(ILogger* const logger) {
    return CompactImpl::IteratorImpl::setLogger(logger);
}

ILogger* ICompact::IIterator::getLogger() {
    return CompactImpl::IteratorImpl::getLogger();
}

ICompact::IIterator::~IIterator() = default;

ICompact::~ICompact() = default;
