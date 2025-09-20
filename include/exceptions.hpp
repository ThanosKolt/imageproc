#include <stdexcept>

class UserException : public std::runtime_error{
    public:
    UserException(const std::string& msg)
        :std::runtime_error(msg){}
};
