#ifndef SANDBOX_CPP_BINARY_SEARCH_TREE_H
#define SANDBOX_CPP_BINARY_SEARCH_TREE_H

// #include "allocator.h"
// #include "logger.h"

#include <cstddef>
#include <functional>
#define UNUSED(expr) do { (void)(expr); } while (0)


// #include "memory.h"
#include "memory_with_list.h"
#include "associative_container.h"

// #include "not_implemented.h"

// #include "logger_concrete.h"
// #include "traversable.h"
#include <stack>



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
    public associative_container<tkey, tvalue>
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
        std::stack<tree_node *> _way;

        tree_node *_current;
        tree_node *_begin;
        tree_node *_end;

    public:

        explicit infix_iterator(
            tree_node *tree_root,
            tree_node *begin_or_end_node);

        tree_node *get_node_pointer() const;

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

    class insertion_template_method
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
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_insert_inner(
            tkey const &key,
            tvalue &&value,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

        virtual void after_insert_inner(
            tkey const &key,
            tvalue &&value,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

    private:

        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const;
        allocating::memory *get_allocator() const;

    };

    class reading_template_method
    {

    public:

        virtual ~reading_template_method() = default;
        reading_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree)
            : _tree(tree) {}

    public:

        tvalue const &read(
            tkey const &key,
            tree_node *&tree_root_address);

    private:

        tvalue const &read_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_read_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

        virtual void after_read_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);
    
    private:
        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const;
        allocating::memory *get_allocator() const;

    };

    class removing_template_method
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
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_remove_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

        virtual void after_remove_inner(
            tkey const &key,
            tree_node *&subtree_root_address,
            std::stack<tree_node **> &path_to_subtree_root_exclusive);

    private:
        binary_search_tree<tkey, tvalue, tkey_comparer> *_tree;

        logging::logger *get_logger() const;
        allocating::memory *get_allocator() const;

    };

private:

    tree_node *_root;
    insertion_template_method *_insertion;
    reading_template_method *_reading;
    removing_template_method *_removing;
    allocating::memory *_allocator;
    logging::logger *_logger;

protected:

    explicit binary_search_tree(
        insertion_template_method *insertion,
        reading_template_method *reading,
        removing_template_method *removing,
        allocating::memory *allocator = nullptr,
        logging::logger *logger = nullptr);

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

    ~binary_search_tree();

public:

    void insert(
        tkey const &key,
        tvalue &&value) final;

    tvalue const &get(
        tkey const &key) final;

    tvalue &&remove(
        tkey const &key) final;

private:

    logging::logger *get_logger() const;

public:

    prefix_iterator begin_prefix() const noexcept;

    prefix_iterator end_prefix() const noexcept;

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    postfix_iterator begin_postfix() const noexcept;

    postfix_iterator end_postfix() const noexcept;

protected:

    void left_rotation(tree_node *&subtree_root) const;

    void right_rotation(tree_node *&subtree_root) const;

