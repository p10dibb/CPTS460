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

    if (argc > 2)
    {
         close(0);
        fd = open(argv[2], O_RDONLY);
    }

    //reads FILE By line
    int i=0;
    while (getline(buf))
    {
        // strcat(full, buf);
         if (isSubstring(argv[1], buf) == 1)
        {
            printf("%s\n", buf);
        }
        // i++;
    }



    return 0;
}