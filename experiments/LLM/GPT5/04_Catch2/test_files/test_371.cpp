// File: test_basicresult_enforceok_371.cpp
#include <gtest/gtest.h>

namespace Catch { namespace Clara { namespace Detail {

// Forward declarations from the provided interface
enum class ResultType { Ok = 0, LogicError = 1, RuntimeError = 2 };

template <typename T>
class BasicResult {
public:
    // Factories and API based on the provided interface
    template <typename U>
    static auto ok(U&& value) -> BasicResult;

    static auto ok() -> BasicResult;
    static auto logicError(std::string&& message) -> BasicResult;
    static auto runtimeError(std::string&& message) -> BasicResult;

    explicit operator bool() const;
    auto type() const -> ResultType;
    auto errorMessage() const -> std::string const&;

    // `enforceOk()` is tested as a black-box observable (death/no-death).
    // It is public in the snippet with the implementation. If it is protected
    // in your tree, expose it in tests via a trivial test-only subclass.
    void enforceOk() const; // from the snippet

    // Cross-type copy constructor (from the interface snippet)
    template <typename U>
    explicit BasicResult(BasicResult<U> const& other);
};

}}} // namespace Catch::Clara::Detail

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// ----------------------------- Tests ---------------------------------

// OK path should not terminate the process.
TEST(BasicResultEnforceOkTest_371, EnforceOk_DoesNotAbort_OnOk_371) {
    auto r = BasicResult<int>::ok();
    // If this aborts, the test process dies and the test fails.
    r.enforceOk();
    SUCCEED(); // Reached here => no abort/assert fired.
}

// LogicError should cause the process to die when enforceOk() is called.
TEST(BasicResultEnforceOkTest_371, EnforceOk_Death_OnLogicError_371) {
    auto r = BasicResult<int>::logicError(std::string{"bad logic"});
#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH(r.enforceOk(), ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/config.";
#endif
}

// RuntimeError should cause the process to die when enforceOk() is called.
TEST(BasicResultEnforceOkTest_371, EnforceOk_Death_OnRuntimeError_371) {
    auto r = BasicResult<int>::runtimeError(std::string{"boom"});
#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH(r.enforceOk(), ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/config.";
#endif
}

// Cross-type copy: behavior should be preserved after templated copy construction.
TEST(BasicResultEnforceOkTest_371, EnforceOk_Death_AfterCrossTypeCopy_371) {
    auto src = BasicResult<long>::runtimeError(std::string{"x-type"});
    BasicResult<int> copied(src); // uses templated copy ctor from interface
#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH(copied.enforceOk(), ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/config.";
#endif
}
