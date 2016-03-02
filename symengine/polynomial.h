/**
 *  \file polynomial.h
 *  Class for sparse Polynomial: UnivariatePolynomial and Polynomial
 *
 **/
#ifndef SYMENGINE_POLYNOMIALS_H
#define SYMENGINE_POLYNOMIALS_H

#include <symengine/monomials.h>
#include <symengine/dict.h>
#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>
#include <symengine/expression.h>

namespace SymEngine {
//! UnivariatePolynomial Class
class UnivariatePolynomial : public Basic{
public:
    //! `degree` : Degree of UnivariatePolynomial
    //! `var_` : Variable of the uni-variate UnivariatePolynomial
    //! `dict_` : holds the UnivariatePolynomial
    // UnivariatePolynomial x**2 + 2*x + 1 has dict_ = {{0, 1}, {1, 2}, {2, 1}} with var_ = "x"
    unsigned int degree_;
    RCP<const Symbol> var_;
    map_uint_mpz dict_;
public:
    IMPLEMENT_TYPEID(UNIVARIATEPOLYNOMIAL)
    //! Constructor of UnivariatePolynomial class
    UnivariatePolynomial(const RCP<const Symbol> &var, const unsigned int &degree, map_uint_mpz&& dict);
    //! Constructor using a dense vector of integer_class coefficients
    UnivariatePolynomial(const RCP<const Symbol> &var, const std::vector<integer_class> &v);

    static RCP<const UnivariatePolynomial> create(const RCP<const Symbol> &var,
            const std::vector<integer_class> &v) {
        return make_rcp<const UnivariatePolynomial>(var, v);
    }

    //! \return true if canonical
    bool is_canonical(const unsigned int &degree, const map_uint_mpz& dict) const;
    //! \return size of the hash
    std::size_t __hash__() const;
    /*! Equality comparator
     * \param o - Object to be compared with
     * \return whether the 2 objects are equal
     * */
    bool __eq__(const Basic &o) const;
    int compare(const Basic &o) const;

    /*! Creates appropriate instance (i.e Symbol, Integer,
    * Mul, Pow, UnivariatePolynomial) depending on the size of dictionary `d`.
    */
    static RCP<const Basic> from_dict(const RCP<const Symbol> &var, map_uint_mpz &&d);
    /*!
    * Adds coef*var_**n to the dict_
    */
    static void dict_add_term(map_uint_mpz &d,
            const integer_class &coef, const unsigned int &n);
    integer_class max_coef() const;
    //! Evaluates the UnivariatePolynomial at value x
    integer_class eval(const integer_class &x) const;
    //! Evaluates the UnivariatePolynomial at value 2**x
    integer_class eval_bit(const int &x) const;

    //! \return `true` if `0`
    bool is_zero() const;
    //! \return `true` if `1`
    bool is_one() const;
    //! \return `true` if `-1`
    bool is_minus_one() const;
    //! \return `true` if integer
    bool is_integer() const;
    //! \return `true` if symbol
    bool is_symbol() const;
    //! \return `true` if mul
    bool is_mul() const;
    //! \return `true` if pow
    bool is_pow() const;

    virtual vec_basic get_args() const;

    inline RCP<const Symbol> get_var() const {
        return var_;
    }
    inline const map_uint_mpz& get_dict() const {
        return dict_;
    };

}; //UnivariatePolynomial
/*
class UnivariateExprPolynomial: public Basic {
public:
    unsigned int degree_;
    RCP<const Symbol> var_;
    map_uint_expr dict_;
public:
    IMPLEMENT_TYPEID(UNIVARIATEEXPRPOLYNOMIAL)*/
    //! Constructor of UnivariatePolynomial class
    /*UnivariateExprPolynomial(const RCP<const Symbol> &var, const unsigned int &degree, map_uint_expr&& dict);*/
    //! Constructor using a dense vector of mpz_class coefficients
    //UnivariateExprPolynomial(const RCP<const Symbol> &var, const std::vector<mpz_class> &v);
    /*static RCP<const UnivariateExprPolynomial> create(const RCP<const Symbol> &var,
            const std::vector<mpz_class> &v) {
        return make_rcp<const UnivariateExprPolynomial>(var, v);
    }*/

