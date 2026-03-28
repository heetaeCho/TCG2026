// File: tests/generators/GeneratorUntypedBase_currentElementAsString_59_tests.cpp

#include <gtest/gtest.h>
#include <string>

// Include the public interface under test.
// Adjust the include path to match your project layout.
#include "Catch2/src/catch2/interfaces/catch_interfaces_generatortracker.hpp"

namespace {

using Catch::Generators::GeneratorUntypedBase;
using Catch::StringRef;

// Helper to convert Catch2's StringRef to std::string without relying on internals.
static std::string ToStdString(StringRef sr) {
    return std::string(sr.data(), sr.size());
}

// A tiny test double that overrides the (private virtual) stringifyImpl to:
//  - control the produced string
//  - count how many times the base calls it (observable effect)
class FakeGenerator_59 : public GeneratorUntypedBase {
public:
    FakeGenerator_59(std::string first, std::string second)
        : first_(std::move(first)), second_(std::move(second)) {}

    int stringifyCalls() const { return calls_; }

private:
    // Matches the base's private virtual signature. Even though the base declares
    // it private, overriding is allowed; the base will dispatch to this via the
    // virtual call inside currentElementAsString().
    const std::string stringifyImpl() override {
        ++calls_;
        if (first_call_) {
            first_call_ = false;
            return first_;
        }
        return second_;
    }

    int calls_ = 0;
    bool first_call_ = true;
    std::string first_, second_;
};

class GeneratorUntypedBaseTest_59 : public ::testing::Test {};

} // namespace

// [Normal operation] First call materializes the string via stringifyImpl,
// subsequent calls return the cached value without re-calling stringifyImpl.
TEST_F(GeneratorUntypedBaseTest_59, CachesValueAfterFirstCall_59) {
    FakeGenerator_59 gen("alpha", "beta");

    // First call: should invoke stringifyImpl once and return "alpha".
    StringRef r1 = gen.currentElementAsString();
    EXPECT_EQ(ToStdString(r1), "alpha");
    EXPECT_EQ(gen.stringifyCalls(), 1);

    // Second call: should return cached "alpha" and NOT call stringifyImpl again.
    StringRef r2 = gen.currentElementAsString();
    EXPECT_EQ(ToStdString(r2), "alpha");
    EXPECT_EQ(gen.stringifyCalls(), 1);

    // Third call: still cached.
    StringRef r3 = gen.currentElementAsString();
    EXPECT_EQ(ToStdString(r3), "alpha");
    EXPECT_EQ(gen.stringifyCalls(), 1);
}

// [Boundary condition] If the first produced string is empty,
// currentElementAsString() should (per the observable behavior) re-invoke
// stringifyImpl on a subsequent call, because the cache remains empty.
TEST_F(GeneratorUntypedBaseTest_59, EmptyStringIsNotCached_ReevaluatesOnNextCall_59) {
    // First stringifyImpl -> "", second stringifyImpl -> "now-nonempty"
    FakeGenerator_59 gen("", "now-nonempty");

    // First call: returns empty string, one stringifyImpl call.
    StringRef r1 = gen.currentElementAsString();
    EXPECT_TRUE(ToStdString(r1).empty());
    EXPECT_EQ(gen.stringifyCalls(), 1);

    // Second call: because previous cached value was empty, it should call stringifyImpl again,
    // and now return the new non-empty value.
    StringRef r2 = gen.currentElementAsString();
    EXPECT_EQ(ToStdString(r2), "now-nonempty");
    EXPECT_EQ(gen.stringifyCalls(), 2);

    // Third call: value is now non-empty and should be cached; no further calls expected.
    StringRef r3 = gen.currentElementAsString();
    EXPECT_EQ(ToStdString(r3), "now-nonempty");
    EXPECT_EQ(gen.stringifyCalls(), 2);
}

// [Idempotence of observable result] When the first value is non-empty,
// repeated calls must keep returning the same observable value (cache hit).
TEST_F(GeneratorUntypedBaseTest_59, RepeatedCallsReturnSameValueWhenNonEmpty_59) {
    // If stringifyImpl were called again it would return "changed",
    // but caching should prevent that.
    FakeGenerator_59 gen("first", "changed");

    auto s1 = ToStdString(gen.currentElementAsString());
    auto s2 = ToStdString(gen.currentElementAsString());
    auto s3 = ToStdString(gen.currentElementAsString());

    EXPECT_EQ(s1, "first");
    EXPECT_EQ(s2, "first");
    EXPECT_EQ(s3, "first");
    EXPECT_EQ(gen.stringifyCalls(), 1);
}
