#ifndef MATRIZESPARSA_CPP_H
#define MATRIZESPARSA_CPP_H

template <class T>
MatrizEsparsa<T>::MatrizEsparsa()
{

}

template <class T>
MatrizEsparsa<T>::~MatrizEsparsa()
{
    typename index_type::iterator it;
    for(it=rows.begin(); it!=rows.end(); ++it)
        destroy((*it).content, 1);
}

template <class T>
bool MatrizEsparsa<T>::find( Node** begin, const index_data_type &pos, bool c, Node** &p ) const
{
    p = begin;
    while(*p)
    {
        if( (*p)->index[c] == pos ) return 1;
        if( (*p)->index[c] > pos ) return 0;
        p = &( (*p)->sgtNode[c]);
    }
    return 0;
}

template <class T>
void MatrizEsparsa<T>::destroy( Node* n, bool c )
{
    if( !n )
        return;
    destroy( n->sgtNode[c], c );
    delete n;
}

template <class T>
void MatrizEsparsa<T>::insert( const T &c, const index_data_type &row, const index_data_type &col )
{
    if( exists(row, col) )
    {
        Node** begin = &(*rows.find(row)).content;
        Node ** p;
        find( begin, col, 1, p);
        (*p)->data = c;
        return;
    }

    Index_node_data irow(row);
    Index_node_data icol(col);
    if( !rows.exists(irow) )
        rows.add(irow);
    if( !cols.exists(icol) )
        cols.add(icol);

    Node* n = new Node(c, row, col);

    Node** begin = &(*rows.find(irow)).content;
    Node** p;
    find(begin, col, 1, p);
    Node* temp = (*p);
    (*p) = n;
    n->sgtNode[1] = temp;

    begin = &(*cols.find(icol)).content;
    find(begin, row, 0, p);
    temp = (*p);
    (*p) = n;
    n->sgtNode[0] = temp;
    return;
}

template <class T>
bool MatrizEsparsa<T>::exists( const index_data_type &row, const index_data_type &col )
{
    Index_node_data irow(row);
    if( !rows.exists(irow) )
        return 0;
    Node** begin = &(*rows.find(irow)).content;
    Node** p;
    if( !find(begin, col, 1, p) )
        return 0;
    return 1;
}

template <class T>
T MatrizEsparsa<T>::get( const index_data_type &row, const index_data_type &col )
{
    Index_node_data irow(row);
    Node** begin = &(*rows.find(irow)).content;
    Node** p;
    find(begin, col, 1, p);
    return (*p)->data;
}

template <class T>
T& MatrizEsparsa<T>::operator()( const index_data_type &row, const index_data_type &col )
{
    if( !exists(row, col) )
    {
        T temp;
        insert(temp, row, col);
    }
    Index_node_data irow(row);
    Node** begin = &(*rows.find(irow)).content;
    Node** p;
    find(begin, col, 1, p);
    return (*p)->data;
}

template <class T>
void MatrizEsparsa<T>::reset()
{
    typename index_type::iterator it;
    for(it=rows.begin(); it!=rows.end(); ++it)
    {
        destroy((*it).content, 1);
        rows.erase(*it);
    }
    for(it=cols.begin(); it!=cols.end(); ++it)
        cols.erase(*it);
}

#endif // MATRIZESPARSA_CPP_H
