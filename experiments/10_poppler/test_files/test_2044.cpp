#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "Form.h"



using namespace testing;



// Mock Form class to control its behavior in tests

class MockForm : public Form {

public:

    MOCK_CONST_METHOD0(getDefaultResources, GfxResources*());

};



// Test fixture for PopplerAnnotFreeText creation

class PopplerAnnotFreeTextTest_2044 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the mock form and other necessary objects

        pdfDoc = new PDFDoc();

        mockForm = new MockForm(pdfDoc);

        docCatalog = new Catalog(*pdfDoc);

        annot = std::make_shared<AnnotFreeText>(docCatalog, Ref(1, 0));

    }



    void TearDown() override {

        // Clean up

        delete mockForm;

        delete pdfDoc;

        delete docCatalog;

    }



    PDFDoc* pdfDoc;

    MockForm* mockForm;

    Catalog* docCatalog;

    std::shared_ptr<AnnotFreeText> annot;

};



// Test normal operation with valid font name and size

TEST_F(PopplerAnnotFreeTextTest_2044, ValidFontNameAndSize_2044) {

    // Set up the default appearance for testing

    auto da = std::make_unique<DefaultAppearance>("Arial", 12.0);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a GfxResources object

    auto mockResources = new GfxResources();

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(mockResources));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_desc is correctly set

    ASSERT_NE(popplerAnnot->ft_annot->font_desc, nullptr);

    EXPECT_STREQ(popplerAnnot->ft_annot->font_desc->font_name, "Arial");

    EXPECT_EQ(popplerAnnot->ft_annot->font_desc->size_pt, 12.0);



    // Clean up

    poppler_annot_free(popplerAnnot);

    delete mockResources;

}



// Test boundary condition with empty font name

TEST_F(PopplerAnnotFreeTextTest_2044, EmptyFontName_2044) {

    // Set up the default appearance for testing with an empty font name

    auto da = std::make_unique<DefaultAppearance>("", 12.0);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a GfxResources object

    auto mockResources = new GfxResources();

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(mockResources));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_desc is correctly set to default or fallback font

    ASSERT_NE(popplerAnnot->ft_annot->font_desc, nullptr);

    EXPECT_STREQ(popplerAnnot->ft_annot->font_desc->font_name, ""); // Assuming no fallback is set



    // Clean up

    poppler_annot_free(popplerAnnot);

    delete mockResources;

}



// Test exceptional case with null form

TEST_F(PopplerAnnotFreeTextTest_2044, NullForm_2044) {

    // Set up the default appearance for testing

    auto da = std::make_unique<DefaultAppearance>("Arial", 12.0);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a nullptr GfxResources object

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(nullptr));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_desc is correctly set to default or fallback font

    ASSERT_NE(popplerAnnot->ft_annot->font_desc, nullptr);

    EXPECT_STREQ(popplerAnnot->ft_annot->font_desc->font_name, ""); // Assuming no fallback is set



    // Clean up

    poppler_annot_free(popplerAnnot);

}



// Test boundary condition with zero font size

TEST_F(PopplerAnnotFreeTextTest_2044, ZeroFontSize_2044) {

    // Set up the default appearance for testing with zero font size

    auto da = std::make_unique<DefaultAppearance>("Arial", 0.0);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a GfxResources object

    auto mockResources = new GfxResources();

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(mockResources));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_desc is correctly set with default or fallback size if applicable

    ASSERT_NE(popplerAnnot->ft_annot->font_desc, nullptr);

    EXPECT_EQ(popplerAnnot->ft_annot->font_desc->size_pt, 0.0); // Assuming no adjustment for zero size



    // Clean up

    poppler_annot_free(popplerAnnot);

    delete mockResources;

}



// Test normal operation with font color set

TEST_F(PopplerAnnotFreeTextTest_2044, FontColorSet_2044) {

    // Set up the default appearance for testing with a specific font color

    auto da = std::make_unique<DefaultAppearance>("Arial", 12.0);

    AnnotColor ac{1.0, 0.5, 0.5};

    da->setFontColor(ac);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a GfxResources object

    auto mockResources = new GfxResources();

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(mockResources));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_color is correctly set

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.red, 1.0);

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.green, 0.5);

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.blue, 0.5);



    // Clean up

    poppler_annot_free(popplerAnnot);

    delete mockResources;

}



// Test boundary condition with no font color set

TEST_F(PopplerAnnotFreeTextTest_2044, NoFontColorSet_2044) {

    // Set up the default appearance for testing without a specific font color

    auto da = std::make_unique<DefaultAppearance>("Arial", 12.0);

    annot->setDefaultAppearance(std::move(da));



    // Mock behavior of Form to return a GfxResources object

    auto mockResources = new GfxResources();

    EXPECT_CALL(*mockForm, getDefaultResources()).WillRepeatedly(Return(mockResources));



    // Create the PopplerAnnotFreeText instance

    PopplerAnnot* popplerAnnot = _poppler_annot_free_text_new(annot);



    // Verify that font_color is set to default (black)

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.red, 0.0);

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.green, 0.0);

    ASSERT_EQ(popplerAnnot->ft_annot->font_color.blue, 0.0);



    // Clean up

    poppler_annot_free(popplerAnnot);

    delete mockResources;

}
