#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/annot_stamp_draft.h"

#include "./TestProjects/poppler/poppler/PDFDoc.h"

#include "./TestProjects/poppler/poppler/Dict.h"



using ::testing::NiceMock;

using ::testing::Return;

using ::testing::_;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



class AnnotStampDraftTest_2014 : public ::testing::Test {

protected:

    NiceMock<MockPDFDoc> mock_pdf_doc_;

};



TEST_F(AnnotStampDraftTest_2014, GetDraftStampExtGStateDict_ReturnsValidDict_2014) {

    auto* ext_gstate_dict = getDraftStampExtGStateDict(&mock_pdf_doc_);

    ASSERT_NE(ext_gstate_dict, nullptr);

}



TEST_F(AnnotStampDraftTest_2014, GetDraftStampExtGStateDict_HasCorrectNestedDicts_2014) {

    auto* ext_gstate_dict = getDraftStampExtGStateDict(&mock_pdf_doc_);

    ASSERT_TRUE(ext_gstate_dict->hasKey("a0"));

    ASSERT_TRUE(ext_gstate_dict->hasKey("a1"));



    auto a0_dict = ext_gstate_dict->lookupNF("a0");

    auto a1_dict = ext_gstate_dict->lookupNF("a1");



    ASSERT_TRUE(a0_dict.isDict());

    ASSERT_TRUE(a1_dict.isDict());

}



TEST_F(AnnotStampDraftTest_2014, GetDraftStampExtGStateDict_NestedDictsHaveCorrectValues_2014) {

    auto* ext_gstate_dict = getDraftStampExtGStateDict(&mock_pdf_doc_);

    auto a0_dict = ext_gstate_dict->lookupNF("a0");

    auto a1_dict = ext_gstate_dict->lookupNF("a1");



    auto ca_a0 = a0_dict.dictLookupNF("CA").getNum();

    auto ca_a1 = a1_dict.dictLookupNF("CA").getNum();



    auto ca_lower_a0 = a0_dict.dictLookupNF("ca").getNum();

    auto ca_lower_a1 = a1_dict.dictLookupNF("ca").getNum();



    EXPECT_DOUBLE_EQ(ca_a0, 0.588235);

    EXPECT_DOUBLE_EQ(ca_a1, 1);



    EXPECT_DOUBLE_EQ(ca_lower_a0, 0.588235);

    EXPECT_DOUBLE_EQ(ca_lower_a1, 1);

}



TEST_F(AnnotStampDraftTest_2014, GetDraftStampExtGStateDict_DoesNotModifyInputPDFDoc_2014) {

    EXPECT_CALL(mock_pdf_doc_, getXRef()).Times(1);



    getDraftStampExtGStateDict(&mock_pdf_doc_);

}
