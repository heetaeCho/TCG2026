CATEGORIES = { # Lexical = 15, Syntactic = 25, Linker = 4, Semantic = 175 => 207
    "Lexical": ['err_character_not_allowed_identifier', 'err_character_too_large', 'err_invalid_suffix_constant', 
                'err_ucn_escape_invalid', 'err_pp_expected_after', 'err_pp_bad_paste', 'err_unterminated_raw_string', 
                'err_too_many_args_in_macro_invoc', 'err_character_not_allowed', 'err_unterm_macro_invoc', 
                'err_pp_file_not_found', 'err_pp_invalid_directive', 'ext_reserved_user_defined_literal',
                "err_unterminated_raw_string", "err_escape_too_large"],

    "Syntactic": ['err_attributes_not_allowed', 'err_incomplete_array_member_init', 
                  'err_brackets_go_after_unqualified_id', 'err_expected_lparen_after_type', 
                  'err_expected_class_name', 'err_expected_expression', 'err_missing_param', 
                  'err_expected_statement', 'err_expected_unqualified_id', 'err_extraneous_closing_brace', 
                  'err_invalid_token_after_declarator_suggest_equal', 'err_keyword_as_parameter', 
                  'err_namespace_nonnamespace_scope', 'err_illegal_decl_reference_to_reference', 
                  'err_invalid_reference_qualifier_application', 'err_using_namespace_in_class',
                   "Unknown_Parse#1", "err_unexpected_unqualified_id", "err_bad_parameter_name",
                   "err_virt_specifier_outside_class", "err_unexpected_template_in_unqualified_id",
                   "err_function_definition_not_allowed", "err_init_list_bin_op", "err_templated_invalid_declaration",
                   "err_extraneous_token_before_semi"],

    "Linker": ["err_undefined_symbol", "err_undefined_reference", "err_multiple_definition", "err_cannot_find_library"],

    "Semantic": { # subtype = 16
        # Abstract-Type Instantiation = 6
        "Abstract-Type Instantiation": ["err_allocation_of_abstract_type", "err_abstract_type_in_decl#1", 
                                        "err_abstract_type_in_decl#2", "err_abstract_type_in_decl#3", "err_array_of_abstract_type",
                                        "err_abstract_type_in_decl#4"],
        # Access Control = 6
        "Access Control": ["err_access", "err_access_ctor", "err_access_base_ctor", "err_access_dtor_base",
                           "err_access_field_ctor", "err_access_dtor_var"],
        # Constexpr/Enum/Assert/Literal = 9
        "Constexpr/Enum/Assert/Literal": ["err_constexpr_if_condition_expression_is_not_constant",
                                          "err_constexpr_var_requires_const_init",
                                          "err_constexpr_var_non_literal", "err_constexpr_non_literal_param",
                                          "err_constexpr_body_no_return","err_static_assert_failed", 
                                          "err_static_assert_expression_is_not_constant", "err_forward_ref_enum",
                                          "err_ovl_no_viable_literal_operator"],
        # Construction/Initialization = 15
        "Construction/Initialization": ["err_ovl_no_viable_function_in_init", "err_ovl_deleted_special_init",
                                        "err_missing_default_ctor#1", "err_missing_default_ctor#2",
                                        "err_default_init_const", "err_default_member_initializer_not_yet_parsed",
                                        "err_ctor_dtor_returns_void", "err_excess_initializers", "err_variable_object_no_init",
                                        "warn_field_is_uninit", "err_reference_var_requires_init",
                                        "err_destructor_return_type", "err_selected_explicit_constructor",
                                        "err_deleted_inherited_ctor_use", "err_only_constructors_take_base_inits",
                                        "err_initializer_string_for_char_array_too_long"],
        # Deleted/Special Member = 9
        "Deleted/Special Member": ["err_ovl_deleted_call", "err_ovl_deleted_init", "err_deleted_function_use", 
                                   "err_deleted_override", "err_ovl_deleted_special_oper", "err_ovl_deleted_oper",
                                   "warn_defaulted_comparison_deleted", "err_ovl_deleted_conversion_in_cast",
                                   "err_typecheck_deleted_function"],
        # Functions/Call Resolution = 11
        "Functions/Call Resolution": ["err_ovl_ambiguous_init", "err_ovl_no_viable_object_call", 
                                      "err_member_call_without_object", "err_typecheck_call_not_function",
                                      "err_typecheck_call_too_few_args", "err_typecheck_call_too_many_args",
                                      "err_typecheck_call_too_few_args_one", "err_ovl_diff_return_type", "err_ref_qualifier_overload",
                                      "err_ovl_unresolvable", "err_early_catch_all"],
        # Operator/Call = 14
        "Operator/Call": ["err_typecheck_invalid_operands", "err_ovl_no_viable_oper", "err_ovl_no_viable_subscript",
                          "err_ovl_ambiguous_oper_unary", "err_ovl_no_oper", "err_typecheck_subscript_value",
                          "err_no_subobject_property_setting", "err_typecheck_array_not_modifiable_lvalue",
                          "err_typecheck_assign_const", "err_typecheck_unary_expr", "err_for_range_deduction_failure",
                          "err_typecheck_illegal_increment_decrement", "err_for_range_invalid",
                          "err_typecheck_subscript_not_integer"],
        # Override/Inheritance = 12
        "Override/Inheritance": ["err_function_marked_override_not_overriding", "override_keyword_hides_virtual_member_function",
                                 "override_keyword_only_allowed_on_virtual_member_functions", 
                                 "err_covariant_return_ambiguous_derived_to_base_conv", 
                                 "err_different_return_type_for_overriding_virtual_function",
                                 "err_override_exception_spec", "err_class_marked_final_used_as_base",
                                 "err_not_direct_base_or_virtual", "err_base_must_be_class", "err_bad_dynamic_cast_not_polymorphic",
                                 "err_using_decl_constructor_not_in_direct_base", "err_missing_exception_specification"],
        # Incomplete Type = 19
        "Incomplete Type": ["err_bad_cast_incomplete", "err_typecheck_decl_incomplete_type", "err_field_incomplete_or_sizeless",
                            "err_incomplete_member_access", "err_new_incomplete_or_sizeless_type",
                            "err_typecheck_arithmetic_incomplete_or_sizeless_type", "err_subscript_incomplete_or_sizeless_type",
                            "warn_delete_incomplete", "err_typecheck_incomplete_tag", "err_func_def_incomplete_result",
                            "err_incomplete_nested_name_spec", "err_for_range_incomplete_type", "err_init_incomplete_type",
                            "err_sizeof_alignof_incomplete_or_sizeless_type", "err_invalid_incomplete_type_use",
                            "err_incomplete_base_class", "err_call_function_incomplete_return", "err_call_incomplete_argument",
                            "err_auto_fn_used_before_defined"],
        # Symbol/Lookup = 14
        "Symbol/Lookup": ["err_undeclared_var_use", "err_no_member", "err_no_template", "err_not_tag_in_scope", 
                          "err_using_directive_member_suggest", "err_unknown_type_or_class_name_suggest", "err_undeclared_use",
                          "err_ref_non_value", "err_ambiguous_reference", "err_unexpected_namespace", "Unknown_Sema#1",
                          "err_lambda_impcap", "err_addr_ovl_no_viable", "err_out_of_line_qualified_id_type_names_constructor"],
        # Templates/Generics = 24
        "Templates/Generics": ["err_implicit_instantiate_member_undefined", "err_template_arg_list_different_arity", 
                               "err_template_missing_args", "err_not_class_template_specialization", "err_template_spec_needs_header",
                               "err_template_arg_must_be_type", "err_template_arg_must_be_template", 
                               "err_template_arg_template_params_mismatch", "err_template_inside_local_class",
                               "err_deduced_class_template_ctor_no_viable", "err_function_template_spec_no_match",
                               "err_var_spec_no_template", "err_template_spec_redecl_out_of_scope",
                               "err_template_arg_must_be_expr", "err_explicit_instantiation_unqualified_wrong_namespace",
                               "err_explicit_instantiation_not_known", "Unknown_Sema#2", "err_template_spec_redecl_global_scope",
                               "err_template_member", "err_function_parameter_pack_without_parameter_packs", "Unknown_Sema#3",
                               "err_non_template_in_template_id", "err_pack_expansion_without_parameter_packs",
                               "err_unexpanded_parameter_pack"],
        # Type Conversion/Reference Binding = 27
        "Type Conversion/Reference Binding": ["err_typecheck_nonviable_condition_incomplete", "err_typecheck_nonviable_condition",
                                              "err_init_conversion_failed", "err_typecheck_convert_incompatible", 
                                              "err_typecheck_convert_incompatible_pointer", "warn_init_list_type_narrowing",
                                              "ext_init_list_constant_narrowing", "err_ovl_ambiguous_conversion_in_cast",
                                              "err_ovl_no_viable_conversion_in_cast", "err_lvalue_reference_bind_to_initlist",
                                              "err_lvalue_to_rvalue_ref", "err_reference_bind_failed", "err_bad_cxx_cast_generic",
                                              "err_bad_cxx_cast_unrelated_class", "err_bad_reinterpret_cast_small_int",
                                              "err_ovl_no_conversion_in_cast", "err_typecheck_bool_condition",
                                              "err_auto_inconsistent_deduction", "err_auto_var_deduction_failure",
                                              "err_typecheck_convert_discards_qualifiers", "err_reference_bind_drops_quals",
                                              "err_typecheck_missing_return_type_incompatible",
                                              "err_typecheck_converted_constant_expression", "err_typecheck_comparison_of_distinct_pointers",
                                              "err_typecheck_convert_int_pointer", "ext_typecheck_convert_incompatible_pointer_sign",
                                              "err_bad_reinterpret_cast_overload"
                                              ],
        # Type Redefinition/Redeclaration = 14
        "Type Redefinition/Redeclaration": ["err_redefinition", "err_redeclaration_different_type", "err_member_decl_does_not_match",
                                            "err_member_redeclared", "err_duplicate_member", "err_tag_definition_of_typedef",
                                            "err_redefinition_different_typedef", "err_enum_redeclare_type_mismatch",
                                            "err_invalid_declarator_scope", "err_different_language_linkage",
                                            "err_use_with_wrong_tag", "err_static_non_static", "err_enum_redeclare_scoped_mismatch",
                                            "err_using_decl_conflict_reverse"],
        # Qualifier/Specifier Missuse = 11
        "Qualifier/Specifier Missuse": ["err_invalid_qualified_function_type", "err_mutable_function", 
                                        "err_mutable_nonmember", "err_auto_not_allowed", "err_void_only_param",
                                        "err_missing_type_specifier", "err_param_default_argument_nonfunc",
                                        "err_va_start_fixed_function", "warn_unused_expr", "err_static_block_func",
                                        "err_exceptions_disabled"],
        # Pointer/Reference Misuse = 14
        "Pointer/Reference Misuse": ["err_typecheck_invalid_lvalue_addrof", "err_reference_to_void", 
                                    "err_deduced_class_template_compound_type", "err_illegal_decl_pointer_to_reference",
                                    "err_illegal_decl_array_of_functions", "err_typecheck_indirection_requires_pointer",
                                    "err_bad_memptr_rhs", "err_delete_operand", "warn_format_nonliteral_noargs",
                                    "err_func_returning_array_function", "err_reference_to_local_in_enclosing_context",
                                    "err_typecheck_addrof_temporary", "err_invalid_form_pointer_member_function",
                                    "err_illegal_decl_mempointer_to_void"],
        # This/Non-Static Member/Using Misuse = 21
        "This/Non-Static Member/Using Misuse": ["err_invalid_this_use", "err_member_function_call_bad_cvr", "err_bound_member_function",
                                "err_member_qualification", "err_using_decl_can_not_refer_to_class_member",
                                "err_using_decl_nested_name_specifier_is_not_class", "err_member_reference_needs_call",
                                "err_typecheck_member_reference_struct_union", "err_typecheck_member_reference_suggestion",
                                "err_mem_init_not_member_or_class", "err_expected_class_or_namespace", 
                                "err_auto_variable_cannot_appear_in_own_initializer", "err_static_data_member_not_allowed_in_local_class",
                                "err_using_decl_nested_name_specifier_is_not_base_class", "err_nested_non_static_member_use",
                                "err_typecheck_member_reference_type", "err_member_function_call_bad_ref", "err_this_capture",
                                "err_invalid_non_static_member_use", "err_using_decl_nested_name_specifier_is_current_class",
                                "err_unqualified_pointer_member_function"],
    },
}

