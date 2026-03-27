// poppler-form-field-test-2306.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <cstring>

// Include the implementation file so we can directly exercise the static
// poppler_form_field_class_init() and compare against poppler_form_field_finalize().
#include "poppler-form-field.cc"

namespace {

class PopplerFormFieldClassInitTest_2306 : public ::testing::Test {
protected:
  // Create storage that *starts* with a real GObjectClass so that
  // G_OBJECT_CLASS(klass) inside poppler_form_field_class_init() is safe.
  struct FakeKlass {
    GObjectClass parent;
  };

  static void DummyFinalize(GObject* /*object*/) {}

  static FakeKlass MakeZeroedFakeKlass() {
    FakeKlass k;
    std::memset(&k, 0, sizeof(k));
    return k;
  }
};

TEST_F(PopplerFormFieldClassInitTest_2306, SetsFinalizePointerToPopplerFinalize_2306) {
  FakeKlass fk = MakeZeroedFakeKlass();
  ASSERT_EQ(fk.parent.finalize, nullptr);

  poppler_form_field_class_init(reinterpret_cast<PopplerFormFieldClass*>(&fk));

  EXPECT_EQ(fk.parent.finalize, poppler_form_field_finalize);
}

TEST_F(PopplerFormFieldClassInitTest_2306, OverwritesExistingFinalizePointer_2306) {
  FakeKlass fk = MakeZeroedFakeKlass();
  fk.parent.finalize = &PopplerFormFieldClassInitTest_2306::DummyFinalize;
  ASSERT_NE(fk.parent.finalize, poppler_form_field_finalize);

  poppler_form_field_class_init(reinterpret_cast<PopplerFormFieldClass*>(&fk));

  EXPECT_EQ(fk.parent.finalize, poppler_form_field_finalize);
}

TEST_F(PopplerFormFieldClassInitTest_2306, NullKlassCausesDeathIfSupported_2306) {
  // The function dereferences klass via G_OBJECT_CLASS(klass), so nullptr is an error case.
  EXPECT_DEATH_IF_SUPPORTED(poppler_form_field_class_init(nullptr), "");
}

}  // namespace