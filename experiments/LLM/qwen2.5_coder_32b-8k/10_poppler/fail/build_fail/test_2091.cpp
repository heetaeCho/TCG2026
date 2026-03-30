#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "Annot.h"



// Mock PDFDoc and other dependencies if needed

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD0(isEncrypted, bool());

};



// Test fixture for PopplerAnnotText tests

class PopplerAnnotTextTest_2091 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the PDFDoc and other dependencies if needed

        mock_pdf_doc = std::make_unique<MockPDFDoc>();

        poppler_annot_text = static_cast<PopplerAnnotText*>(g_object_new(POPPLER_TYPE_ANNOT_TEXT, nullptr));

        poppler_annot_text->annot.reset(new AnnotText(mock_pdf_doc.get(), nullptr, nullptr));

    }



    void TearDown() override {

        g_object_unref(poppler_annot_text);

    }



    std::unique_ptr<MockPDFDoc> mock_pdf_doc;

    PopplerAnnotText *poppler_annot_text = nullptr;

};



TEST_F(PopplerAnnotTextTest_2091, GetIcon_ReturnsNull_WhenIconIsEmpty_2091) {

    EXPECT_STREQ(poppler_annot_text_get_icon(poppler_annot_text), nullptr);

}



TEST_F(PopplerAnnotTextTest_2091, GetIcon_ReturnsNonNull_WhenIconIsNotEmpty_2091) {

    static_cast<AnnotText*>(poppler_annot_text->annot.get())->setIcon("Comment");

    gchar *icon = poppler_annot_text_get_icon(poppler_annot_text);

    ASSERT_NE(icon, nullptr);

    EXPECT_STREQ(icon, "Comment");

    g_free(icon);

}



TEST_F(PopplerAnnotTextTest_2091, GetIcon_ReturnsCorrectString_WhenIconSetMultipleTimes_2091) {

    static_cast<AnnotText*>(poppler_annot_text->annot.get())->setIcon("Note");

    gchar *icon = poppler_annot_text_get_icon(poppler_annot_text);

    ASSERT_NE(icon, nullptr);

    EXPECT_STREQ(icon, "Note");

    g_free(icon);



    static_cast<AnnotText*>(poppler_annot_text->annot.get())->setIcon("Help");

    icon = poppler_annot_text_get_icon(poppler_annot_text);

    ASSERT_NE(icon, nullptr);

    EXPECT_STREQ(icon, "Help");

    g_free(icon);

}



TEST_F(PopplerAnnotTextTest_2091, GetIcon_ReturnsNull_WhenIconSetToEmptyString_2091) {

    static_cast<AnnotText*>(poppler_annot_text->annot.get())->setIcon("");

    EXPECT_STREQ(poppler_annot_text_get_icon(poppler_annot_text), nullptr);

}



TEST_F(PopplerAnnotTextTest_2091, GetIcon_ReturnsNull_WhenPopplerAnnotIsNull_2091) {

    EXPECT_STREQ(poppler_annot_text_get_icon(nullptr), nullptr);

}
