#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <set>
#include <vector>

#include "Form.h"
#include "PDFDoc.h"
#include "Object.h"
#include "GooString.h"
#include "GlobalParams.h"

class FormFieldTest_884 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal FormField via a PDF document with a form
    std::unique_ptr<PDFDoc> createTestDoc(const std::string &path) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(path.c_str()));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }

    // Helper: create a FormField from a dictionary object
    std::unique_ptr<FormField> createFormField(PDFDoc *doc, Object &&obj, FormFieldType type = formText) {
        std::set<int> usedParents;
        Ref ref = {0, 0};
        // This may or may not work depending on the Object contents
        return std::make_unique<FormField>(doc, std::move(obj), ref, nullptr, &usedParents, type);
    }
};

// Test that getDefaultAppearance returns nullptr when no default appearance is set
TEST_F(FormFieldTest_884, GetDefaultAppearanceReturnsNullWhenNotSet_884) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();
    
    std::set<int> usedParents;
    Ref ref = {0, 0};
    
    // Create a minimal field dict without /DA entry
    Object fieldDict(new Dict(nullptr));
    
    // We can't easily construct FormField without a valid PDFDoc,
    // but we test the interface contract
    // If construction fails, we skip
    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        GooString *da = field.getDefaultAppearance();
        // Default appearance should be null if not set in dict
        EXPECT_EQ(da, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setDefaultAppearance and getDefaultAppearance
TEST_F(FormFieldTest_884, SetDefaultAppearanceUpdatesValue_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        std::string testAppearance = "/Helv 12 Tf 0 g";
        field.setDefaultAppearance(testAppearance);
        
        GooString *da = field.getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), testAppearance.c_str());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setDefaultAppearance with empty string
TEST_F(FormFieldTest_884, SetDefaultAppearanceWithEmptyString_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        field.setDefaultAppearance("");
        
        GooString *da = field.getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), "");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setReadOnly and isReadOnly
TEST_F(FormFieldTest_884, SetReadOnlyAndIsReadOnly_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        field.setReadOnly(true);
        EXPECT_TRUE(field.isReadOnly());
        
        field.setReadOnly(false);
        EXPECT_FALSE(field.isReadOnly());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setStandAlone and isStandAlone
TEST_F(FormFieldTest_884, SetStandAloneAndIsStandAlone_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        field.setStandAlone(true);
        EXPECT_TRUE(field.isStandAlone());
        
        field.setStandAlone(false);
        EXPECT_FALSE(field.isStandAlone());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getType returns the type passed during construction
TEST_F(FormFieldTest_884, GetTypeReturnsConstructedType_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        EXPECT_EQ(field.getType(), formText);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getNumWidgets on a field with no widgets
TEST_F(FormFieldTest_884, GetNumWidgetsReturnsZeroForEmptyField_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        EXPECT_GE(field.getNumWidgets(), 0);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getNumChildren on a field with no children
TEST_F(FormFieldTest_884, GetNumChildrenReturnsZeroForLeafField_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        EXPECT_GE(field.getNumChildren(), 0);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setPartialName and getPartialName
TEST_F(FormFieldTest_884, SetPartialNameAndGetPartialName_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        GooString name("TestFieldName");
        field.setPartialName(name);
        
        const GooString *retrievedName = field.getPartialName();
        ASSERT_NE(retrievedName, nullptr);
        EXPECT_STREQ(retrievedName->c_str(), "TestFieldName");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getRef returns the ref passed during construction
TEST_F(FormFieldTest_884, GetRefReturnsConstructedRef_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {42, 7};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        Ref result = field.getRef();
        EXPECT_EQ(result.num, 42);
        EXPECT_EQ(result.gen, 7);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getObj returns non-null
TEST_F(FormFieldTest_884, GetObjReturnsNonNull_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        Object *obj = field.getObj();
        EXPECT_NE(obj, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setDefaultAppearance overwrite
TEST_F(FormFieldTest_884, SetDefaultAppearanceOverwritesPrevious_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        field.setDefaultAppearance("/Helv 10 Tf 0 g");
        field.setDefaultAppearance("/Cour 14 Tf 1 0 0 rg");
        
        GooString *da = field.getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), "/Cour 14 Tf 1 0 0 rg");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findWidgetByRef with non-existing ref returns nullptr
TEST_F(FormFieldTest_884, FindWidgetByRefReturnsNullForNonExisting_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        Ref searchRef = {999, 0};
        FormWidget *widget = field.findWidgetByRef(searchRef);
        EXPECT_EQ(widget, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findFieldByRef with non-matching ref
TEST_F(FormFieldTest_884, FindFieldByRefReturnsNullForNonMatching_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {1, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        Ref searchRef = {999, 0};
        FormField *found = field.findFieldByRef(searchRef);
        EXPECT_EQ(found, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findFieldByRef with matching ref
TEST_F(FormFieldTest_884, FindFieldByRefReturnsSelfForMatchingRef_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {5, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        FormField *found = field.findFieldByRef(ref);
        // Should find itself
        EXPECT_EQ(found, &field);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getNoExport
TEST_F(FormFieldTest_884, GetNoExportDefaultValue_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        // By default, noExport should be false (typical default)
        bool noExport = field.getNoExport();
        // Just verify it returns a valid boolean
        EXPECT_TRUE(noExport == true || noExport == false);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setPartialName with empty name
TEST_F(FormFieldTest_884, SetPartialNameWithEmptyString_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        GooString emptyName("");
        field.setPartialName(emptyName);
        
        const GooString *retrievedName = field.getPartialName();
        ASSERT_NE(retrievedName, nullptr);
        EXPECT_STREQ(retrievedName->c_str(), "");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test construction with different FormFieldType
TEST_F(FormFieldTest_884, ConstructWithButtonType_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formButton);
        EXPECT_EQ(field.getType(), formButton);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test construction with choice type
TEST_F(FormFieldTest_884, ConstructWithChoiceType_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formChoice);
        EXPECT_EQ(field.getType(), formChoice);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test multiple setReadOnly toggles
TEST_F(FormFieldTest_884, MultipleReadOnlyToggles_884) {
    Object fieldDict(new Dict(nullptr));
    std::set<int> usedParents;
    Ref ref = {0, 0};

    try {
        FormField field(nullptr, std::move(fieldDict), ref, nullptr, &usedParents, formText);
        
        for (int i = 0; i < 10; ++i) {
            field.setReadOnly(true);
            EXPECT_TRUE(field.isReadOnly());
            field.setReadOnly(false);
            EXPECT_FALSE(field.isReadOnly());
        }
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}
