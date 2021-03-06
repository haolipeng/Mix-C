#ifndef xpack_meta_is_number
#define xpack_meta_is_number
    #pragma push_macro("xuser")
    #undef  xuser
    #define xuser mixc::meta_is_number
    #include"define/base_type.hpp"
    #include"is_integer.hpp"
    #include"is_float.hpp"
    #include"is_enum.hpp"

    namespace xuser{
        template<class a> struct meta {
            static constexpr bool result = inc::is_integer<a> || inc::is_float<a> || inc::is_enum<a>;
        };

        template<class a>
        constexpr bool is_number = meta<a>::result;
    }

    #pragma pop_macro("xuser")
#endif

namespace xuser::inc{
    using ::mixc::meta_is_number::is_number;
}
