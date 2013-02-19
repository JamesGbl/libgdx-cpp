#ifndef GDX_CPP_LOG
#define GDX_CPP_LOG

#include <gdx-cpp/utils/ScopedGuard.hpp>
#include <string>
#include <stdexcept>

#define GDX_TO_STRING_MACRO(x) #x
#define GDX_TO_STRING_MACRO_(x) GDX_TO_STRING_MACRO(x)
#define GDX_TO_STRING_MACRO_LINE_ GDX_TO_STRING_MACRO_(__LINE__)

namespace gdx {
    void internal_log_debug(const std::string&, const std::string&, const std::string&, const char*, ...);
    void internal_log_info(const std::string&, const std::string&, const std::string&, const char*, ...);
    void internal_log_error(const std::string&, const std::string&, const std::string&, const char*, ...);
}

#ifdef GDX_LOG_LEVEL_DEBUG
#define gdx_log_debug(tag, format, ...) gdx::internal_log_debug(tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format, ##__VA_ARGS__)
#else
#define gdx_log_debug(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_INFO
#define gdx_log_info(tag, format, ...) gdx::internal_log_info(tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format, ##__VA_ARGS__)
#else
#define gdx_log_info(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_ERROR
#define gdx_log_error(tag, format, ...) do { gdx::internal_log_error(tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format,  ##__VA_ARGS__); gdx::ScopedGuard<RuntimeLogErrorExecutor> guard( (RuntimeLogErrorExecutor()) ); } while (false)
#else
#define gdx_log_error(tag, format, ...) ((void) 0)
#endif

struct RuntimeLogErrorExecutor {
    void operator()() const {         
         throw std::runtime_error("gdx runtime error, see the error output for detail");
    }
};

namespace gdx {
class Log {
public:
    virtual void debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    virtual void error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    virtual void info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    
    virtual ~Log() { }
};
}

#endif // GDX_CPP_LOG
