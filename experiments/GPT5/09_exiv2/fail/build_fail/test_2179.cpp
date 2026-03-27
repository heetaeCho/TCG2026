// File: test_xmpdatum_impl_2179.cpp
// TEST_ID: 2179
//
// Unit tests for: Exiv2::Xmpdatum::Impl
// Interface under test (from ./TestProjects/exiv2/src/xmp.cpp):
//   Impl(const XmpKey& key, const Value* pValue) : key_(key.clone()) { if (pValue) value_ = pValue->clone(); }
//
// Constraints:
// - Treat implementation as a black box.
// - Test only observable behavior via the provided interface (public members here).
// - No reliance on private/internal state.

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Exiv2 headers (paths may vary in your project layout)
#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

// NOTE: The declaration of Exiv2::Xmpdatum::Impl must be visible to compile these tests.
// In many Exiv2 layouts, this is available via an XMP header; if not, include the correct header
// that declares Exiv2::Xmpdatum and its nested Impl.
// Example candidates (adjust as needed):
//   #include "exiv2/xmp.hpp"
//   #include "exiv2/xmp_exiv2.hpp"
//
// If your build exposes Impl only in xmp.cpp, you’ll need to expose the declaration to tests
// (e.g., via an internal header) rather than including the .cpp here.
#include "exiv2/xmp.hpp"  // <-- adjust if needed

namespace {

// A minimal concrete Value subclass so we can verify cloning behavior without relying on
// Exiv2's concrete Value types (we do NOT infer any Exiv2 internal logic).
class TestValue_2179 final : public Exiv2::Value {
 public:
  explicit TestValue_2179(int id = 0)
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), id_(id) {}

  void setId(int id) { id_ = id; }
  int id() const { return id_; }

 private:
  // Value::clone() calls the virtual clone_() internally. Overriding is allowed even if base is private.
  const Exiv2::Value* clone_() override { return new TestValue_2179(*this); }

  int id_;
};

class XmpdatumImplTest_2179 : public ::testing::Test {
 protected:
  static Exiv2::XmpKey MakeKey(const std::string& s) { return Exiv2::XmpKey(s); }
};

}  // namespace

TEST_F(XmpdatumImplTest_2179, ConstructorClonesKeyWhenValueNull_2179) {
  const Exiv2::XmpKey key = MakeKey("Xmp.dc.title");

  Exiv2::Xmpdatum::Impl impl(key, nullptr);

  ASSERT_NE(impl.key_.get(), nullptr);
  EXPECT_EQ(impl.key_->key(), key.key());
  EXPECT_EQ(impl.value_.get(), nullptr);
}

TEST_F(XmpdatumImplTest_2179, ConstructorClonesKeyIndependentlyFromOriginal_2179) {
  Exiv2::XmpKey key = MakeKey("Xmp.dc.title");
  Exiv2::Xmpdatum::Impl impl(key, nullptr);

  // Mutate the original key object (via assignment) and verify Impl's cloned key remains unchanged.
  key = MakeKey("Xmp.dc.description");

  ASSERT_NE(impl.key_.get(), nullptr);
  EXPECT_EQ(impl.key_->key(), std::string("Xmp.dc.title"));
}

TEST_F(XmpdatumImplTest_2179, ConstructorClonesValueWhenNonNull_2179) {
  const Exiv2::XmpKey key = MakeKey("Xmp.dc.title");
  TestValue_2179 original(7);

  Exiv2::Xmpdatum::Impl impl(key, &original);

  ASSERT_NE(impl.key_.get(), nullptr);
  EXPECT_EQ(impl.key_->key(), key.key());

  ASSERT_NE(impl.value_.get(), nullptr);
  EXPECT_NE(impl.value_.get(), static_cast<const Exiv2::Value*>(&original));

  // Verify it is a clone of our dynamic type (observable via RTTI in the test).
  auto* cloned = dynamic_cast<TestValue_2179*>(impl.value_.get());
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->id(), 7);
}

TEST_F(XmpdatumImplTest_2179, ConstructorClonedValueIsIndependentFromOriginal_2179) {
  const Exiv2::XmpKey key = MakeKey("Xmp.dc.title");
  TestValue_2179 original(1);

  Exiv2::Xmpdatum::Impl impl(key, &original);
  ASSERT_NE(impl.value_.get(), nullptr);

  auto* cloned = dynamic_cast<TestValue_2179*>(impl.value_.get());
  ASSERT_NE(cloned, nullptr);

  // Change original after construction; clone should not change if cloning occurred.
  original.setId(99);
  EXPECT_EQ(cloned->id(), 1);
}