public:

    void print_prefix() const override;

    void print_infix() const override;

    void print_postfix() const override;

    void print_container() const override;

};



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

        for (size_t i = 0; i < deep; ++i) {
            std::cout << "\t";
        }
        std::cout << "\\_____";


        if (subtree_root == nullptr) {
            std::cout << "NULL\n";
            return;
        }

        std::cout << subtree_root->key << std::endl;

        print_tree(subtree_root->left_subtree_address, deep + 1);
        print_tree(subtree_root->right_subtree_address, deep + 1);
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

    if (nullptr != _way.top()) {

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

    if (_way.empty()) {

        _way.push(_tree_root);

    }

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

// region insertion implementation
template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::left_rotation(tree_node *&subtree_root) const {
    
    tree_node *prev_root = subtree_root;
    subtree_root = prev_root->right_subtree_address;
    prev_root->right_subtree_address = subtree_root->left_subtree_address;
    subtree_root->left_subtree_address = prev_root;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::right_rotation(tree_node *&subtree_root) const {
    
    UNUSED(subtree_root);
    // tree_node *prev_root = subtree_root;
    // subtree_root = prev_root->left_subtree_address;
    // prev_root->left_subtree_address = subtree_root->right_subtree_address;
    // subtree_root->right_subtree_address = prev_root;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&tree_root_address) {

    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> temp_stack;

    return insert_inner(key, std::move(value), tree_root_address,
                        temp_stack);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert_inner(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    logging::logger *logger = get_logger();

    // before_insert_inner(key, std::move(value), subtree_root_address, path_to_subtree_root_exclusive);

    tkey_comparer comparer;

    if (nullptr == subtree_root_address) {
        // creating new node here
        logger->log("subtree_root_address is nullptr. Start creating a new node", logging::logger::severity::information);

        allocating::memory *allocator = get_allocator();

        tree_node *new_node =
        // new binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node();
            reinterpret_cast<tree_node *>(
                allocator->allocate(sizeof(binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node))
            );


        new_node->key = key;
        new_node->value = value;
        new_node->left_subtree_address = new_node->right_subtree_address = nullptr;


        if (path_to_subtree_root_exclusive.empty()) {
            subtree_root_address = new_node;
        } else {

            if (comparer((*path_to_subtree_root_exclusive.top())->key, key) > 0) {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = new_node;
            } else {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = new_node;
            }
        }

        logger->log("Created node is " + cast_to_str(new_node), logging::logger::severity::information);

        return;
    }

    logger->log("Pair {" + cast_to_str(subtree_root_address->key) + ", " + cast_to_str(subtree_root_address->value) + "}", logging::logger::severity::information);

    int comparation = comparer(subtree_root_address->key, key);
    if (comparation == 0) {

        logger->log("Key " + cast_to_str(subtree_root_address->key) + " value " + cast_to_str(subtree_root_address->value), logging::logger::severity::information);
        subtree_root_address->value = std::move(value);

        return;
    }


    path_to_subtree_root_exclusive.push(&subtree_root_address);
    tree_node *next_node;

    if (comparation > 0) {

        logger->log("Move right", logging::logger::severity::information);

        next_node = subtree_root_address->right_subtree_address;
    } else {

        logger->log("Move left", logging::logger::severity::information);

        next_node = subtree_root_address->left_subtree_address;
    }

    insert_inner(key, std::move(value), next_node, path_to_subtree_root_exclusive);
    path_to_subtree_root_exclusive.pop();

    // after_insert_inner(key, std::move(value), next_node, path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::before_insert_inner(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(value);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::after_insert_inner(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    UNUSED(key);
    UNUSED(value);
    UNUSED(subtree_root_address);
    UNUSED(path_to_subtree_root_exclusive);
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

    std::stack<tree_node **> temp_stack;

    return read_inner(key, tree_root_address, temp_stack);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue const &binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_inner(
    tkey const &key,
    tree_node *&subtree_root_address,
    std::stack<tree_node **> &path_to_subtree_root_exclusive) {

    logging::logger *logger = get_logger();

    // before_read_inner(key, subtree_root_address, path_to_subtree_root_exclusive);

    if (nullptr == subtree_root_address) {
        logger->log("A value was not found", logging::logger::severity::information);
        throw std::runtime_error("No such key in a tree!\n");
    }

    tkey_comparer comparer;

    if (comparer(subtree_root_address->key, key) == 0) {
        logger->log("Found a value " + cast_to_str(subtree_root_address->value), logging::logger::severity::information);
        return subtree_root_address->value;
    }

    path_to_subtree_root_exclusive.push(&subtree_root_address);
    tree_node *next_node;

    logger->log("Pair {" + cast_to_str(subtree_root_address->key) + ", " + cast_to_str(subtree_root_address->value) + "}", logging::logger::severity::information);

    if (comparer(subtree_root_address->key, key) > 0) {
        next_node = subtree_root_address->right_subtree_address;
    } else {
        next_node = subtree_root_address->left_subtree_address;
    }

    tvalue const &value = read_inner(key, next_node, path_to_subtree_root_exclusive);

    // after_read_inner(key, next_node, path_to_subtree_root_exclusive);
    

    return value;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::before_read_inner(
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

    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> temp_stack;

    return std::move(remove_inner(key, tree_root_address,
                     temp_stack));
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::tree_node **> &path_to_subtree_root_exclusive) {

    logging::logger *logger = get_logger();

    // before_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);


    if (nullptr == subtree_root_address) {
        logger->log("Node with key " + cast_to_str(key) + " was not found", logging::logger::severity::information);
        throw std::runtime_error("No such key in a tree!\n");
    }

    tkey_comparer comparer;
    int comparation = comparer(subtree_root_address->key, key);

    if (comparation == 0) {

        allocating::memory *allocator = get_allocator();

        tvalue &&value_to_remove = std::move(subtree_root_address->value);

        if (subtree_root_address->left_subtree_address != nullptr && nullptr != subtree_root_address->right_subtree_address) {

            // std::cout << "both subtrees exists\n";
            // std::cout << "left has " << subtree_root_address->left_subtree_address->key << " key\n";
            // std::cout << "right has " << subtree_root_address->right_subtree_address->key << " key\n";
            // std::cout << "remove " << subtree_root_address->key << std::endl;
            

            tree_node *left_max = subtree_root_address->left_subtree_address;
            tree_node *left_max_parent = subtree_root_address;

            while (left_max->right_subtree_address) {

                left_max_parent = left_max;
                left_max = left_max->right_subtree_address;
            }


            subtree_root_address->key = left_max->key;
            subtree_root_address->value = std::move(left_max->value);

            if (left_max_parent->right_subtree_address == left_max) {
                left_max_parent->right_subtree_address = left_max->left_subtree_address;
            } else {
                left_max_parent->left_subtree_address = left_max->left_subtree_address;
            }

            allocator->deallocate(left_max);

            _tree->right_rotation(subtree_root_address);

        } else if (nullptr != subtree_root_address->left_subtree_address) {


            tree_node *left_node = subtree_root_address->left_subtree_address;


            
            // std::cout << "left subtree to inherit, ";
            // std::cout << "left has " << left_node->key << " key\n";
            // std::cout << "remove " << subtree_root_address->key << std::endl;



            if (path_to_subtree_root_exclusive.empty()) {
                
            } else if ((*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address) {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = left_node;
            } else {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = left_node;
            }

            allocator->deallocate(subtree_root_address);

            subtree_root_address = left_node;

        } else if (nullptr != subtree_root_address->right_subtree_address) {


            tree_node *right_node = subtree_root_address->right_subtree_address;



            // std::cout << "right subtree to inherit. ";
            // std::cout << "right has " << right_node->key << " key\n";
            // std::cout << "remove " << subtree_root_address->key << std::endl;



            if (path_to_subtree_root_exclusive.empty()) {
                
            } else if ((*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address) {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = right_node;
            } else {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = right_node;
            }
            
            allocator->deallocate(subtree_root_address);


            subtree_root_address = right_node;


        } else {

            // std::cout << "zero\n";

            if (path_to_subtree_root_exclusive.empty()) {
                
            } else if ((*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address) {
                (*path_to_subtree_root_exclusive.top())->left_subtree_address = nullptr;
            } else {
                (*path_to_subtree_root_exclusive.top())->right_subtree_address = nullptr;
            }

            subtree_root_address->~tree_node();

            // std::cout << "remove " << subtree_root_address->key << std::endl;

            allocator->deallocate(subtree_root_address);
            subtree_root_address = nullptr;

        }
 


        logger->log("Node with a key " + cast_to_str(key) + " has been removed", logging::logger::severity::information);


        return std::move(value_to_remove);
    }


    binary_search_tree::tree_node *next_node;

    if (comparation > 0) {
        next_node = subtree_root_address->right_subtree_address;
    } else {
        next_node = subtree_root_address->left_subtree_address;
    }

    path_to_subtree_root_exclusive.push(&subtree_root_address);

    tvalue &&removing_value = std::move(remove_inner(key, next_node, path_to_subtree_root_exclusive));
    
    after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
    
    path_to_subtree_root_exclusive.pop();

    return std::move(removing_value);

    
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::before_remove_inner(
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
    logging::logger *logger)
    : _insertion(insertion(this)),
      _reading(reading(this)),
      _removing(removing(this)),
      _allocator(allocator),
      _logger(logger) {

    logger->log("Tree is created", logging::logger::severity::information);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    allocating::memory *allocator,
    logging::logger *logger):
    _root(nullptr),
    _insertion(new insertion_template_method(this)),
    _reading(new reading_template_method(this)),
    _removing(new removing_template_method(this)),
    _allocator(allocator),
    _logger(logger) {

    logger->log("Tree is created", logging::logger::severity::information);
}

// template<
//     typename tkey,
//     typename tvalue,
//     typename tkey_comparer>
// binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
//     const binary_search_tree &other)
// {
//     // TODO move
// }

// template<
//     typename tkey,
//     typename tvalue,
//     typename tkey_comparer>
// binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
//     binary_search_tree &&other) noexcept
// {
//     // TODO
// }

// template<
//     typename tkey,
//     typename tvalue,
//     typename tkey_comparer>
// binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
//     const binary_search_tree &other)
// {
//     if (this == &other)
//     {
//         return *this;
//     }

//     return *this;
// }

// template<
//     typename tkey,
//     typename tvalue,
//     typename tkey_comparer>
// binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
//     binary_search_tree &&other) noexcept
// {
//     if (this == &other)
//     {
//         return *this;
//     }

//     return *this;
// }

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::~binary_search_tree() {
    
    _logger->log("Deallocating tree", logging::logger::severity::information);

    auto it_end = end_postfix();
    for (auto it = begin_postfix(); it != it_end; ++it) {
        _allocator->deallocate(it.get_node_pointer());
    }

    _logger->log("Deallocating complited", logging::logger::severity::information);

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

    _logger->log("Start inserting {" + cast_to_str(key) + ", " + cast_to_str(value) + "}", logging::logger::severity::information);
    return _insertion->insert(key, std::move(value), _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue const &binary_search_tree<tkey, tvalue, tkey_comparer>::get(
    tkey const &key) {

    logging::logger *logger = get_logger();
    logger->log("Start getting the node with key " + cast_to_str(key), logging::logger::severity::information);
    return _reading->read(key, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::remove(
    tkey const &key) {

    logging::logger *logger = get_logger();
    logger->log("Start removing the node with key " + cast_to_str(key), logging::logger::severity::information);
    return std::move(_removing->remove(key, _root));
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


// endregion logger_holder contract implementation

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