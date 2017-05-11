#include <stdio.h>

/* Write a void function which can print the following text on the screen:

------------
-- TOTORO --
------------
- GREENFOX -
------------

Name this function as "TotoroLogoPrinter" and call it from the main function!*/
void TotoroLogoPrinter();

int main(){

    TotoroLogoPrinter();
    return 0;
}

void TotoroLogoPrinter() {

    printf("------------\n-- TOTORO --\n------------\n- GREENFOX -\n------------");

    return;
}
