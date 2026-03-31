#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

// Include necessary headers
#include "poppler/PDFDoc.h"
#include "poppler/Form.h"
#include "poppler/GlobalParams.h"

class FormTest_929 : public ::testing::Test {
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

// Test that a document without forms has no Form object or zero fields
TEST_F(FormTest_929, NoFormInDocument_929) {
    // Load a PDF that has no form fields
    // We test with a simple PDF if available; if not, we check null form
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    // Document may or may not have a form; if no form, pointer is null
    if (form == nullptr) {
        SUCCEED();
    } else {
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test getNumFields returns non-negative value
TEST_F(FormTest_929, GetNumFieldsNonNegative_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (form) {
        EXPECT_GE(form->getNumFields(), 0);
    }
}

// Test form with fields has positive getNumFields
TEST_F(FormTest_929, FormWithFieldsHasPositiveCount_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (form) {
        EXPECT_GT(form->getNumFields(), 0);
    } else {
        GTEST_SKIP() << "No form in document";
    }
}

// Test getRootField with valid index
TEST_F(FormTest_929, GetRootFieldValidIndex_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form || form->getNumFields() == 0) {
        GTEST_SKIP() << "No form fields available";
    }
    
    FormField *field = form->getRootField(0);
    EXPECT_NE(field, nullptr);
}

// Test getRootField for all fields
TEST_F(FormTest_929, GetAllRootFields_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    int numFields = form->getNumFields();
    for (int i = 0; i < numFields; i++) {
        FormField *field = form->getRootField(i);
        EXPECT_NE(field, nullptr) << "Field at index " << i << " is null";
    }
}

// Test getNeedAppearances returns a boolean
TEST_F(FormTest_929, GetNeedAppearances_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    bool needAppearances = form->getNeedAppearances();
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(needAppearances == true || needAppearances == false);
}

// Test getDefaultResources
TEST_F(FormTest_929, GetDefaultResources_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    // Default resources may or may not be null depending on the document
    GfxResources *resources = form->getDefaultResources();
    // Just verify no crash
    SUCCEED();
}

// Test getCalculateOrder returns a vector
TEST_F(FormTest_929, GetCalculateOrder_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const std::vector<Ref> &calcOrder = form->getCalculateOrder();
    // Calculate order can be empty; just verify it's accessible
    EXPECT_GE(calcOrder.size(), 0u);
}

// Test findWidgetByRef with invalid ref
TEST_F(FormTest_929, FindWidgetByInvalidRef_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    Ref invalidRef = {-1, -1};
    FormWidget *widget = form->findWidgetByRef(invalidRef);
    EXPECT_EQ(widget, nullptr);
}

// Test findFieldByRef with invalid ref
TEST_F(FormTest_929, FindFieldByInvalidRef_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    Ref invalidRef = {-1, -1};
    const FormField *field = form->findFieldByRef(invalidRef);
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with non-existent name
TEST_F(FormTest_929, FindFieldByNonExistentName_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const FormField *field = form->findFieldByFullyQualifiedName("NonExistentFieldName12345");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedName with empty name
TEST_F(FormTest_929, FindFieldByEmptyName_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const FormField *field = form->findFieldByFullyQualifiedName("");
    EXPECT_EQ(field, nullptr);
}

// Test findFieldByFullyQualifiedNameOrRef with non-existent name
TEST_F(FormTest_929, FindFieldByFullyQualifiedNameOrRefNonExistent_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const FormField *field = form->findFieldByFullyQualifiedNameOrRef("NonExistentField999");
    EXPECT_EQ(field, nullptr);
}

// Test getDefaultResourcesObj
TEST_F(FormTest_929, GetDefaultResourcesObj_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    Object *obj = form->getDefaultResourcesObj();
    // Object pointer should not be null (it points to internal object)
    EXPECT_NE(obj, nullptr);
}

// Test getDefaultAppearance
TEST_F(FormTest_929, GetDefaultAppearance_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const GooString *da = form->getDefaultAppearance();
    // Default appearance may or may not be set
    SUCCEED();
}

// Test Form copy constructor is deleted (compile-time check done by design)
// This is verified by the = delete declaration; we just ensure form works normally
TEST_F(FormTest_929, FormIsNotCopyable_929) {
    EXPECT_FALSE(std::is_copy_constructible<Form>::value);
    EXPECT_FALSE(std::is_copy_assignable<Form>::value);
}

// Test findFontInDefaultResources with non-existent font
TEST_F(FormTest_929, FindFontInDefaultResourcesNonExistent_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    const std::string result = form->findFontInDefaultResources("NonExistentFont", "Regular");
    // Should return empty string if font not found
    EXPECT_TRUE(result.empty());
}

// Test consistency between getNumFields and getRootField
TEST_F(FormTest_929, FieldCountConsistencyWithGetRootField_929) {
    auto doc = loadDocument("../test/unittestcases/AcroFormExportValues.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    Form *form = catalog->getForm();
    if (!form) {
        GTEST_SKIP() << "No form in document";
    }

    int numFields = form->getNumFields();
    int validCount = 0;
    for (int i = 0; i < numFields; i++) {
        if (form->getRootField(i) != nullptr) {
            validCount++;
        }
    }
    EXPECT_EQ(validCount, numFields);
}
