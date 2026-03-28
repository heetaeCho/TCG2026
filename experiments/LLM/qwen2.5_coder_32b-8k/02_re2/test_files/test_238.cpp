#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/re2.cc"



namespace re2 {



class EmptyStorageTest_238 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(EmptyStorageTest_238, NamedGroupsInitiallyEmpty_238) {

    const std::map<std::string, int>* named_groups = empty_named_groups();

    EXPECT_TRUE(named_groups->empty());

}



TEST_F(EmptyStorageTest_238, BoundaryCondition_EmptyStringSize_238) {

    const std::map<std::string, int>* named_groups = empty_named_groups();

    EXPECT_EQ(named_groups->size(), 0);

}



// No observable behavior for exceptions as the function returns a static map reference



} // namespace re2
