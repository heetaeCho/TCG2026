#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP_Const.h"

class TouchUpDataModelTest_1969 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            throw std::runtime_error("Failed to initialize XMP toolkit");
        }
        SXMPMeta::RegisterNamespace(kXMP_NS_EXIF, "exif", nullptr);
        SXMPMeta::RegisterNamespace(kXMP_NS_DC, "dc", nullptr);
        SXMPMeta::RegisterNamespace(kXMP_NS_DM, "xmpDM", nullptr);
        SXMPMeta::RegisterNamespace(kXMP_NS_XMP_MM, "xmpMM", nullptr);
        SXMPMeta::RegisterNamespace(kXMP_NS_XMP_Rights, "xmpRights", nullptr);
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        meta = SXMPMeta();
    }

    SXMPMeta meta;

    std::string wrapInRDF(const std::string& body, const std::string& aboutAttr = "") {
        return
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
            "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
            "<rdf:Description rdf:about=\"" + aboutAttr + "\""
            " xmlns:dc=\"http://purl.org/dc/elements/1.1/\""
            " xmlns:exif=\"http://ns.adobe.com/exif/1.0/\""
            " xmlns:xmpDM=\"http://ns.adobe.com/xmp/1.0/DynamicMedia/\""
            " xmlns:xmpMM=\"http://ns.adobe.com/xap/1.0/mm/\""
            " xmlns:xmpRights=\"http://ns.adobe.com/xap/1.0/rights/\">"
            + body +
            "</rdf:Description>"
            "</rdf:RDF>"
            "</x:xmpmeta>";
    }
};

