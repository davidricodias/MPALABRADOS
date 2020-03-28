/** 
 * @file mi_random.h
 * @author acid
 *
 */

#ifndef MI_RANDOM_H
#define MI_RANDOM_H

class mi_random {

public:
    typedef unsigned long  result_type;
    result_type mmin,mmax;
private:

    result_type xact;

public:
    mi_random() {
        xact = 1;
        mmin = 0;
        mmax = 98765432123;
    }

    mi_random(int seed) {
        xact = seed;
         mmin = 0;
        mmax = 98765432123;
    }
    result_type min(){return mmin;}
    result_type max(){return mmax;}
    result_type operator()()  {
        xact = (result_type) (123456 * xact + 1023013) % mmax;
        return xact;
    }

};
#endif /* MI_RANDOM_H */

