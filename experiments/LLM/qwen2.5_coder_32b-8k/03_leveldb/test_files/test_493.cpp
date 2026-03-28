#include <gtest/gtest.h>

#include "util/no_destructor.h"



namespace leveldb {



class NoDestructorTest_493 : public ::testing::Test {

protected:

    using TestType = int;

};



TEST_F(NoDestructorTest_493, ConstructorInitializesValue_493) {

    NoDestructor<TestType> noDestructor(42);

    EXPECT_EQ(*noDestructor.get(), 42);

}



TEST_F(NoDestructorTest_493, DefaultConstructorInitializesZero_493) {

    NoDestructor<TestType> noDestructor;

    EXPECT_EQ(*noDestructor.get(), 0);

}



TEST_F(NoDestructorTest_493, CopyConstructorIsDeleted_493) {

    NoDestructor<TestType> original(42);

    static_assert(!std::is_copy_constructible_v<NoDestructor<TestType>>, "Copy constructor should be deleted");

}



TEST_F(NoDestructorTest_493, AssignmentOperatorIsDeleted_493) {

    NoDestructor<TestType> original(42);

    NoDestructor<TestType> other(0);

    static_assert(!std::is_copy_assignable_v<NoDestructor<TestType>>, "Assignment operator should be deleted");

}



TEST_F(NoDestructorTest_493, DestructorDoesNotCrash_493) {

    NoDestructor<TestType>* noDestructor = new NoDestructor<TestType>(42);

    delete noDestructor;

}



} // namespace leveldb
