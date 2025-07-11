#include "data_type.h"
#include <assert.h>

int data_type::unused_offset = 0;

std::shared_ptr<data_type> data_type::create(base_data_type b_type)
{
    assert(b_type == I32_TYPE || b_type == BOOL_TYPE || b_type == VOID_TYPE || b_type == FUN_TYPE);
    auto ptr = std::make_shared<data_type>();
    ptr->type = b_type;
    switch (b_type)
    {
    case I32_TYPE:
        ptr->siz = 4;
        break;
    case BOOL_TYPE:
        ptr->siz = 4;
        break;
    default:
        break;
    }
    return ptr;
}

std::shared_ptr<data_type> data_type::create(base_data_type b_type, std::shared_ptr<data_type> e_type)
{
    assert(b_type == REFER_TYPE || b_type == MUT_REFER_TYPE);
    if(b_type == REFER_TYPE)
    {
        auto ptr = std::make_shared<refer_type>(*e_type);
        return ptr;
    }
    else if(b_type == MUT_REFER_TYPE)
    {
        auto ptr = std::make_shared<mut_refer_type>(*e_type);
        return ptr;
    }
    else
    {
        assert(0);
        return nullptr;
    }
}

std::shared_ptr<data_type> data_type::create(base_data_type b_type, int l, std::shared_ptr<data_type> e_type)
{
    assert(b_type == ARRAY_TYPE);
    auto ptr = std::make_shared<array_type>(l, *e_type);
    return ptr;
};

std::shared_ptr<data_type> data_type::create(base_data_type b_type, int l, const std::vector<std::shared_ptr<data_type>> e_type)
{
    assert(b_type == TUPLE_TYPE);
    auto ptr = std::make_shared<tuple_type>(l, e_type);
    return ptr;
}

std::shared_ptr<data_type> data_type::create(const data_type& e_type)
{
    if(e_type.type == REFER_TYPE)
    {
        auto ptr = std::make_shared<refer_type>(*(((refer_type *)(&e_type))->t_type));
        return ptr;
    }
    else if(e_type.type == MUT_REFER_TYPE)
    {
        auto ptr = std::make_shared<mut_refer_type>(*(((mut_refer_type *)(&e_type))->t_type));
        return ptr;
    }
    else if(e_type.type == ARRAY_TYPE)
    {
        array_type *eptr = (array_type *)(&e_type);
        auto ptr = std::make_shared<array_type>(eptr->len, *(eptr->t_type));
        return ptr;
    }
    else if(e_type.type == TUPLE_TYPE)
    {
        tuple_type *eptr = (tuple_type *)(&e_type);
        auto ptr = std::make_shared<tuple_type>(eptr->len, eptr->t_type);
        return ptr;
    }
    else
    {
        return data_type::create(e_type.type);
    }
}

data_type::data_type(const data_type& e_type)
{
    assert(0); //万策尽了，请不要使用复制构造函数，而是使用工厂函数create
}

data_type data_type::shallow_copy(const data_type &e_type)
{
    //写不动了，之后把这个补上吧
}

data_type & data_type::operator=(const data_type& e_type)
{
    assert(0);//万策尽2.0，请使用工厂函数create
}

refer_type::refer_type(const data_type& e_type)
{
    this->siz = 4;
    this->type = REFER_TYPE;
    this->t_type = data_type::create(e_type);
}

mut_refer_type::mut_refer_type(const data_type& e_type)
{
    this->siz = 4;
    this->type = MUT_REFER_TYPE;
    this->t_type = data_type::create(e_type);
}

array_type::array_type(int l, const data_type& e_type)
{
    this->siz = l * e_type.siz;
    this->type = ARRAY_TYPE;
    this->len = l;
    this->t_type = data_type::create(e_type);
}

tuple_type::tuple_type(int l, const std::vector<std::shared_ptr<data_type>> e_type)
{
    this->siz = 0;
    for (auto et : e_type)
    {
        this->siz += et->siz;
    }
    this->type = TUPLE_TYPE;
    this->len = l;
    this->t_type.resize(e_type.size());
    for (int i = 0; i < (int)e_type.size(); i++)
    {
        this->t_type[i] = data_type::create(*e_type[i]);
    }
}

/**--------------剪切线，上面是复制相关的---------------- */

