#include "element_type.h"
#include <assert.h>

std::shared_ptr<element_type> element_type::create(base_element_type b_type)
{
    assert(b_type == I32_TYPE || b_type == BOOL_TYPE);
    auto ptr = std::make_shared<element_type>();
    ptr->type = b_type;
    switch (b_type)
    {
    case I32_TYPE:
        ptr->siz = 4;
        break;
    case BOOL_TYPE:
        ptr->siz = 1;
        break;
    default:
        break;
    }
    return ptr;
}

std::shared_ptr<element_type> element_type::create(base_element_type b_type, std::shared_ptr<element_type> e_type)
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

std::shared_ptr<element_type> element_type::create(base_element_type b_type, int l, std::shared_ptr<element_type> e_type)
{
    assert(b_type == ARRAY_TYPE);
    auto ptr = std::make_shared<array_type>(l, *e_type);
    return ptr;
};

std::shared_ptr<element_type> element_type::create(base_element_type b_type, int l, const std::vector<std::shared_ptr<element_type>> e_type)
{
    assert(b_type == TUPLE_TYPE);
    auto ptr = std::make_shared<tuple_type>(l, e_type);
    return ptr;
}

std::shared_ptr<element_type> element_type::create(const element_type& e_type)
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
        return element_type::create(e_type.type);
    }
}

element_type::element_type(const element_type& e_type)
{
    assert(0); //万策尽了，请不要使用复制构造函数，而是使用工厂函数create
}

element_type element_type::shallow_copy(const element_type &e_type)
{
    //写不动了，之后把这个补上吧
}

element_type & element_type::operator=(const element_type& e_type)
{
    assert(0);//万策尽2.0，请使用工厂函数create
}

refer_type::refer_type(const element_type& e_type)
{
    this->siz = 4;
    this->offset = 0;
    this->type = REFER_TYPE;
    this->t_type = element_type::create(e_type);
}

mut_refer_type::mut_refer_type(const element_type& e_type)
{
    this->siz = 4;
    this->offset = 0;
    this->type = MUT_REFER_TYPE;
    this->t_type = element_type::create(e_type);
}

array_type::array_type(int l, const element_type& e_type)
{
    this->siz = l * e_type.siz;
    this->offset = 0;
    this->type = ARRAY_TYPE;
    this->len = l;
    this->t_type = element_type::create(e_type);
}

tuple_type::tuple_type(int l, const std::vector<std::shared_ptr<element_type>> e_type)
{
    this->siz = 0;
    for (auto et : e_type)
    {
        this->siz += et->siz;
    }
    this->offset = 0;
    this->type = TUPLE_TYPE;
    this->len = l;
    this->t_type.resize(e_type.size());
    for (int i = 0; i < (int)e_type.size(); i++)
    {
        this->t_type[i] = element_type::create(*e_type[i]);
    }
}

/**--------------剪切线，上面是复制相关的---------------- */

bool element_type::operator==(const element_type &e_type) const
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

bool element_type::operator!=(const element_type &e_type) const
{
    return !(*this == e_type);
}

std::shared_ptr<element_type> element_type::get_sub_class(int x) const
{
    if(this->type == REFER_TYPE)
    {
        assert(x == 0);
        return ((refer_type *)this)->t_type;
    }
    else if(this->type == MUT_REFER_TYPE)
    {
        assert(x == 0);
        return ((mut_refer_type *)this)->t_type;
    }
    else if(this->type == ARRAY_TYPE)
    {
        assert(x < ((array_type *)this)->len);
        return ((array_type *)this)->t_type;
    }
    else if(this->type == TUPLE_TYPE)
    {
        assert(x < ((tuple_type *)this)->len);
        return ((tuple_type *)this)->t_type[x];
    }
    else
    {
        assert(0);
    }
}