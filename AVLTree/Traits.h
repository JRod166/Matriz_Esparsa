#ifndef TRAITS_H
#define TRAITS_H
#include "OrderAsc.h"
#include "OrderDesc.h"

template <class t>
struct Asc
{
    typedef t data_type;
    typedef OrderAsc<data_type> cmp_type;
};

template <class t>
struct Desc
{
    typedef t data_type;
    typedef OrderDesc<data_type> cmp_type;
};



#endif // TRAITS_H
