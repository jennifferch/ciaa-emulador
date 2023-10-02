
#ifndef MBED_CALLBACK_H
#define MBED_CALLBACK_H

#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <new>
#include "mbed_assert.h"

namespace mbed {
/** \addtogroup platform */
/** @{*/
/**
 * \defgroup platform_Callback Callback class
 * @{
 */

/** Callback class based on template specialization
 *
 * @note Synchronization level: Not protected
 */
template <typename F>
class Callback;

/** Callback class based on template specialization
 *
 * @note Synchronization level: Not protected
 */
template <typename R>
class Callback<R()> {
public:
    /** Create a Callback with a static function
     *  @param func     Static function to attach
     */
    Callback(R(*func)() = 0)
    {
        if (!func) {
            memset(this, 0, sizeof(Callback));
        } else {
            generate(func);
        }
    }

    template<typename T, typename U>
    void attach(U *obj, R(T::*method)())
    {
        this->~Callback();
        new (this) Callback(obj, method);
    }

    /** Call the attached function
     */
    R call() const
    {
       // MBED_ASSERT(_ops);
        return _ops->call(this);
    }

    /** Call the attached function
     */
    R operator()() const
    {
        return call();
    }

    /** Test if function has been attached
     */
    operator bool() const
    {
        return _ops;
    }



private:
    // Stored as pointer to function and pointer to optional object
    // Function pointer is stored as union of possible function types
    // to guarantee proper size and alignment
    struct _class;
    union {
        void (*_staticfunc)();
        void (*_boundfunc)(_class *);
        void (_class::*_methodfunc)();
    } _func;
    void *_obj;

    // Dynamically dispatched operations
    const struct ops {
        R(*call)(const void *);
        void (*move)(void *, const void *);
        void (*dtor)(void *);
    } *_ops;

    // Generate operations for function object
    template <typename F>
    void generate(const F &f)
    {
        static const ops ops = {
            &Callback::function_call<F>,
            &Callback::function_move<F>,
            &Callback::function_dtor<F>,
        };
        MBED_STATIC_ASSERT(sizeof(Callback) - sizeof(_ops) >= sizeof(F),
                          "Type F must not exceed the size of the Callback class");
        memset(this, 0, sizeof(Callback));
        new (this) F(f);
        _ops = &ops;
    }

    // Function attributes
    template <typename F>
    static R function_call(const void *p)
    {
        return (*(F *)p)();
    }

    template <typename F>
    static void function_move(void *d, const void *p)
    {
        new (d) F(*(F *)p);
    }

    template <typename F>
    static void function_dtor(void *p)
    {
        ((F *)p)->~F();
    }

};



/** Create a callback class with type inferred from the arguments
 *
 *  @param func     Static function to attach
 *  @return         Callback with inferred type
 */
template <typename R>
Callback<R()> callback(R(*func)() = 0)
{
    return Callback<R()>(func);
}

} // namespace mbed

#endif