#include <gtest/gtest.h>

#include <exiv2/matroskavideo.hpp>



using namespace Exiv2::Internal;



class MatroskaTagTest_91 : public ::testing::Test {

protected:

    MatroskaTag tagWithSkipProcess;

    MatroskaTag tagWithoutSkipProcess;



    MatroskaTagTest_91()

        : tagWithSkipProcess(1, "testLabel", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip),

          tagWithoutSkipProcess(2, "anotherLabel", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Process) {}

};



TEST_F(MatroskaTagTest_91, IsSkipped_ReturnsTrueForSkipProcess_91) {

    EXPECT_TRUE(tagWithSkipProcess.isSkipped());

}



TEST_F(MatroskaTagTest_91, IsSkipped_ReturnsFalseForNonSkipProcess_91) {

    EXPECT_FALSE(tagWithoutSkipProcess.isSkipped());

}



// Assuming isComposite() and dump() are part of the interface to be tested as well

class MatroskaTagCompositeTest_91 : public ::testing::Test {

protected:

    MatroskaTag compositeTag;

    MatroskaTag nonCompositeTag;



    MatroskaTagCompositeTest_91()

        : compositeTag(3, "compositeLabel", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Composite),

          nonCompositeTag(4, "nonCompositeLabel", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Process) {}

};



TEST_F(MatroskaTagCompositeTest_91, IsComposite_ReturnsTrueForCompositeProcess_91) {

    EXPECT_TRUE(compositeTag.isComposite());

}



TEST_F(MatroskaTagCompositeTest_91, IsComposite_ReturnsFalseForNonCompositeProcess_91) {

    EXPECT_FALSE(nonCompositeTag.isComposite());

}



class MatroskaTagEqualityTest_91 : public ::testing::Test {

protected:

    MatroskaTag tagWithId1;

    MatroskaTag tagWithDifferentId;



    MatroskaTagEqualityTest_91()

        : tagWithId1(5, "someLabel"),

          tagWithDifferentId(6, "anotherLabel") {}

};



TEST_F(MatroskaTagEqualityTest_91, OperatorEqual_ReturnsTrueForSameId_91) {

    EXPECT_TRUE(tagWithId1 == 5);

}



TEST_F(MatroskaTagEqualityTest_91, OperatorEqual_ReturnsFalseForDifferentId_91) {

    EXPECT_FALSE(tagWithId1 == tagWithDifferentId._id);

}
