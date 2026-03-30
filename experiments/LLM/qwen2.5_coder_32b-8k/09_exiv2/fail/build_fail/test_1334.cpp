#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



// Test fixture for ExifKey tests

class ExifKeyTest_1334 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Test normal operation of the copy assignment operator

TEST_F(ExifKeyTest_1334, CopyAssignmentOperator_NormalOperation_1334) {

    ExifKey key1("some_key");

    ExifKey key2;

    key2 = key1;



    EXPECT_EQ(key1.key(), key2.key());

}



// Test boundary condition with an empty string

TEST_F(ExifKeyTest_1334, Constructor_EmptyString_1334) {

    ExifKey key("");

    EXPECT_TRUE(key.key().empty());

}



// Test normal operation of the constructor with uint16_t and groupName

TEST_F(ExifKeyTest_1334, Constructor_Uint16tAndGroupName_NormalOperation_1334) {

    ExifKey key(0x123, "IFD0");

    EXPECT_EQ(key.tag(), 0x123);

    EXPECT_EQ(key.groupName(), "IFD0");

}



// Test normal operation of the constructor with TagInfo

TEST_F(ExifKeyTest_1334, Constructor_TagInfo_NormalOperation_1334) {

    TagInfo tagInfo = {0x123, "TagLabel", "TagDesc", ifdIdNotSet};

    ExifKey key(tagInfo);

    EXPECT_EQ(key.tag(), 0x123);

}



// Test setting and getting idx

TEST_F(ExifKeyTest_1334, SetIdx_NormalOperation_1334) {

    ExifKey key("some_key");

    key.setIdx(5);

    EXPECT_EQ(key.idx(), 5);

}



// Test exceptional case for setIdx with negative value (if applicable)

// Assuming idx should be non-negative

TEST_F(ExifKeyTest_1334, SetIdx_NegativeValue_ExceptionalCase_1334) {

    ExifKey key("some_key");

    EXPECT_THROW(key.setIdx(-1), std::exception);

}



// Test getting various string properties

TEST_F(ExifKeyTest_1334, GetStringProperties_NormalOperation_1334) {

    TagInfo tagInfo = {0x123, "TagLabel", "TagDesc", ifdIdNotSet};

    ExifKey key(tagInfo);

    EXPECT_EQ(key.tagName(), "TagLabel");

    EXPECT_EQ(key.tagLabel(), "TagLabel");

    EXPECT_EQ(key.tagDesc(), "TagDesc");

}



// Test getting IfdId

TEST_F(ExifKeyTest_1334, GetIfdId_NormalOperation_1334) {

    TagInfo tagInfo = {0x123, "TagLabel", "TagDesc", ifdIdNotSet};

    ExifKey key(tagInfo);

    EXPECT_EQ(key.ifdId(), IfdId::ifdIdNotSet);

}



// Test cloning functionality

TEST_F(ExifKeyTest_1334, Clone_NormalOperation_1334) {

    ExifKey key("some_key");

    auto clonedKey = key.clone();

    EXPECT_NE(clonedKey.get(), nullptr);

    EXPECT_EQ(key.key(), clonedKey->key());

}
