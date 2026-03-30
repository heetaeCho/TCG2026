#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "subprocess.h"



using ::testing::Return;



class SubprocessSetTest : public ::testing::Test {

protected:

    SubprocessSet subprocess_set_;

};



TEST_F(SubprocessSetTest_93, AddCommand_NormalOperation_93) {

    Subprocess* subprocess = subprocess_set_.Add("test_command", false);

    ASSERT_NE(subprocess, nullptr);

}



TEST_F(SubprocessSetTest_93, DoWork_ReturnsFalseWhenNoSubprocesses_93) {

    bool result = subprocess_set_.DoWork();

    EXPECT_FALSE(result);

}



TEST_F(SubprocessSetTest_93, NextFinished_ReturnsNullptrWhenNoFinishedSubprocesses_93) {

    Subprocess* finished_subprocess = subprocess_set_.NextFinished();

    EXPECT_EQ(finished_subprocess, nullptr);

}



TEST_F(SubprocessSetTest_93, Clear_DoesNotCrashWithEmptySet_93) {

    subprocess_set_.Clear();  // Should not throw or crash

}



TEST_F(SubprocessSetTest_93, SetInterruptedFlag_SetsInterruptedState_93) {

    SubprocessSet::SetInterruptedFlag(SIGINT);

    EXPECT_TRUE(SubprocessSet::IsInterrupted());

}



TEST_F(SubprocessSetTest_93, IsInterrupted_ReturnsFalseInitially_93) {

    EXPECT_FALSE(SubprocessSet::IsInterrupted());

}



TEST_F(SubprocessSetTest_93, HandlePendingInterruption_DoesNotCrash_93) {

    subprocess_set_.HandlePendingInterruption();  // Should not throw or crash

}
