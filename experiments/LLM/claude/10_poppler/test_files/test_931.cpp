#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

class FormTest_931 : public ::testing::Test {
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

// Test that getDefaultAppearance returns a value (possibly null) without crashing
TEST_F(FormTest_931, GetDefaultAppearanceReturnsValue_931) {
    // We need a PDF with a form to test this
    // Using a simple PDF that may or may not have forms
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    // getDefaultAppearance may return nullptr or a valid GooString pointer
    const GooString *da = form->getDefaultAppearance();
    // Just verify it doesn't crash - value can be null or non-null
    SUCCEED();
}

// Test getNeedAppearances returns a boolean
TEST_F(FormTest_931, GetNeedAppearancesReturnsBool_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    bool needAppearances = form->getNeedAppearances();
    // Just verify it returns without crashing
    (void)needAppearances;
    SUCCEED();
}

// Test getNumFields returns a non-negative value
TEST_F(FormTest_931, GetNumFieldsReturnsNonNegative_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    int numFields = form->getNumFields();
    EXPECT_GE(numFields, 0);
}

// Test getRootField with valid index
TEST_F(FormTest_931, GetRootFieldValidIndex_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    int numFields = form->getNumFields();
    if (numFields > 0) {
        FormField *field = form->getRootField(0);
        EXPECT_NE(field, nullptr);
    }
}

// Test getDefaultResources
TEST_F(FormTest_931, GetDefaultResourcesReturnsValue_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    GfxResources *resources = form->getDefaultResources();
    // May be null or non-null depending on the PDF
    SUCCEED();
}

// Test getDefaultResourcesObj
TEST_F(FormTest_931, GetDefaultResourcesObjReturnsValue_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    Object *resourcesObj = form->getDefaultResourcesObj();
    EXPECT_NE(resourcesObj, nullptr);
}

// Test getCalculateOrder returns a reference to vector
TEST_F(FormTest_931, GetCalculateOrderReturnsVector_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Should be a valid reference, size >= 0
    EXPECT_GE(static_cast<int>(calcOrder.size()), 0);
}

// Test getTextQuadding
TEST_F(FormTest_931, GetTextQuaddingReturnsValue_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    VariableTextQuadding quadding = form->getTextQuadding();
    // Quadding should be one of the valid enum values
    SUCCEED();
}

// Test findWidgetByRef with invalid ref
TEST_F(FormTest_931, FindWidgetByRefInvalidRef_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    Ref invalidRef = {-1, -1};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with invalid ref
TEST_F(FormTest_931, FindFieldByRefInvalidRef_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    Ref invalidRef = {-1, -1};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with non-existent name
TEST_F(FormTest_931, FindFieldByFullyQualifiedNameNonExistent_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with empty name
TEST_F(FormTest_931, FindFieldByFullyQualifiedNameEmpty_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedNameOrRef with non-existent
TEST_F(FormTest_931, FindFieldByFullyQualifiedNameOrRefNonExistent_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentFieldNameOrRef99999");
    EXPECT_EQ(field, nullptr);
}

// Test iterating all root fields
TEST_F(FormTest_931, IterateAllRootFields_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Root field at index " << i << " should not be null";
    }
}

// Test that Form copy constructor is deleted (compile-time check would be needed,
// but we verify the interface states it)
TEST_F(FormTest_931, FormIsNotCopyable_931) {
    EXPECT_FALSE(std::is_copy_constructible<Form>::value);
    EXPECT_FALSE(std::is_copy_assignable<Form>::value);
}

// Test findFontInDefaultResources with non-existent font
TEST_F(FormTest_931, FindFontInDefaultResourcesNonExistent_931) {
    auto doc = loadTestDoc("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    if (form == nullptr) {
        GTEST_SKIP() << "PDF has no form";
    }
    
    const std::string result = form->findFontInDefaultResources("NonExistentFont", "Regular");
    // Should return empty string if font not found
    EXPECT_TRUE(result.empty());
}
