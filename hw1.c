/* code for the "hw1" pd class.  This adds an outlet and a state variable.  */

#include "m_pd.h"
 
typedef struct hw1
{
  t_object x_ob;
  t_outlet *x_outlet;
  int n;
  int r;
} t_hw1;

int factorial(int f){
    int fact = 1;
    for(int i = 2; i <= f; i++){
        fact = fact * i;
    }
    return fact;
}

void hw1_float(t_hw1 *x, t_floatarg f)
{
    x->n = (int)f;

    post("Calculating %dC%d...", x->n, x->r);
    int numer = factorial(x->n);
    int denom = factorial(x->r) * factorial(x->n - x->r);

    outlet_float(x->x_outlet, numer / denom);
}

void hw1_ft1(t_hw1 *x, t_floatarg g)
{   
    x->r = (int)g;

    post("Calculating %dC%d...", x->n, x->r);
    int numer = factorial(x->n);
    int denom = factorial(x->r) * factorial(x->n - x->r);

    outlet_float(x->x_outlet, numer / denom);
}

t_class *hw1_class;

void *hw1_new(void)
{
    t_hw1 *x = (t_hw1 *)pd_new(hw1_class);
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, gensym("float"), gensym("ft1"));
    x->x_outlet = outlet_new(&x->x_ob, gensym("float"));
    return (void *)x;
}

void hw1_setup(void)
{
    hw1_class = class_new(gensym("hw1"), (t_newmethod)hw1_new,
    	0, sizeof(t_hw1), 0, 0);
    class_addmethod(hw1_class, (t_method)hw1_ft1, gensym("ft1"), A_FLOAT, 0);
    class_addfloat(hw1_class, hw1_float);
}

