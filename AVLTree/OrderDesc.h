#ifndef ORDERDESC_H
#define ORDERDESC_H


template <class data_type>
class OrderDesc
{
public:
    int operator()(const data_type &obj1, const data_type &obj2)
    {
        if( obj1 < obj2 ) return 1;
        if( obj1 > obj2 ) return -1;
        return 0;
    }


};

#endif // ORDERDESC_H
