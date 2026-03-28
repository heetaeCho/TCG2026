// GeneratorUntypedBase_countedNext_tests_58.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the real Catch2 generator interface
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

using Catch::Generators::GeneratorUntypedBase;

namespace {

// A simple concrete generator for testing that overrides the virtual hooks.
// It exposes observable behavior via its own counters (not the SUT's internals).
class StubSequenceGenerator : public GeneratorUntypedBase {
public:
    explicit StubSequenceGenerator(std::vector<std::string> elems)
        : elems_(std::move(elems)) {}

    // How many times next() was invoked by the SUT
    int nextCalls() const { return next_calls_; }

    // How many times stringifyImpl() was invoked because of currentElementAsString()
    int stringifyCalls() const { return stringify_calls_; }

protected:
    // Move to the next element if possible
    bool next() override {
        ++next_calls_;
        if (pos_ + 1 < elems_.size()) {
            ++pos_;
            return true;
        }
        return false;
    }

    // Produce string for the current element
    const std::string stringifyImpl() override {
        ++stringify_calls_;
        if (elems_.empty()) return std::string();
        return elems_[pos_];
    }

private:
    std::vector<std::string> elems_;
    std::size_t pos_ = 0;
    int next_calls_ = 0;
    int stringify_calls_ = 0;
};

} // namespace

class GeneratorUntypedBaseTest_58 : public ::testing::Test {};

// --- Tests ---

// Verifies initial observable state via the public API.
TEST_F(GeneratorUntypedBaseTest_58, InitialIndexIsZero_58) {
    StubSequenceGenerator gen({ "only" });
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(0));
}

// Verifies that countedNext() returns the same value as the underlying next()
// and increments the public index only on success.
TEST_F(GeneratorUntypedBaseTest_58, CountedNextPropagatesResultAndIncrementsIndexOnSuccess_58) {
    StubSequenceGenerator gen({ "A", "B", "C" });

    // 1st advance: should succeed, index becomes 1
    bool r1 = gen.countedNext();
    EXPECT_TRUE(r1);
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(1));

    // 2nd advance: should succeed, index becomes 2
    bool r2 = gen.countedNext();
    EXPECT_TRUE(r2);
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(2));

    // 3rd advance: at end, should fail, index stays 2
    bool r3 = gen.countedNext();
    EXPECT_FALSE(r3);
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(2));
}

// Verifies that countedNext() does not change the index when next() fails.
TEST_F(GeneratorUntypedBaseTest_58, CountedNextDoesNotChangeIndexOnFailure_58) {
    StubSequenceGenerator gen({ "only" });
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(0));

    // No "next" element exists, so countedNext() should fail and leave index as-is.
    bool r = gen.countedNext();
    EXPECT_FALSE(r);
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(0));
}

// Verifies interaction: each call to countedNext() invokes the virtual next() exactly once.
TEST_F(GeneratorUntypedBaseTest_58, CountedNextInvokesNextExactlyOncePerCall_58) {
    StubSequenceGenerator gen({ "A", "B" });

    // Call countedNext() three times regardless of success/failure
    (void)gen.countedNext(); // true
    (void)gen.countedNext(); // false (end reached)
    (void)gen.countedNext(); // false (still at end)

    EXPECT_EQ(gen.nextCalls(), 3);
}

// Verifies that after a successful countedNext(), asking for the current element's
// string representation triggers (at least) one (re)stringify for the new element,
// which is observable via stringifyImpl() being called again.
TEST_F(GeneratorUntypedBaseTest_58, CurrentElementStringIsComputedForNewElementAfterSuccessfulAdvance_58) {
    StubSequenceGenerator gen({ "first", "second" });

    // Obtain string for the initial element
    (void)gen.currentElementAsString();
    int calls_before = gen.stringifyCalls();

    // Advance successfully
    ASSERT_TRUE(gen.countedNext());

    // Obtain string for the new current element — should require a new stringify
    (void)gen.currentElementAsString();
    int calls_after = gen.stringifyCalls();

    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(1));
    EXPECT_EQ(calls_after, calls_before + 1);
}

// Verifies boundary behavior: repeated calls past the end keep failing and do not change the index.
TEST_F(GeneratorUntypedBaseTest_58, RepeatedCountedNextPastEndRemainsFalseAndIndexStable_58) {
    StubSequenceGenerator gen({ "A", "B" });

    // Move to last valid element
    ASSERT_TRUE(gen.countedNext());
    EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(1));

    // Past the end: keep failing, index stays 1
    for (int i = 0; i < 5; ++i) {
        EXPECT_FALSE(gen.countedNext()) << "Failure expected on attempt " << i;
        EXPECT_EQ(gen.currentElementIndex(), static_cast<std::size_t>(1));
    }
}
