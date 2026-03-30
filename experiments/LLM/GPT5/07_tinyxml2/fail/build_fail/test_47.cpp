// File: test_xmlnode_todeclaration_47.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLNodeToDeclarationTest_47 : public ::testing::Test {};

// A small derived type to verify virtual dispatch without relying on tinyxml2 internals.
class DerivedNodeReturnsDeclaration_47 : public tinyxml2::XMLNode {
public:
	// Return a known (non-null) sentinel pointer.
	tinyxml2::XMLDeclaration* ToDeclaration() override {
		return reinterpret_cast<tinyxml2::XMLDeclaration*>(kSentinel);
	}

	static constexpr uintptr_t kSentinel = 0x1234;
};

}  // namespace

TEST_F(XMLNodeToDeclarationTest_47, DefaultImplementationReturnsNull_47) {
	tinyxml2::XMLNode node;
	EXPECT_EQ(node.ToDeclaration(), nullptr);
}

TEST_F(XMLNodeToDeclarationTest_47, VirtualDispatchUsesOverride_47) {
	DerivedNodeReturnsDeclaration_47 derived;
	tinyxml2::XMLNode* asBase = &derived;

	auto* decl = asBase->ToDeclaration();
	EXPECT_NE(decl, nullptr);
	EXPECT_EQ(reinterpret_cast<uintptr_t>(decl), DerivedNodeReturnsDeclaration_47::kSentinel);
}

TEST_F(XMLNodeToDeclarationTest_47, CanCallMultipleTimesConsistently_47) {
	tinyxml2::XMLNode node;
	EXPECT_EQ(node.ToDeclaration(), nullptr);
	EXPECT_EQ(node.ToDeclaration(), nullptr);
}
