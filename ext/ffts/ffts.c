#include <ruby.h>
#include <stdio.h>
#include "ffts/ffts.h"

static VALUE
ffts_init(VALUE self, VALUE size, VALUE sign) {
  size_t requested = NUM2SIZET(size);
  int sign_v = NUM2INT(sign);
  ffts_plan_t *ffts_plan = ffts_init_1d(requested, sign_v);
  ffts_free(ffts_plan);
  printf("Allocated and released ffts plan.");
  return self;
}

static VALUE
ffts_release(VALUE self) {
  printf("In ffts_release.\n");
  return self;
}

void
Init_ffts(void) {
  VALUE cFFTS;

  cFFTS = rb_const_get(rb_cObject, rb_intern("FFTS"));

  rb_define_method(cFFTS, "initialize", ffts_init, 1);
  rb_define_method(cFFTS, "release", ffts_release, 1);
}
