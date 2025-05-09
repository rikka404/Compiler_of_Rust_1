#pragma once
#include <vector>
#include <set>
#include <queue>
#include <memory>

enum base_element_type
{
    I32_TYPE, 
    BOOL_TYPE, 
    REFER_TYPE, 
    MUT_REFER_TYPE,
    
    ARRAY_TYPE, 
    TUPLE_TYPE, 

    ERROR_TYPE
};

class element_type {
public:
    // element_type(base_element_type b_type);
    // element_type(base_element_type b_type, int l, const element_type& e_type);
    element_type() = default;
    element_type(const element_type&);
    virtual ~element_type() = default;

    static std::shared_ptr<element_type> create(base_element_type b_type);
    static std::shared_ptr<element_type> create(base_element_type b_type, element_type e_type);
    static std::shared_ptr<element_type> create(base_element_type b_type, int l, element_type e_type);
    static std::shared_ptr<element_type> create(base_element_type b_type, int l, const std::vector<std::shared_ptr<element_type>> e_type);
    static std::shared_ptr<element_type> create(const element_type &e_type);
    static element_type shallow_copy(const element_type &e_type);

    int siz;
    int offset; //备战未来
    base_element_type type;

    element_type &operator=(element_type e_type);
    bool operator==(const element_type &e_type) const;
    bool operator!=(const element_type &e_type) const;
    // element_type operator[](int x) const;
    // int getoffset() const;
};

class refer_type :public element_type
{
public:
    std::shared_ptr<element_type> t_type;
    // refer_type();
    refer_type(element_type e_type);
};

class mut_refer_type :public element_type
{
public:
    std::shared_ptr<element_type> t_type;
    // mut_refer_type();
    mut_refer_type(element_type e_type);
};

class array_type :public element_type
{
public:
    int len;
    std::shared_ptr<element_type> t_type;
    // array_type();
    array_type(int l, element_type e_type);
};

class tuple_type :public element_type
{
public:
    int len;
    std::vector<std::shared_ptr<element_type>> t_type;
    // tuple_type();
    tuple_type(int l, const std::vector<std::shared_ptr<element_type>> e_type);
};


