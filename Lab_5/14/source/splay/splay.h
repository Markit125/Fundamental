#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "../../../11/source/tree/binary_search_tree.h"
#include <cstddef>
#include <exception>


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class splay_tree:
    public binary_search_tree<tkey, tvalue, tkey_comparer> {
    
public:

    explicit splay_tree(
        allocating::memory *allocator = nullptr,
        logging::logger *logger = nullptr);

    splay_tree(
        splay_tree const &other);

    splay_tree(
        splay_tree &&other) noexcept;

    splay_tree &operator=(
        splay_tree const &other);

    splay_tree &operator=(
        splay_tree &&other) noexcept;



private:

    void splay(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive);

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *merge(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node_left,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node_right);


public:

    void print_container() const override;


protected:

    class insertion_template_method_splay : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method {

    private:

        splay_tree<tkey, tvalue, tkey_comparer> *_tree;


    public:

        explicit insertion_template_method_splay(splay_tree<tkey, tvalue, tkey_comparer> *tree);


    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    };


    class reading_template_method_splay final : public binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method {

    public:

        explicit reading_template_method_splay(splay_tree<tkey, tvalue, tkey_comparer> *tree);


    private:

        splay_tree<tkey, tvalue, tkey_comparer> *_tree;

    protected:

        void after_read_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

    };


    class removing_template_method_splay final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method {

    public:

        explicit removing_template_method_splay(splay_tree<tkey, tvalue, tkey_comparer> *tree);


    private:

        splay_tree<tkey, tvalue, tkey_comparer> *_tree;

        tvalue &&remove_inner(
            tkey const &key,
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
            std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) override;

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
void splay_tree<tkey, tvalue, tkey_comparer>::print_container() const {

    std::function<void(typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *, size_t)> print_tree;
    print_tree = [&](typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *subtree_root, size_t deep) {

        if (deep == 0) {
            std::cout << "\nTree:\n";
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
            s += "NULL";
            std::cout << s << std::endl;
            return;
        }

        std::cout << s << subtree_root->key << std::endl;

        print_tree(subtree_root->left_subtree_address, deep + 1);
    };

    print_tree(this->_root, 0);

}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **parent = nullptr;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **grand = nullptr;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **great_grand = nullptr;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node = subtree_root_address;
    
    this->safe_log("splay has started", logging::logger::severity::information);

    while (!path_to_subtree_root_exclusive.empty()) {

        parent = path_to_subtree_root_exclusive.top();
        path_to_subtree_root_exclusive.pop();

        if (path_to_subtree_root_exclusive.empty()) {

            this->safe_log("one rotation needed", logging::logger::severity::information);

            if ((*parent)->left_subtree_address == node) {

                this->safe_log("right rotation", logging::logger::severity::information);

                this->right_rotation(parent, nullptr);

            } else {

                this->safe_log("left rotation", logging::logger::severity::information);

                this->left_rotation(parent, nullptr);
            }

            node = *parent;

        } else {

            this->safe_log("two rotations needed", logging::logger::severity::information);

            grand = path_to_subtree_root_exclusive.top();
            path_to_subtree_root_exclusive.pop();

            if (!path_to_subtree_root_exclusive.empty()) {

                this->safe_log("great grand parent exists", logging::logger::severity::information);

                great_grand = path_to_subtree_root_exclusive.top();
                
            }

            if ((*grand)->left_subtree_address == *parent) {

                if ((*parent)->left_subtree_address == node) {

                    this->safe_log("right-right rotations", logging::logger::severity::information);
                    
                    this->right_rotation(grand, great_grand);
                    this->right_rotation(grand, great_grand);
                    node = *grand;

                } else {

                    this->safe_log("left-right rotations", logging::logger::severity::information);

                    this->left_rotation(parent, grand);
                    this->right_rotation(grand, great_grand);
                    node = *grand;
                }

            } else {

                if ((*parent)->left_subtree_address == node) {

                    this->safe_log("right-left rotations", logging::logger::severity::information);

                    this->right_rotation(parent, grand);
                    this->left_rotation(grand, great_grand);
                    node = *grand;

                } else {

                    this->safe_log("left-left rotations", logging::logger::severity::information);

                    this->left_rotation(grand, great_grand);
                    this->left_rotation(grand, great_grand);
                    node = *grand;
                }
            }
        }

        great_grand = nullptr;
        grand = nullptr;
        parent = nullptr;
    }

    this->safe_log("splay has ended", logging::logger::severity::information);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *splay_tree<tkey, tvalue, tkey_comparer>::merge(
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node_left,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node_right) {

    this->safe_log("merge", logging::logger::severity::error);

    if (nullptr == node_left) {
        return node_right;
    }

    if (nullptr == node_right) {
        return node_left;
    }

    if (nullptr == node_left && nullptr == node_right) {
        return nullptr;
    }

    this->safe_log("merge has started", logging::logger::severity::error);

    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> path_to_subtree_root_exclusive;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *max_left = node_left;

    while (nullptr != max_left->right_subtree_address) {

        path_to_subtree_root_exclusive.push(&max_left);
        max_left = max_left->right_subtree_address;
    }

    splay(max_left, path_to_subtree_root_exclusive);

    node_left->right_subtree_address = node_right;

    this->safe_log("merge has ended", logging::logger::severity::warning);

    return node_left;
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_splay::insertion_template_method_splay(
        splay_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree),
        _tree(tree) { }


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::reading_template_method_splay::reading_template_method_splay(
        splay_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(tree),
        _tree(tree) { }


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::removing_template_method_splay::removing_template_method_splay(
        splay_tree<tkey, tvalue, tkey_comparer> *tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree),
        _tree(tree) { }


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::insertion_template_method_splay::after_insert_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);

    _tree->splay(subtree_root_address, path_to_subtree_root_exclusive);
    
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&splay_tree<tkey, tvalue, tkey_comparer>::removing_template_method_splay::remove_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {


    if (nullptr == subtree_root_address) {
        throw std::runtime_error("No such key in a tree!");
    }

    int comparation = _tree->_comparator(subtree_root_address->key, key);

    if (comparation == 0) {
        
        tvalue &&value_to_remove = std::move(subtree_root_address->value);

        _tree->safe_log("found a key (" + cast_to_str(key) + ")", logging::logger::severity::warning);

        _tree->safe_log("subt " + cast_to_str(subtree_root_address), logging::logger::severity::warning);
        _tree->splay(subtree_root_address, path_to_subtree_root_exclusive);
        _tree->safe_log("subt " + cast_to_str(subtree_root_address), logging::logger::severity::warning);

        _tree->print_container();


        typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *left_subtree = _tree->_root->left_subtree_address;
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *right_subtree = _tree->_root->right_subtree_address;


        _tree->_root->~tree_node();
        _tree->safe_deallocate(_tree->_root);
        _tree->_root = nullptr;


        _tree->_root = _tree->merge(left_subtree, right_subtree);

        _tree->print_container();

        return std::move(value_to_remove);
    }

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **next_node = &(comparation > 0 ? subtree_root_address->right_subtree_address : subtree_root_address->left_subtree_address);

    path_to_subtree_root_exclusive.push(&subtree_root_address);

    tvalue &&value_to_remove = std::move(remove_inner(key, *next_node, path_to_subtree_root_exclusive));

    return std::move(value_to_remove);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::removing_template_method_splay::after_remove_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(path_to_subtree_root_exclusive);
    UNUSED(subtree_root_address);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::reading_template_method_splay::after_read_inner(
    tkey const &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);

    _tree->splay(subtree_root_address, path_to_subtree_root_exclusive);
}



template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(
    allocating::memory *allocator,
    logging::logger *logger) :
    binary_search_tree<tkey, tvalue, tkey_comparer>(
        new insertion_template_method_splay(this),
        new reading_template_method_splay(this),
        new removing_template_method_splay(this),
        this->_comparator,
        allocator,
        logger,
        nullptr) {
                
    this->safe_log("Splay tree is created", logging::logger::severity::debug);

}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(
    const splay_tree<tkey, tvalue, tkey_comparer> &other) :
    binary_search_tree<tkey, tvalue, tkey_comparer>(
        new insertion_template_method_splay(this),
        new reading_template_method_splay(this),
        new removing_template_method_splay(this),
        other._comparator,
        other._allocator,
        other._logger,
        nullptr)
{
    this->safe_log("Splay tree is coping", logging::logger::severity::information);
    
    auto item = other.begin_prefix();
    auto end = other.end_prefix();

    for (; item != end; ++item) {

        auto node = item.get_node_pointer();
        tvalue value = node->value;

        this->insert(node->key, std::move(value));
    }

    this->safe_log("Splay tree is copied", logging::logger::severity::information);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(
    splay_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
{
    this->safe_log("Splay tree is moving", logging::logger::severity::information);
    
    this->_insertion = other._insertion;
    this->_reading = other._reading;
    this->_removing = other._removing;
    this->_comparator = other._comparator;
    this->_allocator = other._allocator;
    this->_logger = other._logger;
    this->_root = other._root;

    other._root = nullptr;
    other._insertion = nullptr;
    other._reading = nullptr;
    other._removing = nullptr;

    this->safe_log("Splay tree is moved", logging::logger::severity::information);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer> &splay_tree<tkey, tvalue, tkey_comparer>::operator=(
    splay_tree const &other)
{
    this->safe_log("Splay tree is coping by '='", logging::logger::severity::information);

    this->_insertion = new insertion_template_method_splay(this);
    this->_reading = new reading_template_method_splay(this);
    this->_removing = new removing_template_method_splay(this);
    this->_comparator = other._comparator;
    this->_allocator = other._allocator;
    this->_logger = other._logger;

    
    auto item = other.begin_prefix();
    auto end = other.end_prefix();

    for (; item != end; ++item) {

        auto node = item.get_node_pointer();
        tvalue value = node->value;

        this->insert(node->key, std::move(value));
    }

    this->safe_log("Splay tree is copied", logging::logger::severity::information);

    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer> &splay_tree<tkey, tvalue, tkey_comparer>::operator=(
    splay_tree &&other) noexcept
{
    this->safe_log("Splay tree is moving by '='", logging::logger::severity::information);
    
    this->_insertion = other._insertion;
    this->_reading = other._reading;
    this->_removing = other._removing;
    this->_comparator = other._comparator;
    this->_allocator = other._allocator;
    this->_logger = other._logger;
    this->_root = other._root;

    other._root = nullptr;
    other._insertion = nullptr;
    other._reading = nullptr;
    other._removing = nullptr;

    this->safe_log("Splay tree is moved", logging::logger::severity::information);

    return *this;
}

#endif