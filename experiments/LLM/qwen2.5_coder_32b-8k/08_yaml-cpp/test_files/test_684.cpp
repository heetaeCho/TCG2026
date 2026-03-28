#include <gtest/gtest.h>

#include "yaml-cpp/depthguard.h"

#include "yaml-cpp/mark.h"



namespace YAML {

    template<int max_depth> class DepthGuard;

}



using namespace YAML;



TEST_F(DepthGuardTest_684, ConstructorIncrementsDepth_684) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";

    EXPECT_EQ(depth, 0);

    {

        DepthGuard<10> guard(depth, mark, msg);

        EXPECT_EQ(depth, 1);

    }

    EXPECT_EQ(depth, 0);

}



TEST_F(DepthGuardTest_684, DestructorDecrementsDepth_684) {

    int depth = 1;

    Mark mark;

    std::string msg = "test message";

    EXPECT_EQ(depth, 1);

    {

        DepthGuard<10> guard(depth, mark, msg);

        EXPECT_EQ(depth, 2);

    }

    EXPECT_EQ(depth, 1);

}



TEST_F(DepthGuardTest_684, MaxDepthThrowsException_684) {

    int depth = 9;

    Mark mark;

    std::string msg = "test message";

    EXPECT_THROW({

        DepthGuard<10> guard(depth, mark, msg);

        DepthGuard<10> anotherGuard(depth, mark, msg); // This should throw

    }, DeepRecursion);

}



TEST_F(DepthGuardTest_684, CurrentDepthReturnsCorrectValue_684) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";

    DepthGuard<10> guard(depth, mark, msg);

    EXPECT_EQ(guard.current_depth(), 1);

}



TEST_F(DepthGuardTest_684, DeletedCopyConstructorAndAssignment_684) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";

    DepthGuard<10> guard(depth, mark, msg);



    // Ensure copy constructor is deleted

    static_assert(!std::is_copy_constructible<DepthGuard<10>>::value, "Copy constructor should be deleted");



    // Ensure move constructor is deleted

    static_assert(!std::is_move_constructible<DepthGuard<10>>::value, "Move constructor should be deleted");



    // Ensure copy assignment operator is deleted

    static_assert(!std::is_copy_assignable<DepthGuard<10>>::value, "Copy assignment operator should be deleted");



    // Ensure move assignment operator is deleted

    static_assert(!std::is_move_assignable<DepthGuard<10>>::value, "Move assignment operator should be deleted");

}
