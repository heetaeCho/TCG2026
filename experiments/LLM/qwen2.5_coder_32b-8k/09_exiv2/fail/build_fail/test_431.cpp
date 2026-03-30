#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using testing::_;

using testing::NiceMock;



class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeName, std::string());

    MOCK_CONST_METHOD0(toString, std::string());

    // Add other necessary mocks if needed

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD1(findKey, Exiv2::ExifData::const_iterator(const Exiv2::ExifKey&));

    // Add other necessary mocks if needed

};



TEST(Nikon3MakerNoteTest_431, TagListFl2_ReturnsExpectedValue_431) {

    const auto& tagList = Nikon3MakerNote::tagListFl2();

    EXPECT_EQ(tagList, Nikon3MakerNote::tagInfoFl2_);

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintIiIso_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintAf2AreaMode_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintLensId_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "group");

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintAperture_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printAperture(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintFocal_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printFocal(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintFocusDistance_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintExternalFlashData1Fl6_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintExternalFlashData2_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}



TEST(Nikon3MakerNotePrintFunctionsTest_431, PrintCameraExposureCompensation_NormalOperation_431) {

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, toString()).WillRepeatedly(testing::Return("mock value"));



    Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "mock value");

}
