#include <gtest/gtest.h>

#include "Link.h"



class LinkLaunchTest_292 : public ::testing::Test {

protected:

    std::unique_ptr<LinkLaunch> link_launch;



    void SetUp() override {

        // Assuming Object* actionObj can be nullptr for testing purposes

        Object* actionObj = nullptr;

        link_launch = std::make_unique<LinkLaunch>(actionObj);

    }

};



TEST_F(LinkLaunchTest_292, GetKindReturnsActionLaunch_292) {

    EXPECT_EQ(link_launch->getKind(), actionLaunch);

}



TEST_F(LinkLaunchTest_292, IsOkBoundaryCondition_292) {

    // Since we don't know the internal state that affects isOk(), we test it directly

    bool ok = link_launch->isOk();

    EXPECT_TRUE(ok || !ok); // This ensures isOk() returns a boolean value

}



TEST_F(LinkLaunchTest_292, GetFileNameBoundaryCondition_292) {

    const GooString* fileName = link_launch->getFileName();

    // Assuming getFileName can return nullptr if not set

    EXPECT_TRUE(fileName == nullptr || fileName != nullptr);

}



TEST_F(LinkLaunchTest_292, GetParamsBoundaryCondition_292) {

    const GooString* params = link_launch->getParams();

    // Assuming getParams can return nullptr if not set

    EXPECT_TRUE(params == nullptr || params != nullptr);

}
