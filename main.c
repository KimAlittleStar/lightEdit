#include "Exfunction.h"
#include "lightEdit.h"

#include "memwatch.h"

//this is a new comment:
int main(void)
{
    mwInit();
    char commend[500];
    for (;;)
    {
        //scanf("%s",commend);
        printf("typing your command\n");
        fgets(commend, 499, stdin);
        if (strstr(commend, "exit()") == commend)
            break;
        ExternFunc_excute(commend);
    }
    mwTerm();
    return 0;

    // if (Edit_OpenFile("./context.txt") == true)
    // {
    //     Edit_showLine(-1);

    //     printf("\n");
    //     Edit_showLine(8);
    //     printf("\n");

    //     Edit_replace(8, 0, 4, "a", "A");
    //     Edit_showLine(8);
    //     printf("\n");

    //     Edit_CloseFile("./context.txt");
    // }
}
