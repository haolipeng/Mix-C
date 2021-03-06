#ifndef xpack_test_lang_cxx_align_left
#define xpack_test_lang_cxx_align_left
    #pragma push_macro("xuser")
        #undef  xuser
        #define xuser mixc::test_lang_cxx_align_left
        #include"define/base_type.hpp"
        #include"lang/cxx/align_left.hpp"
        #include"lang/cxx/compare.hpp"
        #include"lang/cxx.hpp"
        #include"macro/xassert.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::test_lang_cxx_align_left{
        xtest(align_left){
            inc::c08 w = "";
            inc::c08 a;
            inc::c08 b;
            auto && alloc = [](uxx length){
                static char buf[100];
                buf[length] = '\0';
                return buf;
            };

            b = w.align_left(0, alloc);
            xassert_eq(0, b.length());

            a = "          ";
            b = w.align_left(10, alloc);
            xassert_eq(0, a.compare(b));

            w = "h";
            a = "h";
            b = w.align_left(1, alloc);
            xassert_eq(0, a.compare(b));

            a = "h ";
            b = w.align_left(2, alloc);
            xassert_eq(0, a.compare(b));

            a = "h  ";
            b = w.align_left(3, alloc);
            xassert_eq(0, a.compare(b));

            w = "hh";
            a = "h";
            b = w.align_left(1, alloc);
            xassert_eq(0, a.compare(b));

            a = "hh";
            b = w.align_left(2, alloc);
            xassert_eq(0, a.compare(b));

            a = "hh ";
            b = w.align_left(3, alloc);
            xassert_eq(0, a.compare(b));

            a = "hh  ";
            b = w.align_left(4, alloc);
            xassert_eq(0, a.compare(b));
        };
    }

#endif
