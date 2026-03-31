#include <gtest/gtest.h>
#include <vector>
#include <cstddef>

// Forward declarations and minimal definitions needed for testing
namespace YAML {
namespace detail {

struct node {
    int value;
    node() : value(0) {}
    node(int v) : value(v) {}
};

// We need the remove_idx template to be available
template <typename Key, typename Enable = void>
struct remove_idx {
    static bool remove(std::vector<node*>& sequence, const Key& key, std::size_t& seqSize) {
        if (static_cast<std::size_t>(key) >= seqSize) {
            return false;
        }
        // Remove the element at index 'key'
        sequence.erase(sequence.begin() + static_cast<std::size_t>(key));
        --seqSize;
        return true;
    }
};

// The function under test
template <typename Key>
static bool remove(std::vector<node*>& sequence, const Key& key, std::size_t& seqSize) {
    return key >= 0 ? remove_idx<std::size_t>::remove(
                          sequence, static_cast<std::size_t>(key), seqSize)
                    : false;
}

}  // namespace detail
}  // namespace YAML

class YamlRemoveTest_666 : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 5; i++) {
            nodes[i].value = i;
            sequence.push_back(&nodes[i]);
        }
        seqSize = 5;
    }

    YAML::detail::node nodes[5];
    std::vector<YAML::detail::node*> sequence;
    std::size_t seqSize;
};

// Test: Removing with a negative key should return false and not modify the sequence
TEST_F(YamlRemoveTest_666, NegativeKeyReturnsFalse_666) {
    int key = -1;
    std::size_t originalSize = seqSize;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, originalSize);
    EXPECT_EQ(sequence.size(), originalSize);
}

// Test: Removing with a valid zero index should succeed
TEST_F(YamlRemoveTest_666, RemoveAtIndexZero_666) {
    int key = 0;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(seqSize, 4u);
    EXPECT_EQ(sequence.size(), 4u);
}

// Test: Removing at the last valid index should succeed
TEST_F(YamlRemoveTest_666, RemoveAtLastIndex_666) {
    int key = 4;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(seqSize, 4u);
    EXPECT_EQ(sequence.size(), 4u);
}

// Test: Removing at an index equal to seqSize (out of bounds) should return false
TEST_F(YamlRemoveTest_666, RemoveAtOutOfBoundsIndex_666) {
    int key = 5;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
    EXPECT_EQ(sequence.size(), 5u);
}

// Test: Removing at an index far beyond seqSize should return false
TEST_F(YamlRemoveTest_666, RemoveAtFarOutOfBoundsIndex_666) {
    int key = 100;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
}

// Test: Removing from an empty sequence should return false
TEST_F(YamlRemoveTest_666, RemoveFromEmptySequence_666) {
    std::vector<YAML::detail::node*> emptySeq;
    std::size_t emptySize = 0;
    int key = 0;
    bool result = YAML::detail::remove(emptySeq, key, emptySize);
    EXPECT_FALSE(result);
    EXPECT_EQ(emptySize, 0u);
}

// Test: Removing with a very negative key should return false
TEST_F(YamlRemoveTest_666, VeryNegativeKeyReturnsFalse_666) {
    int key = -1000;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
}

// Test: Removing a middle element should succeed and reduce size
TEST_F(YamlRemoveTest_666, RemoveMiddleElement_666) {
    int key = 2;
    YAML::detail::node* expectedAfter = sequence[3];
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(seqSize, 4u);
    EXPECT_EQ(sequence.size(), 4u);
    // The element that was at index 3 should now be at index 2
    EXPECT_EQ(sequence[2], expectedAfter);
}

// Test: Successive removals should work correctly
TEST_F(YamlRemoveTest_666, SuccessiveRemovals_666) {
    int key = 0;
    bool result1 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result1);
    EXPECT_EQ(seqSize, 4u);

    bool result2 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result2);
    EXPECT_EQ(seqSize, 3u);

    bool result3 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result3);
    EXPECT_EQ(seqSize, 2u);

    bool result4 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result4);
    EXPECT_EQ(seqSize, 1u);

    bool result5 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result5);
    EXPECT_EQ(seqSize, 0u);

    // Now sequence is empty, removal should fail
    bool result6 = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result6);
    EXPECT_EQ(seqSize, 0u);
}

// Test: Using size_t key type (non-negative by nature)
TEST_F(YamlRemoveTest_666, SizeTKeyTypeValidIndex_666) {
    std::size_t key = 2;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(seqSize, 4u);
}

// Test: Using size_t key type with out of bounds index
TEST_F(YamlRemoveTest_666, SizeTKeyTypeOutOfBounds_666) {
    std::size_t key = 10;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
}

// Test: Single element sequence - remove the only element
TEST_F(YamlRemoveTest_666, SingleElementSequenceRemove_666) {
    YAML::detail::node singleNode(42);
    std::vector<YAML::detail::node*> singleSeq;
    singleSeq.push_back(&singleNode);
    std::size_t singleSize = 1;

    int key = 0;
    bool result = YAML::detail::remove(singleSeq, key, singleSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(singleSize, 0u);
    EXPECT_TRUE(singleSeq.empty());
}

// Test: Key exactly at boundary (seqSize - 1)
TEST_F(YamlRemoveTest_666, KeyAtBoundary_666) {
    int key = static_cast<int>(seqSize - 1);
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_TRUE(result);
    EXPECT_EQ(seqSize, 4u);
}

// Test: Key exactly at seqSize (one past last valid)
TEST_F(YamlRemoveTest_666, KeyOnePasstBoundary_666) {
    int key = static_cast<int>(seqSize);
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
}

// Test: Negative key -1 specifically
TEST_F(YamlRemoveTest_666, NegativeKeyMinusOne_666) {
    int key = -1;
    bool result = YAML::detail::remove(sequence, key, seqSize);
    EXPECT_FALSE(result);
    EXPECT_EQ(seqSize, 5u);
    EXPECT_EQ(sequence.size(), 5u);
}
