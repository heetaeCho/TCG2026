#include <gtest/gtest.h>

#include "tiffimage_int.hpp"



namespace Exiv2 {

namespace Internal {



struct TiffGroupKey {

    uint32_t first;

    uint32_t second;

};



}  // namespace Internal

}  // namespace Exiv2



using namespace Exiv2::Internal;



TEST(TiffGroupKeyHashTest_107, HashCombinesValuesProperly_107) {

    TiffGroupKey key = {0x12345678, 0x9ABCDEF0};

    TiffGroupKey_hash hasher;

    std::size_t hashValue = hasher(key);

    EXPECT_EQ(hashValue, std::hash<uint64_t>{}(static_cast<uint64_t>(key.first) << 32 | static_cast<uint64_t>(key.second)));

}



TEST(TiffGroupKeyHashTest_107, HashHandlesZeroValues_107) {

    TiffGroupKey key = {0, 0};

    TiffGroupKey_hash hasher;

    std::size_t hashValue = hasher(key);

    EXPECT_EQ(hashValue, std::hash<uint64_t>{}(static_cast<uint64_t>(key.first) << 32 | static_cast<uint64_t>(key.second)));

}



TEST(TiffGroupKeyHashTest_107, HashHandlesMaxValues_107) {

    TiffGroupKey key = {0xFFFFFFFF, 0xFFFFFFFF};

    TiffGroupKey_hash hasher;

    std::size_t hashValue = hasher(key);

    EXPECT_EQ(hashValue, std::hash<uint64_t>{}(static_cast<uint64_t>(key.first) << 32 | static_cast<uint64_t>(key.second)));

}



TEST(TiffGroupKeyHashTest_107, HashDifferentiatesKeysWithSameFirstPart_107) {

    TiffGroupKey key1 = {0x12345678, 0x9ABCDEF0};

    TiffGroupKey key2 = {0x12345678, 0x12345678};

    TiffGroupKey_hash hasher;

    std::size_t hashValue1 = hasher(key1);

    std::size_t hashValue2 = hasher(key2);

    EXPECT_NE(hashValue1, hashValue2);

}



TEST(TiffGroupKeyHashTest_107, HashDifferentiatesKeysWithSameSecondPart_107) {

    TiffGroupKey key1 = {0x12345678, 0x9ABCDEF0};

    TiffGroupKey key2 = {0x9ABCDEF0, 0x9ABCDEF0};

    TiffGroupKey_hash hasher;

    std::size_t hashValue1 = hasher(key1);

    std::size_t hashValue2 = hasher(key2);

    EXPECT_NE(hashValue1, hashValue2);

}
