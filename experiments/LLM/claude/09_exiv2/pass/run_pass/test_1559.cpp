#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <set>
#include <map>

// Include the header for AsfVideo::GUIDTag
#include "exiv2/asfvideo.hpp"

using namespace Exiv2;
using byte = uint8_t;

class GUIDTagTest_1559 : public ::testing::Test {
protected:
    // Helper to create GUIDTag with specific values
    AsfVideo::GUIDTag makeTag(uint32_t d1, uint16_t d2, uint16_t d3, std::array<byte, 8> d4) {
        return AsfVideo::GUIDTag(d1, d2, d3, d4);
    }
};

// Test: Two identical GUIDTags should be equal
TEST_F(GUIDTagTest_1559, EqualTagsAreEqual_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_TRUE(tag1 == tag2);
}

// Test: Tags differing in data1 are not equal
TEST_F(GUIDTagTest_1559, DifferentData1NotEqual_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(2, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_FALSE(tag1 == tag2);
}

// Test: Tags differing in data2 are not equal
TEST_F(GUIDTagTest_1559, DifferentData2NotEqual_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 3, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_FALSE(tag1 == tag2);
}

// Test: Tags differing in data3 are not equal
TEST_F(GUIDTagTest_1559, DifferentData3NotEqual_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 4, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_FALSE(tag1 == tag2);
}

// Test: Tags differing in data4 are not equal
TEST_F(GUIDTagTest_1559, DifferentData4NotEqual_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 8});
    EXPECT_FALSE(tag1 == tag2);
}

