#include "lightEdit.h"
#include "include.h"

#include <dirent.h>

V_Declare_Vector(char, String);
V_Declare_Vector(VCT_String *, FileLine);

char filename[255] = {0};

VCT_FileLine *context = NULL;

u8 compareChar(char *a, char *b) { return *a < *b; }

bool Edit_OpenFile(char *name)
{
    FILE *fp = NULL;
    fp = fopen(name, "r");
    if (context == NULL)
    {
        context = VCT_newVCT_FileLine();
        context->deleteSub = VCT_deleteVCT_String;
    }
    else
    {
        context->clear(context);
    }
    VCT_String *lineStr = VCT_newVCT_String();
    lineStr->compare = compareChar;
    if (fp != NULL)
    {
        char ch = 0;
        while ((ch = fgetc(fp)) != EOF)
        {
            lineStr->append(lineStr, ch);
            if (ch == '\n')
            {
                lineStr->append(lineStr, '\0');
                context->append(context, lineStr);
                lineStr = VCT_newVCT_String();
                lineStr->compare = compareChar;
            }
        }
        if (lineStr != context->at(context, context->size - 1)[0])
        {
            context->append(context, lineStr);
        }
        if (fclose(fp) == 0)
        {
            strcpy(filename, name);
            return true;
        }
        else
        {
            context->clear(context);
            K_ERROR("close file error!!%s", "\n");
            return false;
        }
    }
    else
    {
        K_ERROR("open file error!!%s", "\n");
        return false;
    }
}

bool Edit_CloseFile(char *name)
{
    FILE *fp = NULL;
    fp = fopen(name, "w");
    if (Edit_check() == false || fp == NULL)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return false;
    }
    for (u32 i = 0; i < context->getSize(context); i++)
    {
        fwrite(context->at(context, i)[0]->data, context->at(context, i)[0]->size - 1, 1, fp);
    }
    if (fflush(fp) != 0)
    {
        K_ERROR("save file error!!!%s", "\n");
        fclose(fp);
        return false;
    }
    if (fclose(fp) == 0)
    {
        strcpy(filename, "");
        VCT_deleteVCT_FileLine(context);
        context = NULL;
        return true;
    }
    else
    {
        return false;
    }
}

void Edit_showLine(int n)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    if (n == -1)
    {
        for (int i = 0; i < context->getSize(context); i++)
        {
            printf("line %d :%s", i, context->at(context, i)[0]->data);
        }
    }
    else if (n < context->getSize(context))
    {
        printf("line %d :%s", n, context->at(context, n)[0]->data);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

void Edit_deleteLine(int n)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (n < context->getSize(context))
    {
        context->remove(context, n, 1);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

void Edit_copyLineToUp(int des, int src)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (des < context->getSize(context) && src < context->getSize(context))
    {
        VCT_String *oline = context->at(context, src)[0];
        VCT_String *nline = VCT_newVCT_String();
        nline->compare = compareChar;
        nline->reSize(nline, oline->getSize(oline));
        for (u32 i = 0; i < oline->size; i++)
        {
            nline->append(nline, oline->at(oline, i)[0]);
        }

        context->insert(context, des, nline);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}
///< @todo 高耦合 可优化
void Edit_copyLineToDown(int des, int src)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (des < context->getSize(context) && src < context->getSize(context))
    {
        VCT_String *oline = context->at(context, src)[0];
        VCT_String *nline = VCT_newVCT_String();
        nline->compare = compareChar;
        nline->reSize(nline, oline->getSize(oline));
        for (u32 i = 0; i < oline->size; i++)
        {
            nline->append(nline, oline->at(oline, i)[0]);
        }

        context->insert(context, des + 1, nline);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

void Edit_replaceAll(char *des, char *src)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    for (u32 i = 0; i < context->getSize(context); i++)
    {
        context->at(context, i)[0]->replace(context->at(context, i)[0], des, strlen(des), src, strlen(src));
    }
}

void Edit_replace(int line, int row, int charCnt, char *des, char *src)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (line < context->getSize(context))
    {
        VCT_String *tmpString = VCT_newVCT_String();
        tmpString->compare = compareChar;
        for (u32 i = row; i < (row + charCnt) && i < context->at(context, line)[0]->size; i++)
        {
            tmpString->append(tmpString, context->at(context, line)[0]->at(context->at(context, line)[0], i)[0]);
        }
        context->at(context, line)[0]->remove(context->at(context, line)[0], row, charCnt);
        tmpString->replace(tmpString, des, strlen(des), src, strlen(src));
        Edit_instert(line, row, tmpString->data);
        VCT_deleteVCT_String(tmpString);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

void Edit_instert(int line, int row, char *str)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (line < context->getSize(context))
    {
        while (str != NULL && *str != 0)
        {
            context->at(context, line)[0]->insert(context->at(context, line)[0], row, *str);
            str++;
            row++;
        }
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

void Edit_deleteAllStr(char *str)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    for (u32 i = 0; i < context->getSize(context); i++)
    {
        context->at(context, i)[0]->replace(context->at(context, i)[0], str, strlen(str), "", 0);
    }
}

void Edit_deleteStr(int line, int row, int n, char *str)
{
    if (Edit_check() == false)
    {
        K_ERROR("file are no open!!!%s", "\n");
        return;
    }
    else if (line < context->getSize(context))
    {
        VCT_String *tmpString = VCT_newVCT_String();
        tmpString->compare = compareChar;
        for (u32 i = row; i < (row + n) && i < context->at(context, line)[0]->size; i++)
        {
            tmpString->append(tmpString, context->at(context, line)[0]->at(context->at(context, line)[0], i)[0]);
        }
        context->at(context, line)[0]->remove(context->at(context, line)[0], row, n);
        tmpString->replace(tmpString, str, strlen(str), "", 0);
        Edit_instert(line, row, tmpString->data);
        VCT_deleteVCT_String(tmpString);
    }
    else
    {
        K_WARNINR("out of max line%s", "\n");
    }
}

bool Edit_check(void)
{
    return !(strlen(filename) == 0 || context == NULL || context->getSize(context) == 0);
}
