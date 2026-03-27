#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/impl.h"



using namespace YAML::detail;



class GetFunctionTest_662 : public ::testing::Test {

protected:

    std::vector<node*> sequence;

    shared_memory_holder pMemory;



    void SetUp() override {

        // Initialize the sequence with some mock nodes

        sequence.push_back(new node());

        sequence.push_back(new node());

        sequence.push_back(new node());

    }



    void TearDown() override {

        // Clean up allocated nodes

        for (auto* n : sequence) {

            delete n;

        }

        sequence.clear();

    }

};



TEST_F(GetFunctionTest_662, ValidIndexReturnsNode_662) {

    int key = 1; // Valid index within the bounds of the sequence

    node* result = get(sequence, key, pMemory);

    EXPECT_NE(result, nullptr);

}



TEST_F(GetFunctionTest_662, InvalidNegativeIndexReturnsNullptr_662) {

    int key = -1; // Negative index is out of bounds

    node* result = get(sequence, key, pMemory);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetFunctionTest_662, IndexEqualToSizeReturnsNullptr_662) {

    std::size_t key = sequence.size(); // Index equal to the size is out of bounds

    node* result = get(sequence, static_cast<int>(key), pMemory);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetFunctionTest_662, IndexGreaterThanSizeReturnsNullptr_662) {

    std::size_t key = sequence.size() + 1; // Index greater than the size is out of bounds

    node* result = get(sequence, static_cast<int>(key), pMemory);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetFunctionTest_662, BoundaryIndexZeroReturnsNode_662) {

    int key = 0; // Boundary index at zero should return a valid node

    node* result = get(sequence, key, pMemory);

    EXPECT_NE(result, nullptr);

}



TEST_F(GetFunctionTest_662, BoundaryIndexLastElementReturnsNode_662) {

    std::size_t key = sequence.size() - 1; // Boundary index at the last element should return a valid node

    node* result = get(sequence, static_cast<int>(key), pMemory);

    EXPECT_NE(result, nullptr);

}
