// http://turtle.sourceforge.net
//
// Copyright Mathieu Champlon 2008
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <turtle/detail/type_name.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>

namespace
{
    template< typename T >
    std::string to_string( const T& )
    {
        return boost::lexical_cast< std::string >( mock::detail::type_name( BOOST_SP_TYPEID( T ) ) );
    }
}

BOOST_AUTO_TEST_CASE( name_of_base_type_is_extracted )
{
    BOOST_CHECK_EQUAL( "char", to_string( 'a' ) );
    BOOST_CHECK_EQUAL( "bool", to_string( true ) );
    BOOST_CHECK_EQUAL( "int", to_string< int >( 0 ) );
    BOOST_CHECK_EQUAL( "short", to_string< short >( 0 ) );
    BOOST_CHECK_EQUAL( "long", to_string< long >( 0 ) );
    BOOST_CHECK_EQUAL( "unsigned int", to_string< unsigned int >( 0 ) );
    BOOST_CHECK_EQUAL( "unsigned short", to_string< unsigned short >( 0 ) );
    BOOST_CHECK_EQUAL( "unsigned long", to_string< unsigned long >( 0 ) );
}

struct my_type_in_default_namespace
{
    struct inner {};
};

BOOST_AUTO_TEST_CASE( name_of_type_in_default_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_type_in_default_namespace", to_string( my_type_in_default_namespace() ) );
}

BOOST_AUTO_TEST_CASE( name_of_inner_type_from_type_in_default_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "inner", to_string( my_type_in_default_namespace::inner() ) );
}

template< typename T >
struct my_template_type_in_default_namespace
{
    struct inner {};
};

BOOST_AUTO_TEST_CASE( name_of_template_type_in_default_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_template_type_in_default_namespace<int>", to_string( my_template_type_in_default_namespace<int>() ) );
}

BOOST_AUTO_TEST_CASE( name_of_inner_type_from_template_type_in_default_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "inner", to_string( my_template_type_in_default_namespace<int>::inner() ) );
}

namespace
{
    struct my_type_in_anonymous_namespace {};
}

BOOST_AUTO_TEST_CASE( name_of_type_in_anonymous_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_type_in_anonymous_namespace", to_string( my_type_in_anonymous_namespace() ) );
}

namespace nm
{
    struct my_type_from_named_namespace {};
}

BOOST_AUTO_TEST_CASE( name_of_type_from_named_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_type_from_named_namespace", to_string( nm::my_type_from_named_namespace() ) );
}

namespace nm
{
namespace inner
{
    struct my_type_in_named_inner_namespace {};
}
}

BOOST_AUTO_TEST_CASE( name_of_type_in_named_inner_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_type_in_named_inner_namespace", to_string( nm::inner::my_type_in_named_inner_namespace() ) );
}

namespace
{
namespace inner
{
    struct my_type_in_unnamed_inner_namespace {};
}
}

BOOST_AUTO_TEST_CASE( name_of_type_in_unnamed_inner_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_type_in_unnamed_inner_namespace", to_string( inner::my_type_in_unnamed_inner_namespace() ) );
}

BOOST_AUTO_TEST_CASE( name_of_local_type_is_extracted )
{
    struct my_local_type {};
    BOOST_CHECK_EQUAL( "my_local_type", boost::lexical_cast< std::string >( mock::detail::type_name( BOOST_SP_TYPEID( my_local_type ) ) ) );
}

namespace
{
    template< typename T >
    struct my_template_type
    {
        struct inner {};
    };
}

BOOST_AUTO_TEST_CASE( name_of_template_type_in_anonymous_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_template_type<int>", to_string( my_template_type< int >() ) );
    BOOST_CHECK_EQUAL( "my_template_type<exception>", to_string( my_template_type< std::exception >() ) );
}

BOOST_AUTO_TEST_CASE( name_of_inner_type_from_template_type_in_anonymous_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "inner", to_string( my_template_type< int >::inner() ) );
    BOOST_CHECK_EQUAL( "inner", to_string( my_template_type< std::exception >::inner() ) );
}

namespace nm
{
    template< typename T >
    struct my_template_type
    {
        struct inner {};
    };
}

BOOST_AUTO_TEST_CASE( name_of_template_type_in_named_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "my_template_type<int>", to_string( nm::my_template_type< int >() ) );
    BOOST_CHECK_EQUAL( "my_template_type<exception>", to_string( nm::my_template_type< std::exception >() ) );
}

BOOST_AUTO_TEST_CASE( name_of_inner_type_from_template_type_in_named_namespace_is_extracted )
{
    BOOST_CHECK_EQUAL( "inner", to_string( nm::my_template_type< int >::inner() ) );
    BOOST_CHECK_EQUAL( "inner", to_string( nm::my_template_type< std::exception >::inner() ) );
}

namespace nm2
{
    template< typename T >
    struct my_template_type
    {
        template< typename U >
        struct inner {};
    };
}

BOOST_AUTO_TEST_CASE( name_of_inner_type_from_template_type_in_named_namespace_is_extracted2 )
{
    BOOST_CHECK_EQUAL( "inner<int>", to_string( nm2::my_template_type< int >::inner< int >() ) );
    BOOST_CHECK_EQUAL( "inner<int>", to_string( nm2::my_template_type< std::exception >::inner< int >() ) );
}
