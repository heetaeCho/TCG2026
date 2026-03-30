#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Edge and TimeStamp are defined elsewhere in the codebase.

struct Edge {};

using TimeStamp = int64_t;



// Mocking DiskInterface as it's an external collaborator.

class DiskInterface {

public:

    virtual ~DiskInterface() {}

    virtual bool Stat(const std::string& path, TimeStamp* mtime, std::string* err) = 0;

};



TEST_F(NodeTest_51, ValidationOutEdges_ReturnsEmptyVector_51) {

    Node node("dummy_path", 0);

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_51, ValidationOutEdges_ReturnsAddedEdge_51) {

    Node node("dummy_path", 0);

    Edge* edge = new Edge();

    node.AddValidationOutEdge(edge);

    EXPECT_EQ(1, node.validation_out_edges().size());

    EXPECT_EQ(edge, node.validation_out_edges()[0]);

    delete edge;

}



TEST_F(NodeTest_51, StatIfNecessary_CallsDiskInterfaceStat_51) {

    class MockDiskInterface : public DiskInterface {

    public:

        MOCK_METHOD3(Stat, bool(const std::string&, TimeStamp*, std::string*));

    };



    MockDiskInterface mock_disk_interface;

    Node node("dummy_path", 0);

    EXPECT_CALL(mock_disk_interface, Stat(node.path(), testing::_, testing::_)).Times(1);



    std::string err;

    node.StatIfNecessary(&mock_disk_interface, &err);

}



TEST_F(NodeTest_51, StatIfNecessary_ReturnsFalseOnDiskInterfaceFailure_51) {

    class MockDiskInterface : public DiskInterface {

    public:

        MOCK_METHOD3(Stat, bool(const std::string&, TimeStamp*, std::string*));

    };



    MockDiskInterface mock_disk_interface;

    Node node("dummy_path", 0);

    EXPECT_CALL(mock_disk_interface, Stat(node.path(), testing::_, testing::_)).WillOnce(testing::Return(false));



    std::string err;

    bool result = node.StatIfNecessary(&mock_disk_interface, &err);

    EXPECT_FALSE(result);

}



TEST_F(NodeTest_51, StatIfNecessary_ReturnsTrueOnDiskInterfaceSuccess_51) {

    class MockDiskInterface : public DiskInterface {

    public:

        MOCK_METHOD3(Stat, bool(const std::string&, TimeStamp*, std::string*));

    };



    MockDiskInterface mock_disk_interface;

    Node node("dummy_path", 0);

    EXPECT_CALL(mock_disk_interface, Stat(node.path(), testing::_, testing::_)).WillOnce(testing::Return(true));



    std::string err;

    bool result = node.StatIfNecessary(&mock_disk_interface, &err);

    EXPECT_TRUE(result);

}



TEST_F(NodeTest_51, ResetState_ResetsAllStates_51) {

    Node node("dummy_path", 0);

    Edge* edge = new Edge();

    node.AddOutEdge(edge);

    node.MarkMissing();

    node.set_dirty(true);



    node.ResetState();



    EXPECT_FALSE(node.exists());

    EXPECT_EQ(-1, node.mtime());

    EXPECT_FALSE(node.dirty());

    EXPECT_TRUE(node.out_edges().empty());



    delete edge;

}



TEST_F(NodeTest_51, MarkDirty_SetsDirtyToTrue_51) {

    Node node("dummy_path", 0);

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_51, SetInEdge_SetsInEdgeCorrectly_51) {

    Node node("dummy_path", 0);

    Edge* edge = new Edge();

    node.set_in_edge(edge);

    EXPECT_EQ(edge, node.in_edge());



    delete edge;

}



TEST_F(NodeTest_51, SetGeneratedByDepLoader_SetsFlagCorrectly_51) {

    Node node("dummy_path", 0);

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_51, SetId_SetsIdCorrectly_51) {

    Node node("dummy_path", 0);

    int id = 42;

    node.set_id(id);

    EXPECT_EQ(id, node.id());

}
