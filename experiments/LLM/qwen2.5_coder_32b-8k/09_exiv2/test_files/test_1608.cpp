#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/sonymn_int.cpp"



using namespace Exiv2::Internal;



// Mock Value class to simulate behavior needed for testing

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const));

    MOCK_METHOD(std::string, toString, (size_t), (const));

};



TEST_F(SonyMakerNoteTest_1608, PrintImageSize_NormalOperation_1608) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedLong));

    EXPECT_CALL(mockValue, toString(1)).WillOnce(::testing::Return("1920"));

    EXPECT_CALL(mockValue, toString(0)).WillOnce(::testing::Return("1080"));



    SonyMakerNote sonyMakerNote;

    sonyMakerNote.printImageSize(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "1920 x 1080");

}



TEST_F(SonyMakerNoteTest_1608, PrintImageSize_BoundaryCountZero_1608) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(0));



    SonyMakerNote sonyMakerNote;

    sonyMakerNote.printImageSize(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(MockValue())");

}



TEST_F(SonyMakerNoteTest_1608, PrintImageSize_BoundaryCountThree_1608) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(3));



    SonyMakerNote sonyMakerNote;

    sonyMakerNote.printImageSize(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(MockValue())");

}



TEST_F(SonyMakerNoteTest_1608, PrintImageSize_WrongTypeId_1608) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(short));



    SonyMakerNote sonyMakerNote;

    sonyMakerNote.printImageSize(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(MockValue())");

}



TEST_F(SonyMakerNoteTest_1608, PrintImageSize_ExceptionalHandling_1608) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Throw(std::runtime_error("count error")));



    SonyMakerNote sonyMakerNote;

    sonyMakerNote.printImageSize(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(MockValue())");

}
