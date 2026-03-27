#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "convert.cpp"



using namespace Exiv2;

using testing::_;

using testing::Return;

using testing::StrEq;



class ConverterTest : public ::testing::Test {

protected:

    ExifData exifData_;

    XmpData xmpData_;

    Converter converter_{exifData_, xmpData_};

};



TEST_F(ConverterTest, CnvXmpVersion_NormalOperation_1847) {

    // Arrange

    std::string from = "xmp:Version";

    std::string to = "Exif.Image.XMPToolkit";

    std::string value = "\x30\x32\x32\x30";  // Example value as char array



    Xmpdatum xmpDatum(from.c_str(), new Value(1));

    xmpDatum.setValue(value.data(), value.size());



    EXPECT_CALL(xmpData_, findKey(StrEq(from)))

        .WillOnce(Return(&xmpDatum));



    EXPECT_TRUE(converter_.prepareExifTarget(to.c_str()));



    // Act

    converter_.cnvXmpVersion(from.c_str(), to.c_str());



    // Assert

    ASSERT_EQ(exifData_[to].toString(), "48 50 50 48");

}



TEST_F(ConverterTest, CnvXmpVersion_KeyNotFound_1847) {

    // Arrange

    std::string from = "xmp:MissingKey";

    std::string to = "Exif.Image.XMPToolkit";



    EXPECT_CALL(xmpData_, findKey(StrEq(from)))

        .WillOnce(Return(xmpData_.end()));



    // Act

    converter_.cnvXmpVersion(from.c_str(), to.c_str());



    // Assert

    ASSERT_EQ(exifData_.findKey(to.c_str()), exifData_.end());

}



TEST_F(ConverterTest, CnvXmpVersion_ValueTooShort_1847) {

    // Arrange

    std::string from = "xmp:Version";

    std::string to = "Exif.Image.XMPToolkit";

    std::string value = "\x30\x32";  // Value shorter than required



    Xmpdatum xmpDatum(from.c_str(), new Value(1));

    xmpDatum.setValue(value.data(), value.size());



    EXPECT_CALL(xmpData_, findKey(StrEq(from)))

        .WillOnce(Return(&xmpDatum));



    EXPECT_TRUE(converter_.prepareExifTarget(to.c_str()));



    // Act

    converter_.cnvXmpVersion(from.c_str(), to.c_str());



    // Assert

    ASSERT_EQ(exifData_.findKey(to.c_str()), exifData_.end());

}



TEST_F(ConverterTest, CnvXmpVersion_ValueNotOk_1847) {

    // Arrange

    std::string from = "xmp:Version";

    std::string to = "Exif.Image.XMPToolkit";

    std::string value = "\x30\x32\x32\x30";  // Example value as char array



    Xmpdatum xmpDatum(from.c_str(), new Value(1));

    xmpDatum.setValue(value.data(), value.size());

    const_cast<Value&>(xmpDatum.value()).ok_ = false;



    EXPECT_CALL(xmpData_, findKey(StrEq(from)))

        .WillOnce(Return(&xmpDatum));



    EXPECT_TRUE(converter_.prepareExifTarget(to.c_str()));



    // Act

    converter_.cnvXmpVersion(from.c_str(), to.c_str());



    // Assert

    ASSERT_EQ(exifData_.findKey(to.c_str()), exifData_.end());

}



TEST_F(ConverterTest, CnvXmpVersion_EraseEnabled_1847) {

    // Arrange

    std::string from = "xmp:Version";

    std::string to = "Exif.Image.XMPToolkit";

    std::string value = "\x30\x32\x32\x30";  // Example value as char array



    Xmpdatum xmpDatum(from.c_str(), new Value(1));

    xmpDatum.setValue(value.data(), value.size());



    EXPECT_CALL(xmpData_, findKey(StrEq(from)))

        .WillOnce(Return(&xmpDatum));



    EXPECT_TRUE(converter_.prepareExifTarget(to.c_str()));



    converter_.setErase(true);



    // Act

    converter_.cnvXmpVersion(from.c_str(), to.c_str());



    // Assert

    ASSERT_EQ(exifData_[to].toString(), "48 50 50 48");

    ASSERT_EQ(xmpData_.findKey(from.c_str()), xmpData_.end());

}
