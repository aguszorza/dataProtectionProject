#include <gmp.h>

class Mpz {
public:
    mpz_t gmp;

    /* Constructor */
    Mpz(){
    mpz_init(this->gmp);
}

    Mpz(int value){
    mpz_init(this->gmp);
    mpz_set_ui(this->gmp, value);
}

    /* Destructor */
    ~Mpz(){
    mpz_clear(this->gmp);
}

    void operator+=(int value){
    mpz_add_ui(this->gmp, this->gmp, value);
}
};

int main() {
    Mpz test(10);
    gmp_printf("Cd1 = { %Zu }\n", test.gmp);
}
