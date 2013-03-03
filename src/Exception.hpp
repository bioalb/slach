//This exception class was modified from the Chaste source code.

#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

/**
 * @file
 * Contains the Exception class, along with some macros that are widely
 * used throughout the code.
 */
#include <string>
#include <sstream>
#include <cfloat>  // For DBL_MAX
#include <climits> // For UINT_MAX & INT_MAX, necessary in gcc-4.3
#include <cstdlib> // For system() etc., necessary in gcc-4.3

/** Use when initialising an unsigned variable that doesn't have a sensible default value. */
const unsigned UNSIGNED_UNSET = UINT_MAX;
/** Use when initialising an int variable that doesn't have a sensible default value. */
const int INT_UNSET = INT_MAX;
/** Use when initialising a double variable that doesn't have a sensible default value. */
const double DOUBLE_UNSET = DBL_MAX;

/**
 * Exception class.
 * All exceptions thrown by this code are currently instances of this class.
 *
 */
class Exception
{
public:
    /**
     * Construct an exception with a message string.
     *
     * @param rMessage  the message
     * @param rFilename  which source file threw the exception
     * @param lineNumber  which line number of the source file threw the exception
     */
    Exception(const std::string& rMessage, const std::string& rFilename, unsigned lineNumber);

    /**
     * Get the message associated with the exception with file and line number
     *
     * @return The message set when the exception was thrown including file and line number information
     **/
    std::string GetMessage() const;

    /**
     * Get the message associated with the exception
     *
     * @return The message text set when the exception was thrown.
     **/
    std::string GetShortMessage() const;

    /**
     * Helper method for checking we have the right exception.
     *
     * Checks that #mShortMessage matches that given, and returns
     * a suitable error message string if not.  If they do match,
     * returns the empty string.
     *
     * @param expected  the expected value of #mShortMessage
     */
    std::string CheckShortMessage(std::string expected) const;

    /**
     * Helper method for checking we have the right exception.
     *
     * Checks that #mShortMessage contains the given string, and
     * returns a suitable error message string if not.  If it does,
     * returns the empty string.
     *
     * @param expected  some expected substring of #mShortMessage
     */
    std::string CheckShortMessageContains(std::string expected) const;

    /**
     * Level 4 error (Termination).  Execution cannot continue from this point and hence
     * should be terminated (even when running with NDEBUG or in parallel).
     *
     * @param rMessage An error message to appear on the screen
     * @param rFilename  which source file produced the termination error
     * @param lineNumber  which line number of the source file produced the termination error
     */
    static void Terminate(const std::string& rMessage, const std::string& rFilename, unsigned lineNumber);

protected:
    /**
     * Allow subclasses to reset the exception message after construction of the base class,
     * if desired.
     *
     * @param rMessage  the message
     * @param rFilename  which source file threw the exception
     * @param lineNumber  which line number of the source file threw the exception
     */
    void SetMessage(const std::string& rMessage,
                    const std::string& rFilename, unsigned lineNumber);

private:
    std::string mMessage; /**< Full exception message - includes file and line number. */
    std::string mShortMessage; /**< Short exception message - just text of the exception. */
};

/**
 * Terminate execution safely, even when running in parallel.  Use for level 4 errors:
 * execution cannot continue from this point and hence should be terminated (even when running with NDEBUG).
 *
 * @param message  explanatory message
 */
#define TERMINATE(message)                           \
    do {                                             \
        std::stringstream msg_stream;                \
        msg_stream << message;                       \
        Exception::Terminate(msg_stream.str(), __FILE__, __LINE__); \
    } while (false)

/**
 * Convenience macro for throwing an exception, in order to add file and line info.
 *
 * @param message  the error message to use, as a streamed expression
 */
#define EXCEPTION(message)                           \
    do {                                             \
        std::stringstream msg_stream;                \
        msg_stream << message;                       \
        throw Exception(msg_stream.str(), __FILE__, __LINE__); \
    } while (false)

/**
 * Use for control paths that will never be executed, just to make sure they aren't.
 *
 * The exit statement at the end of NEVER_REACHED is not really needed but prevents g++ from complaining about
 * uninitialised variables when you have code that looks like:
 *
 * \code
 *   RelativeTo::Value relative_to;
 *   switch (rPath.relative_to())
 *   {
 *       case cp::relative_to_type::cwd:
 *           relative_to = RelativeTo::CWD;
 *           break;
 *       case cp::relative_to_type::chaste_test_output:
 *           relative_to = RelativeTo::ChasteTestOutput;
 *           break;
 *       case cp::relative_to_type::chaste_source_root:
 *           relative_to = RelativeTo::ChasteSourceRoot;
 *           break;
 *       case cp::relative_to_type::absolute:
 *           relative_to = RelativeTo::Absolute;
 *           break;
 *       default:
 *           NEVER_REACHED;
 *           break;
 *   }
 * \endcode
 *
 * relative_to is considered potentially uninitialised in the default branch unless the compiler finds a exit,
 * assert or throw statement.
 */
#define NEVER_REACHED  TERMINATE("Should have been impossible to reach this line of code"); exit(EXIT_FAILURE)
#endif
