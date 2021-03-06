#ifndef xpack_lock_atom_or
#define xpack_lock_atom_or
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::lock_atom_or
        #include"define/base_type.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::lock_atom_or{
        template<class a>
        inline a atom_xor(a * left, a right){
            return __atomic_xor_fetch(left, right, 5);
        }
    }

#endif

namespace xuser::inc{
    using ::mixc::lock_atom_or::atom_or;
}
