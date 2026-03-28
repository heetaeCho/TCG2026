// poppler-structure-element-text-indent-test_2567.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

namespace {

static std::string GetEnvOrEmpty(const char *name)
{
    const char *v = std::getenv(name);
    return v ? std::string(v) : std::string();
}

static std::string JoinPath(const std::string &a, const std::string &b)
{
    if (a.empty())
        return b;
    if (a.back() == G_DIR_SEPARATOR)
        return a + b;
    return a + G_DIR_SEPARATOR_S + b;
}

static std::string FindExistingPdfPath()
{
    // Try a few common env vars / locations used by Poppler test suites.
    const std::vector<std::string> roots = {
        GetEnvOrEmpty("TESTDATADIR"),
        GetEnvOrEmpty("TOP_SRCDIR"),
        GetEnvOrEmpty("SRCDIR"),
        ".", // fallback
    };

    // Common filenames for tagged/structure PDFs.
    const std::vector<std::string> rels = {
        "tagged.pdf",
        "structure.pdf",
        "struct-tree.pdf",
        "test-data/tagged.pdf",
        "test-data/structure.pdf",
        "testdata/tagged.pdf",
        "testdata/structure.pdf",
        "glib/test-data/tagged.pdf",
        "glib/test-data/structure.pdf",
        "poppler/test-data/tagged.pdf",
        "poppler/test-data/structure.pdf",
        "TestProjects/poppler/test-data/tagged.pdf",
        "TestProjects/poppler/test-data/structure.pdf",
    };

    for (const auto &root : roots) {
        if (root.empty())
            continue;
        for (const auto &rel : rels) {
            const std::string path = JoinPath(root, rel);
            if (g_file_test(path.c_str(), G_FILE_TEST_EXISTS))
                return path;
        }
    }

    // Also try rels directly (in case caller runs from test-data dir).
    for (const auto &rel : rels) {
        if (g_file_test(rel.c_str(), G_FILE_TEST_EXISTS))
            return rel;
    }

    return {};
}

static PopplerStructureElement *FindFirstMatching(PopplerStructureElement *root,
                                                  bool want_block,
                                                  int depth_limit = 128)
{
    if (!root || depth_limit <= 0)
        return nullptr;

    const gboolean is_block = poppler_structure_element_is_block(root);
    if ((want_block && is_block) || (!want_block && !is_block))
        return root;

    // poppler_structure_element_get_children() exists in poppler-glib structure API.
    GList *children = poppler_structure_element_get_children(root);
    for (GList *l = children; l != nullptr; l = l->next) {
        auto *child = static_cast<PopplerStructureElement *>(l->data);
        PopplerStructureElement *found = FindFirstMatching(child, want_block, depth_limit - 1);
        if (found) {
            // Avoid attempting to unref elements we didn't ref; just free the list container.
            g_list_free(children);
            return found;
        }
    }
    g_list_free(children);
    return nullptr;
}

class PopplerStructureTextIndentTest_2567 : public ::testing::Test {
protected:
    void SetUp() override
    {
        const std::string pdf_path = FindExistingPdfPath();
        if (pdf_path.empty()) {
            GTEST_SKIP() << "No tagged/structure PDF test file found (set TESTDATADIR/TOP_SRCDIR/SRCDIR).";
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &error);
        if (!uri) {
            std::string msg = error ? error->message : "unknown error";
            if (error)
                g_error_free(error);
            GTEST_SKIP() << "Failed to create file URI for " << pdf_path << ": " << msg;
        }

        doc_ = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);

        if (!doc_) {
            std::string msg = error ? error->message : "unknown error";
            if (error)
                g_error_free(error);
            GTEST_SKIP() << "Failed to open PDF " << pdf_path << ": " << msg;
        }

        // poppler_document_get_structure_tree() is the typical entry point for structure.
        root_ = poppler_document_get_structure_tree(doc_);
        if (!root_) {
            GTEST_SKIP() << "PDF opened but no structure tree available in this build/file.";
        }
    }

    void TearDown() override
    {
        if (root_) {
            g_object_unref(root_);
            root_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *doc_ = nullptr;
    PopplerStructureElement *root_ = nullptr;
};

} // namespace

TEST_F(PopplerStructureTextIndentTest_2567, NullElementReturnsNaN_2567)
{
    const gdouble v = poppler_structure_element_get_text_indent(nullptr);
    EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureTextIndentTest_2567, NonBlockElementReturnsNaN_2567)
{
    // Find a non-block element somewhere in the tree.
    PopplerStructureElement *non_block = FindFirstMatching(root_, /*want_block=*/false);
    if (!non_block) {
        GTEST_SKIP() << "No non-block structure element found in test document.";
    }

    const gdouble v = poppler_structure_element_get_text_indent(non_block);
    EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureTextIndentTest_2567, BlockElementReturnsNumericValue_2567)
{
    PopplerStructureElement *block = FindFirstMatching(root_, /*want_block=*/true);
    if (!block) {
        GTEST_SKIP() << "No block structure element found in test document.";
    }

    const gdouble v = poppler_structure_element_get_text_indent(block);

    // Observable behavior: for valid block elements, function should return a number (not NaN).
    EXPECT_FALSE(std::isnan(static_cast<double>(v)));
    EXPECT_TRUE(std::isfinite(static_cast<double>(v)));
}

TEST_F(PopplerStructureTextIndentTest_2567, BlockElementIsDeterministicAcrossCalls_2567)
{
    PopplerStructureElement *block = FindFirstMatching(root_, /*want_block=*/true);
    if (!block) {
        GTEST_SKIP() << "No block structure element found in test document.";
    }

    const gdouble v1 = poppler_structure_element_get_text_indent(block);
    const gdouble v2 = poppler_structure_element_get_text_indent(block);

    // If the element is valid, both results should match exactly (same element, same attribute).
    if (!std::isnan(static_cast<double>(v1)) && !std::isnan(static_cast<double>(v2))) {
        EXPECT_EQ(v1, v2);
    } else {
        // If it unexpectedly returned NaN, keep this test from silently passing without signal.
        // (Still doesn't infer internals; just makes the failure obvious.)
        EXPECT_FALSE(std::isnan(static_cast<double>(v1)));
        EXPECT_FALSE(std::isnan(static_cast<double>(v2)));
    }
}