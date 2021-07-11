#include <cmath>
#include <map>
#include "ISet.h"
#include "ISetControlBlock.h"

namespace {
    class SetImpl : public ISet {
    public:
        static RC setLogger(ILogger* const pLogger) {
            if (pLogger == nullptr)
                return RC::NULLPTR_ERROR;
            
            logger = pLogger;
            return RC::SUCCESS;
        }
        static ILogger* getLogger() {
            return logger;
        }

        static ISet* createSet() { return new SetImpl; }
        ISet* clone() const { return new SetImpl(data, size, dim); };

        size_t getDim() const { return dim; }
        size_t getSize() const { return size; }

        RC getCopy(size_t index, IVector *& val) const {
            if (size == 0) {
                logger->warning(RC::SOURCE_SET_EMPTY, __FILE__, __func__, __LINE__);
                return RC::SOURCE_SET_EMPTY;
            }
            if (index > size - 1) {
                logger->warning(RC::INDEX_OUT_OF_BOUND, __FILE__, __func__, __LINE__);
                return RC::INDEX_OUT_OF_BOUND;
            }

            double* buffer = new double[dim];
            for (size_t idx = 0; idx < dim; ++idx)
                buffer[idx] = data[index * dim + idx];
            val = IVector::createVector(dim, buffer);
            delete[] buffer;

            return RC::SUCCESS;
        }
        RC findFirst(IVector const * const& pat, IVector::NORM n, double tol) const {
            if (pat == nullptr) {
                logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
                return RC::NULLPTR_ERROR;
            }
            if (pat->getDim() != dim) {
                logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
                return RC::MISMATCHING_DIMENSIONS;
            }
            if (n == IVector::NORM::AMOUNT || tol < 0) {
                logger->severe(RC::INVALID_ARGUMENT, __FILE__, __func__, __LINE__);
                return RC::INVALID_ARGUMENT;    
            }
            if (std::isnan(tol)) {
                logger->severe(RC::NOT_NUMBER, __FILE__, __func__, __LINE__);
                return RC::NOT_NUMBER;
            }
            if (std::isinf(tol)) {
                logger->severe(RC::INFINITY_OVERFLOW, __FILE__, __func__, __LINE__);
                return RC::INFINITY_OVERFLOW;
            }
        
            for (size_t vec_idx = 0; vec_idx < size; ++vec_idx) {
                bool found = false;
                double* cur_data = new double[dim];
                
                for (size_t idx = 0; idx < dim; ++idx)
                    cur_data[idx] = data[vec_idx * dim + idx];
                IVector* cur_vec = IVector::createVector(dim, cur_data);
                
                if (IVector::equals(pat, cur_vec, n, tol))
                    found = true;
                
                delete[] cur_data;
                delete cur_vec;
                if (found)
                    return RC::SUCCESS;
            }
            return RC::VECTOR_NOT_FOUND;
        }
        RC findFirstAndCopy(IVector const * const& pat, IVector::NORM n, double tol, IVector *& val) const { 
            if (pat == nullptr) {
                logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
                return RC::NULLPTR_ERROR;
            }
            if (pat->getDim() != dim) {
                logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
                return RC::MISMATCHING_DIMENSIONS;
            }
            if (n == IVector::NORM::AMOUNT || tol < 0) {
                logger->severe(RC::INVALID_ARGUMENT, __FILE__, __func__, __LINE__);
                return RC::INVALID_ARGUMENT;    
            }
            if (std::isnan(tol)) {
                logger->severe(RC::NOT_NUMBER, __FILE__, __func__, __LINE__);
                return RC::NOT_NUMBER;
            }
            if (std::isinf(tol)) {
                logger->severe(RC::INFINITY_OVERFLOW, __FILE__, __func__, __LINE__);
                return RC::INFINITY_OVERFLOW;
            }
        
            for (size_t vec_idx = 0; vec_idx < size; ++vec_idx) {
                bool found = false;
                double* cur_data = new double[dim];
                
                for (size_t idx = 0; idx < dim; ++idx)
                    cur_data[idx] = data[vec_idx * dim + idx];
                IVector* cur_vec = IVector::createVector(dim, cur_data);
                
                if (IVector::equals(pat, cur_vec, n, tol))
                    found = true;
                
                delete[] cur_data;
                if (found) {
                    val = cur_vec;
                    return RC::SUCCESS;
                }
                delete cur_vec;
            }
            val = nullptr;
            return RC::VECTOR_NOT_FOUND;
        }

