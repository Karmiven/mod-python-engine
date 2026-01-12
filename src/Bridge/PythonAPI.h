#ifndef MOD_PYTHON_ENGINE_API_H
#define MOD_PYTHON_ENGINE_API_H

#include "PythonHeaders.h"
#include <string>

namespace PyEng::Bridge
{
    /**
     * @brief Python C API wrapper providing safe access to Python operations
     */
    class API
    {
    public:
        // Core type aliases
        using Object = boost::python::object;
        using List = boost::python::list;
        using Dict = boost::python::dict;
        using Tuple = boost::python::tuple;
        using Str = boost::python::str;
        using ErrorAlreadySet = boost::python::error_already_set;

        // Object creation
        static Object FromString(std::string const& s) { return Object(s); }

        // Module operations
        static Object Import(std::string const& name)
        {
            return boost::python::import(boost::python::str(name));
        }

        // Execution
        static Object ExecFile(std::string const& filepath, Object& globals, Object& locals)
        {
            return boost::python::exec_file(filepath.c_str(), globals, locals);
        }

        static Object Exec(std::string const& code, Object& globals, Object& locals)
        {
            return boost::python::exec(boost::python::str(code), globals, locals);
        }

        // Pointer wrapper
        template<typename T>
        static auto Ptr(T* ptr)
        {
            return boost::python::ptr(ptr);
        }

        // Extraction
        template<typename T>
        static T Extract(Object const& obj)
        {
            return boost::python::extract<T>(obj);
        }

        // Checks
        static bool IsNone(Object const& obj) { return obj.ptr() == Py_None; }
        static bool IsCallable(Object const& obj) { return PyCallable_Check(obj.ptr()); }

    private:
        API() = delete;
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_API_H
