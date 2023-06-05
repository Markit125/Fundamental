#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../../../11/source/tree/binary_search_tree.h"
#include <cstddef>
#include <exception>
#include <iostream>

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
            std::cout << "\nTree ==================\n\n";
        }

        if (nullptr != subtree_root) {
            print_tree(subtree_root->right_subtree_address, deep + 1);
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

        print_tree(subtree_root->left_subtree_address, deep + 1);
    };

    print_tree(this->_root, 0);
    std::cout << "\nTree end ==============\n";
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
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::get_height(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) const {
    
    this->safe_log("Get height " + cast_to_str(node ? reinterpret_cast<avl_tree_node *>(node)->height : 0), logging::logger::severity::trace);

    return nullptr != node ? reinterpret_cast<avl_tree_node *>(node)->height : 0;
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
    
    this->safe_log("______Fix height______", logging::logger::severity::debug);

    if (nullptr != *node) {
        // this->safe_log(cast_to_str((*node)->key), logging::logger::severity::debug);
    }


    size_t left;
    size_t right;

    if (nullptr == *node) {
        this->safe_log("nullptr in fix height", logging::logger::severity::debug);
        left = right = 0;
    } else {
        left = get_height((*node)->left_subtree_address);
        right = get_height((*node)->right_subtree_address);
    }

    this->safe_log("Fix height left, right {"  + cast_to_str(left) + ", " + cast_to_str(right) + "}", logging::logger::severity::debug);
    if (nullptr != *node) {

        // this->safe_log("Keys left, right {"  + cast_to_str((*node)->left_subtree_address ? cast_to_str((*node)->left_subtree_address->key) : "NULL") + ", "
        //     + cast_to_str((*node)->right_subtree_address ? cast_to_str((*node)->right_subtree_address->key) : "NULL") + "}", logging::logger::severity::debug);
        reinterpret_cast<avl_tree_node *>(*node)->height = std::max(left, right) + 1;

        this->safe_log("Now height is " + cast_to_str(reinterpret_cast<avl_tree_node *>(*node)->height),
            logging::logger::severity::debug);
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

    // _tree->safe_log("_____After insert inner_____ key " + cast_to_str(key), logging::logger::severity::debug);
    _tree->safe_log(cast_to_str(subtree_root_address), logging::logger::severity::debug);
    
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **parent = nullptr;

    if (!path_to_subtree_root_exclusive.empty()) {
        parent = path_to_subtree_root_exclusive.top();
    }


    if (nullptr != subtree_root_address) {
        // _tree->safe_log("key: " + cast_to_str(subtree_root_address->key), logging::logger::severity::debug);
    }

    _tree->fix_height(&subtree_root_address);

    int balance = _tree->balance_factor(subtree_root_address);

    _tree->safe_log("balance factor has ended", logging::logger::severity::debug);
    _tree->safe_log("Balance factor " + cast_to_str(balance), logging::logger::severity::debug);


    if (balance == 2) {

        // std::cout << "before:\n";
        // _tree->print_container();

        if (_tree->balance_factor(subtree_root_address->left_subtree_address) == -1)
        {
                _tree->safe_log(">>>>>>> BIG left rotation", logging::logger::severity::debug);
            _tree->left_rotation(&(subtree_root_address->left_subtree_address), &subtree_root_address);

            _tree->fix_height(&(subtree_root_address->left_subtree_address->left_subtree_address));
            _tree->fix_height(&(subtree_root_address->left_subtree_address));

            // std::cout << "half way:\n";
            // _tree->print_container();
        }

        _tree->safe_log(">>>>>>> right rotation", logging::logger::severity::debug);

        _tree->right_rotation(&subtree_root_address, parent);

        _tree->fix_height(&(subtree_root_address->right_subtree_address));
        _tree->fix_height(&subtree_root_address);


        // std::cout << "after:\n";
        // _tree->print_container();

    } else if (balance == -2) {

        // std::cout << "before:\n";
        // _tree->print_container();

        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1)
        {
            _tree->safe_log(">>>>>>> BIG right rotation", logging::logger::severity::debug);

            _tree->right_rotation(&(subtree_root_address->right_subtree_address), &subtree_root_address);

            _tree->fix_height(&(subtree_root_address->right_subtree_address->right_subtree_address));
            _tree->fix_height(&(subtree_root_address->right_subtree_address));

            // std::cout << "half way:\n";
            // _tree->print_container();
        }

            _tree->safe_log(">>>>>>> left rotation", logging::logger::severity::debug);

        _tree->left_rotation(&subtree_root_address, parent);

        _tree->fix_height(&(subtree_root_address->left_subtree_address));
        _tree->fix_height(&subtree_root_address);

        // std::cout << "after:\n";
        // _tree->print_container();
    }

    _tree->safe_log("After insert inner ended", logging::logger::severity::debug);

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

    if (nullptr == subtree_root_address) {
        return;
    }


    // _tree->safe_log("_____After remove inner_____ key removing " + cast_to_str(key), logging::logger::severity::debug);
    
    _tree->safe_log(cast_to_str(subtree_root_address), logging::logger::severity::debug);


    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **parent = nullptr;
    if (!path_to_subtree_root_exclusive.empty()) {
        parent = path_to_subtree_root_exclusive.top();
    }

    // _tree->safe_log("key: " + cast_to_str(subtree_root_address->key), logging::logger::severity::debug);
    

    _tree->fix_height(&subtree_root_address);

    int balance = _tree->balance_factor(subtree_root_address);

    _tree->safe_log("Balance factor " + cast_to_str(balance), logging::logger::severity::debug);


    if (balance == 2) {

        // std::cout << "before:\n";
        _tree->print_container();

        if (_tree->balance_factor(subtree_root_address->left_subtree_address) == -1)
        {
                _tree->safe_log(">>>>>>> BIG left rotation", logging::logger::severity::debug);
            _tree->left_rotation(&(subtree_root_address->left_subtree_address), &subtree_root_address);

            _tree->fix_height(&(subtree_root_address->left_subtree_address->left_subtree_address));
            _tree->fix_height(&(subtree_root_address->left_subtree_address));

            // std::cout << "half way:\n";
            _tree->print_container();
        }


        _tree->safe_log(">>>>>>> right rotation", logging::logger::severity::debug);

        _tree->right_rotation(&subtree_root_address, parent);

        _tree->fix_height(&(subtree_root_address->right_subtree_address));
        _tree->fix_height(&subtree_root_address);


        // std::cout << "after:\n";
        _tree->print_container();

    } else if (balance == -2) {

        // std::cout << "before:\n";
        _tree->print_container();

        if (_tree->balance_factor(subtree_root_address->right_subtree_address) == 1)
        {
            _tree->safe_log(">>>>>>> BIG right rotation", logging::logger::severity::debug);


            _tree->right_rotation(&(subtree_root_address->right_subtree_address), &subtree_root_address);

            _tree->fix_height(&(subtree_root_address->right_subtree_address->right_subtree_address));
            _tree->fix_height(&(subtree_root_address->right_subtree_address));

            // std::cout << "half way:\n";
            _tree->print_container();
        }

            _tree->safe_log(">>>>>>> left rotation", logging::logger::severity::debug);

        _tree->left_rotation(&subtree_root_address, parent);

        _tree->fix_height(&(subtree_root_address->left_subtree_address));
        _tree->fix_height(&subtree_root_address);

        // std::cout << "after:\n";
        _tree->print_container();
    }

    _tree->safe_log("After remove inner ended", logging::logger::severity::debug);

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
                
    this->safe_log("AVL tree is created", logging::logger::severity::debug);

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::~avl_tree() {

}

#endif