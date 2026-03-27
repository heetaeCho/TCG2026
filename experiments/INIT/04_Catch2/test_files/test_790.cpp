// File: tests/ReporterMulti_reportInvalidTestSpec_790.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include <string>

// --- Test-only mock ----------------------------------------------------------

class MockListener_790 : public Catch::IEventListener {
public:
    // IEventListener requires a config pointer; we don't use it in these tests.
    explicit MockListener_790() : Catch::IEventListener(nullptr) {}

    // Only override what we observe in these tests.
    MOCK_METHOD(void, reportInvalidTestSpec, (Catch::StringRef), (override));
};

// A small matcher that compares Catch::StringRef by value.
MATCHER_P(StringRefEq_790, expected, "StringRef equals the expected string") {
    return std::string(arg.data(), arg.size()) == expected;
}

// Helper to create a Catch::Detail::unique_ptr<T> easily.
// (Uses the public constructor from pointer; no internal logic assumed.)
template <typename T, typename... Args>
static Catch::Detail::unique_ptr<T> makeCatchUnique_790(Args&&... args) {
    return Catch::Detail::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// --- Tests -------------------------------------------------------------------

// [Boundary] No children: calling reportInvalidTestSpec should not crash or call anything.
TEST(MultiReporter_ReportInvalidTestSpec, NoChildren_790) {
    // Many Catch2 builds have MultiReporter taking IConfig* in its ctor; if your
    // build differs (e.g., default-constructible), adjust the construction line.
    Catch::MultiReporter multi(/* IConfig* */ nullptr);

    // No reporters/listeners added.
    multi.reportInvalidTestSpec(Catch::StringRef("anything")); // should be a no-op
    SUCCEED(); // Reaching here without exceptions/crash indicates success.
}

// [Normal] Single collaborator receives the forwarded argument exactly.
TEST(MultiReporter_ReportInvalidTestSpec, SingleChild_ForwardsArg_790) {
    Catch::MultiReporter multi(/* IConfig* */ nullptr);

    auto ptr = makeCatchUnique_790<testing::StrictMock<MockListener_790>>();
    auto* raw = ptr.get(); // Keep raw to set expectations after move.

    const std::string input = "bad[spec]:tag??";
    EXPECT_CALL(*raw, reportInvalidTestSpec(StringRefEq_790(input))).Times(1);

    // Use either addReporter or addListener; both are public and valid ways to
    // register collaborators (we do not rely on internal storage details).
    multi.addReporter(std::move(ptr));

    multi.reportInvalidTestSpec(Catch::StringRef(input));
}

// [Normal] Multiple collaborators are all notified (order not asserted).
TEST(MultiReporter_ReportInvalidTestSpec, MultipleChildren_AllNotified_790) {
    Catch::MultiReporter multi(/* IConfig* */ nullptr);

    auto p1 = makeCatchUnique_790<testing::StrictMock<MockListener_790>>();
    auto p2 = makeCatchUnique_790<testing::StrictMock<MockListener_790>>();
    auto* r1 = p1.get();
    auto* r2 = p2.get();

    const std::string arg = "some invalid filter expression";

    EXPECT_CALL(*r1, reportInvalidTestSpec(StringRefEq_790(arg))).Times(1);
    EXPECT_CALL(*r2, reportInvalidTestSpec(StringRefEq_790(arg))).Times(1);

    multi.addListener(std::move(p1));
    multi.addReporter(std::move(p2));

    multi.reportInvalidTestSpec(Catch::StringRef(arg));
}

// [Boundary] Empty & special/unicode strings are forwarded unchanged.
TEST(MultiReporter_ReportInvalidTestSpec, ForwardsEmptyAndSpecialChars_790) {
    Catch::MultiReporter multi(/* IConfig* */ nullptr);

    auto ptr = makeCatchUnique_790<testing::StrictMock<MockListener_790>>();
    auto* raw = ptr.get();

    const std::string empty = "";
    const std::string special = std::string("[]{}*?\\\n\t\x01") + u8"유니코드✓";

    {
        ::testing::InSequence s; // independent sequences per block; not asserting cross-call order
        EXPECT_CALL(*raw, reportInvalidTestSpec(StringRefEq_790(empty))).Times(1);
        EXPECT_CALL(*raw, reportInvalidTestSpec(StringRefEq_790(special))).Times(1);
    }

    multi.addReporter(std::move(ptr));

    multi.reportInvalidTestSpec(Catch::StringRef(empty));
    multi.reportInvalidTestSpec(Catch::StringRef(special));
}
