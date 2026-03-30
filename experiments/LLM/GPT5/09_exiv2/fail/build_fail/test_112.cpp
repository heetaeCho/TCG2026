#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/metadatum.hpp"

namespace Exiv2 {
    // Mock class for Metadatum
    class MockMetadatum : public Metadatum {
    public:
        MOCK_METHOD(uint16_t, tag, (), (const, override));
    };
}

// Unit test for cmpMetadataByTag
TEST_F(cmpMetadataByTagTest_112, TestComparison_LessThan_112) {
    // Creating mock objects
    Exiv2::MockMetadatum lhs;
    Exiv2::MockMetadatum rhs;

    // Setting up mock expectations
    EXPECT_CALL(lhs, tag())
        .WillOnce(testing::Return(1));  // lhs.tag() returns 1
    EXPECT_CALL(rhs, tag())
        .WillOnce(testing::Return(2));  // rhs.tag() returns 2

    // Testing if lhs.tag() < rhs.tag()
    EXPECT_TRUE(Exiv2::cmpMetadataByTag(lhs, rhs));  // Expects true since 1 < 2
}

TEST_F(cmpMetadataByTagTest_112, TestComparison_Equal_112) {
    // Creating mock objects
    Exiv2::MockMetadatum lhs;
    Exiv2::MockMetadatum rhs;

    // Setting up mock expectations
    EXPECT_CALL(lhs, tag())
        .WillOnce(testing::Return(1));  // lhs.tag() returns 1
    EXPECT_CALL(rhs, tag())
        .WillOnce(testing::Return(1));  // rhs.tag() returns 1

    // Testing if lhs.tag() < rhs.tag()
    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));  // Expects false since 1 is not less than 1
}

TEST_F(cmpMetadataByTagTest_112, TestComparison_GreaterThan_112) {
    // Creating mock objects
    Exiv2::MockMetadatum lhs;
    Exiv2::MockMetadatum rhs;

    // Setting up mock expectations
    EXPECT_CALL(lhs, tag())
        .WillOnce(testing::Return(2));  // lhs.tag() returns 2
    EXPECT_CALL(rhs, tag())
        .WillOnce(testing::Return(1));  // rhs.tag() returns 1

    // Testing if lhs.tag() < rhs.tag()
    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));  // Expects false since 2 is not less than 1
}

TEST_F(cmpMetadataByTagTest_112, TestBoundaryComparison_112) {
    // Creating mock objects
    Exiv2::MockMetadatum lhs;
    Exiv2::MockMetadatum rhs;

    // Setting up mock expectations for boundary values
    EXPECT_CALL(lhs, tag())
        .WillOnce(testing::Return(0));  // lhs.tag() returns 0 (lower boundary)
    EXPECT_CALL(rhs, tag())
        .WillOnce(testing::Return(0));  // rhs.tag() returns 0 (equal boundary)

    // Testing boundary comparison
    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));  // Expects false since 0 is not less than 0
}