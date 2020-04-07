#ifndef xpack_lang_cxx
#define xpack_lang_cxx
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::lang_cxx
        #include"define/base_type.hpp"
        #include"macro/xgc.hpp"
        #include"macro/xsv.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::lang_cxx{
        template<class item>
        xgc(core)
            xgc_fields(
                xpro(ptr, item *),
                xpro(count, uxx)
            );

            core() : core(& empty, 0) {}
            core(core const &) = default;
            core(item const * ptr, uxx count) : 
                ptr((item *)ptr), count(count) {
            }

            core(inc::static_string_holder<item> holder){
                ptr   = holder.ptr();
                count = holder.length();
            }
        protected:
            inline static item empty = item(0);
        xgc_end();

        template<class final, class item>
        struct cxx : core<item> {
            using core<item>::core;
            using the_t = core<item>;
            cxx(core<item> const & self) : core<item>(self){}

            item & operator [](uxx index) {
                return core<item>::ptr[index];
            }

            const item & operator [](uxx index) const {
                return core<item>::ptr[index];
            }

            operator item *(){
                return core<item>::ptr;
            }

            operator const item *() const {
                return core<item>::ptr;
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

            /*属性区*/
        public:
            uxx length() const {
                return core<item>::count;
            }

            final & length(uxx value) {
                core<item>::count = value;
                return thex;
            }

            final & length(uxx * result) const {
                result[0] = length();
                return thex;
            }

            bool is_empty() const {
                return length() == 0;
            }
        };
    }

    #ifdef xos64
        #define xc08(str)      xsv(char, "0123456789abcdef", str)
    #endif

    #ifdef xos32
        #define xc08(str)      xsv(char, "01234567", str)
    #endif
#endif

#define xusing_lang_cxx     ::mixc::lang_cxx
