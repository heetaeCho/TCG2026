#include <gtest/gtest.h>
#include <cstdint>

// We need to access the static function typeValid from the Exiv2 namespace.
// Since it's defined as static in image.cpp, we need to include or declare it.
// For testing purposes, we'll replicate the declaration to link against it.
// However, since it's a static function (internal linkage), we need to include the source.

// To test a static function in a .cpp file, we include the source file directly.
// This is a common technique for unit testing static/internal functions.
#include "image.cpp"

namespace {

class TypeValidTest_1064 : public ::testing::Test {
protected:
};

// Test: type value 0 should be invalid (below lower bound)
TEST_F(TypeValidTest_1064, TypeZeroIsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(0));
}

// Test: type value 1 should be valid (lower boundary)
TEST_F(TypeValidTest_1064, TypeOneIsValid_1064) {
    EXPECT_TRUE(Exiv2::typeValid(1));
}

// Test: type value 2 should be valid (just above lower boundary)
TEST_F(TypeValidTest_1064, TypeTwoIsValid_1064) {
    EXPECT_TRUE(Exiv2::typeValid(2));
}

// Test: type value 7 should be valid (middle value)
TEST_F(TypeValidTest_1064, TypeSevenIsValid_1064) {
    EXPECT_TRUE(Exiv2::typeValid(7));
}

// Test: type value 12 should be valid (just below upper boundary)
TEST_F(TypeValidTest_1064, TypeTwelveIsValid_1064) {
    EXPECT_TRUE(Exiv2::typeValid(12));
}

// Test: type value 13 should be valid (upper boundary)
TEST_F(TypeValidTest_1064, TypeThirteenIsValid_1064) {
    EXPECT_TRUE(Exiv2::typeValid(13));
}

// Test: type value 14 should be invalid (above upper bound)
TEST_F(TypeValidTest_1064, TypeFourteenIsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(14));
}

// Test: type value 100 should be invalid (well above upper bound)
TEST_F(TypeValidTest_1064, TypeHundredIsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(100));
}

// Test: maximum uint16_t value should be invalid
TEST_F(TypeValidTest_1064, TypeMaxUint16IsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(UINT16_MAX));
}

// Test: all valid types from 1 to 13 should return true
TEST_F(TypeValidTest_1064, AllValidTypesReturnTrue_1064) {
    for (uint16_t i = 1; i <= 13; ++i) {
        EXPECT_TRUE(Exiv2::typeValid(i)) << "Failed for type: " << i;
    }
}

// Test: values outside the valid range [1, 13] should return false
TEST_F(TypeValidTest_1064, ValuesOutsideRangeReturnFalse_1064) {
    // Check 0 and values from 14 to some reasonable upper limit
    EXPECT_FALSE(Exiv2::typeValid(0));
    for (uint16_t i = 14; i <= 100; ++i) {
        EXPECT_FALSE(Exiv2::typeValid(i)) << "Failed for type: " << i;
    }
}

// Test: type value 256 should be invalid (larger value)
TEST_F(TypeValidTest_1064, TypeTwoFiftySixIsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(256));
}

// Test: type value 1000 should be invalid
TEST_F(TypeValidTest_1064, TypeThousandIsInvalid_1064) {
    EXPECT_FALSE(Exiv2::typeValid(1000));
}

}  // namespace
