#pragma once
#include "CompactImplControlBlock.h"
#include "ICompact.h"

class LIB_EXPORT CompactImpl : public ICompact {
  public:
    static ICompact *createCompact(IVector const *vec1, IVector const *vec2, IMultiIndex const *nodeQuantities);

    ICompact *clone() const override;

    static RC setLogger(ILogger *const logger);
    static ILogger *getLogger();

    bool isInside(IVector const *const &vec) const override;
    RC getVectorCopy(IMultiIndex const *index, IVector *&val) const override;
    RC getVectorCoords(IMultiIndex const *index, IVector *const &val) const override;

    RC getLeftBoundary(IVector *&vec) const override;
    RC getRightBoundary(IVector *&vec) const override;
    size_t getDim() const override;
    IMultiIndex *getGrid() const override;

    class IteratorImpl : public IIterator {
      public:
        IIterator *getNext() override;
        IIterator *clone() const override;

        static RC setLogger(ILogger *const pLogger);
        static ILogger *getLogger();

        RC next() override;

        /*
         * Iterator is invalid, if it was moved forward, when iterator wasn't able to move
         */
        bool isValid() const override;

        /*
         * Method creating new IVector and assigning new address to val
         */
        RC getVectorCopy(IVector *&val) const override;
        /*
         * Method copy data from vector in ISet to vector val
         */
        RC getVectorCoords(IVector *const &val) const override;

      private:
        bool valid;
        IVector *vector;
        CompactImplControlBlock *control_block;
    };

    IIterator *getIterator(IMultiIndex const *const &index, IMultiIndex const *const &bypassOrder) const override;
    // возвращает итератор на левейшую границу
    IIterator *getBegin(IMultiIndex const *const &bypassOrder) const override;
    // возвращает итератор на правейшую границу
    IIterator *getEnd(IMultiIndex const *const &bypassOrder) const override;
    RC moveIterator(IMultiIndex *const &currentIndex, IMultiIndex const *const &bypassOrder);

    ~CompactImpl();

  private:
    static ILogger *logger;
    const IVector *left_boundary;
    const IVector *right_boundary;
    const IMultiIndex *grid;
    size_t dim;

    CompactImpl(const IVector *left, const IVector *right, const IMultiIndex *nodes);
};
