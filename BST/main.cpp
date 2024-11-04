#include <iostream>
#include "BinarySearchTree.h"
void testBinarySearchTree()
{
    BinarySearchTree<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    std::cout << "Minimum element: " << bst.findMin() << std::endl;
    std::cout << "Maximum element: " << bst.findMax() << std::endl;

    std::cout << "Contains 7? " << (bst.contains(7) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 20? " << (bst.contains(20) ? "Yes" : "No") << std::endl;

    bst.remove(7);
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();

    try
    {
        int detachedMin = bst.myDetachMin();
        std::cout << "Detached minimum element: " << detachedMin << std::endl;
        std::cout << "Tree after detaching minimum:" << std::endl;
        bst.printTree();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error detaching minimum: " << e.what() << std::endl;
    }

    
    bst.makeEmpty();
    std::cout << "Tree after making empty:" << std::endl;
    bst.printTree();

    
    std::cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

   
    BinarySearchTree<int> bst2;
    bst2.insert(1);
    bst2.insert(3);
    bst2.insert(2);

    BinarySearchTree<int> bst3(bst2);
    std::cout << "Copied Tree (bst3):" << std::endl;
    bst3.printTree();

    BinarySearchTree<int> bst4;
    bst4 = bst2;
    std::cout << "Assigned Tree (bst4):" << std::endl;
    bst4.printTree();

   
    BinarySearchTree<int> bst5(std::move(bst2));
    std::cout << "Moved Tree (bst5):" << std::endl;
    bst5.printTree();

    BinarySearchTree<int> bst6;
    bst6 = std::move(bst5);
    std::cout << "Move Assigned Tree (bst6):" << std::endl;
    bst6.printTree();

   
    try
    {
        bst.findMax(); 
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main()
{
    testBinarySearchTree();
    return 0;
}
