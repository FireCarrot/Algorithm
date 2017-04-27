#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename U>
class Tree {
 template <typename T>
 class TreeNode {
  public:
   TreeNode(T d) : data_(d) {
     left_ = nullptr;
     right_ = nullptr;
   }

   TreeNode(T d, TreeNode<T>* left, TreeNode<T>* right)
     : data_(d)
     , left_(left)
     , right_(right) {}

   T data() { return data_; }
   TreeNode<T>* left() { return left_; }
   TreeNode<T>* right() { return right_; }
   void set_left(TreeNode<T>* left) { left_ = left; }
   void set_right(TreeNode<T>* right) { right_ = right; }

  private:
   T data_;
   TreeNode<T>* left_;
   TreeNode<T>* right_;
 };

 public:
  ~Tree() {
    Dispose(root_);
  }

  void BuildTree(vector<int>& preorder, vector<int> inorder) {
    int count = 0;
    root_ = new TreeNode<U>(preorder[count]);

    int index = find(inorder.begin(), inorder.end(), root_->data()) - inorder.begin();
    root_->set_left(build_tree(preorder,
                              vector<int>(inorder.begin(), inorder.begin() + index),
                              &count));
    root_->set_right(build_tree(preorder,
                              vector<int>(inorder.begin() + index + 1, inorder.end()),
                              &count));
  }

  void Postorder() {
    cout << "Build tree from preorder and inorder" << endl;
    cout << "Traverse postorder the rebuilt tree" << endl;

    Postorder(root_);

    cout << endl;
  }

 private:
  void Postorder(TreeNode<U>* root) {
    if (!root) return;

    Postorder(root->left());
    Postorder(root->right());

    cout << root->data() << " ";
  }

  TreeNode<U>* build_tree(vector<int>& preorder, vector<int> inorder, int* count) {
    if (inorder.empty())
      return nullptr;

    TreeNode<U>* root = new TreeNode<U>(preorder[++(*count)]);

    int index = find(inorder.begin(), inorder.end(), root->data()) - inorder.begin();
    if (index > 0) {
      root->set_left(build_tree(preorder,
                               vector<int>(inorder.begin(), inorder.begin() + index),
                               count));
    }

    if (index < inorder.end() - inorder.begin()) {
      root->set_right(build_tree(preorder,
                               vector<int>(inorder.begin() + index + 1, inorder.end()),
                               count));
    }
    return root;
  }

  void Dispose(TreeNode<U>* root) {
    if (!root) return;

    Dispose(root->left());
    Dispose(root->right());

    delete root;
  }

  TreeNode<U>* root_;
};

int main() {
  vector<int> preorder = {27, 16, 9, 12, 54, 36, 72};
  vector<int> inorder = {9, 12, 16, 27, 36, 54, 72};

  Tree<int> tree;
  tree.BuildTree(preorder, inorder);
  tree.Postorder();

  return 0;
}

