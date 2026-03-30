#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1343 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



TEST_F(ExifKeyTest_1343, TagReturnsCorrectValue_1343) {

    ExifKey key(0x9003, "ExifIFD");

    EXPECT_EQ(key.tag(), 0x9003);

}



TEST_F(ExifKeyTest_1343, ConstructorWithUint16AndGroupName_1343) {

    ExifKey key(0x9003, "ExifIFD");

    EXPECT_EQ(key.groupName(), "ExifIFD");

}



TEST_F(ExifKeyTest_1343, CopyConstructorPreservesTag_1343) {

    ExifKey original(0x9003, "ExifIFD");

    ExifKey copy(original);

    EXPECT_EQ(copy.tag(), 0x9003);

}



TEST_F(ExifKeyTest_1343, AssignmentOperatorPreservesTag_1343) {

    ExifKey original(0x9003, "ExifIFD");

    ExifKey copy;

    copy = original;

    EXPECT_EQ(copy.tag(), 0x9003);

}



TEST_F(ExifKeyTest_1343, DefaultConstructorInitializesTagToZero_1343) {

    ExifKey key;

    EXPECT_EQ(key.tag(), 0);

}



TEST_F(ExifKeyTest_1343, BoundaryConditionMaxUint16Value_1343) {

    ExifKey key(std::numeric_limits<uint16_t>::max(), "ExifIFD");

    EXPECT_EQ(key.tag(), std::numeric_limits<uint16_t>::max());

}



TEST_F(ExifKeyTest_1343, BoundaryConditionMinUint16Value_1343) {

    ExifKey key(std::numeric_limits<uint16_t>::min(), "ExifIFD");

    EXPECT_EQ(key.tag(), std::numeric_limits<uint16_t>::min());

}



TEST_F(ExifKeyTest_1343, ConstructorWithStringAndTagInfo_1343) {

    TagInfo tagInfo = {0x9003, "SampleTag", "SShort", 2, "Sample Description"};

    ExifKey key(tagInfo);

    EXPECT_EQ(key.tag(), 0x9003);

}



TEST_F(ExifKeyTest_1343, ConstructorWithStringKey_1343) {

    // Assuming the string key can be parsed to extract the tag and other information

    ExifKey key("Exif.ExifIFD.Artist");

    // This test assumes that the tag value is correctly extracted from the string

    EXPECT_EQ(key.groupName(), "ExifIFD");

}



// Note: Additional tests for exceptional cases would require more information about how the class handles invalid input.

```


