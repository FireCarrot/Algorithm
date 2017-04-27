#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class TreeNode {
 public:
  TreeNode(T d) : data_(d) {
    left_ = nullptr;
    right_ = nullptr;
    height_ = 1;
  }

  TreeNode(T d, TreeNode<T>* left, TreeNode<T>* right)
      : data_(d)
      , left_(left)
      , right_(right)
      , height_ (1) {}

  TreeNode<T>* left() { return left_; }
  TreeNode<T>* right() { return right_; }
  void set_left(TreeNode<T>* left) { left_ = left; }
  void set_right(TreeNode<T>* right) { right_ = right; }
  T data() { return data_; }
  int height() { return height_; }
  void set_height(int height) { height_ = height; }

  int balanced_factor() {
    int right_height = right_? right_->height() : 0;
    int left_height = left_ ? left_->height() : 0;
    return right_height - left_height;
  }

 private:
  T data_;
  TreeNode<T>* left_;
  TreeNode<T>* right_;
  int height_;
};

/* AVL tree is a self-balancing binary search tree.
 * In AVL tree, the heights of the two child subtrees of any node differ by at most one;
 * if at any time they differ by more than one, rebalancing is done to restore this property.
 * Lookup, insertion, and deletion all take O(logN) time in both the average and worst cases,
 * where n is the number of nodes in the tree prior to the operation.
 * Insertions and deletions may require the tree to be rebalanced by one or more tree rotations.
 *
 * AVL trees are often compared with red-black trees because both support the same set of
 * operations and take O(log n) time for the basic operations.
 * For lookup-intensive applications, AVL trees are faster than red-black trees
 * because they are more strictly balanced. Similar to red-black trees,
 * AVL trees are height-balanced. Both are, in general, neither weight-balanced nor u-balanced
 * for any u<= 1/2; that is, sibling nodes can have hugely differing numbers of descendants.
 * Algorithm              Average              Worst Case
 * Space                  O(n)                 O(n)
 * Search                 O(log n)             O(log n)
 * Insert                 O(log n)             O(log n)
 * Delete                 O(log n)             O(log n)
 *                         J (+1)
 *                         /    \
 *                    F(-1)      P(+1)
 *                    /  \      /     \
 *                D(-1)  G(0) L(+1)   V(-1)
 *               /              \      /  \
 *            C(0)             N(0)  S(0) X(0)
 *                                         /\
 *                                      Q(0) U(0)
 */

class AVLTree {
 public:
  AVLTree() {
    root_ = nullptr;
  }

  void insert(int v) {
    root_ = insert(root_, v);
  }

  void traverse() {
    inorder(root_);
    cout << endl;
    levelorder(root_);
    cout << endl;
    cout << "height: " << height(root_) << endl;
  }

 private:
  TreeNode<int>* insert(TreeNode<int>* root, int v) {
    if (!root) {
      return new TreeNode<int>(v);
    }

    if (root->data() > v) {
      root->set_left(insert(root->left(), v));
    } else {
      root->set_right(insert(root->right(), v));
    }

    root->set_height(height(root));

//    cout << root->balanced_factor() << " ";
    if (root->balanced_factor() > 1 && root->right()) {
      if (root->right()->data() < v) {
        root = leftRotation(root);
      } else {
        root->set_right(rightRotation(root->right()));
        root = leftRotation(root);
      }
    } else if (root->balanced_factor() < -1 && root->left()) {
      if (root->left()->data() > v) {
        root = rightRotation(root);
      } else {
        root->set_left(leftRotation(root->left()));
        root = rightRotation(root);
      }
    }

    return root;
  }

  int height(TreeNode<int>* node) {
    if (!node) return 0;
    int h = 0;
    h = max(height(node->left()), height(node->right())) + 1;
    return h;
  }

  void inorder(TreeNode<int>* root) {
    if (!root) return;

    inorder(root->left());
    cout << root->data() << " ";
    inorder(root->right());
  }

  void levelorder(TreeNode<int>* root) {
    if (!root) return;

    queue<TreeNode<int>*> Queue;
    Queue.push(root);

    while (!Queue.empty()) {
      TreeNode<int>* node = Queue.front();
      Queue.pop();

      if (node->left()) Queue.push(node->left());
      if (node->right()) Queue.push(node->right());

      cout << node->data() << " ";
    }
  }

  TreeNode<int>* rightRotation(TreeNode<int>* pivot) {
    TreeNode<int>* root = pivot->left();
    pivot->set_left(root->right());
    root->set_right(pivot);
    root->set_height(height(root));
    return root;
  }

  TreeNode<int>* leftRotation(TreeNode<int>* pivot) {
    TreeNode<int>* root = pivot->right();
    pivot->set_right(root->left());
    root->set_left(pivot);
    root->set_height(height(root));
    return root;
  }

  TreeNode<int>* root_;
};

int main() {
  vector<int> inputs = {12, 9, 16, 36, 72, 54, 27};
  AVLTree tree;

  for (int v : inputs) {
    tree.insert(v);
  }

  tree.traverse();
  return 0;
}
