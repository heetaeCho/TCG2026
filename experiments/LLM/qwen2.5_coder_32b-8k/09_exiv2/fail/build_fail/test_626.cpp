#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exv_mn_int.hpp>

#include <sstream>



using namespace Exiv2::Internal;

using testing::_;

using testing::Ref;



class PrintFujiFaceElementTypesTest_626 : public ::testing::Test {

protected:

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is needed, though not used in the function

};



TEST_F(PrintFujiFaceElementTypesTest_626, PutIncreasesCountAsciiString_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.read("123\0", 4);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "face 2 3");

}



TEST_F(PrintFujiFaceElementTypesTest_626, PutIncreasesCountUnsignedShort_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.read(reinterpret_cast<const byte*>(new uint16_t[3]{0, 1, 2}), 6);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "face 1 2");

}



TEST_F(PrintFujiFaceElementTypesTest_626, SingleElementAsciiString_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.read("1\0", 2);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "face");

}



TEST_F(PrintFujiFaceElementTypesTest_626, SingleElementUnsignedShort_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.read(reinterpret_cast<const byte*>(new uint16_t{0}), 2);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "face");

}



TEST_F(PrintFujiFaceElementTypesTest_626, EmptyAsciiString_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.read("", 1);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(PrintFujiFaceElementTypesTest_626, EmptyUnsignedShort_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.read(nullptr, 0);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "()");

}



TEST_F(PrintFujiFaceElementTypesTest_626, UnknownType_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::undefined);

    value.read(nullptr, 0);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "()");

}



TEST_F(PrintFujiFaceElementTypesTest_626, UnknownValueAsciiString_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.read("9\0", 2);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "(9)");

}



TEST_F(PrintFujiFaceElementTypesTest_626, UnknownValueUnsignedShort_626) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.read(reinterpret_cast<const byte*>(new uint16_t{9}), 2);



    printFujiFaceElementTypes(os, value, &exifData);



    EXPECT_EQ(os.str(), "(9)");

}
