#pragma once
#include"meta_seq/tnull.hpp"
#include"meta_seq/tlist.hpp"

namespace mixc{
    // 本来这样写挺好的
    // 但目前C++不准这样做
    // error: class template partial specialization contains template parameters that cannot be deduced
    // this partial specialization will never be used

    // template<class list> struct tpop;
    // template<class last, class ... args>
    // struct tpop<tlist<args..., last>>{
    //     using item = last;
    //     using new_tlist = tlist<args...>;
    // };

    // template<>
    // struct tpop<tlist<>>{
    //     using item = tnull;
    //     using new_tlist = tlist<>;
    // };

    template<class list>
    struct tpop{
    private:
        template<class first, class second, class ... args, class ... result_args>
        static auto invoke(tlist<first, second, args...>, tlist<result_args...>){
            return invoke(
                tlist<second, args...>(),
                tlist<result_args..., first>()
            );
        }

        template<class last, class ... result_args>
        static auto invoke(tlist<last>, tlist<result_args...>){
            struct pair{
                using item = last;
                using new_list = tlist<result_args...>;
            };
            return pair();
        }

        template<class ... result_args>
        static auto invoke(tlist<>, tlist<result_args...>){
            struct pair{
                using item = tnull;
                using new_list = tlist<result_args...>;
            };
            return pair();
        }
        using pair = decltype(
            invoke(list(), tlist<>())
        );
    public:
        using item = typename pair::item;
        using new_list = typename pair::new_list;
    };
}