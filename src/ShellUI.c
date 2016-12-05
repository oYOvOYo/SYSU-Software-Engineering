#include "ShellUI.h"

void ShellUI(void) {
    char ch[10000];
    while(1){
        scanf("%s", ch);
        printf("%s", ch);
        printf("%lf\n", calculate(ch));
    }
}