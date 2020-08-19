#include <iostream>

int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}