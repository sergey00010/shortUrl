/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#include <boost/smart_ptr/allocate_unique.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>

template<class T = void>
struct creator {
    typedef T value_type;
    typedef T* pointer;

    template<class U>
    struct rebind {
        typedef creator<U> other;
    };

    creator() { }

    template<class U>
    creator(const creator<U>&) { }

    T* allocate(std::size_t size) {
        return static_cast<T*>(::operator new(sizeof(T) * size));
    }

    void deallocate(T* ptr, std::size_t) {
        ::operator delete(ptr);
    }
};

template<class T, class U>
inline bool
operator==(const creator<T>&, const creator<U>&)
{
    return true;
}

template<class T, class U>
inline bool
operator!=(const creator<T>&, const creator<U>&)
{
    return false;
}

class type {
public:
    static unsigned instances;

    type() {
        ++instances;
    }

    ~type() {
        --instances;
    }

private:
    type(const type&);
    type& operator=(const type&);
};

unsigned type::instances = 0;

int main()
{
    {
        std::unique_ptr<int,
            boost::alloc_deleter<int, creator<int> > > result =
            boost::allocate_unique<int>(creator<int>());
        BOOST_TEST(result.get() != 0);
        BOOST_TEST(*result == 0);
    }
    {
        std::unique_ptr<const int,
            boost::alloc_deleter<const int, creator<> > > result =
            boost::allocate_unique<const int>(creator<>());
        BOOST_TEST(result.get() != 0);
        BOOST_TEST(*result == 0);
    }
    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<type,
            boost::alloc_deleter<type, creator<type> > > result =
            boost::allocate_unique<type>(creator<type>());
        BOOST_TEST(result.get() != 0);
        BOOST_TEST(type::instances == 1);
        result.reset();
        BOOST_TEST(type::instances == 0);
    }
    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<const type,
            boost::alloc_deleter<const type, creator<> > > result =
            boost::allocate_unique<const type>(creator<>());
        BOOST_TEST(result.get() != 0);
        BOOST_TEST(type::instances == 1);
        result.reset();
        BOOST_TEST(type::instances == 0);
    }
    return boost::report_errors();
}
