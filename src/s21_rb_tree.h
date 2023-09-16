#ifndef CPP2_S21_CONTAINERS_S21_RB_TREE_H_
#define CPP2_S21_CONTAINERS_S21_RB_TREE_H_

#include <iostream>
const bool kBlack = true;
const bool kRed = false;

template <typename K, typename V = int>
struct node {
  std::pair<K, V> key_value;
  node *parent;
  node *left;
  node *right;
  bool color;
  node(const K &key, const V &val = 0, const bool col = kBlack,
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
      // delete node_;
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
    if (node_ == nullptr) {
      node_ = new node<K, V>(key, value, kBlack);
      size_++;
    } else {
      node<K, V> *newNode = insertNode(is_multiset, node_, key, value);
      if (newNode != nullptr) {
        insertBalancing(newNode);
        size_++;
      }
    }
  }
  node<K, V> *findValue(const K &key) { return binarySearch(node_, key); }
  void removeValue(const K &key) {
    node<K, V> *removing_node = findValue(key);
    if (removing_node) {
      size_--;
      removeNode(removing_node);
    } else {
      std::cout << "No such value in the tree" << std::endl;
    }
  }
  node<K, V> *getMinimum() const {
    if (node_ == nullptr) {
      return nullptr;
    }
    node<K, V> *current = node_;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }
  node<K, V> *getMaximum() const {
    node<K, V> *current = node_;
    while (current && current->right != nullptr) {
      current = current->right;
    }
    return current;
  }

 private:
  node<K, V> *node_;
  size_t size_;
  node<K, V> *copyTree(const node<K, V> *source) {
    if (!source) return nullptr;
    node<K, V> *newNode =
        new node<K, V>(source->key_value.first, source->key_value.second);
    newNode->color = source->color;
    newNode->left = copyTree(source->left);
    newNode->right = copyTree(source->right);

    if (newNode->left) newNode->left->parent = newNode;
    if (newNode->right) newNode->right->parent = newNode;

    return newNode;
  }
  void clearTree(node<K, V> *root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
  }
  void leftRotate(node<K, V> *root) {
    node<K, V> *new_root = root->right;
    root->right = new_root->left;
    if (new_root->left) new_root->left->parent = root;
    new_root->parent = root->parent;
    if (!root->parent)
      node_ = new_root;
    else if (root == root->parent->left)
      root->parent->left = new_root;
    else
      root->parent->right = new_root;
    new_root->left = root;
    root->parent = new_root;
  }
  void rightRotate(node<K, V> *root) {
    node<K, V> *new_root = root->left;
    root->left = new_root->right;
    if (new_root->right) new_root->right->parent = root;
    new_root->parent = root->parent;
    if (!root->parent)
      node_ = new_root;
    else if (root == root->parent->right)
      root->parent->right = new_root;
    else
      root->parent->left = new_root;
    new_root->right = root;
    root->parent = new_root;
  }
  bool isBlack(node<K, V> *n) { return n != nullptr && n->color == kBlack; }
  bool isRed(node<K, V> *n) { return n != nullptr && n->color == kRed; }
  bool blackSiblingRedChild(node<K, V> *n) {
    node<K, V> *s = getSibling(n);
    return isBlack(s) && (isRed(s->left) || isRed(s->right));
  }
  node<K, V> *getSibling(node<K, V> *n) {
    if (n == n->parent->left)
      return n->parent->right;
    else
      return n->parent->left;
  }
  bool isSiblingRed(node<K, V> *n) {
    node<K, V> *s = getSibling(n);
    return isRed(s);
  }
  void makeBlack(node<K, V> *n) {
    if (n != nullptr) n->color = kBlack;
  }
  void makeRed(node<K, V> *n) {
    if (n != nullptr) n->color = kRed;
  }
  void insertBalancing(node<K, V> *root) {
    while (root->parent && root->parent->color == kRed) {
      if (root->parent == root->parent->parent->left) {
        node<K, V> *new_root = root->parent->parent->right;  // расмотрим дядю
        if (new_root && new_root->color == kRed) {  // красный дядя
          root->parent->color = kBlack;
          new_root->color = kBlack;
          root->parent->parent->color = kRed;
          root = root->parent->parent;
        } else {  // чёрный дядя
          if (root ==
              root->parent
                  ->right) {  // если это правый потомок выполняем левый поворот
            root = root->parent;  // обновляем указатель - теперь указываем на
                                  // родителя
            leftRotate(root);
          }
          root->parent->color = kBlack;
          root->parent->parent->color = kRed;
          rightRotate(root->parent->parent);
        }
      } else {
        node<K, V> *new_root = root->parent->parent->left;
        if (new_root && new_root->color == kRed) {
          root->parent->color = kBlack;
          new_root->color = kBlack;
          root->parent->parent->color = kRed;
          root = root->parent->parent;
        } else {
          if (root == root->parent->left) {
            root = root->parent;
            rightRotate(root);
          }
          root->parent->color = kBlack;
          root->parent->parent->color = kRed;
          leftRotate(root->parent->parent);
        }
      }
    }
    node_->color = kBlack;
  }

