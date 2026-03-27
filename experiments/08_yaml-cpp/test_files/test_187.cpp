#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"

#include <vector>

#include <map>



namespace YAML {

    namespace detail {



        class NodeIteratorTest_187 : public ::testing::Test {

        protected:

            using SeqIter = std::vector<value_type>::iterator;

            using MapIter = std::map<std::string, value_type>::iterator;



            node_iterator_base<value_type> noneTypeIt;

            node_iterator_base<value_type> sequenceIt;

            node_iterator_base<value_type> mapIt;



            NodeIteratorTest_187() {

                std::vector<value_type> seq = {value_type(42)};

                sequenceIt = node_iterator_base<value_type>(seq.begin());



                std::map<std::string, value_type> map = {{"key", value_type("value")}};

                mapIt = node_iterator_base<value_type>(map.begin(), map.end());

            }

        };



        TEST_F(NodeIteratorTest_187, DereferenceNoneType_187) {

            EXPECT_EQ(noneTypeIt.operator*(), value_type());

        }



        TEST_F(NodeIteratorTest_187, DereferenceSequence_187) {

            EXPECT_EQ(sequenceIt.operator*(), value_type(42));

        }



        TEST_F(NodeIteratorTest_187, DereferenceMap_187) {

            EXPECT_EQ(mapIt.operator*().first, "key");

            EXPECT_EQ(mapIt.operator*().second, value_type("value"));

        }



    } // namespace detail

} // namespace YAML
