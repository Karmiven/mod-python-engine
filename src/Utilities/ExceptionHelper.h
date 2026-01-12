#ifndef MOD_PYTHON_ENGINE_EXCEPTION_HELPER_H
#define MOD_PYTHON_ENGINE_EXCEPTION_HELPER_H

#include "PythonException.h"
#include "PythonAPI.h"
#include <string>
#include <exception>

namespace PyEng::Utilities
{
    /**
     * @brief Exception helper utility
     */
    class ExceptionHelper
    {
    public:
        /**
         * @brief Format current exception
         *
         * Formats both Python and C++ exceptions into readable strings.
         * Must be called from within a catch block with GIL held.
         *
         * @return Formatted exception string
         */
        [[nodiscard]] static std::string Format()
        {
            try
            {
                std::rethrow_exception(std::current_exception());
            }
            catch (Bridge::API::ErrorAlreadySet const&)
            {
                std::string traceback = Bridge::ExceptionHandler::FormatException();
                if (traceback.empty())
                    traceback = "Unable to extract traceback...";

                return "Python Exception:\n" + traceback;
            }
            catch (std::exception const& e)
            {
                return std::string("C++ Exception:\n") + e.what();
            }
            catch (...)
            {
                return "Unknown exception occurred...";
            }
        }

    private:
        ExceptionHelper() = delete;
    };

} // namespace PyEng::Utilities

#endif // MOD_PYTHON_ENGINE_EXCEPTION_HELPER_H
