#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    class ExifKey;

}



using namespace Exiv2;



class ExifKeyTest_1338 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ExifKeyTest_1338, GroupName_ReturnsCorrectValue_1338) {

    ExifKey key("some.group.tag");

    EXPECT_EQ(key.groupName(), "group");

}



TEST_F(ExifKeyTest_1338, GroupName_EmptyString_ReturnsEmptyGroup_1338) {

    ExifKey key("");

    EXPECT_EQ(key.groupName(), "");

}



TEST_F(ExifKeyTest_1338, GroupName_NoGroupSeparator_ReturnsFullStringAsGroupName_1338) {

    ExifKey key("fullstring");

    EXPECT_EQ(key.groupName(), "fullstring");

}



TEST_F(ExifKeyTest_1338, GroupName_MultipleDots_ReturnsFirstPartAsGroupName_1338) {

    ExifKey key("first.second.third.tag");

    EXPECT_EQ(key.groupName(), "first");

}
