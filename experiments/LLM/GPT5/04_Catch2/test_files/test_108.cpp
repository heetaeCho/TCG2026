// File: capturer_capturevalues_tests_108.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <utility>
#include <limits>

// ---- Minimal includes for the tested interface ----
#include "catch2/catch_message.hpp"   // Path as given in prompt

using ::testing::ElementsAre;
using ::testing::Pair;

namespace {

// A small spy that records the observable interactions:
// The template under test calls `captureValue(index, stringify(value))`.
// We do NOT touch private state; we only observe calls to the *public* method.
class CapturerSpy : public Catch::Capturer {
public:
    // Forward to a valid base constructor. We do not rely on any internal behavior.
    // Use innocuous/default-ish args that satisfy the signature.
    CapturerSpy()
    : Catch::Capturer(
          /*macroName*/ Catch::StringRef("TEST_MACRO"),
          /*lineInfo*/  Catch::SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)},
          /*resultType*/ Catch::ResultWas::Info,
          /*names*/ Catch::StringRef("v"))
    {}

    // Record the calls that the template directs here.
    void captureValue(std::size_t index, std::string const& value) {
        calls.emplace_back(index, value);
        // NOTE: Do not call base; we only observe (no internal side effects required for these tests).
    }

    std::vector<std::pair<std::size_t, std::string>> calls;
};

// A simple type that stringifies via operator<< (common Catch stringify route).
struct Widget {
    int id{};
};
inline std::ostream& operator<<(std::ostream& os, const Widget& w) {
    return os << "Widget(" << w.id << ")";
}

} // namespace

// ------------------ TESTS ------------------

// Normal: single value is forwarded with stringified content
TEST(CapturerCaptureValues_108, ForwardsIntAsString_108) {
    CapturerSpy cap;
    cap.captureValues(/*index*/0u, /*value*/123);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(0u, std::string("123")));
}

// Normal: std::string forwarded unchanged
TEST(CapturerCaptureValues_108, ForwardsStdString_108) {
    CapturerSpy cap;
    cap.captureValues(2u, std::string("hello"));

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(2u, std::string("hello")));
}

// Normal: const char* forwarded as string content
TEST(CapturerCaptureValues_108, ForwardsCString_108) {
    CapturerSpy cap;
    cap.captureValues(5u, "alpha");

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(5u, std::string("alpha")));
}

// Normal: bool becomes "true"/"false" (as produced by Catch::Detail::stringify)
TEST(CapturerCaptureValues_108, ForwardsBool_108) {
    CapturerSpy cap;
    cap.captureValues(1u, true);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(1u, std::string("true")));
}

// Boundary: lowest reasonable index (0)
TEST(CapturerCaptureValues_108, BoundaryIndexZero_108) {
    CapturerSpy cap;
    cap.captureValues(0u, 42);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(0u, std::string("42")));
}

// Boundary: very large index
TEST(CapturerCaptureValues_108, BoundaryIndexMax_108) {
    CapturerSpy cap;
    const std::size_t big = std::numeric_limits<std::size_t>::max();
    cap.captureValues(big, 7);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(big, std::string("7")));
}

// Normal: user-defined type stringifies via operator<<
TEST(CapturerCaptureValues_108, ForwardsUserDefinedTypeViaStream_108) {
    CapturerSpy cap;
    Widget w{99};
    cap.captureValues(3u, w);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(3u, std::string("Widget(99)")));
}

// Normal: variadic overload forwards each value (order & content)
TEST(CapturerCaptureValues_108, VariadicForwardsAllValuesInOrder_108) {
    CapturerSpy cap;
    // Expected to forward: index 0->"A", 1->"10", 2->"false"
    cap.captureValues(0u, std::string("A"), 10, false);

    ASSERT_EQ(cap.calls.size(), 3u);
    EXPECT_THAT(cap.calls, ElementsAre(
        Pair(0u, std::string("A")),
        Pair(1u, std::string("10")),
        Pair(2u, std::string("false"))
    ));
}

// Robustness: large string input
TEST(CapturerCaptureValues_108, LargeStringInput_108) {
    CapturerSpy cap;
    std::string big(10000, 'x');
    cap.captureValues(4u, big);

    ASSERT_EQ(cap.calls.size(), 1u);
    EXPECT_THAT(cap.calls[0], Pair(4u, big));
}

// Robustness: multiple sequential calls
TEST(CapturerCaptureValues_108, MultipleSequentialCalls_108) {
    CapturerSpy cap;
    cap.captureValues(0u, "first");
    cap.captureValues(1u, 2);
    cap.captureValues(2u, std::string("third"));

    ASSERT_EQ(cap.calls.size(), 3u);
    EXPECT_THAT(cap.calls, ElementsAre(
        Pair(0u, std::string("first")),
        Pair(1u, std::string("2")),
        Pair(2u, std::string("third"))
    ));
}
