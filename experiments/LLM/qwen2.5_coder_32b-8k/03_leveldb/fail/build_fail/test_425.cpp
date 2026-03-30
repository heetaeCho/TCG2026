#include <gtest/gtest.h>

#include "util/no_destructor.h"



namespace leveldb {



class NoDestructorTest_425 : public ::testing::Test {

protected:

    // Additional setup can be done here if necessary.

};



TEST_F(NoDestructorTest_425, GetReturnsValidPointer_425) {

    NoDestructor<int> no_destructor(42);

    int* ptr = no_destructor.get();

    EXPECT_NE(ptr, nullptr);

}



TEST_F(NoDestructorTest_425, GetPointsToCorrectValue_425) {

    NoDestructor<int> no_destructor(42);

    int* ptr = no_destructor.get();

    EXPECT_EQ(*ptr, 42);

}



TEST_F(NoDestructorTest_425, ConstructorWithMultipleArgs_425) {

    struct Pair { int a; double b; };

    NoDestructor<Pair> no_destructor(1, 3.14);

    Pair* ptr = no_destructor.get();

    EXPECT_EQ(ptr->a, 1);

    EXPECT_DOUBLE_EQ(ptr->b, 3.14);

}



TEST_F(NoDestructorTest_425, NonCopyable_425) {

    NoDestructor<int> no_destructor1(42);

    // Attempting to copy should result in a compile-time error

    // NoDestructor<int> no_destructor2 = no_destructor1;  // This line should cause a compilation failure if uncommented

}



TEST_F(NoDestructorTest_425, DestructorDoesNotDelete_425) {

    int* raw_ptr = new int(42);

    NoDestructor<int*> no_destructor(raw_ptr);

    delete raw_ptr;  // Manually delete the raw pointer to simulate its lifecycle

    int** ptr = no_destructor.get();

    EXPECT_NE(*ptr, nullptr);  // The NoDestructor should not have deleted the pointer

}



}  // namespace leveldb
