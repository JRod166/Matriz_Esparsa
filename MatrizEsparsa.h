#ifndef MATRIZESPARSA_H
#define MATRIZESPARSA_H

#include "AVLTreeProxy.h"

template <class data_type>
class MatrizEsparsa
{
typedef int index_data_type;

class Node
{
public:
    data_type data;
    index_data_type index[2]; // 0: rows, 1: cols
    Node* sgtNode[2]; // 0: down, 1: right
    Node( const data_type &c, const index_data_type &row, const index_data_type &col ): data(c)
    {
        index[0] = row;
        index[1] = col;
        sgtNode[0] = 0;
        sgtNode[1] = 0;
    }
};

class Index_node_data
{
public:
    index_data_type index;
    Node* content;
    Index_node_data( const index_data_type &i ): index(i), content(0) {}
    Index_node_data( const index_data_type &i, Node* _content ): index(i), content(_content) {}
    bool operator<( const Index_node_data &d ) const { return index<d.index;}
    bool operator>( const Index_node_data &d ) const { return index>d.index;}
    bool operator==( const Index_node_data &d ) const { return index==d.index;}
};

typedef AVLTreeProxy<Index_node_data> index_type;

private:
    index_type rows;
    index_type cols;

    bool find( Node** begin, const index_data_type &pos, bool c, Node** &p ) const;// c=1: Busca horizontalmente
    void destroy( Node* n, bool c ); // Función auxiliar del destructor
                                     // c=1: Destruye horizontalmente

public:
    MatrizEsparsa();
    ~MatrizEsparsa();

    void insert( const data_type &c, const index_data_type &row, const index_data_type &col );
    bool exists( const index_data_type &row, const index_data_type &col );
    data_type get( const index_data_type &row, const index_data_type &col );
    data_type& operator()( const index_data_type &row, const index_data_type &col );
    void reset();

};

#include "MatrizEsparsa_cpp.h"

#endif // MATRIZESPARSA_H
