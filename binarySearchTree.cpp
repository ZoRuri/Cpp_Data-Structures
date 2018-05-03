#include <iostream>

template <typename T>
class BinarySearchTree;

template <typename NodeType>
class Node {
	public:
	    friend class BinarySearchTree<NodeType>;
	private:
		NodeType		data;
		Node<NodeType>	*left;
		Node<NodeType>	*right;
        
        int getDegree() { 
            int degree = 0;
        
            if ( this->left != nullptr ) ++degree;
            if ( this->right != nullptr ) ++degree;
       
            return degree;
        }
};

template <typename T>
class BinarySearchTree {
    public:
        BinarySearchTree() { 
            this->rootNode = nullptr; 
            this->elementCount = 0;
        };
    
        Node<T> *getRoot() { return this->rootNode; }
        void insert(T data);
        void remove(T data);
        bool find(T data);
        
        void preorderTraversal();
        void inorderTraversal();
        void postorderTraversal();
    
        int length() { return this->elementCount; };
            
        ~BinarySearchTree() {};
    
    private:  
        Node<T> *rootNode;
        bool insertNode(Node<T> *insertNode, T data);
        Node<T> *findNode(Node<T> *compareNode, T data);
        Node<T> *findNode(Node<T> *compareNode, T data, Node<T> **parrentNode);    // for save parrentNode

        void preorderTraversalRecursive(Node<T> *currentNode);
        void inorderTraversalRecursive(Node<T> *currentNode);
        void postorderTraversalRecursive(Node<T> *currentNode);
    
        int elementCount;
        void increaseElementCount() { ++this->elementCount; };
        void decreaseElementCount() { --this->elementCount; };
    
};

