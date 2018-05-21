#ifndef AVLTREE_CPP_H
#define AVLTREE_CPP_H

#define Tree AVLTree<tr>

//-------------------------------------------------------------
//                     CLASS AVLTREE
//-------------------------------------------------------------

template <class tr>
Tree::AVLTree(): root(NULL)
{
    // Ctor Default
}

template <class tr>
Tree::~AVLTree()
{
    destroy(root);
}

template <class tr>
bool Tree::find( const data_type &obj, node_type** &p )
{
    p = &root;
    while( *p  )
    {
        if( cmp(obj, (*p)->data) == 0 ) return 1;
        p = &(*p)->sons[cmp(obj, (*p)->data) == 1];
    }
    return 0;
}

template <class tr>
bool Tree::find( const data_type &obj, node_type** &p, stack<node_type**> &s )
{
    p = &root;
    while( *p  )
    {
        s.push(p);
        if( cmp(obj, (*p)->data) == 0 ) return 1;
        p = &(*p)->sons[cmp(obj, (*p)->data) == 1];
    }
    return 0;
}

template <class tr>
bool Tree::find( const data_type &obj, node_type** &p, stack<node_type*> &s )
{
    p = &root;
    while( *p  )
    {
        s.push(*p);
        if( cmp(obj, (*p)->data) == 0 ) return 1;
        p = &(*p)->sons[cmp(obj, (*p)->data) == 1];
    }
    return 0;
}

template <class tr>
short Tree::heigh( node_type *p )
{
    if(!p) return 0;
    return p->heigh;
}

template <class tr>
void Tree::updateHeigh( node_type* p )
{
    if(!p) return;
    p->heigh = max( heigh( p->sons[0] ), heigh( p->sons[1] ) )+1;
    return;
}

template <class tr>
 bool Tree::isBalanced( node_type* p )
 {
     if(!p) return 1;
     short factor = heigh( p->sons[0] ) - heigh( p->sons[1] );
     if( -2 < factor && factor < 2 ) return 1;
     return 0;
 }

template <class tr>
void Tree::simpleRotation( node_type **p, bool left )
{
    node_type *temp = (*p)->sons[!left];
    (*p)->sons[!left] = temp->sons[left];
    temp->sons[left] = (*p);
    updateHeigh( *p );
    updateHeigh( temp );
    (*p) = temp;
}

template <class tr>
void Tree::doubleRotation( node_type **p, bool left )
{
    simpleRotation( &(*p)->sons[!left], !left );
    simpleRotation( p, left );
}

template <class tr>
void Tree::balance( node_type **p )
{
    if( heigh((*p)->sons[0]) > heigh((*p)->sons[1]) )
    {
        if( heigh((*p)->sons[0]->sons[0]) > heigh((*p)->sons[0]->sons[1]) )
            simpleRotation( p, 1 );
        else
            doubleRotation( p, 1 );
    }
    else
    {
        if( heigh((*p)->sons[1]->sons[0]) < heigh((*p)->sons[1]->sons[1]) )
            simpleRotation( p, 0 );
        else
            doubleRotation( p, 0 );
    }
}

template <class tr>
bool Tree::isLeaf( node_type *p )
{
    return !p->sons[0] && !p->sons[1];
}

template <class tr>
void Tree::destroy( node_type* p )
{
    if( !p ) return;
    destroy(p->sons[0]);
    destroy(p->sons[1]);
    delete p;
}

template <class tr>
bool Tree::add( const data_type &obj )
{
    node_type **p;
    stack<node_type**> s;
    if( find(obj, p, s) ) return 0;
    (*p) = new node_type(obj);
    while( !s.empty() )
    {
        updateHeigh( *s.top() );
        if( !isBalanced( *s.top() ) ) balance(s.top());
        s.pop();
    }
    return 1;
}

template <class tr>
bool Tree::exists( const data_type &obj )
{
    node_type **p;
    return find(obj, p);
}

template <class tr>
bool Tree::erase( const data_type &obj )
{
    node_type** p;
    stack<node_type**> s;
    if( !find(obj, p, s) ) return 0;
    bool left = (*p)->sons[0];
    bool right = (*p)->sons[1];
    if( left && right)
    {
        node_type** q = &(*p)->sons[1];
        vector<node_type**> aux;
        while( (*q)->sons[0] )
        {
            aux.push_back(&(*q)->sons[0]);
            q = &(*q)->sons[0];
        }
        s.push(&(*q)->sons[1]);
        for( int i=0; i<aux.size(); ++i )
            s.push(aux[i]);
        node_type* qp = *q;
        if( *q == (*p)->sons[1] )
            q = &(*q)->sons[1];
        swap( (*p)->sons[0], qp->sons[0] );
        swap( (*p)->sons[1], qp->sons[1] );
        swap( *p, *q );
        swap(p,q);
        left = 0;
    }
    bool side = right;
    node_type* temp = *p;
    *p = (*p)->sons[side];
    delete temp;
    while( !s.empty() )
    {
        updateHeigh( *s.top() );
        if( !isBalanced( *s.top() ) ) balance(s.top());
        s.pop();
    }
    return 1;
}


template <class tr>
typename Tree::Iterator_inOrder Tree::inOrderBegin()
{
    node_type* p = root;
    stack<node_type*> s;
    if( !p ) return Iterator_inOrder();
    while( p->sons[0] )
    {
        s.push(p);
        p = p->sons[0];
    }
    return Iterator_inOrder(p, s);
}

template <class tr>
typename Tree::Iterator_inOrder Tree::inOrderEnd()
{
    return Iterator_inOrder();
}

