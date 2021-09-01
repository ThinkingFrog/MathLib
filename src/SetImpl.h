#pragma once
#include <map>
#include "ISet.h"
#include "SetImplControlBlock.h"


class SetImpl : public ISet {
public:
    static RC setLogger(ILogger* const pLogger);
    static ILogger* getLogger();

    static ISet* createSet();
    ISet* clone() const;

    size_t getDim() const;
    size_t getSize() const;

    RC getCopy(size_t index, IVector *& val) const;
    RC findFirst(IVector const * const& pat, IVector::NORM n, double tol) const;
    RC findFirstAndCopy(IVector const * const& pat, IVector::NORM n, double tol, IVector *& val) const;

    RC getCoords(size_t index, IVector * const& val) const;
    RC findFirstAndCopyCoords(IVector const * const& pat, IVector::NORM n, double tol, IVector * const& val) const;

    RC insert(IVector const * const& val, IVector::NORM n, double tol);

    RC remove(size_t index);
    RC remove(IVector const * const& pat, IVector::NORM n, double tol);

    class IteratorImpl : public IIterator {
    public:
        IteratorImpl(SetImplControlBlock* const& controlBlock, size_t index, IVector* vector);

        IIterator * getNext(size_t indexInc = 1) const;
        IIterator * getPrevious(size_t indexInc = 1) const;
        IIterator * clone() const;

        static RC setLogger(ILogger * const pLogger);

        RC next(size_t indexInc = 1);
        RC previous(size_t indexInc = 1);
        
        bool isValid() const;

        RC makeBegin();
        RC makeEnd();

        RC getVectorCopy(IVector *& val) const;
        RC getVectorCoords(IVector * const& val) const;

        ~IteratorImpl();

    protected:
        size_t getIndex() const;
        IteratorImpl();
    private:
        size_t cur_unique_idx;
        IVector* cur_vector;
        SetImplControlBlock* control_block;
        static ILogger* logger;
        bool valid;
    };

    IIterator *getIterator(size_t index) const;
    IIterator *getBegin() const;
    IIterator *getEnd() const;
    
    ~SetImpl();

    RC getNextByUniqueIndex(IVector *const &vec, size_t &index, size_t indexInc);
    RC getPrevByUniqueIndex(IVector *const &vec, size_t &index, size_t indexInc);
    RC getFirstByUniqueIndex(IVector *const &vec, size_t &index);
    RC getLastByUniqueIndex(IVector *const &vec, size_t &index);

private:
    static ILogger* logger;
    double* data;
    SetImplControlBlock* control_block;
    std::map<size_t, size_t> unique_idxs_to_order;
    std::map<size_t, size_t> order_idxs_to_unique;
    size_t last_vec_idx;
    size_t capacity; // amount of allocated double values
    size_t size;    // amount of vectors in set
    size_t dim;     // size of a single vector

protected:
    SetImpl();
    SetImpl(double const* const& other_data, size_t other_size, size_t other_dim);
    
};
