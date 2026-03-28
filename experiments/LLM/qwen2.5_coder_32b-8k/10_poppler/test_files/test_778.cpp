#include <gtest/gtest.h>

#include "Annot.h"

#include "PDFDoc.h"



class AnnotTest_778 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        mockDoc = new PDFDoc();

        annot = std::make_unique<Annot>(mockDoc, nullptr);

    }



    void TearDown() override {

        delete mockDoc;

    }

};



TEST_F(AnnotTest_778, GetDocReturnsCorrectPointer_778) {

    EXPECT_EQ(mockDoc, annot->getDoc());

}



TEST_F(AnnotTest_778, IsOkReturnsTrueForValidAnnot_778) {

    EXPECT_TRUE(annot->isOk());

}



TEST_F(AnnotTest_778, MatchReturnsFalseWithNullRef_778) {

    EXPECT_FALSE(annot->match(nullptr));

}



TEST_F(AnnotTest_778, GetHasRefReturnsFalseByDefault_778) {

    EXPECT_FALSE(annot->getHasRef());

}



TEST_F(AnnotTest_778, GetRefReturnsInvalidRefByDefault_778) {

    EXPECT_EQ(Ref::INVALID(), annot->getRef());

}



TEST_F(AnnotTest_778, GetPageNumReturnsZeroByDefault_778) {

    EXPECT_EQ(0, annot->getPageNum());

}



TEST_F(AnnotTest_778, GetFlagsReturnsZeroByDefault_778) {

    EXPECT_EQ(0u, annot->getFlags());

}



TEST_F(AnnotTest_778, GetContentsReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getContents());

}



TEST_F(AnnotTest_778, GetNameReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getName());

}



TEST_F(AnnotTest_778, GetModifiedReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getModified());

}



TEST_F(AnnotTest_778, GetAppearStreamsReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getAppearStreams());

}



TEST_F(AnnotTest_778, GetAppearStateReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getAppearState());

}



TEST_F(AnnotTest_778, GetBorderReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getBorder());

}



TEST_F(AnnotTest_778, GetColorReturnsNullPtrByDefault_778) {

    EXPECT_EQ(nullptr, annot->getColor());

}



TEST_F(AnnotTest_778, GetTreeKeyReturnsZeroByDefault_778) {

    EXPECT_EQ(0, annot->getTreeKey());

}



TEST_F(AnnotTest_778, GetIdIsConsistent_778) {

    int id = annot->getId();

    EXPECT_EQ(id, annot->getId());

}
