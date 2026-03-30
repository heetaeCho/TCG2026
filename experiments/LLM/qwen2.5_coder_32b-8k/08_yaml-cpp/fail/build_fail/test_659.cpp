#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/node/detail/impl.h>



namespace YAML { namespace detail {



class GetIdxTest : public ::testing::Test {

protected:

    std::vector<node*> sequence;

    Key key;

    shared_memory_holder pMemory;

};



TEST_F(GetIdxTest_659, ReturnsNullptrForEmptySequence_659) {

    node* result = get_idx::get(sequence, key, pMemory);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GetIdxTest_659, ReturnsNullptrForNonEmptySequence_659) {

    sequence.push_back(new node());

    node* result = get_idx::get(sequence, key, pMemory);

    EXPECT_EQ(result, nullptr);

    delete sequence[0];

}



TEST_F(GetIdxTest_659, HandlesArbitraryKeyAndMemoryHolder_659) {

    // Assuming Key and shared_memory_holder are default-constructible

    node* result = get_idx::get(sequence, key, pMemory);

    EXPECT_EQ(result, nullptr);

}



} }
