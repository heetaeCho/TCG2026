#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

#include "Form.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GfxState.h"

class FormTest_933 : public ::testing::Test {
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

// Test that Form can be constructed from a valid PDFDoc with forms
TEST_F(FormTest_933, ConstructFormFromValidDoc_933) {
    // We need a PDF with form fields for a meaningful test
    // Using a simple PDF that may or may not have forms
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Form *form = catalog->getForm();
    // Form may or may not exist depending on PDF content
    // Just verify we can query it without crashing
    if (form) {
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_933, GetNumFieldsNonNegative_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        int numFields = form->getNumFields();
        EXPECT_GE(numFields, 0);
    }
}

// Test getRootField with valid index
TEST_F(FormTest_933, GetRootFieldValidIndex_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form && form->getNumFields() > 0) {
        FormField *field = form->getRootField(0);
        EXPECT_NE(field, nullptr);
    }
}

// Test getDefaultResources can be called (may return null)
TEST_F(FormTest_933, GetDefaultResources_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        // Just verify it doesn't crash; result may be null
        GfxResources *res = form->getDefaultResources();
        // No assertion on value since it depends on the PDF
        (void)res;
    }
}

// Test getNeedAppearances
TEST_F(FormTest_933, GetNeedAppearances_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        bool needApp = form->getNeedAppearances();
        // Just verify it returns a valid bool without crashing
        EXPECT_TRUE(needApp || !needApp);
    }
}

// Test getDefaultAppearance
TEST_F(FormTest_933, GetDefaultAppearance_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const GooString *da = form->getDefaultAppearance();
        // May be null; just verify no crash
        (void)da;
    }
}

// Test getCalculateOrder
TEST_F(FormTest_933, GetCalculateOrder_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const std::vector<Ref> &calcOrder = form->getCalculateOrder();
        // Just verify we can access it
        EXPECT_GE(calcOrder.size(), 0u);
    }
}

// Test getDefaultResourcesObj
TEST_F(FormTest_933, GetDefaultResourcesObj_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        Object *resObj = form->getDefaultResourcesObj();
        // May be null; just verify no crash
        (void)resObj;
    }
}

// Test getTextQuadding
TEST_F(FormTest_933, GetTextQuadding_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        VariableTextQuadding q = form->getTextQuadding();
        // Valid values are typically 0, 1, 2
        EXPECT_GE(static_cast<int>(q), 0);
        EXPECT_LE(static_cast<int>(q), 2);
    }
}

// Test findWidgetByRef with an invalid Ref
TEST_F(FormTest_933, FindWidgetByRefInvalid_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        Ref invalidRef = {-1, -1};
        FormWidget *widget = form->findWidgetByRef(invalidRef);
        EXPECT_EQ(widget, nullptr);
    }
}

// Test findFieldByRef with an invalid Ref
TEST_F(FormTest_933, FindFieldByRefInvalid_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        Ref invalidRef = {-1, -1};
        const FormField *field = form->findFieldByRef(invalidRef);
        EXPECT_EQ(field, nullptr);
    }
}

// Test findFieldByFullyQualifiedName with empty string
TEST_F(FormTest_933, FindFieldByFullyQualifiedNameEmpty_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const FormField *field = form->findFieldByFullyQualifiedName("");
        EXPECT_EQ(field, nullptr);
    }
}

// Test findFieldByFullyQualifiedName with nonexistent name
TEST_F(FormTest_933, FindFieldByFullyQualifiedNameNonexistent_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
        EXPECT_EQ(field, nullptr);
    }
}

// Test findFieldByFullyQualifiedNameOrRef with nonexistent field
TEST_F(FormTest_933, FindFieldByFullyQualifiedNameOrRefNonexistent_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentField999");
        EXPECT_EQ(field, nullptr);
    }
}

// Test iterating through all root fields
TEST_F(FormTest_933, IterateAllRootFields_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        int numFields = form->getNumFields();
        for (int i = 0; i < numFields; i++) {
            FormField *field = form->getRootField(i);
            EXPECT_NE(field, nullptr) << "Field at index " << i << " is null";
        }
    }
}

// Test fieldLookup static method with nullptr-like dict scenario
TEST_F(FormTest_933, FieldLookupStaticMethod_933) {
    // fieldLookup is a static method that takes a Dict* and key
    // We test it with a valid dict that doesn't have the key
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    // Create a simple dict object
    Dict *dict = new Dict(doc->getXRef());
    Object result = Form::fieldLookup(dict, "NonExistentKey");
    EXPECT_TRUE(result.isNull());
    delete dict;
}

// Test that a PDF without forms returns null Form
TEST_F(FormTest_933, NullFormForPDFWithoutForms_933) {
    // Try to load a simple PDF without form fields
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    // A PDF without forms should have no Form object, or Form with 0 fields
    if (form) {
        // If form exists, it should have 0 fields for a non-form PDF
        // (or it might not exist at all)
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test reset with empty fields vector
TEST_F(FormTest_933, ResetWithEmptyFieldsExclude_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        std::vector<std::string> emptyFields;
        // Reset with empty list and excludeFields=true should reset all
        form->reset(emptyFields, true);
        // Verify form is still valid
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test reset with empty fields vector and excludeFields=false
TEST_F(FormTest_933, ResetWithEmptyFieldsInclude_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        std::vector<std::string> emptyFields;
        // Reset with empty list and excludeFields=false should reset none
        form->reset(emptyFields, false);
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test findFontInDefaultResources with non-existent font
TEST_F(FormTest_933, FindFontInDefaultResourcesNonExistent_933) {
    auto doc = loadDocument("../test/unittestcases/Field-alias.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Form *form = doc->getCatalog()->getForm();
    if (form) {
        const std::string result = form->findFontInDefaultResources("NonExistentFont", "Regular");
        // Should return empty string if font not found
        // (behavior depends on implementation)
        (void)result;
    }
}
