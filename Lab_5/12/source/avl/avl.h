#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"
// #include "safe_allocator.h"
// #include "complete_logger.h"

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class avl_tree:
    public binary_search_tree<tkey, tvalue, tkey_comparer>
{
    
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

    void get_something();
    

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
void avl_tree<tkey, tvalue, tkey_comparer>::get_something() {
    this->begin_prefix();
}





#endif