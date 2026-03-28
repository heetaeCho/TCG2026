#include <gtest/gtest.h>

#include "db/version_set.h"

#include "db/version_edit.h"

#include <set>



using namespace leveldb;



class CompactionTest_180 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options();

        compaction = new Compaction(options, 0);

        version_edit = new VersionEdit();



        file_metadata1 = new FileMetaData();

        file_metadata2 = new FileMetaData();

        file_metadata1->number = 1;

        file_metadata2->number = 2;



        compaction->inputs_[0].push_back(file_metadata1);

        compaction->inputs_[1].push_back(file_metadata2);

    }



    void TearDown() override {

        delete options;

        delete compaction;

        delete version_edit;

        delete file_metadata1;

        delete file_metadata2;

    }



    Options* options;

    Compaction* compaction;

    VersionEdit* version_edit;

    FileMetaData* file_metadata1;

    FileMetaData* file_metadata2;

};



TEST_F(CompactionTest_180, AddInputDeletions_RemovesFilesFromVersionEdit_180) {

    compaction->AddInputDeletions(version_edit);



    const DeletedFileSet& deleted_files = version_edit->deleted_files_;

    EXPECT_EQ(deleted_files.size(), 2);

    EXPECT_NE(deleted_files.find({0, 1}), deleted_files.end());

    EXPECT_NE(deleted_files.find({1, 2}), deleted_files.end());

}



TEST_F(CompactionTest_180, AddInputDeletions_NoFilesInInputs_DoesNothing_180) {

    compaction->inputs_[0].clear();

    compaction->inputs_[1].clear();

    compaction->AddInputDeletions(version_edit);



    const DeletedFileSet& deleted_files = version_edit->deleted_files_;

    EXPECT_EQ(deleted_files.size(), 0);

}



TEST_F(CompactionTest_180, AddInputDeletions_MultipleFilesInInputs_RemovesAllFromVersionEdit_180) {

    FileMetaData* file_metadata3 = new FileMetaData();

    file_metadata3->number = 3;

    compaction->inputs_[0].push_back(file_metadata3);



    compaction->AddInputDeletions(version_edit);



    const DeletedFileSet& deleted_files = version_edit->deleted_files_;

    EXPECT_EQ(deleted_files.size(), 3);

    EXPECT_NE(deleted_files.find({0, 1}), deleted_files.end());

    EXPECT_NE(deleted_files.find({1, 2}), deleted_files.end());

    EXPECT_NE(deleted_files.find({0, 3}), deleted_files.end());



    delete file_metadata3;

}
