// File: tests/run_context_push_scoped_message_505_tests.cpp
#include <gtest/gtest.h>

// We provide minimal stand-ins for the dependent types used solely to
// construct MessageInfo instances for this black-box test. These test
// doubles avoid touching any private/internal RunContext state.
namespace Catch {

// Minimal stand-ins for dependency types referenced by MessageInfo ctor.
struct StringRef {
    const char* s{};
    StringRef() = default;
    explicit StringRef(const char* str) : s(str) {}
    operator const char*() const { return s; }
};

struct SourceLineInfo {
    const char* file{"dummy.cpp"};
    std::size_t line{1};
    SourceLineInfo() = default;
    SourceLineInfo(const char* f, std::size_t l) : file(f), line(l) {}
};

struct ResultWas { enum OfType { Ok = 0, Info = 1, Warning = 2, Failure = 3 }; };

// Minimal public-facing MessageInfo consistent with the provided interface.
struct MessageInfo {
    // Only the constructor and public equality/ordering operators are declared
    // by interface; we do not rely on or assert anything about internal fields.
    MessageInfo(StringRef macro, SourceLineInfo const& line, ResultWas::OfType t)
        : macroName(macro), lineInfo(line), type(t) {}

    // Public API surface we can legally depend on in black-box tests
    StringRef macroName;
    SourceLineInfo lineInfo;
    ResultWas::OfType type;
};

// Public facade for RunContext with only the method under test.
// We do not re-implement any internals; we just declare the method so we
// can call it. The implementation is provided by the production .cpp.
class RunContext {
public:
    void pushScopedMessage(MessageInfo const& message);
    void popScopedMessage(MessageInfo const& message); // used in one test for pairing semantics
};

} // namespace Catch

using namespace Catch;

class RunContextPushScopedMessageTest_505 : public ::testing::Test {
protected:
    RunContext ctx; // relies on production default construction if available

    static MessageInfo MakeMsg(const char* macro = "TEST_MACRO",
                               const char* file  = "file.cpp",
                               std::size_t line  = 42,
                               ResultWas::OfType type = ResultWas::Info) {
        return MessageInfo(StringRef{macro}, SourceLineInfo{file, line}, type);
    }
};

// Normal operation: pushing a single, well-formed message should not throw.
TEST_F(RunContextPushScopedMessageTest_505, PushSingleMessage_DoesNotThrow_505) {
    auto msg = MakeMsg("SINGLE", "single.cpp", 10, ResultWas::Info);
    EXPECT_NO_THROW(ctx.pushScopedMessage(msg));
}

// Boundary: pushing multiple messages back-to-back should be fine.
TEST_F(RunContextPushScopedMessageTest_505, PushMultipleMessages_DoesNotThrow_505) {
    auto a = MakeMsg("A", "a.cpp", 1, ResultWas::Info);
    auto b = MakeMsg("B", "b.cpp", 2, ResultWas::Warning);
    auto c = MakeMsg("C", "c.cpp", 3, ResultWas::Ok);

    EXPECT_NO_THROW(ctx.pushScopedMessage(a));
    EXPECT_NO_THROW(ctx.pushScopedMessage(b));
    EXPECT_NO_THROW(ctx.pushScopedMessage(c));
}

// Boundary: pushing duplicate/identical messages should not cause errors
// from the public interface perspective.
TEST_F(RunContextPushScopedMessageTest_505, PushDuplicateMessages_DoesNotThrow_505) {
    auto dup = MakeMsg("DUP", "dup.cpp", 99, ResultWas::Info);
    EXPECT_NO_THROW(ctx.pushScopedMessage(dup));
    EXPECT_NO_THROW(ctx.pushScopedMessage(dup)); // duplicate
}

// Usability: pushing a temporary (rvalue) should bind to const& and succeed.
TEST_F(RunContextPushScopedMessageTest_505, PushTemporaryMessage_DoesNotThrow_505) {
    EXPECT_NO_THROW(ctx.pushScopedMessage(MakeMsg("TEMP", "tmp.cpp", 7, ResultWas::Warning)));
}

// Pairing sanity: pushing then popping the same message should be callable
// without throwing (even though we do not assert internal side-effects).
TEST_F(RunContextPushScopedMessageTest_505, PushThenPop_IsCallableWithoutThrow_505) {
    auto msg = MakeMsg("PAIR", "pair.cpp", 5, ResultWas::Info);
    EXPECT_NO_THROW(ctx.pushScopedMessage(msg));
    EXPECT_NO_THROW(ctx.popScopedMessage(msg));
}
