#ifndef MOD_PYTHON_ENGINE_EXECUTION_RESULT_H
#define MOD_PYTHON_ENGINE_EXECUTION_RESULT_H

#include <string>
#include <utility>

namespace PyEng::Utilities
{
    /**
     * @brief Generic result container for operations that can succeed or fail
     *
     * Can be used for any operation that needs to return success/failure status
     * along with output or error information.
     */
    struct ExecutionResult
    {
        bool success;
        std::string output;
        std::string error;

        /**
         * @brief Implicit conversion to bool for easy success checking
         */
        explicit operator bool() const noexcept { return success; }

        /**
         * @brief Create a successful result
         *
         * @param output Output message string (optional)
         * @return ExecutionResult with success=true
         */
        static ExecutionResult Success(std::string const& output = "")
        {
            return {true, std::move(output), ""};
        }

        /**
         * @brief Create a failed result
         *
         * @param error Error message string
         * @return ExecutionResult with success=false
         */
        static ExecutionResult Error(std::string error)
        {
            return {false, "", std::move(error)};
        }

        /**
         * @brief Get the relevant message (output if success, error if failed)
         *
         * @return Reference to output or error string
         */
        [[nodiscard]] std::string const& GetMessage() const noexcept
        {
            return success ? output : error;
        }

        /**
         * @brief Check if result has any message content
         *
         * @return True if output or error is not empty, false otherwise
         */
        [[nodiscard]] bool HasMessage() const noexcept
        {
            return success ? !output.empty() : !error.empty();
        }
    };

} // namespace PyEng::Utilities

#endif // MOD_PYTHON_ENGINE_EXECUTION_RESULT_H
