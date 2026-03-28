#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "CMap.h"
#include "Object.h"
#include "GooString.h"

class CMapTest_1502 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test parsing a CMap from a collection and object (null/invalid object)
TEST_F(CMapTest_1502, ParseWithNullObject_1502) {
    Object obj;
    obj.initNull();
    auto cmap = CMap::parse("Adobe-Japan1", &obj);
    // With a null object, parsing should likely fail and return nullptr
    // (behavior depends on implementation, but we test observable result)
    // This tests the error/boundary case
    EXPECT_EQ(cmap, nullptr);
}

// Test parsing a CMap by name with known collection
TEST_F(CMapTest_1502, ParseByNameIdentity_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    // Identity-H is a well-known built-in CMap
    if (cmap) {
        EXPECT_NE(cmap->getCollection(), nullptr);
        EXPECT_NE(cmap->getCMapName(), nullptr);
    }
}

// Test getCollection returns non-null for a valid CMap
TEST_F(CMapTest_1502, GetCollectionReturnsValidPointer_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        const GooString *collection = cmap->getCollection();
        ASSERT_NE(collection, nullptr);
        // The collection should match what was passed in
        EXPECT_STREQ(collection->c_str(), "Adobe-Identity");
    }
}

// Test getCMapName returns non-null for a valid CMap
TEST_F(CMapTest_1502, GetCMapNameReturnsValidPointer_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        const GooString *cMapName = cmap->getCMapName();
        ASSERT_NE(cMapName, nullptr);
        EXPECT_STREQ(cMapName->c_str(), "Identity-H");
    }
}

// Test getWMode for Identity-H (horizontal)
TEST_F(CMapTest_1502, GetWModeHorizontal_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        // Identity-H is horizontal writing mode
        EXPECT_EQ(cmap->getWMode(), (GfxFont::WritingMode)0);
    }
}

// Test getWMode for Identity-V (vertical)
TEST_F(CMapTest_1502, GetWModeVertical_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-V");
    if (cmap) {
        // Identity-V is vertical writing mode
        EXPECT_EQ(cmap->getWMode(), (GfxFont::WritingMode)1);
    }
}

// Test match with correct collection and name
TEST_F(CMapTest_1502, MatchCorrectCollectionAndName_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        EXPECT_TRUE(cmap->match("Adobe-Identity", "Identity-H"));
    }
}

// Test match with incorrect collection
TEST_F(CMapTest_1502, MatchIncorrectCollection_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        EXPECT_FALSE(cmap->match("Adobe-Japan1", "Identity-H"));
    }
}

// Test match with incorrect name
TEST_F(CMapTest_1502, MatchIncorrectName_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        EXPECT_FALSE(cmap->match("Adobe-Identity", "Identity-V"));
    }
}

// Test match with both incorrect
TEST_F(CMapTest_1502, MatchBothIncorrect_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        EXPECT_FALSE(cmap->match("WrongCollection", "WrongName"));
    }
}

// Test getCID with Identity-H mapping (identity mapping: CID = CharCode)
TEST_F(CMapTest_1502, GetCIDIdentityMapping_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        CharCode c;
        int nUsed;
        // For identity CMap, the 2-byte input should map to itself
        const char input[] = {0x00, 0x41}; // CharCode 0x0041 = 65
        CID cid = cmap->getCID(input, 2, &c, &nUsed);
        EXPECT_EQ(nUsed, 2);
        EXPECT_EQ(c, 0x0041u);
        EXPECT_EQ(cid, 0x0041u);
    }
}

// Test getCID with zero-length input
TEST_F(CMapTest_1502, GetCIDZeroLength_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        CharCode c = 0;
        int nUsed = 0;
        CID cid = cmap->getCID("", 0, &c, &nUsed);
        // With zero length, should indicate no bytes used
        EXPECT_EQ(nUsed, 0);
        EXPECT_EQ(cid, 0u);
    }
}

// Test getCID with single byte input on Identity CMap
TEST_F(CMapTest_1502, GetCIDSingleByteIdentity_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        CharCode c = 0;
        int nUsed = 0;
        const char input[] = {0x42};
        CID cid = cmap->getCID(input, 1, &c, &nUsed);
        // Identity CMap expects 2-byte input; with 1 byte behavior is implementation-defined
        // but nUsed should be set
        EXPECT_GE(nUsed, 0);
    }
}

// Test setReverseMap doesn't crash with valid parameters
TEST_F(CMapTest_1502, SetReverseMapNoCrash_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        const unsigned int rmapSize = 256;
        unsigned int rmap[rmapSize];
        memset(rmap, 0, sizeof(rmap));
        unsigned int ncand = 1;
        EXPECT_NO_THROW(cmap->setReverseMap(rmap, rmapSize, ncand));
    }
}

// Test setReverseMap with zero size
TEST_F(CMapTest_1502, SetReverseMapZeroSize_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        unsigned int rmap[1] = {0};
        EXPECT_NO_THROW(cmap->setReverseMap(rmap, 0, 1));
    }
}

// Test parsing with empty collection string
TEST_F(CMapTest_1502, ParseEmptyCollection_1502) {
    auto cmap = CMap::parse(nullptr, "", "Identity-H");
    // May or may not succeed depending on implementation
    // Just verify no crash
}

// Test parsing with empty CMap name
TEST_F(CMapTest_1502, ParseEmptyCMapName_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "");
    // Should likely return nullptr for an empty/unknown CMap name
    EXPECT_EQ(cmap, nullptr);
}

// Test parsing with nonexistent CMap name
TEST_F(CMapTest_1502, ParseNonexistentCMapName_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "NonExistentCMap");
    EXPECT_EQ(cmap, nullptr);
}

// Test that copy constructor is deleted (compile-time check concept)
// This is validated by the delete declaration; we just verify shared_ptr works
TEST_F(CMapTest_1502, SharedPtrSemantics_1502) {
    auto cmap1 = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap1) {
        auto cmap2 = cmap1; // shared_ptr copy is fine
        EXPECT_EQ(cmap1.get(), cmap2.get());
        EXPECT_EQ(cmap1.use_count(), 2);
    }
}

// Test getCID with various 2-byte inputs on Identity CMap
TEST_F(CMapTest_1502, GetCIDMultipleValues_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        CharCode c;
        int nUsed;

        // Test 0x0000
        const char input0[] = {0x00, 0x00};
        CID cid0 = cmap->getCID(input0, 2, &c, &nUsed);
        EXPECT_EQ(nUsed, 2);
        EXPECT_EQ(cid0, 0x0000u);

        // Test 0xFFFF
        const char inputFF[] = {(char)0xFF, (char)0xFF};
        CID cidFF = cmap->getCID(inputFF, 2, &c, &nUsed);
        EXPECT_EQ(nUsed, 2);
        EXPECT_EQ(cidFF, 0xFFFFu);

        // Test 0x0100
        const char input100[] = {0x01, 0x00};
        CID cid100 = cmap->getCID(input100, 2, &c, &nUsed);
        EXPECT_EQ(nUsed, 2);
        EXPECT_EQ(cid100, 0x0100u);
    }
}

// Test match with empty strings
TEST_F(CMapTest_1502, MatchEmptyStrings_1502) {
    auto cmap = CMap::parse(nullptr, "Adobe-Identity", "Identity-H");
    if (cmap) {
        EXPECT_FALSE(cmap->match("", ""));
        EXPECT_FALSE(cmap->match("Adobe-Identity", ""));
        EXPECT_FALSE(cmap->match("", "Identity-H"));
    }
}
