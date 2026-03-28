#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class XmpdatumTest : public ::testing::Test {

protected:

    XmpKey mockXmpKey;

    Value* mockValue;

    Xmpdatum xmpDatum;



    XmpdatumTest() 

        : mockValue(new Value(TypeId::string)),

          xmpDatum(mockXmpKey, mockValue) {}

};



TEST_F(XmpdatumTest_1292, ToString_ReturnsEmptyStringWhenNoValue_1292) {

    // Arrange

    Xmpdatum xmpDatumWithoutValue(mockXmpKey, nullptr);



    // Act & Assert

    EXPECT_EQ(xmpDatumWithoutValue.toString(0), "");

}



TEST_F(XmpdatumTest_1292, ToString_ReturnsStringValueWhenValueSet_1292) {

    // Arrange

    std::string testString = "Test String";

    ON_CALL(*mockValue, toString()).WillByDefault(Return(testString));



    // Act & Assert

    EXPECT_EQ(xmpDatum.toString(0), testString);

}



TEST_F(XmpdatumTest_1292, ToString_BoundaryConditionWithLargeN_1292) {

    // Arrange

    std::string testString = "Test String";

    ON_CALL(*mockValue, toString()).WillByDefault(Return(testString));



    // Act & Assert

    EXPECT_EQ(xmpDatum.toString(1000000), "");

}



TEST_F(XmpdatumTest_1292, ToString_ExceptionalCaseWithNegativeN_1292) {

    // Arrange

    std::string testString = "Test String";

    ON_CALL(*mockValue, toString()).WillByDefault(Return(testString));



    // Act & Assert

    EXPECT_EQ(xmpDatum.toString(-1), "");

}



TEST_F(XmpdatumTest_1292, ToString_ReturnsSpecificNthValue_1292) {

    // Arrange

    std::string testString = "First Value";

    ON_CALL(*mockValue, toString(0)).WillByDefault(Return(testString));



    // Act & Assert

    EXPECT_EQ(xmpDatum.toString(0), testString);

}
