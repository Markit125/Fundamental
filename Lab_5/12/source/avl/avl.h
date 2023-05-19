#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"
#include <cstddef>
// #include "safe_allocator.h"
// #include "complete_logger.h"

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class avl_tree:
    public binary_search_tree<tkey, tvalue, tkey_comparer> {
    
public:

    explicit avl_tree(
        allocating::memory *allocator = nullptr,
        logging::logger *logger = nullptr);

    // avl_tree(
    //     avl_tree const &other);

    // avl_tree(
    //     avl_tree &&other) noexcept;

    // avl_tree &operator=(
    //     avl_tree const &other);

    // avl_tree &operator=(
    //     avl_tree &&other) noexcept;

    ~avl_tree() override = default;


protected:

    struct avl_tree_node : binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node {

        size_t height;
    };


private:

    size_t get_height(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const;

    int balance_factor(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const;

    void fix_height(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **node);

protected:

    void after_insert_inner(
            tkey const &key,
            tvalue &&value,
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
            std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    void after_remove_inner(
            tkey const &key,
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
            std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    void after_read_inner(
            tkey const &key,
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
            std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

};

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
    allocating::memory *allocator,
    logging::logger *logger): binary_search_tree<tkey, tvalue, tkey_comparer>(allocator, logger) {
    
        // tree_node *node;

    this->safe_log("AVL tree is created", logging::logger::severity::information);
    // _root;
    // _allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::get_height(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const {
    
    return node ? (node->height) : 0;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
int avl_tree<tkey, tvalue, tkey_comparer>::balance_factor(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const {
    
    return get_height(node->left_subtree_address) - get_height(node->right_subtree_address);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::fix_height(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **node) {
    
    (*node)->height = max(get_height((*node)->left_subtree_address), get_height((*node)->right_subtree_address)) + 1;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::after_insert_inner(
    tkey const &key,
    tvalue &&value,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::after_remove_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::after_read_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    
}

#endif