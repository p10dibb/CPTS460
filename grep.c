#include "ucode.c"

//modified from geeks to geeks isSubstring code
int isSubstring(char *s1, char *s2)
{
    int M = strlen(s1);
    int N = strlen(s2);

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return 1;
    }

    return;
}

int main(int argc, char *argv[])
{
    char buf[MAX];
    int fd = 0;
    char *full = "";
    char *cur = "";
    printf("--------------------------\n");
    printf("Pauls GREP\n");
    printf("---------------------------\n");

    //if not valid input
    if (argc < 2)
    {
        printf("Usage: grep pattern filename\n");
        return;
    }

    if (argc >= 2)
    {
        // close(0);
        fd = open(argv[2], O_RDONLY);
    }

    //reads in full file
    int i=0;
    while (read(fd, buf, MAX))
    {
        strcat(full, buf);
        printf("%d\n",i);
        i++;
    }

    // parses file by line if argv1 is substring then print it
    cur = strtok(full, '\n');
    if (isSubstring(argv[1], cur) == 1)
    {
        printf("%s", cur);
    }
    while (1)
    {
        cur = strtok(NULL, '\n');
        if (cur == NULL)
        {
            break;
        }
        if (isSubstring(argv[1], cur) == 1)
        {
            printf("%s\n", cur);
        }
    }

    return 0;
}