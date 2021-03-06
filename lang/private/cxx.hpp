#ifndef xpack_lang_cxx
#define xpack_lang_cxx
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::lang_cxx
        #include"define/base_type.hpp"
        #include"macro/xgc.hpp"
        #include"macro/xprop.hpp"
        #include"macro/xsv.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::lang_cxx{
        template<class final, class item_t>
        struct cxx{
        private:
            inline static item_t empty = item_t(0);
        public:
            xgc_fields(
                xiam(cxx<final, item_t>),
                xpro(ptr,   item_t *),
                xpro(count, uxx)
            );
        public:
            cxx() : 
                cxx(& empty, 0) {}

            cxx(cxx const &) = default;

            constexpr cxx(const item_t * str) : 
                ptr((item_t *)str), count(0) {
                for(uxx i = 0; str[i++]; count = i);
            }

            template<class final_t>
            cxx(cxx<final_t, item_t> const & self) : 
                cxx((the_t &)self){
            }

            template<class type>
            cxx(type const * ptr, uxx count) : 
                ptr((item_t *)ptr), count(count) {
                static_assert(sizeof(type) == sizeof(item_t));
            }

            cxx(inc::static_string_holder<item_t> holder) : 
                cxx(holder.ptr(), holder.length()){
            }

            item_t & operator [](uxx index) const {
                return the.ptr[index];
            }

            operator item_t *(){
                return the.ptr;
            }

            operator const item_t *() const {
                return the.ptr;
            }

            final backward(uxx value) const {
                auto tmp = thex;
                tmp.ptr += value;
                tmp.count -= uxx(value);
                return tmp;
            }

            final forward(uxx value) const {
                return backward(
                    uxx(-ixx(value))
                );
            }

            final shorten(uxx count) const {
                auto tmp = thex;
                tmp.count -= count;
                return tmp;
            }

            final elongate(uxx count) const {
                return shorten(
                    uxx(-ixx(count))
                );
            }

        public:
            xpubget_pubset(length, uxx){
                xr{ return the.count; }
                xw{ the.count = value; }
            };

            xpubget(is_empty, bool){
                return length() == 0;
            };
        };
    }

    #if xis_os64
        #define xc08(str)      xsv(char, "0123456789abcdef", str)
    #elif xis_os32
        #define xc08(str)      xsv(char, "01234567", str)
    #endif
#endif

#define xusing_lang_cxx     ::mixc::lang_cxx