template <class tr>
typename Tree::Iterator_postOrder Tree::postOrderBegin()
{
    node_type* p = root;
    stack<node_type*> s;
    if( !p ) return Iterator_postOrder();
    while( !isLeaf(p) )
    {
        s.push(p);
        if( p->sons[0] ) p = p->sons[0];
        else p = p->sons[1];
    }
    return Iterator_postOrder(p, s);
}

template <class tr>
typename Tree::Iterator_postOrder Tree::postOrderEnd()
{
    return Iterator_postOrder();
}

template <class tr>
typename Tree::Iterator_preOrder Tree::preOrderBegin()
{
    stack<node_type*> s;
    return Iterator_preOrder(root, s);
}

template <class tr>
typename Tree::Iterator_preOrder Tree::preOrderEnd()
{
    return Iterator_preOrder();
}

template <class tr>
typename Tree::iterator_inOrder Tree::find( const data_type &obj )
{
    node_type **p;
    stack<node_type*> s;
    find(obj, p, s);
    return Iterator_inOrder( *p, s );
}

//-------------------------------------------------------------
//                  ABSTRACT CLASS ITERATOR
//-------------------------------------------------------------

template <class tr>
Tree::Iterator::Iterator(): current(NULL)
{
    // Ctor Default
}

template <class tr>
Tree::Iterator::Iterator(node_type* _current, stack<node_type*> _prev): current(_current), prev(_prev)
{
    // Ctor Arguments
}

template <class tr>
Tree::Iterator::Iterator(const Iterator &it): current(it.current), prev(it.prev)
{
    // Cpy Ctor
}

template <class tr>
const typename Tree::Iterator& Tree::Iterator::operator=(const Tree::Iterator &it)
{
    current = it.current;
    prev = it.prev;
    return *this;
}

template <class tr>
bool Tree::Iterator::operator==(const Iterator &it)
{
    return current==it.current;
}

template <class tr>
bool Tree::Iterator::operator!=(const Iterator &it)
{
    return current!=it.current;
}

template <class tr>
typename Tree::data_type& Tree::Iterator::operator*()
{
    return current->data;
}

//-------------------------------------------------------------
//                  CLASS ITERATOR IN ORDER
//-------------------------------------------------------------

template <class tr>
Tree::Iterator_inOrder::Iterator_inOrder(): Iterator()
{
    // Ctor Default
}

template <class tr>
Tree::Iterator_inOrder::Iterator_inOrder(node_type* _current, stack<node_type*> _prev): Iterator(_current, _prev)
{
    // Ctor Arguments
}

template <class tr>
Tree::Iterator_inOrder::Iterator_inOrder(const Iterator_inOrder &it): Iterator(it)
{
    // Cpy Ctor
}

template <class tr>
typename Tree::Iterator_inOrder& Tree::Iterator_inOrder::operator++()
{
    if( this->current->sons[1] )
    {
        this->current = this->current->sons[1];
        while( this->current->sons[0] )
        {
            this->prev.push(this->current);
            this->current = this->current->sons[0];
        }
    }
    else
    {
        if( this->prev.empty() )
        {
            this->current = NULL;
            return *this;
        }
        this->current = this->prev.top();
        this->prev.pop();
    }
    return *this;
}

//-------------------------------------------------------------
//                  CLASS ITERATOR POST ORDER
//-------------------------------------------------------------

template <class tr>
Tree::Iterator_postOrder::Iterator_postOrder(): Iterator()
{
    // Ctor Default
}

template <class tr>
Tree::Iterator_postOrder::Iterator_postOrder(node_type* _current, stack<node_type*> _prev): Iterator(_current, _prev)
{
    // Ctor Arguments
}

template <class tr>
Tree::Iterator_postOrder::Iterator_postOrder(const Iterator_postOrder &it): Iterator(it)
{
    // Cpy Ctor
}

template <class tr>
typename Tree::Iterator_postOrder& Tree::Iterator_postOrder::operator++()
{
    if( this->prev.empty() )
    {
        this->current = NULL;
        return *this;
    }
    if( this->prev.top()->sons[1] && this->prev.top()->sons[1] != this->current )
    {
        this->current = this->prev.top()->sons[1];
        while( !isLeaf(this->current) )
        {
            this->prev.push(this->current);
            if( this->current->sons[0] ) this->current = this->current->sons[0];
            else this->current = this->current->sons[1];
        }
    }
    else
    {
        this->current = this->prev.top();
        this->prev.pop();
    }
    return *this;
}

//-------------------------------------------------------------
//                  CLASS ITERATOR PRE ORDER
//-------------------------------------------------------------

template <class tr>
Tree::Iterator_preOrder::Iterator_preOrder(): Iterator()
{
    // Ctor Default
}

template <class tr>
Tree::Iterator_preOrder::Iterator_preOrder(node_type* _current, stack<node_type*> _prev): Iterator(_current, _prev)
{
    // Ctor Arguments
}

template <class tr>
Tree::Iterator_preOrder::Iterator_preOrder(const Iterator_preOrder &it): Iterator(it)
{
    // Cpy Ctor
}

template <class tr>
typename Tree::Iterator_preOrder& Tree::Iterator_preOrder::operator++()
{
    if( this->current->sons[0] )
    {
        this->prev.push(this->current);
        this->current = this->current->sons[0];
    }
    else if( this->current->sons[1] )
    {
        this->prev.push(this->current);
        this->current = this->current->sons[1];
    }
    else
    {
        while( !this->prev.empty() && (!this->prev.top()->sons[1] || this->prev.top()->sons[1] == this->current) )
        {
            this->current = this->prev.top();
            this->prev.pop();

        }
        if( this->prev.empty() )
        {
            this->current = NULL;
            return *this;
        }
        this->current = this->prev.top()->sons[1];
    }
    return *this;
}



#undef Tree

#endif // AVLTREE_CPP_H