    //! \return true if canonical
    /*bool is_canonical(const unsigned int &degree, const map_uint_expr& dict) const;
    //! \return size of the hash
    std::size_t __hash__() const;*/
    /*! Equality comparator
     * \param o - Object to be compared with
     * \return whether the 2 objects are equal
     * */
    /*bool __eq__(const Basic &o) const;*/
//}; //UnivariateExprPolynomial

//! Adding two UnivariatePolynomial a and b
RCP<const UnivariatePolynomial> add_uni_poly(const UnivariatePolynomial &a, const UnivariatePolynomial &b);
//! Negative of a UnivariatePolynomial
RCP<const UnivariatePolynomial> neg_uni_poly(const UnivariatePolynomial &a);
//! Subtracting two UnivariatePolynomial a and b
RCP<const UnivariatePolynomial> sub_uni_poly(const UnivariatePolynomial &a, const UnivariatePolynomial &b);
//! Multiplying two UnivariatePolynomial a and b
RCP<const UnivariatePolynomial> mul_uni_poly(RCP<const UnivariatePolynomial> a, RCP<const UnivariatePolynomial> b);

inline RCP<const UnivariatePolynomial> univariate_polynomial(RCP<const Symbol> i, unsigned int deg, map_uint_mpz&& dict)
{
    return make_rcp<const UnivariatePolynomial>(i, deg, std::move(dict));
}

 
class MultivariatePolynomial : public Basic{
public:
    //vars: set of variables for th polynomial
    //degrees: max degrees of the symbols
    //dict: dictionary for sparse represntation of polynomial, x**1 * y**2 + 3 * x**4 * y ** 5
    // is represented as {(1,2):1,(4,5):3}
    set_sym vars_;
    umap_sym_uint degrees_;
    umap_uvec_mpz dict_;
public:
    IMPLEMENT_TYPEID(MULTIVARIATEPOLYNOMIAL)
    //constructor from components
    MultivariatePolynomial(const set_sym &var, umap_sym_uint &degrees, umap_uvec_mpz &dict);
    RCP<const Basic> from_dict(const set_sym &s, umap_uvec_mpz &&d) const;
    vec_basic get_args() const;
    bool is_canonical(const set_sym &vars, const umap_sym_uint &degrees, const umap_uvec_mpz &dict);
    std::size_t __hash__() const;
    bool __eq__(const Basic &o) const;
    int compare(const Basic &o) const;
    mpz_class eval(std::map<RCP<const Symbol>, mpz_class, RCPSymbolCompare> &vals);
    std::string toString() const; 
};

//reconciles the positioning of the exponents in the vectors in the umap_uvec_mpz dict_ of the arguments
//with the positioning of the exponents in the correspondng vectors of the output of the function.
//f1 and f2 are vectors whose indicies are the positions in the arguments and whose values are the
//positions in the output.  set_sym s is the set of symbols of the output, and
// s1 and s2 are the sets of the symbols of the inputs.
unsigned int reconcile(vec_uint &v1, vec_uint &v2, set_sym &s, const set_sym &s1, const set_sym &s2);
//same as above, but for reconcileing representation of a UnivariatePolynomial. 
unsigned int reconcile(vec_uint &v1, unsigned int &v2, set_sym &s, const set_sym &s1, const RCP<const Symbol> s2);
//translates vectors from one polynomial into vectors for another.
vec_uint translate(vec_uint original, vec_uint translator, unsigned int size);
vec_uint translate(unsigned int original, unsigned int translator, unsigned int size);
vec_uint uint_vec_translate_and_add(const vec_uint &v1, const vec_uint &v2,const vec_uint &translator1, const vec_uint &translator2, const unsigned int size);
vec_uint uint_vec_translate_and_add(const vec_uint &v1, const unsigned int v2, const vec_uint &translator1,const unsigned int &translator2, const unsigned int size);

RCP<const MultivariatePolynomial> add_mult_poly(const MultivariatePolynomial &a, const MultivariatePolynomial &b);
RCP<const MultivariatePolynomial> neg_mult_poly(const MultivariatePolynomial &a);
RCP<const MultivariatePolynomial> sub_mult_poly(const MultivariatePolynomial &a, const MultivariatePolynomial &b);
RCP<const MultivariatePolynomial> mul_mult_poly(const MultivariatePolynomial &a, const MultivariatePolynomial &b);


RCP<const MultivariatePolynomial> add_mult_poly(const MultivariatePolynomial &a, const UnivariatePolynomial &b);
RCP<const MultivariatePolynomial> sub_mult_poly(const MultivariatePolynomial &a, const UnivariatePolynomial &b);
RCP<const MultivariatePolynomial> sub_mult_poly(const UnivariatePolynomial &a, const MultivariatePolynomial &b);
RCP<const MultivariatePolynomial> mul_mult_poly(const MultivariatePolynomial &a, const UnivariatePolynomial &b);

RCP<const MultivariatePolynomial> add_mult_poly(const UnivariatePolynomial &a, const UnivariatePolynomial &b);
RCP<const MultivariatePolynomial> sub_mult_poly(const UnivariatePolynomial &a, const UnivariatePolynomial &b);
RCP<const MultivariatePolynomial> mul_mult_poly(const UnivariatePolynomial &a, const UnivariatePolynomial &b);


}  //SymEngine

#endif
