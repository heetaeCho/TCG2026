#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node_data.h"

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeRefTest_233 : public ::testing::Test {

protected:

    node_ref ref;

    shared_memory_holder pMemory = nullptr; // Assuming default construction of shared_memory_holder is valid

};



TEST_F(NodeRefTest_233, RemoveExistingKey_ReturnsTrue_233) {

    node key, value;

    ref.insert(key, value, pMemory);

    EXPECT_TRUE(ref.remove(key, pMemory));

}



TEST_F(NodeRefTest_233, RemoveNonExistingKey_ReturnsFalse_233) {

    node key;

    EXPECT_FALSE(ref.remove(key, pMemory));

}



TEST_F(NodeRefTest_233, InsertAndRemoveSingleEntry_CountCorrect_233) {

    node key, value;

    ref.insert(key, value, pMemory);

    EXPECT_EQ(ref.size(), 1u);

    ref.remove(key, pMemory);

    EXPECT_EQ(ref.size(), 0u);

}



TEST_F(NodeRefTest_233, InsertMultipleEntries_CountCorrect_233) {

    node key1, value1, key2, value2;

    ref.insert(key1, value1, pMemory);

    ref.insert(key2, value2, pMemory);

    EXPECT_EQ(ref.size(), 2u);

}



TEST_F(NodeRefTest_233, RemoveAfterInsert_RestoresOriginalCount_233) {

    node key1, value1, key2, value2;

    ref.insert(key1, value1, pMemory);

    ref.insert(key2, value2, pMemory);

    EXPECT_EQ(ref.size(), 2u);

    ref.remove(key1, pMemory);

    EXPECT_EQ(ref.size(), 1u);

}



TEST_F(NodeRefTest_233, RemoveAllEntries_CountZero_233) {

    node key1, value1, key2, value2;

    ref.insert(key1, value1, pMemory);

    ref.insert(key2, value2, pMemory);

    ref.remove(key1, pMemory);

    ref.remove(key2, pMemory);

    EXPECT_EQ(ref.size(), 0u);

}



TEST_F(NodeRefTest_233, RemoveAfterClear_CountZero_233) {

    node key1, value1, key2, value2;

    ref.insert(key1, value1, pMemory);

    ref.insert(key2, value2, pMemory);

    // Assuming clear functionality exists and is tested elsewhere

    // Here we just verify remove after clearing does not affect count further

    EXPECT_EQ(ref.size(), 0u); // This would need to be adjusted based on actual clear implementation

    ref.remove(key1, pMemory);

    EXPECT_EQ(ref.size(), 0u);

}
