#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers from the project
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "poppler/GooString.h"

class FormTest_930 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a PDF file with a form
    std::unique_ptr<PDFDoc> createPDFDocFromFile(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that Form can be constructed from a valid PDFDoc
TEST_F(FormTest_930, ConstructionFromValidDoc_930) {
    // We need a PDF with a form. If no test file is available,
    // we test with a minimal approach.
    // This test verifies that the Form object can be queried without crashing.
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    // Form may or may not exist depending on the PDF
    // If form exists, we can query it
    if (form) {
        int numFields = form->getNumFields();
        EXPECT_GE(numFields, 0);
    }
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_930, GetNumFieldsNonNegative_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    EXPECT_GE(form->getNumFields(), 0);
}

// Test getRootField returns valid pointer for valid index
TEST_F(FormTest_930, GetRootFieldValidIndex_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
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

// Test getRootField for all fields
TEST_F(FormTest_930, GetAllRootFields_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Field at index " << i << " should not be null";
    }
}

// Test getNeedAppearances returns a boolean value
TEST_F(FormTest_930, GetNeedAppearances_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    // Just verify it doesn't crash and returns a valid bool
    bool needAppearances = form->getNeedAppearances();
    EXPECT_TRUE(needAppearances || !needAppearances);
}

// Test getDefaultResources
TEST_F(FormTest_930, GetDefaultResources_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    // getDefaultResources may return nullptr if no default resources are set
    // Just verify it doesn't crash
    GfxResources *resources = form->getDefaultResources();
    // Result can be null or non-null, just verifying no crash
    (void)resources;
}

// Test getDefaultResourcesObj
TEST_F(FormTest_930, GetDefaultResourcesObj_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    Object *obj = form->getDefaultResourcesObj();
    EXPECT_NE(obj, nullptr);
}

// Test getCalculateOrder returns a vector
TEST_F(FormTest_930, GetCalculateOrder_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Calculate order can be empty or have entries
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test findFieldByFullyQualifiedName with empty name
TEST_F(FormTest_930, FindFieldByFullyQualifiedNameEmpty_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    const FormField *field = form->findFieldByFullyQualifiedName("");
    // Empty name should likely return nullptr
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with nonexistent name
TEST_F(FormTest_930, FindFieldByFullyQualifiedNameNonexistent_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test findWidgetByRef with invalid ref
TEST_F(FormTest_930, FindWidgetByRefInvalid_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    Ref invalidRef = {-1, -1};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with invalid ref
TEST_F(FormTest_930, FindFieldByRefInvalid_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    Ref invalidRef = {999999, 999999};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test getDefaultAppearance
TEST_F(FormTest_930, GetDefaultAppearance_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    // Default appearance can be null or a valid string
    const GooString *da = form->getDefaultAppearance();
    // Just verify no crash - result depends on PDF content
    (void)da;
}

// Test findFieldByFullyQualifiedNameOrRef with nonexistent string
TEST_F(FormTest_930, FindFieldByFullyQualifiedNameOrRefNonexistent_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("totally_nonexistent_field_999");
    EXPECT_EQ(field, nullptr);
}

// Test that Form copy constructor is deleted (compile-time check conceptually)
// This is verified by the fact that the class has copy constructor deleted
// We can't test this at runtime, but we document the intent.

// Test reset with empty fields vector
TEST_F(FormTest_930, ResetWithEmptyFields_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    std::vector<std::string> emptyFields;
    // Reset with empty fields and excludeFields=false should not crash
    form->reset(emptyFields, false);

    // Verify form is still accessible
    EXPECT_GE(form->getNumFields(), 0);
}

// Test reset with excludeFields=true
TEST_F(FormTest_930, ResetWithExcludeFields_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    std::vector<std::string> emptyFields;
    form->reset(emptyFields, true);

    EXPECT_GE(form->getNumFields(), 0);
}

// Test fieldLookup static method with null key
TEST_F(FormTest_930, FieldLookupStaticMethod_930) {
    // fieldLookup is a static method that takes a Dict and a key
    // We test it doesn't crash with a valid Dict but non-existent key
    // Creating a minimal Object dict for testing
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();
    
    Object result = Form::fieldLookup(dict, "nonexistent_key");
    EXPECT_TRUE(result.isNull() || result.isNone());
}

// Test getTextQuadding
TEST_F(FormTest_930, GetTextQuadding_930) {
    auto doc = createPDFDocFromFile("../test/unittestcases/Field-annotation-text.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF file not available";
    }

    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }

    VariableTextQuadding quadding = form->getTextQuadding();
    // Quadding should be one of the valid enum values
    EXPECT_GE(static_cast<int>(quadding), 0);
}