template <typename T>
void BinarySearchTree<T>::preorderTraversal() {
    
    preorderTraversalRecursive(this->rootNode);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::preorderTraversalRecursive(Node<T> *currentNode) {
    
    if (currentNode != nullptr) {
        std::cout << currentNode->data << " ";
        preorderTraversalRecursive(currentNode->left);
        preorderTraversalRecursive(currentNode->right);
    }
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal() {
    
    inorderTraversalRecursive(this->rootNode);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::inorderTraversalRecursive(Node<T> *currentNode) {
    
    if (currentNode != nullptr) {
        inorderTraversalRecursive(currentNode->left);
        std::cout << currentNode->data << " ";
        inorderTraversalRecursive(currentNode->right);
    }
}


template <typename T>
void BinarySearchTree<T>::postorderTraversal() {
        
    postorderTraversalRecursive(this->rootNode);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::postorderTraversalRecursive(Node<T> *currentNode) {
    
    if (currentNode != nullptr) {
        postorderTraversalRecursive(currentNode->left);
        postorderTraversalRecursive(currentNode->right);
        std::cout << currentNode->data << " ";
    }
}

template <typename T>
bool BinarySearchTree<T>::insertNode(Node<T> *insertNode, T data) {
    
    if (insertNode->data < data) {
        if (insertNode->right == nullptr) {
            Node<T> *newNode = new Node<T>;
            
            insertNode->right = newNode;            
            newNode->left = nullptr;
            newNode->right = nullptr;
            
            newNode->data = data;
            
            return true;
        }
        else {
            BinarySearchTree<T>::insertNode(insertNode->right, data);
        }
        
    }
    
    if (insertNode->data > data) {
        if (insertNode->left == nullptr) {
            Node<T> *newNode = new Node<T>;
            
            insertNode->left = newNode;
            newNode->left = nullptr;
            newNode->right = nullptr;
            
            newNode->data = data;
            
            return true;
        }
        else {
            BinarySearchTree<T>::insertNode(insertNode->left, data);
        }
    }
    
    if (insertNode->data == data)
        return false;

}

template <typename T>
void BinarySearchTree<T>::insert(T data) {
    
    if (this->rootNode == nullptr) {
        Node<T> *newNode = new Node<T>;
        
        this->rootNode = newNode;        
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->data = data;
        
        increaseElementCount();
    }
    else {
        if ( insertNode(this->rootNode, data) == true )
            increaseElementCount();
    }
}

template <typename T>
void BinarySearchTree<T>::remove(T data) {
    Node<T> *parrentNode = nullptr;
    Node<T> *removeNode = findNode(this->rootNode, data, &parrentNode);

    if (removeNode == nullptr)
        return;
    
    switch( removeNode->getDegree() )
    {
        case 0:    // Case: remove leaf
            if (parrentNode == nullptr) {
                
                this->rootNode = nullptr;
                delete removeNode;
                break;
            }
            
            if (parrentNode->left == removeNode) {
                parrentNode->left = nullptr;
                
                delete removeNode;
            }
            else {
                parrentNode->right = nullptr;
                
                delete removeNode;
            }
            
            break;
            
        case 1:    // Case: remove node with single child
            if (parrentNode == nullptr) {
                if ( this->rootNode->left != nullptr ) {
                    this->rootNode = this->rootNode->left;
                    removeNode->left = nullptr;
                    
                }
                else {
                    this->rootNode = this->rootNode->right;
                    removeNode->right = nullptr;
                }
                
                delete removeNode;
                break;
            }
            
            if (parrentNode->left == removeNode && removeNode->left != nullptr) {
                parrentNode->left = removeNode->left;
                removeNode->left = nullptr;
            }
            else {
                parrentNode->right = removeNode->right;
                removeNode->right = nullptr;
            }
            delete removeNode;                

            break;
            
        case 2:    // Case: remove node with 2 children
            /*
             * 1. find min node in right subtree
             * 2. find max node in left subtree
             */
                      
            if (parrentNode == nullptr) {
                return ;
            }
            else {
                Node<T> *swapNode = removeNode->left;
                Node<T> *swapParrent = removeNode;    // swapNode's parrent node
                
                while(swapNode->right != nullptr)
                {
                    swapParrent = swapNode;
                    swapNode = swapNode->right;
                }
                
                std::cout << swapParrent->data << std::endl;
                std::cout << swapNode->data << std::endl;
				std::cout << removeNode->data << std::endl;
                                
				// need to fix Situation that swapParent == removeNode !!
				return ;
				
				swapParrent->right = swapNode->left;
				swapNode->left = removeNode->left;
				swapNode->right = removeNode->right;
				
				/*
                if (parrentNode->left == removeNode) {
					
                    swapNode->left = removeNode->left;
                    swapNode->right = removeNode->right;
                    parrentNode->left = swapNode;
                    swapParrent->right = nullptr;
                    removeNode->left = nullptr;
                    removeNode->right = nullptr;

                }
                else {					
                    swapNode->left = removeNode->left;
                    swapNode->right = removeNode->right;
                    parrentNode->right = swapNode;
                    swapParrent->right = nullptr;
                    removeNode->left = nullptr;
                    removeNode->right = nullptr;
                }
				*/
                
            }

            delete removeNode;
            break;
            
        default:    // Case: never happened
            std::cout << "???? WHOOPS ????" << std::endl;
            break;
            
    }
    
    decreaseElementCount();
}

template <typename T>
Node<T> *BinarySearchTree<T>::findNode(Node<T> *compareNode, T data) {
    if (compareNode == nullptr) {
        return nullptr;
    }
    
    if (compareNode->data < data) {
        return findNode(compareNode->right, data);
    }

    if (compareNode->data > data) {
        return findNode(compareNode->left, data);
    }
    
    return compareNode;
}

template <typename T>
Node<T> *BinarySearchTree<T>::findNode(Node<T> *compareNode, T data, Node<T> **parrentNode) {
    if (compareNode == nullptr) {
        return nullptr;
    }
        
    if (compareNode->data < data) {
        *parrentNode = compareNode;
        return findNode(compareNode->right, data, parrentNode);
    }

    if (compareNode->data > data) {
        *parrentNode = compareNode;
        return findNode(compareNode->left, data, parrentNode);
    }
    
    return compareNode;
}


template <typename T>
bool BinarySearchTree<T>::find(T data) {
    return ( findNode(this->rootNode, data) == nullptr ) ? false : true;
}


int main() {
    BinarySearchTree<int> tree;
    
    tree.insert(1);
    tree.insert(100);
    tree.insert(101);
    tree.insert(5);
    tree.insert(6);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    
    //std::cout << tree.find(4) << std::endl;

    tree.preorderTraversal();
    // tree.inorderTraversal();
    // tree.postorderTraversal();
    
    //tree.remove(100);
	tree.remove(5);

	
    //tree.remove(1);

	tree.preorderTraversal();
}