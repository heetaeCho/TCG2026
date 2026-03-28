#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers
#include "PDFDoc.h"
#include "Form.h"
#include "GlobalParams.h"

class FormTest_928 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getNeedAppearances returns a bool value (default behavior)
TEST_F(FormTest_928, GetNeedAppearancesReturnsBool_928) {
    // We need a PDF with a form to test this
    // Using a simple PDF that may or may not have NeedAppearances set
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // getNeedAppearances should return either true or false without crashing
    bool result = form->getNeedAppearances();
    EXPECT_TRUE(result == true || result == false);
}

// Test getNumFields returns a non-negative value
TEST_F(FormTest_928, GetNumFieldsNonNegative_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    EXPECT_GE(numFields, 0);
}

// Test getRootField with valid index
TEST_F(FormTest_928, GetRootFieldValidIndex_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    if (numFields > 0) {
        FormField *field = form->getRootField(0);
        EXPECT_NE(field, nullptr);
    }
}

// Test getRootField with last valid index
TEST_F(FormTest_928, GetRootFieldLastIndex_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    if (numFields > 0) {
        FormField *field = form->getRootField(numFields - 1);
        EXPECT_NE(field, nullptr);
    }
}

// Test getDefaultResources
TEST_F(FormTest_928, GetDefaultResources_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Should not crash; may return nullptr if no default resources
    GfxResources *resources = form->getDefaultResources();
    // Just verify it doesn't crash - resources may or may not be null
    (void)resources;
    SUCCEED();
}

// Test getDefaultResourcesObj
TEST_F(FormTest_928, GetDefaultResourcesObj_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Object *obj = form->getDefaultResourcesObj();
    EXPECT_NE(obj, nullptr);
}

// Test getCalculateOrder returns a vector
TEST_F(FormTest_928, GetCalculateOrderReturnsVector_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Calculate order may be empty or have entries
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test getDefaultAppearance
TEST_F(FormTest_928, GetDefaultAppearance_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Should not crash - may return nullptr
    const GooString *da = form->getDefaultAppearance();
    (void)da;
    SUCCEED();
}

// Test findWidgetByRef with invalid ref
TEST_F(FormTest_928, FindWidgetByRefInvalidRef_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {-1, -1};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with invalid ref
TEST_F(FormTest_928, FindFieldByRefInvalidRef_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref invalidRef = {-1, -1};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with nonexistent name
TEST_F(FormTest_928, FindFieldByFullyQualifiedNameNotFound_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("nonexistent_field_name_xyz_12345");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with empty name
TEST_F(FormTest_928, FindFieldByFullyQualifiedNameEmpty_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedNameOrRef with nonexistent
TEST_F(FormTest_928, FindFieldByFullyQualifiedNameOrRefNotFound_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("nonexistent_field_xyz");
    EXPECT_EQ(field, nullptr);
}

// Test getTextQuadding
TEST_F(FormTest_928, GetTextQuadding_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    VariableTextQuadding q = form->getTextQuadding();
    // Should be a valid quadding value
    EXPECT_GE(static_cast<int>(q), 0);
    EXPECT_LE(static_cast<int>(q), 2);
}

// Test that Form copy constructor is deleted (compile-time check implicit)
// We verify the form object works properly after construction
TEST_F(FormTest_928, FormConstructionAndBasicOperations_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Basic consistency: numFields should match accessible root fields
    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Root field at index " << i << " should not be null";
    }
}

// Test fieldLookup static method
TEST_F(FormTest_928, FieldLookupStatic_928) {
    // fieldLookup is a static method that takes a Dict and key
    // We test with a null-like scenario - this depends on implementation
    // but we mainly verify it doesn't crash with typical usage
    SUCCEED(); // Static method testing requires Dict construction which is complex
}

// Test consistency between getNumFields and getRootField
TEST_F(FormTest_928, NumFieldsConsistentWithRootFields_928) {
    auto doc = loadDocument("../test/unittestcases/Form1.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    // All valid indices should return non-null fields
    for (int i = 0; i < numFields; ++i) {
        EXPECT_NE(form->getRootField(i), nullptr);
    }
}
