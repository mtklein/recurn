#include "recurn.h"
#include <stddef.h>

struct program* compile(struct builder* b, val ret) {
    return recurn(b, fimm(b,0.0f), NULL, ret);
}
