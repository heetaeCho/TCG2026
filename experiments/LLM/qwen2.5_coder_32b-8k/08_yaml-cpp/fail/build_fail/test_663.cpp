#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/impl.h>

#include <vector>



using namespace YAML::detail;



// Mock class to simulate shared_memory_holder behavior if necessary

class MockSharedMemoryHolder {

public:

    MOCK_METHOD0(mockMethod, void());

};



TEST_F(YamlNodeDetailTest_663, GetReturnsNullForNegativeKey_663) {

    std::vector<node*> sequence;

    shared_memory_holder pMemory;

    EXPECT_EQ(get(sequence, -1, pMemory), nullptr);

}



TEST_F(YamlNodeDetailTest_663, GetReturnsValidPointerForPositiveKeyWithinBounds_663) {

    node dummyNode;

    std::vector<node*> sequence = { &dummyNode };

    shared_memory_holder pMemory;

    EXPECT_EQ(get(sequence, 0, pMemory), &dummyNode);

}



TEST_F(YamlNodeDetailTest_663, GetReturnsNullForPositiveKeyOutOfBounds_663) {

    std::vector<node*> sequence;

    shared_memory_holder pMemory;

    EXPECT_EQ(get(sequence, 1, pMemory), nullptr);

}



TEST_F(YamlNodeDetailTest_663, GetHandlesEmptySequence_663) {

    std::vector<node*> sequence;

    shared_memory_holder pMemory;

    EXPECT_EQ(get(sequence, 0, pMemory), nullptr);

}
