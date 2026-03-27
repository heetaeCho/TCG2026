// poppler-structure-element-get-form-role-test_2588.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include "poppler.h"
#include "poppler-structure-element.h"

// poppler-private.h shows:
// struct _PopplerStructureElement { public const StructElement * elem; };
// We do NOT touch internal state; we only use public API.

namespace {

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

template <typename T>
using gobj_unique_ptr = std::unique_ptr<T, GObjectUnrefDeleter>;

static gobj_unique_ptr<PopplerDocument> LoadAnyTaggedPdfOrSkip() {
  // Try environment override first.
  const char *env = g_getenv("POPPLER_TEST_PDF");
  std::vector<std::string> candidates;
  if (env && *env) {
    candidates.emplace_back(env);
  }

  // Common test-data locations/names used in Poppler/GLib test suites.
  candidates.emplace_back("./TestProjects/poppler/tests/tagged.pdf");
  candidates.emplace_back("./TestProjects/poppler/tests/structure.pdf");
  candidates.emplace_back("./TestProjects/poppler/tests/data/tagged.pdf");
  candidates.emplace_back("./TestProjects/poppler/tests/data/structure.pdf");
  candidates.emplace_back("./TestProjects/poppler/glib/tests/data/tagged.pdf");
  candidates.emplace_back("./TestProjects/poppler/glib/tests/data/structure.pdf");
  candidates.emplace_back("./TestProjects/poppler/test-data/tagged.pdf");
  candidates.emplace_back("./TestProjects/poppler/test-data/structure.pdf");

  GError *error = nullptr;
  for (const auto &path : candidates) {
    if (!g_file_test(path.c_str(), G_FILE_TEST_IS_REGULAR)) {
      continue;
    }

    // poppler_document_new_from_file expects a URI.
    gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
    if (!uri) {
      if (error) {
        g_clear_error(&error);
      }
      continue;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (doc) {
      return gobj_unique_ptr<PopplerDocument>(doc);
    }
    if (error) {
      g_clear_error(&error);
    }
  }

  GTEST_SKIP() << "No suitable tagged/structure PDF found. "
                  "Set POPPLER_TEST_PDF to a tagged PDF path to enable these tests.";
  return nullptr;
}

static PopplerStructureElement *FindFirstElementByKind(PopplerStructureElement *root,
                                                       PopplerStructureElementKind kind) {
  if (!root) {
    return nullptr;
  }

  if (poppler_structure_element_get_kind(root) == kind) {
    // Keep a ref for the caller.
    return static_cast<PopplerStructureElement *>(g_object_ref(root));
  }

  const gint n = poppler_structure_element_get_n_children(root);
  for (gint i = 0; i < n; ++i) {
    // Assume child is returned with a ref (typical GLib transfer full).
    // If it's transfer-none in this build, unrefing would be wrong; to be safe:
    // - We immediately wrap it in a unique_ptr and then (if returning) ref it.
    PopplerStructureElement *child = poppler_structure_element_get_child(root, i);
    if (!child) {
      continue;
    }
    gobj_unique_ptr<PopplerStructureElement> child_holder(child);

    PopplerStructureElement *found = FindFirstElementByKind(child, kind);
    if (found) {
      return found;
    }
  }
  return nullptr;
}

static PopplerStructureElement *FindFirstElementNotKind(PopplerStructureElement *root,
                                                        PopplerStructureElementKind not_kind) {
  if (!root) {
    return nullptr;
  }

  if (poppler_structure_element_get_kind(root) != not_kind) {
    return static_cast<PopplerStructureElement *>(g_object_ref(root));
  }

  const gint n = poppler_structure_element_get_n_children(root);
  for (gint i = 0; i < n; ++i) {
    PopplerStructureElement *child = poppler_structure_element_get_child(root, i);
    if (!child) {
      continue;
    }
    gobj_unique_ptr<PopplerStructureElement> child_holder(child);

    PopplerStructureElement *found = FindFirstElementNotKind(child, not_kind);
    if (found) {
      return found;
    }
  }
  return nullptr;
}

static bool IsValidFormRole(PopplerStructureFormRole role) {
  switch (role) {
    case POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED:
    case POPPLER_STRUCTURE_FORM_ROLE_RADIO_BUTTON:
    case POPPLER_STRUCTURE_FORM_ROLE_PUSH_BUTTON:
    case POPPLER_STRUCTURE_FORM_ROLE_TEXT_VALUE:
    case POPPLER_STRUCTURE_FORM_ROLE_CHECKBOX:
      return true;
    default:
      return false;
  }
}

class PopplerStructureElementGetFormRoleTest_2588 : public ::testing::Test {
 protected:
  void SetUp() override {
    doc_ = LoadAnyTaggedPdfOrSkip();
    if (!doc_) {
      return;
    }

    PopplerStructureElement *root = poppler_document_get_structure_tree(doc_.get());
    if (!root) {
      GTEST_SKIP() << "Document has no structure tree; cannot obtain structure elements.";
      return;
    }
    root_.reset(root);
  }

  gobj_unique_ptr<PopplerDocument> doc_;
  gobj_unique_ptr<PopplerStructureElement> root_;
};

TEST_F(PopplerStructureElementGetFormRoleTest_2588, NonFormElementReturnsUndefined_2588) {
  ASSERT_TRUE(root_.get());

  gobj_unique_ptr<PopplerStructureElement> non_form(
      FindFirstElementNotKind(root_.get(), POPPLER_STRUCTURE_ELEMENT_FORM));
  if (!non_form) {
    GTEST_SKIP() << "Could not find any non-FORM structure element in the tree.";
  }

  // Error/exceptional case observable via return value: g_return_val_if_fail(...)
  // should return the default enum value. The enum defines UNDEFINED = 0, and
  // the implementation uses EnumNameValue<PopplerStructureFormRole>::values[0].value.
  const PopplerStructureFormRole role = poppler_structure_element_get_form_role(non_form.get());
  EXPECT_EQ(role, POPPLER_STRUCTURE_FORM_ROLE_UNDEFINED);
}

TEST_F(PopplerStructureElementGetFormRoleTest_2588, FormElementRoleIsWithinDeclaredEnum_2588) {
  ASSERT_TRUE(root_.get());

  gobj_unique_ptr<PopplerStructureElement> form(
      FindFirstElementByKind(root_.get(), POPPLER_STRUCTURE_ELEMENT_FORM));
  if (!form) {
    GTEST_SKIP() << "Could not find any FORM structure element in the tree.";
  }

  const PopplerStructureFormRole role = poppler_structure_element_get_form_role(form.get());
  EXPECT_TRUE(IsValidFormRole(role));
}

TEST_F(PopplerStructureElementGetFormRoleTest_2588, FormElementRoleIsStableAcrossCalls_2588) {
  ASSERT_TRUE(root_.get());

  gobj_unique_ptr<PopplerStructureElement> form(
      FindFirstElementByKind(root_.get(), POPPLER_STRUCTURE_ELEMENT_FORM));
  if (!form) {
    GTEST_SKIP() << "Could not find any FORM structure element in the tree.";
  }

  const PopplerStructureFormRole first = poppler_structure_element_get_form_role(form.get());
  const PopplerStructureFormRole second = poppler_structure_element_get_form_role(form.get());
  EXPECT_EQ(first, second);
  EXPECT_TRUE(IsValidFormRole(first));
}

}  // namespace