#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



namespace YAML {

namespace detail {



class NodeRefTest_215 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_215, DefaultTagIsEmptyString_215) {

    EXPECT_EQ(ref.tag(), "");

}



// Assuming there's a way to set the tag for testing purposes

// TEST_F(NodeRefTest_215, SetTagChangesTheTag_215) {

//     ref.set_tag("test");

//     EXPECT_EQ(ref.tag(), "test");

// }



TEST_F(NodeRefTest_215, TagIsConstReference_215) {

    const std::string& tag = ref.tag();

    EXPECT_EQ(&tag, &ref.tag());

}



}  // namespace detail

}  // namespace YAML
