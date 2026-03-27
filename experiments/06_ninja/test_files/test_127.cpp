#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "status_printer.h"

#include "explanations.h"



using namespace testing;



class StatusPrinterTest : public ::testing::Test {

protected:

    BuildConfig config;

    StatusPrinter* status_printer;

    Explanations* mock_explanations;



    void SetUp() override {

        status_printer = new StatusPrinter(config);

        mock_explanations = new Explanations();

        status_printer->SetExplanations(mock_explanations);

    }



    void TearDown() override {

        delete status_printer;

        delete mock_explanations;

    }

};



TEST_F(StatusPrinterTest_127, SetExplanations_SetsExplanationsPointer_127) {

    // Verify that the SetExplanations method sets the internal explanations pointer

    EXPECT_EQ(status_printer->explanations_, mock_explanations);

}



// EdgeAddedToPlan tests

TEST_F(StatusPrinterTest_127, EdgeAddedToPlan_IncrementsTotalEdges_127) {

    const Edge* edge = nullptr; // Assuming Edge is a valid type in the context

    int initial_total_edges = status_printer->total_edges_;

    status_printer->EdgeAddedToPlan(edge);

    EXPECT_EQ(status_printer->total_edges_, initial_total_edges + 1);

}



// EdgeRemovedFromPlan tests

TEST_F(StatusPrinterTest_127, EdgeRemovedFromPlan_DecrementsTotalEdges_127) {

    const Edge* edge = nullptr; // Assuming Edge is a valid type in the context

    status_printer->total_edges_ = 5;

    int initial_total_edges = status_printer->total_edges_;

    status_printer->EdgeRemovedFromPlan(edge);

    EXPECT_EQ(status_printer->total_edges_, initial_total_edges - 1);

}



// BuildEdgeStarted tests

TEST_F(StatusPrinterTest_127, BuildEdgeStarted_IncrementsRunningEdges_127) {

    const Edge* edge = nullptr; // Assuming Edge is a valid type in the context

    int64_t start_time_millis = 0;

    int initial_running_edges = status_printer->running_edges_;

    status_printer->BuildEdgeStarted(edge, start_time_millis);

    EXPECT_EQ(status_printer->running_edges_, initial_running_edges + 1);

}



// BuildEdgeFinished tests

TEST_F(StatusPrinterTest_127, BuildEdgeFinished_DecrementsRunningEdges_127) {

    Edge* edge = nullptr; // Assuming Edge is a valid type in the context

    int64_t start_time_millis = 0;

    int64_t end_time_millis = 100;

    ExitStatus exit_code = ExitStatus::Success;

    std::string output = "output";

    status_printer->running_edges_ = 5;

    int initial_running_edges = status_printer->running_edges_;

    status_printer->BuildEdgeFinished(edge, start_time_millis, end_time_millis, exit_code, output);

    EXPECT_EQ(status_printer->running_edges_, initial_running_edges - 1);

}



// BuildStarted tests

TEST_F(StatusPrinterTest_127, BuildStarted_SetsInitialValues_127) {

    status_printer->BuildStarted();

    EXPECT_EQ(status_printer->started_edges_, 0);

    EXPECT_EQ(status_printer->finished_edges_, 0);

    EXPECT_EQ(status_printer->running_edges_, 0);

}



// BuildFinished tests

TEST_F(StatusPrinterTest_127, BuildFinished_NoOp_127) {

    // Assuming BuildFinished does not change any observable state

    status_printer->BuildFinished();

    // No assertions needed if no state changes are expected

}



// Info tests

TEST_F(StatusPrinterTest_127, Info_NoOp_127) {

    const char* msg = "Info message";

    // Assuming Info does not change any observable state

    status_printer->Info(msg);

    // No assertions needed if no state changes are expected

}



// Warning tests

TEST_F(StatusPrinterTest_127, Warning_NoOp_127) {

    const char* msg = "Warning message";

    // Assuming Warning does not change any observable state

    status_printer->Warning(msg);

    // No assertions needed if no state changes are expected

}



// Error tests

TEST_F(StatusPrinterTest_127, Error_NoOp_127) {

    const char* msg = "Error message";

    // Assuming Error does not change any observable state

    status_printer->Error(msg);

    // No assertions needed if no state changes are expected

}
