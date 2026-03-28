#include <gtest/gtest.h>

#include "db/version_edit.h"



using namespace leveldb;



class VersionEditTest_343 : public ::testing::Test {

protected:

    void SetUp() override {

        version_edit_.Clear();

    }



    VersionEdit version_edit_;

};



TEST_F(VersionEditTest_343, DefaultConstructorCreatesEmptyDebugString_343) {

    EXPECT_EQ(version_edit_.DebugString(), "VersionEdit {\n}\n");

}



TEST_F(VersionEditTest_343, SetComparatorNameUpdatesDebugString_343) {

    version_edit_.SetComparatorName("test_comparator");

    EXPECT_TRUE(version_edit_.DebugString().find("Comparator: test_comparator") != std::string::npos);

}



TEST_F(VersionEditTest_343, SetLogNumberUpdatesDebugString_343) {

    version_edit_.SetLogNumber(12345);

    EXPECT_TRUE(version_edit_.DebugString().find("LogNumber: 12345") != std::string::npos);

}



TEST_F(VersionEditTest_343, SetPrevLogNumberUpdatesDebugString_343) {

    version_edit_.SetPrevLogNumber(67890);

    EXPECT_TRUE(version_edit_.DebugString().find("PrevLogNumber: 67890") != std::string::npos);

}



TEST_F(VersionEditTest_343, SetNextFileUpdatesDebugString_343) {

    version_edit_.SetNextFile(1000);

    EXPECT_TRUE(version_edit_.DebugString().find("NextFile: 1000") != std::string::npos);

}



TEST_F(VersionEditTest_343, SetLastSequenceUpdatesDebugString_343) {

    version_edit_.SetLastSequence(54321);

    EXPECT_TRUE(version_edit_.DebugString().find("LastSeq: 54321") != std::string::npos);

}



TEST_F(VersionEditTest_343, SetCompactPointerUpdatesDebugString_343) {

    InternalKey key;

    version_edit_.SetCompactPointer(0, key);

    EXPECT_TRUE(version_edit_.DebugString().find("CompactPointer: 0") != std::string::npos);

}



TEST_F(VersionEditTest_343, AddFileUpdatesDebugString_343) {

    InternalKey smallest, largest;

    version_edit_.AddFile(1, 200, 1024, smallest, largest);

    EXPECT_TRUE(version_edit_.DebugString().find("AddFile: 1") != std::string::npos);

}



TEST_F(VersionEditTest_343, RemoveFileUpdatesDebugString_343) {

    version_edit_.RemoveFile(2, 300);

    EXPECT_TRUE(version_edit_.DebugString().find("RemoveFile: 2") != std::string::npos);

}



TEST_F(VersionEditTest_343, ClearResetsAllFields_343) {

    version_edit_.SetComparatorName("test_comparator");

    version_edit_.SetLogNumber(12345);

    version_edit_.SetPrevLogNumber(67890);

    version_edit_.SetNextFile(1000);

    version_edit_.SetLastSequence(54321);

    InternalKey key;

    version_edit_.SetCompactPointer(0, key);

    InternalKey smallest, largest;

    version_edit_.AddFile(1, 200, 1024, smallest, largest);

    version_edit_.RemoveFile(2, 300);



    version_edit_.Clear();

    EXPECT_EQ(version_edit_.DebugString(), "VersionEdit {\n}\n");

}



TEST_F(VersionEditTest_343, BoundaryCondition_SetLogNumberZero_343) {

    version_edit_.SetLogNumber(0);

    EXPECT_TRUE(version_edit_.DebugString().find("LogNumber: 0") != std::string::npos);

}



TEST_F(VersionEditTest_343, BoundaryCondition_SetNextFileMaxValue_343) {

    version_edit_.SetNextFile(UINT64_MAX);

    EXPECT_TRUE(version_edit_.DebugString().find("NextFile: 18446744073709551615") != std::string::npos);

}



TEST_F(VersionEditTest_343, BoundaryCondition_SetLastSequenceMaxValue_343) {

    version_edit_.SetLastSequence(UINT64_MAX);

    EXPECT_TRUE(version_edit_.DebugString().find("LastSeq: 18446744073709551615") != std::string::npos);

}



TEST_F(VersionEditTest_343, BoundaryCondition_SetCompactPointerLevelMaxValue_343) {

    InternalKey key;

    version_edit_.SetCompactPointer(INT_MAX, key);

    EXPECT_TRUE(version_edit_.DebugString().find("CompactPointer: 2147483647") != std::string::npos);

}



TEST_F(VersionEditTest_343, BoundaryCondition_AddFileLevelMaxValue_343) {

    InternalKey smallest, largest;

    version_edit_.AddFile(INT_MAX, 0, 0, smallest, largest);

    EXPECT_TRUE(version_edit_.DebugString().find("AddFile: 2147483647") != std::string::npos);

}



TEST_F(VersionEditTest_343, BoundaryCondition_RemoveFileLevelMaxValue_343) {

    version_edit_.RemoveFile(INT_MAX, 0);

    EXPECT_TRUE(version_edit_.DebugString().find("RemoveFile: 2147483647") != std::string::npos);

}