// Test: operator< returns true when data1 is smaller
TEST_F(GUIDTagTest_1559, LessThanByData1_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(2, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< returns true when data1 equal but data2 is smaller
TEST_F(GUIDTagTest_1559, LessThanByData2_1559) {
    auto tag1 = makeTag(1, 1, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< returns true when data1, data2 equal but data3 is smaller
TEST_F(GUIDTagTest_1559, LessThanByData3_1559) {
    auto tag1 = makeTag(1, 2, 2, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< returns true when data1-3 equal but data4 is lexicographically smaller
TEST_F(GUIDTagTest_1559, LessThanByData4_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 8});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< is false for equal tags (irreflexivity)
TEST_F(GUIDTagTest_1559, LessThanIrreflexive_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    auto tag2 = makeTag(1, 2, 3, {0, 1, 2, 3, 4, 5, 6, 7});
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< with data4 differing at first byte
TEST_F(GUIDTagTest_1559, LessThanByData4FirstByte_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(1, 2, 3, {1, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: operator< with data4 differing in the middle
TEST_F(GUIDTagTest_1559, LessThanByData4MiddleByte_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 0, 0, 5, 0, 0, 0, 0});
    auto tag2 = makeTag(1, 2, 3, {0, 0, 0, 6, 0, 0, 0, 0});
    EXPECT_TRUE(tag1 < tag2);
}

// Test: All zero values
TEST_F(GUIDTagTest_1559, AllZeroValues_1559) {
    auto tag1 = makeTag(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 < tag2);
}

// Test: Maximum values
TEST_F(GUIDTagTest_1559, MaxValues_1559) {
    auto tag1 = makeTag(UINT32_MAX, UINT16_MAX, UINT16_MAX, {255, 255, 255, 255, 255, 255, 255, 255});
    auto tag2 = makeTag(UINT32_MAX, UINT16_MAX, UINT16_MAX, {255, 255, 255, 255, 255, 255, 255, 255});
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_FALSE(tag1 < tag2);
}

// Test: Zero less than max
TEST_F(GUIDTagTest_1559, ZeroLessThanMax_1559) {
    auto tag1 = makeTag(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(UINT32_MAX, UINT16_MAX, UINT16_MAX, {255, 255, 255, 255, 255, 255, 255, 255});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
    EXPECT_FALSE(tag1 == tag2);
}

// Test: GUIDTag can be used in std::set (requires operator<)
TEST_F(GUIDTagTest_1559, UsableInStdSet_1559) {
    std::set<AsfVideo::GUIDTag> tagSet;
    auto tag1 = makeTag(1, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(2, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag3 = makeTag(1, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}); // duplicate of tag1

    tagSet.insert(tag1);
    tagSet.insert(tag2);
    tagSet.insert(tag3);

    EXPECT_EQ(tagSet.size(), 2u);
}

// Test: GUIDTag can be used as a map key
TEST_F(GUIDTagTest_1559, UsableAsMapKey_1559) {
    std::map<AsfVideo::GUIDTag, int> tagMap;
    auto tag1 = makeTag(10, 20, 30, {1, 2, 3, 4, 5, 6, 7, 8});
    auto tag2 = makeTag(10, 20, 30, {1, 2, 3, 4, 5, 6, 7, 9});

    tagMap[tag1] = 100;
    tagMap[tag2] = 200;

    EXPECT_EQ(tagMap[tag1], 100);
    EXPECT_EQ(tagMap[tag2], 200);
    EXPECT_EQ(tagMap.size(), 2u);
}

// Test: to_string returns a non-empty string
TEST_F(GUIDTagTest_1559, ToStringReturnsNonEmpty_1559) {
    auto tag = makeTag(0x12345678, 0xABCD, 0xEF01, {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF});
    std::string result = tag.to_string();
    EXPECT_FALSE(result.empty());
}

// Test: to_string of identical tags should produce identical strings
TEST_F(GUIDTagTest_1559, ToStringConsistent_1559) {
    auto tag1 = makeTag(0x12345678, 0xABCD, 0xEF01, {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF});
    auto tag2 = makeTag(0x12345678, 0xABCD, 0xEF01, {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF});
    EXPECT_EQ(tag1.to_string(), tag2.to_string());
}

// Test: to_string of different tags should produce different strings
TEST_F(GUIDTagTest_1559, ToStringDifferentForDifferentTags_1559) {
    auto tag1 = makeTag(1, 2, 3, {4, 5, 6, 7, 8, 9, 10, 11});
    auto tag2 = makeTag(11, 10, 9, {8, 7, 6, 5, 4, 3, 2, 1});
    EXPECT_NE(tag1.to_string(), tag2.to_string());
}

// Test: Construction from bytes
TEST_F(GUIDTagTest_1559, ConstructFromBytes_1559) {
    // A GUID is 16 bytes: data1 (4), data2 (2), data3 (2), data4 (8)
    uint8_t bytes[16] = {
        0x78, 0x56, 0x34, 0x12, // data1 = 0x12345678 (little-endian)
        0xCD, 0xAB,             // data2 = 0xABCD (little-endian)
        0x01, 0xEF,             // data3 = 0xEF01 (little-endian)
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF  // data4
    };
    AsfVideo::GUIDTag tag(bytes);
    // We can at least verify it doesn't crash and produces a string
    std::string result = tag.to_string();
    EXPECT_FALSE(result.empty());
}

// Test: Transitivity of operator<
TEST_F(GUIDTagTest_1559, LessThanTransitivity_1559) {
    auto tag1 = makeTag(1, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(2, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag3 = makeTag(3, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_TRUE(tag2 < tag3);
    EXPECT_TRUE(tag1 < tag3);
}

// Test: Antisymmetry of operator<
TEST_F(GUIDTagTest_1559, LessThanAntisymmetry_1559) {
    auto tag1 = makeTag(5, 10, 15, {1, 2, 3, 4, 5, 6, 7, 8});
    auto tag2 = makeTag(5, 10, 15, {1, 2, 3, 4, 5, 6, 7, 9});
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: data1 takes priority over data2 in ordering
TEST_F(GUIDTagTest_1559, Data1PriorityOverData2_1559) {
    auto tag1 = makeTag(2, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(1, 65535, 65535, {255, 255, 255, 255, 255, 255, 255, 255});
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_TRUE(tag2 < tag1);
}

// Test: data2 takes priority over data3 in ordering
TEST_F(GUIDTagTest_1559, Data2PriorityOverData3_1559) {
    auto tag1 = makeTag(1, 2, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(1, 1, 65535, {255, 255, 255, 255, 255, 255, 255, 255});
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_TRUE(tag2 < tag1);
}

// Test: data3 takes priority over data4 in ordering
TEST_F(GUIDTagTest_1559, Data3PriorityOverData4_1559) {
    auto tag1 = makeTag(1, 2, 3, {0, 0, 0, 0, 0, 0, 0, 0});
    auto tag2 = makeTag(1, 2, 2, {255, 255, 255, 255, 255, 255, 255, 255});
    EXPECT_FALSE(tag1 < tag2);
    EXPECT_TRUE(tag2 < tag1);
}

// Test: Equality is symmetric
TEST_F(GUIDTagTest_1559, EqualityIsSymmetric_1559) {
    auto tag1 = makeTag(42, 43, 44, {1, 2, 3, 4, 5, 6, 7, 8});
    auto tag2 = makeTag(42, 43, 44, {1, 2, 3, 4, 5, 6, 7, 8});
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_TRUE(tag2 == tag1);
}

// Test: to_string for zero tag
TEST_F(GUIDTagTest_1559, ToStringZeroTag_1559) {
    auto tag = makeTag(0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0});
    std::string result = tag.to_string();
    EXPECT_FALSE(result.empty());
}
