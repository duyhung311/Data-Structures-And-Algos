#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <sstream>
#include <fstream>


using namespace std;

template <class K, class V>
class BKUTree {
public:
    class AVLTree;
    class SplayTree;

    class Entry {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree* avl;
    SplayTree* splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5)
    {
        avl = new AVLTree();
        splay = new SplayTree();
    }
    ~BKUTree() { this-> clear(); }

    void add(K key, V value){
        
        if(int(keys.size()) >= maxNumOfKeys) {
            keys.pop();
        }
        keys.push(key);
        // do same as above with splay too
        
        avl->add(key, value);
        splay->add(key,value);
        return;
    }
    string inOrderPrint(){
        return avl->inOrder(this->avl);
    }
    void remove(K key){
        queue<K> resv;
        while (!keys.empty())
        {
            K data  = keys.front();
            if (key != data)
                resv.push(data);
            keys.pop();
        }
        keys = resv;
        avl->remove(key);
        splay->remove(key);
        K splayRootKey = splay->root->entry->key;
        if(int(keys.size()) >= maxNumOfKeys)
            keys.pop();
        keys.push(splayRootKey);
        return;
    }
    V search(K key, vector<K>& traversedList){\
        // 1. check splay's root
        if (key == splay->root->entry->key)
            return splay->root->entry->value;
        // 2. find in queue
        if(searchInQueue(key)){
            if(keys.size()>= maxNumOfKeys)
                keys.pop();
            keys.push(key);
        }
        splay->search(key); // this search have to include splaying

         //find in splay tree and perform splay
        //return avl->search(key); 

        //find in splay tree first
            // + if node is root of splay tree return that root->entry->value
            // + then in queue, if key is in the queue AND perform splay at found node
            // + else search on avl tree
        //if(splay->root == nullptr || splay->root->entry == nullptr || splay->root == nullptr||
            //avl->root == nullptr || avl->root->entry == nullptr|| avl->root == nullptr) throw exception_ptr();
            
        //if(splay->root->entry->key ==  key) return splay->root->entry->key;
        
    }
    bool searchInQueue(K key){
        if(keys.empty()) return false;
        queue<K> resv;
        bool flag = false;
        while(!keys.empty()){
            K data = keys.front();
            if( data == key){
                flag = true;
            }
            resv.push(data);
            keys.pop();
        }
        keys = resv;
         return flag;
    }
    void printBT(){
        //splay->printBT("", splay->root, false);
        avl->printBT("", avl->root, false);
        return;
    }
    void traverseNLROnAVL(void (*func)(K key, V value)){
        avl->traverseNLR(func);
        return;
    }
    void traverseNLROnSplay(void (*func)(K key, V value)){
        splay->traverseNLR(func);
        return;
    }

    void clear(){
        avl->clear();
        splay->clear();
        while (!keys.empty())
          keys.pop();
        return;
    }

