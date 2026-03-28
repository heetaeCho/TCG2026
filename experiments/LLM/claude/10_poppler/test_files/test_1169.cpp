#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

// We need to include the header for GfxCIDFont
// Based on the provided interface, we test getCIDToGID() which returns a const reference to a vector<int>

#include "poppler/GfxFont.h"

// Since GfxCIDFont requires complex construction (Dict*, fontDict, etc.),
// and we cannot easily construct one without the full Poppler infrastructure,
// we focus on testing the observable behavior through the public interface.
// However, given the complexity of constructing GfxCIDFont objects (requiring
// Dict*, Ref, etc.), we may need to work with what's available.

// For these tests, we attempt to create GfxCIDFont objects if possible,
// or test the interface contract through available means.

// Note: Since GfxCIDFont construction requires Poppler internals (Dict*, etc.),
// we test what we can observe. If we cannot construct the object easily,
// we verify the interface contract with minimal assumptions.

#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

class GfxCIDFontTest_1169 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getCIDToGID returns a valid reference (empty vector for a default/minimal font)
TEST_F(GfxCIDFontTest_1169, GetCIDToGIDReturnsVectorReference_1169) {
    // We need to construct a minimal GfxCIDFont. This requires a Dict.
    // Create a minimal font dictionary
    auto xref = std::make_unique<XRef>();
    Dict *fontDict = new Dict(xref.get());
    
    // Set up minimal required entries for a CID font
    fontDict->add("Type", Object(objName, "Font"));
    fontDict->add("Subtype", Object(objName, "CIDFontType2"));
    fontDict->add("BaseFont", Object(objName, "TestFont"));
    
    // Create a CIDSystemInfo dict
    Dict *cidSystemInfo = new Dict(xref.get());
    cidSystemInfo->add("Registry", Object(new GooString("Adobe")));
    cidSystemInfo->add("Ordering", Object(new GooString("Identity")));
    cidSystemInfo->add("Supplement", Object(0));
    fontDict->add("CIDSystemInfo", Object(cidSystemInfo));
    
    Ref id = { 1, 0 };
    Ref embFontID = Ref::INVALID();
    
    // Attempt to construct GfxCIDFont - this may or may not succeed depending on
    // the internal validation
    GfxCIDFont font(nullptr, id, std::optional<std::string>("TestFont"),
                    fontCIDType2, embFontID, fontDict);
    
    // Test getCIDToGID returns a valid reference
    const std::vector<int> &cidToGID = font.getCIDToGID();
    
    // The vector should be a valid object (may be empty if no CIDToGIDMap was provided)
    // We just verify we can access it without crashing
    EXPECT_GE(cidToGID.size(), 0u);
}

// Test that getCIDToGIDLen matches the size of getCIDToGID vector
TEST_F(GfxCIDFontTest_1169, GetCIDToGIDLenMatchesVectorSize_1169) {
    auto xref = std::make_unique<XRef>();
    Dict *fontDict = new Dict(xref.get());
    
    fontDict->add("Type", Object(objName, "Font"));
    fontDict->add("Subtype", Object(objName, "CIDFontType2"));
    fontDict->add("BaseFont", Object(objName, "TestFont"));
    
    Dict *cidSystemInfo = new Dict(xref.get());
    cidSystemInfo->add("Registry", Object(new GooString("Adobe")));
    cidSystemInfo->add("Ordering", Object(new GooString("Identity")));
    cidSystemInfo->add("Supplement", Object(0));
    fontDict->add("CIDSystemInfo", Object(cidSystemInfo));
    
    Ref id = { 1, 0 };
    Ref embFontID = Ref::INVALID();
    
    GfxCIDFont font(nullptr, id, std::optional<std::string>("TestFont"),
                    fontCIDType2, embFontID, fontDict);
    
    const std::vector<int> &cidToGID = font.getCIDToGID();
    unsigned int len = font.getCIDToGIDLen();
    
    EXPECT_EQ(static_cast<unsigned int>(cidToGID.size()), len);
}

