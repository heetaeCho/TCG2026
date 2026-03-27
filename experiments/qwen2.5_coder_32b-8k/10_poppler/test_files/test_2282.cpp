#include <gtest/gtest.h>

#include "CairoOutputDev.h"



using namespace poppler;



TEST(StructParentsMcidHashTest_2282, NormalOperation_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {10, 20};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, (10 << 16 | 20));

}



TEST(StructParentsMcidHashTest_2282, BoundaryConditions_ZeroValues_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {0, 0};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, 0);

}



TEST(StructParentsMcidHashTest_2282, BoundaryConditions_MaxValues_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {65535, 65535};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, (65535 << 16 | 65535));

}



TEST(StructParentsMcidHashTest_2282, BoundaryConditions_MaxFirstValue_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {65535, 0};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, (65535 << 16));

}



TEST(StructParentsMcidHashTest_2282, BoundaryConditions_MaxSecondValue_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {0, 65535};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, 65535);

}



TEST(StructParentsMcidHashTest_2282, BoundaryConditions_NegativeValues_2282) {

    StructParentsMcidHash hasher;

    std::pair<int, int> key = {-1, -1};

    size_t hash_value = hasher(key);

    EXPECT_EQ(hash_value, (static_cast<size_t>(-1) << 16 | static_cast<size_t>(-1)));

}
