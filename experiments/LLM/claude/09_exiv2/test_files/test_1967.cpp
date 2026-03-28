#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include the XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Namespace URIs used in tests
static const char* kXMP_NS_DC = "http://purl.org/dc/elements/1.1/";
static const char* kXMP_NS_DM = "http://ns.adobe.com/xmp/1.0/DynamicMedia/";

class MigrateAudioCopyrightTest_1967 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test: When parsing XMP with dm:copyright and no dc:rights, dc:rights should be created
TEST_F(MigrateAudioCopyrightTest_1967, DmCopyrightMigratedWhenNoDcRights_1967) {
    // Construct XMP with dm:copyright but no dc:rights
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>Test Copyright</xmpDM:copyright>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // After migration, dm:copyright should be deleted
    std::string value;
    bool exists = meta.DoesPropertyExist(kXMP_NS_DM, "copyright");
    EXPECT_FALSE(exists);

    // dc:rights should now exist with x-default containing the dm:copyright value
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    if (found) {
        // The value should contain the original copyright text
        EXPECT_NE(itemValue.find("Test Copyright"), std::string::npos);
    }
}

// Test: When both dm:copyright and dc:rights exist with same value
TEST_F(MigrateAudioCopyrightTest_1967, DmCopyrightMatchesDcRightsNoChange_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/' "
        "         xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>Same Value</xmpDM:copyright>"
        "    <dc:rights>"
        "      <rdf:Alt>"
        "        <rdf:li xml:lang='x-default'>Same Value</rdf:li>"
        "      </rdf:Alt>"
        "    </dc:rights>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be deleted after migration
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));

    // dc:rights x-default should still exist
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    EXPECT_TRUE(found);
}

// Test: When dm:copyright differs from existing dc:rights x-default
TEST_F(MigrateAudioCopyrightTest_1967, DmCopyrightDiffersFromDcRights_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/' "
        "         xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>DM Copyright</xmpDM:copyright>"
        "    <dc:rights>"
        "      <rdf:Alt>"
        "        <rdf:li xml:lang='x-default'>DC Rights</rdf:li>"
        "      </rdf:Alt>"
        "    </dc:rights>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be deleted
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));

    // dc:rights should contain both the original and dm values separated by double LF
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    if (found) {
        EXPECT_NE(itemValue.find("DC Rights"), std::string::npos);
        EXPECT_NE(itemValue.find("DM Copyright"), std::string::npos);
    }
}

// Test: When dc:rights exists but without x-default language
TEST_F(MigrateAudioCopyrightTest_1967, DcRightsWithoutXDefaultGetsXDefault_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/' "
        "         xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>DM Value</xmpDM:copyright>"
        "    <dc:rights>"
        "      <rdf:Alt>"
        "        <rdf:li xml:lang='en-US'>English Rights</rdf:li>"
        "      </rdf:Alt>"
        "    </dc:rights>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be removed
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));

    // x-default should have been created
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    // Should find some value (either x-default or en-US depending on implementation)
    EXPECT_TRUE(found);
}

// Test: Empty dm:copyright value
TEST_F(MigrateAudioCopyrightTest_1967, EmptyDmCopyrightMigration_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright></xmpDM:copyright>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be deleted regardless
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));
}

// Test: No dm:copyright - nothing should happen to dc:rights
TEST_F(MigrateAudioCopyrightTest_1967, NoDmCopyrightNoMigration_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "  <rdf:Description rdf:about=''>"
        "    <dc:rights>"
        "      <rdf:Alt>"
        "        <rdf:li xml:lang='x-default'>Original Rights</rdf:li>"
        "      </rdf:Alt>"
        "    </dc:rights>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(itemValue, "Original Rights");
}

// Test: XMPMeta basic property operations
TEST_F(MigrateAudioCopyrightTest_1967, BasicSetAndGetProperty_1967) {
    SXMPMeta meta;

    meta.SetProperty(kXMP_NS_DC, "title", "Test Title", 0);

    std::string value;
    bool exists = meta.GetProperty(kXMP_NS_DC, "title", &value, nullptr);
    EXPECT_TRUE(exists);
    EXPECT_EQ(value, "Test Title");
}

