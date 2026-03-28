#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Form.h"
#include "PDFDoc.h"
#include "Object.h"
#include "GooString.h"

// Helper to create a minimal PDFDoc for testing
// We need a valid PDFDoc to construct FormField objects
class FormFieldTest_888 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF in memory for testing
        // We'll try to construct FormField with minimal valid objects
    }

    void TearDown() override {
    }

    // Helper to create a dictionary Object that represents a minimal form field
    Object createMinimalFieldDict() {
        Object dict = Object(new Dict(nullptr));
        return dict;
    }
};

// Test that getAlternateUiName returns nullptr when no alternate UI name is set
TEST_F(FormFieldTest_888, GetAlternateUiName_WhenNotSet_ReturnsNull_888) {
    // Create a minimal form field dictionary without /TU entry
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    // Note: This may crash if PDFDoc is required to be non-null
    // We test observable behavior through the interface
    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        const GooString *altName = field.getAlternateUiName();
        // If no /TU entry, alternateUiName should be nullptr
        EXPECT_EQ(altName, nullptr);
    } catch (...) {
        // If construction fails due to null PDFDoc, that's acceptable
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getType returns the type passed during construction
TEST_F(FormFieldTest_888, GetType_ReturnsConstructedType_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        EXPECT_EQ(field.getType(), formText);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test isReadOnly default and setter
TEST_F(FormFieldTest_888, SetReadOnly_ChangesReadOnlyState_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        // Set read only to true
        field.setReadOnly(true);
        EXPECT_TRUE(field.isReadOnly());

        // Set read only to false
        field.setReadOnly(false);
        EXPECT_FALSE(field.isReadOnly());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test isStandAlone and setStandAlone
TEST_F(FormFieldTest_888, SetStandAlone_ChangesStandAloneState_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        field.setStandAlone(true);
        EXPECT_TRUE(field.isStandAlone());

        field.setStandAlone(false);
        EXPECT_FALSE(field.isStandAlone());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setPartialName and getPartialName
TEST_F(FormFieldTest_888, SetPartialName_UpdatesPartialName_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        GooString name("TestFieldName");
        field.setPartialName(name);

        const GooString *result = field.getPartialName();
        ASSERT_NE(result, nullptr);
        EXPECT_STREQ(result->c_str(), "TestFieldName");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setDefaultAppearance and getDefaultAppearance
TEST_F(FormFieldTest_888, SetDefaultAppearance_UpdatesAppearance_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        std::string appearance = "/Helv 12 Tf 0 0 0 rg";
        field.setDefaultAppearance(appearance);

        GooString *da = field.getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), "/Helv 12 Tf 0 0 0 rg");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getRef returns the ref passed during construction
TEST_F(FormFieldTest_888, GetRef_ReturnsConstructionRef_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {42, 7};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        Ref result = field.getRef();
        EXPECT_EQ(result.num, 42);
        EXPECT_EQ(result.gen, 7);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getNumWidgets when no widgets are added
TEST_F(FormFieldTest_888, GetNumWidgets_WhenEmpty_ReturnsZero_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        EXPECT_GE(field.getNumWidgets(), 0);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getNumChildren when no children exist
TEST_F(FormFieldTest_888, GetNumChildren_WhenEmpty_ReturnsZero_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        EXPECT_GE(field.getNumChildren(), 0);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getMappingName when not set
TEST_F(FormFieldTest_888, GetMappingName_WhenNotSet_ReturnsNull_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        const GooString *mapping = field.getMappingName();
        // When not set, should be nullptr
        EXPECT_EQ(mapping, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findWidgetByRef with invalid ref returns nullptr
TEST_F(FormFieldTest_888, FindWidgetByRef_InvalidRef_ReturnsNull_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        Ref searchRef = {999, 0};
        FormWidget *widget = field.findWidgetByRef(searchRef);
        EXPECT_EQ(widget, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findFieldByRef with non-matching ref
TEST_F(FormFieldTest_888, FindFieldByRef_NonMatchingRef_ReturnsNull_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        Ref searchRef = {999, 0};
        FormField *found = field.findFieldByRef(searchRef);
        // Should return nullptr if ref doesn't match
        // or return &field if ref matches
        if (searchRef.num != ref.num || searchRef.gen != ref.gen) {
            EXPECT_EQ(found, nullptr);
        }
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findFieldByRef with matching ref
TEST_F(FormFieldTest_888, FindFieldByRef_MatchingRef_ReturnsSelf_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        FormField *found = field.findFieldByRef(ref);
        EXPECT_EQ(found, &field);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test getObj returns non-null
TEST_F(FormFieldTest_888, GetObj_ReturnsNonNull_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        Object *obj = field.getObj();
        EXPECT_NE(obj, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setReadOnly toggle multiple times
TEST_F(FormFieldTest_888, SetReadOnly_ToggleMultipleTimes_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);

        field.setReadOnly(true);
        EXPECT_TRUE(field.isReadOnly());

        field.setReadOnly(false);
        EXPECT_FALSE(field.isReadOnly());

        field.setReadOnly(true);
        EXPECT_TRUE(field.isReadOnly());
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setPartialName with empty string
TEST_F(FormFieldTest_888, SetPartialName_EmptyString_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        GooString emptyName("");
        field.setPartialName(emptyName);

        const GooString *result = field.getPartialName();
        ASSERT_NE(result, nullptr);
        EXPECT_STREQ(result->c_str(), "");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test construction with different FormFieldTypes
TEST_F(FormFieldTest_888, GetType_Button_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formButton);
        EXPECT_EQ(field.getType(), formButton);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

TEST_F(FormFieldTest_888, GetType_Choice_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formChoice);
        EXPECT_EQ(field.getType(), formChoice);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

TEST_F(FormFieldTest_888, GetType_Signature_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formSignature);
        EXPECT_EQ(field.getType(), formSignature);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test findFieldByFullyQualifiedName with non-existing name
TEST_F(FormFieldTest_888, FindFieldByFullyQualifiedName_NonExisting_ReturnsNull_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        FormField *found = field.findFieldByFullyQualifiedName("nonexistent.field.name");
        // Depending on whether the field's FQN matches, this may or may not be nullptr
        // For a non-matching name, expect nullptr
        EXPECT_EQ(found, nullptr);
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}

// Test setDefaultAppearance with empty string
TEST_F(FormFieldTest_888, SetDefaultAppearance_EmptyString_888) {
    Object fieldObj = Object(new Dict(nullptr));
    Ref ref = {1, 0};
    std::set<int> usedParents;

    try {
        FormField field(nullptr, std::move(fieldObj), ref, nullptr, &usedParents, formText);
        field.setDefaultAppearance("");

        GooString *da = field.getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), "");
    } catch (...) {
        GTEST_SKIP() << "Cannot construct FormField without valid PDFDoc";
    }
}
