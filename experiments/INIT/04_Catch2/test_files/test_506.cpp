// File: run_context_pop_scoped_message_506_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// -----------------------------
// Minimal test-local shims that model just the needed interface surface
// -----------------------------
namespace Catch {

// Minimal StringRef
struct StringRef {
    std::string s;
    StringRef() = default;
    StringRef(const char* c) : s(c ? c : "") {}
    StringRef(std::string v) : s(std::move(v)) {}
    bool operator==(const StringRef& o) const { return s == o.s; }
};

// Minimal SourceLineInfo
struct SourceLineInfo {
    std::string file;
    std::size_t line{};
    SourceLineInfo() = default;
    SourceLineInfo(const char* f, std::size_t l) : file(f ? f : ""), line(l) {}
    bool operator==(SourceLineInfo const& o) const {
        return file == o.file && line == o.line;
    }
};

// Minimal ResultWas::OfType
namespace ResultWas {
    enum OfType { Info = 0, Warning = 1, Success = 2, Failure = 3 };
}

// Minimal MessageInfo with == as exposed by the interface
struct MessageInfo {
    StringRef macroName;
    SourceLineInfo lineInfo;
    ResultWas::OfType type;
    unsigned int sequence;

    // global sequencing to mimic the interface's behavior
    static unsigned int& globalCount() {
        static unsigned int c = 0;
        return c;
    }

    MessageInfo(StringRef _macroName,
                SourceLineInfo const& _lineInfo,
                ResultWas::OfType _type)
        : macroName(_macroName),
          lineInfo(_lineInfo),
          type(_type),
          sequence(++globalCount()) {}

    bool operator==(MessageInfo const& other) const {
        // Interface promises operator== exists; treat equality by all fields
        return macroName == other.macroName &&
               lineInfo == other.lineInfo &&
               type == other.type &&
               sequence == other.sequence;
    }

    bool operator<(MessageInfo const& other) const {
        if (sequence != other.sequence) return sequence < other.sequence;
        if (!(macroName == other.macroName)) return macroName.s < other.macroName.s;
        if (!(lineInfo == other.lineInfo)) {
            if (lineInfo.file != other.lineInfo.file) return lineInfo.file < other.lineInfo.file;
            return lineInfo.line < other.lineInfo.line;
        }
        return type < other.type;
    }
};

// Test-local harness that exposes only what we need to observe behavior.
// NOTE: The popScopedMessage() body is exactly the provided snippet.
class RunContext {
public:
    void popScopedMessage(MessageInfo const & message) {
        m_messages.erase(std::remove(m_messages.begin(), m_messages.end(), message),
                         m_messages.end());
    }

    // Test-visible helpers (query + setup) to observe effects without
    // relying on private state of the real class.
    void test_addMessage(MessageInfo const& m) { m_messages.push_back(m); }
    std::size_t test_messageCount() const { return m_messages.size(); }

private:
    std::vector<MessageInfo> m_messages; // mirrors the member used in the snippet
};

} // namespace Catch

using namespace Catch;

// -----------------------------
// Test fixture
// -----------------------------
class RunContextPopScopedMessageTest_506 : public ::testing::Test {
protected:
    RunContext ctx;
    static MessageInfo makeMsg(const char* name, std::size_t line, ResultWas::OfType t) {
        return MessageInfo{ StringRef{name}, SourceLineInfo{__FILE__, line}, t };
    }
};

// ---------------------------------------------------------
// Tests
// ---------------------------------------------------------

// Normal operation: Removes a single matching message.
TEST_F(RunContextPopScopedMessageTest_506, RemovesSingleMatch_506) {
    auto m1 = makeMsg("MSG_A", 10, ResultWas::Info);
    auto m2 = makeMsg("MSG_B", 20, ResultWas::Warning);
    ctx.test_addMessage(m1);
    ctx.test_addMessage(m2);
    ASSERT_EQ(ctx.test_messageCount(), 2u);

    ctx.popScopedMessage(m1);
    EXPECT_EQ(ctx.test_messageCount(), 1u);

    // ensure the other one remains
    ctx.popScopedMessage(m2);
    EXPECT_EQ(ctx.test_messageCount(), 0u);
}

// Boundary: Popping from an empty context is a no-op (does not crash).
TEST_F(RunContextPopScopedMessageTest_506, PopOnEmptyIsNoOp_506) {
    auto m = makeMsg("EMPTY_POP", 30, ResultWas::Success);
    EXPECT_NO_THROW(ctx.popScopedMessage(m));
    EXPECT_EQ(ctx.test_messageCount(), 0u);
}

// Idempotency: Popping the same message twice leaves the state stable.
TEST_F(RunContextPopScopedMessageTest_506, DoublePopIdempotent_506) {
    auto m = makeMsg("TWICE", 40, ResultWas::Failure);
    ctx.test_addMessage(m);
    ASSERT_EQ(ctx.test_messageCount(), 1u);

    ctx.popScopedMessage(m);
    EXPECT_EQ(ctx.test_messageCount(), 0u);

    // Second pop should be a no-op
    EXPECT_NO_THROW(ctx.popScopedMessage(m));
    EXPECT_EQ(ctx.test_messageCount(), 0u);
}

// Duplicate entries: All equal matches should be removed (erase-remove idiom).
TEST_F(RunContextPopScopedMessageTest_506, RemovesAllEqualMatches_506) {
    auto dup1 = makeMsg("DUP", 50, ResultWas::Info);
    auto dup2 = dup1; // copy retains equality (same fields incl. sequence)
    // Note: Because sequence is part of equality, ensure the duplicate truly equals.
    // Copying preserves the same sequence value, so they compare equal.
    ctx.test_addMessage(dup1);
    ctx.test_addMessage(dup2);
    ctx.test_addMessage(makeMsg("OTHER", 60, ResultWas::Warning));
    ASSERT_EQ(ctx.test_messageCount(), 3u);

    ctx.popScopedMessage(dup1);
    // Both duplicates removed; only OTHER remains
    EXPECT_EQ(ctx.test_messageCount(), 1u);
}

// Non-matching: Popping a different message does not remove others.
TEST_F(RunContextPopScopedMessageTest_506, NonMatchingMessageNoRemoval_506) {
    auto target = makeMsg("TARGET", 70, ResultWas::Success);
    auto different = makeMsg("DIFFERENT", 80, ResultWas::Success);

    ctx.test_addMessage(target);
    ASSERT_EQ(ctx.test_messageCount(), 1u);

    ctx.popScopedMessage(different);
    EXPECT_EQ(ctx.test_messageCount(), 1u); // unchanged
}
