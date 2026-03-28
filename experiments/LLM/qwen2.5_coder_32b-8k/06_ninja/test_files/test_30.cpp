#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include "disk_interface.h"



using ::testing::_;

using ::testing::Return;

using ::testing::SetArgReferee;



class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(TimeStamp, Stat, (const std::string& path, std::string* err), (override));

    MOCK_METHOD(bool, MakeDir, (const std::string& path), (override));

    MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& contents, bool crlf_on_windows), (override));

    MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));

};



class NodeTest : public ::testing::Test {

protected:

    MockDiskInterface mock_disk_interface;

    Node node{"path/to/file", 12345};

};



TEST_F(NodeTest_30, StatIfNecessary_StatusKnown_ReturnsTrue_30) {

    EXPECT_CALL(mock_disk_interface, Stat(_, _)).Times(0);

    node.UpdatePhonyMtime(100); // Ensure status is known

    ASSERT_TRUE(node.StatIfNecessary(&mock_disk_interface, nullptr));

}



TEST_F(NodeTest_30, StatIfNecessary_StatusNotKnown_CallsStat_ReturnsTrue_30) {

    std::string err;

    TimeStamp mtime = 12345;

    EXPECT_CALL(mock_disk_interface, Stat("path/to/file", _))

        .WillOnce(DoAll(SetArgReferee<1>(err), Return(mtime)));

    ASSERT_TRUE(node.StatIfNecessary(&mock_disk_interface, &err));

}



TEST_F(NodeTest_30, StatIfNecessary_StatusNotKnown_CallsStat_ReturnsFalse_30) {

    std::string err;

    EXPECT_CALL(mock_disk_interface, Stat("path/to/file", _))

        .WillOnce(DoAll(SetArgReferee<1>("Error"), Return(-1)));

    ASSERT_FALSE(node.StatIfNecessary(&mock_disk_interface, &err));

    EXPECT_EQ(err, "Error");

}



TEST_F(NodeTest_30, StatIfNecessary_StatusNotKnown_ErrPtrNull_ReturnsTrue_30) {

    TimeStamp mtime = 12345;

    EXPECT_CALL(mock_disk_interface, Stat("path/to/file", _))

        .WillOnce(Return(mtime));

    ASSERT_TRUE(node.StatIfNecessary(&mock_disk_interface, nullptr));

}



TEST_F(NodeTest_30, StatIfNecessary_StatusNotKnown_ErrPtrNull_ReturnsFalse_30) {

    EXPECT_CALL(mock_disk_interface, Stat("path/to/file", _))

        .WillOnce(Return(-1));

    ASSERT_FALSE(node.StatIfNecessary(&mock_disk_interface, nullptr));

}
