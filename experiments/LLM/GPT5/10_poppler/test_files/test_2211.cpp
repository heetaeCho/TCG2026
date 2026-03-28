// File: poppler-document-class-init-test_2211.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

namespace {

class PopplerDocumentClassInitTest_2211 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure the PopplerDocument GType is registered and class_init has run.
    doc_class_ = static_cast<GObjectClass*>(g_type_class_ref(POPPLER_TYPE_DOCUMENT));
    ASSERT_NE(doc_class_, nullptr);
  }

  void TearDown() override {
    if (doc_class_) {
      g_type_class_unref(doc_class_);
      doc_class_ = nullptr;
    }
  }

  GParamSpec* FindProp(const char* name) {
    EXPECT_NE(doc_class_, nullptr);
    return g_object_class_find_property(doc_class_, name);
  }

  static void ExpectHasFlags(GParamSpec* pspec, GParamFlags expected_bits_set) {
    ASSERT_NE(pspec, nullptr);
    EXPECT_EQ((pspec->flags & expected_bits_set), expected_bits_set);
  }

  static void ExpectLacksFlags(GParamSpec* pspec, GParamFlags expected_bits_clear) {
    ASSERT_NE(pspec, nullptr);
    EXPECT_EQ((pspec->flags & expected_bits_clear), static_cast<GParamFlags>(0));
  }

  GObjectClass* doc_class_ = nullptr;
};

TEST_F(PopplerDocumentClassInitTest_2211, HooksAreInstalledOnGObjectClass_2211) {
  // Observable via public GObjectClass fields.
  auto* gobj_class = doc_class_;
  ASSERT_NE(gobj_class, nullptr);

  EXPECT_NE(gobj_class->finalize, nullptr);
  EXPECT_NE(gobj_class->get_property, nullptr);
  EXPECT_NE(gobj_class->set_property, nullptr);
}

TEST_F(PopplerDocumentClassInitTest_2211, StringPropertiesExistWithExpectedFlags_2211) {
  struct {
    const char* name;
    bool readable;
    bool writable;
  } kProps[] = {
      {"title", true, true},
      {"format", true, false},
      {"author", true, true},
      {"subject", true, true},
      {"keywords", true, true},
      {"creator", true, true},
      {"producer", true, true},
      {"subtype-string", true, false},
      {"metadata", true, false},
  };

  for (const auto& p : kProps) {
    SCOPED_TRACE(p.name);
    GParamSpec* pspec = FindProp(p.name);
    ASSERT_NE(pspec, nullptr);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), G_TYPE_STRING);

    if (p.readable) ExpectHasFlags(pspec, G_PARAM_READABLE);
    else ExpectLacksFlags(pspec, G_PARAM_READABLE);

    if (p.writable) ExpectHasFlags(pspec, G_PARAM_WRITABLE);
    else ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
  }
}

TEST_F(PopplerDocumentClassInitTest_2211, FormatMajorMinorAreUintReadableWithExpectedDefaults_2211) {
  {
    GParamSpec* pspec = FindProp("format-major");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_UINT(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);

    auto* uspec = G_PARAM_SPEC_UINT(pspec);
    EXPECT_EQ(uspec->minimum, 0u);
    EXPECT_EQ(uspec->maximum, G_MAXUINT);
    EXPECT_EQ(uspec->default_value, 1u);
  }

  {
    GParamSpec* pspec = FindProp("format-minor");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_UINT(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);

    auto* uspec = G_PARAM_SPEC_UINT(pspec);
    EXPECT_EQ(uspec->minimum, 0u);
    EXPECT_EQ(uspec->maximum, G_MAXUINT);
    EXPECT_EQ(uspec->default_value, 0u);
  }
}

TEST_F(PopplerDocumentClassInitTest_2211, DateIntPropertiesAreDeprecatedReadWriteWithExpectedRange_2211) {
  struct {
    const char* name;
  } kIntDeprecated[] = {{"creation-date"}, {"mod-date"}};

  for (const auto& p : kIntDeprecated) {
    SCOPED_TRACE(p.name);
    GParamSpec* pspec = FindProp(p.name);
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_INT(pspec));

    ExpectHasFlags(pspec, static_cast<GParamFlags>(G_PARAM_READWRITE | G_PARAM_DEPRECATED));

    auto* ispec = G_PARAM_SPEC_INT(pspec);
    EXPECT_EQ(ispec->minimum, -1);
    EXPECT_EQ(ispec->maximum, G_MAXINT);
    EXPECT_EQ(ispec->default_value, -1);
  }
}

