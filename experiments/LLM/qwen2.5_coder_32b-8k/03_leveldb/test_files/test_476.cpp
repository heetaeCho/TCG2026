#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_edit.h"



using namespace leveldb;

using ::testing::Return;



class VersionEditTest_476 : public ::testing::Test {

protected:

    VersionEdit* version_edit;



    void SetUp() override {

        version_edit = new VersionEdit();

    }



    void TearDown() override {

        delete version_edit;

    }

};



TEST_F(VersionEditTest_476, ClearResetsAllFields_476) {

    // Set some fields

    version_edit->SetComparatorName("comparator");

    version_edit->SetLogNumber(1);

    version_edit->SetPrevLogNumber(2);

    version_edit->SetNextFile(3);

    version_edit->SetLastSequence(4);

    version_edit->SetCompactPointer(5, InternalKey());

    version_edit->AddFile(6, 7, 8, InternalKey(), InternalKey());



    // Clear the VersionEdit object

    version_edit->Clear();



    // Check if all fields are reset

    std::string debug_string = version_edit->DebugString();

    EXPECT_TRUE(debug_string.find("comparator") == std::string::npos);

    EXPECT_TRUE(debug_string.find("log_number") == std::string::npos);

    EXPECT_TRUE(debug_string.find("prev_log_number") == std::string::npos);

    EXPECT_TRUE(debug_string.find("next_file_number") == std::string::npos);

    EXPECT_TRUE(debug_string.find("last_sequence") == std::string::npos);

    EXPECT_TRUE(debug_string.find("compact_pointer") == std::string::npos);

    EXPECT_TRUE(debug_string.find("add_file") == std::string::npos);

}



TEST_F(VersionEditTest_476, SetComparatorNameUpdatesDebugString_476) {

    version_edit->SetComparatorName("test_comparator");

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("comparator=test_comparator"));

}



TEST_F(VersionEditTest_476, SetLogNumberUpdatesDebugString_476) {

    version_edit->SetLogNumber(123);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("log_number=123"));

}



TEST_F(VersionEditTest_476, SetPrevLogNumberUpdatesDebugString_476) {

    version_edit->SetPrevLogNumber(456);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("prev_log_number=456"));

}



TEST_F(VersionEditTest_476, SetNextFileUpdatesDebugString_476) {

    version_edit->SetNextFile(789);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("next_file_number=789"));

}



TEST_F(VersionEditTest_476, SetLastSequenceUpdatesDebugString_476) {

    version_edit->SetLastSequence(101112);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("last_sequence=101112"));

}



TEST_F(VersionEditTest_476, SetCompactPointerUpdatesDebugString_476) {

    InternalKey key;

    version_edit->SetCompactPointer(3, key);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("compact_pointer=3:"));

}



TEST_F(VersionEditTest_476, AddFileUpdatesDebugString_476) {

    InternalKey smallest, largest;

    version_edit->AddFile(1, 2, 3, smallest, largest);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("add_file=1:2:3:"));

}



TEST_F(VersionEditTest_476, RemoveFileUpdatesDebugString_476) {

    version_edit->RemoveFile(1, 2);

    EXPECT_THAT(version_edit->DebugString(), testing::HasSubstr("del_file=1:2"));

}



TEST_F(VersionEditTest_476, EncodeToAndDecodeFromWorkTogether_476) {

    std::string encoded;

    version_edit->SetComparatorName("comparator");

    version_edit->EncodeTo(&encoded);



    VersionEdit decoded_version_edit;

    Slice src(encoded);

    Status status = decoded_version_edit.DecodeFrom(src);

    EXPECT_TRUE(status.ok());



    EXPECT_EQ(version_edit->DebugString(), decoded_version_edit.DebugString());

}
