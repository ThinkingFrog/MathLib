#pragma once
#include "IMultiIndex.h"

class LIB_EXPORT MultiIndexImpl : public IMultiIndex {
public:
    static IMultiIndex* createMultiIndex(size_t dim, const size_t* indices);
    IMultiIndex* clone() const;

    size_t getDim() const;
    const size_t* getData() const;
    // Dim needs for double check that ptr_data have the same size as dimension of multi-index
    RC setData(size_t dim, size_t const* const& ptr_data);

    static RC setLogger(ILogger * const pLogger);
    static ILogger* getLogger();

    RC getAxisIndex(size_t axisIndex, size_t &val) const;
    RC setAxisIndex(size_t axisIndex, size_t val);

    RC incAxisIndex(size_t axisIndex, ssize_t val);

private:
protected:
};
