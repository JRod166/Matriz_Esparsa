#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include "Traits.h"
#include <stack>
#include <vector>

using namespace std;

//-------------------------------------------------------------
//                     CLASS AVLTREE
//-------------------------------------------------------------


template <class tr>
class AVLTree
{
typedef typename tr::data_type data_type;
typedef typename tr::cmp_type cmp_type;
typedef AVLNode<data_type> node_type;

private:
    node_type *root;
    cmp_type cmp;

    bool find( const data_type &obj, node_type** &p );
    bool find( const data_type &obj, node_type** &p, stack<node_type**> &s );
    bool find( const data_type &obj, node_type** &p, stack<node_type*> &s );
    short heigh( node_type* p );
    void updateHeigh( node_type* p );
    bool isBalanced( node_type* p );
    void simpleRotation( node_type **p, bool left );
    void doubleRotation( node_type **p, bool left );
    void balance( node_type **p );
    inline static bool isLeaf( node_type* p );
    void destroy( node_type* p );

public:
    AVLTree();
    ~AVLTree();

    bool add( const data_type &obj );
    bool exists( const data_type &obj );
    bool erase( const data_type &obj );


    //-------------------------------------------------------------
    //                  ABSTRACT CLASS ITERATOR
    //-------------------------------------------------------------

    class Iterator
    {
    protected:
        node_type* current;
        stack<node_type*> prev;

    public:
        Iterator();
        Iterator(node_type* _current, stack<node_type*> _prev);
        Iterator(const Iterator &it);

        const Iterator& operator=(const Iterator &it);
        bool operator==(const Iterator &it);
        bool operator!=(const Iterator &it);
        virtual Iterator& operator++() = 0;
        data_type& operator*();
    };

    //-------------------------------------------------------------
    //                  CLASS ITERATOR IN ORDER
    //-------------------------------------------------------------

    class Iterator_inOrder: public Iterator
    {
    public:
        Iterator_inOrder();
        Iterator_inOrder(node_type* _current, stack<node_type*> _prev);
        Iterator_inOrder(const Iterator_inOrder &it);

        Iterator_inOrder& operator++();
    };

    //-------------------------------------------------------------
    //                  CLASS ITERATOR POST ORDER
    //-------------------------------------------------------------

    class Iterator_postOrder: public Iterator
    {
    public:
        Iterator_postOrder();
        Iterator_postOrder(node_type* _current, stack<node_type*> _prev);
        Iterator_postOrder(const Iterator_postOrder &it);

        Iterator_postOrder& operator++();
    };

    //-------------------------------------------------------------
    //                  CLASS ITERATOR PRE ORDER
    //-------------------------------------------------------------

    class Iterator_preOrder: public Iterator
    {
    public:
        Iterator_preOrder();
        Iterator_preOrder(node_type* _current, stack<node_type*> _prev);
        Iterator_preOrder(const Iterator_preOrder &it);

        Iterator_preOrder& operator++();
    };

//-------------------------------------------------------------
//                  CLASS TREE
//-------------------------------------------------------------


    Iterator_inOrder inOrderBegin();
    Iterator_inOrder inOrderEnd();
    Iterator_postOrder postOrderBegin();
    Iterator_postOrder postOrderEnd();
    Iterator_preOrder preOrderBegin();
    Iterator_preOrder preOrderEnd();

    typedef Iterator_inOrder iterator_inOrder;
    typedef Iterator_postOrder iterator_postOrder;
    typedef Iterator_preOrder iterator_preOrder;

    iterator_inOrder find( const data_type &obj );

};

#include "AVLTree_cpp.h"

#endif // AVLTREE_H
