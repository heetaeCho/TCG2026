#include <gtest/gtest.h>

#include "db/version_edit.h"



using namespace leveldb;



class VersionEditTest_63 : public ::testing::Test {

protected:

    VersionEdit* version_edit_;



    void SetUp() override {

        version_edit_ = new VersionEdit();

    }



    void TearDown() override {

        delete version_edit_;

    }

};



TEST_F(VersionEditTest_63, SetPrevLogNumber_NormalOperation_63) {

    uint64_t prev_log_number = 12345;

    version_edit_->SetPrevLogNumber(prev_log_number);

}



TEST_F(VersionEditTest_63, SetPrevLogNumber_BoundaryCondition_Zero_63) {

    uint64_t prev_log_number = 0;

    version_edit_->SetPrevLogNumber(prev_log_number);

}



TEST_F(VersionEditTest_63, SetPrevLogNumber_BoundaryCondition_MaxUint64_63) {

    uint64_t prev_log_number = UINT64_MAX;

    version_edit_->SetPrevLogNumber(prev_log_number);

}
