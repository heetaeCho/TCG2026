#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
#include "XMP_Environment.h"
#include "XMP_Const.h"
#include "ExpatAdapter.hpp"
#include "XMLParserAdapter.hpp"

class ExpatAdapterTest_2096 : public ::testing::Test {
protected:
    ExpatAdapter* adapter;

    void SetUp() override {
        adapter = XMP_NewExpatAdapter(false);
        ASSERT_NE(adapter, nullptr);
    }

    void TearDown() override {
        if (adapter) {
            delete adapter;
            adapter = nullptr;
        }
    }

    void ParseXML(const std::string& xml) {
        adapter->ParseBuffer(xml.c_str(), xml.size(), true);
    }
};

// Test: Basic XML parsing with xpacket PI
TEST_F(ExpatAdapterTest_2096, ParseXpacketPI_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    // The tree should have content from parsing
    XML_Node& tree = adapter->tree;
    // Check that PI nodes with target "xpacket" were added
    bool foundXpacketPI = false;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            foundXpacketPI = true;
            break;
        }
    }
    EXPECT_TRUE(foundXpacketPI);
}

// Test: Non-xpacket PI should be ignored
TEST_F(ExpatAdapterTest_2096, NonXpacketPIIgnored_2096) {
    std::string xml = "<?xml version='1.0'?>"
                      "<?somethingelse data='test'?>"
                      "<root/>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    // Check that no PI node with name "somethingelse" exists
    XML_Node& tree = adapter->tree;
    bool foundNonXpacketPI = false;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "somethingelse") {
            foundNonXpacketPI = true;
            break;
        }
    }
    EXPECT_FALSE(foundNonXpacketPI);
}

// Test: xpacket PI with data should store value
TEST_F(ExpatAdapterTest_2096, XpacketPIStoresValue_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    // Find xpacket PI nodes and verify they have values
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            // The value should be the data portion of the PI
            EXPECT_FALSE(tree.content[i]->value.empty());
        }
    }
}

// Test: xpacket end PI
TEST_F(ExpatAdapterTest_2096, XpacketEndPI_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    // Look for end PI
    bool foundEndPI = false;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            if (tree.content[i]->value.find("end") != std::string::npos) {
                foundEndPI = true;
            }
        }
    }
    EXPECT_TRUE(foundEndPI);
}

// Test: PI node kind is kPINode
TEST_F(ExpatAdapterTest_2096, PINodeKindIsCorrect_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->name == "xpacket") {
            EXPECT_EQ(tree.content[i]->kind, kPINode);
        }
    }
}

// Test: PI node parent is correct
TEST_F(ExpatAdapterTest_2096, PINodeParentIsCorrect_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            EXPECT_EQ(tree.content[i]->parent, &tree);
        }
    }
}

// Test: Simple element parsing
TEST_F(ExpatAdapterTest_2096, SimpleElementParsing_2096) {
    std::string xml = "<root><child>text</child></root>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    EXPECT_GT(tree.content.size(), 0u);
}

// Test: Empty XML element
TEST_F(ExpatAdapterTest_2096, EmptyElement_2096) {
    std::string xml = "<root/>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    EXPECT_GT(tree.content.size(), 0u);
}

// Test: Multiple xpacket PIs are added
TEST_F(ExpatAdapterTest_2096, MultipleXpacketPIs_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    int piCount = 0;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            piCount++;
        }
    }
    EXPECT_EQ(piCount, 2);
}

// Test: Parsing in chunks (not last)
TEST_F(ExpatAdapterTest_2096, ParseBufferInChunks_2096) {
    std::string part1 = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>";
    std::string part2 = "<root/>";
    std::string part3 = "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW({
        adapter->ParseBuffer(part1.c_str(), part1.size(), false);
        adapter->ParseBuffer(part2.c_str(), part2.size(), false);
        adapter->ParseBuffer(part3.c_str(), part3.size(), true);
    });
    
    XML_Node& tree = adapter->tree;
    EXPECT_GT(tree.content.size(), 0u);
}

// Test: xpacket PI name is stored correctly
TEST_F(ExpatAdapterTest_2096, XpacketPINameStoredCorrectly_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode) {
            EXPECT_EQ(tree.content[i]->name, "xpacket");
        }
    }
}

// Test: Tree root kind is kRootNode
TEST_F(ExpatAdapterTest_2096, TreeRootKind_2096) {
    EXPECT_EQ(adapter->tree.kind, kRootNode);
}

// Test: Initial tree state
TEST_F(ExpatAdapterTest_2096, InitialTreeState_2096) {
    EXPECT_EQ(adapter->tree.kind, kRootNode);
    EXPECT_TRUE(adapter->tree.name.empty());
}

// Test: Parse with namespace
TEST_F(ExpatAdapterTest_2096, ParseWithNamespace_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<x:root xmlns:x='http://example.com'>"
                      "<x:child>value</x:child>"
                      "</x:root>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    EXPECT_GT(tree.content.size(), 0u);
}

// Test: Parse empty buffer as last
TEST_F(ExpatAdapterTest_2096, ParseEmptyBufferAsLast_2096) {
    std::string xml = "<root/>";
    adapter->ParseBuffer(xml.c_str(), xml.size(), false);
    EXPECT_NO_THROW(adapter->ParseBuffer("", 0, true));
}

// Test: xpacket begin PI value content
TEST_F(ExpatAdapterTest_2096, XpacketBeginPIValueContent_2096) {
    std::string xml = "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
                      "<root/>"
                      "<?xpacket end='w'?>";
    
    EXPECT_NO_THROW(ParseXML(xml));
    
    XML_Node& tree = adapter->tree;
    bool foundBeginPI = false;
    for (size_t i = 0; i < tree.content.size(); ++i) {
        if (tree.content[i]->kind == kPINode && tree.content[i]->name == "xpacket") {
            if (tree.content[i]->value.find("begin") != std::string::npos) {
                foundBeginPI = true;
                // Verify the value contains the expected data
                EXPECT_NE(tree.content[i]->value.find("id="), std::string::npos);
            }
        }
    }
    EXPECT_TRUE(foundBeginPI);
}