    class SplayTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            typename AVLTree::Node* corr; 
            friend class BKUTree;
            friend class AVLTree;
            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
        };

    public:
        Node* root;

        SplayTree(): root(NULL) {};
        ~SplayTree() {this->clear();};
        
        void add(K key, V value);
        void add(Entry* entry);
        Node* mypreadd(Entry* entry);
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));
        void clear();
        // my helping functions for splay tree
        Node* myAdd(Node* toIns, Node* pR, int & relativeHeight);
         Node* splay(Node* pR, K key, int& dist);
        Node* mySplay(Node* pR, K key, int& dist);
        Node* insert(Node* root, Entry* entry);
        Node* splay(Node* root, K key);
        Node* zig(Node* root);
        Node* zag(Node* root);
        void mySplayClearAll( Node* pR);
        Node* splayNodeToDel(Node* pR, K key, int& dist );
        void deleteNode(K key);
        
    };

    class AVLTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            int balance;
            typename SplayTree::Node* corr;
            friend class BKUTree;
            friend class SplayTree;
            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
        };

    public:
        Node* root;
        AVLTree(): root(NULL) {};
        ~AVLTree() { this->clear(); };
        void add(K key, V value){
            this->root = insert(root, key, value);
            return;
        }
        void add(Entry* entry);
        void remove(K key){
            deleteNode(this->root, key);
            return;
        }
        V search(K key){
            return search(this->root, key);
        }

        void traverseNLR(void (*func)(K key, V value));// done
    
        void clear(){
            myAVLClearAll(root);
            return;
        }
        // my helping functions for avl tree
        
        
        string inOrderRec(Node* root) {
            stringstream ss;
            if (root != nullptr) {
                ss << inOrderRec(root->left);
                ss << root->entry->value << " ";
                ss << inOrderRec(root->right);
            }
            return ss.str();
        }
        void myAVLClearAll(Node* pR);
        Node* insert(Node* root, K  key, V value);
        Node* deleteNode(Node* root, K key);
        int difference(Node* root);
        int height(Node* root);
        Node* balance(Node* root);
        Node* ll_rot(Node* root);
        Node* rr_rot(Node* root);
        Node* lr_rot(Node* root);
        Node* rl_rot(Node* root);
        V    search(Node* root, K key);
        Node* searchForNode(K key, Node* pR);
        string inOrder(AVLTree* avl){
            return inOrderRec(avl->root);
        }

    };
};
/*************************************************************************************************
*                                                                                                *
*                                    AVL TREE                                                    *
*                                                                                                *
*************************************************************************************************/
template <class K, class V>
void BKUTree <K,V>::AVLTree::traverseNLR(void (*func)(K key, V value)){
    function<void(void (*)(K, V), Node *)> recursiveNLR = [&](void (*func)(K, V), Node *pR) {
    if (pR == nullptr)
      return;

    (*func)(pR->entry->key, pR->entry->value);

    if (pR->left != nullptr)
      recursiveNLR(func, pR->left);
    if (pR->right != nullptr)
      recursiveNLR(func, pR->right);
    };

    recursiveNLR(func, root);
    return;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::insert(Node* root, K key, V value){
    if(root!= nullptr && root->entry != nullptr && root->entry->key == key) throw "Duplicate key";
    if(root == nullptr) {
        root = new Node(new Entry(key,value), nullptr,nullptr); 
        return root;
    }
    if(key < root->entry->key) {
        root->left = insert(root->left, key,value);
        root = balance(root);
        return root;
    }
    else {
        root->right = insert(root->right,key,value);
        root = balance(root);
        return root;
    }
    
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::deleteNode(Node* root, K key){
        if(root == NULL)
            throw "Not found";
        if(key < root->entry->key){
            root->left = deleteNode(root->left,key);
        }
            
        else if(key > root->entry->key){
            root->right = deleteNode(root->right,key);
        }
        
        else {
            // 1 child // 0 child
            if (root->left == nullptr && root->right == nullptr) { // 0 child
                delete root;
                root = NULL;
            }
            else if(root->left == nullptr && root->right!= nullptr){ // 1 right child
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if(root->right == nullptr && root->left!= nullptr){
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else{
                Node* toDel = root->right;
                while(toDel!=NULL && toDel->left != nullptr)
                   toDel = toDel->left;

                
                root->entry->key = toDel->entry->key;
                root->entry->value = toDel->entry->value;
                //delete toDel;

                root->right = deleteNode(root->right,toDel->entry->key);
            }
            
        }
        return root;
}

template <class K, class V>
void BKUTree<K,V>::AVLTree::myAVLClearAll(Node* pR){
    if(!(pR == nullptr)){
      myAVLClearAll(pR->right);
      myAVLClearAll(pR->left);
      delete pR->entry;
      if (pR == root)
        root = nullptr;
      pR->left = nullptr;
      pR->right = nullptr;
      delete pR;
    }
    return;
}

template <class K, class V>
int  BKUTree<K,V>::AVLTree::height(Node* root){
    int h = 0;
   if (root != NULL) {
      int l_height = height(root->left);
      int r_height = height(root->right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}

template <class K, class V>
int BKUTree<K,V>::AVLTree::difference(Node* root){
    int l_height = height(root->left);
   int r_height = height(root->right);
   int b_factor = l_height - r_height;
   return b_factor;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::balance(Node* root) {
   int bal_factor = difference(root);
   if (bal_factor > 1) {
      if (difference(root->left) > 0)
         root = ll_rot(root);
      else
         root = lr_rot(root);
   } else if (bal_factor < -1) {
      if (difference(root->right) > 0)
         root = rl_rot(root);
      else
         root = rr_rot(root);
   }
   return root;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::ll_rot(Node* root){
    Node* tmp;
    tmp = root->left;
    root->left =  tmp->right;
    tmp->right = root;
    return tmp;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::rr_rot(Node* root){
    Node* tmp;
    tmp = root->right;
    root->right =  tmp->left;
    tmp->left = root;
    return tmp;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::lr_rot(Node* root){
    Node* tmp;
    tmp = root->left;
    root->left = rr_rot(tmp);
    return ll_rot(root);
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::rl_rot(Node* root){
    Node* tmp;
    tmp = root->right;
    root->right = ll_rot(tmp);
    return rr_rot(root);
}

template <class K, class V>
V BKUTree<K,V>::AVLTree::search(Node* root,K key){
    return searchForNode(key, root)->entry->key;
}

template <class K, class V>
typename BKUTree<K,V>::AVLTree::Node* BKUTree<K,V>::AVLTree::searchForNode(K key, Node* pR){
    
    if (pR == nullptr)
        throw "Not found";
    if(pR->entry->key == key) 
        return pR;
    if(key < pR->entry->key) 
        return searchForNode(key, pR->left);
    if (key > pR->entry->key  )
        return searchForNode(key, pR->right);
    return pR;

}

/*************************************************************************************************
*                                                                                                *
*                                   SPLAY TREE                                                   *
*                                                                                                *
*************************************************************************************************/
template <class K, class V>
void BKUTree<K,V>::SplayTree::remove(K key){
     deleteNode(key);
     return;
}

template <class K, class V>
typename BKUTree<K,V>::SplayTree::Node* BKUTree<K,V>::SplayTree::splayNodeToDel(Node* pR, K key, int& dist){
    if (pR == nullptr)
    throw "Not found";
    if (key == pR->entry->key)
    {
         dist = 1;
        return pR;
    }
    if(key < pR->entry->key)
        pR->left = splayNodeToDel(pR->left, key, dist);
    if(key > pR->entry->key)
        pR->right = splayNodeToDel(pR->right, key, dist);
    if(pR == root && dist == 1){
        if(key < pR->entry->key)
            return zig(pR);
        if(key > pR->entry->key)
            return zag(pR);
    }
    else if(dist == 2){
        dist = 1;
        if(key > pR->entry->key){ // zag
            if(key < pR->right->entry->key){ // zag zig
                pR->right = zig(pR->right);
                return zag(pR);
            }

             if(key > pR->right->entry->key){// zag zag
                Node* temp = zag(pR);
                return zag(temp);
            }
            
        }      
        if(key < pR->entry->key){// zig
            if(key > pR->left->entry->key){
                pR->left = zag(pR->left); // zig zag
                return zig(pR);
            }
            if(key < pR->left->entry->key){// zig zig
                Node* temp = zig(pR);
                return zig(temp);
            }
            
        }
    }
    else{
        dist++;
        return pR;
    }
    return pR;
}

template <class K, class V>
void BKUTree<K,V>::SplayTree::deleteNode(K key){
    int dist = 0;
    root = splayNodeToDel(root,key, dist);

    if( root->right == nullptr){
        Node* tmp = root;
        root = root->left;
        delete tmp->entry;
        delete tmp;
    }
    else if(root->left == nullptr){
        Node* tmp = root;
        root = root->right;
        delete tmp->entry;
        delete tmp;
    }
    else{
            dist = 0;
            Node* nodeToBeRoot = root->left;
            while(nodeToBeRoot->right != nullptr){
                nodeToBeRoot = nodeToBeRoot->right;
            }
            K resvKey = nodeToBeRoot->entry->key;
            Node* resvRoot = root;
            root = root->left;
            root = splayNodeToDel(root, resvKey, dist);
            root->right = resvRoot->right;
            delete resvRoot->entry;
            delete resvRoot; 
    }
    return;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::clear(){
    mySplayClearAll(this->root);
    return;
}

template <class K, class V>
void BKUTree<K, V>::SplayTree::mySplayClearAll(Node* pR){
    if(!(pR == nullptr)){
        mySplayClearAll(pR->right);
        mySplayClearAll(pR->left);
        
        if (pR == root)
            root = nullptr;
        pR->left = nullptr;
        pR->right = nullptr;
        if(pR == root ) root = nullptr;
        delete pR;
    }
    return;
}



template <class K, class V>
V BKUTree<K,V>::SplayTree::search(K key){
    int dist = 0;
    
    root = splayNodeToDel(root,key,dist);
    return root->entry->value;
}

/***********************************************
*                SEARCH !!!                    *
************************************************/
template <class K, class V>
void BKUTree<K, V>::SplayTree::traverseNLR(void (*func)(K, V)){
    function<void(void (*)(K, V), Node *)> recursiveNLR = [&](void (*func)(K, V), Node *pR) {
    if (pR == nullptr)
      return;

    (*func)(pR->entry->key, pR->entry->value);

    if (pR->left != nullptr)
      recursiveNLR(func, pR->left);
    if (pR->right != nullptr)
      recursiveNLR(func, pR->right);
    };
    recursiveNLR(func, root);
    return;
}

template <class K, class V>
void BKUTree<K,V>::SplayTree::add(K key, V value){
    Entry* newEntry = new Entry(key,value);
    mypreadd(newEntry);
    return;
}

template <class K, class V>
typename BKUTree<K,V>::SplayTree::Node* BKUTree<K,V>::SplayTree::zig(Node* root){
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp; // zig is right rotate
}
template <class K, class V>
typename BKUTree<K,V>::SplayTree::Node*  BKUTree<K,V>::SplayTree::zag(Node* root){
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}   


template <class K,class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::myAdd(Node* toIns, Node* pR, int & relativeHeight){
    if(pR == nullptr){
        relativeHeight = 1;
        return toIns;
    }
    if(toIns->entry->key == pR->entry->key) throw "Duplicate key";
    if(toIns->entry->key < pR->entry->key) 
        pR->left = myAdd(toIns, pR->left, relativeHeight);
    if(toIns->entry->key > pR->entry->key)
        pR->right = myAdd(toIns,pR->right, relativeHeight);
    
    if(pR == root && relativeHeight == 1){
        if(toIns->entry->key < pR->entry->key)
            return zig(pR);
        if(toIns->entry->key > pR->entry->key)
            return zag(pR);
    }
    else if( relativeHeight == 2){
        relativeHeight = 1;
        if(toIns->entry->key < pR->entry->key){// zig first then...
            if(toIns->entry->key < pR->left->entry->key){
                // then zig again
                Node* temp = zig(pR);
                return zig(temp);
            }
            if (toIns->entry->key > pR->left->entry->key){
                //then zag
                pR->left = zag(pR->left);
                return zig(pR);
            }
        } 
        else if(toIns->entry->key > pR->entry->key){// zag first then...
            if(toIns->entry->key < pR->right->entry->key){
                // then zig again
                pR->right = zig(pR->right);
                return zag(pR);
            }
            if (toIns->entry->key > pR->right->entry->key){
                //then zag
                Node* temp = zag(pR);
                return zag(temp);
            }
        } 
    }
    else if(relativeHeight ==1){
        relativeHeight +=1;
        return pR;
    }
    return pR;
}


template <class K, class V>
typename BKUTree<K, V>::SplayTree::Node *BKUTree<K, V>::SplayTree::mypreadd(Entry *entry)
{
  Node *newNode = new Node(entry);
  int i = 0;
  root = myAdd(newNode, root, i);
  return newNode;
}

