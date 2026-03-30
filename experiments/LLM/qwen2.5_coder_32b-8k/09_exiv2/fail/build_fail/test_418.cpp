#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon2MakerNoteTest_418 : public ::testing::Test {

protected:

    Nikon2MakerNote nikon2MakerNote;

};



TEST_F(Nikon2MakerNoteTest_418, TagList_ReturnsStaticData_418) {

    const auto& tagList = Nikon2MakerNote::tagList();

    EXPECT_TRUE(tagList != nullptr);

}



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(std::string, toString, (), (const, override));

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD0(count, size_t());

};



TEST_F(Nikon2MakerNoteTest_418, Print0x000a_NormalOperation_418) {

    std::ostringstream os;

    MockValue mockValue;

    MockExifData mockExifData;



    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("Mocked Value"));



    nikon2MakerNote.print0x000a(os, mockValue, &mockExifData);



    EXPECT_EQ(os.str(), "Mocked Value");

}



TEST_F(Nikon2MakerNoteTest_418, Print0x000a_ValueEmptyString_418) {

    std::ostringstream os;

    MockValue mockValue;

    MockExifData mockExifData;



    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return(""));



    nikon2MakerNote.print0x000a(os, mockValue, &mockExifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(Nikon2MakerNoteTest_418, Print0x000a_ExifDataNullptr_418) {

    std::ostringstream os;

    MockValue mockValue;



    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("Mocked Value"));



    nikon2MakerNote.print0x000a(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Mocked Value");

}
