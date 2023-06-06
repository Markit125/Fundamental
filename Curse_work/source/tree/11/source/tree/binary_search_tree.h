#ifndef SANDBOX_CPP_BINARY_SEARCH_TREE_H
#define SANDBOX_CPP_BINARY_SEARCH_TREE_H

#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#define UNUSED(expr) do { (void)(expr); } while (0)


#include "../../../../data/type_data/type_data.h"
#include "../../../../memory/3/source/memory_with_list/memory_with_list.h"
#include "associative_container.h"
#include "../../../../logger/source/logger/complete/complete_logger.h"
#include "../../../11/source/allocator/safe_allocator.h"


template <class T>
std::string cast_to_str(const T& object) {

    std::stringstream ss;
    ss << object;
    
    return ss.str();
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class binary_search_tree:
    public associative_container<tkey, tvalue>, protected logging::complete_logger, protected allocating::safe_allocator
{

protected:

    struct tree_node
    {
        
        tkey key;

        tvalue value;

        tree_node *left_subtree_address;

        tree_node *right_subtree_address;

    };

public:

    class prefix_iterator final
    {

    private:

        tree_node *_tree_root;
        std::stack<tree_node *> _way;

        tree_node *_current;
        tree_node *_begin;
        tree_node *_end;

    public:

        explicit prefix_iterator(
            tree_node *tree_root,
            tree_node *begin_or_end_node);

        tree_node *get_node_pointer() const;

        void set_iterator(tree_node *);

    public:

        bool operator==(
            prefix_iterator const &other) const;

        bool operator!=(
            prefix_iterator const &other) const;

        prefix_iterator& operator++();

        prefix_iterator operator++(
            int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;        

    };

    class infix_iterator final
    {

    private:

        tree_node *_tree_root;
    public:
        std::stack<tree_node *> _way;

        tree_node *_current;
        tree_node *_begin;
        tree_node *_end;

    public:

        explicit infix_iterator(
            tree_node *tree_root,
            tree_node *begin_or_end_node);

        tree_node *get_node_pointer() const;

        void set_iterator(tree_node *, std::stack<binary_search_tree::tree_node *> &path_to_subtree_root_exclusive);

    public:

        bool operator==(
            infix_iterator const &other) const;

        bool operator!=(
            infix_iterator const &other) const;

        infix_iterator& operator++();

        infix_iterator operator++(
            int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

    class postfix_iterator final
    {

    private:

        tree_node *_tree_root;
        std::stack<tree_node *> _way;

        tree_node *_current;
        tree_node *_begin;
        tree_node *_end;

    public:

        explicit postfix_iterator(
            tree_node *tree_root,
            tree_node *begin_or_end_node);

        tree_node *get_node_pointer() const;

    public:

        bool operator==(
            postfix_iterator const &other) const;

        bool operator!=(
            postfix_iterator const &other) const; 

        postfix_iterator &operator++();

        postfix_iterator operator++(
            int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

protected:

    class insertion_template_method : private allocating::safe_allocator, private logging::complete_logger
    {

    public:

        virtual ~insertion_template_method() = default;

        insertion_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree)
            : _tree(tree) {}

    public:

        void insert(
            tkey const &key,
            tvalue &&value,
            tree_node *&tree_root_address);

    private:

        void insert_inner(
            tkey const &key,
            tvalue &&value,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void after_insert_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);

    private:

        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const override;

        allocating::memory *get_allocator() const override;

    protected:

        virtual size_t get_size_node() const;

        virtual void initialize_new_node(
            tree_node *&new_node, tkey const &key, tvalue &&value) const;

    };

    class reading_template_method : private allocating::safe_allocator, private logging::complete_logger
    {

    public:

        virtual ~reading_template_method() = default;
        reading_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree)
            : _tree(tree) {}

    public:

        tvalue const &read(
            tkey const &key,
            tree_node *&tree_root_address);

        bool find(
            tkey const &key,
            tree_node *&tree_root_address,
            std::pair<tkey, tvalue *> *found);

        void find_left_bound(
            tkey const &key,
            tree_node *&tree_root_address,
            std::stack<binary_search_tree::tree_node *> &path_to_subtree_root_exclusive,
            tree_node *&node_need);

    private:

        tvalue const &read_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void after_read_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);
    
    private:
        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const override;

        allocating::memory *get_allocator() const override;

    };

    class removing_template_method : private allocating::safe_allocator, private logging::complete_logger
    {

    public:

        virtual ~removing_template_method() = default;
        removing_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree)
            : _tree(tree) {}

    public:

        tvalue &&remove(
            tkey const &key,
            tree_node *&tree_root_address);

    private:

        tvalue &&remove_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void after_remove_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive);

    private:
        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const override;

        allocating::memory *get_allocator() const override;

    };

protected:

    insertion_template_method *_insertion;
    reading_template_method *_reading;
    removing_template_method *_removing;
    allocating::memory *_allocator;
    logging::logger *_logger;
    tree_node *_root;

protected:

    explicit binary_search_tree(
        insertion_template_method *insertion,
        reading_template_method *reading,
        removing_template_method *removing,
        allocating::memory *allocator = nullptr,
        logging::logger *logger = nullptr, 
        tree_node *root = nullptr);

public:

    explicit binary_search_tree(
        allocating::memory *allocator = nullptr,
        logging::logger *logger = nullptr);

    binary_search_tree(
        binary_search_tree const &other);

    binary_search_tree(
        binary_search_tree &&other) noexcept;

    binary_search_tree &operator=(
        binary_search_tree const &other);

    binary_search_tree &operator=(
        binary_search_tree &&other) noexcept;

    ~binary_search_tree() override;

public:

    void insert(
        tkey const &key,
        tvalue &&value) final override;

    tvalue const &get(
        tkey const &key) final override;

    tvalue &&remove(
        tkey const &key) final override;

    bool find(
        tkey const &key, std::pair<tkey, tvalue *> *found) final override;


private:

    void find_left_bound(tkey const &key,
        std::stack<tree_node *> &path_to_subtree_root_exclusive,
        tree_node *&node_need);

private:

    logging::logger *get_logger() const override;

    allocating::memory *get_allocator() const override;

public:

    prefix_iterator begin_prefix() const noexcept;

    prefix_iterator end_prefix() const noexcept;

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    postfix_iterator begin_postfix() const noexcept;

    postfix_iterator end_postfix() const noexcept;

protected:

    virtual void left_rotation(tree_node **subtree_root, tree_node **parent) const;

    virtual void right_rotation(tree_node **subtree_root, tree_node **parent) const;

public:

    void print_prefix() const;

    void print_infix() const;

    void print_postfix() const;

    virtual void print_container() const override;

    virtual void print_container_logger() const override;

    virtual void print_notes_between(std::stringstream &out_stream,tkey left_bound, tkey right_bound) override;

};


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_notes_between(std::stringstream &out_stream, tkey const left_bound, tkey const right_bound) {

    safe_log("START", logging::logger::severity::information);

    auto it = end_infix();

    tree_node *node = nullptr;
    std::stack<binary_search_tree::tree_node *> path_to_subtree_root_exclusive;
    find_left_bound(left_bound, path_to_subtree_root_exclusive, node);
    

    if (nullptr == node) {
        return;
    }
        
    it.set_iterator(node, path_to_subtree_root_exclusive);

    tkey_comparer comparer;
    auto end = end_infix();

    print_container();

    safe_log("left_bound " + cast_to_str(left_bound) + " right bound " + cast_to_str(right_bound), logging::logger::severity::information);

    auto iii = end;

    while (it != end && comparer(std::get<1>(*it), right_bound) >= 0) {

        if (iii != end ? comparer(std::get<1>(*it), std::get<1>(*iii)) : 1) {
            out_stream << std::get<1>(*it) << std::endl;
            out_stream << std::get<2>(*it) << std::endl << std::endl;
        }

        iii = it;
        ++it;

    }
  
    safe_log("ENDED", logging::logger::severity::information);
    
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find_left_bound(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree::tree_node *> &path_to_subtree_root_exclusive,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&node_need) {

    if (node_need) _tree->safe_log("Current node " + cast_to_str(node_need->key), logging::logger::severity::information);

    if (nullptr == subtree_root_address) {

        // next node
        _tree->safe_log("Leaf", logging::logger::severity::debug);
        
        if (path_to_subtree_root_exclusive.empty()) {
            return;
        }

        while (path_to_subtree_root_exclusive.top() != node_need) {
            path_to_subtree_root_exclusive.pop();

            if (path_to_subtree_root_exclusive.empty()) {
                break;
            }
        }
        return;
    }

    tkey_comparer comparer;

    if (comparer(subtree_root_address->key, key) == 0) {

        node_need = subtree_root_address;
        path_to_subtree_root_exclusive.push(subtree_root_address);
        _tree->safe_log(cast_to_str(subtree_root_address->key) + " == " + cast_to_str(node_need->key), logging::logger::severity::information);
        
        return;
    }

    tree_node *next_node;

    // _tree->safe_log("Pair {" + cast_to_str(subtree_root_address->key) + ", " + cast_to_str(subtree_root_address->value) + "}", logging::logger::severity::debug);

    if (comparer(subtree_root_address->key, key) > 0) {
        next_node = subtree_root_address->right_subtree_address;
    } else {
        node_need = subtree_root_address;
        next_node = subtree_root_address->left_subtree_address;
    }

    path_to_subtree_root_exclusive.push(subtree_root_address);

    find_left_bound(key, next_node, path_to_subtree_root_exclusive, node_need);
}



template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_container_logger() const {

    std::function<void(tree_node *, size_t)> print_tree;
    print_tree = [&](tree_node *subtree_root, size_t deep) {

        if (deep == 0) {
            safe_log("Tree", logging::logger::severity::information);
        }

        if (nullptr != subtree_root) {
            print_tree(subtree_root->left_subtree_address, deep + 1);
        }

        if (subtree_root == nullptr) {
            return;
        }

        // safe_log(cast_to_str(subtree_root->key), logging::logger::severity::information);

        print_tree(subtree_root->right_subtree_address, deep + 1);
    };

    print_tree(_root, 0);

}



template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_container() const {

    std::function<void(tree_node *, size_t)> print_tree;
    print_tree = [&](tree_node *subtree_root, size_t deep) {

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
            s += "NULL\n";
            std::cout << s;
            return;
        }

        std::cout << s << cast_to_str(subtree_root->key) << std::endl;

        print_tree(subtree_root->left_subtree_address, deep + 1);
    };

    print_tree(_root, 0);

}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_prefix() const {

    auto it_end = end_prefix();
    for (auto it = begin_prefix(); it != it_end; ++it) {
        std::cout << std::get<2>(*it) << " ";
    }
    std::cout << std::endl;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_infix() const {

    auto it_end = end_infix();
    for (auto it = begin_infix(); it != it_end; ++it) {
        std::cout << std::get<2>(*it) << " ";
    }
    std::cout << std::endl;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::print_postfix() const {

    auto it_end = end_postfix();
    for (auto it = begin_postfix(); it != it_end; ++it) {
        std::cout << std::get<2>(*it) << " ";
    }
    std::cout << std::endl;
}


// region iterators implementation

// region prefix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::prefix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *tree_root,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *begin_or_end_node) {

    _way = std::stack<tree_node *>();

    _begin = tree_root;
    _end = tree_root;


    if (nullptr != _end) {
        while (_end->right_subtree_address) {
            _end = _end->right_subtree_address;
        }
    }

    _current = nullptr == begin_or_end_node ? nullptr : _begin;

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const &other) const {

    if (_current == other._current && _way == other._way) {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator!=(
    binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const &other) const {

    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++() {

    if (nullptr == _current || _current == _end) {

        _current = nullptr;
        _way = std::stack<tree_node *>();

        return *this;
    }

    if (nullptr != _current->left_subtree_address) {

        _way.push(_current);
        _current = _current->left_subtree_address;

        return *this;
    }

    if (nullptr != _current->right_subtree_address) {

        _way.push(_current);
        _current = _current->right_subtree_address;

        return *this;
    }
        
    if (_current == _way.top()->left_subtree_address) {

        _current = _way.top();
        _way.pop();
        
        while (nullptr == _current->right_subtree_address && !_way.empty()) {

            _current = _way.top();
            _way.pop();
        }
        
        _current = _current->right_subtree_address;        
    }

    
    return *this;
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++(
    int not_used) {

    UNUSED(not_used);

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator previous = *this;
    ++(*this);

    return previous;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator*() const {

    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current->key, _current->value);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::get_node_pointer() const {

    return _current;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::get_node_pointer() const {

    return _current;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::get_node_pointer() const {
    
    return _current;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::set_iterator(binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node) {

    _current = node;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::set_iterator(binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *node,
        std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *> &path_to_subtree_root_exclusive) {

    _way = path_to_subtree_root_exclusive;
    _current = node;
}


//endregion prefix_iterator implementation

//region infix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::infix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *tree_root,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *begin_or_end_node) {

    _way = std::stack<tree_node *>();
    _begin = tree_root;

    if (nullptr == begin_or_end_node) {

        if (nullptr != _begin) {
            while (nullptr != _begin->left_subtree_address) {
                _begin = _begin->left_subtree_address;
            }
        }

        _current = nullptr;

    } else {
        
        if (nullptr != _begin) {
            while (nullptr != _begin->left_subtree_address) {

                _way.push(_begin);
                _begin = _begin->left_subtree_address;
            }
        }

        _current = _begin;
    }
    
    _end = tree_root;

    if (nullptr != _end) {
        while (nullptr != _end->right_subtree_address) {
            _end = _end->right_subtree_address;
        }
    }

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const &other) const {

    if (_current == other._current && _way == other._way) {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator!=(
    binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const &other) const {

    return !(*this == other);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++() {


    if (nullptr == _current || _current == _end) {

        _current = nullptr;
        _way = std::stack<tree_node *>();

        return *this;
    }

    if (nullptr != _current->right_subtree_address) {

        _way.push(_current);
        _current = _current->right_subtree_address;

        while (nullptr != _current->left_subtree_address) {
            
            _way.push(_current);
            _current = _current->left_subtree_address;
        }

        return *this;
    }
    
    if (!_way.empty()) {

        if (_way.top()->left_subtree_address == _current) {

            _current = _way.top();
            _way.pop();

            return *this;
        }

        while (_way.top()->right_subtree_address == _current) {

            _current = _way.top();
            _way.pop();
        }

        _current = _way.top();
        _way.pop();

        return *this;
    }

    // if (_way.empty()) {

    //     _way.push(_tree_root);

    // }

    return *this;

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++(
    int not_used) {

    UNUSED(not_used);

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator previous = *this;
    ++(*this);

    return previous;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator*() const {

    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current->key, _current->value);
}

//endregion infix_iterator implementation

//region postfix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::postfix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *tree_root,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *begin_or_end_node) {

    _way = std::stack<tree_node *>();
    _begin = tree_root;

    if (nullptr == begin_or_end_node) {

        if (nullptr != _begin) {
            while (nullptr != _begin->left_subtree_address) {
                _begin = _begin->left_subtree_address;
            }
        }

        _current = nullptr;

    } else {

        while (nullptr != _begin->left_subtree_address) {

            _way.push(_begin);
            _begin = _begin->left_subtree_address;
        }

        _current = _begin;
    }

    _end = tree_root;

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const &other) const {

    if (_current == other._current && _way == other._way) {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator!=(
    binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const &other) const {

    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++() {
    if (nullptr == _current || _current == _end) {
        
        _current = nullptr;
        _way = std::stack<tree_node *>();

        return *this;
    }

    if (_way.top()->right_subtree_address == _current) {

        _current = _way.top();
        _way.pop();

        return *this;
    }

    if (_way.top()->left_subtree_address == _current) {

        _current = _way.top();
        _way.pop();

        if (nullptr != _current->right_subtree_address) {
            
            _way.push(_current);
            _current = _current->right_subtree_address;

            while (nullptr != _current->left_subtree_address || nullptr != _current->right_subtree_address) {
                
                _way.push(_current);
                
                if (nullptr != _current->left_subtree_address) {
                    _current = _current->left_subtree_address;
                } else {
                    _current = _current->right_subtree_address;
                }
            }
        }
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++(
    int not_used) {

    UNUSED(not_used);

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator previous = *this;
    ++(*this);

    return previous;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator*() const {

    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current->key, _current->value);
}


// endregion prefix_iterator implementation

// endregion iterators implementation

// region template methods implementation

// region rotation implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::left_rotation(
        tree_node **subtree_root, tree_node **parent) const {

    tree_node *node = (*subtree_root)->right_subtree_address;
    (*subtree_root)->right_subtree_address = node->left_subtree_address;
    node->left_subtree_address = *subtree_root;

    if (nullptr != parent) {
        if ((*parent)->right_subtree_address == *subtree_root) {
            (*parent)->right_subtree_address = node;
        // } else if ((*parent)->left_subtree_address == *subtree_root) {
        } else {
            (*parent)->left_subtree_address = node;
        }
    }

    *subtree_root = node;

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::right_rotation(
        tree_node **subtree_root, tree_node **parent) const {
    
    safe_log("" + cast_to_str(*subtree_root), logging::logger::severity::debug);

    if (parent) {
        if ((*parent)->right_subtree_address) {
            safe_log("" + cast_to_str((*parent)->right_subtree_address), logging::logger::severity::debug);
        }
    }

    tree_node *node = (*subtree_root)->left_subtree_address;
    (*subtree_root)->left_subtree_address = node->right_subtree_address;
    node->right_subtree_address = *subtree_root;


    if (nullptr != parent) {
        if ((*parent)->right_subtree_address == *subtree_root) {
            (*parent)->right_subtree_address = node;
        } else {
            (*parent)->left_subtree_address = node;
        }
    }

    *subtree_root = node;
    
}

// endregion rotation implementation

// region insertion implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&tree_root_address) {

    UNUSED(tree_root_address);
    std::stack<binary_search_tree::tree_node **> path_to_subtree_root_exclusive;

    return insert_inner(key, std::move(value), _tree->_root,
                        path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert_inner(
    tkey const &key,
    tvalue &&value,
    binary_search_tree::tree_node *&subtree_root_address,
    std::stack<binary_search_tree::tree_node **> &path_to_subtree_root_exclusive) {

    tkey_comparer comparer;
    _tree->safe_log("Insert inner", logging::logger::severity::trace);


    if (nullptr == subtree_root_address) {
        // creating new node here

        _tree->safe_log("subtree_root_address is nullptr. Start creating a new node", logging::logger::severity::debug);

        tree_node *new_node = reinterpret_cast<tree_node *>(
            _tree->safe_allocate(get_size_node())
        );

        initialize_new_node(new_node, key, std::move(value));


        if (path_to_subtree_root_exclusive.empty()) {
            subtree_root_address = new_node;
        } else {

            if (comparer((*path_to_subtree_root_exclusive.top())->key, key) > 0) {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = new_node;
            } else {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = new_node;
            }
        }


        _tree->safe_log("Created node is " + cast_to_str(new_node), logging::logger::severity::debug);

        after_insert_inner(key, new_node, path_to_subtree_root_exclusive);

        return;
    }

    int comparation = comparer(subtree_root_address->key, key);
    
    if (comparation == 0) {
        // replacing node by new one

        _tree->safe_log("node with existing key. Start creating a replacement node key: " + cast_to_str(key), logging::logger::severity::debug);

        tree_node *new_node = reinterpret_cast<tree_node *>(
            _tree->safe_allocate(get_size_node())
        );

        initialize_new_node(new_node, key, std::move(value));

        new_node->left_subtree_address = subtree_root_address->left_subtree_address;
        new_node->right_subtree_address = subtree_root_address->right_subtree_address;

        if (!path_to_subtree_root_exclusive.empty()) {
            
            if (comparer((*path_to_subtree_root_exclusive.top())->key, key) > 0) {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = new_node;
            } else {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = new_node;
            }
        }

        subtree_root_address->~tree_node();
        _tree->safe_deallocate(subtree_root_address);

        subtree_root_address = new_node;

        subtree_root_address->value = std::move(value);


        _tree->safe_log("Replaced node is " + cast_to_str(new_node), logging::logger::severity::debug);

        after_insert_inner(key, new_node, path_to_subtree_root_exclusive);

        return;
    }


    path_to_subtree_root_exclusive.push(&subtree_root_address);
    tree_node *next_node;

    if (comparation > 0) {

        _tree->safe_log("Move right", logging::logger::severity::debug);

        next_node = subtree_root_address->right_subtree_address;
    } else {

        _tree->safe_log("Move left", logging::logger::severity::debug);

        next_node = subtree_root_address->left_subtree_address;
    }

    insert_inner(key, std::move(value), next_node, path_to_subtree_root_exclusive);
    path_to_subtree_root_exclusive.pop();


    // tree_node **nodenode = &next_node;
    // after_insert_inner(key, *nodenode, path_to_subtree_root_exclusive);
    _tree->safe_log("after inner #3", logging::logger::severity::debug);
    after_insert_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::after_insert_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_size_node() const {

    return sizeof(tree_node);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::initialize_new_node(
    tree_node *&new_node, tkey const &key, tvalue &&value) const {

    new (new_node) tree_node{key, std::move(value), nullptr, nullptr };
}

// endregion insertion implementation

// region reading implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue const &binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read(
    tkey const &key,
    tree_node *&tree_root_address) {

        UNUSED(tree_root_address);
    std::stack<tree_node **> path_to_subtree_root_exclusive;

    return read_inner(key, _tree->_root, path_to_subtree_root_exclusive);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find(
    tkey const &key,
    tree_node *&subtree_root_address,
    std::pair<tkey, tvalue *> *found) {

    if (nullptr == subtree_root_address) {
        _tree->safe_log("A value was not found", logging::logger::severity::debug);
        throw std::runtime_error("A value was not found");
        return false;
    }

    tkey_comparer comparer;

    if (comparer(subtree_root_address->key, key) == 0) {
        // _tree->safe_log("Found a value " + cast_to_str(subtree_root_address->value), logging::logger::severity::debug);
        found->first = subtree_root_address->key;
        found->second = &(subtree_root_address->value);
        return true;
    }

    tree_node *next_node;

    // _tree->safe_log("Pair {" + cast_to_str(subtree_root_address->key) + ", " + cast_to_str(subtree_root_address->value) + "}", logging::logger::severity::debug);

    if (comparer(subtree_root_address->key, key) > 0) {
        next_node = subtree_root_address->right_subtree_address;
    } else {
        next_node = subtree_root_address->left_subtree_address;
    }

    return find(key, next_node, found);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue const &binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_inner(
    tkey const &key,
    tree_node *&subtree_root_address,
    std::stack<tree_node **> &path_to_subtree_root_exclusive) {

    if (nullptr == subtree_root_address) {
        _tree->safe_log("A value was not found", logging::logger::severity::debug);
        throw std::runtime_error("No such key in a tree!");
    }

    tkey_comparer comparer;

    if (comparer(subtree_root_address->key, key) == 0) {
        // _tree->safe_log("Found a value " + cast_to_str(subtree_root_address->value), logging::logger::severity::debug);
        after_read_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
        return subtree_root_address->value;
    }

    path_to_subtree_root_exclusive.push(&subtree_root_address);
    tree_node *next_node;

    // _tree->safe_log("Pair {" + cast_to_str(subtree_root_address->key) + ", " + cast_to_str(subtree_root_address->value) + "}", logging::logger::severity::debug);

    if (comparer(subtree_root_address->key, key) > 0) {
        next_node = subtree_root_address->right_subtree_address;
    } else {
        next_node = subtree_root_address->left_subtree_address;
    }

    tvalue const &value = read_inner(key, next_node, path_to_subtree_root_exclusive);

    after_read_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
    

    return value;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::after_read_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
}

// endregion reading implementation

// region removing implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&tree_root_address) {

    UNUSED(tree_root_address);
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> path_to_subtree_root_exclusive;

    return std::move(remove_inner(key, _tree->_root,
                     path_to_subtree_root_exclusive));
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {


    if (nullptr == subtree_root_address) {
        throw std::runtime_error("No such key in a tree!");
    }

    tkey_comparer comparer;
    int comparation = comparer(subtree_root_address->key, key);

    if (comparation == 0) {


        tvalue &&value_to_remove = std::move(subtree_root_address->value);

        if (subtree_root_address->left_subtree_address != nullptr && nullptr != subtree_root_address->right_subtree_address) {

            tree_node *left_max = subtree_root_address->left_subtree_address;
            tree_node *left_max_parent = subtree_root_address;




            path_to_subtree_root_exclusive.push(&subtree_root_address);
            std::stack<tree_node *> references;
            int ii = 0;

            while (left_max->right_subtree_address) {
                ++ii;
                references.push(left_max);
                path_to_subtree_root_exclusive.push(&(references.top()));
                

                // _tree->safe_log("=========================== added " + cast_to_str(left_max->key), logging::logger::severity::debug);
                // _tree->safe_log("top " + cast_to_str((*(path_to_subtree_root_exclusive.top()))->key), logging::logger::severity::debug);

                left_max_parent = left_max;
                left_max = left_max->right_subtree_address;

                _tree->safe_log("=== node " + cast_to_str(&(references.top())), logging::logger::severity::debug);
            }

            _tree->safe_log("iterations " + cast_to_str(ii), logging::logger::severity::debug);
            
            // if (!path_to_subtree_root_exclusive.empty())
                // _tree->safe_log("top " + cast_to_str((*(path_to_subtree_root_exclusive.top()))->key), logging::logger::severity::debug);


            subtree_root_address->key = left_max->key;
            subtree_root_address->value = std::move(left_max->value);

            if (left_max_parent->right_subtree_address == left_max) {
                left_max_parent->right_subtree_address = left_max->left_subtree_address;
            } else {
                left_max_parent->left_subtree_address = left_max->left_subtree_address;
            }

            left_max->~tree_node();
            _tree->safe_deallocate(left_max);

            if (!path_to_subtree_root_exclusive.empty() && ii != 0) {

                tree_node *touched_node = *(path_to_subtree_root_exclusive.top());

                _tree->safe_log("After remove inner removing =================================================================", logging::logger::severity::debug);


                while (comparer(touched_node->key, subtree_root_address->key)) {
                    
                // _tree->safe_log("                                                  touch " + cast_to_str(touched_node->key) + " sub " + cast_to_str(subtree_root_address->key), logging::logger::severity::debug);


                    // _tree->safe_log("After remove inner removing =============== touched " + cast_to_str(touched_node->key), logging::logger::severity::debug);

                    path_to_subtree_root_exclusive.pop();
                    if (comparer(touched_node->key, key)) {
                        after_remove_inner(key, touched_node, path_to_subtree_root_exclusive);
                    }


                    if (!path_to_subtree_root_exclusive.empty()) {
                        touched_node = *(path_to_subtree_root_exclusive.top());
                    } else {
                        break;
                    }
                }
                
                _tree->safe_log("After remove inner removing completed! ===============", logging::logger::severity::debug);
            }

            // _tree->safe_log("Node with a key " + cast_to_str(key) + " has been removed", logging::logger::severity::debug);

            return std::move(value_to_remove);


        } else if (nullptr != subtree_root_address->left_subtree_address) {

            tree_node *left_node = subtree_root_address->left_subtree_address;

            subtree_root_address->~tree_node();

            _tree->safe_deallocate(subtree_root_address);

            subtree_root_address = left_node;

        } else if (nullptr != subtree_root_address->right_subtree_address) {

            tree_node *right_node = subtree_root_address->right_subtree_address;

            subtree_root_address->~tree_node();

            _tree->safe_deallocate(subtree_root_address);
    
            subtree_root_address = right_node;

        } else {

            subtree_root_address->~tree_node();
            
            _tree->safe_deallocate(subtree_root_address);
            
            subtree_root_address = nullptr;
        }


        // _tree->safe_log("Node with a key " + cast_to_str(key) + " has been removed", logging::logger::severity::debug);

        after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);

        return std::move(value_to_remove);
    }


    binary_search_tree::tree_node **next_node = &(comparation > 0 ? subtree_root_address->right_subtree_address : subtree_root_address->left_subtree_address);

    path_to_subtree_root_exclusive.push(&subtree_root_address);

    tvalue &&value_to_remove = std::move(remove_inner(key, *next_node, path_to_subtree_root_exclusive));
    
    path_to_subtree_root_exclusive.pop();
    
    after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);

    return std::move(value_to_remove);
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::after_remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
}

// endregion implementation

// endregion template methods

// region construction, assignment, destruction implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    binary_search_tree::insertion_template_method *insertion,
    binary_search_tree::reading_template_method *reading,
    binary_search_tree::removing_template_method *removing,
    allocating::memory *allocator,
    logging::logger *logger,
    tree_node *root)
    : _insertion(insertion),
      _reading(reading),
      _removing(removing),
      _allocator(allocator),
      _logger(logger),
      _root(root) {

    safe_log("Tree is created", logging::logger::severity::debug);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    allocating::memory *allocator,
    logging::logger *logger):
    _insertion(new insertion_template_method(this)),
    _reading(new reading_template_method(this)),
    _removing(new removing_template_method(this)),
    _allocator(allocator),
    _logger(logger),
    _root(nullptr) {

    safe_log("Tree is created", logging::logger::severity::debug);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    const binary_search_tree &other)
{
    UNUSED(other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    binary_search_tree &&other) noexcept
{
    UNUSED(other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
    const binary_search_tree &other)
{
    UNUSED(other);
    // if (this == &other)
    // {
    //     return *this;
    // }

    // return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
    binary_search_tree &&other) noexcept
{
    UNUSED(other);
    // if (this == &other)
    // {
    //     return *this;
    // }

    // return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::~binary_search_tree() {
    
    safe_log("[BST] Deallocating tree", logging::logger::severity::debug);

    auto it_end = end_postfix();

    safe_log("Type is " + cast_to_str(begin_postfix().get_node_pointer()), logging::logger::severity::warning);

    for (auto it = begin_postfix(); it != it_end; ++it) {
        // safe_log("Type is " + cast_to_str(typeid(it.get_node_pointer()).name()), logging::logger::severity::warning);
        safe_log("GIN " + cast_to_str((it.get_node_pointer())->key), logging::logger::severity::warning);
        (it.get_node_pointer())->~tree_node();
        safe_deallocate(it.get_node_pointer());
    }
    
    safe_log("Deallocation complited", logging::logger::severity::debug);

    delete _insertion;
    delete _reading;
    delete _removing;
}

// endregion construction, assignment, destruction implementation

// region associative_container contract implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insert(
    tkey const &key,
    tvalue &&value) {
    
    // safe_log("Start inserting {" + cast_to_str(key) + ", " + cast_to_str(value) + "}", logging::logger::severity::debug);
    return _insertion->insert(key, std::move(value), _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue const &binary_search_tree<tkey, tvalue, tkey_comparer>::get(
    tkey const &key) {

    // safe_log("Start getting the node with key " + cast_to_str(key), logging::logger::severity::debug);
    return _reading->read(key, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::remove(
    tkey const &key) {

    // safe_log("Start removing the node with key " + cast_to_str(key), logging::logger::severity::debug);
    return std::move(_removing->remove(key, _root));
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::find(
    tkey const &key,
    std::pair<tkey, tvalue *> *found) {

    // safe_log("Start finding the node with key " + cast_to_str(key), logging::logger::severity::debug);
    return _reading->find(key, _root, found);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::find_left_bound(
    tkey const &key,
    std::stack<tree_node *> &path_to_subtree_root_exclusive,
    binary_search_tree::tree_node *&node_need) {

    // safe_log("Start finding the node with key " + cast_to_str(key), logging::logger::severity::debug);
    return _reading->find_left_bound(key, _root, path_to_subtree_root_exclusive, node_need);
}

// endregion associative_container contract implementation

// region logger_holder contract implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
logging::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::get_logger() const {

    return _logger;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
logging::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_logger() const {

    return _tree->_logger;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
logging::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::get_logger() const {

    return _tree->_logger;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
logging::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_logger() const {

    return _tree->_logger;
}

// endregion logger_holder contract implementation

// region allocator_holder contract implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
allocating::memory *binary_search_tree<tkey, tvalue, tkey_comparer>::get_allocator() const {

    return _allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
allocating::memory *binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_allocator() const {

    return _tree->_allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
allocating::memory *binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::get_allocator() const {

    return _tree->_allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
allocating::memory *binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_allocator() const {

    return _tree->_allocator;
}

// endregion allocator_holder contract implementation

// region iterators requesting implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_prefix() const noexcept
{
    return prefix_iterator(_root, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_prefix() const noexcept
{
    return prefix_iterator(_root, nullptr);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_infix() const noexcept
{
    return infix_iterator(_root, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_infix() const noexcept
{
    return infix_iterator(_root, nullptr);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_postfix() const noexcept
{
    return postfix_iterator(_root, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_postfix() const noexcept
{
    return postfix_iterator(_root, nullptr);
}



// // endregion iterators requesting implementation

#endif //SANDBOX_CPP_BINARY_SEARCH_TREE_H