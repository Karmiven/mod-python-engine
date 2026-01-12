#ifndef MOD_PYTHON_ENGINE_OUTPUT_H
#define MOD_PYTHON_ENGINE_OUTPUT_H

#include "PythonAPI.h"
#include <string>

namespace PyEng::Bridge
{
    /**
     * @brief RAII guard for capturing Python stdout/stderr
     *
     * Redirects sys.stdout and sys.stderr to a StringIO buffer, automatically
     * restoring original streams on destruction. Requires GIL to be held during
     * construction and destruction.
     */
    class OutputCapture
    {
    public:
        OutputCapture()
            : sysModule(API::Import("sys")),
              ioModule(API::Import("io")),
              oldStdout(sysModule.attr("stdout")),
              oldStderr(sysModule.attr("stderr")),
              stringIO(ioModule.attr("StringIO")())
        {
            sysModule.attr("stdout") = stringIO;
            sysModule.attr("stderr") = stringIO;
        }

        ~OutputCapture()
        {
            try
            {
                sysModule.attr("stdout") = oldStdout;
                sysModule.attr("stderr") = oldStderr;
            }
            catch (...) { /* skip exceptions in destructor */ }
        }

        OutputCapture(OutputCapture const&) = delete;
        OutputCapture& operator=(OutputCapture const&) = delete;

        /**
         * @brief Retrieve all captured output
         *
         * @return String containing captured stdout/stderr
         */
        std::string GetOutput() const
        {
            return API::Extract<std::string>(stringIO.attr("getvalue")());
        }

    private:
        API::Object sysModule;
        API::Object ioModule;
        API::Object oldStdout;
        API::Object oldStderr;
        API::Object stringIO;
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_OUTPUT_H