#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* top);
    void rotateRight(AVLNode<Key, Value>* top);
    void restructure(AVLNode<Key, Value>* node);
    int height(AVLNode<Key, Value>* start);
    void removeFix( AVLNode<Key,Value>* node, int diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO


    //case 1: no items in list:
    if (this -> root_ == nullptr){
        AVLNode<Key, Value>* nn = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        nn -> setBalance(0);
        nn-> setLeft(nullptr);
        nn -> setRight(nullptr);
        this -> root_ = nn;
        return;
    }
    //case 2: non-empty tree
    AVLNode<Key, Value>* pn = static_cast<AVLNode<Key, Value>*>(this->root_); //parent_node
    AVLNode<Key, Value>* cn = pn; //current_node
    bool isLeft = false;
    while (cn != nullptr){
        pn = cn;
        if (new_item.first > (cn -> getKey())){
            cn = cn -> getRight();
            isLeft = false;
        } else if (new_item.first < (cn -> getKey())){
            cn = cn -> getLeft();
            isLeft = true;
            int x =1;
        } else {
            cn -> setValue(new_item.second);
            return;            
        }
    }
    AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, pn);
    if (isLeft){
        pn -> setLeft(new_node);
    } else{
        pn -> setRight(new_node);
    }



    //now, we have inserted a new node to the bottom of our tree.

    new_node->setBalance(0);

    AVLNode<Key, Value>* update = new_node;
    while (update->getParent() != nullptr){
        AVLNode<Key, Value>* parent = update -> getParent();
        if (update == parent -> getLeft()){
            parent -> setBalance (parent->getBalance() -1);
        } else if (update == parent -> getRight()){
            parent -> setBalance (parent->getBalance() +1);
        }
        if (parent -> getBalance() == 0){
            break;
        }
        if ((parent -> getBalance() > 1) || (parent -> getBalance() < -1)){
            restructure(parent);
            break;
            
        }
        update = update-> getParent();
    }

}


template <class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* top){
    bool isLeft = false;
    if (top -> getParent() != nullptr){
        if (top == top-> getParent()-> getLeft()){
        isLeft = true;
        }
    }
    

    AVLNode<Key, Value>* child = top-> getLeft();

    top -> setLeft(child -> getRight());
    if (top -> getLeft() != nullptr){
        top-> getLeft()-> setParent(top);

    }
    child -> setRight(top); 
    child -> setParent(top-> getParent());
    if (child -> getParent()!= nullptr){
        if (isLeft){
            child -> getParent()-> setLeft(child);
        } else {
            child -> getParent()-> setRight(child);
        }
    }   
    top-> setParent(child);

    if (child -> getParent() == nullptr){
        this -> root_ = child;
    }
    // if (top -> getLeft() != nullptr){
    //     top -> getLeft() -> setParent(top);
    // }


    //the balance of each node is the diff between
    //its right and left subtrees heights

    top -> setBalance(height(top -> getRight()) - height(top-> getLeft()));
    child -> setBalance(height(child->getRight()) - height (child-> getLeft()));

}
template <class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* top){
    AVLNode<Key, Value>* child = top-> getRight();
    bool isLeft = false;
    if (top -> getParent() != nullptr){
        if (top == top-> getParent()-> getLeft()){
        isLeft = true;
        }
    }
    top-> setRight(child -> getLeft());
    if (top -> getRight() != nullptr){
        top-> getRight() -> setParent(top);
    }
    child-> setLeft(top);

    
    child -> setParent(top -> getParent());
    if (child -> getParent() != nullptr){
        if (isLeft){
            child -> getParent()-> setLeft(child);
        } else {
            child -> getParent()-> setRight(child);
        }
    }
    top-> setParent(child);
    if (child -> getParent() == nullptr){
        this -> root_ = child;
    }

    //the balance of each node is the diff between
    //its right and left subtrees heights

    top -> setBalance(height(top -> getRight()) - height(top-> getLeft()));
    child -> setBalance(height(child->getRight()) - height (child-> getLeft()));

}

template<class Key, class Value>
int AVLTree<Key, Value>:: height(AVLNode<Key, Value>* start){

    if (start == nullptr){
        return 0;
    }

    int lTree = height(start -> getLeft());
    int rTree = height (start -> getRight());

    return 1 + std::max(lTree, rTree);

}
template<class Key, class Value>
void AVLTree<Key, Value>:: restructure(AVLNode<Key, Value>* node){
  
    int pBalance = node -> getBalance();
    AVLNode<Key, Value>* child;
    int cBalance;
    if (pBalance < 0){
        cBalance = node -> getLeft()-> getBalance();
        child = node -> getLeft();
    } else if (pBalance > 0){
        cBalance = node -> getRight() -> getBalance();
        child = node -> getRight();
    }

    //at this point, we know the balances of the parent and child 
    //and we have pointers to the parent and child nodes



    if (pBalance * cBalance >= 0){ //both have the same sign, zig-zig rotation
        if (pBalance > 0){
            rotateLeft(node);
        } else if (pBalance < 0){
            rotateRight(node);
        }

    } else {    //child and parent have separate signs

        //first else-if statement: make rotations on child nodes
        if (cBalance > 0){ 
            rotateLeft(child);
            
        } else if (cBalance < 0){
            rotateRight(child);
        }

        //second else-if statement: make rotations on parent nodes
        if (pBalance > 0){
            rotateLeft(node);
        } else if (pBalance < 0){
            rotateRight(node);
        }

    }


}


