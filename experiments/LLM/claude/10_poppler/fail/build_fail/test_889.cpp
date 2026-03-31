#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <set>
#include <vector>

#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "goo/GooString.h"

// Helper to create a minimal PDFDoc for testing purposes
// Since we can't easily construct FormField without a PDFDoc and valid Object,
// we need to work within the constraints of the available constructors.

class FormFieldTest_889 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll attempt to create FormField objects where possible.
        // Since FormField requires a PDFDoc, Object, Ref, and parent,
        // and those are complex to set up, we test what we can through
        // the public interface.
    }

    void TearDown() override {
    }

    // Helper to create a test PDFDoc from a minimal PDF file if available
    // For unit testing, we may need to create objects carefully.
};

// Test that getMappingName returns nullptr when no mapping name is set
// This tests the basic accessor for mappingName
TEST_F(FormFieldTest_889, GetMappingNameReturnsNullWhenNotSet_889) {
    // We need a valid FormField to test. Since construction requires
    // PDFDoc and Objects, we'll try to create one with minimal setup.
    // If we can't construct one easily, we test the interface contract.

    // Create a minimal PDF in memory for testing
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Try to open a PDFDoc from memory
    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        // Create a simple field object (dictionary with minimal entries)
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("testfield")));

        Ref ref = {100, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        // getMappingName should return nullptr if TM key is not in the dict
        const GooString *mappingName = field->getMappingName();
        EXPECT_EQ(mappingName, nullptr);
    }
}

// Test getMappingName when mapping name is set in the field dictionary
TEST_F(FormFieldTest_889, GetMappingNameReturnsValueWhenSet_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("testfield")));
        fieldObj.dictSet("TM", Object(new GooString("MyMappingName")));

        Ref ref = {101, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *mappingName = field->getMappingName();
        ASSERT_NE(mappingName, nullptr);
        EXPECT_STREQ(mappingName->c_str(), "MyMappingName");
    }
}

// Test getPartialName
TEST_F(FormFieldTest_889, GetPartialNameReturnsCorrectValue_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("partialFieldName")));

        Ref ref = {102, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *partialName = field->getPartialName();
        ASSERT_NE(partialName, nullptr);
        EXPECT_STREQ(partialName->c_str(), "partialFieldName");
    }
}

// Test setPartialName changes the partial name
TEST_F(FormFieldTest_889, SetPartialNameUpdatesValue_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("oldName")));

        Ref ref = {103, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        GooString newName("newPartialName");
        field->setPartialName(newName);

        const GooString *partialName = field->getPartialName();
        ASSERT_NE(partialName, nullptr);
        EXPECT_STREQ(partialName->c_str(), "newPartialName");
    }
}

// Test isReadOnly and setReadOnly
TEST_F(FormFieldTest_889, ReadOnlyDefaultAndSet_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("roField")));

        Ref ref = {104, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        // Without Ff flag set, readOnly should be false by default
        EXPECT_FALSE(field->isReadOnly());

        field->setReadOnly(true);
        EXPECT_TRUE(field->isReadOnly());

        field->setReadOnly(false);
        EXPECT_FALSE(field->isReadOnly());
    }
}

// Test getType returns the type passed during construction
TEST_F(FormFieldTest_889, GetTypeReturnsConstructedType_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("typeField")));

        Ref ref = {105, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        EXPECT_EQ(field->getType(), formText);
    }
}

// Test getRef returns the ref passed during construction
TEST_F(FormFieldTest_889, GetRefReturnsConstructedRef_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("refField")));

        Ref ref = {106, 2};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formButton);

        Ref returnedRef = field->getRef();
        EXPECT_EQ(returnedRef.num, 106);
        EXPECT_EQ(returnedRef.gen, 2);
    }
}

// Test standAlone getter and setter
TEST_F(FormFieldTest_889, StandAloneGetterSetter_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("saField")));

        Ref ref = {107, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        field->setStandAlone(true);
        EXPECT_TRUE(field->isStandAlone());

        field->setStandAlone(false);
        EXPECT_FALSE(field->isStandAlone());
    }
}

// Test getNumWidgets for a field with no widgets (terminal field without widget annotations)
TEST_F(FormFieldTest_889, GetNumWidgetsForFieldWithNoWidgets_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("widgetField")));

        Ref ref = {108, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        // Number of widgets should be non-negative
        EXPECT_GE(field->getNumWidgets(), 0);
    }
}

