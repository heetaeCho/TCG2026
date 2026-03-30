#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using testing::Eq;



class CanonMakerNoteTest_943 : public ::testing::Test {

protected:

    CanonMakerNote makerNote_;

};



TEST_F(CanonMakerNoteTest_943, Print0x0008_NormalOperation_LessThanFourCharacters_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("abc");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "(abc)");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_NormalOperation_ExactlyFourCharacters_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("abcd");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "abcd");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_NormalOperation_MoreThanFourCharacters_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("abcdefgh");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "abcd-efgh");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_BoundaryCondition_EmptyString_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "()");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_BoundaryCondition_SingleCharacter_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("a");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "(a)");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_BoundaryCondition_FourCharacters_943) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("1234");

    makerNote_.print0x0008(os, value, nullptr);

    EXPECT_EQ(os.str(), "1234");

}



TEST_F(CanonMakerNoteTest_943, Print0x0008_ExceptionalCase_NullValue_943) {

    std::ostringstream os;

    Exiv2::Value* value = nullptr;

    makerNote_.print0x0008(os, *value, nullptr); // This test assumes that dereferencing a null pointer is undefined behavior and should not be tested directly.

    // Since we cannot pass a null Value object to the function, this case is not testable under normal circumstances.

}
