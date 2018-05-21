#ifndef AVLNODE_H
#define AVLNODE_H

template <class data_type>
class AVLNode
{
template <class tr> friend class AVLTree;

private:
    data_type data;
    AVLNode* sons[2];
    short heigh;

public:
    AVLNode();
    AVLNode( const data_type &obj );

};

#include "AVLNode_cpp.h"

#endif // AVLNODE_H
