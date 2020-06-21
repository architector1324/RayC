#include <stdio.h>
#include "thrd.h"

CHAN(float)

thrd_chan(float) ch;

THREAD(void*, prod_t, float, a);

void* prod(float a) {
    printf("snd: %f\n", a);
    thrd_chan_snd(ch, a);
}

int main() {
    ch = thrd_chan_init(float)();

    thrd(prod_t) th;
    thrd_create(prod_t, th, prod, 3.14f);

    printf("recv: %f\n", thrd_chan_recv(ch));

    thrd_chan_free(ch);

    return 0;
}