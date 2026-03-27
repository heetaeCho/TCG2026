#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1346 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state here if needed.

    }



    void TearDown() override {

        // Cleanup any common state here if needed.

    }

};



TEST_F(ExifKeyTest_1346, DefaultConstructorIdx_1346) {

    ExifKey key;

    EXPECT_EQ(key.idx(), 0);

}



TEST_F(ExifKeyTest_1346, StringConstructorIdx_1346) {

    ExifKey key("example");

    EXPECT_EQ(key.idx(), 0); // Assuming default idx is 0

}



TEST_F(ExifKeyTest_1346, TagInfoConstructorIdx_1346) {

    TagInfo ti;

    ExifKey key(ti);

    EXPECT_EQ(key.idx(), 0); // Assuming default idx is 0

}



TEST_F(ExifKeyTest_1346, CopyConstructorIdx_1346) {

    ExifKey original("example");

    ExifKey copy(original);

    EXPECT_EQ(copy.idx(), original.idx());

}



TEST_F(ExifKeyTest_1346, SetIdxChangesIdx_1346) {

    ExifKey key;

    key.setIdx(5);

    EXPECT_EQ(key.idx(), 5);

}



TEST_F(ExifKeyTest_1346, BoundaryConditionSetIdx_1346) {

    ExifKey key;

    key.setIdx(std::numeric_limits<int>::max());

    EXPECT_EQ(key.idx(), std::numeric_limits<int>::max());



    key.setIdx(std::numeric_limits<int>::min());

    EXPECT_EQ(key.idx(), std::numeric_limits<int>::min());

}



TEST_F(ExifKeyTest_1346, TagMethodReturnsExpected_1346) {

    ExifKey key;

    EXPECT_EQ(key.tag(), 0); // Assuming default tag is 0

}



TEST_F(ExifKeyTest_1346, GroupNameMethodReturnsExpected_1346) {

    ExifKey key("example");

    EXPECT_EQ(key.groupName(), ""); // Assuming default groupName is empty string

}
