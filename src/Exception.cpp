#include <iostream>


#include "Exception.hpp"

Exception::Exception(const std::string& rMessage,
                     const std::string& rFilename, unsigned lineNumber)
{
    SetMessage(rMessage, rFilename, lineNumber);
    ///// The following would write the error message to the log file, if one exists.
    ///// It's commented out because you end up with 100s of errors in the log from
    ///// element nodes being swapped around when the mesh is read in.
    //// No way of saying here whether this will be a fatal error, but write
    //// it to the log file (if one exists) in case it is.
    // std::string log_file_message = "Exception occurred (although possibly handled), error message:\n" + message;
    // LOG(1, log_file_message);
}

void Exception::SetMessage(const std::string& rMessage,
                           const std::string& rFilename, unsigned lineNumber)
{
    mShortMessage = rMessage;
    std::stringstream line_number_stream;
    line_number_stream << lineNumber;
    mMessage = std::string("\nChaste error: ") + rFilename + ":"  + line_number_stream.str()  + ": " + mShortMessage;
}

std::string Exception::GetMessage() const
{
    return mMessage;
}

std::string Exception::GetShortMessage() const
{
    return mShortMessage;
}

std::string Exception::CheckShortMessage(std::string expected) const
{
    std::string error;
    if (mShortMessage != expected && mShortMessage != "Another process threw an exception; bailing out.")
    {
        error = "Incorrect exception message thrown: expected (" + expected + "); got (" + mShortMessage + ").";
    }
    return error;
}

std::string Exception::CheckShortMessageContains(std::string expected) const
{
    std::string error;
    if (mShortMessage.find(expected) == std::string::npos && mShortMessage != "Another process threw an exception; bailing out.")
    {
        error = "Incorrect exception message thrown: expected it to contain (" + expected + "); got (" + mShortMessage + ").";
    }
    return error;
}

void Exception::Terminate(const std::string& rMessage, const std::string& rFilename, unsigned lineNumber)
{
    std::stringstream error_message;

    error_message << "\nChaste termination: " << rFilename << ":" << lineNumber  << ": " << rMessage<<"\n";
    std::cerr << error_message.str();
    exit(EXIT_FAILURE);
}
