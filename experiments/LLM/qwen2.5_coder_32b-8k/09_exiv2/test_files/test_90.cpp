#include <gtest/gtest.h>

#include <exiv2/matroskavideo.hpp>



using namespace Exiv2::Internal;



// Test fixture for MatroskaTag tests

class MatroskaTagTest_90 : public ::testing::Test {

protected:

    MatroskaTag tag1;

    MatroskaTag tag2;



    MatroskaTagTest_90()

        : tag1(1, "Label1", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined),

          tag2(2, "Label2") {}

};



// Test if the operator== returns true when ids match

TEST_F(MatroskaTagTest_90, OperatorEquals_ReturnsTrueForSameId_90) {

    EXPECT_TRUE(tag1 == 1);

}



// Test if the operator== returns false when ids do not match

TEST_F(MatroskaTagTest_90, OperatorEquals_ReturnsFalseForDifferentId_90) {

    EXPECT_FALSE(tag1 == 2);

}



// Test boundary condition with max uint64_t value

TEST_F(MatroskaTagTest_90, OperatorEquals_BoundaryConditionWithMaxUint64_90) {

    MatroskaTag tag_max(UINT64_MAX, "LabelMax");

    EXPECT_TRUE(tag_max == UINT64_MAX);

}



// Test boundary condition with min uint64_t value

TEST_F(MatroskaTagTest_90, OperatorEquals_BoundaryConditionWithMinUint64_90) {

    MatroskaTag tag_min(0, "LabelMin");

    EXPECT_TRUE(tag_min == 0);

}



// Test if isSkipped returns false by default (since it's not specified in the constructor)

TEST_F(MatroskaTagTest_90, IsSkipped_ReturnsFalseByDefault_90) {

    EXPECT_FALSE(tag1.isSkipped());

}



// Test if isComposite returns false by default (since it's not specified in the constructor)

TEST_F(MatroskaTagTest_90, IsComposite_ReturnsFalseByDefault_90) {

    EXPECT_FALSE(tag1.isComposite());

}



// Test if dump outputs something to the stream

TEST_F(MatroskaTagTest_90, Dump_OutputsToStream_90) {

    std::ostringstream os;

    tag1.dump(os);

    EXPECT_FALSE(os.str().empty());

}
