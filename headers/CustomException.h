#include <exception>
#include <string>

class CustomException : public std::exception
{
public:
    explicit CustomException(const std::string &message)
        : msg_(message) {}

    // Override the what() function to provide the exception message
    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};