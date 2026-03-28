#include <gtest/gtest.h>

#include "yaml-cpp/depthguard.h"

#include "yaml-cpp/mark.h"



namespace YAML {

    template <int max_depth> class DepthGuard;

}



using namespace YAML;



TEST_F(DepthGuardTest_678, NormalOperationIncreasesDepth_678) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";



    {

        DepthGuard<10> guard(depth, mark, msg);

        EXPECT_EQ(guard.current_depth(), 1);

    }



    EXPECT_EQ(depth, 0);

}



TEST_F(DepthGuardTest_678, BoundaryConditionMaxDepthDoesNotThrow_678) {

    int depth = 9;

    Mark mark;

    std::string msg = "test message";



    try {

        DepthGuard<10> guard(depth, mark, msg);

        EXPECT_EQ(guard.current_depth(), 10);

    } catch (const DeepRecursion& e) {

        FAIL() << "Unexpected exception thrown";

    }



    EXPECT_EQ(depth, 9);

}



TEST_F(DepthGuardTest_678, BoundaryConditionExceedMaxDepthThrows_678) {

    int depth = 10;

    Mark mark;

    std::string msg = "test message";



    EXPECT_THROW({

        DepthGuard<10> guard(depth, mark, msg);

    }, DeepRecursion);



    EXPECT_EQ(depth, 10);

}



TEST_F(DepthGuardTest_678, CopyConstructorDeleted_678) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";



    DepthGuard<10> guard(depth, mark, msg);



    EXPECT_FALSE(std::is_copy_constructible<DepthGuard<10>>::value);

}



TEST_F(DepthGuardTest_678, MoveConstructorDeleted_678) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";



    DepthGuard<10> guard(depth, mark, msg);



    EXPECT_FALSE(std::is_move_constructible<DepthGuard<10>>::value);

}



TEST_F(DepthGuardTest_678, CopyAssignmentDeleted_678) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";



    DepthGuard<10> guard(depth, mark, msg);



    EXPECT_FALSE(std::is_copy_assignable<DepthGuard<10>>::value);

}



TEST_F(DepthGuardTest_678, MoveAssignmentDeleted_678) {

    int depth = 0;

    Mark mark;

    std::string msg = "test message";



    DepthGuard<10> guard(depth, mark, msg);



    EXPECT_FALSE(std::is_move_assignable<DepthGuard<10>>::value);

}
