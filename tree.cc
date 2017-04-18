#include "tree.h"

#include <cassert>
#include <iostream>
#include <queue>

using namespace std;
// #define NDEBUG

void Tree::printNode(Tree::Node* node) {
  assert(node);
  const char term = ' ';
  cout << node->value << term;
}

Tree::Node* Tree::NewNode(int value) {
  return new Node(value);
}

void Tree::insert(int value) {
  Node* node = insert(root, value);
  if (!root)
    root = node;
}

Tree::Node* Tree::insert(Tree::Node* node, int value) {
  Tree::Node* newNode = NewNode(value);
  if (!node)
    return newNode;

  if (node->value < value)
    node->right = insert(node->right, value);
  else if (node->value > value)
    node->left = insert(node->left, value);

  return node;
}

void Tree::traverse(TraverseType type) {
  switch (type) {
    case TraverseType::InOrder:
      inorderTraverse(root);
      break;
    case TraverseType::PreOrder:
      preorderTraverse(root);
      break;
    case TraverseType::PostOrder:
      postorderTraverse(root);
      break;
    case TraverseType::LevelOrder:
      levelorderTraverse(root);
      break;
    default:
      break;
  }
}

void Tree::inorderTraverse(Tree::Node* node) {
  if (!node)
    return;

  inorderTraverse(node->left);
  printNode(node);
  inorderTraverse(node->right);
}

void Tree::preorderTraverse(Tree::Node* node) {
  if (!node)
    return;

  printNode(node);
  preorderTraverse(node->left);
  preorderTraverse(node->right);
}

void Tree::postorderTraverse(Tree::Node* node) {
  if (!node)
    return;

  postorderTraverse(node->left);
  postorderTraverse(node->right);
  printNode(node);
}

void Tree::levelorderTraverse(Tree::Node* node) {
  if (!node)
    return;

  queue<Tree::Node*> Queue;
  Queue.push(node);

  while (!Queue.empty()) {
    Tree::Node* current = Queue.front();
    Queue.pop();
    printNode(current);

    if (current->left)
      Queue.push(current->left);
    if (current->right)
      Queue.push(current->right);
  }
}

Tree::Node* findNode(int value) {
  Tree::Node* node = root;
  while (node) {
    if (node->value < value)
      node = node->right;
    else if (node->value > value)
      node = node->left;
    else
      return node;
  }

  return node;
}

Tree::Node* findNode(Tree::Node* node, int value) {
  if (!node)
    return nullptr;

  if (node->value == value)
    return node;

  if (node->value < value)
    return findNode(node->right);
  else if (node->value > value)
    return findNode(node->left);
}


bool Tree::remove(int value) {
  Tree::Node* node = root;
  Tree::Node* parent = root;
  bool leftChild = true;

  while (node) {
    if (node->value == value)
      break;

    parent = node;
    if (node->value < value) {
      leftChild = false;
      node = node->right;
    }
    else if (node->value > value) {
      leftChild = true;
      node = node->left;
    }
  }

  if (!node)
    return false;

  // if leaf node, simply delete it.
  if (!node->left && !node->right) {
    if (node == root)
      root = nullptr;

    parent->left = nullptr;
    parent->right = nullptr;
  } // if node->left is null, parent points node->right as child
  else if (!node->left) {
    if (node == root)
      root = node->right;
    else if (leftChild) {
      parent->left = node->right;
    } else {
      parent->right = node->right;
    }
  } // if node->right is null, parent points node->left as child
  else if (!node->right) {
    if (node == root)
      root = node->left;
    else if (leftChild) {
      parent->left = node->left;
    } else {
      parent->right = node->left;
    }
  } // two children, so replace with inorder successor
  else {
    Node* current = node->right;
    Node* parentNode = current;

    while (current->left) {
      parentNode = current;
      current = current->left;
    }

    parentNode->left = current->right;
    current->left = node->left;
    current->right = node->right;

    if (node == root)
      root = current;
    else if (leftChild)
      parent->left = current;
    else
      parent->right = current;
  }

  free(node);
  return true;
}

