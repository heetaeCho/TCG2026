#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch;

using namespace std;



class StringStreamsTest : public ::testing::Test {

protected:

    StringStreams streams;

};



TEST_F(StringStreamsTest_646, AddReturnsValidIndex_646) {

    EXPECT_EQ(0u, streams.add());

}



TEST_F(StringStreamsTest_646, MultipleAddsReturnIncrementingIndices_646) {

    EXPECT_EQ(0u, streams.add());

    EXPECT_EQ(1u, streams.add());

    EXPECT_EQ(2u, streams.add());

}



TEST_F(StringStreamsTest_646, AddAfterReleaseReturnsPreviousIndex_646) {

    auto index = streams.add();

    streams.release(index);

    EXPECT_EQ(index, streams.add());

}



TEST_F(StringStreamsTest_646, BoundaryCondition_EmptyUnusedInitially_646) {

    EXPECT_TRUE(streams.m_unused.empty());

    streams.add();

    EXPECT_FALSE(streams.m_unused.empty());

    streams.release(0);

    EXPECT_FALSE(streams.m_unused.empty());

}



TEST_F(StringStreamsTest_646, BoundaryCondition_AddToEmptyStreams_646) {

    EXPECT_EQ(0u, streams.add());

    EXPECT_EQ(1u, streams.m_streams.size());

}



TEST_F(StringStreamsTest_646, ExceptionalCase_ReleaseInvalidIndex_NoCrash_646) {

    // This test assumes that the release function does not throw for invalid indices.

    streams.release(999); // Invalid index

}
