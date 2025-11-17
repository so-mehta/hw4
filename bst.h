#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <queue>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static int helperHeight(Node<Key, Value>* node, bool& isBalanced);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_== rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;



    
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_ == nullptr){ //end of binary tree, must return NULL iterator
        return *this;
    }

    
    Node<Key, Value>* new_node = current_;

        /* if starting at a parent, must visit leftmost 
            node of right subtree. If no children, and 
            is the left child of their parent, must visit
            parent. if no children and is the right child of 
            parent, must go up until reaches ancestor that either 
            doesn't have a parent or is the left child of parent
            -- visit this parent. 


            */



    if (new_node-> getRight() != nullptr){
        new_node = new_node -> getRight();
        while (new_node -> getLeft() != nullptr){
            new_node = new_node-> getLeft();
        }

        current_ = new_node;
        return *this;
    }

    if (new_node -> getParent() != nullptr){
        if (new_node  == new_node -> getParent()-> getLeft()){ //this node doesn't have a right child and is the left child of parent
            current_ = new_node -> getParent();
            return *this;
        }



        else if (new_node == new_node -> getParent() -> getRight()){
            if (new_node -> getParent() -> getParent() == nullptr){
                current_ = nullptr;
                return *this;
            } else {
                Node<Key, Value>* parent = new_node -> getParent();
                while (new_node == parent -> getRight()){
                    new_node = parent;
                    if (parent -> getParent() == nullptr){
                        current_ = nullptr;
                        return *this;
                    }
                    parent = parent-> getParent();
                }
                current_ = parent;
                return *this;

            }
        }
    }













    


}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO

    root_ = nullptr;

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

   if (root_ == nullptr){
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        root_ = newNode;
        return;
   }

   //now, must traverse list.

   Node<Key, Value>* current_node = root_;
   Node<Key, Value>* parent_node;
   bool isLeft = false;
   while (current_node != nullptr){

            parent_node = current_node;
        if (keyValuePair.first == current_node->getKey()){
            //need to replace this item;
           
            current_node->setValue(keyValuePair.second);
            return;
        } 

        if (keyValuePair.first < current_node->getKey()){
            current_node = current_node ->getLeft();
            isLeft = true;
        } else {
            current_node = current_node ->getRight();
            // parent_node = current_node->getParent();
            isLeft = false;
        }

   }
   Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent_node);
   if (isLeft){
        parent_node->setLeft(newNode);
   } else {
        parent_node-> setRight(newNode);
   }
   return;

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* curr_node = root_;

    //the following while loop searches the tree, finds the node that matches the key
    while (curr_node != nullptr){
        if (key > curr_node -> getKey()){
            curr_node = curr_node-> getRight();
        } else if (key < curr_node -> getKey()){
            curr_node = curr_node -> getLeft();
        } else {
            break;
        }
    }

    if (curr_node == nullptr){ //key not found in tree
        return;
    }

    //curr_node now holds the value with the key
    Node<Key, Value>* swap_node = curr_node;


    //if curr_node has two children, this code finds curr_node's predecessor
    if ((curr_node -> getRight() != nullptr) && (curr_node -> getLeft() != nullptr)){ //two children
        swap_node= curr_node-> getLeft();

        while (swap_node -> getRight()!= nullptr){
            swap_node = swap_node-> getRight();
        }
        //swap_node holds the predecessor
    }

    //if the node we want to swap has two children, then 
    //swap node contains the predecessor. Else, swap_node
    //just contains the original curr_node



    if (swap_node != curr_node){ //curr_node has two children
        nodeSwap(curr_node, swap_node);
        
        //case 1: the predecessor had one left child
        bool isLeft = false;
        if (curr_node == curr_node-> getParent()-> getLeft()){
            isLeft = true;
        }


        if (curr_node -> getLeft() != nullptr){
            Node <Key, Value>* lchild = curr_node-> getLeft();
            if (isLeft){
                curr_node -> getParent() -> setLeft(lchild);
                lchild -> setParent(curr_node-> getParent());
            } else {
                curr_node -> getParent()-> setRight(lchild);
                lchild-> setParent(curr_node-> getParent());
            }
            delete curr_node;
            
        } else { //case 2: the predecessor has no children
            if (isLeft){
                curr_node-> getParent()-> setLeft(nullptr);
            } else {
                curr_node -> getParent()-> setRight(nullptr);
            }
            
            delete curr_node;
            // return;
        }

        if (swap_node -> getParent() == nullptr){
            root_ = swap_node;
        }
        return;

    }   else { //original curr_node has one or zero children

        //case 1: curr_node has no parent
        if (curr_node -> getParent() == nullptr){
            if (curr_node -> getLeft()!= nullptr){
                root_ = curr_node -> getLeft();
                curr_node -> getLeft()-> setParent(nullptr);
            } else if (curr_node -> getRight() != nullptr){
                root_ = curr_node -> getRight();
                curr_node -> getRight()-> setParent(nullptr);
            } else {
                root_ = nullptr;
            }
            delete curr_node;
            return;
        }

        //case 2: curr_node has one or no child and a parent

        bool isLeft = false;
        if (curr_node == curr_node-> getParent()-> getLeft()){
            isLeft = true;
        } else {
            isLeft = false;
        }
    

       if (curr_node -> getLeft() != nullptr){
            if (isLeft){
                curr_node -> getParent() -> setLeft(curr_node-> getLeft());
                curr_node -> getLeft()->setParent(curr_node->getParent());
                delete curr_node;
                return;
            } else {
                curr_node -> getParent()-> setRight(curr_node->getLeft());
                curr_node-> getLeft()-> setParent(curr_node-> getParent());
                delete curr_node;
                return;
            }



        } else if (curr_node -> getRight()!= nullptr){
            if (isLeft){
                curr_node -> getParent() -> setLeft(curr_node-> getRight());   
                curr_node -> getRight()->setParent(curr_node->getParent());
                delete curr_node;
                return;
            } else {
                curr_node -> getParent()-> setRight(curr_node->getRight());
                curr_node-> getRight()-> setParent(curr_node-> getParent());
                delete curr_node;
                return;

            }
        }


        //final case: curr_node has no children

        if (isLeft){
            curr_node-> getParent()->setLeft(nullptr);
        } else {
            curr_node-> getParent()-> setRight(nullptr);
        }
        delete curr_node;
        return;
    }


}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO


    Node<Key, Value>* cn = current;
    if (cn == nullptr){
        return nullptr;
    }
    cn = cn -> getLeft();
    while (cn -> getRight()!= nullptr){
        cn = cn-> getRight();
    }
    return cn;

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    if (root_ == nullptr){
        return;
    }
    std::queue<Node<Key, Value>*> tree;
    tree.push(root_);
    while (!(tree.empty())){
        Node<Key,Value>* cn = tree.front();
        if (cn -> getLeft() != nullptr){
            tree.push(cn-> getLeft());
        } 
        if (cn -> getRight() != nullptr){
            tree.push(cn-> getRight());
        }
        tree.pop();
        delete cn;
        
    }
    root_ = nullptr;

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

    if (root_ == nullptr){
        return nullptr;
    }
    Node<Key, Value>* cn = root_;
    while (cn-> getLeft()!= nullptr){
        cn = cn-> getLeft();
    }
    return cn;

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* cn = root_;
    if (root_ == nullptr){
        return nullptr;
    }


    while (cn != nullptr){
        if (key > cn-> getKey()){
            cn = cn-> getRight();
        } else if (key < cn -> getKey()){
            cn = cn-> getLeft();
        } else {
            return cn;
        }
    }
    return nullptr;


}

/**
 * Return true iff the BST is balanced.
 */

 //Note: watched https://www.youtube.com/watch?v=QfJsau0ItOY to get an idea of how to approach this function
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    
    bool isBalanced = true;
    helperHeight(root_, isBalanced);
    return isBalanced;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::helperHeight(Node<Key, Value>* node, bool& isBalanced){
    if (node == nullptr){
        return 0; // this node has a height of 0
    }
    int lHeight = helperHeight(node -> getLeft(), isBalanced);
    int rHeight = helperHeight(node -> getRight(), isBalanced);


    if (((lHeight - rHeight) >= 2) || ((lHeight - rHeight) <= -2)){
        isBalanced = false; //violates property that diff in heights must be at most 1
    }
    int max;
    if (lHeight > rHeight){
        max = lHeight;
    } else if (rHeight > lHeight){
        max = rHeight;
    } else {
        max = lHeight;
    }
    return max + 1;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
