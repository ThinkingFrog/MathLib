#pragma once
#include "ICompact.h"

class LIB_EXPORT CompactImpl : public ICompact {
public:
    static ICompact* createCompact(IVector const * vec1, IVector const * vec2, IMultiIndex const *nodeQuantities);

    ICompact *clone() const override;

    static RC setLogger(ILogger* const logger);
    static ILogger* getLogger();

    bool isInside(IVector const * const&vec) const override;
    /*
    * Method creating new IVector and assigning new address to val
    */
    RC getVectorCopy(IMultiIndex const *index, IVector *& val) const override;
    /*
    * Method copy data from vector in ISet to vector val
    */
    RC getVectorCoords(IMultiIndex const *index, IVector * const& val) const override;

    // левейшая по всем координатам
    RC getLeftBoundary(IVector *& vec) const override;
    // правейшая по всем координатам
    RC getRightBoundary(IVector *& vec) const override;
    size_t getDim() const override;
    IMultiIndex* getGrid() const override;

    //  grid используется для задания сетки на получившемся пересечении
    static ICompact* createIntersection(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid, double tol);
    /* CompactSpan - компактная оболочка: строим наименьшее компактное множество, содержащее 2 переданных */
    static ICompact* createCompactSpan(ICompact const *op1, ICompact const *op2, IMultiIndex const* const grid);

    class IteratorImpl : public IIterator {
    public:
        IIterator * getNext() override;
        IIterator * clone() const override;

        static RC setLogger(ILogger * const pLogger);
        static ILogger* getLogger();

        RC next() override;
        
        /*
        * Iterator is invalid, if it was moved forward, when iterator wasn't able to move
        */
        bool isValid() const override;

        /*
        * Method creating new IVector and assigning new address to val
        */
        RC getVectorCopy(IVector *& val) const override;
        /*
        * Method copy data from vector in ISet to vector val
        */
        RC getVectorCoords(IVector * const& val) const override;
    private:
    protected:
    };

    IIterator* getIterator(IMultiIndex const * const&index, IMultiIndex const * const &bypassOrder) const override;
    // возвращает итератор на левейшую границу
    IIterator* getBegin(IMultiIndex const * const &bypassOrder) const override;
    // возвращает итератор на правейшую границу
    IIterator* getEnd(IMultiIndex const * const &bypassOrder) const override;
    
private:
    IVector* left_boundary;
    IVector* right_boundary;
    IMultiIndex* node_counts;
};
