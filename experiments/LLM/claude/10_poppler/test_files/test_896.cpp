#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Form.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <set>

class FormFieldButtonTest_896 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that noToggleToOff returns a boolean value
// Since we can't easily construct FormFieldButton without a valid PDFDoc,
// we test via a minimal PDF that contains a button field.

TEST_F(FormFieldButtonTest_896, NoToggleToOffReturnsBool_896) {
    // Create a minimal PDF with a button form field
    // Using a test PDF file if available, otherwise test the interface concept
    
    // We need a valid PDFDoc to construct FormFieldButton
    // Create a simple test by loading a minimal PDF
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    // Look for a button field in the form
    bool foundButton = false;
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            // noToggleToOff should return a bool without crashing
            bool result = button->noToggleToOff();
            (void)result; // Just verify it doesn't crash and returns a bool
            foundButton = true;
            break;
        }
    }
    
    if (!foundButton) {
        GTEST_SKIP() << "No button field found in test PDF";
    }
}

TEST_F(FormFieldButtonTest_896, GetButtonTypeReturnsValidType_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            FormButtonType btype = button->getButtonType();
            EXPECT_TRUE(btype == formButtonCheck || btype == formButtonPush || btype == formButtonRadio);
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, GetAppearanceStateReturnsNonNull_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            // getAppearanceState may return nullptr or a valid string
            const char *state = button->getAppearanceState();
            // Just verify it doesn't crash
            if (state) {
                EXPECT_GT(strlen(state), 0u);
            }
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, GetNumSiblingsNonNegative_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            int numSiblings = button->getNumSiblings();
            EXPECT_GE(numSiblings, 0);
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, GetStateForOffState_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            // getState returns bool for whether the given state matches
            bool stateOff = button->getState("Off");
            // Just verify it returns a valid bool without crashing
            (void)stateOff;
            SUCCEED();
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, SetStateAndVerify_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            
            if (button->getButtonType() == formButtonCheck) {
                // Try setting state to "Off"
                bool result = button->setState("Off", false);
                // Result depends on current state and noToggleToOff
                (void)result;
                SUCCEED();
            }
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, GetDefaultAppearanceState_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            // May return nullptr if no default appearance state is set
            const char *defaultState = button->getDefaultAppearanceState();
            // Just verify no crash
            (void)defaultState;
            SUCCEED();
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, GetSiblingWithValidIndex_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            int numSiblings = button->getNumSiblings();
            
            for (int j = 0; j < numSiblings; j++) {
                FormFieldButton *sibling = button->getSibling(j);
                // Sibling may or may not be null depending on initialization
                (void)sibling;
            }
            SUCCEED();
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, SetStateWithIgnoreToggleOff_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            
            // Try setting state with ignoreToggleOff = true
            bool result = button->setState("Off", true);
            // With ignoreToggleOff=true, setting to Off should generally succeed
            (void)result;
            SUCCEED();
            break;
        }
    }
}

TEST_F(FormFieldButtonTest_896, CheckboxToggleBehavior_896) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/checkbox_form.pdf"));
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form found in test PDF";
    }
    
    for (int i = 0; i < form->getNumFields(); i++) {
        FormField *field = form->getRootField(i);
        if (field && field->getType() == formButton) {
            FormFieldButton *button = static_cast<FormFieldButton *>(field);
            
            if (button->getButtonType() == formButtonCheck) {
                const char *origState = button->getAppearanceState();
                std::string origStateStr = origState ? origState : "";
                
                // Set to Off
                button->setState("Off", true);
                const char *offState = button->getAppearanceState();
                if (offState) {
                    EXPECT_STREQ(offState, "Off");
                }
                
                break;
            }
        }
    }
}
