#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "casiomn_int.cpp"



using namespace Exiv2::Internal;



class CasioMakerNoteTest_1821 : public ::testing::Test {

protected:

    CasioMakerNote casioMakerNote;

    std::ostringstream oss;

    Value mockValue;



    void setUpMockValue(const std::vector<long>& values) {

        EXPECT_CALL(mockValue, size()).WillRepeatedly(::testing::Return(values.size()));

        for (size_t i = 0; i < values.size(); ++i) {

            EXPECT_CALL(mockValue, toInt64(i)).WillRepeatedly(::testing::Return(values[i]));

        }

    }

};



TEST_F(CasioMakerNoteTest_1821, NormalOperationWith12Values_1821) {

    std::vector<long> values = {50, 48, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("2050:12:34 56:57:58:59", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, NormalOperationWith10Values_1821) {

    std::vector<long> values = {50, 48, 51, 52, 53, 54, 55, 56, 57, 58};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("2050:12:34 56:57:58", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, BoundaryConditionWithLessThan10Values_1821) {

    std::vector<long> values = {1, 2, 3};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("3", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, BoundaryConditionWithExactly10ValuesStartingWith70_1821) {

    std::vector<long> values = {70, 48, 51, 52, 53, 54, 55, 56, 57, 58};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("1970:12:34 56:57:58", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, BoundaryConditionWithExactly10ValuesStartingWithLessThan70_1821) {

    std::vector<long> values = {50, 48, 51, 52, 53, 54, 55, 56, 57, 58};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("2050:12:34 56:57:58", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, HandlingOfZeroValues_1821) {

    std::vector<long> values = {50, 48, 0, 52, 53, 54, 55, 56, 57, 58};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("2050:12:34 56:57:58", oss.str());

}



TEST_F(CasioMakerNoteTest_1821, HandlingOfAllZeroValues_1821) {

    std::vector<long> values = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    setUpMockValue(values);

    casioMakerNote.print0x0015(oss, mockValue, nullptr);

    EXPECT_EQ("0", oss.str());

}
