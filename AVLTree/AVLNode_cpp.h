#ifndef AVLNODE_CPP_H
#define AVLNODE_CPP_H


template <class data_type>
AVLNode<data_type>::AVLNode(): heigh(1)
{
    sons[0] = NULL;
    sons[1] = NULL;

}

template <class data_type>
AVLNode<data_type>::AVLNode( const data_type &obj ): data(obj), heigh(1)
{
    sons[0] = NULL;
    sons[1] = NULL;
}

#endif // AVLNODE_CPP_H