        RC getCoords(size_t index, IVector * const& val) const {
            if (size == 0) {
                logger->warning(RC::SOURCE_SET_EMPTY, __FILE__, __func__, __LINE__);
                return RC::SOURCE_SET_EMPTY;
            }
            if (index > size - 1) {
                logger->warning(RC::INDEX_OUT_OF_BOUND, __FILE__, __func__, __LINE__);
                return RC::INDEX_OUT_OF_BOUND;
            }
            if (val == nullptr) {
                logger->warning(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
                return RC::NULLPTR_ERROR;
            }

            double* buffer = new double[dim];
            for (size_t idx = 0; idx < dim; ++idx)
                buffer[idx] = data[index * dim + idx];
            RC err = val->setData(dim, buffer);
            delete[] buffer;

            return err;
        }
        RC findFirstAndCopyCoords(IVector const * const& pat, IVector::NORM n, double tol, IVector * const& val) const { 
                        if (pat == nullptr) {
                logger->severe(RC::NULLPTR_ERROR, __FILE__, __func__, __LINE__);
                return RC::NULLPTR_ERROR;
            }
            if (pat->getDim() != dim) {
                logger->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
                return RC::MISMATCHING_DIMENSIONS;
            }
            if (n == IVector::NORM::AMOUNT || tol < 0) {
                logger->severe(RC::INVALID_ARGUMENT, __FILE__, __func__, __LINE__);
                return RC::INVALID_ARGUMENT;    
            }
            if (std::isnan(tol)) {
                logger->severe(RC::NOT_NUMBER, __FILE__, __func__, __LINE__);
                return RC::NOT_NUMBER;
            }
            if (std::isinf(tol)) {
                logger->severe(RC::INFINITY_OVERFLOW, __FILE__, __func__, __LINE__);
                return RC::INFINITY_OVERFLOW;
            }
        
            for (size_t vec_idx = 0; vec_idx < size; ++vec_idx) {
                bool found = false;
                double* cur_data = new double[dim];
                
                for (size_t idx = 0; idx < dim; ++idx)
                    cur_data[idx] = data[vec_idx * dim + idx];
                IVector* cur_vec = IVector::createVector(dim, cur_data);
                
                if (IVector::equals(pat, cur_vec, n, tol))
                    found = true;
                
                delete cur_vec;
                if (found) {
                    val->setData(dim, cur_data);
                    return RC::SUCCESS;
                }
                delete[] cur_data;
            }
            return RC::VECTOR_NOT_FOUND;
        }

        RC insert(IVector const * const& val, IVector::NORM n, double tol) {
            if (dim == 0)
                dim = val->getDim();
            else if (dim != val->getDim()) {
                logger->warning(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
                return RC::MISMATCHING_DIMENSIONS;
            }
            if (size == 0)
                last_vec_idx = 0;

            const double* vec_data = val->getData();

            for (size_t vec_idx = 0; vec_idx < size; ++vec_idx) {
                double* sub = new double[dim];
                for (size_t idx = 0; idx < dim; ++idx)
                    sub[idx] = fabs(vec_data[idx] - data[vec_idx * dim + idx]);
                IVector* tmp = IVector::createVector(dim, sub);
                if (tmp->norm(n) <= tol) {
                    delete[] sub;
                    delete tmp;
                    logger->warning(RC::VECTOR_ALREADY_EXIST, __FILE__, __func__, __LINE__);
                    return RC::VECTOR_ALREADY_EXIST;
                }
                delete[] sub;
                delete tmp;
            }

            while (capacity < size * dim + val->getDim()) {
                capacity *= 2;
                double *tmp = new double[capacity];
                for (size_t idx = 0; idx < size * dim; ++idx)
                    tmp[idx] = data[idx];
                delete [] data;
                data = tmp;
            }

            const double* val_data = val->getData();
            for (size_t idx = 0; idx < dim; ++idx)
                data[size * dim + idx] = val_data[idx];
            
            vec_idxs.insert(std::pair<double*, size_t>(data + size * dim, last_vec_idx++));
            ++size;
            
            return RC::SUCCESS;
        }

        RC remove(size_t index) {
            if (size == 0) {
                logger->warning(RC::SOURCE_SET_EMPTY, __FILE__, __func__, __LINE__);
                return RC::SOURCE_SET_EMPTY;
            }
            if (index > size - 1) {
                logger->warning(RC::INDEX_OUT_OF_BOUND, __FILE__, __func__, __LINE__);
                return RC::INDEX_OUT_OF_BOUND;
            }

            double* new_data = new double[capacity];
            for (size_t vec_idx = 0, new_idx = 0; vec_idx < size; ++vec_idx) {
                if (vec_idx != index)
                    for (size_t idx = 0; idx < dim; ++idx, ++new_idx)
                        new_data[new_idx] = data[vec_idx * size + idx];
            }
            delete[] data;
            data = new_data;
            --size;
            
            return RC::SUCCESS; 
        }
        RC remove(IVector const * const& pat, IVector::NORM n, double tol) { 
            if (size == 0) {
                logger->warning(RC::SOURCE_SET_EMPTY, __FILE__, __func__, __LINE__);
                return RC::SOURCE_SET_EMPTY;
            }
            
            return RC::SUCCESS;
         }

        /*
        * Iterator object can be created with ISet methods ISet::getIterator, ISet::getBegin, ISet::getEnd
        */
        class IteratorImpl : public IIterator {
        public:
            /*
            * Create iterator associated with next/previous position
            *
            * @param [in] indexInc Quantity of steps forward
            */
            IIterator * getNext(size_t indexInc = 1) const { return nullptr; }
            IIterator * getPrevious(size_t indexInc = 1) const { return nullptr; }
            IIterator * clone() const { return nullptr; }

            static RC setLogger(ILogger * const pLogger) { 
                if (pLogger == nullptr)
                    return RC::NULLPTR_ERROR;
                
                logger = pLogger;
                return RC::SUCCESS;
            }

            /*
            * Moves iterator forward/backward
            */
            RC next(size_t indexInc = 1)  { return RC::SUCCESS; }
            RC previous(size_t indexInc = 1)  { return RC::SUCCESS; }
            
            bool isValid() const { return false; }

            RC makeBegin() { return RC::SUCCESS; }
            RC makeEnd() { return RC::SUCCESS; }

            /*
            * Getter of value (same semantic as ISet::getCopy)
            */
            RC getVectorCopy(IVector *& val) const { return RC::SUCCESS; }
            /*
            * Getter of value (same semantic as ISet::getCoords)
            */
            RC getVectorCoords(IVector * const& val) const { return RC::SUCCESS; }

            ~IteratorImpl()  = default;

        protected:
            /*
            * As long as iterator refers to vector in ISet, which corresponds to unique index, we can compare iterators by this index
            */
            size_t getIndex() const { return 0; }
            IteratorImpl() = default;
        private:
            ISetControlBlock* control_block;
            static ILogger* logger;
        };


        IIterator *getIterator(size_t index) const { return nullptr; }
        IIterator *getBegin() const { return nullptr; }
        IIterator *getEnd() const { return nullptr; }
        
        ~SetImpl() {
            delete[] data;
        }
        
    private:
        static ILogger* logger;
        double* data;
        std::map<double*, size_t> vec_idxs;
        size_t last_vec_idx;
        size_t capacity; // amount of allocated double values
        size_t size;    // amount of vectors in set
        size_t dim;     // size of a single vector
    
    protected:
        SetImpl() { 
            capacity = 100;
            data = new double[capacity];
            
            size = 0;
            dim = 0;
            last_vec_idx = 0;
        }
        SetImpl(double const* const& other_data, size_t other_size, size_t other_dim) { 
            capacity = other_size;
            data = new double[capacity];
            for (size_t idx = 0; idx < other_size * other_dim; ++idx)
                data[idx] = other_data[idx];
            
            size = other_size;
            dim = other_dim;
        }
        
    };
    ILogger* SetImpl::logger = nullptr;
    ILogger* SetImpl::IteratorImpl::logger = nullptr;
};

RC ISet::setLogger(ILogger* const logger) {
    return SetImpl::setLogger(logger);
}
ILogger* ISet::getLogger() {
    return SetImpl::getLogger();
}
ISet* ISet::createSet() {
    return SetImpl::createSet();
}
ISet* ISet::makeIntersection(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    if (op1->getDim() != op2->getDim()) {
        getLogger()->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return nullptr;
    }

    size_t dim = op1->getDim();
    ISet* new_set = ISet::createSet();

    for (size_t vec_idx = 0; vec_idx < op1->getSize(); ++vec_idx) {
        double* empty_data = new double[dim];

        IVector* vec1 = IVector::createVector(dim, empty_data);
        RC err = op1->getCoords(vec_idx, vec1);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;
            
            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }
        
        IVector* vec2 = IVector::createVector(op1->getDim(), new double[op1->getDim()]);
        err = op2->findFirstAndCopyCoords(vec1, n, tol, vec2);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete vec2;
            delete[] empty_data;

            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }

