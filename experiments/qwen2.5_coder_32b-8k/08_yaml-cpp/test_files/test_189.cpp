#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"



using namespace YAML::detail;



class NodeIteratorBaseTest_189 : public ::testing::Test {

protected:

    MapIter map_begin;

    MapIter map_end;

    node_iterator_base<int> iterator;



    virtual void SetUp() override {

        // Initialize map_begin and map_end with appropriate values

        // For demonstration, we assume some mock iterators are available.

        map_begin = MapIter();  // Mock initialization

        map_end = MapIter();    // Mock initialization

        iterator = node_iterator_base<int>(map_begin, map_end);

    }

};



TEST_F(NodeIteratorBaseTest_189, IncrementUntilDefined_NoElements_189) {

    // Setup: No elements in the range

    MapIter it = map_begin;

    EXPECT_EQ(it, map_end);



    // Exercise & Verify

    MapIter result_it = iterator.increment_until_defined(it);

    EXPECT_EQ(result_it, map_end);  // Should return map_end as there are no elements

}



TEST_F(NodeIteratorBaseTest_189, IncrementUntilDefined_AllUndefined_189) {

    // Setup: All elements in the range are undefined

    MapIter it = map_begin;

    while (it != map_end) {

        EXPECT_CALL(iterator, is_defined(it)).WillRepeatedly(::testing::Return(false));

        ++it;

    }



    // Exercise & Verify

    MapIter result_it = iterator.increment_until_defined(map_begin);

    EXPECT_EQ(result_it, map_end);  // Should return map_end as all elements are undefined

}



TEST_F(NodeIteratorBaseTest_189, IncrementUntilDefined_FirstElementDefined_189) {

    // Setup: First element is defined

    MapIter it = map_begin;

    EXPECT_CALL(iterator, is_defined(it)).WillOnce(::testing::Return(true));



    // Exercise & Verify

    MapIter result_it = iterator.increment_until_defined(map_begin);

    EXPECT_EQ(result_it, map_begin);  // Should return map_begin as the first element is defined

}



TEST_F(NodeIteratorBaseTest_189, IncrementUntilDefined_SecondElementDefined_189) {

    // Setup: Second element is defined

    MapIter it = map_begin;

    EXPECT_CALL(iterator, is_defined(it)).WillOnce(::testing::Return(false));

    ++it;

    EXPECT_CALL(iterator, is_defined(it)).WillOnce(::testing::Return(true));



    // Exercise & Verify

    MapIter result_it = iterator.increment_until_defined(map_begin);

    EXPECT_EQ(result_it, it);  // Should return the second element as it is defined

}



TEST_F(NodeIteratorBaseTest_189, IncrementUntilDefined_LastElementDefined_189) {

    // Setup: Last element is defined

    MapIter it = map_begin;

    MapIter last_it = map_begin;

    while (++it != map_end) {

        EXPECT_CALL(iterator, is_defined(last_it)).WillOnce(::testing::Return(false));

        last_it = it;

    }

    EXPECT_CALL(iterator, is_defined(last_it)).WillOnce(::testing::Return(true));



    // Exercise & Verify

    MapIter result_it = iterator.increment_until_defined(map_begin);

    EXPECT_EQ(result_it, last_it);  // Should return the last element as it is defined

}
