/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 * Author: LTSACH
 *
 * Created on 12 September 2020, 17:11
 */

#ifndef AVL_H
#define AVL_H
#include "BST.h"
#include "list/DLinkedList.h"
#include "stacknqueue/Queue.h"

#define XNode typename BST<K,V>::Node


template<class K, class V>
class AVL : public BST<K,V>{
public:
    void add(K key, V value=0){
        this->pRoot = add(this->pRoot, new XNode(typename BST<K,V>::Entry(key, value)));
        this->count += 1;
    }
    V remove(K key, bool* success=0){
        V retValue = 0; //O: NULL
        bool success_;
        this->pRoot = remove(this->pRoot, key, success_, retValue);
        if(success_) this->count -= 1;
        if(success != 0) *success = success_;
        
        return retValue;
    }
    int height(){
        if(this->pRoot == 0) return 0;
        return this->pRoot->height();
    }
    void println(string (*entry2str)(K&,V&)=0){
        cout << "Tree height: " << this->height() << endl;
        cout << "Tree nodes:"  << endl;
        cout << this->toString(entry2str, true) << endl;
    }
    /*
     * bfactor: designed for being used to test AVL tree
     *          so, maybe not useful for real application
     * It returns a list of balance factor (string) of nodes visited with BFS-traversal
     * (see AVLTest for example)
     */
    DLinkedList<string> bfactor(){
        DLinkedList<string> list;
        if(this->pRoot == 0) return list;
        
        Queue<XNode*> queue;
        queue.push(this->pRoot);
        while(!queue.empty()){
            XNode* pNode = queue.pop();
            if(pNode->bfactor == nEMPTY) list.add("EMPTY");
            else if(pNode->bfactor == nLH) list.add("LH");
            else if(pNode->bfactor == nEH) list.add("EH");
            else list.add("RH");
            
            if(pNode->bfactor == nEMPTY){
                delete pNode; //because alloc in [1] or [2]
                continue;
            } 
            if((pNode->pLeft == 0) && (pNode->pRight == 0) ) continue;
            
            if(pNode->pLeft != 0) queue.push(pNode->pLeft);
            else queue.push(new XNode()); //[1]
            if(pNode->pRight != 0) queue.push(pNode->pRight);
            else queue.push(new XNode()); //[2]
        }
        return list;
    }
private:
    /*
     Current tree:
                    45
                   /  \
                 33    72
                      /  \
                     55  84

    Adding 75:
                    45    : RH of RH
                   /  \
                 33    72
                      /  \
                     55  84
                        /
                       75    
     
    rotateLeft(at 45):
                    72
                   /  \
                 45    84
                / \    /
              33  55  75        
    
     */
    XNode* rotateLeft(XNode* root){
        //YOUR CODE HERE
        XNode* tmp;
        tmp = root->pRight;
        root->pRight =  tmp->pLeft;
        tmp->pLeft = root;
        root->updateHeight();
        tmp->updateHeight();
        return tmp;
    }
    
    /*
    Current tree:
                45
               /  \
             33    72
            /  \
          24    40
    
    Adding 15:
                45    : LH of LH => Rotate right
               /  \
             33    72
            /  \
          24    40
         /
       15     
    rotateRight(at 45):
             33
            /  \
          24    45
         /     /  \
       15     40   72
     *     
     */
    XNode* rotateRight(XNode* root){
        //YOUR CODE HERE
        XNode* tmp;
        tmp = root->pLeft; // b
        root->pLeft =  tmp->pRight; //d
        tmp->pRight = root;
        root->updateHeight();
        tmp->updateHeight();
        return tmp;
    }

    XNode* rebalance(XNode* root){
        //YOUR CODE HERE
        if(root == nullptr) return root;
        root->updateHeight();
        if(root->isBalanced()) return root;
        XNode* ptr = root;
        if(root->isLH()){
            XNode* leftTree = root->pLeft;
            if(leftTree->isRH())  
                root->pLeft = rotateLeft(root->pLeft);
            ptr = rotateRight(root);
        }
        else if(root->isRH()){
            XNode* rightTree = root->pRight;
            if(rightTree->isLH())  
                root->pRight = rotateRight(root->pRight);
            ptr = rotateLeft(root);
        }
        return ptr;
    }

    XNode* add(XNode* root, XNode* newNode){
        //YOUR CODE HERE
        if(root == 0) return newNode;
        if(newNode->data.key < root->data.key)
            root->pLeft = add(root->pLeft, newNode);
        else
            root->pRight = add(root->pRight, newNode);
        return rebalance(root);
    }

    
    XNode* remove(XNode* root, K key, bool& success, V& retValue){
        //YOUR CODE HERE
        if(root == 0){
            success = false;
            return 0;
        }
        XNode* ptr = root;
        if(key < root->data.key)
            root->pLeft = remove(root->pLeft, key, success, retValue);
        else if(key > root->data.key){
            root->pRight = remove(root->pRight, key, success, retValue);
        }
        else{
            if(root->pLeft == 0 || root->pRight == 0){
                ptr = (root->pLeft==0)? root->pRight: root->pLeft;
                success = true;
                retValue = root->data.value;
                root->data.value = 0;
                delete root;
            }
            else{
                V temp = root->data.value;
                XNode* maxLeft = root->pLeft;
                while(maxLeft->pRight != 0) maxLeft = maxLeft->pRight;
                root->data=maxLeft->data;
                root->pLeft = remove(root->pLeft, maxLeft->data.key, success, retValue);
                success = true;
                retValue = temp;
            }
        }
        return rebalance(ptr);
    }
};


#endif /* AVL_H */

