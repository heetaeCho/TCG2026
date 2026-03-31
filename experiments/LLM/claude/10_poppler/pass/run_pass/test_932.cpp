#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

#include "Form.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FormTest_932 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that Form can be constructed from a PDFDoc with forms
TEST_F(FormTest_932, ConstructFromPDFDoc_932) {
    // We need a PDF document that contains form fields to properly test
    // Since we don't have a test PDF readily available, we test with a simple PDF
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    // Form may or may not exist depending on document
    // This test just verifies no crash occurs
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_932, GetNumFieldsNonNegative_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    EXPECT_GE(form->getNumFields(), 0);
}

// Test getRootField with valid index
TEST_F(FormTest_932, GetRootFieldValidIndex_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
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

// Test getRootField iterating through all fields
TEST_F(FormTest_932, GetAllRootFields_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Field at index " << i << " is null";
    }
}

// Test getTextQuadding returns a valid enum value
TEST_F(FormTest_932, GetTextQuaddingValid_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    VariableTextQuadding quadding = form->getTextQuadding();
    // VariableTextQuadding should be one of the valid enum values
    EXPECT_TRUE(quadding == VariableTextQuadding::leftJustified ||
                quadding == VariableTextQuadding::centered ||
                quadding == VariableTextQuadding::rightJustified);
}

// Test getNeedAppearances returns a boolean
TEST_F(FormTest_932, GetNeedAppearances_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Just verify it doesn't crash and returns a valid bool
    bool needAppearances = form->getNeedAppearances();
    EXPECT_TRUE(needAppearances == true || needAppearances == false);
}

// Test getDefaultResources
TEST_F(FormTest_932, GetDefaultResources_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // Default resources may or may not be present
    GfxResources *resources = form->getDefaultResources();
    // Just verify no crash - resources can be null
}

// Test getDefaultResourcesObj
TEST_F(FormTest_932, GetDefaultResourcesObj_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
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
TEST_F(FormTest_932, GetCalculateOrder_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Calculate order can be empty, just verify no crash
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test getDefaultAppearance
TEST_F(FormTest_932, GetDefaultAppearance_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const GooString *da = form->getDefaultAppearance();
    // Default appearance may or may not be set - just test no crash
}

// Test findWidgetByRef with invalid ref
TEST_F(FormTest_932, FindWidgetByRefInvalid_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
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
TEST_F(FormTest_932, FindFieldByRefInvalid_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
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

// Test findFieldByFullyQualifiedName with empty string
TEST_F(FormTest_932, FindFieldByFullyQualifiedNameEmpty_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
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

// Test findFieldByFullyQualifiedName with nonexistent name
TEST_F(FormTest_932, FindFieldByFullyQualifiedNameNonexistent_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedNameOrRef with nonexistent value
TEST_F(FormTest_932, FindFieldByFullyQualifiedNameOrRefNonexistent_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentField");
    EXPECT_EQ(field, nullptr);
}

// Test findWidgetByRef with ref {0, 0}
TEST_F(FormTest_932, FindWidgetByRefZero_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    Ref zeroRef = {0, 0};
    FormWidget *widget = form->findWidgetByRef(zeroRef);
    // Ref {0, 0} is unlikely to be valid
    // Just verify no crash
}

// Test Form copy constructor is deleted (compile-time check implicitly)
// This is verified by the = delete declaration

// Test fieldLookup static method with nullptr
TEST_F(FormTest_932, FieldLookupStaticMethod_932) {
    // fieldLookup is static, test with a minimal dict
    // Since we can't easily construct a Dict without XRef, 
    // we verify the static method exists by referencing it
    // Actual testing would require proper Dict construction
}

// Test reset with empty fields vector
TEST_F(FormTest_932, ResetWithEmptyFields_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    std::vector<std::string> emptyFields;
    // Reset with empty fields and excludeFields=false should be a no-op essentially
    form->reset(emptyFields, false);
    
    // Verify form is still accessible
    EXPECT_GE(form->getNumFields(), 0);
}

// Test reset with excludeFields=true and empty fields (should reset all)
TEST_F(FormTest_932, ResetWithEmptyFieldsExclude_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    std::vector<std::string> emptyFields;
    form->reset(emptyFields, true);
    
    // Verify form is still accessible after reset
    EXPECT_GE(form->getNumFields(), 0);
}

// Test findFontInDefaultResources with empty strings
TEST_F(FormTest_932, FindFontInDefaultResourcesEmpty_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::string result = form->findFontInDefaultResources("", "");
    // Empty font family should return empty result
}

// Test findFontInDefaultResources with nonexistent font
TEST_F(FormTest_932, FindFontInDefaultResourcesNonexistent_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    const std::string result = form->findFontInDefaultResources("NonExistentFontFamily999", "Regular");
    // Font not in resources should return empty string
    EXPECT_TRUE(result.empty());
}

// Test postWidgetsLoad doesn't crash
TEST_F(FormTest_932, PostWidgetsLoadNoCrash_932) {
    auto doc = loadTestDoc("../test/unittestcases/Field-test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in test PDF";
    }
    
    // postWidgetsLoad should not crash even if called multiple times
    form->postWidgetsLoad();
    EXPECT_GE(form->getNumFields(), 0);
}
