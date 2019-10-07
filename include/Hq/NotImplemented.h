#include <stdexcept>
#include <sstream>

namespace hq
{
class NotImplemented : public std::logic_error
{
public:
    NotImplemented()
        : std::logic_error("Function not yet implemented")
    {
    }

    NotImplemented(const char* message)
        : std::logic_error(message)
    {
    }
};
}

#define GLUE(a, b) a##b
#define JOIN(a, b) GLUE(a, b)
#define UNIQUE(sym) JOIN(sym, __LINE__)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define NOT_IMPLEMENTED       \
    throw hq::NotImplemented( \
        (std::string("Not implemented: ") + __FUNCTION__ + " (" __FILE__ ":" TOSTRING(__LINE__) ")").c_str())