  void removeBalancing(node<K, V> *tested_node) {
    while (tested_node != node_ && (tested_node != nullptr ||
                                    tested_node->color == kBlack)) {  // всё ок
      if (tested_node == tested_node->parent->left) {  // всё ок
        node<K, V> *brother = getSibling(tested_node);
        if (brother == nullptr) {
          continue;
        }
        if (brother->color == kRed) {
          // brother->color == kBlack;
          tested_node->parent->color = kRed;
          leftRotate(tested_node->parent);
        }
        if ((brother->left == nullptr || brother->left->color == kBlack) &&
            (brother->right == nullptr || brother->right->color == kBlack)) {
          brother->color = kRed;
        } else {
          if (brother->right == nullptr || brother->right->color == kBlack) {
            brother->left->color = kBlack;
            brother->color = kRed;
            rightRotate(brother);
          }
          brother->color = tested_node->parent->color;
          tested_node->parent->color = kBlack;
          brother->right->color = kBlack;
          leftRotate(tested_node->parent);
          tested_node = node_;
        }
      } else {
        node<K, V> *brother = getSibling(tested_node);
        if (brother == nullptr) {
          continue;
        }
        if (brother->color == kRed) {
          // brother->color == kBlack;
          tested_node->parent->color = kRed;
          rightRotate(tested_node->parent);
        }
        if ((brother->left == nullptr || brother->left->color == kBlack) &&
            (brother->right == nullptr || brother->right->color == kBlack)) {
          brother->color = kRed;
        } else {
          if (brother->left == nullptr || brother->left->color == kBlack) {
            brother->right->color = kBlack;
            brother->color = kRed;
            leftRotate(brother);
          }
          brother->color = tested_node->parent->color;
          tested_node->parent->color = kBlack;
          brother->left->color = kBlack;
          rightRotate(tested_node->parent);
          tested_node = node_;
        }
      }
    }
    tested_node->color = kBlack;
    node_->color = kBlack;
  }

  node<K, V> *getNext(node<K, V> *current) {
    node<K, V> *next_node = current;
    while (next_node->left) {
      next_node = next_node->left;
    }
    return next_node;
  }
  void removeNode(node<K, V> *node_to_remove) {
    if (!node_to_remove->left &&
        !node_to_remove->right) {  // у вершины нет детей
      // removeBalancing(node_to_remove);
      if (node_to_remove == node_) {
        node_ = nullptr;
      } else {
        if (node_to_remove == node_to_remove->parent->left)
          node_to_remove->parent->left = nullptr;
        else
          node_to_remove->parent->right = nullptr;
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
      if (node_to_remove == node_to_remove->parent->left) {
        node_to_remove->parent->left = next_node;
      } else {
        node_to_remove->parent->right = next_node;
      }
      next_node->parent = node_to_remove->parent;
    }
    if (next_node != node_to_remove) {
      node_to_remove->color = next_node->color;
      node_to_remove->key_value.first = next_node->key_value.first;
      node_to_remove->key_value.second = next_node->key_value.second;
      delete node_to_remove;
      return;
    }
    if (next_node->color == kBlack) {
      removeBalancing(node_to_remove);
    }
  }

  node<K, V> *insertNode(bool is_multiset, node<K, V> *parent, const K &key,
                         const V &value) {
    node<K, V> *current = parent;
    node<K, V> *last = parent;
    while (current != nullptr) {
      last = current;
      if (is_multiset) {
        if (key < current->key_value.first) {
          current = current->left;
        } else if (key >= current->key_value.first) {
          current = current->right;
        }
      } else {
        if (key < current->key_value.first) {
          current = current->left;
        } else if (key > current->key_value.first) {
          current = current->right;
        } else {
          return nullptr;
        }
      }
    }
    node<K, V> *new_node = new node<K, V>(key, value, kRed, last);
    if (key < last->key_value.first) {
      last->left = new_node;
    } else {
      last->right = new_node;
    }
    return new_node;
  }

  node<K, V> *binarySearch(node<K, V> *current_node, const K &key) {
    while (current_node != nullptr) {
      if (key < current_node->key_value.first) {
        current_node = current_node->left;
      } else if (key > current_node->key_value.first) {
        current_node = current_node->right;
      } else {
        return current_node;
      }
    }
    return nullptr;
  }
};

#endif  // CPP2_S21_CONTAINERS_S21_RB_TREE_H_