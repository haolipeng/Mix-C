#ifndef xpack_interface_ranger
#define xpack_interface_ranger
    #pragma push_macro("xuser")
    #undef  xuser
    #define xuser mixc::interface_ranger
    #include"configure.hpp"
    #include"define/base_type.hpp"
    #include"interface/initializer_list.hpp"
    #include"math/index_system.hpp"
    #include"memop/addressof.hpp"
    #include"memop/signature.hpp"
    
    namespace xuser{
        enum : uxx{
            positive    = 0,
            negtive     = uxx(-1)
        };

        struct base{
            voidp   ptr = nullptr;
            voidp   itr = nullptr;
            uxx     ofs = 0;
            uxx     len = 0;
            uxx     msk = 0;

            base(){}

            template<class object>
            base(object * ptr, uxx ofs, uxx len, uxx msk) : 
                ptr(ptr),
                itr(convert(ptr)),
                ofs(ofs),
                len(len),
                msk(msk){
            }

            template<class item_t>
            base(inc::initializer_list<item_t> * ptr, uxx ofs, uxx len, uxx msk) : 
                ptr((item_t *)(item_t const *)ptr->begin()),
                itr(voidp(& access_initializer_list<item_t>)),
                ofs(ofs),
                len(len),
                msk(msk){
            }

            template<class item_t>
            item_t & access(uxx index) const {
                return inc::signature<item_t &, uxx>::call(ptr, itr, (index ^ msk) + ofs);
            }

        private:
            template<class item_t>
            static item_t & access_initializer_list(item_t * ptr, uxx index){
                return ptr[index];
            }

            template<class object>
            static voidp convert(object * list){
                using item_t = decltype(list[0][0]);
                item_t & (object::*ptr)(uxx) = & object::operator[];
                return *(voidp *)& ptr;
            }
        };

        template<class item_t>
        struct ranger{
        private:
            base    dat;
            xgc_fields(
                xiam(ranger<item_t>)
            );
        public:
            ranger(){}

            ranger(base impl) : 
                dat(impl){}

            template<class random_access_t> 
            #if not xfor_msvc_hint
            requires(
                inc::signature<item_t &, uxx>::has(& random_access_t::operator[]) and
                inc::signature<uxx>::has(& random_access_t::length) 
            )
            #endif
            ranger(random_access_t const & impl){
                dat = base(xref impl, 0, impl.length(), positive);
            }

            ranger(inc::initializer_list<item_t> impl){
                dat = base(xref impl, 0, impl.size(), positive);
            }

            uxx length() const {
                return dat.len;
            }

            item_t & operator[](uxx index){
                return dat.access<item_t>(index);
            }

            item_t & operator[](uxx index) const {
                return dat.access<item_t>(index);
            }

            bool is_positive() const {
                return dat.msk == positive;
            }

            ranger<item_t> range(iinterval i){
                ranger<item_t> r = the;
                i.normalize(the.length());

                if (is_positive()){ // 正序
                    if (i.left() <= i.right()){ // 正序
                        r.dat.ofs += i.left();
                        r.dat.len  = i.right() - i.left() + 1;
                        r.dat.msk  = positive;
                    }
                    else{ // 反序
                        r.dat.ofs += i.left();
                        r.dat.len  = i.left() - i.right() + 1;
                        r.dat.msk  = negtive;
                    }
                }
                else{ // 反序
                    if (i.left() <= i.right()){ // 反序 & 正序 -> 反序
                        r.dat.ofs -= i.left();
                        r.dat.len  = i.right() - i.left() + 1;
                        r.dat.msk  = negtive;
                    }
                    else{ // 反序 & 反序 -> 正序
                        r.dat.ofs -= i.left() + 1;
                        r.dat.len  = i.left() - i.right() + 1;
                        r.dat.msk  = positive;
                    }
                }
                return r;
            }
        };

        #define xranger(...)                                                        \
        ::mixc::interface_ranger::ranger<__VA_ARGS__> range(::mixc::iinterval i){   \
            using namespace ::mixc::interface_ranger;                               \
            if (i.normalize(this->length());                                        \
                i.left() <= i.right()){                                             \
                return base(this, i.left(), i.right() - i.left() + 1, positive);    \
            }                                                                       \
            else{                                                                   \
                return base(this, i.left() + 1, i.left() - i.right() + 1, negtive); \
            }                                                                       \
        }
    }

    #pragma pop_macro("xuser")
#endif

namespace xuser::inc{
    using ::mixc::interface_ranger::ranger;
}

#include"math/index_system.hpp"
