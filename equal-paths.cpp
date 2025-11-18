#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
//Note: this code is adapted from bst.h. Like I mentioned there, I used https://www.youtube.com/watch?v=QfJsau0ItOY to understand the problem
int helperHeight(Node* node, bool& isBalanced){
    if (node == nullptr){
        return 0; // this node has a height of 0
    }
    int lHeight = helperHeight(node -> left, isBalanced);
    int rHeight = helperHeight(node -> right, isBalanced);

    //can only change isBalanced from false to true
    if ((lHeight != rHeight) && (node -> right != nullptr) && (node -> left != nullptr)){
        isBalanced = false; 
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

bool equalPaths(Node * root)
{
    // Add your code below
    

    bool isBalanced = true;
    helperHeight(root, isBalanced);
    return isBalanced;
    



}




