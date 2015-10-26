#include <stdio.h>
#include <stdbool.h>
#include <ruby.h>
#include <ffts/ffts.h>

// Declare variables.
VALUE mFFTS;
VALUE cPlan;
VALUE cCPlan;

bool is_power_of_two(size_t num);

static VALUE
ffts_plan_initialize(VALUE self, VALUE rb_frames, VALUE rb_sign) {
  ffts_plan_t *plan;

  size_t n = RARRAY_LEN(rb_frames);
  if (!is_power_of_two(n)) {
    rb_raise(rb_eRuntimeError, "Frames must be a power of 2.");
    return Qnil;
  }

  int sign_v = NUM2INT(rb_sign);
  if (sign_v != -1 && sign_v != 1) {
    rb_raise(rb_eRuntimeError, "Sign must be 1 or -1.");
    return Qnil;
  }

  plan = ffts_init_1d(n, sign_v);

  VALUE rb_plan = Data_Wrap_Struct(cCPlan, NULL, ffts_free, plan);

  rb_funcall(self, rb_intern("n="), 1, INT2NUM(n));
  rb_funcall(self, rb_intern("frames="), 1, rb_frames);
  rb_funcall(self, rb_intern("sign="), 1, rb_sign);
  rb_funcall(self, rb_intern("plan="), 1, rb_plan);

  return self;
}

static VALUE
ffts_plan_execute(VALUE self) {


  VALUE rb_plan = rb_funcall(self, rb_intern("plan"), 0);
  VALUE rb_frames = rb_funcall(self, rb_intern("frames"), 0);
  VALUE rb_n = rb_funcall(self, rb_intern("n"), 0);

  ffts_plan_t *plan;
  Data_Get_Struct(rb_plan, ffts_plan_t, plan);

  size_t n = NUM2INT(rb_n);
  if (!is_power_of_two(n)) {
    return Qnil;
  }

  size_t alloc_length = 2 * n * sizeof(float);
  float __attribute__ ((aligned(32))) *input = valloc(alloc_length);
  float __attribute__ ((aligned(32))) *output = valloc(alloc_length);

  for (int i = 0; i < n; ++i) {
    input[i] = (float)NUM2DBL(RARRAY_AREF(rb_frames, i));
  }

  ffts_execute(plan, input, output);

  VALUE rb_output = rb_ary_new();
  for (int i = 0; i < n; ++i) {
    rb_ary_push(rb_output, DBL2NUM(output[i]));
  }

  free(input);
  free(output);

  return rb_output;
}

bool
is_power_of_two(size_t num) {
  return num != 0 && (num & (num - 1)) == 0;
}

void
Init_ffts(void) {
  mFFTS = rb_const_get(rb_cObject, rb_intern("FFTS"));
  cPlan = rb_define_class_under(mFFTS, "Plan", rb_cObject);
  cCPlan = rb_define_class_under(mFFTS, "CPlan", rb_cObject);

  rb_define_method(cPlan, "initialize", ffts_plan_initialize, 2);
  rb_define_method(cPlan, "execute", ffts_plan_execute, 0);

  rb_define_attr(cPlan, "n", 1, 1);
  rb_define_attr(cPlan, "frames", 1, 1);
  rb_define_attr(cPlan, "sign", 1, 1);
  rb_define_attr(cPlan, "plan", 1, 1);
}
