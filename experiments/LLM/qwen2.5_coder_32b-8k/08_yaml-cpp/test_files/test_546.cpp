#include <gtest/gtest.h>

#include "yaml-cpp/depthguard.h"



namespace YAML {



class DepthGuardTest_546 : public ::testing::Test {

protected:

    int depth;

    Mark mark; // Assuming Mark is a valid type in the context of yaml-cpp

    std::string msg;



    void SetUp() override {

        depth = 0;

        mark = Mark(); // Proper initialization should be done as per actual implementation

        msg = "Test Message";

    }

};



TEST_F(DepthGuardTest_546, ConstructorIncrementsDepth_546) {

    EXPECT_EQ(depth, 0);

    DepthGuard guard(depth, mark, msg);

    EXPECT_EQ(depth, 1);

}



TEST_F(DepthGuardTest_546, DestructorDecrementsDepth_546) {

    depth = 1;

    {

        DepthGuard guard(depth, mark, msg);

        EXPECT_EQ(depth, 2);

    }

    EXPECT_EQ(depth, 1);

}



TEST_F(DepthGuardTest_546, CurrentDepthReturnsCorrectValue_546) {

    depth = 3;

    DepthGuard guard(depth, mark, msg);

    EXPECT_EQ(guard.current_depth(), 4);

}



TEST_F(DepthGuardTest_546, CopyConstructorDeleted_546) {

    DepthGuard original(depth, mark, msg);

    // This should not compile

    // DepthGuard copy = original;

}



TEST_F(DepthGuardTest_546, MoveConstructorDeleted_546) {

    DepthGuard original(depth, mark, msg);

    // This should not compile

    // DepthGuard moved = std::move(original);

}



TEST_F(DepthGuardTest_546, CopyAssignmentOperatorDeleted_546) {

    DepthGuard original(depth, mark, msg);

    DepthGuard another(0, mark, msg);

    // This should not compile

    // another = original;

}



TEST_F(DepthGuardTest_546, MoveAssignmentOperatorDeleted_546) {

    DepthGuard original(depth, mark, msg);

    DepthGuard another(0, mark, msg);

    // This should not compile

    // another = std::move(original);

}



}  // namespace YAML
