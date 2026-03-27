#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>



// Mock Key type for testing purposes

struct Key {};



namespace YAML { namespace detail {



struct remove_idx {

    static bool remove(std::vector<node*>&, const Key&, std::size_t&);

};



} } // namespace YAML::detail



using namespace YAML::detail;



class RemoveIdxTest : public ::testing::Test {

protected:

    std::vector<node*> nodes;

    Key key;

    std::size_t index;

};



TEST_F(RemoveIdxTest_664, RemoveReturnsFalse_664) {

    EXPECT_FALSE(remove_idx::remove(nodes, key, index));

}



// Since the function always returns false and has no observable side effects,

// there are no other normal operation, boundary conditions, or exceptional cases to test.

```


