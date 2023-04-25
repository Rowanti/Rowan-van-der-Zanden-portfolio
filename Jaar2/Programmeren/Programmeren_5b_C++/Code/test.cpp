float x = 3.5;
float *p = &x;

void f(float &x){
    x++;
}
f(x);
cout<< x;