TEST_F(PopplerDocumentClassInitTest_2211, DateTimeBoxedPropertiesAreReadWriteGDateTime_2211) {
  struct {
    const char* name;
  } kBoxed[] = {{"creation-datetime"}, {"mod-datetime"}};

  for (const auto& p : kBoxed) {
    SCOPED_TRACE(p.name);
    GParamSpec* pspec = FindProp(p.name);
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_BOXED(pspec));

    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), G_TYPE_DATE_TIME);
    ExpectHasFlags(pspec, G_PARAM_READWRITE);
  }
}

TEST_F(PopplerDocumentClassInitTest_2211, LinearizedIsReadableBooleanWithDefaultFalse_2211) {
  GParamSpec* pspec = FindProp("linearized");
  ASSERT_NE(pspec, nullptr);
  ASSERT_TRUE(G_IS_PARAM_SPEC_BOOLEAN(pspec));

  ExpectHasFlags(pspec, G_PARAM_READABLE);
  ExpectLacksFlags(pspec, G_PARAM_WRITABLE);

  auto* bspec = G_PARAM_SPEC_BOOLEAN(pspec);
  EXPECT_FALSE(bspec->default_value);
}

TEST_F(PopplerDocumentClassInitTest_2211, EnumAndFlagsPropertiesAreReadableWithExpectedTypesAndDefaults_2211) {
  // page-layout
  {
    GParamSpec* pspec = FindProp("page-layout");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PAGE_LAYOUT);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PAGE_LAYOUT_UNSET);
  }

  // page-mode
  {
    GParamSpec* pspec = FindProp("page-mode");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PAGE_MODE);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PAGE_MODE_UNSET);
  }

  // viewer-preferences (flags)
  {
    GParamSpec* pspec = FindProp("viewer-preferences");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_FLAGS(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_VIEWER_PREFERENCES);

    auto* fspec = G_PARAM_SPEC_FLAGS(pspec);
    EXPECT_EQ(static_cast<guint>(fspec->default_value),
              static_cast<guint>(POPPLER_VIEWER_PREFERENCES_UNSET));
  }

  // print-scaling
  {
    GParamSpec* pspec = FindProp("print-scaling");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PRINT_SCALING);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PRINT_SCALING_APP_DEFAULT);
  }

  // print-duplex
  {
    GParamSpec* pspec = FindProp("print-duplex");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PRINT_DUPLEX);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PRINT_DUPLEX_NONE);
  }

  // subtype
  {
    GParamSpec* pspec = FindProp("subtype");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PDF_SUBTYPE);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PDF_SUBTYPE_UNSET);
  }

  // subtype-part
  {
    GParamSpec* pspec = FindProp("subtype-part");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PDF_PART);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PDF_SUBTYPE_PART_UNSET);
  }

  // subtype-conformance
  {
    GParamSpec* pspec = FindProp("subtype-conformance");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_ENUM(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PDF_CONFORMANCE);

    auto* espec = G_PARAM_SPEC_ENUM(pspec);
    EXPECT_EQ(espec->default_value, POPPLER_PDF_SUBTYPE_CONF_UNSET);
  }

  // permissions (flags)
  {
    GParamSpec* pspec = FindProp("permissions");
    ASSERT_NE(pspec, nullptr);
    ASSERT_TRUE(G_IS_PARAM_SPEC_FLAGS(pspec));
    ExpectHasFlags(pspec, G_PARAM_READABLE);
    ExpectLacksFlags(pspec, G_PARAM_WRITABLE);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), POPPLER_TYPE_PERMISSIONS);

    auto* fspec = G_PARAM_SPEC_FLAGS(pspec);
    EXPECT_EQ(static_cast<guint>(fspec->default_value),
              static_cast<guint>(POPPLER_PERMISSIONS_FULL));
  }
}

TEST_F(PopplerDocumentClassInitTest_2211, PrintNCopiesIsReadableIntWithMinOneDefaultOne_2211) {
  GParamSpec* pspec = FindProp("print-n-copies");
  ASSERT_NE(pspec, nullptr);
  ASSERT_TRUE(G_IS_PARAM_SPEC_INT(pspec));

  ExpectHasFlags(pspec, G_PARAM_READABLE);
  ExpectLacksFlags(pspec, G_PARAM_WRITABLE);

  auto* ispec = G_PARAM_SPEC_INT(pspec);
  EXPECT_EQ(ispec->minimum, 1);
  EXPECT_EQ(ispec->maximum, G_MAXINT);
  EXPECT_EQ(ispec->default_value, 1);
}

}  // namespace