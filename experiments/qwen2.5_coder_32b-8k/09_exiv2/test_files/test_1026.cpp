#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"



namespace Exiv2 {

    namespace Internal {

        class MockValue : public Value {

        public:

            MOCK_METHOD(const std::ostream&, write, (std::ostream& os), const);

            MOCK_METHOD(size_t, count, (), const);

        };

    }

}



using namespace ::testing;

using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintMinoltaSonyColorModeTest_1026 : public Test {

protected:

    NiceMock<MockValue> mockValue;

    ExifData metadata;

};



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Standard_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Standard"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Standard", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_VividColor_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Vivid Color"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Vivid Color", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Portrait_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Portrait"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Portrait", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Landscape_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Landscape"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Landscape", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Sunset_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Sunset"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Sunset", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_NightViewPortrait_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Night View/Portrait"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Night View/Portrait", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_BlackAndWhite_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Black & White"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Black & White", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_AdobeRGB_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "AdobeRGB"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("AdobeRGB", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Neutral_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Neutral"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Neutral", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Clear_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Clear"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Clear", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Deep_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Deep"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Deep", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_Light_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Light"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Light", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_NightView_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Night View"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Night View", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, NormalOperation_AutumnLeaves_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& { return os << "Autumn Leaves"; }));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("Autumn Leaves", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, BoundaryCondition_ZeroCount_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockValue, write(_)).Times(0);

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, BoundaryCondition_LargeCount_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1000000));

    EXPECT_CALL(mockValue, write(_)).Times(0);

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, &metadata);

    EXPECT_EQ("", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, ExceptionalCase_MetadataNull_1026) {

    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    

    std::ostringstream oss;

    printMinoltaSonyColorMode(oss, mockValue, nullptr);

    EXPECT_EQ("", oss.str());

}



TEST_F(PrintMinoltaSonyColorModeTest_1026, ExceptionalCase_ValueNull_1026) {

    std::ostringstream oss;

    Value* nullValue = nullptr;

    printMinoltaSonyColorMode(oss, *nullValue, &metadata);

    EXPECT_EQ("", oss.str());

}