TEST_F(XmpdatumImplTest_2179, CopyConstructorCopiesKeyAndValue_2179) {
  const Exiv2::XmpKey key = MakeKey("Xmp.dc.title");
  TestValue_2179 original(42);

  Exiv2::Xmpdatum::Impl a(key, &original);
  Exiv2::Xmpdatum::Impl b(a);  // Copy ctor

  ASSERT_NE(a.key_.get(), nullptr);
  ASSERT_NE(b.key_.get(), nullptr);
  EXPECT_EQ(b.key_->key(), a.key_->key());
  EXPECT_NE(b.key_.get(), a.key_.get());  // should be an independent copy/clone

  ASSERT_NE(a.value_.get(), nullptr);
  ASSERT_NE(b.value_.get(), nullptr);
  EXPECT_NE(b.value_.get(), a.value_.get());  // should be an independent copy/clone

  auto* aV = dynamic_cast<TestValue_2179*>(a.value_.get());
  auto* bV = dynamic_cast<TestValue_2179*>(b.value_.get());
  ASSERT_NE(aV, nullptr);
  ASSERT_NE(bV, nullptr);
  EXPECT_EQ(bV->id(), aV->id());
}

TEST_F(XmpdatumImplTest_2179, CopyAssignmentCopiesKeyAndValue_2179) {
  const Exiv2::XmpKey keyA = MakeKey("Xmp.dc.title");
  const Exiv2::XmpKey keyB = MakeKey("Xmp.dc.description");

  TestValue_2179 vA(10);
  TestValue_2179 vB(20);

  Exiv2::Xmpdatum::Impl a(keyA, &vA);
  Exiv2::Xmpdatum::Impl b(keyB, &vB);

  // Copy-assign b from a
  b = a;

  ASSERT_NE(b.key_.get(), nullptr);
  EXPECT_EQ(b.key_->key(), a.key_->key());
  EXPECT_NE(b.key_.get(), a.key_.get());

  ASSERT_NE(b.value_.get(), nullptr);
  EXPECT_NE(b.value_.get(), a.value_.get());

  auto* bV = dynamic_cast<TestValue_2179*>(b.value_.get());
  auto* aV = dynamic_cast<TestValue_2179*>(a.value_.get());
  ASSERT_NE(aV, nullptr);
  ASSERT_NE(bV, nullptr);
  EXPECT_EQ(bV->id(), aV->id());
}

TEST_F(XmpdatumImplTest_2179, SelfAssignmentDoesNotInvalidatePointers_2179) {
  const Exiv2::XmpKey key = MakeKey("Xmp.dc.title");
  TestValue_2179 v(123);

  Exiv2::Xmpdatum::Impl a(key, &v);

  auto* keyPtrBefore = a.key_.get();
  auto* valuePtrBefore = a.value_.get();

  a = a;  // self-assign

  // Observable requirement: object remains valid and usable.
  ASSERT_NE(a.key_.get(), nullptr);
  EXPECT_EQ(a.key_->key(), key.key());

  ASSERT_NE(a.value_.get(), nullptr);
  // We don't assume whether it preserves the same pointers or re-clones;
  // we only assert it's still valid. But we can allow either behavior:
  (void)keyPtrBefore;
  (void)valuePtrBefore;

  auto* aV = dynamic_cast<TestValue_2179*>(a.value_.get());
  ASSERT_NE(aV, nullptr);
  EXPECT_EQ(aV->id(), 123);
}

TEST_F(XmpdatumImplTest_2179, Boundary_EmptyKeyStringStillClones_2179) {
  const Exiv2::XmpKey emptyKey = MakeKey("");

  Exiv2::Xmpdatum::Impl impl(emptyKey, nullptr);

  ASSERT_NE(impl.key_.get(), nullptr);
  EXPECT_EQ(impl.key_->key(), emptyKey.key());
  EXPECT_EQ(impl.value_.get(), nullptr);
}

TEST_F(XmpdatumImplTest_2179, Boundary_LongKeyStringStillClones_2179) {
  std::string longKey(4096, 'a');
  const Exiv2::XmpKey key = MakeKey(longKey);

  Exiv2::Xmpdatum::Impl impl(key, nullptr);

  ASSERT_NE(impl.key_.get(), nullptr);
  EXPECT_EQ(impl.key_->key(), key.key());
  EXPECT_EQ(impl.value_.get(), nullptr);
}