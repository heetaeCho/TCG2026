#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include <string>

// Include necessary headers from poppler
#include "Form.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FormTest_935 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadDocument(const std::string &filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getCalculateOrder returns a reference to a vector of Ref
TEST_F(FormTest_935, GetCalculateOrderReturnsVector_935) {
    // We need a PDF with a form to test this
    // Try to create a PDFDoc from a simple PDF with forms
    // Since we may not have a test PDF, we test what we can
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Just verify it returns without crashing - the vector may be empty
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test that getCalculateOrder returns consistent results on multiple calls
TEST_F(FormTest_935, GetCalculateOrderConsistentResults_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder1 = form->getCalculateOrder();
    const std::vector<Ref> &calcOrder2 = form->getCalculateOrder();
    
    // Should return the same reference
    EXPECT_EQ(&calcOrder1, &calcOrder2);
    EXPECT_EQ(calcOrder1.size(), calcOrder2.size());
}

// Test getNeedAppearances
TEST_F(FormTest_935, GetNeedAppearances_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Just verify it returns a boolean without crashing
    bool needApp = form->getNeedAppearances();
    (void)needApp; // suppress unused warning
    SUCCEED();
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_935, GetNumFieldsNonNegative_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
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
TEST_F(FormTest_935, GetRootFieldValidIndex_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
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
TEST_F(FormTest_935, GetDefaultResources_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // May or may not be null depending on the PDF
    GfxResources *res = form->getDefaultResources();
    (void)res;
    SUCCEED();
}

// Test getDefaultResourcesObj
TEST_F(FormTest_935, GetDefaultResourcesObj_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Object *resObj = form->getDefaultResourcesObj();
    EXPECT_NE(resObj, nullptr);
}

// Test findWidgetByRef with an invalid ref
TEST_F(FormTest_935, FindWidgetByRefInvalidRef_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {-1, -1};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with an invalid ref
TEST_F(FormTest_935, FindFieldByRefInvalidRef_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {-1, -1};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with non-existent name
TEST_F(FormTest_935, FindFieldByFullyQualifiedNameNotFound_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
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

// Test findFieldByFullyQualifiedNameOrRef with non-existent field
TEST_F(FormTest_935, FindFieldByFullyQualifiedNameOrRefNotFound_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentField999");
    EXPECT_EQ(field, nullptr);
}

// Test that Form copy constructor is deleted (compile-time check implied)
// This is a design constraint test - we verify the form exists and works
TEST_F(FormTest_935, FormIsNotCopyable_935) {
    EXPECT_FALSE(std::is_copy_constructible<Form>::value);
    EXPECT_FALSE(std::is_copy_assignable<Form>::value);
}

// Test getDefaultAppearance
TEST_F(FormTest_935, GetDefaultAppearance_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // May return nullptr if not set
    const GooString *da = form->getDefaultAppearance();
    (void)da;
    SUCCEED();
}

// Test that all root fields are accessible
TEST_F(FormTest_935, AllRootFieldsAccessible_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
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
        EXPECT_NE(field, nullptr) << "Root field at index " << i << " is null";
    }
}

// Test getCalculateOrder returns empty vector when no calculate order
TEST_F(FormTest_935, GetCalculateOrderMayBeEmpty_935) {
    auto doc = loadDocument("./TestProjects/poppler/test/unittestcases/Field-AcroForm.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Verify we can iterate over it safely
    for (const auto &ref : calcOrder) {
        EXPECT_GE(ref.num, 0);
    }
}
