#include <gtest/gtest.h>

#include "yaml-cpp/depthguard.h"



namespace YAML {



class DepthGuardTest_92 : public ::testing::Test {

protected:

    int depth;

    Mark mark;

    std::string msg;



    void SetUp() override {

        depth = 0;

        mark = Mark(); // Assuming Mark has a default constructor

        msg = "test message";

    }

};



TEST_F(DepthGuardTest_92, ConstructorIncrementsDepth_92) {

    DepthGuard guard(depth, mark, msg);

    EXPECT_EQ(depth, 1);

}



TEST_F(DepthGuardTest_92, DestructorDecrementsDepth_92) {

    {

        DepthGuard guard(depth, mark, msg);

        EXPECT_EQ(depth, 1);

    }

    EXPECT_EQ(depth, 0);

}



TEST_F(DepthGuardTest_92, CurrentDepthReturnsCorrectValue_92) {

    DepthGuard guard(depth, mark, msg);

    EXPECT_EQ(guard.current_depth(), 1);

}



TEST_F(DepthGuardTest_92, CopyConstructorDeleted_92) {

    DepthGuard original(depth, mark, msg);

    EXPECT_FALSE((std::is_constructible<DepthGuard, const DepthGuard&>::value));

}



TEST_F(DepthGuardTest_92, MoveConstructorDeleted_92) {

    DepthGuard original(depth, mark, msg);

    EXPECT_FALSE((std::is_constructible<DepthGuard, DepthGuard&&>::value));

}



TEST_F(DepthGuardTest_92, CopyAssignmentOperatorDeleted_92) {

    DepthGuard guard(depth, mark, msg);

    DepthGuard other(0, mark, msg);

    EXPECT_FALSE((std::is_assignable<DepthGuard&, const DepthGuard&>::value));

}



TEST_F(DepthGuardTest_92, MoveAssignmentOperatorDeleted_92) {

    DepthGuard guard(depth, mark, msg);

    DepthGuard other(0, mark, msg);

    EXPECT_FALSE((std::is_assignable<DepthGuard&, DepthGuard&&>::value));

}



} // namespace YAML
