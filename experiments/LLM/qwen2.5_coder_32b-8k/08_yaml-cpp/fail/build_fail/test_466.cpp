#include <gtest/gtest.h>

#include "emitterstate.h"

#include <yaml-cpp/emitterstyle.h>



namespace YAML {

    enum class GroupType : int { Seq, Map };

    enum class FlowType : int { Block, Flow };



    struct SettingChanges {};

}



using namespace YAML;



class EmitterStateTest_466 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    Group CreateGroup(GroupType type, FlowType flowType) {

        return Group(type);

    }

};



TEST_F(EmitterStateTest_466, NodeType_Seq_Block_466) {

    Group group(GroupType::Seq, FlowType::Block);

    EXPECT_EQ(group.NodeType(), EmitterNodeType::BlockSeq);

}



TEST_F(EmitterStateTest_466, NodeType_Seq_Flow_466) {

    Group group(GroupType::Seq, FlowType::Flow);

    EXPECT_EQ(group.NodeType(), EmitterNodeType::FlowSeq);

}



TEST_F(EmitterStateTest_466, NodeType_Map_Block_466) {

    Group group(GroupType::Map, FlowType::Block);

    EXPECT_EQ(group.NodeType(), EmitterNodeType::BlockMap);

}



TEST_F(EmitterStateTest_466, NodeType_Map_Flow_466) {

    Group group(GroupType::Map, FlowType::Flow);

    EXPECT_EQ(group.NodeType(), EmitterNodeType::FlowMap);

}

```


