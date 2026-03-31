#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "goo/GooString.h"

// Since we cannot easily construct FormFieldChoice objects (they require PDFDoc, Object, etc.),
// we need to create minimal test infrastructure. However, given the constraints of the interface,
// we focus on what we can test through the public API.

// Helper to create a minimal PDF document for testing
class FormFieldChoiceTest_915 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll attempt to create test objects where possible
    }

    void TearDown() override {
    }

    // Helper to create a FormFieldChoice from a minimal PDF if possible
    // Since constructing FormFieldChoice requires a PDFDoc and proper PDF objects,
    // we'll work with what we can construct
};

// Test getAppearanceSelectedChoice when appearanceSelectedChoice is set
TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_WhenSet_ReturnsAppearanceChoice_915) {
    // This test verifies that when setAppearanceChoiceContent has been called,
    // getAppearanceSelectedChoice returns the appearance choice content
    // rather than the selected choice.
    
    // Due to the complexity of constructing FormFieldChoice (requires PDFDoc),
    // we test the logic observable from the header:
    // If appearanceSelectedChoice is set, it returns that; otherwise getSelectedChoice()
    
    // We need a real PDF to construct FormFieldChoice properly
    // Create a minimal test PDF with a choice field
    
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    
    // If test PDF doesn't exist, we skip
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    // Get form from document
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Find a choice field
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found in test PDF";
    }
    
    // Test: Before setting appearance choice, result comes from getSelectedChoice
    const GooString *result1 = choiceField->getAppearanceSelectedChoice();
    // Result can be nullptr if nothing is selected
    
    // Set appearance choice content
    auto content = std::make_unique<GooString>("TestAppearanceChoice");
    choiceField->setAppearanceChoiceContent(std::move(content));
    
    // Now getAppearanceSelectedChoice should return the appearance content
    const GooString *result2 = choiceField->getAppearanceSelectedChoice();
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2->c_str(), "TestAppearanceChoice");
}

// Test basic properties of FormFieldChoice
TEST_F(FormFieldChoiceTest_915, BasicProperties_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    // Test that combo/listbox are mutually consistent
    bool isCombo = choiceField->isCombo();
    bool isListBox = choiceField->isListBox();
    EXPECT_NE(isCombo, isListBox) << "A choice field should be either combo or listbox";
    
    // Test numChoices is non-negative
    int numChoices = choiceField->getNumChoices();
    EXPECT_GE(numChoices, 0);
    
    // Test getTopIndex is non-negative
    int topIdx = choiceField->getTopIndex();
    EXPECT_GE(topIdx, 0);
}

// Test select and deselect operations
TEST_F(FormFieldChoiceTest_915, SelectDeselectOperations_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    int numChoices = choiceField->getNumChoices();
    if (numChoices == 0) {
        GTEST_SKIP() << "Choice field has no choices";
    }
    
    // Deselect all first
    choiceField->deselectAll();
    EXPECT_EQ(choiceField->getNumSelected(), 0);
    
    // Select first choice
    choiceField->select(0);
    EXPECT_TRUE(choiceField->isSelected(0));
    EXPECT_GE(choiceField->getNumSelected(), 1);
    
    // Deselect all again
    choiceField->deselectAll();
    EXPECT_EQ(choiceField->getNumSelected(), 0);
    EXPECT_FALSE(choiceField->isSelected(0));
}

// Test getChoice and getExportVal for valid indices
TEST_F(FormFieldChoiceTest_915, GetChoiceAndExportVal_ValidIndex_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    int numChoices = choiceField->getNumChoices();
    if (numChoices == 0) {
        GTEST_SKIP() << "No choices available";
    }
    
    // Test that getChoice returns non-null for valid index
    const GooString *choice = choiceField->getChoice(0);
    EXPECT_NE(choice, nullptr);
    
    // getExportVal may or may not be null depending on PDF
    // Just ensure it doesn't crash
    const GooString *exportVal = choiceField->getExportVal(0);
    // exportVal can be nullptr if no export value is defined
}

// Test toggle operation
TEST_F(FormFieldChoiceTest_915, ToggleOperation_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    int numChoices = choiceField->getNumChoices();
    if (numChoices == 0) {
        GTEST_SKIP() << "No choices available";
    }
    
    // Deselect all, then toggle first choice
    choiceField->deselectAll();
    EXPECT_FALSE(choiceField->isSelected(0));
    
    choiceField->toggle(0);
    EXPECT_TRUE(choiceField->isSelected(0));
    
    choiceField->toggle(0);
    EXPECT_FALSE(choiceField->isSelected(0));
}

// Test setEditChoice and getEditChoice for editable combo boxes
TEST_F(FormFieldChoiceTest_915, EditChoiceOperations_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            FormFieldChoice *fc = static_cast<FormFieldChoice *>(field);
            if (fc->hasEdit()) {
                choiceField = fc;
                break;
            }
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No editable choice field found";
    }
    
    // Set an edit choice
    auto editContent = std::make_unique<GooString>("CustomEditValue");
    choiceField->setEditChoice(std::move(editContent));
    
    const GooString *editChoice = choiceField->getEditChoice();
    ASSERT_NE(editChoice, nullptr);
    EXPECT_STREQ(editChoice->c_str(), "CustomEditValue");
}

// Test getAppearanceSelectedChoice returns getSelectedChoice when appearance is not set
TEST_F(FormFieldChoiceTest_915, GetAppearanceSelectedChoice_WhenNotSet_ReturnsSelectedChoice_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    int numChoices = choiceField->getNumChoices();
    if (numChoices == 0) {
        GTEST_SKIP() << "No choices available";
    }
    
    // Select an item and verify getAppearanceSelectedChoice falls back to getSelectedChoice
    choiceField->deselectAll();
    choiceField->select(0);
    
    const GooString *selectedChoice = choiceField->getSelectedChoice();
    const GooString *appearanceChoice = choiceField->getAppearanceSelectedChoice();
    
    // When no appearance choice is set, they should be the same
    EXPECT_EQ(selectedChoice, appearanceChoice);
}

// Test boundary: isSelected with boundary index values
TEST_F(FormFieldChoiceTest_915, IsSelected_BoundaryIndices_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            choiceField = static_cast<FormFieldChoice *>(field);
            break;
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No choice field found";
    }
    
    int numChoices = choiceField->getNumChoices();
    if (numChoices == 0) {
        GTEST_SKIP() << "No choices available";
    }
    
    // Test first and last valid indices
    choiceField->deselectAll();
    
    // First index
    choiceField->select(0);
    EXPECT_TRUE(choiceField->isSelected(0));
    
    // Last valid index
    if (numChoices > 1) {
        choiceField->deselectAll();
        choiceField->select(numChoices - 1);
        EXPECT_TRUE(choiceField->isSelected(numChoices - 1));
    }
}

// Test multiselect behavior if available
TEST_F(FormFieldChoiceTest_915, MultiSelectBehavior_915) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/choiceFieldTest.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    FormFieldChoice *choiceField = nullptr;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formChoice) {
            FormFieldChoice *fc = static_cast<FormFieldChoice *>(field);
            if (fc->isMultiSelect() && fc->getNumChoices() >= 2) {
                choiceField = fc;
                break;
            }
        }
    }
    
    if (!choiceField) {
        GTEST_SKIP() << "No multiselect choice field found";
    }
    
    choiceField->deselectAll();
    choiceField->select(0);
    choiceField->select(1);
    
    EXPECT_TRUE(choiceField->isSelected(0));
    EXPECT_TRUE(choiceField->isSelected(1));
    EXPECT_GE(choiceField->getNumSelected(), 2);
}
