#ifndef xpack_dumb_struct_t
#define xpack_dumb_struct_t
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::dumb_struct_t
        #include"define/base_type.hpp"
        #include"macro/xgc.hpp"
        #include"meta/is_class.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::dumb_struct_t{
        template<class type, bool is_class> struct struct_t;
        template<class type>
        struct struct_t<type, true> : type {
            xgc_fields(
                xiam(struct_t<type, true>, type)
            );
        public:
            struct_t(struct_t const &) = default;

            template<class ... args>
            struct_t(args const & ... list) :
                type(list...) {}

        };

        template<class type>
        struct struct_t<type, false>{
            xgc_fields(
                xiam(struct_t<type, false>),
                xpro(data, type)
            );
        public:
            template<class ... args>
            struct_t(args const & ... list) : 
                data(list...){
            }

            operator type & (){
                return data;
            }

            operator const type & () const {
                return data;
            }
        };
    }

#endif

namespace xuser::inc{
    template<class type>
    using struct_t = ::mixc::dumb_struct_t::
        struct_t<type, mixc::dumb_struct_t::inc::is_class<type>>;
}
