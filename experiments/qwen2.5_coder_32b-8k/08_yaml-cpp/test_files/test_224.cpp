#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/exceptions.h"



namespace YAML {

    namespace detail {



        class NodeRefTest_224 : public ::testing::Test {

        protected:

            node_ref testNode;

        };



        TEST_F(NodeRefTest_224, SetStyle_Default_224) {

            EmitterStyle::value initialStyle = testNode.style();

            testNode.set_style(EmitterStyle::Default);

            EXPECT_EQ(testNode.style(), EmitterStyle::Default);

        }



        TEST_F(NodeRefTest_224, SetStyle_Block_224) {

            testNode.set_style(EmitterStyle::Block);

            EXPECT_EQ(testNode.style(), EmitterStyle::Block);

        }



        TEST_F(NodeRefTest_224, SetStyle_Flow_224) {

            testNode.set_style(EmitterStyle::Flow);

            EXPECT_EQ(testNode.style(), EmitterStyle::Flow);

        }



        TEST_F(NodeRefTest_224, SetStyle_Invalid_Value_Does_Not_Change_Style_224) {

            EmitterStyle::value invalidStyle = static_cast<EmitterStyle::value>(-1);

            testNode.set_style(invalidStyle);

            EXPECT_NE(testNode.style(), invalidStyle);

        }



    } // namespace detail

} // namespace YAML
