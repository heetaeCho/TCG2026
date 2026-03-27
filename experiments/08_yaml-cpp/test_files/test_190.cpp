#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"

#include <map>



using namespace YAML::detail;



class NodeIteratorBaseTest_190 : public ::testing::Test {

protected:

    struct TestNode {

        bool is_defined() const { return m_isDefined; }

        void set_defined(bool defined) { m_isDefined = defined; }



    private:

        bool m_isDefined = false;

    };



    using MapIter = std::map<int, TestNode>::iterator;



    NodeIteratorBaseTest_190() {

        testMap[1].set_defined(true);

        testMap[2].set_defined(false);

        testMap[3].set_defined(true);



        mapIt = testMap.begin();

        mapEnd = testMap.end();

    }



    std::map<int, TestNode> testMap;

    MapIter mapIt;

    MapIter mapEnd;

    node_iterator_base<MapIter> iterator;

};



TEST_F(NodeIteratorBaseTest_190, IsDefined_ReturnsTrueForBothDefinedNodes_190) {

    EXPECT_TRUE(iterator.is_defined(testMap.find(1)));

    EXPECT_TRUE(iterator.is_defined(testMap.find(3)));

}



TEST_F(NodeIteratorBaseTest_190, IsDefined_ReturnsFalseForUndefinedNode_190) {

    EXPECT_FALSE(iterator.is_defined(testMap.find(2)));

}



TEST_F(NodeIteratorBaseTest_190, IsDefined_ReturnsFalseForEndIterator_190) {

    EXPECT_FALSE(iterator.is_defined(mapEnd));

}



TEST_F(NodeIteratorBaseTest_190, IsDefined_ReturnsTrueWhenBothKeyAndValueAreDefined_190) {

    EXPECT_TRUE(iterator.is_defined(testMap.find(1)));

}



TEST_F(NodeIteratorBaseTest_190, IsDefined_ReturnsFalseWhenOnlyKeyIsDefined_190) {

    testMap[2].set_defined(false);

    EXPECT_FALSE(iterator.is_defined(testMap.find(2)));

}
