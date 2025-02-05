//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//


#include <boost/url/detail/config.hpp>
#include <boost/url/decode_view.hpp>
#include <boost/url/params_ref.hpp>
#include <boost/url/params_view.hpp>
#include <boost/url/url_base.hpp>
#include <boost/url/grammar/ci_string.hpp>
#include <boost/assert.hpp>
#include <utility>

namespace boost {
namespace urls {

//------------------------------------------------
//
// Special Members
//
//------------------------------------------------

auto
params_ref::
operator=(params_ref const& other) ->
    params_ref&
{
    if (!ref_.alias_of(other.ref_))
        assign(other.begin(), other.end());
    return *this;
}

params_ref::
operator
params_view() const noexcept
{
    return { ref_, opt_ };
}

//------------------------------------------------
//
// Modifiers
//
//------------------------------------------------

void
params_ref::
assign(
    std::initializer_list<
        param_view> init)
{
    assign(init.begin(), init.end());
}

auto
params_ref::
insert(
    iterator before,
    param_view const& p) ->
        iterator
{
    return iterator(
        u_->edit_params(
            before.it_,
            before.it_,
            detail::param_iter(p)),
        opt_);
}

auto
params_ref::
insert(
    iterator before,
    std::initializer_list<
        param_view> init) ->
    iterator
{
    return insert(
        before,
        init.begin(),
        init.end());
}

std::size_t
params_ref::
erase(
    core::string_view key,
    ignore_case_param ic) noexcept
{
    // end() can't be fully cached,
    // since erase invalidates it.
    iterator it;
    {
        auto const end_ = end();
        it = find_last(end_, key, ic);
        if(it == end_)
            return 0;
    }
    std::size_t n = 0;
    for(;;)
    {
        ++n;
        // Use it->key instead of key,
        // to handle self-intersection
        auto prev = find_last(it, (*it).key, ic);
        if(prev == end())
            break;
        erase(it);
        it = prev;
    }
    erase(it);
    return n;
}

auto
params_ref::
replace(
    iterator pos,
    param_view const& p) ->
        iterator
{
    return iterator(
        u_->edit_params(
            pos.it_,
            std::next(pos).it_,
            detail::param_iter(p)),
        opt_);
}

auto
params_ref::
replace(
    iterator from,
    iterator to,
    std::initializer_list<
        param_view> init) ->
    iterator
{
    return replace(
        from,
        to,
        init.begin(),
        init.end());
}

auto
params_ref::
unset(
    iterator pos) noexcept ->
        iterator
{
    BOOST_ASSERT(pos.it_.nk > 0);
    core::string_view s;
    return iterator(
        u_->edit_params(
            pos.it_,
            pos.it_.next(),
            detail::param_value_iter(
                pos.it_.nk - 1, s, false)),
        opt_);
}

auto
params_ref::
set(
    iterator pos,
    core::string_view value) ->
        iterator
{
    BOOST_ASSERT(pos.it_.nk > 0);
    return iterator(
        u_->edit_params(
            pos.it_,
            pos.it_.next(),
            detail::param_value_iter(
                pos.it_.nk - 1, value, true)),
        opt_);
}

auto
params_ref::
set(
    core::string_view key,
    core::string_view value,
    ignore_case_param ic) ->
        iterator
{
    // VFALCO we can't cache end() here
    // because it is invalidated
    // every time we set or erase.
    auto it0 = find(key, ic);
    if(it0 == end())
        return append({key, value});
    it0 = set(it0, value);
    auto it = end();
    for(;;)
    {
        it = find_last(it, key, ic);
        if(it == it0)
            return it0;
        it = erase(it);
    }
}

auto
params_ref::
erase(
    iterator pos) noexcept ->
    iterator
{
    return erase(
        pos,
        std::next(pos));
}

auto
params_ref::
erase(
    iterator first,
    iterator last) noexcept ->
        iterator
{
    core::string_view s("", 0);
    return iterator(
        u_->edit_params(
            first.it_,
            last.it_,
            detail::query_iter(s)),
        opt_);
}

} // urls
} // boost

