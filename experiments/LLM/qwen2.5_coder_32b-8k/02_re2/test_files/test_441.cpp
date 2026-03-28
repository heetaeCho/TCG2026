#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace re2 {



class DFA;

class Workq;



// Mocking external collaborators if needed (none in this case)



TEST_F(WorkqTest_441, IsMark_ValidIndex_ReturnsFalse_441) {

    Workq workq(10, 5);

    EXPECT_FALSE(workq.is_mark(3));

}



TEST_F(WorkqTest_441, IsMark_IndexEqualToN_ReturnsTrue_441) {

    Workq workq(10, 5);

    EXPECT_TRUE(workq.is_mark(10));

}



TEST_F(WorkqTest_441, IsMark_IndexGreaterThanN_ReturnsTrue_441) {

    Workq workq(10, 5);

    EXPECT_TRUE(workq.is_mark(15));

}



TEST_F(WorkqTest_441, Maxmark_DefaultInitialization_ReturnsCorrectValue_441) {

    Workq workq(10, 5);

    EXPECT_EQ(workq.maxmark(), 5);

}



TEST_F(WorkqTest_441, Clear_SizeAfterClear_IsZero_441) {

    Workq workq(10, 5);

    workq.insert(3);

    workq.clear();

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(WorkqTest_441, Mark_NextmarkIncremented_441) {

    Workq workq(10, 5);

    int initial_nextmark = workq.maxmark() + workq.n_;

    workq.mark();

    EXPECT_EQ(workq.maxmark() + workq.n_, initial_nextmark + 1);

}



TEST_F(WorkqTest_441, Insert_IdInserted_SizeIncreasedByOne_441) {

    Workq workq(10, 5);

    int initial_size = workq.size();

    workq.insert(3);

    EXPECT_EQ(workq.size(), initial_size + 1);

}



TEST_F(WorkqTest_441, Insert_IdAlreadyExists_SizeDoesNotChange_441) {

    Workq workq(10, 5);

    workq.insert(3);

    int size_after_insert = workq.size();

    workq.insert(3);

    EXPECT_EQ(workq.size(), size_after_insert);

}



TEST_F(WorkqTest_441, InsertNew_IdInserted_SizeIncreasedByOne_441) {

    Workq workq(10, 5);

    int initial_size = workq.size();

    workq.insert_new(3);

    EXPECT_EQ(workq.size(), initial_size + 1);

}



TEST_F(WorkqTest_441, InsertNew_IdAlreadyExists_SizeDoesNotChange_441) {

    Workq workq(10, 5);

    workq.insert_new(3);

    int size_after_insert = workq.size();

    workq.insert_new(3);

    EXPECT_EQ(workq.size(), size_after_insert);

}



} // namespace re2
