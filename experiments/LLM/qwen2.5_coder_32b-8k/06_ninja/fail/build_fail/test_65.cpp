#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include "build_log.h"

#include "deps_log.h"

#include "disk_interface.h"

#include "node.h"

#include "edge.h"



using namespace testing;



class DependencyScanTest_65 : public ::testing::Test {

protected:

    NiceMock<MockState> state_;

    MockBuildLog build_log_;

    MockDepsLog deps_log_;

    MockDiskInterface disk_interface_;

    DepfileParserOptions depfile_parser_options_{};

    Explanations explanations_{};



    DependencyScan scan_{

        &state_,

        &build_log_,

        &deps_log_,

        &disk_interface_,

        &depfile_parser_options_,

        &explanations_

    };



    Node node_;

    Edge edge_;

    std::string err_;

    std::vector<Node*> validation_nodes_;

    _Bool dirty_{false};

};



TEST_F(DependencyScanTest_65, RecomputeDirty_NormalOperation_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.RecomputeDirty(&node_, &validation_nodes_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, RecomputeDirty_BoundaryConditions_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    std::vector<Node*> empty_validation_nodes;

    bool result = scan_.RecomputeDirty(&node_, &empty_validation_nodes, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, RecomputeDirty_ExceptionalCases_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.RecomputeDirty(nullptr, &validation_nodes_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, RecomputeOutputsDirty_NormalOperation_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.RecomputeOutputsDirty(&edge_, &node_, &dirty_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, RecomputeOutputsDirty_BoundaryConditions_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.RecomputeOutputsDirty(nullptr, &node_, &dirty_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, RecomputeOutputsDirty_ExceptionalCases_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.RecomputeOutputsDirty(&edge_, nullptr, &dirty_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, LoadDyndeps_NormalOperation_Node_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.LoadDyndeps(&node_, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, LoadDyndeps_NormalOperation_NodeAndFile_65) {

    DyndepFile ddf{};

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.LoadDyndeps(&node_, &ddf, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, LoadDyndeps_BoundaryConditions_Node_65) {

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.LoadDyndeps(nullptr, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, LoadDyndeps_BoundaryConditions_NodeAndFile_65) {

    DyndepFile ddf{};

    EXPECT_CALL(build_log_, ...); // Mock any expected interactions with build_log_

    bool result = scan_.LoadDyndeps(nullptr, &ddf, &err_);

    // Verify the return value or other observable behaviors

}



TEST_F(DependencyScanTest_65, BuildLogAccess_NormalOperation_65) {

    BuildLog* log = scan_.build_log();

    EXPECT_EQ(log, &build_log_);

}



TEST_F(DependencyScanTest_65, SetBuildLog_NormalOperation_65) {

    MockBuildLog new_build_log;

    scan_.set_build_log(&new_build_log);

    BuildLog* log = scan_.build_log();

    EXPECT_EQ(log, &new_build_log);

}
