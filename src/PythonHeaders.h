#ifndef MOD_PYTHON_ENGINE_HEADERS_H
#define MOD_PYTHON_ENGINE_HEADERS_H

/**
 * Central include point for all Python/C++ integration. Handles environment
 * normalization (placeholders, compatibility, macros) before loading
 * the underlying library.
 */

// Primary attempt: Define the macro to request global placeholders
//    (This is standard Boost behavior, though AC might override it)
#ifndef BOOST_BIND_GLOBAL_PLACEHOLDERS
    #define BOOST_BIND_GLOBAL_PLACEHOLDERS
#endif

// Include boost bind headers (these will read the macro above)
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

// Fallback mechanism:
//    If the build system (CMake) explicitly defined BOOST_BIND_NO_PLACEHOLDERS,
//    the macro above is ignored. We must manually inject the namespace.
#if defined(BOOST_BIND_NO_PLACEHOLDERS)
    using namespace boost::placeholders;
#endif

// Include the core library
#include <boost/python.hpp>

#endif // MOD_PYTHON_ENGINE_HEADERS_H
