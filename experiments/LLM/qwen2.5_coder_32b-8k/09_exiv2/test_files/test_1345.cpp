#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {



class ExifKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(ExifKeyTest_1345, DefaultConstructorIfdIdNotSet_1345) {

    ExifKey key;

    EXPECT_EQ(key.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifKeyTest_1345, StringConstructorIfdIdNotSet_1345) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifKeyTest_1345, TagGroupConstructorIfdIdNotSet_1345) {

    ExifKey key(0x927C, "GPSInfo");

    EXPECT_EQ(key.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifKeyTest_1345, CopyConstructorPreservesIfdId_1345) {

    ExifKey original(0x927C, "GPSInfo");

    ExifKey copy = original;

    EXPECT_EQ(copy.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifKeyTest_1345, AssignmentOperatorPreservesIfdId_1345) {

    ExifKey original(0x927C, "GPSInfo");

    ExifKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.ifdId(), IfdId::ifdIdNotSet);

}



TEST_F(ExifKeyTest_1345, SetIdxDoesNotAffectIfdId_1345) {

    ExifKey key;

    key.setIdx(5);

    EXPECT_EQ(key.ifdId(), IfdId::ifdIdNotSet);

}



}  // namespace Exiv2
