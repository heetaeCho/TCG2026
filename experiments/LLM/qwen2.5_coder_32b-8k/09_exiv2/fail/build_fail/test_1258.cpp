#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/properties.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpPropertiesTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

};



TEST_F(XmpPropertiesTest_NormalOperation_1258, PrintPropertyWithKnownKey_1258) {

    const std::string key = "Xmp.exif.ApertureValue";

    EXPECT_CALL(mockValue, count()).WillRepeatedly(::testing::Return(1));



    XmpProperties xmpProps;

    xmpProps.printProperty(os, key, mockValue);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(XmpPropertiesTest_NormalOperation_1258, PrintPropertyWithUnknownKey_1258) {

    const std::string key = "Xmp.unknown.Key";

    EXPECT_CALL(mockValue, count()).WillRepeatedly(::testing::Return(1));



    XmpProperties xmpProps;

    xmpProps.printProperty(os, key, mockValue);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(XmpPropertiesTest_BoundaryConditions_1258, PrintPropertyWithEmptyKey_1258) {

    const std::string key = "";

    EXPECT_CALL(mockValue, count()).WillRepeatedly(::testing::Return(1));



    XmpProperties xmpProps;

    xmpProps.printProperty(os, key, mockValue);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(XmpPropertiesTest_BoundaryConditions_1258, PrintPropertyWithValueCountZero_1258) {

    const std::string key = "Xmp.exif.ApertureValue";

    EXPECT_CALL(mockValue, count()).WillRepeatedly(::testing::Return(0));



    XmpProperties xmpProps;

    xmpProps.printProperty(os, key, mockValue);



    EXPECT_TRUE(os.str().empty());

}



TEST_F(XmpPropertiesTest_ExceptionalCases_1258, PrintPropertyWithInvalidValue_1258) {

    const std::string key = "Xmp.exif.ApertureValue";

    EXPECT_CALL(mockValue, count()).WillRepeatedly(::testing::Return(1));

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(false));



    XmpProperties xmpProps;

    xmpProps.printProperty(os, key, mockValue);



    EXPECT_TRUE(os.str().empty());

}
