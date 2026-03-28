#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"



using namespace Exiv2::Internal;



class MatroskaTagTest_92 : public ::testing::Test {

protected:

    MatroskaTag tag1;

    MatroskaTag tag2;

    MatroskaTag compositeTag;



    MatroskaTagTest_92()

        : tag1(1, "Tag1"),

          tag2(2, "Tag2", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip),

          compositeTag(3, "CompositeTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Composite) {}

};



TEST_F(MatroskaTagTest_92, Constructor_DefaultValues_92) {

    EXPECT_EQ(tag1._id, 1);

    EXPECT_EQ(tag1._label, "Tag1");

    EXPECT_EQ(tag1._type, matroskaTypeEnum::UndefinedType);

    EXPECT_EQ(tag1._process, matroskaProcessEnum::Undefined);



    EXPECT_EQ(tag2._id, 2);

    EXPECT_EQ(tag2._label, "Tag2");

    EXPECT_EQ(tag2._type, matroskaTypeEnum::UndefinedType);

    EXPECT_EQ(tag2._process, matroskaProcessEnum::Skip);

}



TEST_F(MatroskaTagTest_92, Constructor_CustomValues_92) {

    EXPECT_EQ(compositeTag._id, 3);

    EXPECT_EQ(compositeTag._label, "CompositeTag");

    EXPECT_EQ(compositeTag._type, matroskaTypeEnum::UndefinedType);

    EXPECT_EQ(compositeTag._process, matroskaProcessEnum::Composite);

}



TEST_F(MatroskaTagTest_92, OperatorEquals_IdMatch_92) {

    EXPECT_TRUE(tag1 == 1);

    EXPECT_FALSE(tag1 == 2);

}



TEST_F(MatroskaTagTest_92, IsSkipped_NotSkipped_92) {

    EXPECT_FALSE(tag1.isSkipped());

}



TEST_F(MatroskaTagTest_92, IsSkipped_Skipped_92) {

    EXPECT_TRUE(tag2.isSkipped());

}



TEST_F(MatroskaTagTest_92, IsComposite_NotComposite_92) {

    EXPECT_FALSE(tag1.isComposite());

}



TEST_F(MatroskaTagTest_92, IsComposite_Composite_92) {

    EXPECT_TRUE(compositeTag.isComposite());

}