bool data_type::operator==(const data_type &e_type) const
{
    if(this->type != e_type.type)
        return false;
    else if(this->type == REFER_TYPE)
    {
        refer_type *ptr = (refer_type *)this;
        refer_type *eptr = (refer_type *)(&e_type);
        return *(ptr->t_type) == *(eptr->t_type);
    }
    else if(this->type == MUT_REFER_TYPE)
    {
        mut_refer_type *ptr = (mut_refer_type *)this;
        mut_refer_type *eptr = (mut_refer_type *)(&e_type);
        return *(ptr->t_type) == *(eptr->t_type);
    }
    else if(this->type == ARRAY_TYPE)
    {
        array_type *ptr = (array_type *)this;
        array_type *eptr = (array_type *)(&e_type);
        if(ptr->len != eptr->len)
            return false;
        return *(ptr->t_type) == *(eptr->t_type);
    }
    else if(this->type == TUPLE_TYPE)
    {
        tuple_type *ptr = (tuple_type *)this;
        tuple_type *eptr = (tuple_type *)(&e_type);
        if(ptr->len != eptr->len)
            return false;
        for (int i = 0; i < ptr->len; i++)
        {
            if(*(ptr->t_type[i]) != *(eptr->t_type[i]))
                return false;   
        }
        return true;
    }
    else
    {
        return true;
    }
}

bool data_type::operator!=(const data_type &e_type) const
{
    return !(*this == e_type);
}

std::shared_ptr<data_type> data_type::get_sub_class(int x, int& offset) const
{
    if(this->type == REFER_TYPE)
    {
        assert(x == 0);
        offset = -1; //如果要拿到引用的子类，那么就只是一个类，没有偏移量
        return ((refer_type *)this)->t_type;
    }
    else if(this->type == MUT_REFER_TYPE)
    {
        assert(x == 0);
        offset = -1;
        return ((mut_refer_type *)this)->t_type;
    }
    else if(this->type == ARRAY_TYPE)
    {
        // assert(x < ((array_type *)this)->len && x >= 0);
        if (x >= ((array_type *)this)->len || x < 0)
        {
            std::cout << "[ERROR] [DATA_TYPE] array index out of range" << std::endl;
            exit(0);
        }
        if(offset != -1)
            offset += ((array_type *)this)->t_type->siz * x;
        return ((array_type *)this)->t_type;
    }
    else if(this->type == TUPLE_TYPE)
    {
        // assert(x < ((tuple_type *)this)->len && x >= 0);
        if (x >= ((tuple_type *)this)->len || x < 0)
        {
            std::cout << "[ERROR] [DATA_TYPE] tuple index out of range" << std::endl;
            exit(0);
        }
        if(offset != -1)
        {
            for (int i = 0; i < x; i++)
            {
                offset += ((tuple_type *)this)->t_type[i]->siz;
            }
        }
        return ((tuple_type *)this)->t_type[x];
    }
    else
    {
        assert(0);
    }
}

std::ostream &operator<<(std::ostream &out, const data_type &e_type)
{
    if (e_type.type == I32_TYPE)
    {
        out << "i32";
    }
    else if (e_type.type == BOOL_TYPE)
    {
        out << "bool";
    }
    else if (e_type.type == VOID_TYPE)
    {
        out << "void";
    }
    else if (e_type.type == FUN_TYPE)
    {
        out << "fun";
    }
    else if (e_type.type == ERROR_TYPE)
    {
        out << "error_type";
    }
    else if (e_type.type == REFER_TYPE)
    {
        refer_type *eptr = (refer_type *)(&e_type);
        out << "& " << *(eptr->t_type);
    }
    else if (e_type.type == MUT_REFER_TYPE)
    {
        mut_refer_type *eptr = (mut_refer_type *)(&e_type);
        out << "&mut " << *(eptr->t_type);
    }
    else if (e_type.type == ARRAY_TYPE)
    {
        array_type *eptr = (array_type *)(&e_type);
        out << "[" << *(eptr->t_type) << ";" << eptr->len << "] ";
    }
    else if (e_type.type == TUPLE_TYPE)
    {
        tuple_type *eptr = (tuple_type *)(&e_type);
        out << "(";
        for (int i = 0; i < eptr->len; i++)
        // for (int i = eptr->len - 1; i >= 0; i--)
        {
            out << *(eptr->t_type[i]);
            if (i != eptr->len - 1 || i == 0)
                out << ",";
        }
        out << ")";
    }
    else
    {
        assert(0);
    }
    return out;
}