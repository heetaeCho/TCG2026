#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "CMap.h"
#include "Object.h"
#include "GooString.h"

class CMapTest_1503 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test parsing a CMap from collection and name strings
TEST_F(CMapTest_1503, ParseFromCollectionAndName_1503) {
    // Try parsing a well-known CMap
    std::string collection = "Adobe-Japan1";
    std::string cMapName = "90ms-RKSJ-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    // The result depends on whether the CMap file exists in the system
    // We just verify the interface works without crashing
    if (cmap) {
        EXPECT_NE(cmap->getCMapName(), nullptr);
        EXPECT_NE(cmap->getCollection(), nullptr);
    }
}

// Test parsing a CMap from an Object
TEST_F(CMapTest_1503, ParseFromObject_1503) {
    Object obj;
    obj.initNull();
    std::string collection = "Adobe-Identity";
    
    auto cmap = CMap::parse(collection, &obj);
    // A null object should likely result in no valid CMap or a default one
    // Just ensure no crash
    SUCCEED();
}

// Test that getCMapName returns the name set during construction
TEST_F(CMapTest_1503, GetCMapNameReturnsName_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        const GooString *name = cmap->getCMapName();
        ASSERT_NE(name, nullptr);
        EXPECT_STREQ(name->c_str(), "Identity-H");
    }
}

// Test that getCollection returns the collection set during construction
TEST_F(CMapTest_1503, GetCollectionReturnsCollection_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        const GooString *coll = cmap->getCollection();
        ASSERT_NE(coll, nullptr);
        EXPECT_STREQ(coll->c_str(), "Adobe-Identity");
    }
}

// Test match function with matching collection and name
TEST_F(CMapTest_1503, MatchWithCorrectCollectionAndName_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        EXPECT_TRUE(cmap->match("Adobe-Identity", "Identity-H"));
    }
}

// Test match function with non-matching collection
TEST_F(CMapTest_1503, MatchWithWrongCollection_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        EXPECT_FALSE(cmap->match("Adobe-Japan1", "Identity-H"));
    }
}

// Test match function with non-matching name
TEST_F(CMapTest_1503, MatchWithWrongName_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        EXPECT_FALSE(cmap->match("Adobe-Identity", "Identity-V"));
    }
}

// Test match with both wrong
TEST_F(CMapTest_1503, MatchWithBothWrong_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        EXPECT_FALSE(cmap->match("Wrong-Collection", "Wrong-Name"));
    }
}

// Test getWMode for Identity-H (should be horizontal = 0)
TEST_F(CMapTest_1503, GetWModeHorizontal_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        // Identity-H should have horizontal writing mode
        EXPECT_EQ(static_cast<int>(cmap->getWMode()), 0);
    }
}

// Test getWMode for Identity-V (should be vertical = 1)
TEST_F(CMapTest_1503, GetWModeVertical_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-V";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        // Identity-V should have vertical writing mode
        EXPECT_EQ(static_cast<int>(cmap->getWMode()), 1);
    }
}

// Test getCID with Identity-H mapping (identity mapping: CID = character code)
TEST_F(CMapTest_1503, GetCIDIdentityMapping_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        CharCode c;
        int nUsed;
        const char testStr[] = {0x00, 0x41}; // character code 0x0041 = 65
        CID cid = cmap->getCID(testStr, 2, &c, &nUsed);
        // For identity mapping, CID should equal the character code
        EXPECT_EQ(cid, 0x0041);
        EXPECT_EQ(nUsed, 2);
    }
}

// Test getCID with single byte input
TEST_F(CMapTest_1503, GetCIDSingleByte_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        CharCode c;
        int nUsed;
        const char testStr[] = {0x42};
        CID cid = cmap->getCID(testStr, 1, &c, &nUsed);
        // Just verify it doesn't crash and nUsed is reasonable
        EXPECT_GE(nUsed, 1);
    }
}

// Test getCID with zero-length input
TEST_F(CMapTest_1503, GetCIDZeroLength_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        CharCode c;
        int nUsed;
        const char testStr[] = {0x00};
        CID cid = cmap->getCID(testStr, 0, &c, &nUsed);
        // With zero length, should handle gracefully
        EXPECT_GE(nUsed, 0);
    }
}

// Test setReverseMap doesn't crash
TEST_F(CMapTest_1503, SetReverseMapNoCrash_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        const unsigned int rmapSize = 256;
        unsigned int rmap[rmapSize];
        memset(rmap, 0, sizeof(rmap));
        // Should not crash
        cmap->setReverseMap(rmap, rmapSize, 1);
        SUCCEED();
    }
}

// Test parsing with empty collection string
TEST_F(CMapTest_1503, ParseEmptyCollection_1503) {
    std::string collection = "";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    // May or may not succeed, but should not crash
    SUCCEED();
}

// Test parsing with empty CMap name
TEST_F(CMapTest_1503, ParseEmptyCMapName_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    // May or may not succeed, but should not crash
    SUCCEED();
}

// Test that copy constructor is deleted (compile-time check; we just verify the shared_ptr works)
TEST_F(CMapTest_1503, SharedPtrSemantics_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap1 = CMap::parse(nullptr, collection, cMapName);
    if (cmap1) {
        auto cmap2 = cmap1; // shared_ptr copy is fine
        EXPECT_EQ(cmap1.get(), cmap2.get());
        EXPECT_EQ(cmap1.use_count(), 2);
    }
}

// Test match with empty strings
TEST_F(CMapTest_1503, MatchWithEmptyStrings_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        EXPECT_FALSE(cmap->match("", ""));
        EXPECT_FALSE(cmap->match("", "Identity-H"));
        EXPECT_FALSE(cmap->match("Adobe-Identity", ""));
    }
}

// Test getCID with high byte values
TEST_F(CMapTest_1503, GetCIDHighByteValues_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        CharCode c;
        int nUsed;
        const char testStr[] = {(char)0xFF, (char)0xFF};
        CID cid = cmap->getCID(testStr, 2, &c, &nUsed);
        // For identity mapping, should map to 0xFFFF
        EXPECT_EQ(cid, 0xFFFF);
        EXPECT_EQ(nUsed, 2);
    }
}

// Test getCID with null bytes
TEST_F(CMapTest_1503, GetCIDNullBytes_1503) {
    std::string collection = "Adobe-Identity";
    std::string cMapName = "Identity-H";
    
    auto cmap = CMap::parse(nullptr, collection, cMapName);
    if (cmap) {
        CharCode c;
        int nUsed;
        const char testStr[] = {0x00, 0x00};
        CID cid = cmap->getCID(testStr, 2, &c, &nUsed);
        // For identity mapping, CID 0 = notdef typically
        EXPECT_EQ(cid, 0x0000);
        EXPECT_EQ(nUsed, 2);
    }
}
