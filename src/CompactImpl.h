#pragma once
#include "ICompact.h"

class LIB_EXPORT CompactImpl : public ICompact {
public:
    static ICompact* createCompact(IVector const * vec1, IVector const * vec2, IMultiIndex const *nodeQuantities);

    ICompact *clone() const;

    static RC setLogger(ILogger* const logger);
    static ILogger* getLogger();

    bool isInside(IVector const * const&vec) const;
    /*
    * Method creating new IVector and assigning new address to val
    */
    RC getVectorCopy(IMultiIndex const *index, IVector *& val) const;
    /*
    * Method copy data from vector in ISet to vector val
    */
    RC getVectorCoords(IMultiIndex const *index, IVector * const& val) const;

    // левейшая по всем координатам
    RC getLeftBoundary(IVector *& vec) const;
    // правейшая по всем координатам
    RC getRightBoundary(IVector *& vec) const;
    size_t getDim() const;
    IMultiIndex* getGrid() const;

    //  grid используется для задания сетки на получившемся пересечении
    static ICompact* createIntersection(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid, double tol);
    /* CompactSpan - компактная оболочка: строим наименьшее компактное множество, содержащее 2 переданных */
    static ICompact* createCompactSpan(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid);

    class IteratorImpl : public IIterator {
    public:
        IIterator * getNext();
        IIterator * clone() const;

        static RC setLogger(ILogger * const pLogger);
        static ILogger* getLogger();

        RC next();
        
        /*
        * Iterator is invalid, if it was moved forward, when iterator wasn't able to move
        */
        bool isValid() const;

        /*
        * Method creating new IVector and assigning new address to val
        */
        RC getVectorCopy(IVector *& val) const;
        /*
        * Method copy data from vector in ISet to vector val
        */
        RC getVectorCoords(IVector * const& val) const;
    private:
    protected:
    };

    IIterator* getIterator(IMultiIndex const * const&index, IMultiIndex const * const &bypassOrder) const;
    // возвращает итератор на левейшую границу
    IIterator* getBegin(IMultiIndex const * const &bypassOrder) const;
    // возвращает итератор на правейшую границу
    IIterator* getEnd(IMultiIndex const * const &bypassOrder) const;
    
private:
protected:
};
