#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const));

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(int64_t, toInt64, (), (const));

};



TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_ValidInput_ReturnsCorrectOutput_955) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(32));



    CanonMakerNote makerNote;

    makerNote.printSi0x0003(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "5.00");

}



TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_ZeroCount_ReturnsEmptyString_955) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(0));



    CanonMakerNote makerNote;

    makerNote.printSi0x0003(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_InvalidTypeId_ReturnsEmptyString_955) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::int8));



    CanonMakerNote makerNote;

    makerNote.printSi0x0003(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_NegativeValue_ReturnsCorrectOutput_955) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(-32));



    CanonMakerNote makerNote;

    makerNote.printSi0x0003(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "3.75");

}



TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_MaxShortValue_ReturnsCorrectOutput_955) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(std::numeric_limits<short>::max()));



    CanonMakerNote makerNote;

    makerNote.printSi0x0003(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "28.59");

}
