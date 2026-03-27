#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



namespace {



class ImageTest_1063 : public ::testing::Test {

protected:

    Exiv2::Image image{Exiv2::ImageType::jpeg, 0x0FFF, std::make_unique<Exiv2::BasicIo>()};

};



TEST_F(ImageTest_1063, TypeNameForUnsignedByte_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::unsignedByte), "BYTE");

}



TEST_F(ImageTest_1063, TypeNameForAsciiString_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::asciiString), "ASCII");

}



TEST_F(ImageTest_1063, TypeNameForUnsignedShort_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::unsignedShort), "SHORT");

}



TEST_F(ImageTest_1063, TypeNameForUnsignedLong_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::unsignedLong), "LONG");

}



TEST_F(ImageTest_1063, TypeNameForUnsignedRational_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::unsignedRational), "RATIONAL");

}



TEST_F(ImageTest_1063, TypeNameForSignedByte_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::signedByte), "SBYTE");

}



TEST_F(ImageTest_1063, TypeNameForUndefined_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::undefined), "UNDEFINED");

}



TEST_F(ImageTest_1063, TypeNameForSignedShort_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::signedShort), "SSHORT");

}



TEST_F(ImageTest_1063, TypeNameForSignedLong_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::signedLong), "SLONG");

}



TEST_F(ImageTest_1063, TypeNameForSignedRational_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::signedRational), "SRATIONAL");

}



TEST_F(ImageTest_1063, TypeNameForTiffFloat_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::tiffFloat), "FLOAT");

}



TEST_F(ImageTest_1063, TypeNameForTiffDouble_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::tiffDouble), "DOUBLE");

}



TEST_F(ImageTest_1063, TypeNameForTiffIfd_1063) {

    EXPECT_STREQ(image.typeName(Exiv2::tiffIfd), "IFD");

}



TEST_F(ImageTest_1063, TypeNameForUnknownType_1063) {

    EXPECT_STREQ(image.typeName(static_cast<Exiv2::TypeId>(99)), "unknown");

}



}  // namespace
