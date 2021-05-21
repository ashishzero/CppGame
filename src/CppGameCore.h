#pragma once

#include <stdint.h>

#if defined(__clang__) || defined(__ibmxl__)
#define COMPILER_CLANG 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#elif defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(__MINGW32__) || defined(__MINGW64__)
#define COMPILER_MINGW 1
#elif defined(__INTEL_COMPILER)
#define COMPILER_INTEL 1
#else
#error Missing Compiler detection
#endif

#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_MSVC)
#define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif
#if !defined(COMPILER_INTEL)
#define COMPILER_INTEL 0
#endif

#if defined(__ANDROID__) || defined(__ANDROID_API__)
#define OS_ANDROID 1
#elif defined(__gnu_linux__) || defined(__linux__) || defined(linux) || defined(__linux)
#define OS_LINUX 1
#elif defined(macintosh) || defined(Macintosh)
#define OS_MAC 1
#elif defined(__APPLE__) && defined(__MACH__)
#defined OS_MAC 1
#elif defined(__APPLE__)
#define OS_IOS 1
#elif defined(_WIN64) || defined(_WIN32)
#define OS_WINDOWS 1
#else
#error Missing Operating System Detection
#endif

#if !defined(OS_ANDRIOD)
#define OS_ANDRIOD 0
#endif
#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif
#if !defined(OS_MAC)
#define OS_MAC 0
#endif
#if !defined(OS_IOS)
#define OS_IOS 0
#endif
#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64) || defined(_M_X64)
#define ARCH_X64 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(_X86_)
#define ARCH_X86 1
#elif defined(__arm__) || defined(__thumb__) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error Missing Architecture Identification
#endif

#if !defined(ARCH_X64)
#define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
#define ARCH_X86 0
#endif
#if !defined(ARCH_ARM)
#define ARCH_ARM 0
#endif
#if !defined(ARCH_ARM64)
#define ARCH_ARM64 0
#endif

#if defined(__GNUC__)
#define __PROCEDURE__ __FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define __PROCEDURE__ __PRETTY_PROCEDURE__
#elif defined(__FUNCSIG__)
#define __PROCEDURE__ __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define __PROCEDURE__ __PROCEDURE__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define __PROCEDURE__ __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define __PROCEDURE__ __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define __PROCEDURE__ __func__
#elif defined(_MSC_VER)
#define __PROCEDURE__ __FUNCSIG__
#else
#define __PROCEDURE__ "_unknown_"
#endif

#if defined(HAVE_SIGNAL_H) && !defined(__WATCOMC__)
#include <signal.h>  // raise()
#endif

#if defined(_MSC_VER)
#define TriggerBreakpoint() __debugbreak()
#elif ((!defined(__NACL__)) && ((defined(__GNUC__) || defined(__clang__)) && (defined(__i386__) || defined(__x86_64__))))
#define TriggerBreakpoint() __asm__ __volatile__("int $3\n\t")
#elif defined(__386__) && defined(__WATCOMC__)
#define TriggerBreakpoint() _asm { int 0x03}
#elif defined(HAVE_SIGNAL_H) && !defined(__WATCOMC__)
#define TriggerBreakpoint() raise(SIGTRAP)
#else
#define TriggerBreakpoint() ((int *)0) = 0
#endif

#define Unimplemented() TriggerBreakpoint()
#define Unreachable()   TriggerBreakpoint()
#define NoDefaultCase()      \
    default:                 \
        TriggerBreakpoint(); \
        break

#if !defined(BUILD_DEBUG) && !defined(BUILD_INTERNAL) && !defined(BUILD_RELEASE)
#if defined(_DEBUG) || defined(DEBUG)
#define BUILD_DEBUG
#elif defined(NDEBUG)
#define BUILD_RELEASE
#else
#define BUILD_DEBUG
#endif
#endif

#if !defined(ASSERTION_HANDLED)
#define AssertHandle(file, line, proc) TriggerBreakpoint()
#else
void AssertHandle(const char *file, int line, const char *proc);
#endif

#if defined(BUILD_DEBUG)
#define DebugTriggerbreakpoint TriggerBreakpoint
#define Assert(x)                                                  \
        do {                                                           \
            if (!(x)) AssertHandle(__FILE__, __LINE__, __PROCEDURE__); \
        } while (0)
#else
#define DebugTriggerbreakpoint()
#define Assert(x) \
        do {          \
            0;        \
        } while (0)
#endif

//
//
//

#if !defined(PRODUCT_NAME)
#define PRODUCT_NAME "Kuro"
#endif

//
//
//

#define ArrayCount(a)  (sizeof(a) / sizeof((a)[0]))
#define Minimum(a, b)  (((a) < (b)) ? (a) : (b))
#define Maximum(a, b)  (((a) > (b)) ? (a) : (b))
#define Clamp(a, b, v) Minimum(b, Maximum(a, v))

#if defined(__cplusplus)
#define _ConcatInternal(x, y) x##y
#define _Concat(x, y)         _ConcatInternal(x, y)

template <typename T>
struct ExitScope {
    T lambda;
    ExitScope(T lambda): lambda(lambda) { }
    ~ExitScope() { lambda(); }
};
struct ExitScopeHelp {
    template <typename T>
    ExitScope<T> operator+(T t) {
        return t;
    }
};
#define Defer const auto &_Concat(defer__, __LINE__) = ExitScopeHelp() + [&]()

struct String {
    uint8_t *Data;
    int64_t  Length;

    constexpr String(): Data(0), Length(0) { }
    template <int64_t _Length>
    constexpr String(const char(&a)[_Length]) : Data((uint8_t *)a), Length(_Length - 1) { }
    constexpr String(const uint8_t *_Data, int64_t _Length) : Data((uint8_t *)_Data), Length(_Length) { }
    constexpr String(const char *_Data, int64_t _Length) : Data((uint8_t *)_Data), Length(_Length) { }
    const uint8_t &operator[](const int64_t index) const {
        Assert(index < Length);
        return Data[index];
    }
    uint8_t &operator[](const int64_t index) {
        Assert(index < Length);
        return Data[index];
    }
};

#else

tyedef struct String {
    uint8_t *Data;
    int64_t  Length;
} String;
#define StringLiteral(lit) (String) { lit, (int64_t)(sizeof(lit) - 1) }

#endif
