#ifndef xusing_lang_cxx
    #include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_is_starts_with
#define xpack_lang_cxx_is_starts_with
    #pragma push_macro("xuser")
    #pragma push_macro("xusing_lang_cxx")
        #undef  xusing_lang_cxx
        #undef  xuser
        #define xuser mixc::lang_cxx_is_starts_with
        #include"define/base_type.hpp"
        #include"interface/can_compare.hpp"
        #include"lang/cxx/compare_fastly.hpp"
        #include"lang/cxx.hpp"
    #pragma pop_macro("xusing_lang_cxx")
    #pragma pop_macro("xuser")

    namespace mixc::lang_cxx_is_starts_with{
        // using item = char;
        // template<class item> struct core;
        // template<>
        // struct core<item> : inc::cxx<item> {

        template<class item>
        struct core : inc::cxx<item> {
            using inc::cxx<item>::cxx;
            using the_t = core<item>;

            bool is_starts_with(the_t value, inc::can_compare<item> compare) const {
                if (the.length() < value.length() or value.length() == 0){
                    return false;
                }
                return the_t(the)
                    .length(value.length())
                    .compare_fastly(value) == 0;
            }
        };
    }
#endif

namespace mixc::lang_cxx_is_starts_with::xuser{
    template<class final, class item>
    struct cxx : xusing_lang_cxx::cxx<final, item> {
        using xusing_lang_cxx::cxx<final, item>::cxx;
        using the_t = mixc::lang_cxx_is_starts_with::core<item>;

        bool is_starts_with(
            fianl                  value, 
            inc::can_compare<item> compare = inc::default_compare<item>) const {
            return the.is_starts_with(value, compare);
        }

        final & is_starts_with(
            final                  value, 
            bool                 * receive,
            inc::can_compare<item> compare = inc::default_compare<item>) const {
            receive[0] = the.is_starts_with(value, compare);
            return thex;
        }
    };
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_is_starts_with::xuser