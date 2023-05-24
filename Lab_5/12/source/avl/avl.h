#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../../../11/source/tree/binary_search_tree.h"
#include <cstddef>

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

    ~avl_tree();


protected:

    struct avl_tree_node : binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node {

        // struct binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node binary_tree;

        size_t height = 0;

    };


private:

    size_t get_height(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const;

    int balance_factor(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const;

    void fix_height(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **node);
    
    void print_container() const override;


protected:

    class insertion_template_method_avl : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method {

    private:

        avl_tree<tkey, tvalue, tkey_comparer> *_tree;


    public:

        explicit insertion_template_method_avl(avl_tree<tkey, tvalue, tkey_comparer> *tree);


    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    private:

        size_t get_size_node() const override;

        void initialize_new_node(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&new_node, tkey const &key, tvalue &&value) const override;

    };


    class reading_template_method_avl final : public binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method {

    public:

        explicit reading_template_method_avl(avl_tree<tkey, tvalue, tkey_comparer> *tree);


    private:

        avl_tree<tkey, tvalue, tkey_comparer> *_tree;

    protected:

        void after_read_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    };


    class removing_template_method_avl final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method {

    public:

        explicit removing_template_method_avl(avl_tree<tkey, tvalue, tkey_comparer> *tree);


    private:

        avl_tree<tkey, tvalue, tkey_comparer> *_tree;

    protected:

        void after_remove_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    };
    
};


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::print_container() const {

    std::function<void(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *, size_t)> print_tree;
    print_tree = [&](typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *subtree_root, size_t deep) {

        if (deep == 0) {
            std::cout << "\nTree:\n";
        }

        if (nullptr != subtree_root) {
            print_tree(subtree_root->left_subtree_address, deep + 1);
        }

        std::string s;


        for (size_t i = 0; i < deep; ++i) {
            s += "\t";
        }
        s += "______";


        if (subtree_root == nullptr) {
            s += "NULL (" + cast_to_str(get_height(subtree_root)) + ")\n";
            std::cout << s;
            return;
        }

        std::cout << s << subtree_root->key << " (" << get_height(subtree_root) << ")" << std::endl;

        print_tree(subtree_root->right_subtree_address, deep + 1);
    };

    print_tree(this->_root, 0);

}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_avl::get_size_node() const {

    return sizeof(avl_tree_node);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_avl::initialize_new_node(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&new_node, tkey const &key, tvalue &&value) const {

    new (new_node) typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node {key, std::move(value), nullptr, nullptr};
    // new (reinterpret_cast<avl_tree_node *>(new_node)) avl_tree_node {key, std::move(value), nullptr, nullptr, 0};
}

// template<
//     typename tkey,
//     typename tvalue,
//     typename tkey_comparer>
// avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
//     allocating::memory *allocator,
//     logging::logger *logger): binary_search_tree<tkey, tvalue, tkey_comparer>(allocator, logger) {
    
    
// }

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::get_height(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const {
    
    this->safe_log("Get height " + cast_to_str(node ? reinterpret_cast<avl_tree_node *>(node)->height : 0), logging::logger::severity::trace);


    return node ? reinterpret_cast<avl_tree_node *>(node)->height : 0;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
int avl_tree<tkey, tvalue, tkey_comparer>::balance_factor(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const {
    
    if (node) {
        return get_height(node->left_subtree_address) - get_height(node->right_subtree_address);
    }

    return 0;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::fix_height(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **node) {
    

    // if (nullptr != node) {
    //     reinterpret_cast<avl_tree_node *>(node)->height = std::max(get_height((node)->left_subtree_address),
    //         get_height((node)->right_subtree_address)) + 1;
    // }

    size_t left;
    size_t right;

    if (nullptr == *node) {
        this->safe_log("nullllllllllllllllll fixheight", logging::logger::severity::information);
        left = right = 0;
    } else {
        left = get_height((*node)->left_subtree_address);
        right = get_height((*node)->right_subtree_address);
    }

    this->safe_log("Fix height left, right {"  + cast_to_str(left) + ", " + cast_to_str(right) + "}", logging::logger::severity::information);

    if (nullptr != *node) {
        reinterpret_cast<avl_tree_node *>(*node)->height = std::max(left, right) + 1;

        this->safe_log("Height is " + cast_to_str(reinterpret_cast<avl_tree_node *>(*node)->height),
            logging::logger::severity::information);
    }

    

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_avl::insertion_template_method_avl(
        avl_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree),
        _tree(tree)
{

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::reading_template_method_avl::reading_template_method_avl(
        avl_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(tree),
        _tree(tree)
{

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::removing_template_method_avl::removing_template_method_avl(
        avl_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree),
        _tree(tree)
{

}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_avl::after_insert_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(path_to_subtree_root_exclusive);

    _tree->safe_log("_____After insert inner_____", logging::logger::severity::trace);
    _tree->safe_log("___________________AVL___________________", logging::logger::severity::trace);
    
    _tree->safe_log(cast_to_str(subtree_root_address), logging::logger::severity::trace);
    if (nullptr != subtree_root_address) {
        _tree->safe_log("key: " + cast_to_str(subtree_root_address->key), logging::logger::severity::trace);
    }


    
    _tree->fix_height(&subtree_root_address);

    _tree->safe_log("fix height has ended", logging::logger::severity::trace);

    int balance = _tree->balance_factor(subtree_root_address);

    _tree->safe_log("balance factor has ended", logging::logger::severity::trace);

    _tree->safe_log("Balance factor " + cast_to_str(balance), logging::logger::severity::information);

    if (balance == -2) {
        // left rotation


        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1) {
            // right rotation

            // avl_tree_node **node = &(subtree_root_address->right_subtree_address);
            // _tree->right_rotation(*node);
            _tree->right_rotation(subtree_root_address->right_subtree_address);

            _tree->fix_height(&(subtree_root_address));
            _tree->fix_height(&(subtree_root_address->right_subtree_address));

        }

        // avl_tree_node **node = &(subtree_root_address->left_subtree_address);
        // _tree->left_rotation(*node);
        _tree->left_rotation(subtree_root_address);

        _tree->fix_height(&(subtree_root_address));
        _tree->fix_height(&(subtree_root_address->left_subtree_address));

    } else if (balance == 2) {
        // right rotation

        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1) {
            // left rotation

            // avl_tree_node **node = &(subtree_root_address->left_subtree_address);
            // _tree->left_rotation(*node);
            _tree->left_rotation(subtree_root_address->left_subtree_address);

            _tree->fix_height(&(subtree_root_address));
            _tree->fix_height(&(subtree_root_address->left_subtree_address));

        }

        // avl_tree_node **node = &(subtree_root_address->right_subtree_address);
        // _tree->right_rotation(*node);
        _tree->right_rotation(subtree_root_address);

        _tree->fix_height(&(subtree_root_address));
        _tree->fix_height(&(subtree_root_address->right_subtree_address));
    }

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::removing_template_method_avl::after_remove_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(path_to_subtree_root_exclusive);
    // _tree->after_insert_inner(key, subtree_root_address, path_to_subtree_root_exclusive);


    _tree->safe_log("_____After remove inner_____", logging::logger::severity::);
    _tree->safe_log("___________________AVL___________________", logging::logger::severity::trace);
    
    _tree->safe_log(cast_to_str(subtree_root_address), logging::logger::severity::trace);



    _tree->fix_height(&subtree_root_address);

    int balance = _tree->balance_factor(subtree_root_address);

    if (balance == -2) {
        // left rotation

        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1) {
            // right rotation

            _tree->right_rotation(subtree_root_address->right_subtree_address);
            _tree->fix_height(&(subtree_root_address));
            _tree->fix_height(&(subtree_root_address->right_subtree_address));

        }

        _tree->left_rotation(subtree_root_address);
        _tree->fix_height(&(subtree_root_address));
        _tree->fix_height(&(subtree_root_address->left_subtree_address));

    } else if (balance == 2) {
        // right rotation

        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1) {
            // left rotation

            _tree->left_rotation(subtree_root_address->left_subtree_address);
            _tree->fix_height(&(subtree_root_address));
            _tree->fix_height(&(subtree_root_address->left_subtree_address));

        }

        _tree->right_rotation(subtree_root_address);
        _tree->fix_height(&(subtree_root_address));
        _tree->fix_height(&(subtree_root_address->right_subtree_address));
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::reading_template_method_avl::after_read_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
}



template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
    allocating::memory *allocator,
    logging::logger *logger) :
    binary_search_tree<tkey, tvalue, tkey_comparer>(
        new insertion_template_method_avl(this),
        new reading_template_method_avl(this),
        new removing_template_method_avl(this),
        allocator,
        logger,
        nullptr) {
                
    this->safe_log("AVL tree is created", logging::logger::severity::information);

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::~avl_tree() {

}

#endif