// Test setDefaultAppearance and getDefaultAppearance
TEST_F(FormFieldTest_889, SetAndGetDefaultAppearance_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("daField")));

        Ref ref = {109, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        std::string appearance = "/Helv 12 Tf 0 g";
        field->setDefaultAppearance(appearance);

        GooString *da = field->getDefaultAppearance();
        ASSERT_NE(da, nullptr);
        EXPECT_STREQ(da->c_str(), "/Helv 12 Tf 0 g");
    }
}

// Test getAlternateUiName when TU key is set
TEST_F(FormFieldTest_889, GetAlternateUiNameWhenSet_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("tuField")));
        fieldObj.dictSet("TU", Object(new GooString("Tooltip Text")));

        Ref ref = {110, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *altName = field->getAlternateUiName();
        ASSERT_NE(altName, nullptr);
        EXPECT_STREQ(altName->c_str(), "Tooltip Text");
    }
}

// Test getAlternateUiName returns nullptr when TU key is not set
TEST_F(FormFieldTest_889, GetAlternateUiNameReturnsNullWhenNotSet_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("noTuField")));

        Ref ref = {111, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *altName = field->getAlternateUiName();
        EXPECT_EQ(altName, nullptr);
    }
}

// Test getNumChildren for a field with no children
TEST_F(FormFieldTest_889, GetNumChildrenForLeafField_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("leafField")));

        Ref ref = {112, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        EXPECT_GE(field->getNumChildren(), 0);
    }
}

// Test getFullyQualifiedName
TEST_F(FormFieldTest_889, GetFullyQualifiedNameForSimpleField_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("fqnField")));

        Ref ref = {113, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *fqn = field->getFullyQualifiedName();
        // For a field without parent, FQN should equal the partial name
        ASSERT_NE(fqn, nullptr);
        EXPECT_STREQ(fqn->c_str(), "fqnField");
    }
}

// Test getMappingName with empty string
TEST_F(FormFieldTest_889, GetMappingNameWithEmptyString_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("emptyTMField")));
        fieldObj.dictSet("TM", Object(new GooString("")));

        Ref ref = {114, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        const GooString *mappingName = field->getMappingName();
        // Should return a GooString even if it's empty
        ASSERT_NE(mappingName, nullptr);
        EXPECT_STREQ(mappingName->c_str(), "");
    }
}

// Test getObj returns non-null
TEST_F(FormFieldTest_889, GetObjReturnsNonNull_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("objField")));

        Ref ref = {115, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        Object *obj = field->getObj();
        ASSERT_NE(obj, nullptr);
        EXPECT_TRUE(obj->isDict());
    }
}

// Test findWidgetByRef returns nullptr for non-existent ref
TEST_F(FormFieldTest_889, FindWidgetByRefReturnsNullForNonExistent_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("findWidgetField")));

        Ref ref = {116, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        Ref searchRef = {999, 0};
        FormWidget *widget = field->findWidgetByRef(searchRef);
        EXPECT_EQ(widget, nullptr);
    }
}

// Test findFieldByRef returns nullptr for non-existent ref
TEST_F(FormFieldTest_889, FindFieldByRefReturnsNullForNonExistent_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("findFieldByRefField")));

        Ref ref = {117, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        Ref searchRef = {998, 0};
        FormField *found = field->findFieldByRef(searchRef);
        EXPECT_EQ(found, nullptr);
    }
}

// Test findFieldByRef returns the field itself when ref matches
TEST_F(FormFieldTest_889, FindFieldByRefReturnsSelfWhenMatching_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("selfRefField")));

        Ref ref = {118, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        FormField *found = field->findFieldByRef(ref);
        EXPECT_EQ(found, field.get());
    }
}

// Test getNoExport default value
TEST_F(FormFieldTest_889, GetNoExportDefaultValue_889) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Object fieldObj = Object(new Dict(doc->getXRef()));
        fieldObj.dictSet("T", Object(new GooString("noExportField")));

        Ref ref = {119, 0};
        std::set<int> usedParents;

        auto field = std::make_unique<FormField>(doc.get(), std::move(fieldObj), ref, nullptr, &usedParents, formText);

        // Without NoExport flag, should be false by default
        EXPECT_FALSE(field->getNoExport());
    }
}
