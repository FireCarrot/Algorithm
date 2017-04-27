#include <vector>
#include <iostream>
#include <queue>

using namespace std;

template <typename S>
class Tree {
  template <typename T>
  class TreeNode {
  public:
    TreeNode(T d) : data_(d) {}

    void insert_child(TreeNode* child) {
      children_.push_back(child);
    }

    vector<TreeNode*>& children() {
      return children_;
    }

    T data() { return data_; }

  private:
    T data_;
    vector<TreeNode*> children_;
  };

public:
  ~Tree() {
    if (!root_)
      return;

    Dispose(root_);
  }

  void Traverse(){
    cout << "===== Tree traverse and height =====" << endl;
    cout << " Preorder:  ";
    Preorder(root_);
    cout << endl;

    cout << " Inorder:  ";
    Inorder(root_);
    cout << endl;

    cout << " Postorder: ";
    Postorder(root_);
    cout << endl;

    cout << " Levelorder: ";
    Levelorder(root_);
    cout << endl;
    cout << " Tree Level: "<< height(root_) << endl;
  }

  void BuildTree(int level) {
    int n = 3;

    S cnt = 1;
    root_ = new TreeNode<S>(cnt++);
    TreeNode<S>* sub_root = root_;
    for (int l = 1; l <= level; l++) {
      for (int i = 1; i <= n; i++) {
        TreeNode<S>* node = new TreeNode<S>(cnt++);
        sub_root->insert_child(node);
      }

      sub_root = sub_root->children()[0];
    }
  }

  int height(TreeNode<S>* root) {
    if (!root) return 0;

    int h = 0;
    for (TreeNode<S>* node : root->children()) {
      h = max(h, height(node) + 1);
    }

    return h;
  }

private:
  void Dispose(TreeNode<S>* root) {
    if (!root)
      return;

    for (TreeNode<S>* node : root->children()) {
      Dispose(node);
    }

    delete root;
  }
  void Preorder(TreeNode<S>* root) {
    if (!root) return;

    cout << root->data() << " ";
    for (TreeNode<S>* child : root->children()) {
      Preorder(child);
    }
  }
  void Inorder(TreeNode<S>* root) {
  }
  void Postorder(TreeNode<S>* root) {
    if (!root) return;

    for (TreeNode<S>* child : root->children()) {
      Postorder(child);
    }
    cout << root->data() << " ";
  }
  void Levelorder(TreeNode<S>* root) {
    if (!root) return;

    queue<TreeNode<S>*> Queue;
    Queue.push(root);

    while (!Queue.empty()) {
      TreeNode<S>* root = Queue.front();
      cout << root->data() << " ";
      Queue.pop();

      for (TreeNode<S>* node : root->children()) {
        Queue.push(node);
      }
    }
  }

  TreeNode<S>* root_ = nullptr;
};

int main() {
  int level = 5;
  Tree<int> tree;
  tree.BuildTree(level);
  tree.Traverse();
}
