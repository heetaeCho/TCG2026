#include <gtest/gtest.h>

#include "db/version_edit.h"



namespace leveldb {



class VersionEditTest_62 : public ::testing::Test {

protected:

    VersionEdit* version_edit;



    void SetUp() override {

        version_edit = new VersionEdit();

    }



    void TearDown() override {

        delete version_edit;

    }

};



TEST_F(VersionEditTest_62, SetLogNumber_SetsCorrectly_62) {

    uint64_t log_number = 12345;

    version_edit->SetLogNumber(log_number);

    // Since we cannot access private members directly, we rely on observable behavior.

    // Here we assume that EncodeTo and DecodeFrom can be used to verify the set value.

    std::string encoded;

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    ASSERT_EQ(decoded_version_edit.log_number_, log_number);

}



TEST_F(VersionEditTest_62, SetLogNumber_MultipleTimes_62) {

    uint64_t first_log_number = 12345;

    uint64_t second_log_number = 67890;



    version_edit->SetLogNumber(first_log_number);

    version_edit->SetLogNumber(second_log_number);



    std::string encoded;

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    ASSERT_EQ(decoded_version_edit.log_number_, second_log_number);

}



TEST_F(VersionEditTest_62, SetLogNumber_BoundaryCondition_62) {

    uint64_t max_log_number = UINT64_MAX;

    version_edit->SetLogNumber(max_log_number);



    std::string encoded;

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    ASSERT_EQ(decoded_version_edit.log_number_, max_log_number);

}



TEST_F(VersionEditTest_62, SetLogNumber_ZeroValue_62) {

    uint64_t zero_log_number = 0;

    version_edit->SetLogNumber(zero_log_number);



    std::string encoded;

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    ASSERT_EQ(decoded_version_edit.log_number_, zero_log_number);

}



TEST_F(VersionEditTest_62, Clear_ResetsLogNumber_62) {

    uint64_t log_number = 12345;

    version_edit->SetLogNumber(log_number);

    version_edit->Clear();



    std::string encoded;

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Status status = decoded_version_edit.DecodeFrom(Slice(encoded));

    ASSERT_TRUE(status.ok());

    ASSERT_FALSE(decoded_version_edit.has_log_number_);

}



}  // namespace leveldb
