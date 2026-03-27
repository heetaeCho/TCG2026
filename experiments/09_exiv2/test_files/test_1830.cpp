#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "convert.cpp"



namespace Exiv2 {

    class MockExifData : public ExifData {};

    class MockIptcData : public IptcData {};

    class MockXmpData : public XmpData {};

}



using namespace testing;

using namespace Exiv2;



class ConverterTest_1830 : public Test {

protected:

    MockExifData mockExifData_;

    MockXmpData mockXmpData_;

    MockIptcData mockIptcData_;



    Converter converterWithExifAndXmp_{mockExifData_, mockXmpData_};

    Converter converterWithIptcAndXmp_{mockIptcData_, mockXmpData_, "charset"};

};



TEST_F(ConverterTest_1830, SetEraseDefaultTrue_1830) {

    converterWithExifAndXmp_.setErase();

    EXPECT_EQ(converterWithExifAndXmp_.erase(), true);

}



TEST_F(ConverterTest_1830, SetEraseFalse_1830) {

    converterWithExifAndXmp_.setErase(false);

    EXPECT_EQ(converterWithExifAndXmp_.erase(), false);

}



TEST_F(ConverterTest_1830, SetEraseTrueExplicit_1830) {

    converterWithExifAndXmp_.setErase(true);

    EXPECT_EQ(converterWithExifAndXmp_.erase(), true);

}
