#pragma once
#include "IMultiIndex.h"

#define PTR_DATA (size_t*)((u_int8_t*)(this) + sizeof(MultiIndexImpl))

class LIB_EXPORT MultiIndexImpl : public IMultiIndex {
public:
    static IMultiIndex* createMultiIndex(size_t dim, const size_t* indices);
    IMultiIndex* clone() const override;

    size_t getDim() const override;
    const size_t* getData() const override;
    // Dim needs for double check that ptr_data have the same size as dimension of multi-index
    RC setData(size_t dim, size_t const* const& ptr_data) override;

    static RC setLogger(ILogger * const pLogger);
    static ILogger* getLogger();

    RC getAxisIndex(size_t axisIndex, size_t &val) const override;
    RC setAxisIndex(size_t axisIndex, size_t val) override;

    RC incAxisIndex(size_t axisIndex, ssize_t val) override;

private:
    size_t dim;
    static ILogger* logger;
protected:
    MultiIndexImpl(size_t dim);
};
