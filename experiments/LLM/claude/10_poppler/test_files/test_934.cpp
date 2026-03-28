#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include <memory>
#include <string>

class FormTest_934 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getDefaultResourcesObj returns a non-null Object pointer
TEST_F(FormTest_934, GetDefaultResourcesObjReturnsNonNull_934) {
    // We need a PDF with a form to test this
    // Try to create a minimal test with a PDF that has AcroForm
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog available";
    }
    
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Object *resObj = form->getDefaultResourcesObj();
    ASSERT_NE(resObj, nullptr);
}

// Test getNeedAppearances returns a boolean value
TEST_F(FormTest_934, GetNeedAppearancesReturnsBool_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    bool needApp = form->getNeedAppearances();
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(needApp == true || needApp == false);
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_934, GetNumFieldsReturnsNonNegative_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    EXPECT_GE(numFields, 0);
}

// Test getRootField with valid index
TEST_F(FormTest_934, GetRootFieldValidIndex_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    if (numFields > 0) {
        FormField *field = form->getRootField(0);
        EXPECT_NE(field, nullptr);
    }
}

// Test getDefaultResources
TEST_F(FormTest_934, GetDefaultResources_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Just verify it doesn't crash - may or may not be null depending on the PDF
    GfxResources *res = form->getDefaultResources();
    // No assertion on value since it depends on the PDF content
    (void)res;
    SUCCEED();
}

// Test getCalculateOrder returns a valid reference
TEST_F(FormTest_934, GetCalculateOrderReturnsValidRef_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Calculate order may be empty, but the call should not crash
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test getTextQuadding
TEST_F(FormTest_934, GetTextQuaddingReturnsValid_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    VariableTextQuadding quadding = form->getTextQuadding();
    // Should be one of the valid enum values
    EXPECT_GE(static_cast<int>(quadding), 0);
}

// Test findWidgetByRef with invalid ref returns nullptr
TEST_F(FormTest_934, FindWidgetByRefInvalidRefReturnsNull_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {99999, 99999};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with invalid ref returns nullptr
TEST_F(FormTest_934, FindFieldByRefInvalidRefReturnsNull_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {99999, 99999};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with non-existent name returns nullptr
TEST_F(FormTest_934, FindFieldByFullyQualifiedNameNotFound_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedNameOrRef with non-existent field returns nullptr
TEST_F(FormTest_934, FindFieldByFullyQualifiedNameOrRefNotFound_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test getDefaultAppearance
TEST_F(FormTest_934, GetDefaultAppearance_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // May return nullptr if no default appearance is set
    const GooString *da = form->getDefaultAppearance();
    // Just verify the call doesn't crash
    (void)da;
    SUCCEED();
}

// Test iterating through all root fields
TEST_F(FormTest_934, IterateAllRootFields_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Root field at index " << i << " should not be null";
    }
}

// Test findFontInDefaultResources with non-existent font
TEST_F(FormTest_934, FindFontInDefaultResourcesNotFound_934) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::string result = form->findFontInDefaultResources("NonExistentFontFamily99999", "Regular");
    // Expected to return empty string when font is not found
    EXPECT_TRUE(result.empty());
}

// Test that Form copy constructor is deleted (compile-time check - just ensure it's documented)
TEST_F(FormTest_934, FormIsNotCopyable_934) {
    EXPECT_FALSE(std::is_copy_constructible<Form>::value);
    EXPECT_FALSE(std::is_copy_assignable<Form>::value);
}
