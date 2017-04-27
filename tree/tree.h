#ifndef __TREE_H_
#define __TREE_H_

class Tree {
public:
  enum class TraverseType: int {
    InOrder = 1,
    PreOrder,
    PostOrder,
    LevelOrder
  };

  class Node {
    public:
      Node(int v)
         : left(nullptr)
         , right(nullptr)
         , value(v) {}

      Node* left;
      Node* right;
      int value;
  };

  Tree() : root(nullptr) {}
  void insert(int value);
  bool remove(int value);
//  void swap(int depth);
//  void getHeight();
  void inorderTraverse(Tree::Node*);
  void preorderTraverse(Tree::Node*);
  void postorderTraverse(Tree::Node*);
  void levelorderTraverse(Tree::Node*);
  void traverse(TraverseType type);

private:
  void printNode(Tree::Node* node);
  Tree::Node* NewNode(int value);
  Tree::Node* insert(Tree::Node* node, int value);
  Tree::Node* findNode(int value);
  Tree::Node* findNode(Tree::Node* node, int value);

  Tree::Node* root;
};

#endif
