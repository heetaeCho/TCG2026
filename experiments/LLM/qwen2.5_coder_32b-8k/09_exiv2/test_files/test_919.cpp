#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



// Mocking Value and ExifData for testing purposes

class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeName, std::string());

    MOCK_CONST_METHOD0(toString, std::string());

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD1(findKey, const Exiv2::Exifdatum&(const Exiv2::ExifKey&));

};



TEST_F(CanonMakerNoteTest_919, TagListFcd3_ReturnsConstantValue_919) {

    auto result = CanonMakerNote::tagListFcd3();

    EXPECT_EQ(result, CanonMakerNote::tagInfoFcd3_);

}



TEST_F(CanonMakerNoteTest_919, PrintFiFileNumber_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    MockExifData mockMetadata;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintFocalLength_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    MockExifData mockMetadata;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, Print0x0008_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, Print0x000a_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, Print0x000c_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::print0x000c(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintCs0x0002_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintCsLensType_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    MockExifData mockMetadata;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintCsLens_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintLe0x0000_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0001_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0002_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0003_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0009_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x000c_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x000d_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x000e_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x000e(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0013_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0015_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0016_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0017_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintSi0x0018_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}



TEST_F(CanonMakerNoteTest_919, PrintFiFocusDistance_ValidInput_ReturnsStream_919) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("MockedValue"));



    auto result = CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_EQ(result.str(), "MockedValue");

}
