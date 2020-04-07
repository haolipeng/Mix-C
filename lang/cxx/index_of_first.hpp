#ifndef xusing_lang_cxx
    #include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_index_of_first
#define xpack_lang_cxx_index_of_first
    #pragma push_macro("xuser")
    #pragma push_macro("xusing_lang_cxx")
        #undef  xusing_lang_cxx
        #undef  xuser
        #define xuser mixc::lang_cxx_index_of_first
        #include"define/base_type.hpp"
        #include"interface/can_callback.hpp"
        #include"interface/can_compare.hpp"
        #include"lang/cxx.hpp"
    #pragma pop_macro("xusing_lang_cxx")
    #pragma pop_macro("xuser")

    namespace mixc::lang_cxx_index_of_first{
        // using item = char;
        // template<class item> struct core;
        // template<>
        // struct core<item> : inc::cxx<item> {

        template<class item>
        struct core : inc::cxx<item> {
            using inc::cxx<item>::cxx;
            using the_t = core<item>;

            uxx index_of_first(item value, inc::can_compare<item> compare) const {
                for (uxx i = 0; i < the.length(); i++){
                    if (compare(the[i], value) == 0){
                        return i;
                    }
                }
                return not_exist;
            }

            template<class compare_invoke>
            uxx index_of_first(
                the_t                  value,
                compare_invoke const & compare) const {

                the_t origin = the;
                uxx  miss   = 0;
                uxx  index;

                if (origin.length() < value.length() or value.length() == 0) {
                    return not_exist;
                }
                while(true){
                    if (index = origin.index_of_first(value[miss], compare); index == not_exist){
                        break;
                    }
                    if (origin = origin.backward(index - miss); origin.length() < value.length()) {
                        break;
                    }
                    for (index = 0; ; index++){
                        if (index == value.length()) {
                            return uxx(origin - the);
                        }
                        if (compare(origin[index], value[index]) != 0) {
                            miss = index;
                            break;
                        }
                    }
                }
                return not_exist;
            }

            void index_of_first(
                the_t                              value, 
                inc::can_callback<void(uxx index)> match,
                inc::can_compare<item>             compare) const {

                for(auto cur = the;;){
                    if (uxx i = cur.index_of_first(value, compare); i == not_exist){
                        return;
                    }
                    else{
                        cur = cur.backward(i + value.length());
                        match(i);
                    }
                }
            }
        };
    }
#endif

namespace mixc::lang_cxx_index_of_first::xuser {
    template<class final, class item>
    struct cxx : xusing_lang_cxx::cxx<final, item> {
        using xusing_lang_cxx::cxx<final, item>::cxx;
        using the_t = core<item>;

        uxx index_of_first(
            item                   value, 
            inc::can_compare<item> compare = inc::default_compare<item>) const {
            return the.index_of_first(value, compare);
        }

        uxx index_of_first(
            final                  value, 
            inc::can_compare<item> compare = inc::default_compare<item>) const {
            return the.index_of_first(value, compare);
        }

        void index_of_first(
            the_t                              value, 
            inc::can_callback<void(uxx index)> match,
            inc::can_compare<item>             compare = inc::default_compare<item>) const {
            the.index_of_first(value, match, compare);
        }
    };
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_index_of_first::xuser
