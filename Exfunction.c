#include "Exfunction.h"
#include "cvector.h"
#include "lightEdit.h"
#include "stdio.h"
#include "string.h"

#define MATCH_CASE_ENABLE 0 //函数调用名称大小写是否敏感 1表示敏感 0 表示不敏感
void show(int i);
void showcircle(char ch, int r);
void simplefunction(char *str, unsigned int sum, float dee, char ch);

static int ExternFunc_Find(char *funcname);
static void ExternFunc_list(void);
//static void ExternFunc_SocReset(void);
static unsigned char matchString(const char *str1, const char *str2);
const CALLFUNCTIONTABLE functable[] =
    {
        EXPOTRFUNC(LIST, ExternFunc_list, "", " 函数列表"),
        EXPOTRFUNC(help, ExternFunc_list, "", "If you want to support Chinese display please convert all files to GB2312"),
        EXPOTRFUNC(circle, showcircle, " %c %d", "串口显示一个圆"),
        EXPOTRFUNC(open, Edit_OpenFile, "%s", "open [filename] open a file with name"),
        EXPOTRFUNC(close, Edit_CloseFile, "%s", "close [filename] close a file with name"),
        EXPOTRFUNC(L, Edit_showLine, "%d", "L [n] show at n line context"),
        EXPOTRFUNC(D, Edit_deleteLine, "%d", "D [n] delete at n line context"),
        EXPOTRFUNC(CU, Edit_copyLineToUp, "%d %d", "CU [n] [m] Copy n rows above m rows"),
        EXPOTRFUNC(CD, Edit_copyLineToDown, "%d %d", "CD [n] [m] Copy n rows below m rows"),
        EXPOTRFUNC(RA, Edit_replaceAll, "%s %s", "RA [str1] [str2] Replace all str1's with str2"),
        EXPOTRFUNC(R, Edit_replace, "%d %d %d %s %s", "R [line] [row] [n] [str1] [str2] Replace str1 with str2 in n characters after the row column of line"),
        EXPOTRFUNC(I, Edit_instert, "%d %d %s", "I [line] [row] [str1] Insert str1 in the row column of line"),
        EXPOTRFUNC(DAStr, Edit_instert, "%s", "DAStr [str1] Delete All str1"),
        EXPOTRFUNC(DStr, Edit_deleteStr, "%d %d %d %s", "DStr [line] [row] [n] [str1] delete str1 in n characters after the row column of line"),
        EXPOTRFUNC(CFB, show, " %d", "%d乘法表")};
//EXPOTRFUNC( 函数别名命令行调用的名字 |真正的函数名 | 函数传参的格式字符串 |这个函数的简介)
void simplefunction(char *str, unsigned int sum, float dee, char ch)
{

    //    fl.flo = dee;
    printf("接收到的字符串是:%s,\n\
        接收到的字符是: %c \n\
	接受到的数字是 %d\n\
        接收到的小数是 %f __ \n ",
           str, ch, sum, dee);
}

void showcircle(char ch, int r)
{
    for (int i = 1; i <= (2 * r); i++)
    {
        for (int j = 1; j < (2 * r); j++)
        {
            if (((i - r) * (i - r) + (j - r) * (j - r)) <= (r * r))
                printf("%c ", ch);
            else
                printf("%c ", ' ');
        }
        printf("\n");
    }
}

void show(int i)
{
    for (int qq = 1; qq <= i; qq++)
    {
        for (int j = 1; j <= qq; j++)
        {
            printf("%dx%d=%2d  ", j, qq, j * qq);
        }
        printf("\n");
    }
}

void ExternFunc_list(void)
{
    //    static char isfirstPrint = 0;

    int size = sizeof(functable) / sizeof(functable[0]);
    printf("QuickComplet:");
    for (int i = 0; i < size; i++)
    {
        printf("\"%s\"", functable[i].FuncName);
        if (i != (size - 1))
            printf(",");
    }
    printf("\n\n*---------------------------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf(" |    %s(%s);%30s\n", functable[i].FuncName, functable[i].fmt, functable[i].Introduction);
        if (i != size - 1)
            printf(" |--------------------------------------------------------\n");
    }
    printf("*---------------------------------------------------------\n");
}

static int ExternFunc_Find(char *funcname)
{
    int size = sizeof(functable) / sizeof(functable[0]);
    for (int i = 0; i < size; i++)
    {
        if (matchString(funcname, functable[i].FuncName) == 0)
            return i;
    }
    return -1;
}

static void *args[7][100] = {0};
void ExternFunc_excute(char *str)
{
    char *ptemp;
    char ch;
    ptemp = strrchr(str, '\n'); //find the last \n ,then remove it
    if (ptemp != NULL)
    {
        *ptemp = '\0';
    }
    ptemp = strstr(str, " ");
    if (ptemp == NULL)
    {
        ptemp = str + strlen(str);
        ch = *ptemp;
    }
    else
    {
        ch = '\0';
        *ptemp = '\0';
        ptemp++;
    }

    int loc = ExternFunc_Find(str); //寻找函数
    if (loc == -1)
    {
        printf("%s are not find\n the function list :\n", str);
        ExternFunc_list();
        return;
    }

    if (ch != '\0')
        *ptemp = ch;
    int success = sscanf(ptemp, functable[loc].fmt, &args[0][1], &args[1][1], &args[2][1], &args[3][1], &args[4][1], &args[5][1]);

    //为兼容 可以输入字符串而做出的妥协
    int i = 0;
    ptemp = (char *)functable[loc].fmt;
    for (i = 0; i < 7; i++)
    {
        if ((ptemp = strstr(ptemp, "%")) != NULL)
        {

            if (*(++ptemp) == 's')
                args[i][0] = &args[i][1];
            else if (*ptemp == 'f')
            {
                args[i][0] = args[i][1];
            }
            else
                args[i][0] = args[i][1];
        }
        else
            break;
    }
    if (i != success)
    {
        printf("Err: 函数%s 参数应该为%d个,但只有%d\n", functable[loc].FuncName, i, success);
        return;
    }
    //调用真正的函数
    functable[loc].func(args[0][0], args[1][0], args[2][0], args[3][0], args[4][0], args[5][0], args[6][0]);
}

unsigned char matchString(const char *str1, const char *str2)
{
    char *ptemp1 = (char *)str1;
    char *ptemp2 = (char *)str2;
    while (*ptemp1 != '\0' || *ptemp2 != '\0')
    {
#if MATCH_CASE_ENABLE == 0
        if (((*ptemp1 - *ptemp2) == ('A' - 'a') || (*ptemp1 - *ptemp2) == ('a' - 'A')) &&
            (*ptemp1 >= 'A' && *ptemp1 <= 'z' && *ptemp2 >= 'A' && *ptemp2 <= 'z'))
        {
            ptemp1++;
            ptemp2++;
        }
        else if (*ptemp1 != *ptemp2)
            return 1;
#else
        if (*ptemp1 != *ptemp2)
            return 1;
#endif

        else
        {
            ptemp1++;
            ptemp2++;
        }
    }
    if (*ptemp1 == '\0' && *ptemp2 == '\0')
        return 0;
    else
        return 0xFF;
}
