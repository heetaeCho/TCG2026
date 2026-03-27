#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/sigmamn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;

using ::testing::Return;



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD0(count, size_t());

};



class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeName, std::string());

    MOCK_CONST_METHOD0(toString, std::string());

};



TEST(SigmaMakerNoteTest_1356, TagList_ReturnsExpectedTagInfo_1356) {

    auto tagInfo = SigmaMakerNote::tagList();

    EXPECT_NE(tagInfo, nullptr);

}



TEST(SigmaMakerNoteTest_1356, PrintStripLabel_CallsOstream_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    SigmaMakerNote::printStripLabel(oss, mockValue, &mockExifData);



    EXPECT_FALSE(oss.str().empty());

}



TEST(SigmaMakerNoteTest_1356, Print0x0008_CallsOstream_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    SigmaMakerNote::print0x0008(oss, mockValue, &mockExifData);



    EXPECT_FALSE(oss.str().empty());

}



TEST(SigmaMakerNoteTest_1356, Print0x0009_CallsOstream_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    SigmaMakerNote::print0x0009(oss, mockValue, &mockExifData);



    EXPECT_FALSE(oss.str().empty());

}



TEST(SigmaMakerNoteTest_1356, PrintStripLabel_ValueToStringCalled_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, toString()).Times(1);



    SigmaMakerNote::printStripLabel(oss, mockValue, &mockExifData);

}



TEST(SigmaMakerNoteTest_1356, Print0x0008_ValueToStringCalled_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, toString()).Times(1);



    SigmaMakerNote::print0x0008(oss, mockValue, &mockExifData);

}



TEST(SigmaMakerNoteTest_1356, Print0x0009_ValueToStringCalled_1356) {

    MockValue mockValue;

    MockExifData mockExifData;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, toString()).Times(1);



    SigmaMakerNote::print0x0009(oss, mockValue, &mockExifData);

}