        new_set->insert(vec1, n, tol);

        delete vec1;
        delete vec2;
        delete[] empty_data;
    }

    return new_set;
}
ISet* ISet::makeUnion(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    if (op1->getDim() != op2->getDim()) {
        getLogger()->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return nullptr;
    }

    size_t dim = op1->getDim();
    ISet* new_set = op1->clone();

    for (size_t vec_idx = 0; vec_idx < op1->getSize(); ++vec_idx) {
        double* empty_data = new double[dim];

        IVector* vec1 = IVector::createVector(dim, empty_data);
        RC err = op1->getCoords(vec_idx, vec1);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;
            
            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }
        
        IVector* vec2 = IVector::createVector(op1->getDim(), new double[op1->getDim()]);
        err = op2->findFirstAndCopyCoords(vec1, n, tol, vec2);
        if (err == RC::VECTOR_NOT_FOUND) {
            new_set->insert(vec1, n, tol);
        }
        else if (err != RC::SUCCESS) {
            delete vec1;
            delete vec2;
            delete[] empty_data;

            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }

        delete vec1;
        delete vec2;
        delete[] empty_data;
    }

    return new_set;
}
ISet* ISet::sub(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    if (op1->getDim() != op2->getDim()) {
        getLogger()->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return nullptr;
    }

    size_t dim = op1->getDim();
    ISet* new_set = ISet::createSet();

    for (size_t vec_idx = 0; vec_idx < op1->getSize(); ++vec_idx) {
        double* empty_data = new double[dim];

        IVector* vec1 = IVector::createVector(dim, empty_data);
        RC err = op1->getCoords(vec_idx, vec1);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;
            
            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }
        
        err = op2->findFirst(vec1, n, tol);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;

            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return new_set;
        }
        new_set->insert(vec1, n, tol);

        delete vec1;
        delete[] empty_data;
    }

    return new_set;
}
ISet* ISet::symSub(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    ISet* un = ISet::makeUnion(op1, op2, n, tol);
    ISet* inter = ISet::makeIntersection(op1, op2, n, tol);
    ISet* sub = ISet::sub(un, inter, n, tol);
    
    delete un;
    delete inter;
    return sub;
}
bool ISet::equals(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    if (op1->getSize() != op2->getSize()) {
        getLogger()->warning(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return false;
    }

    return subSet(op1, op2, n, tol);
}
bool ISet::subSet(ISet const * const& op1, ISet const * const& op2, IVector::NORM n, double tol) {
    if (op1->getDim() != op2->getDim()) {
        getLogger()->severe(RC::MISMATCHING_DIMENSIONS, __FILE__, __func__, __LINE__);
        return false;
    }

    size_t dim = op1->getDim();

    for (size_t vec_idx = 0; vec_idx < op1->getSize(); ++vec_idx) {
        double* empty_data = new double[dim];

        IVector* vec1 = IVector::createVector(dim, empty_data);
        RC err = op1->getCoords(vec_idx, vec1);
        if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;
            
            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return false;
        }
        
        err = op2->findFirst(vec1, n, tol);
        if (err == RC::VECTOR_NOT_FOUND) {
            return false;
        }
        else if (err != RC::SUCCESS) {
            delete vec1;
            delete[] empty_data;

            getLogger()->warning(err, __FILE__, __func__, __LINE__);
            return false;
        }

        delete vec1;
        delete[] empty_data;
    }

    return true;
}
RC ISet::IIterator::setLogger(ILogger * const pLogger) {
    return SetImpl::IteratorImpl::setLogger(pLogger);
}
ILogger* ISet::IIterator::getLogger() {
    return SetImpl::IteratorImpl::getLogger();
}
ISet::~ISet() = default;
