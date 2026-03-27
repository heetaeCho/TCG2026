#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/matroskavideo.hpp"



namespace {



using namespace Exiv2::Internal;



class MatroskaTagTest_93 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(MatroskaTagTest_93, DumpOutputsCorrectFormat_93) {

    MatroskaTag tag(0x1A45DFA3, "EBML", matroskaTypeEnum::ElementType, matroskaProcessEnum::ReadAndWrite);

    tag.dump(oss);

    EXPECT_EQ(" MatroskaTag  id: [0x1a45dfa3] label:[EBML] type:[ElementType] process :[ReadAndWrite]\n", oss.str());

}



TEST_F(MatroskaTagTest_93, ConstructorWithFullParametersSetsValuesCorrectly_93) {

    MatroskaTag tag(0x4286, "Duration", matroskaTypeEnum::FloatType, matroskaProcessEnum::Read);

    EXPECT_EQ(tag._id, 0x4286);

    EXPECT_EQ(tag._label, "Duration");

    EXPECT_EQ(tag._type, matroskaTypeEnum::FloatType);

    EXPECT_EQ(tag._process, matroskaProcessEnum::Read);

}



TEST_F(MatroskaTagTest_93, ConstructorWithMinimalParametersSetsDefaultValues_93) {

    MatroskaTag tag(0x4286, "Duration");

    EXPECT_EQ(tag._id, 0x4286);

    EXPECT_EQ(tag._label, "Duration");

    EXPECT_EQ(tag._type, matroskaTypeEnum::UndefinedType);

    EXPECT_EQ(tag._process, matroskaProcessEnum::Undefined);

}



TEST_F(MatroskaTagTest_93, EqualityOperatorMatchesId_93) {

    MatroskaTag tag(0x1A45DFA3, "EBML");

    EXPECT_TRUE(tag == 0x1A45DFA3);

    EXPECT_FALSE(tag == 0x4286);

}



TEST_F(MatroskaTagTest_93, IsSkippedReturnsFalseByDefault_93) {

    MatroskaTag tag(0x1A45DFA3, "EBML");

    EXPECT_FALSE(tag.isSkipped());

}



TEST_F(MatroskaTagTest_93, IsCompositeReturnsFalseByDefault_93) {

    MatroskaTag tag(0x1A45DFA3, "EBML");

    EXPECT_FALSE(tag.isComposite());

}



}  // namespace
