// File: boundvalueref_vector_setvalue_378_tests.cpp
#include <gtest/gtest.h>

// Include the real header from your tree
// Adjust the include path as needed in your build
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace C = Catch::Clara::Detail;

class BoundValueRefVector_SetValue_Test_378 : public ::testing::Test {
protected:
    std::vector<int> values_;
    // Use the vector-accepting ctor of BoundValueRef<T>
    std::unique_ptr<C::BoundValueRef<int>> ref_;

    void SetUp() override {
        ref_ = std::make_unique<C::BoundValueRef<int>>(values_);
    }
};

/**
 * Normal operation: a valid integer string should convert successfully
 * and be appended to the referenced vector.
 */
TEST_F(BoundValueRefVector_SetValue_Test_378, AppendsOnSuccess_378) {
    auto result = ref->setValue("7");
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(values_.size(), 1u);
    EXPECT_EQ(values_[0], 7);
}

/**
 * Multiple calls: successive successful conversions should append
 * in order (verifies push_back and ordering).
 */
TEST_F(BoundValueRefVector_SetValue_Test_378, AppendsInOrderAcrossCalls_378) {
    EXPECT_TRUE(static_cast<bool>(ref->setValue("1")));
    EXPECT_TRUE(static_cast<bool>(ref->setValue("2")));
    EXPECT_TRUE(static_cast<bool>(ref->setValue("3")));

    ASSERT_EQ(values_.size(), 3u);
    EXPECT_EQ(values_[0], 1);
    EXPECT_EQ(values_[1], 2);
    EXPECT_EQ(values_[2], 3);
}

/**
 * Failure case: an invalid integer string should NOT append anything
 * and should return a failing ParserResult.
 */
TEST_F(BoundValueRefVector_SetValue_Test_378, DoesNotAppendOnFailure_378) {
    // Seed with one good value so we can assert "no change" on failure
    ASSERT_TRUE(static_cast<bool>(ref->setValue("10")));
    ASSERT_EQ(values_.size(), 1u);

    auto bad = ref->setValue("not-an-int");
    EXPECT_FALSE(static_cast<bool>(bad));
    // Vector should remain unchanged
    EXPECT_EQ(values_.size(), 1u);
    EXPECT_EQ(values_[0], 10);
}

/**
 * Boundary: empty string as input should fail conversion for int,
 * and therefore not append to the vector.
 */
TEST_F(BoundValueRefVector_SetValue_Test_378, EmptyStringFails_NoAppend_378) {
    auto res = ref->setValue("");
    EXPECT_FALSE(static_cast<bool>(res));
    EXPECT_TRUE(values_.empty());
}

/**
 * Boundary: extremal numeric value (INT_MAX) as a string.
 * If the library accepts it, it should append correctly.
 * This test asserts observable success and correct stored value.
 */
TEST_F(BoundValueRefVector_SetValue_Test_378, AcceptsIntMaxWhenConvertible_378) {
    const std::string maxStr = std::to_string(std::numeric_limits<int>::max());
    auto res = ref->setValue(maxStr);
    // Treat behavior as black box: just assert based on the returned result.
    if (static_cast<bool>(res)) {
        ASSERT_EQ(values_.size(), 1u);
        EXPECT_EQ(values_[0], std::numeric_limits<int>::max());
    } else {
        // If conversion is rejected by the underlying parser, it must not append.
        EXPECT_TRUE(values_.empty());
    }
}
