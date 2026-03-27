#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/annot_stamp_for_comment.h"

#include "poppler/PDFDoc.h"

#include "poppler/Dict.h"



using ::testing::Return;

using ::testing::_;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (const));

};



TEST(getForCommentStampExtGStateDictTest_2006, NormalOperation_2006) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    XRef* xref = new XRef();

    EXPECT_CALL(*mockPdfDoc, getXRef()).WillOnce(Return(xref));



    Dict* extGStateDict = getForCommentStampExtGStateDict(mockPdfDoc.get());



    ASSERT_NE(extGStateDict, nullptr);

    ASSERT_TRUE(extGStateDict->hasKey("a0"));

    ASSERT_TRUE(extGStateDict->hasKey("a1"));



    Dict* a0Dict = extGStateDict->lookupNF("a0").getDict();

    ASSERT_NE(a0Dict, nullptr);

    ASSERT_EQ(a0Dict->lookupNF("CA").getNum(), 0.588235);

    ASSERT_EQ(a0Dict->lookupNF("ca").getNum(), 0.588235);



    Dict* a1Dict = extGStateDict->lookupNF("a1").getDict();

    ASSERT_NE(a1Dict, nullptr);

    ASSERT_EQ(a1Dict->lookupNF("CA").getNum(), 1);

    ASSERT_EQ(a1Dict->lookupNF("ca").getNum(), 1);



    delete extGStateDict;

    delete xref;

}



TEST(getForCommentStampExtGStateDictTest_2006, BoundaryConditions_2006) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    XRef* xref = new XRef();

    EXPECT_CALL(*mockPdfDoc, getXRef()).WillOnce(Return(xref));



    Dict* extGStateDict = getForCommentStampExtGStateDict(mockPdfDoc.get());



    ASSERT_EQ(extGStateDict->getLength(), 2);



    delete extGStateDict;

    delete xref;

}



TEST(getForCommentStampExtGStateDictTest_2006, ExceptionalCases_2006) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    XRef* xref = nullptr;

    EXPECT_CALL(*mockPdfDoc, getXRef()).WillOnce(Return(xref));



    // This test assumes that passing a null xref to Dict constructor leads to defined behavior

    // such as non-null dict creation with no entries.

    Dict* extGStateDict = getForCommentStampExtGStateDict(mockPdfDoc.get());



    ASSERT_NE(extGStateDict, nullptr);

    ASSERT_EQ(extGStateDict->getLength(), 0);



    delete extGStateDict;

}



TEST(getForCommentStampExtGStateDictTest_2006, ExternalInteractions_2006) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    XRef* xref = new XRef();

    EXPECT_CALL(*mockPdfDoc, getXRef()).WillOnce(Return(xref));



    Dict* extGStateDict = getForCommentStampExtGStateDict(mockPdfDoc.get());



    ASSERT_NE(extGStateDict, nullptr);

    EXPECT_EQ(mockPdfDoc->getXRef(), xref);



    delete extGStateDict;

    delete xref;

}