PATTERNS = {
    # 선언에서 타입 지정자 누락
    "err_missing_type_specifier": (r"a type specifier is required for all declarations", "missing type specifier in declaration"),
    # 추상 클래스 타입 객체 할당 시도
    "err_allocation_of_abstract_type": (r"allocating an object of abstract class type '.+?'(?:\s*\(aka '.+?'\))?", "allocating object of abstract class type"),
    # 불완전한 타입 객체 할당 시도
    "err_new_incomplete_or_sizeless_type": (r"allocation of incomplete type '.+?'", "allocation of incomplete type"),
    # 함수형 캐스트에서 모호한 변환
    "err_ovl_ambiguous_conversion_in_cast": (r"ambiguous conversion for functional-style cast from '.+?' to '.+?'", "ambiguous conversion for functional-style cast"),
    # 속성 목록이 올 수 없는 위치
    "err_attributes_not_allowed": (r"an attribute list cannot appear here", "attribute list in invalid position"),
    # 불완전한 타입 포인터에 대한 산술 연산
    "err_typecheck_arithmetic_incomplete_or_sizeless_type": (r"arithmetic on a pointer to an incomplete type '.+?'", "arithmetic on pointer to incomplete type"),
    # 기본 멤버 초기화자에서 배열 크기 추론 불가
    "err_incomplete_array_member_init": (r"array bound cannot be deduced from a default member initializer", "array bound cannot be deduced from default member initializer"),
    # 배열 타입 대입 불가
    "err_typecheck_array_not_modifiable_lvalue": (r"array type '.+?'(?:\s*\(aka '.+?'\))? is not assignable", "array type is not assignable"),
    # const 한정자 무시하고 대입
    "err_typecheck_convert_discards_qualifiers": (r"assigning to '.+?' from '.+?' discards qualifiers", "assigning discards qualifiers"),
    # 호환되지 않는 타입 대입
    "err_typecheck_convert_incompatible": (r"assigning to '.+?'(?:\s*\(aka '.+?'\))? from incompatible type '.+?'", "assigning from incompatible type"),
    # 삭제된 함수 사용 시도
    "err_deleted_function_use": (r"attempt to use a deleted function", "attempt to use deleted function"),
    # final로 표시된 클래스 상속 시도
    "err_class_marked_final_used_as_base": (r"base '.+?' is marked 'final'", "base class marked final"),
    # 기본 클래스의 생성자가 private
    "err_access_base_ctor": (r"base class '.+?' has private (?:default )?constructor", "base class has private constructor"),
    # 기본 클래스의 소멸자가 private
    "err_access_dtor_base": (r"base class '.+?' has private destructor", "base class has private destructor"),
    # 기본 클래스가 불완전한 타입
    "err_incomplete_base_class": (r"base class has incomplete type", "base class has incomplete type"),
    # 멤버 참조의 베이스가 함수
    "err_member_reference_needs_call": (r"base of member reference is a function; perhaps you meant to call it with no arguments\?", "base of member reference is function"),
    # 베이스 지정자가 클래스를 가리키지 않음
    "err_base_must_be_class": (r"base specifier must name a class", "base specifier must name a class"),
    # 참조 바인딩 시 한정자 제거
    "err_reference_bind_drops_quals": (r"binding reference of type '.+?' to value of type '.+?' drops '(?:const|volatile)' qualifier", "binding reference drops qualifier"),
    # 배열 선언 시 괄호 위치 오류
    "err_brackets_go_after_unqualified_id": (r"brackets are not allowed here; to declare an array, place the brackets after the name", "brackets not allowed here"),
    # 삭제된 생성자 호출
    "err_ovl_deleted_init": (r"call to deleted constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to deleted constructor"),
    # 암묵적으로 삭제된 생성자 호출
    "err_ovl_deleted_special_init": (r"call to implicitly-deleted (?:copy|default) constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to implicitly-deleted constructor"),
    # 삭제된 함수 호출
    "err_ovl_deleted_call": (r"call to deleted function '.+?'", "call to deleted function"),
    # 모호한 함수/생성자/멤버 함수 호출
    "err_ovl_ambiguous_init": (r"call to (?:constructor of|member function|'.+?') '.+?' is ambiguous|call to '.+?' is ambiguous", "ambiguous call"),
    # 객체 인자 없이 비정적 멤버 함수 호출
    "err_member_call_without_object": (r"call to non-static member function without an object argument", "call to non-static member function without object argument"),
    # 함수가 아닌 타입 호출 시도
    "err_typecheck_call_not_function": (r"called object type '.+?'(?:\s*\(aka '.+?'\))? is not a function or function pointer", "called object type is not a function or function pointer"),
    # 불완전한 반환 타입으로 함수 호출
    "err_call_function_incomplete_return": (r"calling '.+?'(?:\s*\(aka '.+?'\))? with incomplete return type '.+?'(?:\s*\(aka '.+?'\))?", "calling with incomplete return type"),
    # private/protected 생성자/소멸자 호출
    "err_access_ctor": (r"calling a (?:private|protected) (?:constructor|destructor) of class '.+?'", "calling private or protected constructor or destructor"),
    # const 한정 타입에 대입 불가
    "err_typecheck_assign_const": (r"cannot assign to (?:non-static data member|static data member|variable) '.+?' with const-qualified type '.+?'(?:\s*\(aka '.+?'\))?|cannot assign to return value because function '.+?' returns a const value", "cannot assign to const-qualified type or value"),
    # 변환 연산자 없이 타입 변환 불가
    "err_ovl_no_conversion_in_cast": (r"cannot convert '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))? without a conversion operator", "cannot convert without conversion operator"),
    # 네임스페이스 범위 밖에서 정의/재선언 불가
    "err_invalid_declarator_scope": (r"cannot define or redeclare '.+?' here because namespace '.*?' does not enclose namespace '.+?'", "cannot define or redeclare outside enclosing namespace"),
    # unique_ptr 표현식 delete 불가
    "err_delete_operand": (r"cannot delete expression of type '.+?'", "cannot delete expression of type"),
    # void에 대한 참조 생성 불가
    "err_reference_to_void": (r"cannot form a reference to 'void'", "cannot form reference to void"),
    # 추론된 클래스 템플릿 특수화 타입에 대한 포인터/참조 생성 불가
    "err_deduced_class_template_compound_type": (r"cannot form (?:pointer|reference) to deduced class template specialization type", "cannot form pointer or reference to deduced class template specialization type"),
    # 타입 불일치로 초기화 불가
    "err_init_conversion_failed": (r"cannot initialize (?:a parameter|a variable|a member subobject|an array element|object parameter|return object) of type '.+?'(?:\s*\(aka '.+?'\))? with (?:an lvalue|an rvalue|an expression) of type '.+?'(?:\s*\(aka '.+?'\))?", "cannot initialize with incompatible type"),
    # ref-qualifier 없는 멤버 함수와 ref-qualifier 있는 멤버 함수 오버로드 불가
    "err_ref_qualifier_overload": (r"cannot overload a member function without a ref-qualifier with a member function with ref-qualifier '.+?'", "cannot overload member function with ref-qualifier mismatch"),
    # 종속 템플릿 특수화 불가
    "err_not_class_template_specialization": (r"cannot specialize a dependent template", "cannot specialize dependent template"),
    # rvalue 주소 참조 불가
    "err_typecheck_invalid_lvalue_addrof": (r"cannot take the address of an rvalue of type '.+?'", "cannot take address of rvalue"),
    # 예외 비활성화 상태에서 try/throw 사용 불가
    "err_exceptions_disabled": (r"cannot use '(?:try|throw)' with exceptions disabled", "cannot use try or throw with exceptions disabled"),
    # 불완전한 타입을 range로 사용 불가
    "err_for_range_incomplete_type": (r"cannot use incomplete type '.+?' as a range", "cannot use incomplete type as range"),
    # 식별자에 허용되지 않는 문자
    "err_character_not_allowed_identifier": (r"character <.+?> not allowed in an identifier", "character not allowed in identifier"),
    # 문자 리터럴 타입에 비해 너무 큰 문자
    "err_character_too_large": (r"character too large for enclosing character literal type", "character too large for character literal type"),
    # 클래스 멤버 재선언 불가
    "err_member_redeclared": (r"class member cannot be redeclared", "class member cannot be redeclared"),
    # 클래스 템플릿 부분 특수화가 올바른 네임스페이스 안에 없음
    "err_template_spec_redecl_out_of_scope": (r"class template partial specialization of '.+?' not in a namespace enclosing '.+?'", "class template partial specialization not in enclosing namespace"),
    # 상수 표현식이 타입으로 좁혀질 수 없음
    "ext_init_list_constant_narrowing": (r"constant expression evaluates to .+? which cannot be narrowed to type '.+?'(?:\s*\(aka '.+?'\))?", "constant expression cannot be narrowed"),
    # constexpr 생성자의 매개변수 타입이 리터럴 타입이 아님
    "err_constexpr_non_literal_param": (r"constexpr constructor's .+? parameter type '.+?'(?:\s*\(aka '.+?'\))? is not a literal type", "constexpr constructor parameter is not literal type"),
    # constexpr if 조건이 상수 표현식이 아님
    "err_constexpr_if_condition_expression_is_not_constant": (r"constexpr if condition is not a constant expression", "constexpr if condition is not constant expression"),
    # constexpr 변수가 상수 표현식으로 초기화되지 않음
    "err_constexpr_var_requires_const_init": (r"constexpr variable '.+?' must be initialized by a constant expression", "constexpr variable must be initialized by constant expression"),
    # constexpr 변수가 비리터럴 타입을 가질 수 없음
    "err_constexpr_var_non_literal": (r"constexpr variable cannot have non-literal type '.+?'", "constexpr variable cannot have non-literal type"),
    # 생성자가 void 표현식을 반환하면 안됨
    "err_ctor_dtor_returns_void": (r"constructor '.+?' must not return void expression", "constructor must not return void expression"),
    # 기본 생성자 없는 기본 클래스/멤버 명시적 초기화 필요
    "err_missing_default_ctor#1": (r"constructor for '.+?' must explicitly initialize the (?:base class|member) '.+?' which does not have a default constructor", "constructor must explicitly initialize base class or member without default constructor"),
    # 초기화 리스트 원소 타입 추론 충돌
    "err_auto_inconsistent_deduction": (r"deduced conflicting types \('.+?' vs '.+?'(?:\s*\(aka '.+?'\))?\) for initializer list element type", "deduced conflicting types for initializer list element type"),
    # user-provided 기본 생성자 없는 const 타입 기본 초기화
    "err_default_init_const": (r"default initialization of an object of const type '.+?'(?:\s*\(aka '.+?'\))?(?:\s*without a user-provided default constructor)?", "default initialization of const type without user-provided default constructor"),
    # 멤버 함수 밖에서 기본 멤버 초기화자 필요
    "err_default_member_initializer_not_yet_parsed": (r"default member initializer for '.+?' needed within definition of enclosing class '.+?' outside of member functions", "default member initializer needed outside of member functions"),
    # 타입 정의가 동일한 이름의 type alias 또는 typedef와 충돌함
    "err_tag_definition_of_typedef": (r"definition of type '.+?' conflicts with (?:type alias|typedef) of the same name", "definition conflicts with type alias or typedef")  ,
    # 삭제된 함수가 비삭제 함수를 오버라이드할 수 없음
    "err_deleted_override": (r"deleted function '.+?' cannot override a non-deleted function", "deleted function cannot override non-deleted function"),
    # 불완전한 타입 포인터 삭제로 인한 미정의 동작
    "warn_delete_incomplete": (r"deleting pointer to incomplete type '.+?'(?:\s*\(aka '.+?'\))? (?:may cause undefined behavior|is incompatible with C\+\+\w+ and may cause undefined behavior)", "deleting pointer to incomplete type may cause undefined behavior"),
    # 중복 멤버 선언
    "err_duplicate_member": (r"duplicate member '.+?'", "duplicate member"),
    # 다른 기본 타입으로 열거형 재선언
    "err_enum_redeclare_type_mismatch": (r"enumeration redeclared with different underlying type '.+?' \(was '.+?'(?:\s*\(aka '.+?'\))?\)", "enumeration redeclared with different underlying type"),
    # 오버라이딩 함수의 예외 명세가 기본 버전보다 느슨함
    "err_override_exception_spec": (r"exception specification of overriding function is more lax than base version", "exception specification more lax than base version"),
    # 초기화 목록에 허용된 것보다 많은 요소가 포함됨
    "err_excess_initializers": (r"excess elements in (?:scalar|array|struct) initializer", "excess elements in initializer"),
    # 구문 기호/키워드 필요 (구체적인 패턴 먼저)
    "err_expected_lparen_after_type": (r"expected '\(' for function-style cast or type construction", "expected '(' for function-style cast or type construction"),
    "err_expected_class_name": (r"expected class name", "expected class name"),
    "err_expected_expression": (r"expected expression", "expected expression"),
    # 65: (r"expected namespace name", "expected namespace name"),
    "err_missing_param": (r"expected parameter declarator", "expected parameter declarator"),
    "err_expected_statement": (r"expected statement", "expected statement"),
    "err_expected_unqualified_id": (r"expected unqualified-id", "expected unqualified-id"),
    # 구문 기호 누락 (일반, 위의 구체적 패턴 이후에 위치)
    "Unknown_Parse#1": (r"expected .+", "expected punctuation or keyword"),
    # 명시적으로 기본 설정된 생성자/소멸자가 암묵적으로 삭제됨
    "warn_defaulted_comparison_deleted": (r"explicitly defaulted (?:default constructor|destructor) is implicitly deleted", "explicitly defaulted constructor or destructor is implicitly deleted"),
    # 할당 불가능한 표현식 또는 비객체 타입에 대한 할당 시도
    "err_no_subobject_property_setting": (r"(?:expression|non-object type '.+?'(?:\s*\(aka '.+?'\))?) is not assignable", "expression or non-object type is not assignable"),
    # 사용되지 않는 표현식 결과
    "warn_unused_expr": (r"expression result unused", "expression result unused"),
    # 불필요한 닫는 중괄호
    "err_extraneous_closing_brace": (r"extraneous closing brace \('}'\)", "extraneous closing brace"),
    # 필드가 사용될 때 초기화되지 않음
    "warn_field_is_uninit": (r"field '.+?' is uninitialized when used here", "field is uninitialized when used"),
    # 필드가 불완전한 타입
    "err_field_incomplete_or_sizeless": (r"field has incomplete type '.+?'", "field has incomplete type"),
    # 필드 타입의 기본 생성자/소멸자가 private/protected
    "err_access_field_ctor": (r"field of type '.+?' has (?:private|protected) (?:(?:default )?constructor|destructor)", "field of type has private or protected constructor or destructor"),
    # 필드 타입이 추상 클래스
    "err_abstract_type_in_decl#1": (r"field type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "field type is abstract class"),
    # 포맷 문자열이 문자열 리터럴이 아님
    "warn_format_nonliteral_noargs": (r"format string is not a string literal \(potentially insecure\)", "format string is not a string literal"),
    # 함수가 함수 타입을 반환할 수 없음
    "err_func_returning_array_function": (r"function cannot return function type '.+?'(?:\s*\(aka '.+?'\))?", "function cannot return function type"),
    # 반환 타입만 다른 함수 오버로드 불가
    "err_ovl_diff_return_type": (r"functions that differ only in their return type cannot be overloaded", "functions differ only in return type cannot be overloaded"),
    # 암묵적 기본 생성자가 기본 생성자 없는 멤버 명시적 초기화 필요
    "err_missing_default_ctor#2": (r"implicit default constructor for '.+?' must explicitly initialize the member '.+?' which does not have a default constructor", "implicit default constructor must explicitly initialize member without default constructor"),
    # 정의되지 않은 템플릿의 암묵적 인스턴스화
    "err_implicit_instantiate_member_undefined": (r"implicit instantiation of undefined template '.+?'", "implicit instantiation of undefined template"),
    # 호환되지 않는 포인터 타입 대입
    "err_typecheck_convert_incompatible_pointer": (r"incompatible pointer types assigning to '.+?'(?:\s*\(aka '.+?'\))? from '.+?'(?:\s*\(aka '.+?'\))?", "incompatible pointer types assigning"),
    # 타입의 불완전한 정의
    "err_typecheck_incomplete_tag": (r"incomplete definition of type '.+?'", "incomplete definition of type"),
    # 함수 정의/람다에서 불완전한 결과 타입
    "err_func_def_incomplete_result": (r"incomplete result type '.+?'(?:\s*\(aka '.+?'\))? in (?:function definition|lambda expression)", "incomplete result type in function definition or lambda expression"),
    # 중첩 이름 지정자에 불완전한 타입
    "err_incomplete_nested_name_spec": (r"incomplete type '.+?' named in nested name specifier", "incomplete type in nested name specifier"),
    # 포인터 피연산자가 필요한 간접 참조
    "err_typecheck_indirection_requires_pointer": (r"indirection requires pointer operand \('.+?'(?:\s*\(aka '.+?'\))? invalid\)", "indirection requires pointer operand"),
    # 불완전한 타입 초기화
    "err_init_incomplete_type": (r"initialization of incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "initialization of incomplete type"),
    # 선언 끝에 잘못된 '=='
    "err_invalid_token_after_declarator_suggest_equal": (r"invalid '==' at end of declaration; did you mean '='\?", "invalid '==' at end of declaration"),
    # 불완전한 타입에 alignas/sizeof 적용 불가
    "err_sizeof_alignof_incomplete_or_sizeless_type": (r"invalid application of '(?:alignas|sizeof)' to an incomplete type '.+?'", "invalid application of alignas or sizeof to incomplete type"),
    # 이항 표현식에 잘못된 피연산자
    "err_typecheck_invalid_operands": (r"invalid operands to binary expression \('.+?'(?:\s*\(aka '.+?'\))? and '.+?'(?:\s*\(aka '.+?'\))?\)", "invalid operands to binary expression"),
    # 잘못된 매개변수 이름 (키워드 사용)
    "err_keyword_as_parameter": (r"invalid parameter name: '.+?' is a keyword", "invalid parameter name is keyword"),
    # 상수에 잘못된 접미사
    "err_invalid_suffix_constant": (r"invalid suffix '.+?' on (?:floating|integer) constant", "invalid suffix on constant"),
    # 잘못된 유니버설 문자
    "err_ucn_escape_invalid": (r"invalid universal character", "invalid universal character"),
    # 불완전한 타입 사용
    "err_invalid_incomplete_type_use": (r"invalid use of incomplete type '.+?'", "invalid use of incomplete type"),
    # 비정적 멤버 함수 외부에서 this 사용
    "err_invalid_this_use": (r"invalid use of 'this' outside of a non-static member function", "invalid use of this outside non-static member function"),
    # enum 전방 선언 금지
    "err_forward_ref_enum": (r"ISO C\+\+ forbids forward references to 'enum' types", "ISO C++ forbids forward references to enum types"),
    # 불완전한 타입으로 멤버 접근
    "err_incomplete_member_access": (r"member access into incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "member access into incomplete type"),
    # 멤버 초기화자가 비정적 데이터 멤버 또는 기본 클래스를 가리키지 않음
    "err_mem_init_not_member_or_class": (r"member initializer '.+?' does not name a non-static data member or base class", "member initializer does not name non-static data member or base class"),
    # 멤버 참조 기본 타입이 구조체 또는 유니온이 아님
    "err_typecheck_member_reference_struct_union": (r"member reference base type '.+?'(?:\s*\(aka '.+?'\))? is not a structure or union", "member reference base type is not structure or union"),
    # 멤버 참조 시 포인터 여부에 맞지 않는 연산자를 사용하려 함
    "err_typecheck_member_reference_suggestion": (r"member reference type '.+?'(?:\s*\(aka '.+?'\))? is (?:not a pointer(?:; did you mean to use '\.')?|a pointer(?:; did you mean to use '->')?)\??", "member reference type wrong operator"),
    # 'defined' 뒤에 ')' 누락
    "err_pp_expected_after": (r"missing '\)' after 'defined'", "missing ')' after defined"),
    # 해당 타입을 참조할 때 올바른 태그 키워드를 사용해야 함
    "Unknown_Sema#1": (r"must use '(?:class|struct|union)' tag to refer to type '.+?'(?:\s*\(aka '.+?'\))? in this scope", "must use class or struct tag to refer to type"),
    # 네임스페이스는 전역 또는 네임스페이스 범위에서만 정의 가능
    "err_namespace_nonnamespace_scope": (r"namespaces can only be defined in global or namespace scope", "namespaces can only be defined in global or namespace scope"),
    # 네임스페이스에 해당 클래스 없음
    "err_not_tag_in_scope": (r"no class named '.+?' in namespace '.+?'", "no class named in namespace"),
    # 함수 템플릿 특수화에 매칭되는 함수 템플릿 없음
    "err_function_template_spec_no_match": (r"no function template matches function template specialization '.+?'", "no function template matches specialization"),
    # 초기화에 매칭되는 생성자 없음
    "err_ovl_no_viable_function_in_init": (r"no matching constructor for initialization of '.+?'(?:\s*\(aka '.+?'\))?", "no matching constructor for initialization"),
    # 함수 스타일 캐스트에 매칭되는 변환 없음
    "err_ovl_no_viable_conversion_in_cast": (r"no matching conversion for functional-style cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))?", "no matching conversion for functional-style cast"),
    # 매칭되는 함수/멤버 함수 없음
    "err_ovl_no_viable_object_call": (r"no matching (?:member )?function for call to (?:object of type )?'.+?'(?:\s*\(aka '.+?'\))?", "no matching function or member function for call"),
    # 매칭되는 리터럴 연산자 없음
    "err_ovl_no_viable_literal_operator": (r"no matching literal operator for call to '.+?' with argument(?:s)? of type(?:s)? '.+?'(?:\s*or\s*'.+?'|(?:\s*\(aka '.+?'\))?\s*and\s*'.+?')?, and no matching literal operator template", "no matching literal operator for call"),
    # 네임스페이스/클래스/전역에 해당 멤버 없음
    "err_no_member": (r"no member named '.+?' in (?:namespace '.+?'|'.+?'|the global namespace)(?:; did you mean .+?)?", "no member named in namespace or class"),
    # 네임스페이스/클래스/전역에 해당 타입/템플릿 없음 #err_typename_nested_not_found
    "err_no_template": (r"no (?:type|template) named '.+?'(?: in (?:namespace '.+?'|'.+?'|the global namespace))?(?:; did you mean (?:simply )?'.+?')?", "no type or template named in namespace or class"),
    # 템플릿 인수 추론을 위한 생성자 또는 추론 가이드 없음
    "err_deduced_class_template_ctor_no_viable": (r"no viable constructor or deduction guide for deduction of template arguments of '.+?'", "no viable constructor or deduction guide"),
    # 반환값 타입 변환 불가
    "err_typecheck_nonviable_condition": (r"no viable conversion from returned value of type '.+?'(?:\s*\(aka '.+?'\))? to function return type '.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion from returned value"),
    # 타입 변환 불가
    "err_typecheck_nonviable_condition_incomplete": (r"no viable conversion from '.+?'(?:\s*\(aka '.+?'\))? to (?:incomplete type )?'.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion"),
    # 오버로드된 '=' 연산자 없음
    "err_ovl_no_viable_oper": (r"no viable overloaded '.+?'", "no viable overloaded operator"),  # 해당 타입에 적합한 오버로드된 연산자가 없음
    # 오버로드된 [] 연산자 없음 #err_ovl_no_viable_oper
    "err_ovl_no_viable_subscript": (r"no viable overloaded operator\[\] for type '.+?'(?:\s*\(aka '.+?'\))?", "no viable overloaded operator[]"),
    # non-const lvalue 참조 바인딩 불가
    "err_lvalue_reference_bind_to_initlist": (r"non-const lvalue reference to type '.+?'(?:\s*\(aka '.+?'\))? cannot bind to (?:a value of unrelated type|a temporary of type|an initializer list temporary)(?:\s*'.+?'(?:\s*\(aka '.+?'\))?)?", "non-const lvalue reference cannot bind"),
    # 비친구 클래스 멤버에 한정된 이름 불가
    "err_member_qualification": (r"non-friend class member '.+?' cannot have a qualified name", "non-friend class member cannot have qualified name"),
    # 비가상 멤버 함수가 가상 멤버 함수를 숨김
    "override_keyword_hides_virtual_member_function": (r"non-virtual member function marked 'override' hides virtual member function(?:s)?", "non-virtual member function marked override hides virtual member function"),
    # 네임스페이스에 해당 네임스페이스 없음
    "err_using_directive_member_suggest": (r"no namespace named '.+?' in namespace '.+?'(?:; did you mean '.+?')?", "no namespace named in namespace"),
    # constexpr 함수에 return 문 없음
    "err_constexpr_body_no_return": (r"no return statement in constexpr function", "no return statement in constexpr function"),
    # 변수 템플릿 특수화에 매칭되는 변수 템플릿 없음
    "err_var_spec_no_template": (r"no variable template matches specialization", "no variable template matches specialization"),
    # 복사 대입 연산자가 암묵적으로 삭제되어 대입 불가
    "err_ovl_deleted_special_oper": (r"object of type '.+?'(?:\s*\(aka '.+?'\))? cannot be assigned because its copy assignment operator is implicitly deleted", "object cannot be assigned because copy assignment operator is implicitly deleted"),
    # 가상 멤버 함수만 override 표시 가능
    "override_keyword_only_allowed_on_virtual_member_functions": (r"only virtual member functions can be marked 'override'", "only virtual member functions can be marked override"),
    # out-of-line 정의가 클래스 내 선언과 불일치
    "err_member_decl_does_not_match": (r"out-of-line definition of '.+?' does not match any declaration in '.+?'", "out-of-line definition does not match any declaration"),
    # 오버로드 해결 시 삭제된 연산자 선택
    "err_ovl_deleted_oper": (r"overload resolution selected deleted operator '='", "overload resolution selected deleted operator"),
    # 유효하지 않은 전처리 토큰 생성
    "err_pp_bad_paste": (r"pasting formed '.+?', an invalid preprocessing token", "pasting formed invalid preprocessing token"),
    # 동일한 이름에 대해 서로 다른 타입으로 선언이 충돌함
    "err_redeclaration_different_type": (r"(?:redeclaration of '.+?' with a different type: '.+?' vs '.+?'|conflicting types for '.+?')", "redeclaration with different type or conflicting types"),
    # 재정의
    "err_redefinition": (r"redefinition of (?:default argument|parameter '.+?'|'.+?'(?:(?: as different kind of symbol)?)?)", "redefinition"),
    # 외부 람다 또는 함수에서 선언된 지역 변수를 참조하려 함
    "err_reference_to_local_in_enclosing_context": (r"reference to local variable '.+?' declared in enclosing (?:lambda expression|function '.+?')", "reference to local variable in enclosing lambda or function"),
    # 비정적 멤버 함수 참조는 호출되어야 함
    "err_bound_member_function": (r"reference to non-static member function must be called(?:; did you mean to call it with no arguments\?)?", "reference to non-static member function must be called"),
    # 오버로드된 함수 참조 해결 불가
    "err_ovl_unresolvable": (r"reference to overloaded function could not be resolved(?:; did you mean to call it\?)?", "reference to overloaded function could not be resolved"),
    # 타입 참조가 lvalue/rvalue에 바인딩 불가
    "err_reference_bind_failed": (r"reference to type '.+?'(?:\s*\(aka '.+?'\))? could not bind to (?:an lvalue|an rvalue) of type '.+?'(?:\s*\(aka '.+?'\))?", "reference to type could not bind"),
    # reinterpret_cast 또는 const_cast가 허용되지 않거나 qualifier를 제거함
    "err_bad_cxx_cast_generic": (r"(?:reinterpret_cast|const_cast) from (?:rvalue|'.+?'(?:\s*\(aka '.+?'\))?) to (?:reference type )?'.+?'(?:\s*\(aka '.+?'\))?(?:(?:, which are not related by inheritance,)? is not allowed| casts away qualifiers)?", "reinterpret_cast or const_cast is not allowed or casts away qualifiers"),
    # 람다 반환 타입 불일치
    "err_typecheck_missing_return_type_incompatible": (r"return type '.+?'(?:\s*\(aka '.+?'\))? must match previous return type '.+?'(?:\s*\(aka '.+?'\))? when lambda expression has unspecified explicit return type", "return type must match previous return type in lambda"),
    # 반환 타입이 추상 클래스
    "err_abstract_type_in_decl#2": (r"return type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "return type is abstract class"),
    # 가상 함수의 반환 타입이 공변적이지 않음
    "err_covariant_return_ambiguous_derived_to_base_conv": (r"return type of virtual function '.+?' is not covariant with the return type of the function it overrides", "return type of virtual function is not covariant"),
    # .* 연산자의 우측 피연산자가 멤버 포인터 타입이 아님
    "err_bad_memptr_rhs": (r"right hand operand to \.\* has non-pointer-to-member type '.+?'(?:\s*\(aka '.+?'\))?", "right hand operand to .* has non-pointer-to-member type"),
    # rvalue 참조가 lvalue에 바인딩 불가
    "err_lvalue_to_rvalue_ref": (r"rvalue reference to type '.+?' cannot bind to lvalue of type '.+?'", "rvalue reference cannot bind to lvalue"),
    # 모호한 참조
    "err_ambiguous_reference": (r"reference to '.+?' is ambiguous", "reference is ambiguous"),
    # 정적 어서션 표현식이 정수 상수 표현식이 아님
    "err_static_assert_expression_is_not_constant": (r"static assertion expression is not an integral constant expression", "static assertion expression is not integral constant expression"),
    # 정적 어서션 실패
    "err_static_assert_failed": (r"static assertion failed.*", "static assertion failed"),
    # 지역 구조체에 정적 데이터 멤버 불가
    "err_static_data_member_not_allowed_in_local_class": (r"static data member '.+?' not allowed in (?:local|anonymous) struct", "static data member not allowed in local or anonymous struct"),
    # static_cast가 허용되지 않거나 qualifier를 제거함
    "err_bad_cxx_cast_unrelated_class": (r"static_cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))?(?:(?:, which are not related by inheritance,)? is not allowed| casts away qualifiers)", "static_cast is not allowed or casts away qualifiers"),
    # 불완전한 타입 포인터 서브스크립트
    "err_subscript_incomplete_or_sizeless_type": (r"subscript of pointer to incomplete type '.+?'", "subscript of pointer to incomplete type"),
    # 서브스크립트 대상이 배열/포인터/벡터가 아님
    "err_typecheck_subscript_value": (r"subscripted value is not an array, pointer, or vector", "subscripted value is not array pointer or vector"),
    # 템플릿 타입 매개변수에 타입이 아닌 인자
    "err_template_arg_must_be_type": (r"template argument for template type parameter must be a type", "template argument must be a type"),
    # 템플릿 템플릿 매개변수에 클래스 템플릿 또는 타입 별칭 템플릿이 아닌 인자
    "err_template_arg_must_be_template": (r"template argument for template template parameter must be a class template or type alias template", "template argument for template template parameter must be class template or type alias template"),
    # 템플릿 특수화에 'template<>' 필요
    "err_template_spec_needs_header": (r"template specialization requires 'template<>'", "template specialization requires template<>"),
    # 템플릿 템플릿 인자의 템플릿 매개변수가 다름
    "err_template_arg_template_params_mismatch": (r"template template argument has different template parameters than its corresponding template template parameter", "template template argument has different template parameters"),
    # 지역 클래스 내부에 템플릿 선언 불가
    "err_template_inside_local_class": (r"templates cannot be declared inside of a local class", "templates cannot be declared inside local class"),
    # 함수 호출 인자 부족
    "err_typecheck_call_too_few_args": (r"too few arguments (?:provided to function-like macro invocation|to function call, expected \d+, have \d+(?:; did you mean '.+?')?)", "too few arguments"),
    # 템플릿 인자 부족
    "err_template_arg_list_different_arity": (r"too few template arguments for (?:alias template|class template) '.+?'", "too few template arguments"),
    # 함수형 매크로 인자 과다
    "err_too_many_args_in_macro_invoc": (r"too many arguments provided to function-like macro invocation", "too many arguments to function-like macro"),
    # 함수 호출 인자 과다
    "err_typecheck_call_too_many_args": (r"too many arguments to function call, expected .+?, have .+?", "too many arguments to function call"),
    # 직접/가상 기본 클래스가 아닌 타입
    "err_not_direct_base_or_virtual": (r"type '.+?' is not a direct or virtual base of '.+?'", "type is not direct or virtual base"),
    # 타입이 좁혀질 수 없음
    "warn_init_list_type_narrowing": (r"type '.+?' cannot be narrowed to '.+?'(?:\s*\(aka '.+?'\))? in initializer list", "type cannot be narrowed in initializer list"),
    # 타입이 서브스크립트 연산자를 제공하지 않음
    "err_ovl_no_oper": (r"type '.+?'(?:\s*\(aka '.+?'\))? does not provide a (?:subscript|call) operator", "type does not provide subscript or call operator"),
    # type alias 또는 typedef가 다른 타입으로 재정의됨
    "err_redefinition_different_typedef": (r"(?:type alias|typedef) redefinition with different types \('.+?'(?:\s*\(aka '.+?'\))? vs '.+?'(?:\s*\(aka '.+?'\))?\)", "type alias or typedef redefinition with different types") ,
    # 참조의 참조 타입 이름 선언
    "err_illegal_decl_reference_to_reference": (r"type name declared as a reference to a reference", "type name declared as reference to reference"),
    # 예상치 못한 문자
    "err_character_not_allowed": (r"unexpected character <.+?>", "unexpected character"),
    # 예상치 못한 네임스페이스 이름
    "err_unexpected_namespace": (r"unexpected namespace name '.+?': expected expression", "unexpected namespace name"),
    # 알 수 없는 클래스/타입/템플릿 이름
    "err_unknown_type_or_class_name_suggest": (r"unknown (?:class|type|template) name '.+?'(?:; did you mean '.+?')?", "unknown class or template name"),
    # 함수형 매크로 호출이 종료되지 않음
    "err_unterm_macro_invoc": (r"unterminated function-like macro invocation", "unterminated function-like macro invocation"),
    # 이전 선언과 일치하지 않는 태그 타입으로 OfType 사용
    "err_use_with_wrong_tag": (r"use of '.+?' with tag type that does not match previous declaration", "use of identifier with mismatched tag type"),
    # 클래스 템플릿에 템플릿 인자 필요
    "err_template_missing_args": (r"use of class template '.+?' requires template arguments(?:; argument deduction not allowed .+?)?", "use of class template requires template arguments"),
    # 오버로드된 연산자 사용이 모호함
    "err_ovl_ambiguous_oper_unary": (r"use of overloaded operator '.+?' is ambiguous \(with operand types '.+?'(?:\s*\(aka '.+?'\))? and '.+?'(?:\s*\(aka '.+?'\))?\)", "use of overloaded operator is ambiguous"),
    # 선언되지 않은 식별자 사용
    "err_undeclared_var_use": (r"use of undeclared identifier '.+?'(?:; did you mean '.+?')?", "use of undeclared identifier"),
    # 선언되지 않은 operator() 사용
    "err_undeclared_use": (r"use of undeclared 'operator\(\)'", "use of undeclared operator()"),
    # using 선언이 클래스 멤버를 참조할 수 없음
    "err_using_decl_can_not_refer_to_class_member": (r"using declaration cannot refer to (?:class member|a namespace)", "using declaration cannot refer to class member or namespace"),
    # using 선언이 클래스가 아닌 네임스페이스를 참조함
    "err_using_decl_nested_name_specifier_is_not_class": (r"using declaration in class refers into '.+?', which is not a class", "using declaration in class refers to non-class"),
    # bool로 문맥 변환 불가
    "err_typecheck_bool_condition": (r"value of type '.+?'(?:\s*\(aka '.+?'\))? is not contextually convertible to 'bool'", "value is not contextually convertible to bool"),
    # 캡처 기본값 없는 람다에서 암묵적 캡처 불가
    "err_lambda_impcap": (r"variable '.+?' cannot be implicitly captured in a lambda with no capture-default specified", "variable cannot be implicitly captured in lambda"),
    # auto 타입 변수의 호환되지 않는 초기화자
    "err_auto_var_deduction_failure": (r"variable '.+?' with type 'auto\s*\*?' has incompatible initializer of type '.+?'(?:\s*\(aka '.+?'\))?", "variable with auto type has incompatible initializer"),
    # auto 추론 타입 변수가 자신의 초기화자에 등장
    "err_auto_variable_cannot_appear_in_own_initializer": (r"variable '.+?' declared with deduced type 'auto' cannot appear in its own initializer", "variable with deduced auto type cannot appear in its own initializer"),
    # 불완전한 타입의 변수
    "err_typecheck_decl_incomplete_type": (r"variable has incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "variable has incomplete type"),
    # private/protected 소멸자를 가진 타입의 변수
    "err_access_dtor_var": (r"(?:variable|temporary) of type '.+?'(?:\s*\(aka '.+?'\))? has (?:private|protected) destructor", "variable or temporary of type has private or protected destructor"),
    # 변수 타입이 추상 클래스
    "err_abstract_type_in_decl#3": (r"variable type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "variable type is abstract class"),
    # 가상 함수의 반환 타입이 오버라이드하는 함수와 다름
    "err_different_return_type_for_overriding_virtual_function": (r"virtual function '.+?' has a different return type \('.+?'(?:\s*\(aka '.+?'\))?\) than the function it overrides \(which has return type '.+?'\)", "virtual function has different return type than overridden function"),
    # 가변 크기 객체 초기화 불가
    "err_variable_object_no_init": (r"variable-sized object may not be initialized", "variable-sized object may not be initialized"),
    # 파일을 찾을 수 없음
    "err_pp_file_not_found": (r"'.+?' file not found", "file not found"),
    # private/protected 멤버 접근
    "err_access": (r"'.+?' is a (?:private|protected) member of '.+?'", "private or protected member access"),
    # 불완전한 타입
    "err_bad_cast_incomplete": (r"'.+?' is an incomplete type", "incomplete type"),
    # const가 아닌 함수에 const 객체로 this 인자 전달
    "err_member_function_call_bad_cvr": (r"'this' argument to member function '.+?' has type '.+?'(?:\s*\(aka '.+?'\))?, but function is not marked const", "this argument to non-const member function"),
    # 함수 프로토타입에 auto 또는 decltype(auto)를 사용하려 함
    "err_auto_not_allowed": (r"'(?:auto|decltype\(auto\))' not allowed in function prototype", "auto or decltype(auto) not allowed in function prototype"),
    # const 한정자가 참조에 적용될 수 없음
    "err_invalid_reference_qualifier_application": (r"'const' qualifier may not be applied to a reference", "const qualifier may not be applied to reference"),
    # mutable이 함수에 적용될 수 없음
    "err_mutable_function": (r"'mutable' cannot be applied to functions", "mutable cannot be applied to functions"),
    # using namespace가 클래스 내부에서 허용되지 않음
    "err_using_namespace_in_class": (r"'using namespace' is not allowed in classes", "using namespace not allowed in classes"),
    # void가 첫 번째이자 유일한 매개변수여야 함
    "err_void_only_param": (r"'void' must be the first and only parameter if specified", "void must be first and only parameter"),
    # override가 표시됐지만 오버라이드하는 함수가 없음
    "err_function_marked_override_not_overriding": (r"'.+?' marked 'override' but does not override any member functions", "marked override but does not override any member functions"),
    # 값을 참조할 수 없는 식별자
    "err_ref_non_value": (r"'.+?' does not refer to a value", "does not refer to a value"),
    # gmock_xxx가 함수 배열로 선언됨
    "err_illegal_decl_array_of_functions": (r"'.+?' declared as array of functions of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as array of functions"),
    # va_start가 고정 인자 함수에서 사용됨
    "err_va_start_fixed_function": (r"'va_start' used in function with fixed args", "va_start used in function with fixed args"),
    # 클래스, 네임스페이스, 열거형이 아닌 식별자
    "err_expected_class_or_namespace": (r"'.+?'(?:\s*\(aka '.+?'\))? is not a class, namespace, or enumeration", "is not a class namespace or enumeration"),
    # 참조에 대한 포인터로 선언된 타입 이름
    "err_illegal_decl_pointer_to_reference": (r"'.+?' declared as a pointer to a reference of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as pointer to reference"),
    # 다형성이 아닌 타입
    "err_bad_dynamic_cast_not_polymorphic": (r"'.+?' is not polymorphic", "is not polymorphic"),
    # 단항 표현식에 잘못된 인자 타입
    "err_typecheck_unary_expr": (r"invalid argument type '.+?'(?:\s*\(aka '.+?'\))? to unary expression", "invalid argument type to unary expression"),
    # 포인터를 더 작은 타입으로 캐스트 시 정보 손실
    "err_bad_reinterpret_cast_small_int": (r"cast from pointer to smaller type '.+?'(?:\s*\(aka '.+?'\))? loses information", "cast from pointer to smaller type loses information"),
    # 비멤버 함수에 const 한정자 불가
    "err_invalid_qualified_function_type": (r"non-member function cannot have 'const' qualifier", "non-member function cannot have const qualifier"),
    # mutable은 멤버 변수에만 적용 가능
    "err_mutable_nonmember": (r"'mutable' can only be applied to member variables", "mutable can only be applied to member variables"),
    # 함수 호출 인자 누락
    "err_typecheck_call_too_few_args_one": (r"too few arguments to function call, (?:single|at least) argument '.+?' (?:was not|must be) specified", "too few arguments to function call single argument not specified"),
    # 선언의 언어 링키지가 다름
    "err_different_language_linkage": (r"declaration of '.+?' has a different language linkage", "declaration has different language linkage"),
    # 기본 인자는 함수 선언의 매개변수에만 지정 가능
    "err_param_default_argument_nonfunc": (r"default arguments can only be specified for parameters in a function declaration", "default arguments only for parameters in function declaration"),

    # 함수형 캐스트 시도 시 삭제된 함수(생성자 등)가 호출됨
    "err_ovl_deleted_conversion_in_cast": (r"functional-style cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?' uses deleted function", "functional-style cast uses deleted function"),
    # 타입 변환 시 삭제된 변환 함수가 호출됨
    "err_typecheck_deleted_function": (r"conversion function from '.+?'(?:\s*\(aka '.+?'\))? to '.+?' invokes a deleted function", "conversion function invokes deleted function"),
    # 레퍼런스 변수 또는 추론된 타입의 변수 선언 시 초기화가 누락됨
    "err_reference_var_requires_init": (r"declaration of (?:reference variable '.+?'|variable '.+?' with deduced type '.+?') requires an initializer", "declaration of variable requires an initializer"),
    # 생성자, 소멸자, 또는 변환 함수에 반환 타입이 잘못 지정됨
    "err_destructor_return_type": (r"(?:constructor|destructor|conversion function) cannot have a return type", "constructor or destructor or conversion function cannot have a return type"),
    # using 선언이 베이스 클래스가 아닌 타입을 참조함
    "err_using_decl_nested_name_specifier_is_not_base_class": (r"using declaration refers into '.+?', which is not a base class of '.+?'", "using declaration refers into non-base class"),
#######################
    # 임시 객체의 주소를 취하려 함 Pointer/Reference Misuse
    "err_typecheck_addrof_temporary": (r"taking the address of a temporary object of type '.+?'(?:\s*\(aka '.+?'\))?", "taking address of temporary object"),  
    # 비타입 템플릿 파라미터에 표현식이 아닌 값이 전달됨 Templates/Generics
    "err_template_arg_must_be_expr": (r"template argument for non-type template parameter must be an expression", "template argument for non-type template parameter must be an expression"),  
    # 중첩 타입에서 외부 클래스의 non-static 멤버를 참조함 This/Non-Static Member/Using Misuse
    "err_nested_non_static_member_use": (r"use of non-static data member '.+?' of '.+?' from nested type '.+?'", "use of non-static data member from nested type"),  

    # 명시적 인스턴스화가 올바른 네임스페이스 안에 없음 Templates/Generics
    "err_explicit_instantiation_unqualified_wrong_namespace": (r"explicit instantiation of '.+?' must occur in namespace '.+?'", "explicit instantiation must occur in enclosing namespace"),  
    # 명시적 인스턴스화 대상이 유효한 템플릿 요소가 아님 Templates/Generics
    "err_explicit_instantiation_not_known": (r"explicit instantiation of '.+?' does not refer to a function template, variable template, member function, member class, or static data member", "explicit instantiation does not refer to valid template target"),  
    # 템플릿이 아닌 타입에 대해 명시적 특수화를 시도함 Templates/Generics
    "Unknown_Sema#2": (r"explicit specialization of non-template (?:struct|class|union) '.+?'", "explicit specialization of non-template type"),  

    # static 선언이 이전의 non-static 선언과 충돌함 Type Redefinition/Redeclaration
    "err_static_non_static": (r"static declaration of '.+?' follows non-static declaration", "static declaration follows non-static declaration"),  
    # 추상 클래스 타입의 배열을 선언하려 함 Abstract-Type Instantiation
    "err_array_of_abstract_type": (r"array of abstract class type '.+?'", "array of abstract class type"),  
    # 해당 타입이 대상 타입으로 암묵적 변환이 불가능함 Type Conversion & Reference Binding 
    "err_typecheck_converted_constant_expression": (r"value of type '.+?'(?:\s*\(aka '.+?'\))? is not implicitly convertible to '.+?'(?:\s*\(aka '.+?'\))?", "value of type is not implicitly convertible"),  
    # 서로 다른 포인터 타입 간의 비교 시도 Type Conversion & Reference Binding 
    "err_typecheck_comparison_of_distinct_pointers": (r"comparison of distinct pointer types \('.+?'(?:\s*\(aka '.+?'\))? and '.+?'(?:\s*\(aka '.+?'\))?\)", "comparison of distinct pointer types"),  
    # 범위 기반 for문에서 iterate 불가능한 타입을 범위로 사용하려 함 Operator/Call
    "err_for_range_deduction_failure": (r"cannot use type '.+?'(?:\s*\(aka '.+?'\))? as a range", "cannot use type as a range"),  
    # 타입 멤버에 화살표 또는 점 연산자로 잘못 접근하려 함 This/Non-Static Member/Using Misuse
    "err_typecheck_member_reference_type": (r"cannot (?:refer to type member '.+?' in '.+?'(?:\s*\(aka '.+?'\))? with '(?:->|\.)'|use (?:arrow|dot) operator on a type)", "cannot use arrow or dot operator on type member"),  
    # lvalue 객체에서 rvalue ref-qualifier가 있는 멤버 함수를 호출하려 함 This/Non-Static Member/Using Misuse
    "err_member_function_call_bad_ref": (r"'this' argument to member function '.+?' is an lvalue, but function has rvalue ref-qualifier", "this argument is lvalue but function has rvalue ref-qualifier"),  
    # 캡처 기본값 없이 this를 암묵적으로 캡처하려 함 This/Non-Static Member/Using Misuse 
    "err_this_capture": (r"'this' cannot be implicitly captured in this context", "this cannot be implicitly captured in this context"),  
    # 멤버 함수에 대한 non-constant 포인터를 생성하려 함 Pointer/Reference Misuse
    "err_invalid_form_pointer_member_function": (r"cannot create a non-constant pointer to member function", "cannot create non-constant pointer to member function"),  
    # 감소 연산이 불가능한 타입에 대해 decrement 연산자를 사용하려 함 Operator/Call 
    "err_typecheck_illegal_increment_decrement": (r"cannot decrement value of type '.+?'(?:\s*\(aka '.+?'\))?", "cannot decrement value of type"),  

    # 유효하지 않은 전처리 지시문이 사용됨 Lexical
    "err_pp_invalid_directive": (r"invalid preprocessing directive", "invalid preprocessing directive"),  
    # 범위 기반 for문에서 begin() 함수가 없는 타입을 범위로 사용하려 함 Operator/Call
    "err_for_range_invalid": (r"invalid range expression of type '.+?'(?:\s*\(aka '.+?'\))?; no viable 'begin' function available", "invalid range expression type no viable begin function"),  
    # 리터럴과 식별자 사이에 공백이 없어 잘못된 suffix로 인식됨 Lexical 
    "ext_reserved_user_defined_literal": (r"invalid suffix on literal; C\+\+11 requires a space between literal and identifier", "invalid suffix on literal requires space"),  
    # non-static 데이터 멤버를 유효하지 않은 문맥에서 사용하려 함  This/Non-Static Member/Using Misuse
    "err_invalid_non_static_member_use": (r"invalid use of non-static data member '.+?'", "invalid use of non-static data member"),  
    # 직접 베이스 클래스가 아닌 클래스에서 생성자를 상속하려 함 Override/Inheritance
    "err_using_decl_constructor_not_in_direct_base": (r"'.+?' is not a direct base of '.+?', cannot inherit constructors", "is not a direct base cannot inherit constructors"), 
    # 함수 인자로 불완전한 타입을 전달하려 함 Incomplete Type 
    "err_call_incomplete_argument": (r"argument type '.+?'(?:\s*\(aka '.+?'\))? is incomplete", "argument type is incomplete"),  
    # 클래스 템플릿 특수화가 전역 스코프에 없음 Templates/Generics 
    "err_template_spec_redecl_global_scope": (r"class template specialization of '.+?' must occur at global scope", "class template specialization must occur at global scope"),  

    # non-static 데이터 멤버를 템플릿으로 선언하려 함 Templates/Generics 
    "err_template_member": (r"non-static data member '.+?' cannot be declared as a template", "non-static data member cannot be declared as a template"),  
    # 함수 파라미터 팩의 타입에 전개되지 않은 파라미터 팩이 없음 Templates/Generics 
    "err_function_parameter_pack_without_parameter_packs": (r"type '.+?'(?:\s*\(aka '.+?'\))? of function parameter pack does not contain any unexpanded parameter packs", "type of function parameter pack does not contain unexpanded parameter packs"),  
    # type-id 문맥에서 이름을 지정하려 함 Syntactic
    "err_unexpected_unqualified_id": (r"type-id cannot have a name", "type-id cannot have a name"),
    # using 선언이 자기 자신의 클래스를 참조하려 함 This/Non-Static Member/Using Misuse 
    "err_using_decl_nested_name_specifier_is_current_class": (r"using declaration refers to its own class", "using declaration refers to its own class"),  
    # catch-all 핸들러가 마지막에 위치하지 않음 Functions/Calls Resolution
    "err_early_catch_all": (r"catch-all handler must come last", "catch-all handler must come last"),  
    # 복사 초기화 문맥에서 explicit 생성자가 선택됨 Construction/Initialization 
    "err_selected_explicit_constructor": (r"chosen constructor is explicit in copy-initialization", "chosen constructor is explicit in copy-initialization"),  
    # 베이스 클래스에서 상속된 생성자가 암묵적으로 삭제됨 Construction/Initialization 
    "err_deleted_inherited_ctor_use": (r"constructor inherited by '.+?' from base class '.+?' is implicitly deleted", "inherited constructor is implicitly deleted"),  
    # 템플릿 인자에 auto를 사용하려 함 Templates/Generics
    "Unknown_Sema#3": (r"'auto' not allowed in template argument", "auto not allowed in template argument"), 
    # operator()를 파라미터 이름으로 사용하려 함 Syntactic
    "err_bad_parameter_name": (r"'operator\(\)' cannot be the name of a parameter", "operator() cannot be the name of a parameter"),  
    # 클래스 정의 외부에서 override 지정자를 사용하려 함 Syntactic
    "err_virt_specifier_outside_class": (r"'override' specifier is not allowed outside a class definition", "override specifier is not allowed outside a class definition"),  
    # 템플릿이 아닌 이름 뒤에 템플릿 인자가 사용됨 Templates/Generics 
    "err_non_template_in_template_id": (r"'.+?' does not name a template but is followed by template arguments", "identifier does not name a template but is followed by template arguments"),  
    # 허용되지 않는 문맥에서 template 키워드를 사용하려 함 Syntactic
    "err_unexpected_template_in_unqualified_id": (r"'template' keyword not permitted here", "template keyword not permitted here"),  
    # void 타입에 대한 멤버 포인터를 선언하려 함 Pointer/Reference Misuse
    "err_illegal_decl_mempointer_to_void": (r"'.+?' declared as a member pointer to void", "declared as member pointer to void"),  
    # 생성자가 아닌 함수에서 베이스 클래스 초기화를 시도함 Construction/Initialization 
    "err_only_constructors_take_base_inits": (r"only constructors take base initializers", "only constructors take base initializers"),  
    # raw string 리터럴의 종료 구분자가 없음 Lexical
    "err_unterminated_raw_string": (r'raw string missing terminating delimiter \).*?"', "raw string missing terminating delimiter"),  
    # 추론된 반환 타입을 가진 함수가 정의되기 전에 사용됨 Incomplete Type
    "err_auto_fn_used_before_defined": (r"function '.+?' with deduced return type cannot be used before it is defined", "function with deduced return type cannot be used before it is defined"),  
    # 블록 스코프에서 선언된 함수에 static 저장 클래스를 지정하려 함 Qualifier/Specifier Misuse 
    "err_static_block_func": (r"function declared in block scope cannot have 'static' storage class", "function declared in block scope cannot have static storage class"),  
    # 허용되지 않는 문맥에서 함수를 정의하려 함 Syntactic
    "err_function_definition_not_allowed": (r"function definition is not allowed here", "function definition is not allowed here"),  
    # 멤버 함수의 주소를 취할 때 명시적으로 이름을 한정해야 함 This/Non-Static Member/Using Misuse
    "err_unqualified_pointer_member_function": (r"must explicitly qualify name of member function when taking its address", "must explicitly qualify name of member function when taking its address"),  
    # 정수 타입을 포인터 타입으로 암묵적 변환하여 할당하려 함 Type Conversion & Reference Binding
    "err_typecheck_convert_int_pointer": (r"incompatible integer to pointer conversion assigning to '.+?'(?:\s*\(aka '.+?'\))? from '.+?'(?:\s*\(aka '.+?'\))?", "incompatible integer to pointer conversion assigning"),  
    # 연산자의 우측 피연산자로 initializer list를 사용하려 함 Syntactic
    "err_init_list_bin_op": (r"initializer list cannot be used on the right hand side of operator '.+?'", "initializer list cannot be used on right hand side of operator"),  
    # char 배열 초기화 문자열이 배열 크기보다 큼 Construction/Initialization 
    "err_initializer_string_for_char_array_too_long": (r"initializer-string for char array is too long, array size is \d+ but initializer has size \d+ \(including the null terminating character\)", "initializer string for char array is too long"),  
    # static_assert 선언을 템플릿으로 사용하려 함 Syntactic
    "err_templated_invalid_declaration": (r"a static_assert declaration cannot be a template", "static_assert declaration cannot be a template"),  
    # 오버로드된 함수의 주소가 요구되는 타입과 일치하지 않음 Symbol/Lookup
    "err_addr_ovl_no_viable": (r"address of overloaded function '.+?' does not match required type '.+?'(?:\s*\(aka '.+?'\))?", "address of overloaded function does not match required type"),  
    # 배열 첨자로 정수가 아닌 타입을 사용하려 함 Operator/Call 
    "err_typecheck_subscript_not_integer": (r"array subscript is not an integer", "array subscript is not an integer"),  
    # plain char 타입과 다른 정수 타입 간의 포인터 변환으로 할당하려 함 Type Conversion & Reference Binding 
    "ext_typecheck_convert_incompatible_pointer_sign": (r"assigning to '.+?'(?:\s*\(aka '.+?'\))? from '.+?'(?:\s*\(aka '.+?'\))? converts between pointers to integer types where one is of the unique plain 'char' type and the other is not", "assigning converts between pointers to integer types with plain char"),  
    # 팩 확장에 전개되지 않은 파라미터 팩이 없음 Templates/Generics 
    "err_pack_expansion_without_parameter_packs": (r"pack expansion does not contain any unexpanded parameter packs", "pack expansion does not contain any unexpanded parameter packs"),  
    # 함수 파라미터 타입으로 추상 클래스를 사용하려 함 Abstract-Type Instantiation 
    "err_abstract_type_in_decl#4": (r"parameter type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "parameter type is an abstract class"),  
    # 이전에 unscoped로 선언된 열거형을 scoped로 재선언하려 함 Type Redefinition/Redeclaration 
    "err_enum_redeclare_scoped_mismatch": (r"enumeration previously declared as unscoped", "enumeration previously declared as unscoped"),  
    # 표현식, static_assert, 또는 선언 타입에 전개되지 않은 파라미터 팩이 포함됨 Templates/Generics 
    "err_unexpanded_parameter_pack": (r"(?:static assertion|expression|declaration type) contains unexpanded parameter pack '.+?'", "contains unexpanded parameter pack"),  
    # 세미콜론 앞에 불필요한 닫는 괄호가 있음 Syntactic
    "err_extraneous_token_before_semi": (r"extraneous '\)' before ';'", "extraneous ) before ;"), 
    # 선언이 스코프 내 using 선언의 대상과 충돌함 Type Redefinition/Redeclaration 
    "err_using_decl_conflict_reverse": (r"declaration conflicts with target of using declaration already in scope", "declaration conflicts with target of using declaration already in scope"), 
    # 16진수 이스케이프 시퀀스가 유효 범위를 벗어남 Lexical
    "err_escape_too_large": (r"hex escape sequence out of range", "hex escape sequence out of range"),  
    # 한정된 참조가 타입이 아닌 생성자 이름으로 해석됨 Symbol/Lookup
    "err_out_of_line_qualified_id_type_names_constructor": (r"qualified reference to '.+?' is a constructor name rather than a type in this context", "qualified reference is a constructor name rather than a type"),  

    # reinterpret_cast로 오버로드된 함수를 특정 타입으로 해석할 수 없음  Type Conversion & Reference Binding
    "err_bad_reinterpret_cast_overload": (r"reinterpret_cast cannot resolve overloaded function '.+?' to type '.+?'(?:\s*\(aka '.+?'\))?", "reinterpret_cast cannot resolve overloaded function"),  
    # 함수에 필요한 예외 명세가 누락됨 Override/Inheritance
    "err_missing_exception_specification": (r"'.+?' is missing exception specification '(?:throw|noexcept)\([^)]*\)'", "missing exception specification"),  

    "err_undefined_symbol": (r"undefined reference to symbol:?\s*.+?", "undefined symbol"),
    "err_undefined_reference": (r"undefined reference to `.+?'", "undefined reference"),
    "err_multiple_definition": (r"multiple definition of `.+?'", "multiple definition"),
    "err_cannot_find_library": (r"cannot find -l.+", "cannot find library"),
}

CATEGORIE_DESCRIPTIONS = { # Lexical = 11, Syntactic = 17, Linker = 4, Semantic = 175 => 207
    "Lexical": {"description": "잘못된 문자, 매크로 인자 오류, 헤더 파일 누락 등 전처리 또는 토크나이징 단계에서 발생하는 오류",
                "solution": "잘못된 문자나 토큰을 수정하거나, 매크로 인자 개수를 맞추거나, 누락된 헤더 파일을 include를 고려"},
    "Syntactic": {"description": "괄호, 세미콜론, 키워드 등 문법 요소의 누락 또는 잘못된 위치로 인해 발생하는 오류",
                "solution": "누락된 문법 요소를 추가하거나, 잘못된 위치의 문법 요소를 올바른 위치로 수정을 고려"},
    "Linker": {"description": "정의 심볼, 중복 정의, 라이브러리 누락 등 링킹 단계에서 발생하는 오류",
                "solution": "누락된 심볼의 정의를 추가하거나, 중복 정의를 제거하거나, 필요한 라이브러리를 링크 대상에 추가를 고려"},
    # subtype = 16
    "Semantic": { 
        "description": "문법적으로는 올바르나 언어의 타입 시스템, 이름 조회, 접근 제어, 초기화 규칙 등 의미론적 제약을 위반하여 발생하는 오류",
        "solution": "",
        "subtypes":{
            "Abstract-Type Instantiation": {"description": "순수 가상 함수(pure virtual functions)가 구현되지 않은 추상 클래스를 직접 인스턴스화, 리턴 또는 할당을 시도",
                    "solution": "해당 추상 클래스를 상속한 Mock/Fake 클래스에서 모든 순수 가상 함수가 구현되어 있는지 확인하거나, 추상 클래스를 집적 사용하는 코드를 구체 클래스로 교체를 고려"},
            "Access Control": {"description": "현재 스코프에서 접근할 수 없는 private or protected 멤버, 생성자, 또는 소멸자에 접근을 시도",
                    "solution": "Public 인터페이스를 통해 접근하거나, 테스트용 접근 방식(friend 선언, getter 추가 등)을 고려"},
            "Constexpr/Enum/Assert/Literal": {"description": "constexpr 제약 위반, enum 전방 선언, static_assert 실패, 또는 리터럴 suffix 오용",
                    "solution": "constexpr 문맥에서 상수 표현식으로 수정, enum 정의 헤더 include, static_assert 조건의 타입/값 로직 확인 또는 literal suffix 확인을 고려"},
            "Construction/Initialization": {"description": "유효한 생성자 호출에 실패했거나, 멤버/베이스 클래스의 초기화 규칙을 위반",
                    "solution": "생성자의 인자 타입/개수를 확인하고 일치시키거나, 누락된 기본 생성자 또는 멤버 초기화 추가를 고려"},
            "Deleted/Special Member": {"description": "삭제되었거나 암묵적으로(implicitly) 삭제된 함수, 연산자 또는 특수 멤버를 호출하려 시도",
                    "solution": "삭제된 함수를 호출하는 코드를 제거하거나, 복사나 이동 대신 참조 등 다른 방식으로 객체 전달을 고려"},
            "Functions/Call Resolution": {"description": "오버로드 충돌 또는 호출 대상 부재로 함수 호출이 모호하거나 해석 불가능",
                    "solution": "명시적 캐스트나 타입 지정으로 오버로드 후보를 좁히거나, 인자 타입을 호출 대상 시그니처에 맞게 수정을 고려"},
            "Operator/Call": {"description": "호환되지 않는 피연산자 타입이나 연산자 정의 누락으로 연산자 또는 호출 표현식 사용 실패",
                    "solution": "피연산자 타입을 확인하고 호환되는 타입으로 수정하거나, 사용하는 연산자가 해당 타입에 정의되어 있는지 확인을 고려"},
            "Override/Inheritance": {"description": "Mock 또는 서브 클래스에서 override 시그니처, 반환 타입, 또는 상속 관계가 잘못 정의",
                    "solution": "베이스 클래스의 가상 함수 시그니처와 반환 타입을 확인하고 Mock 클래스의 override 선언 일치를 고려"},
            "Incomplete Type": {"description": "사용 시점에 완전히 정의되지 않은 타입의 사용 시도",
                    "solution": "해당 타입의 정의가 포함된 헤더를 include 하거나, 전방 선언을 완전한 정의로 교체를 고려"},
            "Symbol/Lookup": {"description": "현재 스코프에서 해석할 수 없는 식별자, 멤버, 네임스페이스 또는 타입을 참조하려 시도",
                    "solution": "오타 여부를 확인하고, 필요한 네임스페이스를 명시하거나, 참조하는 심볼이 실제로 존재하는지 확인을 고려"},
            "Templates/Generics": {"description": "템플릿 인자, 특수화 또는 인스턴스화를 컴파일러가 해석할 수 없는 방식으로 사용",
                    "solution": "템플릿 인자를 명시적으로 지정하거나, 특수화 문법 수정 및 템플릿 정의 헤더 include 확인을 고려"},
            "Type Conversion/Reference Binding": {"description": "유효하지 않은 암묵적/명시적 타입 변환을 수행하거나, 호환되지 않는 값(value)에 레퍼런스를 바인딩 시도",
                    "solution": "명시적 캐스트를 추가하거나, 인자/변수 타입을 대상 타입에 맞게 수정하거나, 레퍼런스 바인딩 대상의 타입과 수명 확인을 고려"},
            "Type Redefinition/Redeclaration": {"description": "기존 타입, 별칭, 또는 심볼과 충돌하는 재정의 또는 재선언 시도",
                    "solution": "중복 선언을 제거하거나, 헤더 가드 또는 include 순서를 확인하고, 시그니처가 기존 선언과 일치하는지 확인을 고려"},
            "Qualifier/Specifier Missuse": {"description": "const, mutable, auto, void 등의 한정자 또는 지정자를 허용되지 않는 문맥에서 오용",
                    "solution": "해당 한정자/지정자의 사용 문맥이 언어 규칙에 맞는지 확인하고, 잘못 적용된 위치에서 제거하거나 올바른 문맥으로 이동을 고려"},
            "Pointer/Reference Rules": {"description": "rvalue의 주소 취득, 레퍼런스에 대한 포인터 형성 등 포인터/레퍼런스 관련 규칙을 위반",
                    "solution": "포인터/레퍼런스 형성 규칙을 확인하고, rvalue 대신 lvalue를 사용하거나 불필요한 간접 참조의 제거를 고려"},
            "Member Access Rules": {"description": "this, non-static 멤버 참조 또는 using 선언을 유효하지 않은 문맥에서 잘못 사용함",
                    "solution": "this 사용 문맥이 non-static 멤버 함수 내인지 확인하고, non-static 멤버는 객체를 통해 접근하도록 수정하거나, using 선언의 대상이 유효한지 확인을 고려"},
        }
    },
}

categories_pattern_sum = 0
for key in CATEGORIES.keys():
    if key != "Semantic":
        pattern_list = CATEGORIES.get(key)
        # print(key, ': ', len(pattern_list))
        categories_pattern_sum = categories_pattern_sum + len(pattern_list)
        for pattern in pattern_list:
            if pattern in PATTERNS.keys():
                continue
            else:
                print(pattern)
    else:
        subtypes = CATEGORIES.get(key)
        for subtype in subtypes.keys():
            pattern_list = subtypes.get(subtype)
            # print(subtype, ': ', len(pattern_list))
            categories_pattern_sum = categories_pattern_sum + len(pattern_list)
            for pattern in pattern_list:
                if pattern in PATTERNS.keys():
                    continue
                else:
                    print(pattern)

print(len(PATTERNS) == categories_pattern_sum)

for pattern in PATTERNS.keys():
    if pattern in CATEGORIES["Lexical"] or pattern in CATEGORIES["Linker"] or pattern in CATEGORIES["Syntactic"]:
        continue
    else:
        is_in = False
        for k, v in CATEGORIES["Semantic"].items():
            if pattern in v:
                is_in = True
                break
        if not is_in:
            print(pattern)

for key in CATEGORIES.keys():
    if key != "Semantic":
        description, solution = CATEGORIE_DESCRIPTIONS.get(key).items()
        print(f"{key}: {description}")
        print(f"solution: {solution}\n")
    else:
        escription, solution, _ = CATEGORIE_DESCRIPTIONS.get(key).items()
        print(f"{key}: {description}")
        print(f"solution: {solution}\n")
        subtypes = CATEGORIE_DESCRIPTIONS.get(key).get("subtypes")
        for subtype in subtypes.keys():
            description, solution = subtypes.get(subtype).items()
            print(f"{subtype}: {description}")
            print(f"solution: {solution}\n")

total = 0
total_semantic = 0
for key in CATEGORIES.keys():
    if key != "Semantic":
        value = CATEGORIES.get(key)
        print(f"{key}: {len(value)}")
        total += len(value)
    else:
        subtypes = CATEGORIES.get(key)
        for subtype in subtypes:
            print(f"{subtype}: {len(subtypes.get(subtype))}")
            total_semantic += len(subtypes.get(subtype))
print("Semantic: ", total_semantic)
print("Total: ", total+total_semantic)