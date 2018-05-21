#ifndef AVLTREEPROXY_H
#define AVLTREEPROXY_H

#include "AVLTree/AVLTree.h"
#include "AVLTree/Traits.h"

template <class data_type>
class AVLTreeProxy
{
private:
    AVLTree<Asc<data_type> >* tree;

public:
    AVLTreeProxy(): tree(new AVLTree<Asc<data_type> >) {}
    ~AVLTreeProxy() { delete tree;}

    bool add( const data_type &obj )
    {
        return tree->add(obj);
    }

    bool exists( const data_type &obj )
    {
        return tree->exists(obj);
    }

    bool erase( const data_type &obj )
    {
        return tree->erase(obj);
    }

    typedef typename AVLTree<Asc<data_type> >::iterator_inOrder iterator;

    iterator begin()
    {
        return tree->inOrderBegin();
    }

    iterator end()
    {
        return tree->inOrderEnd();
    }

    iterator find( const data_type &obj )
    {
        return tree->find(obj);
    }

};

#endif // AVLTREEPROXY_H
