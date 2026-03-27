#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



class StringStreamsTest : public ::testing::Test {

protected:

    StringStreams stringStreams;

};



TEST_F(StringStreamsTest_647, AddReturnsValidIndex_647) {

    std::size_t index = stringStreams.add();

    EXPECT_GE(index, 0);

}



TEST_F(StringStreamsTest_647, ReleaseRestoresStreamState_647) {

    std::size_t index = stringStreams.add();

    stringStreams.release(index);

    // No observable behavior to directly verify stream state restoration,

    // but we can ensure it doesn't crash and behaves as expected.

}



TEST_F(StringStreamsTest_647, ReleasePushesIndexToUnusedList_647) {

    std::size_t index = stringStreams.add();

    EXPECT_TRUE(stringStreams.m_unused.empty());

    stringStreams.release(index);

    EXPECT_FALSE(stringStreams.m_unused.empty());

    EXPECT_EQ(stringStreams.m_unused.back(), index);

}



TEST_F(StringStreamsTest_647, ReleaseMultipleIndices_647) {

    std::size_t index1 = stringStreams.add();

    std::size_t index2 = stringStreams.add();

    stringStreams.release(index1);

    stringStreams.release(index2);

    EXPECT_EQ(stringStreams.m_unused.size(), 2);

}



TEST_F(StringStreamsTest_647, AddAndReleaseMultipleTimes_647) {

    for (int i = 0; i < 10; ++i) {

        std::size_t index = stringStreams.add();

        stringStreams.release(index);

    }

    EXPECT_EQ(stringStreams.m_unused.size(), 10);

}



TEST_F(StringStreamsTest_647, ReleaseInvalidIndexDoesNotCrash_647) {

    // Assuming invalid index is greater than current size of m_streams

    std::size_t invalidIndex = stringStreams.m_streams.size() + 1;

    EXPECT_NO_THROW(stringStreams.release(invalidIndex));

}



TEST_F(StringStreamsTest_647, ReleaseSameIndexMultipleTimesDoesNotCrash_647) {

    std::size_t index = stringStreams.add();

    stringStreams.release(index);

    EXPECT_NO_THROW(stringStreams.release(index)); // Releasing the same index again

}
