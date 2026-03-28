#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/sonymn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class GetMetaVersionTest_1586 : public ::testing::Test {

protected:

    ExifData metadata;

};



TEST_F(GetMetaVersionTest_1586, NormalOperation_1586) {

    std::string val;

    metadata.add(ExifKey("Exif.SonySInfo1.MetaVersion"), new AsciiValue("1.2"));

    EXPECT_TRUE(getMetaVersion(&metadata, val));

    EXPECT_EQ(val, "1.2");

}



TEST_F(GetMetaVersionTest_1586, BoundaryCondition_EmptyString_1586) {

    std::string val;

    metadata.add(ExifKey("Exif.SonySInfo1.MetaVersion"), new AsciiValue(""));

    EXPECT_TRUE(getMetaVersion(&metadata, val));

    EXPECT_EQ(val, "");

}



TEST_F(GetMetaVersionTest_1586, BoundaryCondition_NoKeyFound_1586) {

    std::string val;

    EXPECT_FALSE(getMetaVersion(&metadata, val));

    EXPECT_EQ(val, "");

}



TEST_F(GetMetaVersionTest_1586, ExceptionalCase_WrongType_1586) {

    std::string val;

    metadata.add(ExifKey("Exif.SonySInfo1.MetaVersion"), new DataValue<unsigned short>(123));

    EXPECT_FALSE(getMetaVersion(&metadata, val));

    EXPECT_EQ(val, "");

}
