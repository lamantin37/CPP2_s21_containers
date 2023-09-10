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

  size_t getSize() { return size_; }
  node<K, V> *getNode() { return node_; }
  void insert_value(bool is_multiset, const K &key, const V &value = 0) {
    if (node_ == nullptr) {
      node_ = new node<K, V>(key, value, kBlack);
      size_++;
    } else {
      node<K, V> *newNode = insert_node(is_multiset, node_, key, value);
      if (newNode != nullptr) {
        insert_balancing(newNode);
        size_++;
      }
    }
  }
  node<K, V> *find_value(const K &key) { return binary_search(node_, key); }
  void remove_value(const K &key) {
    node<K, V> *removing_node = find_value(key);
    if (removing_node) {
      size_--;
      remove_node(removing_node);
    } else {
      std::cout << "No such value in the tree" << std::endl;
    }
  }
  node<K, V> *get_minimum() const {
    if (node_ == nullptr) {
      return nullptr;
    }

    node<K, V> *current = node_;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }
  node<K, V> *get_maximum() const {
    node<K, V> *current = node_;
    while (current && current->right != nullptr) {
      current = current->right;
    }
    return current;
  }

 private:
  node<K, V> *node_;
  size_t size_;
  void left_rotate(node<K, V> *root) {
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
  void right_rotate(node<K, V> *root) {
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
  bool is_black(node<K, V> *n) { return n != nullptr && n->color == kBlack; }
  bool is_red(node<K, V> *n) { return n != nullptr && n->color == kRed; }
  bool black_sibling_red_child(node<K, V> *n) {
    node<K, V> *s = get_sibling(n);
    return is_black(s) && (is_red(s->left) || is_red(s->right));
  }
  node<K, V> *get_sibling(node<K, V> *n) {
    if (n == n->parent->left)
      return n->parent->right;
    else
      return n->parent->left;
  }
  bool is_siblingRed(node<K, V> *n) {
    node<K, V> *s = get_sibling(n);
    return is_red(s);
  }
  void make_black(node<K, V> *n) {
    if (n != nullptr) n->color = kBlack;
  }
  void make_red(node<K, V> *n) {
    if (n != nullptr) n->color = kRed;
  }
  void insert_balancing(node<K, V> *root) {
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
            left_rotate(root);
          }
          root->parent->color = kBlack;
          root->parent->parent->color = kRed;
          right_rotate(root->parent->parent);
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
            right_rotate(root);
          }
          root->parent->color = kBlack;
          root->parent->parent->color = kRed;
          left_rotate(root->parent->parent);
        }
      }
    }
    node_->color = kBlack;
  }
  void remove_balancing(node<K, V> *tested_node) {
    if (!tested_node->parent) {
      if (tested_node->left) {
        node_ = tested_node->left;
      } else if (tested_node->right) {
        node_ = tested_node->right;
      } else {
        node_ = nullptr;
      }
      return;
    }
    if (tested_node->color == kBlack &&
        (tested_node->left == nullptr || tested_node->left->color == kBlack) &&
        (tested_node->right == nullptr ||
         tested_node->right->color == kBlack)) {
      make_red(tested_node);
      if (tested_node->parent) {
        remove_balancing(tested_node->parent);
      } else if (is_siblingRed(tested_node)) {  // брат красный
        node<K, V> *par =
            tested_node->parent;  // брат становится родителем отца
        node<K, V> *sib = get_sibling(tested_node);
        make_red(par);    // красим отца в красный
        make_black(sib);  // а брата в чёрный
        if (tested_node == par->left) {
          left_rotate(par);
        } else {
          right_rotate(par);
        }
        remove_balancing(tested_node);
      } else if (black_sibling_red_child(
                     tested_node)) {  // черный брат с красным ребёнком
        node<K, V> *par = tested_node->parent;
        node<K, V> *sib = get_sibling(tested_node);
        if (is_black(sib->right)) {  // чёрный правый ребенок
          make_black(sib->left);  // перекрашиваем красного правого ребенка
                                  // брата в чёрный
          make_red(sib);  // а брата в чёрный
          right_rotate(sib);
        } else {  // красный правый ребёнок
          sib->color = par->color;  // перекрашиваем брата в цвет отца
          make_black(par);  // перекрашиваем отца в чёрный
          make_black(sib->right);  // и ребёнка тоже в чёрный
          if (tested_node == par->left) {
            left_rotate(par);
          } else {
            right_rotate(par);
          }
        }
      } else {  // оба рёбнка брата чёрные
        make_red(get_sibling(tested_node));
        if (!is_red(tested_node->parent)) {
          remove_balancing(tested_node->parent);
        } else {
          make_black(tested_node->parent);
        }
      }
    }
  }
  node<K, V> *get_next(node<K, V> *current) {
    node<K, V> *next_node = current;
    while (next_node->left) {
      next_node = next_node->left;
    }
    return next_node;
  }
  void remove_node(node<K, V> *node_to_remove) {
    if (!node_to_remove->left &&
        !node_to_remove->right) {  // у вершины нет детей
      if (node_to_remove == node_to_remove->parent->left) {
        node_to_remove->parent->left = nullptr;
      } else {
        node_to_remove->parent->right = nullptr;
      }
      remove_balancing(node_to_remove);
      delete node_to_remove;
      return;
    } else if (node_to_remove->left &&
               node_to_remove->right) {  // у вершины есть оба ребёнка
      node<K, V> *leftmost_node = get_next(node_to_remove->right);
      node_to_remove->key_value.first = leftmost_node->key_value.first;
      remove_node(leftmost_node);
      return;
    } else if (node_to_remove->left ||
               node_to_remove->right) {  // у вершины один ребёнок
      if (node_to_remove->left) {
        if ((node_to_remove == node_to_remove->parent->left)) {
          node_to_remove->parent->left = node_to_remove->left;
          node_to_remove->left->parent = node_to_remove->parent;
        } else {
          node_to_remove->parent->right = node_to_remove->left;
          node_to_remove->left->parent = node_to_remove->parent;
        }
      } else if (node_to_remove->right) {
        if ((node_to_remove == node_to_remove->parent->left)) {
          node_to_remove->parent->left = node_to_remove->right;
          node_to_remove->right->parent = node_to_remove->parent;
        } else {
          node_to_remove->parent->right = node_to_remove->right;
          node_to_remove->right->parent = node_to_remove->parent;
        }
      }
      remove_balancing(node_to_remove);
      delete node_to_remove;
      return;
    }
  }

  node<K, V> *insert_node(bool is_multiset, node<K, V> *parent, const K &key,
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

  node<K, V> *binary_search(node<K, V> *current_node, const K &key) {
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