// Test that isCIDFont returns true for GfxCIDFont
TEST_F(GfxCIDFontTest_1169, IsCIDFontReturnsTrue_1169) {
    auto xref = std::make_unique<XRef>();
    Dict *fontDict = new Dict(xref.get());
    
    fontDict->add("Type", Object(objName, "Font"));
    fontDict->add("Subtype", Object(objName, "CIDFontType2"));
    fontDict->add("BaseFont", Object(objName, "TestFont"));
    
    Dict *cidSystemInfo = new Dict(xref.get());
    cidSystemInfo->add("Registry", Object(new GooString("Adobe")));
    cidSystemInfo->add("Ordering", Object(new GooString("Identity")));
    cidSystemInfo->add("Supplement", Object(0));
    fontDict->add("CIDSystemInfo", Object(cidSystemInfo));
    
    Ref id = { 1, 0 };
    Ref embFontID = Ref::INVALID();
    
    GfxCIDFont font(nullptr, id, std::optional<std::string>("TestFont"),
                    fontCIDType2, embFontID, fontDict);
    
    EXPECT_TRUE(font.isCIDFont());
}

// Test getCIDToGID returns empty vector when no CIDToGIDMap is provided
TEST_F(GfxCIDFontTest_1169, GetCIDToGIDEmptyWhenNoCIDToGIDMap_1169) {
    auto xref = std::make_unique<XRef>();
    Dict *fontDict = new Dict(xref.get());
    
    fontDict->add("Type", Object(objName, "Font"));
    fontDict->add("Subtype", Object(objName, "CIDFontType0"));
    fontDict->add("BaseFont", Object(objName, "TestCIDFont"));
    
    Dict *cidSystemInfo = new Dict(xref.get());
    cidSystemInfo->add("Registry", Object(new GooString("Adobe")));
    cidSystemInfo->add("Ordering", Object(new GooString("Japan1")));
    cidSystemInfo->add("Supplement", Object(0));
    fontDict->add("CIDSystemInfo", Object(cidSystemInfo));
    
    Ref id = { 2, 0 };
    Ref embFontID = Ref::INVALID();
    
    GfxCIDFont font(nullptr, id, std::optional<std::string>("TestCIDFont"),
                    fontCIDType0, embFontID, fontDict);
    
    const std::vector<int> &cidToGID = font.getCIDToGID();
    
    // Without a CIDToGIDMap entry, the mapping should be empty
    EXPECT_TRUE(cidToGID.empty());
    EXPECT_EQ(font.getCIDToGIDLen(), 0u);
}

// Test that getCIDToGID returns a consistent reference on multiple calls
TEST_F(GfxCIDFontTest_1169, GetCIDToGIDConsistentReference_1169) {
    auto xref = std::make_unique<XRef>();
    Dict *fontDict = new Dict(xref.get());
    
    fontDict->add("Type", Object(objName, "Font"));
    fontDict->add("Subtype", Object(objName, "CIDFontType2"));
    fontDict->add("BaseFont", Object(objName, "TestFont"));
    
    Dict *cidSystemInfo = new Dict(xref.get());
    cidSystemInfo->add("Registry", Object(new GooString("Adobe")));
    cidSystemInfo->add("Ordering", Object(new GooString("Identity")));
    cidSystemInfo->add("Supplement", Object(0));
    fontDict->add("CIDSystemInfo", Object(cidSystemInfo));
    
    Ref id = { 3, 0 };
    Ref embFontID = Ref::INVALID();
    
    GfxCIDFont font(nullptr, id, std::optional<std::string>("TestFont"),
                    fontCIDType2, embFontID, fontDict);
    
    const std::vector<int> &ref1 = font.getCIDToGID();
    const std::vector<int> &ref2 = font.getCIDToGID();
    
    // Both calls should return references to the same underlying vector
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1.size(), ref2.size());
}
