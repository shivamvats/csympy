#include "symbol.h"
#include "integer.h"
#include "constants.h"

namespace CSymPy {

Symbol::Symbol(const std::string &name)
    : name_{name}
{
}

std::size_t Symbol::__hash__() const
{
    std::hash<std::string> hash_fn;
    return hash_fn(name_);
}

bool Symbol::__eq__(const Basic &o) const
{
    if (is_a<Symbol>(o))
        //return name_ == static_cast<const Symbol &>(o).name_;
        return (this->__hash__() ==  o.__hash__());
    return false;
}

int Symbol::compare(const Basic &o) const
{
    CSYMPY_ASSERT(is_a<Symbol>(o))
    //const Symbol &s = static_cast<const Symbol &>(o);
    //if (name_ == s.name_) return 0;
    std::size_t this_hash = this->__hash__(), o_hash = o.__hash__();
    if (this_hash == o_hash) return 0;
    return this_hash < o_hash ? -1 : 1;
}

std::string Symbol::__str__() const
{
    return name_;
}

RCP<const Basic> Symbol::diff(const RCP<const Symbol> &x) const
{
    if (x->name_ == this->name_)
        return one;
    else
        return zero;
}

} // CSymPy
