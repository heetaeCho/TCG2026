#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"

#include "yaml-cpp/node/detail/node_iterator.h"



namespace YAML {

    namespace detail {



        class IteratorBaseTest_199 : public ::testing::Test {

        protected:

            using iterator_type = iterator_base<int>;

            iterator_type iter;

        };



        TEST_F(IteratorBaseTest_199, PreIncrementOperatorIncreasesCount_199) {

            auto& result = ++iter;

            EXPECT_EQ(&result, &iter);

        }



        TEST_F(IteratorBaseTest_199, PostIncrementOperatorReturnsCopyBeforeIncrement_199) {

            iterator_type copy = iter++;

            EXPECT_NE(&copy, &iter);

        }



        class NodeIteratorBaseTest_199 : public ::testing::Test {

        protected:

            using node_iterator_type = node_iterator_base<int>;

            node_iterator_type nodeIter;

        };



        TEST_F(NodeIteratorBaseTest_199, PreIncrementOperatorIncreasesCount_199) {

            auto& result = ++nodeIter;

            EXPECT_EQ(&result, &nodeIter);

        }



        TEST_F(NodeIteratorBaseTest_199, PostIncrementOperatorReturnsCopyBeforeIncrement_199) {

            node_iterator_type copy = nodeIter++;

            EXPECT_NE(&copy, &nodeIter);

        }



    } // namespace detail

} // namespace YAML
