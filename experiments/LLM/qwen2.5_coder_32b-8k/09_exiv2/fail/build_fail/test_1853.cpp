#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class ConverterTest : public ::testing::Test {

protected:

    XmpData mockXmpData;

    Converter converter{mockXmpData};



    MOCK_METHOD(void, setXmpDataValue, (const std::string& key, const std::string& value));

};



TEST_F(ConverterTest_1853, WriteExifDigest_AddsNativeDigests_1853) {

    // Arrange

    EXPECT_CALL(mockXmpData, operator[]("Xmp.tiff.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumTiff));

    EXPECT_CALL(mockXmpData, operator[]("Xmp.exif.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumExif));



    // Act

    converter.writeExifDigest();



    // Assert - No explicit assert needed as the call expectations are checked by Google Mock.

}



TEST_F(ConverterTest_1853, WriteExifDigest_NoXmpToolkit_DoesNothing_1853) {

    // Arrange

    // No need to mock anything since we're expecting no calls when EXV_HAVE_XMP_TOOLKIT is not defined.



    // Act

    converter.writeExifDigest();



    // Assert - No explicit assert needed as the lack of call expectations are checked by Google Mock.

}



TEST_F(ConverterTest_1853, WriteExifDigest_HandlesEmptyXmpData_1853) {

    // Arrange

    EXPECT_CALL(mockXmpData, operator[]("Xmp.tiff.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumTiff));

    EXPECT_CALL(mockXmpData, operator[]("Xmp.exif.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumExif));



    // Act

    converter.writeExifDigest();



    // Assert - No explicit assert needed as the call expectations are checked by Google Mock.

}



TEST_F(ConverterTest_1853, WriteExifDigest_SetsCorrectKeys_1853) {

    // Arrange

    EXPECT_CALL(mockXmpData, operator[]("Xmp.tiff.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumTiff));

    EXPECT_CALL(mockXmpData, operator[]("Xmp.exif.NativeDigest")).WillOnce(testing::ReturnRef(mockXmpDatumExif));



    // Act

    converter.writeExifDigest();



    // Assert - No explicit assert needed as the call expectations are checked by Google Mock.

}
