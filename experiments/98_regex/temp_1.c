PATTERNS = {
    # 선언에서 타입 지정자 누락
    // "err_missing_type_specifier": (r"a type specifier is required for all declarations", "missing type specifier in declaration"),
    # 추상 클래스 타입 객체 할당 시도
    // "err_allocation_of_abstract_type": (r"allocating an object of abstract class type '.+?'(?:\s*\(aka '.+?'\))?", "allocating object of abstract class type"),
    # 불완전한 타입 객체 할당 시도
    // "err_new_incomplete_or_sizeless_type": (r"allocation of incomplete type '.+?'", "allocation of incomplete type"),
    # 함수형 캐스트에서 모호한 변환
    // "err_ovl_ambiguous_conversion_in_cast": (r"ambiguous conversion for functional-style cast from '.+?' to '.+?'", "ambiguous conversion for functional-style cast"),
    # 속성 목록이 올 수 없는 위치
    // "err_attributes_not_allowed": (r"an attribute list cannot appear here", "attribute list in invalid position"),
    # 불완전한 타입 포인터에 대한 산술 연산
    // "err_typecheck_arithmetic_incomplete_or_sizeless_type": (r"arithmetic on a pointer to an incomplete type '.+?'", "arithmetic on pointer to incomplete type"),
    # 기본 멤버 초기화자에서 배열 크기 추론 불가
    // "err_incomplete_array_member_init": (r"array bound cannot be deduced from a default member initializer", "array bound cannot be deduced from default member initializer"),
    # 배열 타입 대입 불가
    // "err_typecheck_array_not_modifiable_lvalue": (r"array type '.+?'(?:\s*\(aka '.+?'\))? is not assignable", "array type is not assignable"),
    # const 한정자 무시하고 대입
    // "err_typecheck_convert_discards_qualifiers": (r"assigning to '.+?' from '.+?' discards qualifiers", "assigning discards qualifiers"),
    # 호환되지 않는 타입 대입
    // "err_typecheck_convert_incompatible": (r"assigning to '.+?'(?:\s*\(aka '.+?'\))? from incompatible type '.+?'", "assigning from incompatible type"),
    # 삭제된 함수 사용 시도
    // "err_deleted_function_use": (r"attempt to use a deleted function", "attempt to use deleted function"),
    # final로 표시된 클래스 상속 시도
    // "err_class_marked_final_used_as_base": (r"base '.+?' is marked 'final'", "base class marked final"),
    # 기본 클래스의 생성자가 private
    // "err_access_base_ctor": (r"base class '.+?' has private (?:default )?constructor", "base class has private constructor"),
    # 기본 클래스의 소멸자가 private
    // "err_access_dtor_base": (r"base class '.+?' has private destructor", "base class has private destructor"),
    # 기본 클래스가 불완전한 타입
    // "err_incomplete_base_class": (r"base class has incomplete type", "base class has incomplete type"),
    # 멤버 참조의 베이스가 함수
    // "err_member_reference_needs_call": (r"base of member reference is a function; perhaps you meant to call it with no arguments\?", "base of member reference is function"),
    # 베이스 지정자가 클래스를 가리키지 않음
    // "err_base_must_be_class": (r"base specifier must name a class", "base specifier must name a class"),
    # 참조 바인딩 시 한정자 제거
    // "err_reference_bind_drops_quals": (r"binding reference of type '.+?' to value of type '.+?' drops '(?:const|volatile)' qualifier", "binding reference drops qualifier"),
    # 배열 선언 시 괄호 위치 오류
    // "err_brackets_go_after_unqualified_id": (r"brackets are not allowed here; to declare an array, place the brackets after the name", "brackets not allowed here"),
    # 삭제된 생성자 호출
    // "err_ovl_deleted_init": (r"call to deleted constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to deleted constructor"),
    # 암묵적으로 삭제된 생성자 호출
    // "err_ovl_deleted_special_init": (r"call to implicitly-deleted (?:copy|default) constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to implicitly-deleted constructor"),
    # 삭제된 함수 호출
    // "err_ovl_deleted_call": (r"call to deleted function '.+?'", "call to deleted function"),
    # 모호한 함수/생성자/멤버 함수 호출
    // "err_ovl_ambiguous_init": (r"call to (?:constructor of|member function|'.+?') '.+?' is ambiguous|call to '.+?' is ambiguous", "ambiguous call"),
    # 객체 인자 없이 비정적 멤버 함수 호출
    // "err_member_call_without_object": (r"call to non-static member function without an object argument", "call to non-static member function without object argument"),
    # 함수가 아닌 타입 호출 시도
    // "err_typecheck_call_not_function": (r"called object type '.+?'(?:\s*\(aka '.+?'\))? is not a function or function pointer", "called object type is not a function or function pointer"),
    # 불완전한 반환 타입으로 함수 호출
    // "err_call_function_incomplete_return": (r"calling '.+?'(?:\s*\(aka '.+?'\))? with incomplete return type '.+?'(?:\s*\(aka '.+?'\))?", "calling with incomplete return type"),
    # private/protected 생성자/소멸자 호출
    // "err_access_ctor": (r"calling a (?:private|protected) (?:constructor|destructor) of class '.+?'", "calling private or protected constructor or destructor"),
    # const 한정 타입에 대입 불가
    // "err_typecheck_assign_const": (r"cannot assign to (?:non-static data member|variable) '.+?' with const-qualified type '.+?'(?:\s*\(aka '.+?'\))?", "cannot assign to const-qualified type"),
    # 변환 연산자 없이 타입 변환 불가
    // "err_ovl_no_conversion_in_cast": (r"cannot convert '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))? without a conversion operator", "cannot convert without conversion operator"),
    # 네임스페이스 범위 밖에서 정의/재선언 불가
    // "err_invalid_declarator_scope": (r"cannot define or redeclare '.+?' here because namespace '.*?' does not enclose namespace '.+?'", "cannot define or redeclare outside enclosing namespace"),
    # unique_ptr 표현식 delete 불가
    // "err_delete_operand": (r"cannot delete expression of type '.+?'", "cannot delete expression of type"),
    # void에 대한 참조 생성 불가
    // "err_reference_to_void": (r"cannot form a reference to 'void'", "cannot form reference to void"),
    # 추론된 클래스 템플릿 특수화 타입에 대한 포인터/참조 생성 불가
    // "err_deduced_class_template_compound_type": (r"cannot form (?:pointer|reference) to deduced class template specialization type", "cannot form pointer or reference to deduced class template specialization type"),
    # 타입 불일치로 초기화 불가
    // "err_init_conversion_failed": (r"cannot initialize (?:a parameter|a variable|a member subobject|an array element|object parameter|return object) of type '.+?'(?:\s*\(aka '.+?'\))? with (?:an lvalue|an rvalue|an expression) of type '.+?'(?:\s*\(aka '.+?'\))?", "cannot initialize with incompatible type"),
    # ref-qualifier 없는 멤버 함수와 ref-qualifier 있는 멤버 함수 오버로드 불가
    // "err_ref_qualifier_overload": (r"cannot overload a member function without a ref-qualifier with a member function with ref-qualifier '.+?'", "cannot overload member function with ref-qualifier mismatch"),
    # 종속 템플릿 특수화 불가
    // "err_not_class_template_specialization": (r"cannot specialize a dependent template", "cannot specialize dependent template"),
    # rvalue 주소 참조 불가
    // "err_typecheck_invalid_lvalue_addrof": (r"cannot take the address of an rvalue of type '.+?'", "cannot take address of rvalue"),
    # 예외 비활성화 상태에서 try/throw 사용 불가
    "err_exceptions_disabled": (r"cannot use '(?:try|throw)' with exceptions disabled", "cannot use try or throw with exceptions disabled"),
    # 불완전한 타입을 range로 사용 불가
    // "err_for_range_incomplete_type": (r"cannot use incomplete type '.+?' as a range", "cannot use incomplete type as range"),
    # 식별자에 허용되지 않는 문자
    // "err_character_not_allowed_identifier": (r"character <.+?> not allowed in an identifier", "character not allowed in identifier"),
    # 문자 리터럴 타입에 비해 너무 큰 문자
    // "err_character_too_large": (r"character too large for enclosing character literal type", "character too large for character literal type"),
    # 클래스 멤버 재선언 불가
    // "err_member_redeclared": (r"class member cannot be redeclared", "class member cannot be redeclared"),
    # 클래스 템플릿 부분 특수화가 올바른 네임스페이스 안에 없음
    // "err_template_spec_redecl_out_of_scope": (r"class template partial specialization of '.+?' not in a namespace enclosing '.+?'", "class template partial specialization not in enclosing namespace"),
    # 상수 표현식이 타입으로 좁혀질 수 없음
    // "ext_init_list_constant_narrowing": (r"constant expression evaluates to .+? which cannot be narrowed to type '.+?'(?:\s*\(aka '.+?'\))?", "constant expression cannot be narrowed"),
    # constexpr 생성자의 매개변수 타입이 리터럴 타입이 아님
    // "err_constexpr_non_literal_param": (r"constexpr constructor's .+? parameter type '.+?'(?:\s*\(aka '.+?'\))? is not a literal type", "constexpr constructor parameter is not literal type"),
    # constexpr if 조건이 상수 표현식이 아님
    // "err_constexpr_if_condition_expression_is_not_constant": (r"constexpr if condition is not a constant expression", "constexpr if condition is not constant expression"),
    # constexpr 변수가 상수 표현식으로 초기화되지 않음
    // "err_constexpr_var_requires_const_init": (r"constexpr variable '.+?' must be initialized by a constant expression", "constexpr variable must be initialized by constant expression"),
    # constexpr 변수가 비리터럴 타입을 가질 수 없음
    // "err_constexpr_var_non_literal": (r"constexpr variable cannot have non-literal type '.+?'", "constexpr variable cannot have non-literal type"),
    # 생성자가 void 표현식을 반환하면 안됨
    // "err_ctor_dtor_returns_void": (r"constructor '.+?' must not return void expression", "constructor must not return void expression"),
    # 기본 생성자 없는 기본 클래스/멤버 명시적 초기화 필요
    // "err_missing_default_ctor#1": (r"constructor for '.+?' must explicitly initialize the (?:base class|member) '.+?' which does not have a default constructor", "constructor must explicitly initialize base class or member without default constructor"),
    # 초기화 리스트 원소 타입 추론 충돌
    // "err_auto_inconsistent_deduction": (r"deduced conflicting types \('.+?' vs '.+?'(?:\s*\(aka '.+?'\))?\) for initializer list element type", "deduced conflicting types for initializer list element type"),
    # user-provided 기본 생성자 없는 const 타입 기본 초기화
    // "err_default_init_const": (r"default initialization of an object of const type '.+?'(?:\s*\(aka '.+?'\))? without a user-provided default constructor", "default initialization of const type without user-provided default constructor"),
    # 멤버 함수 밖에서 기본 멤버 초기화자 필요
    // "err_default_member_initializer_not_yet_parsed": (r"default member initializer for '.+?' needed within definition of enclosing class '.+?' outside of member functions", "default member initializer needed outside of member functions"),
    # 타입 정의가 동일한 이름의 타입 별칭과 충돌
    // "err_tag_definition_of_typedef": (r"definition of type '.+?' conflicts with type alias of the same name", "definition conflicts with type alias"),
    # 삭제된 함수가 비삭제 함수를 오버라이드할 수 없음
    // "err_deleted_override": (r"deleted function '.+?' cannot override a non-deleted function", "deleted function cannot override non-deleted function"),
    # 불완전한 타입 포인터 삭제로 인한 미정의 동작
    // "warn_delete_incomplete": (r"deleting pointer to incomplete type '.+?' may cause undefined behavior", "deleting pointer to incomplete type may cause undefined behavior"),
    # 중복 멤버 선언
    // "err_duplicate_member": (r"duplicate member '.+?'", "duplicate member"),
    # 다른 기본 타입으로 열거형 재선언
    // "err_enum_redeclare_type_mismatch": (r"enumeration redeclared with different underlying type '.+?' \(was '.+?'(?:\s*\(aka '.+?'\))?\)", "enumeration redeclared with different underlying type"),
    # 오버라이딩 함수의 예외 명세가 기본 버전보다 느슨함
    // "err_override_exception_spec": (r"exception specification of overriding function is more lax than base version", "exception specification more lax than base version"),
    # 스칼라 초기화자에 초과 원소
    // "err_excess_initializers": (r"excess elements in scalar initializer", "excess elements in scalar initializer"),
    # 구문 기호/키워드 필요 (구체적인 패턴 먼저)
    // "err_expected_lparen_after_type": (r"expected '\(' for function-style cast or type construction", "expected '(' for function-style cast or type construction"),
    // "err_expected_class_name": (r"expected class name", "expected class name"),
    // "err_expected_expression": (r"expected expression", "expected expression"),
    # 65: (r"expected namespace name", "expected namespace name"),
    // "err_missing_param": (r"expected parameter declarator", "expected parameter declarator"),
    // "err_expected_statement": (r"expected statement", "expected statement"),
    // "err_expected_unqualified_id": (r"expected unqualified-id", "expected unqualified-id"),
    # 구문 기호 누락 (일반, 위의 구체적 패턴 이후에 위치)
    // "Unknown_Parse#1": (r"expected .+", "expected punctuation or keyword"),
    # 명시적으로 기본 설정된 생성자/소멸자가 암묵적으로 삭제됨
    // "warn_defaulted_comparison_deleted": (r"explicitly defaulted (?:default constructor|destructor) is implicitly deleted", "explicitly defaulted constructor or destructor is implicitly deleted"),
    # 대입 불가능한 표현식
    // "err_no_subobject_property_setting": (r"expression is not assignable", "expression is not assignable"),
    # 사용되지 않는 표현식 결과
    // "warn_unused_expr": (r"expression result unused", "expression result unused"),
    # 불필요한 닫는 중괄호
    // "err_extraneous_closing_brace": (r"extraneous closing brace \('}'\)", "extraneous closing brace"),
    # 필드가 사용될 때 초기화되지 않음
    // "warn_field_is_uninit": (r"field '.+?' is uninitialized when used here", "field is uninitialized when used"),
    # 필드가 불완전한 타입
    // "err_field_incomplete_or_sizeless": (r"field has incomplete type '.+?'", "field has incomplete type"),
    # 필드 타입의 기본 생성자/소멸자가 private
    // "err_access_field_ctor": (r"field of type '.+?' has private (?:(?:default )?constructor|destructor)", "field of type has private constructor or destructor"),
    # 필드 타입이 추상 클래스
    // "err_abstract_type_in_decl#1": (r"field type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "field type is abstract class"),
    # 포맷 문자열이 문자열 리터럴이 아님
    // "warn_format_nonliteral_noargs": (r"format string is not a string literal \(potentially insecure\)", "format string is not a string literal"),
    # 함수가 함수 타입을 반환할 수 없음
    // "err_func_returning_array_function": (r"function cannot return function type '.+?'(?:\s*\(aka '.+?'\))?", "function cannot return function type"),
    # 반환 타입만 다른 함수 오버로드 불가
    // "err_ovl_diff_return_type": (r"functions that differ only in their return type cannot be overloaded", "functions differ only in return type cannot be overloaded"),
    # 암묵적 기본 생성자가 기본 생성자 없는 멤버 명시적 초기화 필요
    // "err_missing_default_ctor#2": (r"implicit default constructor for '.+?' must explicitly initialize the member '.+?' which does not have a default constructor", "implicit default constructor must explicitly initialize member without default constructor"),
    # 정의되지 않은 템플릿의 암묵적 인스턴스화
    // "err_implicit_instantiate_member_undefined": (r"implicit instantiation of undefined template '.+?'", "implicit instantiation of undefined template"),
    # 호환되지 않는 포인터 타입 대입
    // "err_typecheck_convert_incompatible_pointer": (r"incompatible pointer types assigning to '.+?' from '.+?'", "incompatible pointer types assigning"),
    # 타입의 불완전한 정의
    // "err_typecheck_incomplete_tag": (r"incomplete definition of type '.+?'", "incomplete definition of type"),
    # 함수 정의/람다에서 불완전한 결과 타입
    // "err_func_def_incomplete_result": (r"incomplete result type '.+?'(?:\s*\(aka '.+?'\))? in (?:function definition|lambda expression)", "incomplete result type in function definition or lambda expression"),
    # 중첩 이름 지정자에 불완전한 타입
    // "err_incomplete_nested_name_spec": (r"incomplete type '.+?' named in nested name specifier", "incomplete type in nested name specifier"),
    # 포인터 피연산자가 필요한 간접 참조
    // "err_typecheck_indirection_requires_pointer": (r"indirection requires pointer operand \('.+?'(?:\s*\(aka '.+?'\))? invalid\)", "indirection requires pointer operand"),
    # 불완전한 타입 초기화
    // "err_init_incomplete_type": (r"initialization of incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "initialization of incomplete type"),
    # 선언 끝에 잘못된 '=='
    // "err_invalid_token_after_declarator_suggest_equal": (r"invalid '==' at end of declaration; did you mean '='\?", "invalid '==' at end of declaration"),
    # 불완전한 타입에 alignas/sizeof 적용 불가
    // "err_sizeof_alignof_incomplete_or_sizeless_type": (r"invalid application of '(?:alignas|sizeof)' to an incomplete type '.+?'", "invalid application of alignas or sizeof to incomplete type"),
    # 이항 표현식에 잘못된 피연산자
    // "err_typecheck_invalid_operands": (r"invalid operands to binary expression \('.+?'(?:\s*\(aka '.+?'\))? and '.+?'(?:\s*\(aka '.+?'\))?\)", "invalid operands to binary expression"),
    # 잘못된 매개변수 이름 (키워드 사용)
    // "err_keyword_as_parameter": (r"invalid parameter name: '.+?' is a keyword", "invalid parameter name is keyword"),
    # 상수에 잘못된 접미사
    // "err_invalid_suffix_constant": (r"invalid suffix '.+?' on (?:floating|integer) constant", "invalid suffix on constant"),
    # 잘못된 유니버설 문자
    // "err_ucn_escape_invalid": (r"invalid universal character", "invalid universal character"),
    # 불완전한 타입 사용
    // "err_invalid_incomplete_type_use": (r"invalid use of incomplete type '.+?'", "invalid use of incomplete type"),
    # 비정적 멤버 함수 외부에서 this 사용
    // "err_invalid_this_use": (r"invalid use of 'this' outside of a non-static member function", "invalid use of this outside non-static member function"),
    # enum 전방 선언 금지
    // "err_forward_ref_enum": (r"ISO C\+\+ forbids forward references to 'enum' types", "ISO C++ forbids forward references to enum types"),
    # 불완전한 타입으로 멤버 접근
    // "err_incomplete_member_access": (r"member access into incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "member access into incomplete type"),
    # 멤버 초기화자가 비정적 데이터 멤버 또는 기본 클래스를 가리키지 않음
    // "err_mem_init_not_member_or_class": (r"member initializer '.+?' does not name a non-static data member or base class", "member initializer does not name non-static data member or base class"),
    # 멤버 참조 기본 타입이 구조체 또는 유니온이 아님
    // "err_typecheck_member_reference_struct_union": (r"member reference base type '.+?'(?:\s*\(aka '.+?'\))? is not a structure or union", "member reference base type is not structure or union"),
    # 잘못된 멤버 접근 연산자 사용
    // "err_typecheck_member_reference_suggestion": (r"member reference type '.+?'(?:\s*\(aka '.+?'\))? is (?:not a pointer; did you mean to use '\.'|a pointer; did you mean to use '->')\?", "member reference type wrong operator"),
    # 'defined' 뒤에 ')' 누락
    // "err_pp_expected_after": (r"missing '\)' after 'defined'", "missing ')' after defined"),
    # 타입 참조 시 'class' 태그 필요
    // "Unknown_Sema#1": (r"must use 'class' tag to refer to type '.+?' in this scope", "must use class tag to refer to type"),
    # 네임스페이스는 전역 또는 네임스페이스 범위에서만 정의 가능
    // "err_namespace_nonnamespace_scope": (r"namespaces can only be defined in global or namespace scope", "namespaces can only be defined in global or namespace scope"),
    # 네임스페이스에 해당 클래스 없음
    // "err_not_tag_in_scope": (r"no class named '.+?' in namespace '.+?'", "no class named in namespace"),
    # 함수 템플릿 특수화에 매칭되는 함수 템플릿 없음
    // "err_function_template_spec_no_match": (r"no function template matches function template specialization '.+?'", "no function template matches specialization"),
    # 초기화에 매칭되는 생성자 없음
    // "err_ovl_no_viable_function_in_init": (r"no matching constructor for initialization of '.+?'(?:\s*\(aka '.+?'\))?", "no matching constructor for initialization"),
    # 함수 스타일 캐스트에 매칭되는 변환 없음
    // "err_ovl_no_viable_conversion_in_cast": (r"no matching conversion for functional-style cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))?", "no matching conversion for functional-style cast"),
    # 매칭되는 함수/멤버 함수 없음
    // "err_ovl_no_viable_object_call": (r"no matching (?:member )?function for call to (?:object of type )?'.+?'(?:\s*\(aka '.+?'\))?", "no matching function or member function for call"),
    # 매칭되는 리터럴 연산자 없음
    // "err_ovl_no_viable_literal_operator": (r"no matching literal operator for call to '.+?' with arguments of types '.+?' and '.+?', and no matching literal operator template", "no matching literal operator for call"),
    # 네임스페이스/클래스/전역에 해당 멤버 없음
    // "err_no_member": (r"no member named '.+?' in (?:namespace '.+?'|'.+?'|the global namespace)(?:; did you mean .+?)?", "no member named in namespace or class"),
    # 네임스페이스/클래스/전역에 해당 타입/템플릿 없음 #err_typename_nested_not_found
    // "err_no_template": (r"no (?:type|template) named '.+?'(?: in (?:namespace '.+?'|'.+?'|the global namespace))?(?:; did you mean (?:simply )?'.+?')?", "no type or template named in namespace or class"),
    # 템플릿 인수 추론을 위한 생성자 또는 추론 가이드 없음
    // "err_deduced_class_template_ctor_no_viable": (r"no viable constructor or deduction guide for deduction of template arguments of '.+?'", "no viable constructor or deduction guide"),
    # 반환값 타입 변환 불가
    // "err_typecheck_nonviable_condition": (r"no viable conversion from returned value of type '.+?'(?:\s*\(aka '.+?'\))? to function return type '.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion from returned value"),
    # 타입 변환 불가
    // "err_typecheck_nonviable_condition_incomplete": (r"no viable conversion from '.+?'(?:\s*\(aka '.+?'\))? to (?:incomplete type )?'.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion"),
    # 오버로드된 '=' 연산자 없음
    // "err_ovl_no_viable_oper": (r"no viable overloaded '='", "no viable overloaded '='"),
    # 오버로드된 [] 연산자 없음 #err_ovl_no_viable_oper
    // "err_ovl_no_viable_subscript": (r"no viable overloaded operator\[\] for type '.+?'(?:\s*\(aka '.+?'\))?", "no viable overloaded operator[]"),
    # non-const lvalue 참조 바인딩 불가
    // "err_lvalue_reference_bind_to_initlist": (r"non-const lvalue reference to type '.+?'(?:\s*\(aka '.+?'\))? cannot bind to (?:a value of unrelated type|a temporary of type) '.+?'(?:\s*\(aka '.+?'\))?", "non-const lvalue reference cannot bind"),
    # 비친구 클래스 멤버에 한정된 이름 불가
    // "err_member_qualification": (r"non-friend class member '.+?' cannot have a qualified name", "non-friend class member cannot have qualified name"),
    # 비가상 멤버 함수가 가상 멤버 함수를 숨김
    // "override_keyword_hides_virtual_member_function": (r"non-virtual member function marked 'override' hides virtual member function(?:s)?", "non-virtual member function marked override hides virtual member function"),
    # 네임스페이스에 해당 네임스페이스 없음
    // "err_using_directive_member_suggest": (r"no namespace named '.+?' in namespace '.+?'(?:; did you mean '.+?')?", "no namespace named in namespace"),
    # constexpr 함수에 return 문 없음
    // "err_constexpr_body_no_return": (r"no return statement in constexpr function", "no return statement in constexpr function"),
    # 변수 템플릿 특수화에 매칭되는 변수 템플릿 없음
    // "err_var_spec_no_template": (r"no variable template matches specialization", "no variable template matches specialization"),
    # 복사 대입 연산자가 암묵적으로 삭제되어 대입 불가
    // "err_ovl_deleted_special_oper": (r"object of type '.+?'(?:\s*\(aka '.+?'\))? cannot be assigned because its copy assignment operator is implicitly deleted", "object cannot be assigned because copy assignment operator is implicitly deleted"),
    # 가상 멤버 함수만 override 표시 가능
    // "override_keyword_only_allowed_on_virtual_member_functions": (r"only virtual member functions can be marked 'override'", "only virtual member functions can be marked override"),
    # out-of-line 정의가 클래스 내 선언과 불일치
    // "err_member_decl_does_not_match": (r"out-of-line definition of '.+?' does not match any declaration in '.+?'", "out-of-line definition does not match any declaration"),
    # 오버로드 해결 시 삭제된 연산자 선택
    // "err_ovl_deleted_oper": (r"overload resolution selected deleted operator '='", "overload resolution selected deleted operator"),
    # 유효하지 않은 전처리 토큰 생성
    // "err_pp_bad_paste": (r"pasting formed '.+?', an invalid preprocessing token", "pasting formed invalid preprocessing token"),
    # raw 문자열 종료 구분자 누락
    // "err_unterminated_raw_string": (r"raw string missing terminating delimiter \).+?\"", "raw string missing terminating delimiter"),
    # 다른 타입으로 재선언
    // "err_redeclaration_different_type": (r"redeclaration of '.+?' with a different type: '.+?' vs '.+?'", "redeclaration with different type"),
    # 재정의
    // "err_redefinition": (r"redefinition of '.+?'(?: as different kind of symbol)?", "redefinition"),
    # 람다 표현식에서 선언된 지역 변수 참조
    // "err_reference_to_local_in_enclosing_context": (r"reference to local variable '.+?' declared in enclosing lambda expression", "reference to local variable in enclosing lambda"),
    # 비정적 멤버 함수 참조는 호출되어야 함
    // "err_bound_member_function": (r"reference to non-static member function must be called(?:; did you mean to call it with no arguments\?)?", "reference to non-static member function must be called"),
    # 오버로드된 함수 참조 해결 불가
    // "err_ovl_unresolvable": (r"reference to overloaded function could not be resolved(?:; did you mean to call it\?)?", "reference to overloaded function could not be resolved"),
    # 타입 참조가 lvalue/rvalue에 바인딩 불가
    // "err_reference_bind_failed": (r"reference to type '.+?'(?:\s*\(aka '.+?'\))? could not bind to (?:an lvalue|an rvalue) of type '.+?'(?:\s*\(aka '.+?'\))?", "reference to type could not bind"),
    # reinterpret_cast 불가
    // "err_bad_cxx_cast_generic": (r"reinterpret_cast from '.+?' to '.+?'(?:\s*\(aka '.+?'\))? is not allowed", "reinterpret_cast is not allowed"),
    # 람다 반환 타입 불일치
    // "err_typecheck_missing_return_type_incompatible": (r"return type '.+?'(?:\s*\(aka '.+?'\))? must match previous return type '.+?' when lambda expression has unspecified explicit return type", "return type must match previous return type in lambda"),
    # 반환 타입이 추상 클래스
    // "err_abstract_type_in_decl#2": (r"return type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "return type is abstract class"),
    # 가상 함수의 반환 타입이 공변적이지 않음
    // "err_covariant_return_ambiguous_derived_to_base_conv": (r"return type of virtual function '.+?' is not covariant with the return type of the function it overrides", "return type of virtual function is not covariant"),
    # .* 연산자의 우측 피연산자가 멤버 포인터 타입이 아님
    // "err_bad_memptr_rhs": (r"right hand operand to \.\* has non-pointer-to-member type '.+?'(?:\s*\(aka '.+?'\))?", "right hand operand to .* has non-pointer-to-member type"),
    # rvalue 참조가 lvalue에 바인딩 불가
    // "err_lvalue_to_rvalue_ref": (r"rvalue reference to type '.+?' cannot bind to lvalue of type '.+?'", "rvalue reference cannot bind to lvalue"),
    # 모호한 참조
    // "err_ambiguous_reference": (r"reference to '.+?' is ambiguous", "reference is ambiguous"),
    # 정적 어서션 표현식이 정수 상수 표현식이 아님
    // "err_static_assert_expression_is_not_constant": (r"static assertion expression is not an integral constant expression", "static assertion expression is not integral constant expression"),
    # 정적 어서션 실패
    // "err_static_assert_failed": (r"static assertion failed.*", "static assertion failed"),
    # 지역 구조체에 정적 데이터 멤버 불가
    // "err_static_data_member_not_allowed_in_local_class": (r"static data member '.+?' not allowed in local struct '.+?'", "static data member not allowed in local struct"),
    # 상속 관계 없는 타입 간 static_cast 불가
    // "err_bad_cxx_cast_unrelated_class": (r"static_cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?', which are not related by inheritance, is not allowed", "static_cast between unrelated types is not allowed"),
    # 불완전한 타입 포인터 서브스크립트
    // "err_subscript_incomplete_or_sizeless_type": (r"subscript of pointer to incomplete type '.+?'", "subscript of pointer to incomplete type"),
    # 서브스크립트 대상이 배열/포인터/벡터가 아님
    // "err_typecheck_subscript_value": (r"subscripted value is not an array, pointer, or vector", "subscripted value is not array pointer or vector"),
    # 템플릿 타입 매개변수에 타입이 아닌 인자
    // "err_template_arg_must_be_type": (r"template argument for template type parameter must be a type", "template argument must be a type"),
    # 템플릿 템플릿 매개변수에 클래스 템플릿 또는 타입 별칭 템플릿이 아닌 인자
    // "err_template_arg_must_be_template": (r"template argument for template template parameter must be a class template or type alias template", "template argument for template template parameter must be class template or type alias template"),
    # 템플릿 특수화에 'template<>' 필요
    // "err_template_spec_needs_header": (r"template specialization requires 'template<>'", "template specialization requires template<>"),
    # 템플릿 템플릿 인자의 템플릿 매개변수가 다름
    // "err_template_arg_template_params_mismatch": (r"template template argument has different template parameters than its corresponding template template parameter", "template template argument has different template parameters"),
    # 지역 클래스 내부에 템플릿 선언 불가
    // "err_template_inside_local_class": (r"templates cannot be declared inside of a local class", "templates cannot be declared inside local class"),
    # 호출 인자 부족
    // "err_typecheck_call_too_few_args": (r"too few arguments (?:provided to function-like macro invocation|to function call, expected \d+, have \d+(?:; did you mean '.+?')?)", "too few arguments"),
    # 템플릿 인자 부족
    // "err_template_arg_list_different_arity": (r"too few template arguments for (?:alias template|class template) '.+?'", "too few template arguments"),
    # 함수형 매크로 인자 과다
    // "err_too_many_args_in_macro_invoc": (r"too many arguments provided to function-like macro invocation", "too many arguments to function-like macro"),
    # 함수 호출 인자 과다
    // "err_typecheck_call_too_many_args": (r"too many arguments to function call, expected .+?, have .+?", "too many arguments to function call"),
    # 직접/가상 기본 클래스가 아닌 타입
    // "err_not_direct_base_or_virtual": (r"type '.+?' is not a direct or virtual base of '.+?'", "type is not direct or virtual base"),
    # 타입이 좁혀질 수 없음
    // "warn_init_list_type_narrowing": (r"type '.+?' cannot be narrowed to '.+?'(?:\s*\(aka '.+?'\))? in initializer list", "type cannot be narrowed in initializer list"),
    # 타입이 서브스크립트 연산자를 제공하지 않음
    // "err_ovl_no_oper": (r"type '.+?'(?:\s*\(aka '.+?'\))? does not provide a (?:subscript|call) operator", "type does not provide subscript or call operator"),
    # 타입 별칭 재정의 시 타입 불일치
    // "err_redefinition_different_typedef": (r"type alias redefinition with different types \('.+?' vs '.+?'\)", "type alias redefinition with different types"),
    # 참조의 참조 타입 이름 선언
    // "err_illegal_decl_reference_to_reference": (r"type name declared as a reference to a reference", "type name declared as reference to reference"),
    # 예상치 못한 문자
    // "err_character_not_allowed": (r"unexpected character <.+?>", "unexpected character"),
    # 예상치 못한 네임스페이스 이름
    // "err_unexpected_namespace": (r"unexpected namespace name '.+?': expected expression", "unexpected namespace name"),
    # 알 수 없는 클래스/타입 이름
    // "err_unknown_type_or_class_name_suggest": (r"unknown (?:class|type) name '.+?'(?:; did you mean '.+?')?", "unknown class name"),
    # 함수형 매크로 호출이 종료되지 않음
    // "err_unterm_macro_invoc": (r"unterminated function-like macro invocation", "unterminated function-like macro invocation"),
    # 이전 선언과 일치하지 않는 태그 타입으로 OfType 사용
    // "err_use_with_wrong_tag": (r"use of 'OfType' with tag type that does not match previous declaration", "use of OfType with mismatched tag type"),
    # 클래스 템플릿에 템플릿 인자 필요
    // "err_template_missing_args": (r"use of class template '.+?' requires template arguments(?:; argument deduction not allowed .+?)?", "use of class template requires template arguments"),
    # 오버로드된 [] 연산자 사용이 모호함
    // "err_ovl_ambiguous_oper_unary": (r"use of overloaded operator '\[\]' is ambiguous \(with operand types '.+?' and '.+?'\)", "use of overloaded operator[] is ambiguous"),
    # 선언되지 않은 식별자 사용
    // "err_undeclared_var_use": (r"use of undeclared identifier '.+?'(?:; did you mean '.+?')?", "use of undeclared identifier"),
    # 선언되지 않은 operator() 사용
    // "err_undeclared_use": (r"use of undeclared 'operator\(\)'", "use of undeclared operator()"),
    # using 선언이 클래스 멤버를 참조할 수 없음
    // "err_using_decl_can_not_refer_to_class_member": (r"using declaration cannot refer to (?:class member|a namespace)", "using declaration cannot refer to class member or namespace"),
    # using 선언이 클래스가 아닌 네임스페이스를 참조함
    // "err_using_decl_nested_name_specifier_is_not_class": (r"using declaration in class refers into '.+?', which is not a class", "using declaration in class refers to non-class"),
    # bool로 문맥 변환 불가
    // "err_typecheck_bool_condition": (r"value of type '.+?'(?:\s*\(aka '.+?'\))? is not contextually convertible to 'bool'", "value is not contextually convertible to bool"),
    # 캡처 기본값 없는 람다에서 암묵적 캡처 불가
    // "err_lambda_impcap": (r"variable '.+?' cannot be implicitly captured in a lambda with no capture-default specified", "variable cannot be implicitly captured in lambda"),
    # auto 타입 변수의 호환되지 않는 초기화자
    // "err_auto_var_deduction_failure": (r"variable '.+?' with type 'auto' has incompatible initializer of type '.+?'", "variable with auto type has incompatible initializer"),
    # auto 추론 타입 변수가 자신의 초기화자에 등장
    // "err_auto_variable_cannot_appear_in_own_initializer": (r"variable '.+?' declared with deduced type 'auto' cannot appear in its own initializer", "variable with deduced auto type cannot appear in its own initializer"),
    # 불완전한 타입의 변수
    // "err_typecheck_decl_incomplete_type": (r"variable has incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "variable has incomplete type"),
    # private/protected 소멸자를 가진 타입의 변수
    // "err_access_dtor_var": (r"variable of type '.+?' has (?:private|protected) destructor", "variable of type has private or protected destructor"),
    # 변수 타입이 추상 클래스
    // "err_abstract_type_in_decl#3": (r"variable type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "variable type is abstract class"),
    # 가상 함수의 반환 타입이 오버라이드하는 함수와 다름
    // "err_different_return_type_for_overriding_virtual_function": (r"virtual function '.+?' has a different return type \('.+?'(?:\s*\(aka '.+?'\))?\) than the function it overrides \(which has return type '.+?'\)", "virtual function has different return type than overridden function"),
    # 가변 크기 객체 초기화 불가
    // "err_variable_object_no_init": (r"variable-sized object may not be initialized", "variable-sized object may not be initialized"),
    # 파일을 찾을 수 없음
    // "err_pp_file_not_found": (r"'.+?' file not found", "file not found"),
    # private/protected 멤버 접근
    // "err_access": (r"'.+?' is a (?:private|protected) member of '.+?'", "private or protected member access"),
    # 불완전한 타입
    // "err_bad_cast_incomplete": (r"'.+?' is an incomplete type", "incomplete type"),
    # const가 아닌 함수에 const 객체로 this 인자 전달
    // "err_member_function_call_bad_cvr": (r"'this' argument to member function '.+?' has type '.+?'(?:\s*\(aka '.+?'\))?, but function is not marked const", "this argument to non-const member function"),
    # auto가 함수 프로토타입에서 허용되지 않음
    // "err_auto_not_allowed": (r"'auto' not allowed in function prototype", "auto not allowed in function prototype"),
    # const 한정자가 참조에 적용될 수 없음
    // "err_invalid_reference_qualifier_application": (r"'const' qualifier may not be applied to a reference", "const qualifier may not be applied to reference"),
    # mutable이 함수에 적용될 수 없음
    // "err_mutable_function": (r"'mutable' cannot be applied to functions", "mutable cannot be applied to functions"),
    # using namespace가 클래스 내부에서 허용되지 않음
    // "err_using_namespace_in_class": (r"'using namespace' is not allowed in classes", "using namespace not allowed in classes"),
    # void가 첫 번째이자 유일한 매개변수여야 함
    // "err_void_only_param": (r"'void' must be the first and only parameter if specified", "void must be first and only parameter"),
    # override가 표시됐지만 오버라이드하는 함수가 없음
    // "err_function_marked_override_not_overriding": (r"'.+?' marked 'override' but does not override any member functions", "marked override but does not override any member functions"),
    # 값을 참조할 수 없는 식별자
    // "err_ref_non_value": (r"'.+?' does not refer to a value", "does not refer to a value"),
    # gmock_xxx가 함수 배열로 선언됨
    // "err_illegal_decl_array_of_functions": (r"'.+?' declared as array of functions of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as array of functions"),
    # va_start가 고정 인자 함수에서 사용됨
    // "err_va_start_fixed_function": (r"'va_start' used in function with fixed args", "va_start used in function with fixed args"),
    # 클래스, 네임스페이스, 열거형이 아닌 식별자
    // "err_expected_class_or_namespace": (r"'.+?' is not a class, namespace, or enumeration", "is not a class namespace or enumeration"),
    # 참조에 대한 포인터로 선언된 타입 이름
    // "err_illegal_decl_pointer_to_reference": (r"'.+?' declared as a pointer to a reference of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as pointer to reference"),
    # 다형성이 아닌 타입
    // "err_bad_dynamic_cast_not_polymorphic": (r"'.+?' is not polymorphic", "is not polymorphic"),
    # 단항 표현식에 잘못된 인자 타입
    // "err_typecheck_unary_expr": (r"invalid argument type '.+?' to unary expression", "invalid argument type to unary expression"),
    # 포인터를 더 작은 타입으로 캐스트 시 정보 손실
    // "err_bad_reinterpret_cast_small_int": (r"cast from pointer to smaller type '.+?'(?:\s*\(aka '.+?'\))? loses information", "cast from pointer to smaller type loses information"),
    # 비멤버 함수에 const 한정자 불가
    // "err_invalid_qualified_function_type": (r"non-member function cannot have 'const' qualifier", "non-member function cannot have const qualifier"),
    # mutable은 멤버 변수에만 적용 가능
    // "err_mutable_nonmember": (r"'mutable' can only be applied to member variables", "mutable can only be applied to member variables"),
    # 함수 호출 인자 누락
    // "err_typecheck_call_too_few_args_one": (r"too few arguments to function call, single argument '.+?' was not specified", "too few arguments to function call single argument not specified"),
    # 선언의 언어 링키지가 다름
    // "err_different_language_linkage": (r"declaration of '.+?' has a different language linkage", "declaration has different language linkage"),
    # 기본 인자는 함수 선언의 매개변수에만 지정 가능
    // "err_param_default_argument_nonfunc": (r"default arguments can only be specified for parameters in a function declaration", "default arguments only for parameters in function declaration"),
    
    // "err_undefined_symbol": (r"undefined reference to symbol:?\s*.+?", "undefined symbol"),
    // "err_undefined_reference": (r"undefined reference to `.+?'", "undefined reference"),
    // "err_multiple_definition": (r"multiple definition of `.+?'", "multiple definition"),
    // "err_cannot_find_library": (r"cannot find -l.+", "cannot find library"),
}