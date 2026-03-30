#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1336 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if needed.

    }

};



TEST_F(ExifKeyTest_1336, KeyConstructionFromString_1336) {

    ExifKey exifKey("test_key");

    EXPECT_EQ(exifKey.key(), "test_key");

}



TEST_F(ExifKeyTest_1336, KeyCopyConstructor_1336) {

    ExifKey originalKey("original_key");

    ExifKey copiedKey(originalKey);

    EXPECT_EQ(copiedKey.key(), "original_key");

}



TEST_F(ExifKeyTest_1336, KeyAssignmentOperator_1336) {

    ExifKey key1("key1");

    ExifKey key2("key2");

    key2 = key1;

    EXPECT_EQ(key2.key(), "key1");

}



TEST_F(ExifKeyTest_1336, SetIdxAndGetIdx_1336) {

    ExifKey exifKey("test_key");

    exifKey.setIdx(42);

    EXPECT_EQ(exifKey.idx(), 42);

}



TEST_F(ExifKeyTest_1336, BoundaryCondition_EmptyStringKey_1336) {

    ExifKey exifKey("");

    EXPECT_EQ(exifKey.key(), "");

}



// Assuming tag and groupName are part of the key composition logic

// Since we don't have a direct way to set these in the public interface,

// this test assumes the constructor handling is correct.

TEST_F(ExifKeyTest_1336, ConstructorWithTagAndGroupName_1336) {

    ExifKey exifKey(0x9003, "ExifIFD");

    EXPECT_EQ(exifKey.tag(), 0x9003);

    EXPECT_EQ(exifKey.groupName(), "ExifIFD");

}



TEST_F(ExifKeyTest_1336, BoundaryCondition_ZeroTag_1336) {

    ExifKey exifKey(0, "ExifIFD");

    EXPECT_EQ(exifKey.tag(), 0);

}
