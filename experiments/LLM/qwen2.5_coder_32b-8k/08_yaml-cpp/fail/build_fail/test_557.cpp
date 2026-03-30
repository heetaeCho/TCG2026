#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



namespace YAML {

    class NodeTest_557 : public ::testing::Test {

    protected:

        Node node;

    };



    TEST_F(NodeTest_557, ScalarReturnsEmptyStringForUndefinedNode_557) {

        Node undefinedNode((Zombie()));

        EXPECT_EQ(undefinedNode.Scalar(), detail::node_data::empty_scalar());

    }



    TEST_F(NodeTest_557, ScalarThrowsInvalidNodeExceptionForUndefinedNode_557) {

        Node invalidNode((Zombie("invalid_key")));

        EXPECT_THROW(invalidNode.Scalar(), InvalidNode);

    }



    TEST_F(NodeTest_557, ScalarReturnsCorrectValueForDefinedScalarNode_557) {

        node = Node("test_scalar");

        EXPECT_EQ(node.Scalar(), "test_scalar");

    }



    TEST_F(NodeTest_557, ScalarThrowsInvalidNodeExceptionForNonScalarNode_557) {

        node = Node();

        EXPECT_THROW(node.Scalar(), InvalidNode);

    }

}
