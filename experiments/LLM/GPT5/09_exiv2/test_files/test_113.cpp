#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "metadatum.hpp"  // Include the header for the Metadatum class
namespace Exiv2 {

// Test Fixture
class MetadatumTest_113 : public ::testing::Test {
protected:
    // Any setup required before each test case (if any)
    void SetUp() override {}

    // Any teardown required after each test case (if any)
    void TearDown() override {}
};

// Test for normal operation - comparing two `Metadatum` objects by their key
TEST_F(MetadatumTest_113, CompareMetadatumByKey_Normal_113) {
    Metadatum lhs;
    Metadatum rhs;

    // Mocking `key` method
    EXPECT_CALL(lhs, key()).WillOnce(testing::Return("keyA"));
    EXPECT_CALL(rhs, key()).WillOnce(testing::Return("keyB"));

    // Expecting lhs.key() < rhs.key()
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test for normal operation - comparing two `Metadatum` objects with the same key
TEST_F(MetadatumTest_113, CompareMetadatumByKey_EqualKeys_113) {
    Metadatum lhs;
    Metadatum rhs;

    // Mocking `key` method to return the same value for both
    EXPECT_CALL(lhs, key()).WillOnce(testing::Return("key"));
    EXPECT_CALL(rhs, key()).WillOnce(testing::Return("key"));

    // Expecting lhs.key() is not less than rhs.key()
    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test for boundary condition - empty key comparison
TEST_F(MetadatumTest_113, CompareMetadatumByKey_EmptyKey_113) {
    Metadatum lhs;
    Metadatum rhs;

    // Mocking `key` method to return empty string for lhs
    EXPECT_CALL(lhs, key()).WillOnce(testing::Return(""));
    EXPECT_CALL(rhs, key()).WillOnce(testing::Return("key"));

    // Expecting lhs.key() < rhs.key() since "" < "key"
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test for boundary condition - comparing two empty keys
TEST_F(MetadatumTest_113, CompareMetadatumByKey_EmptyKeys_113) {
    Metadatum lhs;
    Metadatum rhs;

    // Mocking `key` method to return empty string for both
    EXPECT_CALL(lhs, key()).WillOnce(testing::Return(""));
    EXPECT_CALL(rhs, key()).WillOnce(testing::Return(""));

    // Expecting lhs.key() is not less than rhs.key() (both are empty)
    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test for error or exceptional cases - null keys (if applicable to the implementation)
TEST_F(MetadatumTest_113, CompareMetadatumByKey_NullKey_113) {
    Metadatum lhs;
    Metadatum rhs;

    // Mocking `key` method to simulate null keys
    EXPECT_CALL(lhs, key()).WillOnce(testing::Return(""));
    EXPECT_CALL(rhs, key()).WillOnce(testing::Return(nullptr));

    // Expecting lhs.key() < rhs.key() since "" < nullptr (empty string < null pointer in the comparison)
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

}  // namespace Exiv2