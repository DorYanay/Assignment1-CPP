#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I used the solutions from the version A test 2023 and from the Course web.

typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
    {
        return NULL;
    }
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
    return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    PElement *newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (idx >= pArr->ArrSize)
    {
        // Extend Array
        if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    if ((pArr->pElemArr)[idx] != NULL)
    {
        pArr->delFunc((pArr->pElemArr)[idx]);
    };
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

    if (idx >= pArr->ArrSize)
    {
        pArr->ArrSize = idx + 1;
    }

    return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
    if (pArr == NULL)
        return;
    for (int i = 0; i < pArr->ArrSize; i++)
        if ((pArr->pElemArr)[i] != NULL)
        {
            pArr->delFunc((pArr->pElemArr)[i]);
        }
    free(pArr->pElemArr);
    free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int i)
{
    if (pArr == NULL)
    {
        return NULL;
    }
    if ((pArr->ArrSize) <= i)
    {
        return NULL;
    }
    if (((pArr->pElemArr)[i]) == NULL)
    {
        return NULL;
    }
    return pArr->copyFunc((pArr->pElemArr)[i]);
}

int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return -1;
    }
    if ((pArr->ArrSize) < 0)
    {
        return -1;
    }
    return (pArr->ArrSize);
}
void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return;
    }
    for (int i = 0; i < (pArr->ArrSize); i++)
    {
        if (((pArr->pElemArr)[i]) != NULL)
        {
            pArr->printFunc((pArr->pElemArr)[i]);
        }
    }
}