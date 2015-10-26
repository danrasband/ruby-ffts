#include <ruby.h>
#include <stdio.h>
#include <ffts/ffts.h>

// Declare variables.
VALUE cFFTS;

static VALUE
_ffts_plan(VALUE klass, VALUE frames, VALUE sign) {
  ffts_plan_t *plan;

  int sign_v = NUM2INT(sign);
  size_t size = RARRAY_LEN(frames);
  plan = ffts_init_1d(size, sign_v);

  return Data_Wrap_Struct(cFFTS, NULL, ffts_free, plan);
}

static VALUE
_ffts_exec(VALUE klass) {
  printf("In ffts_release.\n");

  return Qnil;
}

void
Init_ffts(void) {
  cFFTS = rb_const_get(rb_cObject, rb_intern("FFTS"));

  rb_define_singleton_method(cFFTS, "plan", _ffts_plan, 2);
  rb_define_singleton_method(cFFTS, "execute", _ffts_exec, 0);
}
