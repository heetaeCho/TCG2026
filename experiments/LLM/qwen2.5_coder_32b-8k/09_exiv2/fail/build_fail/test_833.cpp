#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class XmpValueTest_833 : public ::testing::Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_833, SizeReturnsCorrectSize_833) {

    std::ostringstream os;

    os << "SampleXMPData";

    EXPECT_CALL(xmpValue, write(_)).WillOnce([&os](std::ostream &os_) { os_.write(os.str().c_str(), os.str().size()); return os_; });

    EXPECT_EQ(xmpValue.size(), os.str().size());

}



TEST_F(XmpValueTest_833, SizeHandlesEmptyData_833) {

    std::ostringstream os;

    os << "";

    EXPECT_CALL(xmpValue, write(_)).WillOnce([&os](std::ostream &os_) { os_.write(os.str().c_str(), os.str().size()); return os_; });

    EXPECT_EQ(xmpValue.size(), 0);

}



TEST_F(XmpValueTest_833, SizeHandlesLargeData_833) {

    std::string largeData(1000000, 'a');

    std::ostringstream os;

    os << largeData;

    EXPECT_CALL(xmpValue, write(_)).WillOnce([&os](std::ostream &os_) { os_.write(os.str().c_str(), os.str().size()); return os_; });

    EXPECT_EQ(xmpValue.size(), os.str().size());

}



TEST_F(XmpValueTest_833, XmpArrayTypeDefault_833) {

    EXPECT_EQ(xmpValue.xmpArrayType(), xaNone);

}



TEST_F(XmpValueTest_833, XmpStructDefault_833) {

    EXPECT_EQ(xmpValue.xmpStruct(), xsNone);

}



TEST_F(XmpValueTest_833, SetXmpArrayTypeAndGet_833) {

    xmpValue.setXmpArrayType(xaOrdered);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaOrdered);

}



TEST_F(XmpValueTest_833, SetXmpStructAndGet_833) {

    xmpValue.setXmpStruct(xsAltText);

    EXPECT_EQ(xmpValue.xmpStruct(), xsAltText);

}
