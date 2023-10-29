#ifndef CPP2_S21_CONTAINERS_S21_RB_TREE_H_
#define CPP2_S21_CONTAINERS_S21_RB_TREE_H_

#include <iostream>
#include <stack>

template <typename K, typename V = int>
struct node {
  std::pair<K, V> key_value;
  node *parent;
  node *left;
  node *right;
  enum Color { BLACK, RED } color;
  node(const K &key, const V &val = 0, const Color col = node<K, V>::BLACK,
       node *par = nullptr)
      : key_value(key, val),
        parent(par),
        left(nullptr),
        right(nullptr),
        color(col) {}
};

template <typename K, typename V = int>
class Tree {
 public:
  Tree() {
    node_ = nullptr;
    size_ = 0;
  }

  Tree(Tree<K, V> &&other) : node_(other.node_), size_(other.size_) {
    other.node_ = nullptr;
    other.size_ = 0;
  }

  Tree &operator=(Tree &&other) {
    if (this != &other) {
      node_ = other.node_;
      size_ = other.size_;
      other.node_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  Tree(const Tree<K, V> &other) {
    node_ = copyTree(other.node_);
    size_ = other.size_;
  }

  Tree &operator=(const Tree<K, V> &other) {
    if (this != &other) {
      clearTree(node_);
      node_ = copyTree(other.node_);
      size_ = other.size_;
    }
    return *this;
  }

  size_t getSize() const { return size_; }

  node<K, V> *getNode() const { return node_; }

  void insertValue(bool is_multiset, const K &key, const V &value = 0) {
    if (!node_)
      node_ = new node<K, V>(key, value, node<K, V>::BLACK);
    else if (node<K, V> *newNode = insertNode(is_multiset, node_, key, value))
      insertBalancing(newNode);
    size_++;
  }

  node<K, V> *findValue(const K &key) { return binarySearch(node_, key); }

  void removeValue(const K &key) {
    node<K, V> *removing_node = findValue(key);
    if (!removing_node) return;
    size_--;
    removeNode(removing_node);
  }

  node<K, V> *getMinimum() const { return getExtremeNode(node_, true); }

  node<K, V> *getMaximum() const { return getExtremeNode(node_, false); }

 private:
  node<K, V> *node_;
  size_t size_;

  node<K, V> *getExtremeNode(node<K, V> *start, bool isLeft) const {
    if (!start) return nullptr;
    node<K, V> *current = start;
    while ((isLeft && current->left) || (!isLeft && current->right))
      current = isLeft ? current->left : current->right;
    return current;
  }

  node<K, V> *copyTree(const node<K, V> *source) {
    if (!source) return nullptr;
    std::stack<std::pair<const node<K, V> *, node<K, V> *>> stack;
    node<K, V> *root = new node<K, V>(source->key_value.first,
                                      source->key_value.second, source->color);
    stack.push({source, root});
    while (!stack.empty()) {
      auto [src, dest] = stack.top();
      stack.pop();
      for (int i = 0; i < 2; ++i) {
        const node<K, V> *childSrc = i ? src->right : src->left;
        if (!childSrc) continue;
        node<K, V> *&childDest = i ? dest->right : dest->left;
        childDest = new node<K, V>(childSrc->key_value.first,
                                   childSrc->key_value.second, childSrc->color);
        childDest->parent = dest;
        stack.push({childSrc, childDest});
      }
    }
    return root;
  }

  void clearTree(node<K, V> *root) {
    std::stack<node<K, V> *> s;
    for (s.push(root); !s.empty(); delete root) {
      root = s.top();
      s.pop();
      root->left &&s.push(root->left);
      root->right &&s.push(root->right);
    }
  }

  enum Direction { LEFT, RIGHT };

  void rotate(node<K, V> *root, Direction dir) {
    node<K, V> *new_root = (dir == LEFT) ? root->right : root->left;
    node<K, V> **child_ptr = (dir == LEFT) ? &(root->right) : &(root->left);
    node<K, V> **opp_child_ptr =
        (dir == LEFT) ? &(new_root->left) : &(new_root->right);
    *child_ptr = *opp_child_ptr;
    if (*opp_child_ptr) (*opp_child_ptr)->parent = root;
    new_root->parent = root->parent;
    if (!root->parent)
      node_ = new_root;
    else if (root == ((dir == LEFT) ? root->parent->left : root->parent->right))
      (dir == LEFT ? root->parent->left : root->parent->right) = new_root;
    else
      (dir == LEFT ? root->parent->right : root->parent->left) = new_root;
    *opp_child_ptr = root;
    root->parent = new_root;
  }

  void leftRotate(node<K, V> *root) { rotate(root, LEFT); }

  void rightRotate(node<K, V> *root) { rotate(root, RIGHT); }

  bool blackSiblingRedChild(node<K, V> *n) {
    node<K, V> *s = getSibling(n);
    return checkColor(s, node<K, V>::BLACK) &&
           (checkColor(s->left, node<K, V>::RED) ||
            checkColor(s->right, node<K, V>::RED));
  }

  node<K, V> *getSibling(node<K, V> *n) {
    return (n == n->parent->left) ? n->parent->right : n->parent->left;
  }

  bool isSiblingRed(node<K, V> *n) {
    return checkColor(getSibling(n), node<K, V>::RED);
  }

  bool checkColor(node<K, V> *n, bool color) {
    return n != nullptr && n->color == color;
  }
  void setColor(node<K, V> *n, bool color) {
    if (n) n->color = color;
  }

  void insertBalancing(node<K, V> *root) {
    while (root->parent && root->parent->color == node<K, V>::RED) {
      bool isLeft = root->parent == root->parent->parent->left;
      node<K, V> *uncle =
          isLeft ? root->parent->parent->right : root->parent->parent->left;
      if (uncle && uncle->color == node<K, V>::RED) {
        root->parent->color = node<K, V>::BLACK;
        uncle->color = node<K, V>::BLACK;
        root->parent->parent->color = node<K, V>::RED;
        root = root->parent->parent;
      } else {
        if (root == (isLeft ? root->parent->right : root->parent->left)) {
          root = root->parent;
          isLeft ? leftRotate(root) : rightRotate(root);
        }
        root->parent->color = node<K, V>::BLACK;
        root->parent->parent->color = node<K, V>::RED;
        isLeft ? rightRotate(root->parent->parent)
               : leftRotate(root->parent->parent);
      }
    }
    node_->color = node<K, V>::BLACK;
  }

  void removeBalancing(node<K, V> *tested_node) {
    while (tested_node != node_ &&
           (!tested_node || tested_node->color == node<K, V>::BLACK)) {
      bool isLeft = tested_node == tested_node->parent->left;
      node<K, V> *brother = getSibling(tested_node);
      if (!brother) continue;
      if (brother->color == node<K, V>::RED) {
        tested_node->parent->color = node<K, V>::RED;
        isLeft ? leftRotate(tested_node->parent)
               : rightRotate(tested_node->parent);
      }
      if ((!brother->left || brother->left->color == node<K, V>::BLACK) &&
          (!brother->right || brother->right->color == node<K, V>::BLACK)) {
        brother->color = node<K, V>::RED;
      } else {
        if (isLeft ? (!brother->right ||
                      brother->right->color == node<K, V>::BLACK)
                   : (!brother->left ||
                      brother->left->color == node<K, V>::BLACK)) {
          (isLeft ? brother->left : brother->right)->color = node<K, V>::BLACK;
          brother->color = node<K, V>::RED;
          isLeft ? rightRotate(brother) : leftRotate(brother);
        }
        brother->color = tested_node->parent->color;
        tested_node->parent->color = node<K, V>::BLACK;
        (isLeft ? brother->right : brother->left)->color = node<K, V>::BLACK;
        isLeft ? leftRotate(tested_node->parent)
               : rightRotate(tested_node->parent);
        tested_node = node_;
      }
    }
    if (tested_node) tested_node->color = node<K, V>::BLACK;
    node_->color = node<K, V>::BLACK;
  }

  node<K, V> *getNext(node<K, V> *current) {
    for (; current->left; current = current->left)
      ;
    return current;
  }

  void removeNode(node<K, V> *node_to_remove) {
    if (!node_to_remove->left &&
        !node_to_remove->right) {  // у вершины нет детей
      // removeBalancing(node_to_remove);
      if (node_to_remove == node_) {
        node_ = nullptr;
      } else {
        if (node_to_remove->parent) {
          if (node_to_remove == node_to_remove->parent->left)
            node_to_remove->parent->left = nullptr;
          else
            node_to_remove->parent->right = nullptr;
        }
      }
      delete node_to_remove;
      return;
    }
    node<K, V> *next_node = nullptr;
    if (node_to_remove->left &&
        node_to_remove->right) {  // у вершины есть оба ребёнка
      next_node = getNext(node_to_remove->right);
      if (next_node->right) {
        next_node->right->parent = next_node->parent;
      }
      if (next_node != node_to_remove->right) {
        if (next_node == next_node->parent->left) {
          next_node->parent->left = next_node->right;
        } else {
          next_node->parent->right = next_node->right;
        }
        if (next_node->right) {
          next_node->right->parent = next_node->parent;
        }
      } else {
        node_to_remove->right = next_node->right;
        if (next_node->right) {
          next_node->right->parent = node_to_remove;
        }
      }
      delete next_node;
    } else {  // у вершины один ребёнок
      next_node =
          (node_to_remove->left) ? node_to_remove->left : node_to_remove->right;
      if (node_to_remove->parent) {
        if (node_to_remove == node_to_remove->parent->left) {
          node_to_remove->parent->left = next_node;
        } else {
          node_to_remove->parent->right = next_node;
        }
        next_node->parent = node_to_remove->parent;
      } else {
        node_ = next_node;
        next_node->parent = nullptr;
      }
    }
    if (next_node != node_to_remove) {
      node_to_remove->color = next_node->color;
      node_to_remove->key_value.first = next_node->key_value.first;
      node_to_remove->key_value.second = next_node->key_value.second;
      delete node_to_remove;
      return;
    }
    if (next_node->color == node<K, V>::BLACK) {
      removeBalancing(node_to_remove);
    }
  }

  node<K, V> *insertNode(bool is_multiset, node<K, V> *parent, const K &key,
                         const V &value) {
    node<K, V> *last = parent;
    while (parent) {
      last = parent;
      parent =
          (key < parent->key_value.first)
              ? parent->left
              : ((is_multiset || key > parent->key_value.first) ? parent->right
                                                                : nullptr);
    }
    node<K, V> *new_node = new node<K, V>(key, value, node<K, V>::RED, last);
    (key < last->key_value.first ? last->left : last->right) = new_node;
    return new_node;
  }

  node<K, V> *binarySearch(node<K, V> *n, const K &k) {
    while (n && k != n->key_value.first) {
      n = (k < n->key_value.first) ? n->left : n->right;
    }
    return n;
  }
};

#endif  // CPP2_S21_CONTAINERS_S21_RB_TREE_H_