template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //TODO

    AVLNode<Key, Value>* cn = static_cast<AVLNode<Key, Value>*>(this -> root_);
    while (cn != nullptr){
        if (key > cn -> getKey()){
            cn = cn-> getRight();
        } else if (key < cn -> getKey()){
            cn = cn -> getLeft();
        } else {
            break;
        }
    }
    if (cn == nullptr){ //key not found in tree
        return;
    }


    //At this point, the key was found in the tree and cn points to this node

    //Case 1: this node has two children:
    AVLNode<Key, Value>* swap = cn;
    if ((cn -> getRight() != nullptr) && (cn -> getLeft() != nullptr)){
        swap = cn -> getLeft();
        while (swap -> getRight() != nullptr){
            swap = swap -> getRight();
        }
    }

    //if cn has two children, swap holds its predecessor. otherwise, swap == cn

    if (swap != cn){
        // if (cn == this -> root_){
        //     this -> root_ = swap;
        // }
        int diff;
        bool prevRoot = (cn == this -> root_);
        nodeSwap(cn, swap);
        if (prevRoot){
            this -> root_ = swap;
        }
        AVLNode<Key, Value>* parent = cn -> getParent();
        if (cn == parent -> getRight()){
            parent -> setRight(nullptr);
            delete cn;
           diff= -1;
        } else {
            parent -> setLeft(nullptr);
            delete cn;
            diff = 1;
        }

        removeFix(parent, diff);
        return;
    } else { //Case 2: cn has either 1 or 0 children

        AVLNode<Key, Value>* child  = nullptr;
        if (cn -> getLeft() != nullptr){
            child = cn -> getLeft();
        } else if (cn -> getRight() != nullptr){
            child = cn -> getRight();
        }

        int diff = 0;
        AVLNode<Key, Value>* parent = cn -> getParent();

        if (parent != nullptr){ //cn is NOT the first node
            if (cn == parent -> getLeft()){
                parent -> setLeft(child);
                if (child != nullptr){
                    child -> setParent(parent);
                }
                diff = 1; 
            } else {
                parent -> setRight(child);
                if (child != nullptr){
                    child -> setParent(parent);
                }
                diff = -1;
            }
            delete cn;
            // if (parent != nullptr){
                removeFix(parent, diff);
            
        } else { //cn is the first node of the tree
            if (child == nullptr){ //cn is the only node
                delete cn;
                this -> root_ = nullptr;
                return;
            } else{ // child will be the only node
                this -> root_ = child;
                child -> setParent(nullptr);
                delete cn;
                return;
            }


        }
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix( AVLNode<Key,Value>* node, int diff){
    if (node == nullptr){
        return;
    }
    AVLNode<Key, Value>* parent = node -> getParent();
    int ndiff = 0;
    if (parent != nullptr){
        if (parent -> getLeft() == node){
            ndiff = 1; //left child
        } else {
            ndiff = -1; //right child
        }
    }
    if ((node -> getBalance() + diff ==-2 )||(node -> getBalance() + diff == 2 )){ //Case 1:
        AVLNode<Key,Value>* c;
        bool rRot = false;
        if (node -> getBalance() + diff ==-2){   //requires right rotations
            c = node -> getLeft();
            rRot = true;
        }  else {                               //requires left rotations
            c = node -> getRight();
        }
        

      
        //Case 1a:
        if ((c -> getBalance() == -1 && rRot)|| (c-> getBalance() ==1 && !rRot)){
            if (rRot){ //right rotation
                rotateRight(node);
            } else {             //left rotation
                rotateLeft(node);
            }
            node -> setBalance(0);
            c -> setBalance(0);
            // if (parent != nullptr){
                removeFix(parent, ndiff );

            

        //Case 1b:
        } else if (c -> getBalance() == 0){

            if (rRot){ //right rotation
                rotateRight(node);
                node -> setBalance(-1);
                c -> setBalance(1);
            } else{  //left rotation
                rotateLeft(node);
                node -> setBalance(1);
                c -> setBalance(-1);
            }
            return;

        //Case 1c:
        } else if ((c -> getBalance() == 1 && rRot) || (c->getBalance() == -1 && !rRot)){
            AVLNode<Key, Value>* g;
            if (rRot){  //right rotation
                g = c -> getRight();
                rotateLeft(c);
                rotateRight(node);
                if (g== nullptr){
                    return;
                }
                if (g -> getBalance() ==1 ){
                    node -> setBalance(0);
                    c -> setBalance(-1);
                    // g -> setBalance(0);
                } else if (g -> getBalance() == 0){
                    node -> setBalance(0);
                    c -> setBalance(0);
                    // g -> setBalance(0);
                } else if (g -> getBalance() == -1){
                    node -> setBalance(1);
                    c -> setBalance(0);
                    // g -> setBalance(0);
                }
                g -> setBalance(0);
            }else{  //left rotation
                g = c -> getLeft();
                rotateRight(c);
                rotateLeft(node);
                if (g -> getBalance() ==1 ){
                    node -> setBalance(0); //og = 0
                    c -> setBalance(1); //og = 1
                    g -> setBalance(0);
                } else if (g -> getBalance() == 0){
                    node -> setBalance(0);
                    c -> setBalance(0);
                    g -> setBalance(0);
                } else if (g -> getBalance() == -1){
                    node -> setBalance(-1); //og = -1
                    c -> setBalance(0); //og =0
                    g -> setBalance(0); //og = 0
                }
            }
            removeFix(parent, ndiff);
        }

    } else if (node -> getBalance()  + diff == -1 || node -> getBalance() + diff == 1){ //Case 2
        if (node -> getBalance() == 1){
            node -> setBalance(1);
        }else {
            node -> setBalance(-1);
        }
        return;
    } else if (node -> getBalance() + diff == 0){ //Case 3
        node -> setBalance(0);
        removeFix(parent, ndiff);   
        return;
    }

 }


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
