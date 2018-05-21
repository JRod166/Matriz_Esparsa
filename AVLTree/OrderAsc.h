#ifndef ORDERASC_H
#define ORDERASC_H

template <class data_type>
class OrderAsc
{
public:
    int operator()(const data_type &obj1, const data_type &obj2)
    {
        if( obj1 > obj2 ) return 1;
        if( obj1 < obj2 ) return -1;
        return 0;
    }


};

#endif // ORDERASC_H
