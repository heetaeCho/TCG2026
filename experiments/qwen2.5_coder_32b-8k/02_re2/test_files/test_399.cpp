#include <gtest/gtest.h>

#include "re2/sparse_set.h"

#include "re2/prog.h"



namespace re2 {



class WorkqTest : public ::testing::Test {

protected:

    SparseSet q;

};



TEST_F(WorkqTest_399, AddToQueue_NonZeroId_AddsElement_399) {

    int id = 5;

    AddToQueue(&q, id);

    EXPECT_TRUE(q.contains(id));

}



TEST_F(WorkqTest_399, AddToQueue_ZeroId_DoesNotAddElement_399) {

    int id = 0;

    AddToQueue(&q, id);

    EXPECT_FALSE(q.contains(id));

}



TEST_F(WorkqTest_399, AddToQueue_AlreadyExistingId_DoesNotChangeSize_399) {

    int id = 10;

    q.insert(id); // Manually inserting to set up state

    size_t initial_size = q.size();

    AddToQueue(&q, id);

    EXPECT_EQ(q.size(), initial_size);

}



TEST_F(WorkqTest_399, AddToQueue_NewId_IncreasesSize_399) {

    int id = 15;

    size_t initial_size = q.size();

    AddToQueue(&q, id);

    EXPECT_EQ(q.size(), initial_size + 1);

}



TEST_F(WorkqTest_399, AddToQueue_NegativeId_AddsElement_399) {

    int id = -20;

    AddToQueue(&q, id);

    EXPECT_TRUE(q.contains(id));

}



TEST_F(WorkqTest_399, AddToQueue_MaxSizeExceeded_DoesNotAddElement_399) {

    q.resize(1); // Set max size to 1

    int id1 = 25;

    int id2 = 30;

    AddToQueue(&q, id1);

    EXPECT_TRUE(q.contains(id1));

    AddToQueue(&q, id2);

    EXPECT_FALSE(q.contains(id2)); // Should not add second element due to max size

}



}  // namespace re2
