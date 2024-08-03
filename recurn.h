#pragma once

// Pretty much the usual stuff, just adding program arguments and a return value.
typedef struct { int id; } val;

struct builder* builder(int args);
struct program* compile(struct builder*, val ret);
void run(struct program const*, int n, float* ret, float const* arg[]);

val fimm(struct builder*, float imm);
val farg(struct builder*, int ix);     // Load arg[ix].

val fadd(struct builder*, val,val);
val fmul(struct builder*, val,val);

val fgt(struct builder*, val,val);

// Result of a (previously compiled) sub-program with these arguments.
val call(struct builder*, struct program const *sub, val const arg[]);

// Tail-call the current program if cond is true, otherwise return ret.
struct program* recurn(struct builder*, val cond, val const arg[], val ret);
