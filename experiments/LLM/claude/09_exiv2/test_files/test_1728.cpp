#include <gtest/gtest.h>

// Recreate the struct based on the known interface
namespace Exiv2 {
struct mimeType {
    int comp;
    const char* type;
    bool operator==(int c) const {
        return comp == c;
    }
};
}

class MimeTypeTest_1728 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test equality operator returns true when comp matches
TEST_F(MimeTypeTest_1728, EqualityOperatorReturnsTrueWhenCompMatches_1728) {
    Exiv2::mimeType mt;
    mt.comp = 42;
    mt.type = "image/jpeg";
    EXPECT_TRUE(mt == 42);
}

// Test equality operator returns false when comp does not match
TEST_F(MimeTypeTest_1728, EqualityOperatorReturnsFalseWhenCompDoesNotMatch_1728) {
    Exiv2::mimeType mt;
    mt.comp = 42;
    mt.type = "image/jpeg";
    EXPECT_FALSE(mt == 43);
}

// Test equality with zero value
TEST_F(MimeTypeTest_1728, EqualityOperatorWithZero_1728) {
    Exiv2::mimeType mt;
    mt.comp = 0;
    mt.type = "image/tiff";
    EXPECT_TRUE(mt == 0);
    EXPECT_FALSE(mt == 1);
}

// Test equality with negative value
TEST_F(MimeTypeTest_1728, EqualityOperatorWithNegativeValue_1728) {
    Exiv2::mimeType mt;
    mt.comp = -1;
    mt.type = "image/png";
    EXPECT_TRUE(mt == -1);
    EXPECT_FALSE(mt == 1);
}

// Test equality with large positive value
TEST_F(MimeTypeTest_1728, EqualityOperatorWithLargePositiveValue_1728) {
    Exiv2::mimeType mt;
    mt.comp = 2147483647; // INT_MAX
    mt.type = "application/octet-stream";
    EXPECT_TRUE(mt == 2147483647);
    EXPECT_FALSE(mt == 0);
}

// Test equality with large negative value
TEST_F(MimeTypeTest_1728, EqualityOperatorWithLargeNegativeValue_1728) {
    Exiv2::mimeType mt;
    mt.comp = -2147483648; // INT_MIN
    mt.type = "application/octet-stream";
    EXPECT_TRUE(mt == -2147483648);
    EXPECT_FALSE(mt == 0);
}

// Test that type field can be set and accessed
TEST_F(MimeTypeTest_1728, TypeFieldCanBeSetAndAccessed_1728) {
    Exiv2::mimeType mt;
    mt.comp = 1;
    mt.type = "image/jpeg";
    EXPECT_STREQ(mt.type, "image/jpeg");
}

// Test that type field can be nullptr
TEST_F(MimeTypeTest_1728, TypeFieldCanBeNull_1728) {
    Exiv2::mimeType mt;
    mt.comp = 0;
    mt.type = nullptr;
    EXPECT_EQ(mt.type, nullptr);
}

// Test equality operator does not depend on type field
TEST_F(MimeTypeTest_1728, EqualityOperatorIndependentOfType_1728) {
    Exiv2::mimeType mt1;
    mt1.comp = 5;
    mt1.type = "image/jpeg";

    Exiv2::mimeType mt2;
    mt2.comp = 5;
    mt2.type = "image/png";

    EXPECT_TRUE(mt1 == 5);
    EXPECT_TRUE(mt2 == 5);
}

// Test multiple comparisons on same object
TEST_F(MimeTypeTest_1728, MultipleComparisonsOnSameObject_1728) {
    Exiv2::mimeType mt;
    mt.comp = 10;
    mt.type = "image/tiff";

    EXPECT_TRUE(mt == 10);
    EXPECT_FALSE(mt == 9);
    EXPECT_FALSE(mt == 11);
    EXPECT_FALSE(mt == -10);
    EXPECT_FALSE(mt == 0);
}

// Test const correctness - operator== is const
TEST_F(MimeTypeTest_1728, EqualityOperatorIsConst_1728) {
    const Exiv2::mimeType mt = {7, "image/bmp"};
    EXPECT_TRUE(mt == 7);
    EXPECT_FALSE(mt == 8);
}

// Test with comp value of 1
TEST_F(MimeTypeTest_1728, EqualityOperatorWithCompOne_1728) {
    Exiv2::mimeType mt;
    mt.comp = 1;
    mt.type = "image/jpeg";
    EXPECT_TRUE(mt == 1);
    EXPECT_FALSE(mt == 0);
    EXPECT_FALSE(mt == 2);
}
