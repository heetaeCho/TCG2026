#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/ninja/src/graph.h"

#include "TestProjects/ninja/src/state.h"

#include "TestProjects/ninja/src/disk_interface.h"

#include "TestProjects/ninja/src/depfile_parser_options.h"

#include "TestProjects/ninja/src/explanations.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(bool, Stat, (const std::string &path, TimeStamp *mtime), (override));

    MOCK_METHOD(bool, ReadFile, (const std::string &path, std::string *contents, std::string *err), (override));

};



class MockState : public State {

    // If needed, add mock methods here.

};



class MockExplanations : public Explanations {

    // If needed, add mock methods here.

};



class ImplicitDepLoaderTest_64 : public ::testing::Test {

protected:

    NiceMock<MockDiskInterface> disk_interface_;

    NiceMock<MockState> state_;

    DepsLog deps_log_;

    DepfileParserOptions depfile_parser_options_;

    MockExplanations explanations_;

    ImplicitDepLoader loader_{&state_, &deps_log_, &disk_interface_, &depfile_parser_options_, &explanations_};

};



TEST_F(ImplicitDepLoaderTest_64, LoadDeps_Success_64) {

    Edge edge;

    std::string err;

    EXPECT_CALL(disk_interface_, ReadFile(_, _, _)).WillOnce(Return(true));

    ASSERT_TRUE(loader_.LoadDeps(&edge, &err));

}



TEST_F(ImplicitDepLoaderTest_64, LoadDeps_Failure_64) {

    Edge edge;

    std::string err;

    EXPECT_CALL(disk_interface_, ReadFile(_, _, _)).WillOnce(Return(false));

    ASSERT_FALSE(loader_.LoadDeps(&edge, &err));

}



TEST_F(ImplicitDepLoaderTest_64, LoadDeps_EmptyPath_64) {

    Edge edge;

    std::string err;

    EXPECT_CALL(disk_interface_, ReadFile("", _, _)).WillOnce(Return(false));

    ASSERT_FALSE(loader_.LoadDeps(&edge, &err));

}



TEST_F(ImplicitDepLoaderTest_64, DepsLog_Accessibility_64) {

    EXPECT_EQ(&deps_log_, loader_.deps_log());

}
