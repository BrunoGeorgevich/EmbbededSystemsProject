#include "helloworld.h"

void hello_world() {
    struct mb_display *disp = mb_display_get();

    char *str = "ECOM042.2017.2";

    mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(REFRESH_TIME_HELLOWORLD), str);
    k_sleep(K_MSEC(REFRESH_TIME_HELLOWORLD)*strlen(str));
}
