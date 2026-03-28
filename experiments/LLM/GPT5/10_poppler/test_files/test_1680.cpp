// AttributeTest_1680.cpp
#include <gtest/gtest.h>

#include "StructElement.h" // poppler/StructElement.h

#include <limits>
#include <type_traits>
#include <utility>

// Small helper to call Attribute::setFormattedValue regardless of whether the
// signature is (const char*) or (const GooString*).
namespace {
template <typename T>
auto HasSetFormattedValueCharPtr(int)
    -> decltype(std::declval<T &>().setFormattedValue(static_cast<const char *>(nullptr)), std::true_type{});
template <typename T>
std::false_type HasSetFormattedValueCharPtr(...);

template <typename T>
constexpr bool kHasSetFormattedValueCharPtr = decltype(HasSetFormattedValueCharPtr<T>(0))::value;

static void SetFormattedValueCompat(Attribute &attr, const char *s)
{
    if constexpr (kHasSetFormattedValueCharPtr<Attribute>) {
        attr.setFormattedValue(s);
    } else {
        // Signature variant: setFormattedValue(const GooString*)
        if (s) {
            GooString gs(s);
            attr.setFormattedValue(&gs);
        } else {
            attr.setFormattedValue(static_cast<const GooString *>(nullptr));
        }
    }
}

static Attribute MakeStandardAttr(Attribute::Type type)
{
    // Prefer library-provided default value if available; otherwise use a local null Object.
    if (Object *def = Attribute::getDefaultValue(type)) {
        return Attribute(type, def);
    }
    Object local;
    local.initNull();
    return Attribute(type, &local);
}

static Attribute MakeUnknownAttr()
{
    // Construct Unknown directly.
    Object local;
    local.initNull();
    return Attribute(Attribute::Unknown, &local);
}
} // namespace

TEST(AttributeTest_1680, IsOkReturnsFalseForUnknownType_1680)
{
    Attribute attr = MakeUnknownAttr();
    EXPECT_EQ(attr.getType(), Attribute::Unknown);
    EXPECT_FALSE(attr.isOk());
}

TEST(AttributeTest_1680, IsOkReturnsTrueForStandardType_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);
    EXPECT_EQ(attr.getType(), Attribute::Placement);
    EXPECT_TRUE(attr.isOk());
}

TEST(AttributeTest_1680, UserPropertyConstructionIsOkAndHasTypeUserProperty_1680)
{
    Object local;
    local.initNull();

    Attribute attr(GooString("CustomUserProp"), &local);

    EXPECT_TRUE(attr.isOk());
    EXPECT_EQ(attr.getType(), Attribute::UserProperty);
    EXPECT_NE(attr.getName(), nullptr);
}

TEST(AttributeTest_1680, RevisionRoundTripBoundaryValues_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);

    attr.setRevision(0u);
    EXPECT_EQ(attr.getRevision(), 0u);

    const unsigned int max_u = (std::numeric_limits<unsigned int>::max)();
    attr.setRevision(max_u);
    EXPECT_EQ(attr.getRevision(), max_u);
}

TEST(AttributeTest_1680, HiddenFlagRoundTrip_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);

    attr.setHidden(true);
    EXPECT_TRUE(attr.isHidden());

    attr.setHidden(false);
    EXPECT_FALSE(attr.isHidden());
}

TEST(AttributeTest_1680, FormattedValueNullAndNonNull_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);

    // Do not assume initial state; just ensure calls are safe and observable.
    const char *initial = attr.getFormattedValue();
    (void)initial;

    SetFormattedValueCompat(attr, nullptr);
    EXPECT_EQ(attr.getFormattedValue(), nullptr);

    SetFormattedValueCompat(attr, "formatted-text");
    ASSERT_NE(attr.getFormattedValue(), nullptr);
    EXPECT_STREQ(attr.getFormattedValue(), "formatted-text");

    // Boundary-ish: empty string
    SetFormattedValueCompat(attr, "");
    ASSERT_NE(attr.getFormattedValue(), nullptr);
    EXPECT_STREQ(attr.getFormattedValue(), "");
}

TEST(AttributeTest_1680, GetValueReturnsStableNonNullPointer_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);

    const Object *v1 = attr.getValue();
    const Object *v2 = attr.getValue();

    EXPECT_NE(v1, nullptr);
    EXPECT_EQ(v1, v2);
}

TEST(AttributeTest_1680, TypeAndOwnerNameAreNonNullForOkAttribute_1680)
{
    Attribute attr = MakeStandardAttr(Attribute::Placement);
    ASSERT_TRUE(attr.isOk());

    EXPECT_NE(attr.getTypeName(), nullptr);
    EXPECT_NE(attr.getOwnerName(), nullptr);
}