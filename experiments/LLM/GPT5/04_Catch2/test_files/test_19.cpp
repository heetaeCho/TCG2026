// File: tests/NullOStreamTest_19.cpp

#include <gtest/gtest.h>
#include <ostream>
#include <string>
#include "Catch2/fuzzing/NullOStream.h"

// We use only public/standard observable behavior.
// No assumptions about internal state or NullStreambuf internals.

class NullOStreamTest_19 : public ::testing::Test {
protected:
    NullOStream os_; // Construct once per test
};

// [Normal] Default construction leaves the stream usable.
TEST_F(NullOStreamTest_19, Construct_DefaultState_19) {
    EXPECT_TRUE(os_.good());
    EXPECT_FALSE(os_.fail());
    EXPECT_FALSE(os_.bad());
}

// [Boundary] rdbuf() returns a non-null pointer.
TEST_F(NullOStreamTest_19, Rdbuf_IsNonNull_19) {
    EXPECT_NE(os_.rdbuf(), nullptr);
}

// [Normal] rdbuf() from NullOStream matches the std::ostream base rdbuf().
TEST_F(NullOStreamTest_19, Rdbuf_MatchesBaseRdbuf_19) {
    std::streambuf* from_base = static_cast<std::ostream&>(os_).rdbuf();
    std::streambuf* from_null = static_cast<std::streambuf*>(os_.rdbuf());
    EXPECT_EQ(from_base, from_null);
}

// [Normal] Insertion operators return the same stream and keep it in a good state.
TEST_F(NullOStreamTest_19, InsertionOperators_ReturnSelf_AndRemainGood_19) {
    auto& ref = (os_ << "hello " << 123 << ' ' << 4.5);
    EXPECT_EQ(&ref, &os_);      // operator<< returns *this
    EXPECT_TRUE(os_.good());    // stream stays usable
}

// [Normal] Standard manipulators (endl/flush) work and keep the stream usable.
TEST_F(NullOStreamTest_19, Manipulators_Work_AndRemainGood_19) {
    auto& r1 = (os_ << std::endl); // newline + flush
    EXPECT_EQ(&r1, &os_);
    EXPECT_TRUE(os_.good());

    auto& r2 = (os_ << std::flush); // explicit flush
    EXPECT_EQ(&r2, &os_);
    EXPECT_TRUE(os_.good());
}

// [Boundary] Very large output is accepted without setting badbit/failbit.
TEST_F(NullOStreamTest_19, LargeOutput_DoesNotSetBadOrFail_19) {
    std::string big(1 << 20, 'x'); // ~1MB
    os_ << big;
    EXPECT_TRUE(os_.good());
    EXPECT_FALSE(os_.fail());
    EXPECT_FALSE(os_.bad());
}

// [Exceptional/Observable] Manually setting badbit is reflected in stream state and persists.
TEST_F(NullOStreamTest_19, SetBadbit_ReflectedAndPersists_19) {
    os_.setstate(std::ios::badbit);
    EXPECT_TRUE(os_.bad());
    EXPECT_FALSE(os_.good());

    // Further writes should not clear badbit.
    os_ << "still bad";
    EXPECT_TRUE(os_.bad());
    EXPECT_FALSE(os_.good());
}
