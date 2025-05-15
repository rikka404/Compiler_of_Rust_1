#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <memory>

enum base_data_type
{
    I32_TYPE, 
    BOOL_TYPE, 
    REFER_TYPE, 
    MUT_REFER_TYPE,
    
    ARRAY_TYPE, 
    TUPLE_TYPE, 

    VOID_TYPE,
    ERROR_TYPE
};

class data_type {
public:
    // element_type(base_data_type b_type);
    // element_type(base_data_type b_type, int l, const element_type& e_type);
    data_type() = default;
    data_type(const data_type&);
    virtual ~data_type() = default;
    // ~element_type()
    // {
    //     std::cout << "xigou" << std::endl;
    // }

    static std::shared_ptr<data_type> create(base_data_type b_type);
    static std::shared_ptr<data_type> create(base_data_type b_type, std::shared_ptr<data_type> e_type);
    static std::shared_ptr<data_type> create(base_data_type b_type, int l, std::shared_ptr<data_type> e_type);
    static std::shared_ptr<data_type> create(base_data_type b_type, int l, const std::vector<std::shared_ptr<data_type>> e_type);
    static std::shared_ptr<data_type> create(const data_type &e_type);
    static data_type shallow_copy(const data_type &e_type);

    int siz;
    base_data_type type;
    

    data_type &operator=(const data_type& e_type);
    bool operator==(const data_type &e_type) const;
    bool operator!=(const data_type &e_type) const;
    static int unused_offset;
    std::shared_ptr<data_type> get_sub_class(int x, int& offset = unused_offset) const; //放弃了offset字段，在这里使用offset得到偏移量
    //虽说这里能实现给定下标的偏移量计算，但是事实上更多的是表达式为下标，这时候就只能取儿子的大小再计算了
};

class refer_type :public data_type
{
public:
    std::shared_ptr<data_type> t_type;
    // refer_type();
    refer_type(const data_type& e_type);
};

class mut_refer_type :public data_type
{
public:
    std::shared_ptr<data_type> t_type;
    // mut_refer_type();
    mut_refer_type(const data_type& e_type);
};

class array_type :public data_type
{
public:
    int len;
    std::shared_ptr<data_type> t_type;
    // array_type();
    array_type(int l, const data_type& e_type);
};

class tuple_type :public data_type
{
public:
    int len;
    std::vector<std::shared_ptr<data_type>> t_type;
    // tuple_type();
    tuple_type(int l, const std::vector<std::shared_ptr<data_type>> e_type);
};


