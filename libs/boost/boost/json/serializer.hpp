//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_SERIALIZER_HPP
#define BOOST_JSON_SERIALIZER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/detail/format.hpp>
#include <boost/json/detail/stream.hpp>
#include <boost/json/detail/writer.hpp>
#include <boost/json/serialize_options.hpp>
#include <boost/json/value.hpp>

namespace boost {
namespace json {

/** A serializer for JSON.

    This class traverses an instance of a library
    type and emits serialized JSON text by filling
    in one or more caller-provided buffers. To use,
    declare a variable and call @ref reset with
    a pointer to the variable you want to serialize.
    Then call @ref read over and over until
    @ref done returns `true`.

    @par Example

    This demonstrates how the serializer may
    be used to print a JSON value to an output
    stream.

    @code

    void print( std::ostream& os, value const& jv)
    {
        serializer sr;
        sr.reset( &jv );
        while( ! sr.done() )
        {
            char buf[ 4000 ];
            os << sr.read( buf );
        }
    }

    @endcode

    @par Thread Safety

    The same instance may not be accessed concurrently.
*/
class serializer
    : detail::writer
{
    using fn_t = bool (*)(writer&, detail::stream&);

    fn_t fn0_ = nullptr;
    fn_t fn1_ = nullptr;
    bool done_ = false;

public:
    /// Move constructor (deleted)
    serializer(serializer&&) = delete;

    /** Destructor

        All temporary storage is deallocated.

        @par Complexity
        Constant

        @par Exception Safety
        No-throw guarantee.
    */
#ifdef BOOST_JSON_DOCS
    BOOST_JSON_DECL
    ~serializer() noexcept;
#endif // BOOST_JSON_DOCS

    /** Constructor

        This constructs a serializer with no value.
        The value may be set later by calling @ref reset.
        If serialization is attempted with no value,
        the output is as if a null value is serialized.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param opts The options for the serializer. If this parameter
        is omitted, the serializer will output only standard JSON.
    */
    BOOST_JSON_DECL
    serializer( serialize_options const& opts = {} ) noexcept;

    /** Constructor

        This constructs a serializer with no value.
        The value may be set later by calling @ref reset.
        If serialization is attempted with no value,
        the output is as if a null value is serialized.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the `boost::container::pmr::memory_resource` to
        use when producing partial output. Shared ownership of the memory
        resource is retained until the serializer is destroyed.

        @param buf An optional static buffer to
        use for temporary storage when producing
        partial output.

        @param buf_size The number of bytes of
        valid memory pointed to by `buf`.

        @param opts The options for the serializer. If this parameter
        is omitted, the serializer will output only standard JSON.
    */
    BOOST_JSON_DECL
    serializer(
        storage_ptr sp,
        unsigned char* buf = nullptr,
        std::size_t buf_size = 0,
        serialize_options const& opts = {}) noexcept;

    /** Returns `true` if the serialization is complete

        This function returns `true` when all of the
        characters in the serialized representation of
        the value have been read.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    done() const noexcept
    {
        return done_;
    }

    /** Reset the serializer for a new element

        This function prepares the serializer to emit
        a new serialized JSON representing `*p`.
        Any internally allocated memory is
        preserved and re-used for the new output.

        @param p A pointer to the element to serialize.
        Ownership is not transferred; The caller is
        responsible for ensuring that the lifetime of
        `*p` extends until it is no longer needed.
    */
    /** @{ */
    BOOST_JSON_DECL
    void
    reset(value const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(array const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(object const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(string const* p) noexcept;

    template<class T>
    void
    reset(T const* p) noexcept;
    /** @} */

    /** Reset the serializer for a new string

        This function prepares the serializer to emit
        a new serialized JSON representing the string.
        Any internally allocated memory is
        preserved and re-used for the new output.

        @param sv The characters representing the string.
        Ownership is not transferred; The caller is
        responsible for ensuring that the lifetime of
        the characters reference by `sv` extends
        until it is no longer needed.
    */
    BOOST_JSON_DECL
    void
    reset(string_view sv) noexcept;

    /** Reset the serializer for std::nullptr_t

        This function prepares the serializer to emit
        a new serialized JSON representing null.
        Any internally allocated memory is
        preserved and re-used for the new output.
    */
    BOOST_JSON_DECL
    void
    reset(std::nullptr_t) noexcept;

    /** Read the next buffer of serialized JSON

        This function attempts to fill the caller
        provided buffer starting at `dest` with
        up to `size` characters of the serialized
        JSON that represents the value. If the
        buffer is not large enough, multiple calls
        may be required.
\n
        If serialization completes during this call;
        that is, that all of the characters belonging
        to the serialized value have been written to
        caller-provided buffers, the function
        @ref done will return `true`.

        @par Preconditions
        @code
        this->done() == false
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A @ref string_view containing the
        characters written, which may be less than
        `size`.

        @param dest A pointer to valid memory of at
        least `size` bytes.

        @param size The maximum number of characters
        to write to the memory pointed to by `dest`.
    */
    BOOST_JSON_DECL
    string_view
    read(char* dest, std::size_t size);

    /** Read the next buffer of serialized JSON

        This function allows reading into a
        character array, with a deduced maximum size.

        @par Preconditions
        @code
        this->done() == false
        @endcode

        @par Effects
        @code
        return this->read( dest, N );
        @endcode

        @par Complexity
        Linear in `N`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A @ref string_view containing the
        characters written, which may be less than
        `size`.

        @param dest The character array to write to.
    */
    template<std::size_t N>
    string_view
    read(char(&dest)[N])
    {
        return read(dest, N);
    }

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    string_view
    read(char(&dest)[N], std::size_t n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
        return read(dest, n);
    }
#endif
};

} // namespace json
} // namespace boost

#include <boost/json/impl/serializer.hpp>

#endif