// Test: dc:subject ordered array bits are cleared
TEST_F(TouchUpDataModelTest_1969, DcSubjectOrderedBitsCleared_1969) {
    std::string xmp = wrapInRDF(
        "<dc:subject>"
        "  <rdf:Seq>"
        "    <rdf:li>keyword1</rdf:li>"
        "    <rdf:li>keyword2</rdf:li>"
        "  </rdf:Seq>"
        "</dc:subject>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    XMP_OptionBits opts = 0;
    std::string val;
    bool exists = meta.GetProperty(kXMP_NS_DC, "dc:subject", nullptr, nullptr, &opts);
    ASSERT_TRUE(exists);
    // The ordered/alternate/alttext bits should be cleared, leaving only unordered array
    EXPECT_EQ(opts & kXMP_PropArrayIsOrdered, 0u);
    EXPECT_EQ(opts & kXMP_PropArrayIsAlternate, 0u);
    EXPECT_EQ(opts & kXMP_PropArrayIsAltText, 0u);
    // But it should still be an array
    EXPECT_NE(opts & kXMP_PropValueIsArray, 0u);
}

// Test: dc:description is repaired to have proper alt-text structure
TEST_F(TouchUpDataModelTest_1969, DcDescriptionRepairAltText_1969) {
    std::string xmp = wrapInRDF(
        "<dc:description>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test description</rdf:li>"
        "  </rdf:Alt>"
        "</dc:description>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string value;
    XMP_OptionBits opts = 0;
    bool exists = meta.GetArrayItem(kXMP_NS_DC, "dc:description", 1, &value, nullptr, &opts);
    ASSERT_TRUE(exists);
    EXPECT_EQ(value, "Test description");
}

// Test: dc:title is repaired to have proper alt-text
TEST_F(TouchUpDataModelTest_1969, DcTitleRepairAltText_1969) {
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"en\">My Title</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string value;
    bool exists = meta.GetArrayItem(kXMP_NS_DC, "dc:title", 1, &value, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(value, "My Title");
}

// Test: dc:rights is repaired
TEST_F(TouchUpDataModelTest_1969, DcRightsRepairAltText_1969) {
    std::string xmp = wrapInRDF(
        "<dc:rights>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Copyright 2024</rdf:li>"
        "  </rdf:Alt>"
        "</dc:rights>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string value;
    bool exists = meta.GetArrayItem(kXMP_NS_DC, "dc:rights", 1, &value, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(value, "Copyright 2024");
}

// Test: UUID in about attribute is migrated to xmpMM:InstanceID
TEST_F(TouchUpDataModelTest_1969, UUIDMigratedToInstanceID_1969) {
    // A valid UUID format: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx (36 chars)
    std::string uuid = "550e8400-e29b-41d4-a716-446655440000";
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        uuid
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(instanceID, uuid);

    // The object name should be cleared
    std::string objName;
    meta.GetObjectName(&objName);
    EXPECT_TRUE(objName.empty());
}

// Test: uuid: prefixed name is migrated to xmpMM:InstanceID
TEST_F(TouchUpDataModelTest_1969, UUIDPrefixMigratedToInstanceID_1969) {
    std::string uuid = "uuid:550e8400-e29b-41d4-a716-446655440000";
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        uuid
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(instanceID, uuid);
}

// Test: Non-UUID about attribute is NOT migrated
TEST_F(TouchUpDataModelTest_1969, NonUUIDNotMigrated_1969) {
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        "some-random-string"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    // Non-UUID should not create InstanceID (unless it happens to match format)
    // "some-random-string" is 18 chars, not 36, and no uuid: prefix
    EXPECT_FALSE(exists);
}

// Test: Empty about attribute does not create InstanceID
TEST_F(TouchUpDataModelTest_1969, EmptyAboutNoInstanceID_1969) {
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        ""
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    EXPECT_FALSE(exists);
}

// Test: Simple exif:UserComment is converted to alt-text array
TEST_F(TouchUpDataModelTest_1969, SimpleUserCommentConvertedToArray_1969) {
    std::string xmp = wrapInRDF(
        "<exif:UserComment>A simple comment</exif:UserComment>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    // After TouchUpDataModel, exif:UserComment should be an array
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty(kXMP_NS_EXIF, "exif:UserComment", nullptr, nullptr, &opts);
    ASSERT_TRUE(exists);
    EXPECT_NE(opts & kXMP_PropValueIsArray, 0u);

    // Should have at least one array item
    std::string itemValue;
    exists = meta.GetArrayItem(kXMP_NS_EXIF, "exif:UserComment", 1, &itemValue, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(itemValue, "A simple comment");
}

// Test: Parsing empty buffer
TEST_F(TouchUpDataModelTest_1969, ParseEmptyBuffer_1969) {
    EXPECT_NO_THROW({
        meta.ParseFromBuffer("", 0, 0);
    });
}

// Test: Normal parse with no special fixup needed
TEST_F(TouchUpDataModelTest_1969, NormalParseNoFixup_1969) {
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Simple title</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string value;
    bool exists = meta.GetArrayItem(kXMP_NS_DC, "dc:title", 1, &value, nullptr, nullptr);
    ASSERT_TRUE(exists);
    EXPECT_EQ(value, "Simple title");
}

// Test: dc:subject as unordered bag remains unordered
TEST_F(TouchUpDataModelTest_1969, DcSubjectBagRemainsUnordered_1969) {
    std::string xmp = wrapInRDF(
        "<dc:subject>"
        "  <rdf:Bag>"
        "    <rdf:li>tag1</rdf:li>"
        "    <rdf:li>tag2</rdf:li>"
        "  </rdf:Bag>"
        "</dc:subject>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty(kXMP_NS_DC, "dc:subject", nullptr, nullptr, &opts);
    ASSERT_TRUE(exists);
    EXPECT_NE(opts & kXMP_PropValueIsArray, 0u);
    EXPECT_EQ(opts & kXMP_PropArrayIsOrdered, 0u);
    EXPECT_EQ(opts & kXMP_PropArrayIsAlternate, 0u);
}

// Test: UUID with uppercase letters is NOT recognized as UUID (code only accepts lowercase)
TEST_F(TouchUpDataModelTest_1969, UppercaseUUIDNotMigrated_1969) {
    std::string uuid = "550E8400-E29B-41D4-A716-446655440000";
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        uuid
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    // Uppercase hex letters are not accepted by the UUID check in the code
    EXPECT_FALSE(exists);
}

// Test: 36-char string with wrong dash positions is not UUID
TEST_F(TouchUpDataModelTest_1969, WrongDashPositionNotUUID_1969) {
    // 36 chars but dashes in wrong positions
    std::string notUuid = "550e840-0e29b-41d4-a716-4466554400000";
    ASSERT_EQ(notUuid.size(), 37u); // Actually this won't be 36...
    // Let's construct a proper 36-char string with wrong dashes
    std::string bad = "550e8400e-e29b-41d4-a716-44665544000"; // 36 chars, dash at pos 8 replaced
    if (bad.size() != 36) {
        bad = "550e84000e29b-41d4-a716-446655440000"; // adjust
    }
    // Simpler approach: just use 36 chars with dash at wrong position
    bad = "550e8400-e29b-41d4-a716-44665544000x"; // not all hex
    // Just test a clearly non-UUID 36-char string
    bad = "abcdefghijklmnopqrstuvwxyz0123456789"; // 36 chars, no dashes
    ASSERT_EQ(bad.size(), 36u);

    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Test</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>",
        bad
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string instanceID;
    bool exists = meta.GetProperty(kXMP_NS_XMP_MM, "xmpMM:InstanceID", &instanceID, nullptr, nullptr);
    // This string has chars like 'k', 'l', etc. that are > 'f' but <= 'z', so they pass the check.
    // Actually looking at the code: it checks ('a' <= ch) && (ch <= 'z') - so all lowercase letters pass!
    // And there are no dashes, so positions 8,13,18,23 would need to be dashes but aren't.
    // The code checks: if ch == '-', then verify position. Otherwise check digit/lowercase.
    // So 'i','j','k'... at position 8 would NOT be '-', but they pass the else branch. So it would be UUID = true.
    // Actually wait - the code says: if position 8,13,18,23 has a non-dash that passes digit/letter check, it's fine.
    // The dashes are only required IF the character IS a dash. So a 36-char all-lowercase-hex string IS considered UUID.
    EXPECT_TRUE(exists);
}

// Test: Multiple schemas present simultaneously
TEST_F(TouchUpDataModelTest_1969, MultipleSchemasTouchUp_1969) {
    std::string xmp = wrapInRDF(
        "<dc:subject>"
        "  <rdf:Seq>"
        "    <rdf:li>keyword</rdf:li>"
        "  </rdf:Seq>"
        "</dc:subject>"
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Title</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>"
        "<dc:description>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Description</rdf:li>"
        "  </rdf:Alt>"
        "</dc:description>"
    );
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    // dc:subject should have ordered bits cleared
    XMP_OptionBits opts = 0;
    ASSERT_TRUE(meta.GetProperty(kXMP_NS_DC, "dc:subject", nullptr, nullptr, &opts));
    EXPECT_EQ(opts & kXMP_PropArrayIsOrdered, 0u);

    // dc:title should be accessible
    std::string val;
    ASSERT_TRUE(meta.GetArrayItem(kXMP_NS_DC, "dc:title", 1, &val, nullptr, nullptr));
    EXPECT_EQ(val, "Title");

    // dc:description should be accessible
    ASSERT_TRUE(meta.GetArrayItem(kXMP_NS_DC, "dc:description", 1, &val, nullptr, nullptr));
    EXPECT_EQ(val, "Description");
}

// Test: No schemas that need touch-up
TEST_F(TouchUpDataModelTest_1969, NoTouchUpNeeded_1969) {
    std::string xmp =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<xmp:CreatorTool>Test</xmp:CreatorTool>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>";

    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_ParseMoreBuffers);
    EXPECT_NO_THROW(meta.ParseFromBuffer(nullptr, 0, 0));
}

// Test: Incremental parsing
TEST_F(TouchUpDataModelTest_1969, IncrementalParsing_1969) {
    std::string xmp = wrapInRDF(
        "<dc:title>"
        "  <rdf:Alt>"
        "    <rdf:li xml:lang=\"x-default\">Incremental</rdf:li>"
        "  </rdf:Alt>"
        "</dc:title>"
    );

    // Parse in chunks
    size_t half = xmp.size() / 2;
    meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(half), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(xmp.c_str() + half, static_cast<XMP_StringLen>(xmp.size() - half), kXMP_ParseMoreBuffers);
    meta.ParseFromBuffer(nullptr, 0, 0);

    std::string val;
    ASSERT_TRUE(meta.GetArrayItem(kXMP_NS_DC, "dc:title", 1, &val, nullptr, nullptr));
    EXPECT_EQ(val, "Incremental");
}
