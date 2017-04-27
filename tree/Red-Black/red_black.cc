#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 1. Every node has a color either red or black.
// 2. Root of tree is always black.
// 3. There are no two adjacent red nodes
//    (A red node cannot have a red parent or red child).
// 4. Every path from root to a NULL node has same number of black nodes.
// 5. Comparison with AVL Tree
//    The AVL trees are more balanced compared to Red Black Trees, but
//    they may cause more rotations during insertion and deletion.
//    So if your application involves many frequent insertions and
//    deletions, then Red Black trees should be preferred. And if the
//    insertions and deletions are less frequent and search is more frequent
//    and search is more frequent operation, then AVL tree should be preferred
//    over Red Black Tree.
// 6. Black height is number of black nodes on a path from a node to a leaf.
//    Leaf nodes are also counted black nodes. From above properties 3 and 4,
//    we can derive, a node of height h has black-height >= h/2.
// 7. Every Red Black Tree with n nodes has height <= 2Log(n+1)
// 8. Insertion : Try recoloring first, if recoloring doesn't work, then go
//    for rotation.
//    1) Recoloring
//    2) Rotation
// 9. Let x be the newly inserted node.
//    1) Perform standard BST insertion and make the color of newly inserted nodes
//       as RED.
//    2) If x is root, change color of x as BLACK (Black height of complete tree
//       increases by 1).
//    3) Do following if color of x's parent is not BLACK or x is not root.
//      a) If x's uncle is RED (Grand parent must have been black from property 4)
//        (i) Change color of parent and uncle as BLACK.
//        (ii) color of grand parent as RED.
//        (iii) Change x = x's grandparent, repeat steps 2 and 3 for new x.
//      b) If x's uncle is BLACK, then there can be four configurations for x,
//         x's parent (p) and x's grandparent(g) (This is similar to AVL Tree)
//        (i) Left Left Case ( p is left child of g and x is left child of p)
//        (ii) Left Right Case (p is left child of g and x is right child of p)
//        (iii) Right Right Case (Mirror of case a)
//        (iv) Right Left Case (Mirror of case c)
class RedBlackTree {
  enum class Color : int {
    BLACK = 0,
    RED = 1,
  };

  template <typename T>
  class TreeNode {
   public:
      TreeNode(int data) : data_(data)
                         , left_(nullptr)
                         , right_(nullptr)
                         , color_(Color::RED),
                         , height_(0) {}
      T data_;
      TreeNode<T>* left_;
      TreeNode<T>* right_;
      Color color_;
      int height_;
  };

 public:
  RedBlackTree() : root_(nullptr) {}

  int height(TreeNode<int>* root) {
    if (!root) return 0;

    int h = 0;
    h = max(height(root->left_), height(root->right_)) + 1;
    return h;
  }

  void Traverse() {
    levelorder(root_);
    cout << endl;
    cout << "height: " << height(root_) << endl;
  }

  void Insertion(int data) {
    root_ = insert(root_, data);
    root_->color_ = Color::BLACK;
  }

 private:
  void levelorder(TreeNode<int>* root) {
    if (!root) return;

    queue<TreeNode<int>*> Queue;
    Queue.push(root);

    while (!Queue.empty()) {
      TreeNode<int>* node = Queue.front();
      Queue.pop();

      cout << node->data_ << " ";
      if (node->left_) Queue.push(node->left_);
      if (node->right_) Queue.push(node->right_);
    }
  }

  TreeNode<int>* insert(TreeNode<int>* parent, int data) {
    if (!parent) {
      return new TreeNode<int>(data);
    }

    if (data < parent->data_)
      parent->left_ = insert(parent->left_, data);
    else
      parent->right_ = insert(parent->right_, data);

    return parent;
  }

  TreeNode<int>* root_;

};

int main() {
  vector<int> inputs = {12, 9, 16, 36, 72, 54, 27};
  RedBlackTree tree;
  for (int d : inputs) {
    tree.Insertion(d);
  }

  tree.Traverse();

}
