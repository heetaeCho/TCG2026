#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/impl.h>

#include <vector>

#include <memory>



namespace YAML {

namespace detail {



class NodeImplTest : public ::testing::Test {

protected:

    std::vector<node*> sequence;

    shared_memory_holder memory;



    void SetUp() override {

        // Initialize some nodes for testing

        sequence.push_back(new node());

        sequence.push_back(new node());

        sequence.push_back(new node());

    }



    void TearDown() override {

        // Clean up the allocated nodes

        for (auto* n : sequence) {

            delete n;

        }

        sequence.clear();

    }

};



TEST_F(NodeImplTest_660, GetValidIndex_ReturnsNode_660) {

    Key key = 1;

    node* result = get(sequence, key, memory);

    EXPECT_EQ(result, sequence[key]);

}



TEST_F(NodeImplTest_660, GetFirstElement_ReturnsNode_660) {

    Key key = 0;

    node* result = get(sequence, key, memory);

    EXPECT_EQ(result, sequence[key]);

}



TEST_F(NodeImplTest_660, GetLastElement_ReturnsNode_660) {

    Key key = sequence.size() - 1;

    node* result = get(sequence, key, memory);

    EXPECT_EQ(result, sequence[key]);

}



TEST_F(NodeImplTest_660, GetIndexOutOfRange_ReturnsNullptr_660) {

    Key key = sequence.size();

    node* result = get(sequence, key, memory);

    EXPECT_EQ(result, nullptr);

}



TEST_F(NodeImplTest_660, GetNegativeIndex_ReturnsNullptr_660) {

    Key key = -1;

    node* result = get(sequence, key, memory);

    EXPECT_EQ(result, nullptr);

}



} // namespace detail

} // namespace YAML
