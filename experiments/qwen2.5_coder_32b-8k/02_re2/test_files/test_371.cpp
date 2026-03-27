#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassBuilderTest_371 : public ::testing::Test {

protected:

    void SetUp() override {

        cc = new CharClassBuilder();

    }



    void TearDown() override {

        delete cc;

    }



    CharClassBuilder* cc;

};



TEST_F(CharClassBuilderTest_371, AddRangeValidRange_371) {

    EXPECT_TRUE(cc->AddRange(10, 20));

}



TEST_F(CharClassBuilderTest_371, AddRangeInvalidRange_371) {

    EXPECT_FALSE(cc->AddRange(20, 10));

}



TEST_F(CharClassBuilderTest_371, AddCharClassNonEmpty_371) {

    CharClassBuilder cc2;

    cc2.AddRange(5, 15);

    cc->AddCharClass(&cc2);

    EXPECT_EQ(cc->size(), 1);

}



TEST_F(CharClassBuilderTest_371, AddCharClassEmpty_371) {

    CharClassBuilder cc2;

    cc->AddCharClass(&cc2);

    EXPECT_EQ(cc->size(), 0);

}



TEST_F(CharClassBuilderTest_371, ContainsInRange_371) {

    cc->AddRange(10, 20);

    EXPECT_TRUE(cc->Contains(15));

}



TEST_F(CharClassBuilderTest_371, ContainsOutOfRange_371) {

    cc->AddRange(10, 20);

    EXPECT_FALSE(cc->Contains(25));

}



TEST_F(CharClassBuilderTest_371, FoldsASCIIByDefault_371) {

    EXPECT_TRUE(cc->FoldsASCII());

}



TEST_F(CharClassBuilderTest_371, CopyPreservesRanges_371) {

    cc->AddRange(10, 20);

    CharClassBuilder* copy = cc->Copy();

    EXPECT_EQ(copy->size(), 1);

    delete copy;

}



TEST_F(CharClassBuilderTest_371, NegateInvertsRanges_371) {

    cc->AddRange(10, 20);

    cc->Negate();

    EXPECT_NE(cc->size(), 1); // After negation, size should change

}



TEST_F(CharClassBuilderTest_371, RemoveAboveRemovesCorrectly_371) {

    cc->AddRange(10, 20);

    cc->RemoveAbove(15);

    EXPECT_EQ(cc->size(), 1); // Range should be split or modified

}



TEST_F(CharClassBuilderTest_371, EmptyInitially_371) {

    EXPECT_TRUE(cc->empty());

}



TEST_F(CharClassBuilderTest_371, NotFullInitially_371) {

    EXPECT_FALSE(cc->full());

}