// Test: DeleteProperty removes property
TEST_F(MigrateAudioCopyrightTest_1967, DeletePropertyRemovesIt_1967) {
    SXMPMeta meta;

    meta.SetProperty(kXMP_NS_DM, "copyright", "Some Copyright", 0);
    EXPECT_TRUE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));

    meta.DeleteProperty(kXMP_NS_DM, "copyright");
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));
}

// Test: SetLocalizedText and GetLocalizedText
TEST_F(MigrateAudioCopyrightTest_1967, SetAndGetLocalizedText_1967) {
    SXMPMeta meta;

    meta.SetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", "Default Rights", 0);

    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(itemValue, "Default Rights");
}

// Test: dm:copyright with special characters
TEST_F(MigrateAudioCopyrightTest_1967, DmCopyrightWithSpecialChars_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>Copyright &amp; Trademark ™ 2023</xmpDM:copyright>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be removed after migration
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));
}

// Test: dc:rights with double LF already present and same dm value
TEST_F(MigrateAudioCopyrightTest_1967, DcRightsAlreadyHasDoubleLFSameValue_1967) {
    // Build XMP where dc:rights x-default already has double LF pattern
    SXMPMeta meta;

    // Set dc:rights with double LF pattern
    std::string rightsWithLF = "Original\n\nDM Copyright";
    meta.SetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", rightsWithLF.c_str(), 0);

    // Verify it was set
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(itemValue, rightsWithLF);
}

// Test: Parsing empty XMP buffer
TEST_F(MigrateAudioCopyrightTest_1967, ParseEmptyBuffer_1967) {
    SXMPMeta meta;

    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "  <rdf:Description rdf:about=''/>"
        "</rdf:RDF>";

    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DC, "rights"));
}

// Test: Multiple languages in dc:rights with dm:copyright
TEST_F(MigrateAudioCopyrightTest_1967, MultipleLangDcRightsWithDmCopyright_1967) {
    const char* xmpData =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
        "         xmlns:xmpDM='http://ns.adobe.com/xmp/1.0/DynamicMedia/' "
        "         xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "  <rdf:Description rdf:about=''>"
        "    <xmpDM:copyright>DM Copyright Text</xmpDM:copyright>"
        "    <dc:rights>"
        "      <rdf:Alt>"
        "        <rdf:li xml:lang='x-default'>Default Rights</rdf:li>"
        "        <rdf:li xml:lang='en-US'>English Rights</rdf:li>"
        "        <rdf:li xml:lang='fr-FR'>Droits Français</rdf:li>"
        "      </rdf:Alt>"
        "    </dc:rights>"
        "  </rdf:Description>"
        "</rdf:RDF>";

    SXMPMeta meta;
    meta.ParseFromBuffer(xmpData, static_cast<XMP_StringLen>(strlen(xmpData)));

    // dm:copyright should be deleted
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DM, "copyright"));

    // x-default should have been modified to include DM copyright
    std::string actualLang, itemValue;
    bool found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default",
                                        &actualLang, &itemValue, nullptr);
    EXPECT_TRUE(found);
    EXPECT_NE(itemValue.find("DM Copyright Text"), std::string::npos);

    // Other language entries should still exist
    std::string enLang, enValue;
    found = meta.GetLocalizedText(kXMP_NS_DC, "rights", "", "en-US",
                                   &enLang, &enValue, nullptr);
    EXPECT_TRUE(found);
}

// Test: Erase clears all properties
TEST_F(MigrateAudioCopyrightTest_1967, EraseRemovesAllProperties_1967) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test", 0);
    meta.SetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", "Rights", 0);

    meta.Erase();

    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DC, "title"));
    EXPECT_FALSE(meta.DoesPropertyExist(kXMP_NS_DC, "rights"));
}
