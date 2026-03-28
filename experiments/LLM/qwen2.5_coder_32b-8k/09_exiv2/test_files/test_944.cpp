#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <string>

#include "TestProjects/exiv2/src/canonmn_int.cpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_944 : public ::testing::Test {

protected:

    CanonMakerNote makerNote;

    std::ostringstream os;

};



TEST_F(CanonMakerNoteTest_944, Print0x000a_NormalOperation_944) {

    Exiv2::Value value;

    value.setValue(Exiv2::TypeId::unsignedLong, "12345678");

    makerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "00bc03038");

}



TEST_F(CanonMakerNoteTest_944, Print0x000a_BoundaryCondition_Zero_944) {

    Exiv2::Value value;

    value.setValue(Exiv2::TypeId::unsignedLong, "0");

    makerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "000000000");

}



TEST_F(CanonMakerNoteTest_944, Print0x000a_BoundaryCondition_MaxUint32_944) {

    Exiv2::Value value;

    value.setValue(Exiv2::TypeId::unsignedLong, "4294967295");

    makerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "ffffffffff");

}



TEST_F(CanonMakerNoteTest_944, Print0x000a_ErrorCase_NonNumericString_944) {

    Exiv2::Value value;

    value.setValue(Exiv2::TypeId::unsignedLong, "abcdefg");

    EXPECT_THROW(makerNote.print0x000a(os, value, nullptr), std::invalid_argument);

}



TEST_F(CanonMakerNoteTest_944, Print0x000a_ErrorCase_EmptyString_944) {

    Exiv2::Value value;

    value.setValue(Exiv2::TypeId::unsignedLong, "");

    EXPECT_THROW(makerNote.print0x000a(os, value, nullptr), std::invalid_argument);

}
