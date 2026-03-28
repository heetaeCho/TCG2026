#include <gtest/gtest.h>
#include <vector>
#include <cstddef>

// Forward declare/define minimal types needed
namespace YAML {
namespace detail {

// Minimal node type for testing
struct node {
    int value;
    node(int v = 0) : value(v) {}
};

// The function under test (copied from the provided implementation)
// Using size_t as the Key type based on the interface
static bool remove(std::vector<node*>& sequence, const std::size_t& key, std::size_t& seqSize) {
    if (key >= sequence.size()) {
        return false;
    } else {
        sequence.erase(sequence.begin() + key);
        if (seqSize > key) {
            --seqSize;
        }
        return true;
    }
}

}  // namespace detail
}  // namespace YAML

class RemoveTest_665 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create some nodes for testing
        for (int i = 0; i < 5; ++i) {
            nodes_.push_back(new YAML::detail::node(i));
            all_nodes_.push_back(nodes_.back());
        }
    }

    void TearDown() override {
        for (auto* n : all_nodes_) {
            delete n;
        }
    }

    std::vector<YAML::detail::node*> nodes_;
    std::vector<YAML::detail::node*> all_nodes_;  // Keep track of all allocated nodes
};

// Test removing an element from the beginning of the sequence
TEST_F(RemoveTest_665, RemoveFirstElement_665) {
    std::size_t seqSize = 5;
    std::size_t key = 0;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 4u);
    // The first element should now be what was previously the second
    EXPECT_EQ(nodes_[0]->value, 1);
}

// Test removing an element from the middle of the sequence
TEST_F(RemoveTest_665, RemoveMiddleElement_665) {
    std::size_t seqSize = 5;
    std::size_t key = 2;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 4u);
    // Elements after the removed one should shift down
    EXPECT_EQ(nodes_[0]->value, 0);
    EXPECT_EQ(nodes_[1]->value, 1);
    EXPECT_EQ(nodes_[2]->value, 3);
    EXPECT_EQ(nodes_[3]->value, 4);
}

// Test removing the last element of the sequence
TEST_F(RemoveTest_665, RemoveLastElement_665) {
    std::size_t seqSize = 5;
    std::size_t key = 4;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 4u);
}

// Test removing with key equal to sequence size (out of bounds)
TEST_F(RemoveTest_665, RemoveKeyEqualToSize_665) {
    std::size_t seqSize = 5;
    std::size_t key = 5;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_FALSE(result);
    EXPECT_EQ(nodes_.size(), 5u);
    EXPECT_EQ(seqSize, 5u);
}

// Test removing with key greater than sequence size (out of bounds)
TEST_F(RemoveTest_665, RemoveKeyGreaterThanSize_665) {
    std::size_t seqSize = 5;
    std::size_t key = 100;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_FALSE(result);
    EXPECT_EQ(nodes_.size(), 5u);
    EXPECT_EQ(seqSize, 5u);
}

// Test removing from an empty sequence
TEST_F(RemoveTest_665, RemoveFromEmptySequence_665) {
    std::vector<YAML::detail::node*> empty;
    std::size_t seqSize = 0;
    std::size_t key = 0;

    bool result = YAML::detail::remove(empty, key, seqSize);

    EXPECT_FALSE(result);
    EXPECT_EQ(empty.size(), 0u);
    EXPECT_EQ(seqSize, 0u);
}

// Test removing when seqSize is less than vector size
TEST_F(RemoveTest_665, RemoveWhenSeqSizeLessThanVectorSize_665) {
    std::size_t seqSize = 3;  // seqSize is smaller than actual vector size (5)
    std::size_t key = 2;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 2u);  // seqSize was 3, key was 2, so seqSize > key => --seqSize = 2
}

// Test removing when seqSize equals key (seqSize not greater than key)
TEST_F(RemoveTest_665, RemoveWhenSeqSizeEqualsKey_665) {
    std::size_t seqSize = 2;
    std::size_t key = 2;  // key == seqSize, but key < sequence.size()

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 2u);  // seqSize was 2, key was 2, seqSize is NOT > key, so no decrement
}

// Test removing when seqSize is less than key
TEST_F(RemoveTest_665, RemoveWhenSeqSizeLessThanKey_665) {
    std::size_t seqSize = 1;
    std::size_t key = 3;  // key > seqSize

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 1u);  // seqSize was 1, key was 3, seqSize NOT > key, so no decrement
}

// Test removing the only element in a single-element sequence
TEST_F(RemoveTest_665, RemoveSingleElement_665) {
    std::vector<YAML::detail::node*> single;
    YAML::detail::node* n = new YAML::detail::node(42);
    all_nodes_.push_back(n);
    single.push_back(n);
    std::size_t seqSize = 1;
    std::size_t key = 0;

    bool result = YAML::detail::remove(single, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(single.size(), 0u);
    EXPECT_EQ(seqSize, 0u);
}

// Test multiple consecutive removals
TEST_F(RemoveTest_665, MultipleRemovals_665) {
    std::size_t seqSize = 5;

    // Remove element at index 0 three times
    EXPECT_TRUE(YAML::detail::remove(nodes_, (std::size_t)0, seqSize));
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 4u);
    EXPECT_EQ(nodes_[0]->value, 1);

    EXPECT_TRUE(YAML::detail::remove(nodes_, (std::size_t)0, seqSize));
    EXPECT_EQ(nodes_.size(), 3u);
    EXPECT_EQ(seqSize, 3u);
    EXPECT_EQ(nodes_[0]->value, 2);

    EXPECT_TRUE(YAML::detail::remove(nodes_, (std::size_t)0, seqSize));
    EXPECT_EQ(nodes_.size(), 2u);
    EXPECT_EQ(seqSize, 2u);
    EXPECT_EQ(nodes_[0]->value, 3);
}

// Test that seqSize of 0 with non-empty sequence and key 0 does not decrement seqSize
TEST_F(RemoveTest_665, SeqSizeZeroWithNonEmptySequence_665) {
    std::size_t seqSize = 0;
    std::size_t key = 0;

    bool result = YAML::detail::remove(nodes_, key, seqSize);

    EXPECT_TRUE(result);
    EXPECT_EQ(nodes_.size(), 4u);
    EXPECT_EQ(seqSize, 0u);  // seqSize was 0, NOT > key (0), so no decrement
}

// Test removing with large key on empty sequence
TEST_F(RemoveTest_665, RemoveLargeKeyEmptySequence_665) {
    std::vector<YAML::detail::node*> empty;
    std::size_t seqSize = 0;
    std::size_t key = std::numeric_limits<std::size_t>::max();

    bool result = YAML::detail::remove(empty, key, seqSize);

    EXPECT_FALSE(result);
    EXPECT_EQ(empty.size(), 0u);
    EXPECT_EQ(seqSize, 0u);
}
