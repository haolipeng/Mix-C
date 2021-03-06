#ifndef xpack_define_bitbind
#define xpack_define_bitbind
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::define_bitbind
        #include"define/base_type.hpp"
        #include"macro/xgc.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::define_bitbind{
        template<class type, class bit_type = bool>
        struct bitbind{
            using final = bitbind;
            
            xgc_fields(
                xiam(bitbind<type, bit_type>),
                xpro(ptr,  type *);
                xpro(mask, type);
            );
        public:
            bitbind() : bitbind(nullptr, 0) {}
            bitbind(type * bits, uxx index){
                this->bind(bits, index);
            }

            bit_type operator = (bit_type value){
                ptr[0] = value ? ptr[0] | mask : ptr[0] & ~mask;
                return value;
            }

            void bind(type * bits, uxx index){
                ptr = bits;
                mask = type(1) << index;
            }

            void swap_value(bitbind value){
                bit_type a = the;
                bit_type b = value;
                the        = b;
                value      = a;
            }

            operator bit_type(){
                return bit_type((ptr[0] & mask) != 0);
            }
        };
    }

#endif

namespace xuser::inc{
    using mixc::define_bitbind::bitbind;
}
