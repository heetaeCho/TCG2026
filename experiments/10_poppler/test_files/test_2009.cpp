#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/annot_stamp_not_approved.h"

#include "./TestProjects/poppler/poppler/PDFDoc.h"



using ::testing::Return;

using ::testing::_;



class PDFDocMock : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



class AnnotStampNotApprovedTest_2009 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDocMock> mock_pdf_doc;

    XRef* mock_xref;



    void SetUp() override {

        mock_pdf_doc = std::make_unique<PDFDocMock>();

        mock_xref = new XRef();

        EXPECT_CALL(*mock_pdf_doc, getXRef()).WillRepeatedly(Return(mock_xref));

    }



    void TearDown() override {

        delete mock_xref;

    }

};



TEST_F(AnnotStampNotApprovedTest_2009, ReturnsValidDict_2009) {

    Dict* extGStateDict = getNotApprovedStampExtGStateDict(mock_pdf_doc.get());

    ASSERT_NE(extGStateDict, nullptr);

}



TEST_F(AnnotStampNotApprovedTest_2009, ContainsA0DictWithCorrectValues_2009) {

    Dict* extGStateDict = getNotApprovedStampExtGStateDict(mock_pdf_doc.get());

    const Object& a0Obj = extGStateDict->lookupNF("a0");

    ASSERT_TRUE(a0Obj.isDict());



    const Dict* a0Dict = a0Obj.getDict();

    const Object& caObjA0 = a0Dict->lookupNF("CA");

    const Object& caObjCa = a0Dict->lookupNF("ca");



    EXPECT_DOUBLE_EQ(caObjA0.getNum(), 0.588235);

    EXPECT_DOUBLE_EQ(caObjCa.getNum(), 0.588235);

}



TEST_F(AnnotStampNotApprovedTest_2009, ContainsA1DictWithCorrectValues_2009) {

    Dict* extGStateDict = getNotApprovedStampExtGStateDict(mock_pdf_doc.get());

    const Object& a1Obj = extGStateDict->lookupNF("a1");

    ASSERT_TRUE(a1Obj.isDict());



    const Dict* a1Dict = a1Obj.getDict();

    const Object& caObjA1 = a1Dict->lookupNF("CA");

    const Object& caObjCa = a1Dict->lookupNF("ca");



    EXPECT_DOUBLE_EQ(caObjA1.getNum(), 1);

    EXPECT_DOUBLE_EQ(caObjCa.getNum(), 1);

}



TEST_F(AnnotStampNotApprovedTest_2009, DictContainsTwoKeys_2009) {

    Dict* extGStateDict = getNotApprovedStampExtGStateDict(mock_pdf_doc.get());

    EXPECT_EQ(extGStateDict->getLength(), 2);

}
