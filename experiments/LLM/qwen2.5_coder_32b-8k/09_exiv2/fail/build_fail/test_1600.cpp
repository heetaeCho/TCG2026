#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::StrEq;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

};



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_NormalOperationPositiveValues_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::signedLong, std::vector<int64_t>{1500, 2500});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("A/B: B1.50, G/M: M2.50"));

}



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_NormalOperationNegativeValues_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::signedLong, std::vector<int64_t>{-1500, -2500});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("A/B: A1.50, G/M: G2.50"));

}



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_NormalOperationZeroValues_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::signedLong, std::vector<int64_t>{0, 0});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("A/B: 0, G/M: 0"));

}



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_BoundaryConditionSingleValue_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::signedLong, std::vector<int64_t>{1500});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("()"));

}



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_BoundaryConditionThreeValues_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::signedLong, std::vector<int64_t>{1500, 2500, 3500});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("()"));

}



TEST_F(SonyMakerNoteTest_1600, PrintWBShiftABGMPrecise_ErrorCaseWrongType_1600) {

    Exiv2::Value value;

    value.setValue(Exiv2::ValueType::unsignedLong, std::vector<uint64_t>{1500, 2500});

    std::ostringstream os;

    sonyMakerNote.printWBShiftABGMPrecise(os, value, nullptr);

    EXPECT_THAT(os.str(), StrEq("()"));

}
