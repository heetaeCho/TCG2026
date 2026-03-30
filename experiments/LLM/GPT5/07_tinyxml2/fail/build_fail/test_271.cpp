// File: ./TestProjects/tinyxml2/tests/XMLDocumentDeepCopyTest_271.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

static std::string DocToString(const XMLDocument& doc)
{
	XMLPrinter printer;
	doc.Print(&printer);
	return std::string(printer.CStr() ? printer.CStr() : "");
}

class DeepCopyTest_271 : public ::testing::Test {
protected:
	// Builds a simple but non-trivial document structure.
	// <root a="1"><child>text</child><!--c--><?pi?></root>
	static void BuildSampleDoc(XMLDocument& doc)
	{
		XMLElement* root = doc.NewElement("root");
		ASSERT_NE(root, nullptr);
		root->SetAttribute("a", "1");
		doc.InsertEndChild(root);

		XMLElement* child = doc.NewElement("child");
		ASSERT_NE(child, nullptr);
		child->SetText("text");
		root->InsertEndChild(child);

		XMLComment* comment = doc.NewComment("c");
		ASSERT_NE(comment, nullptr);
		root->InsertEndChild(comment);

		XMLDeclaration* decl = doc.NewDeclaration("pi");
		ASSERT_NE(decl, nullptr);
		root->InsertEndChild(decl);
	}
};

}  // namespace

TEST_F(DeepCopyTest_271, CopiesFullDocumentTree_271)
{
	XMLDocument src(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(src);

	XMLDocument dst(true, WHITESPACE_PRESERVE);
	ASSERT_TRUE(dst.NoChildren());

	src.DeepCopy(&dst);

	// Observable behavior: serialized output matches.
	EXPECT_EQ(DocToString(dst), DocToString(src));

	// Also ensure dst now has a root element.
	ASSERT_NE(dst.RootElement(), nullptr);
	EXPECT_STREQ(dst.RootElement()->Name(), "root");
}

TEST_F(DeepCopyTest_271, OverwritesExistingTargetContent_271)
{
	XMLDocument src(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(src);

	XMLDocument dst(true, WHITESPACE_PRESERVE);
	// Pre-populate dst with different content.
	{
		XMLElement* other = dst.NewElement("other");
		ASSERT_NE(other, nullptr);
		other->SetAttribute("b", "2");
		dst.InsertEndChild(other);
	}
	const std::string before = DocToString(dst);
	ASSERT_FALSE(before.empty());

	src.DeepCopy(&dst);

	// After DeepCopy, dst should match src (and not keep old content).
	EXPECT_EQ(DocToString(dst), DocToString(src));
	EXPECT_NE(DocToString(dst), before);
}

TEST_F(DeepCopyTest_271, SelfCopyIsNoOpAndDoesNotCrash_271)
{
	XMLDocument doc(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(doc);
	const std::string before = DocToString(doc);

	// Should be a no-op per interface comment (technically success).
	doc.DeepCopy(&doc);

	EXPECT_EQ(DocToString(doc), before);
}

TEST_F(DeepCopyTest_271, CopyingEmptySourceClearsTarget_271)
{
	XMLDocument emptySrc(true, WHITESPACE_PRESERVE);
	ASSERT_TRUE(emptySrc.NoChildren());

	XMLDocument dst(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(dst);
	ASSERT_FALSE(dst.NoChildren());

	emptySrc.DeepCopy(&dst);

	// Observable: destination becomes empty as well.
	EXPECT_TRUE(dst.NoChildren());
	EXPECT_EQ(DocToString(dst), DocToString(emptySrc));
}

TEST_F(DeepCopyTest_271, CopiedNodesBelongToTargetDocument_271)
{
	XMLDocument src(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(src);

	XMLDocument dst(true, WHITESPACE_PRESERVE);
	src.DeepCopy(&dst);

	// Use only public API: walk top-level children and ensure GetDocument() is dst.
	for (const XMLNode* n = dst.FirstChild(); n; n = n->NextSibling()) {
		ASSERT_NE(n->GetDocument(), nullptr);
		EXPECT_EQ(n->GetDocument(), &dst);
	}
}

// Death test for null target: DeepCopy has TIXMLASSERT(target).
// This is typically active in debug builds. Guard to avoid flakes in release builds.
#if GTEST_HAS_DEATH_TEST
TEST_F(DeepCopyTest_271, NullTargetTriggersAssertInDebug_271)
{
	XMLDocument src(true, WHITESPACE_PRESERVE);
	BuildSampleDoc(src);

	// In many builds, TIXMLASSERT maps to assert(), which aborts.
#ifndef NDEBUG
	EXPECT_DEATH({ src.DeepCopy(nullptr); }, ".*");
#else
	// In release builds, assert may be compiled out; just ensure it doesn't crash the test harness
	// by not calling it.
	GTEST_SKIP() << "Assertions disabled (NDEBUG); skipping death test.";
#endif
}
#endif
