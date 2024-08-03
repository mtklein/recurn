#include "recurn.h"

int main(void) {

    // float square(float x) { return x*x; }
    struct program *square;
    {
        struct builder *b = builder(1);
        val x = farg(b,0);
        square = compile(b,fmul(b, x,x));
    }

    // float cube(float x) { return x * square(x); }
    struct program *cube;
    {
        struct builder *b = builder(1);
        val x  = farg(b,0),
            x2 = call(b, square, (val const[]){x});
        cube = compile(b, fmul(b, x,x2));
    }

    if (!cube) {
        return 1;
    }

    // float pow_acc(float acc, float x, float n) {
    //     return n > 0 ? pow_acc(acc*x, x, n-1) : acc;
    // }
    struct program *pow_acc;
    {
        struct builder *b = builder(3);
        val acc = farg(b,0),
              x = farg(b,1),
              n = farg(b,2);

        pow_acc = recurn(b, fgt(b, n, fimm(b,0.0f))
                          , (val const[]){ fmul(b, acc,x), x, fadd(b, n,fimm(b,-1.0f)) }
                          , acc);
    }

    // float pow(float x, float n) {
    //     return pow_acc(1.0f, x, n);
    // }
    struct program *pow;
    {
        struct builder *b = builder(2);
        val acc = fimm(b, 1.0f),
              x = farg(b, 0),
              n = farg(b, 1);
        pow = compile(b, call(b, pow_acc, (val const[]){ acc,x,n }));
    }

    if (!pow) {
        return 2;
    }

    return 0;
}
