#include <cmath>
#include "CompactImpl.h"


ILogger* CompactImpl::logger = nullptr;

CompactImpl::CompactImpl(const IVector* left, const IVector* right, const IMultiIndex* nodes) {
    left_boundary = left->clone();
    right_boundary = right->clone();
    grid = nodes->clone();
    dim = left_boundary->getDim();
}

CompactImpl::~CompactImpl() {
    delete left_boundary;
    delete right_boundary;
    delete grid;
}

ICompact* CompactImpl::createCompact(IVector const * vec1, IVector const * vec2, IMultiIndex const *nodeQuantities) {
    if (vec1 == nullptr || vec2 == nullptr || nodeQuantities == nullptr) {
        logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return nullptr;
    }
    if (vec1->getDim() != vec2->getDim() || vec2->getDim() != nodeQuantities->getDim()) {
        logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return nullptr;
    }

    return new (std::nothrow) CompactImpl(vec1, vec2, nodeQuantities);
}

RC CompactImpl::setLogger(ILogger* const pLogger) {
    if (pLogger == nullptr)
        return RC::NULLPTR_ERROR;
    
    logger = pLogger;
    return RC::SUCCESS;
}

ILogger* CompactImpl::getLogger() {
    return logger;
}

ICompact* CompactImpl::clone() const {
    return createCompact(left_boundary, right_boundary, grid);
}

bool CompactImpl::isInside(IVector const* const& vec) const {
    if (vec == nullptr) {
        logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return false;
    }
    if (vec->getDim() != dim) {
        logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return false;
    }

    const double* left_data = left_boundary->getData();
    const double* right_data = right_boundary->getData();
    const double* vec_data = vec->getData();

    for (size_t idx = 0; idx < dim; ++idx) 
        if (vec_data[idx] > right_data[idx] || vec_data[idx] < left_data[idx])
            return false;
    return true;
}

RC CompactImpl::getLeftBoundary(IVector *& vec) const {
    IVector* copy = left_boundary->clone();
    vec = copy;
    if (copy == nullptr) {
        logger->warning(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return RC::NULLPTR_ERROR;
    }
    return RC::SUCCESS;
}
RC CompactImpl::getRightBoundary(IVector *& vec) const {
    IVector* copy = right_boundary->clone();
    vec = copy;
    if (copy == nullptr) {
        logger->warning(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return RC::NULLPTR_ERROR;
    }
    return RC::SUCCESS;
}

size_t CompactImpl::getDim() const {
    return dim;
}

IMultiIndex* CompactImpl::getGrid() const {
    return grid->clone();
}

RC CompactImpl::getVectorCopy(IMultiIndex const *index, IVector *& val) const {
    double* empty_data = new double[dim];
    IVector* tmp = IVector::createVector(dim, empty_data);
    delete[] empty_data;

    if (tmp == nullptr) {
        logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        val = nullptr;
        return RC::NULLPTR_ERROR;
    }

    RC err = getVectorCoords(index, tmp);
    if (err != RC::SUCCESS) {
        logger->severe(err, __FILE__, __func__, __LINE__);
        val = nullptr;
        delete tmp;
        return err;
    }

    val = tmp;
    return RC::SUCCESS;
}

RC CompactImpl::getVectorCoords(IMultiIndex const *index, IVector * const& val) const {
    if (index == nullptr) {
        logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return RC::NULLPTR_ERROR;
    }
    if (index->getDim() != dim || val->getDim() != dim) {
        logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return RC::MISMATCHING_DIMENSIONS;
    }

    const size_t* index_data = index->getData();
    const size_t* grid_data = grid->getData();
    for (size_t idx = 0; idx < dim; ++idx)
        if (index_data[idx] > grid_data[idx]) {
            logger->severe(RC::INDEX_OUT_OF_BOUND, __FILE__, __func__, __LINE__);
            return RC::INDEX_OUT_OF_BOUND;
        }
    
    const double* left_data = left_boundary->getData();
    const double* right_data = right_boundary->getData();
    for (size_t idx = 0; idx < dim; ++idx) {
        double lambda = (double)(index_data[idx]) / (grid_data[idx] - 1);
        val->setCord(idx, (1.0 - lambda) * left_data[idx] + lambda * right_data[idx]);
    }

    return RC::SUCCESS;
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

RC CompactImpl::moveIterator(IMultiIndex * const &currentIndex, IMultiIndex const * const &bypassOrder) {
    return RC::SUCCESS;
}

ICompact* ICompact::createIntersection(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid, double tol) {
    if (op1 == nullptr || op2 == nullptr || grid == nullptr) {
        getLogger()->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
        return nullptr;
    }
    if (std::isnan(tol) || std::isinf(tol)) {
        getLogger()->severe(RC::NOT_NUMBER, __FILE__, __func__, __LINE__);
        return nullptr;
    }
    if (op1->getDim() != op2->getDim() || op1->getDim() != grid->getDim()) {
        getLogger()->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return nullptr;
    }

    IVector* com1_left_bound, *com1_right_bound, *com2_left_bound, *com2_right_bound;
    RC err = op1->getLeftBoundary(com1_left_bound);
    if (err != RC::SUCCESS) {
        getLogger()->severe(err, __FILE__, __func__, __LINE__);
        return nullptr;
    }
}

ICompact* ICompact::createCompactSpan(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid) {
    return nullptr;
}

RC ICompact::IIterator::setLogger(ILogger* const logger) {
    return CompactImpl::IteratorImpl::setLogger(logger);
}

ILogger* ICompact::IIterator::getLogger() {
    return CompactImpl::IteratorImpl::getLogger();
}

ICompact::IIterator::~IIterator() = default;

ICompact::~ICompact() = default;
