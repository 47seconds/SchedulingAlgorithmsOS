#include <stdio.h>

int main()
{
    int k = 0, a = 0, b = 0, process, no_of_resources, cnt = 0;
    int instance[5], op[10], availability[5];
    int P[10];
    int allocated[10][5], need[10][5], MAX[10][5];

    printf("\nEnter the number of resources : ");
    scanf("%d", &no_of_resources);

    printf("\nEnter the max instances of each resource\n");
    for (int i = 0; i < no_of_resources; i++)
    {
        availability[i] = 0;
        printf("%c= ", 'a' + i);
        scanf("%d", &instance[i]);
    }

    printf("\nEnter the number of processes : ");
    scanf("%d", &process);

    printf("\nEnter the allocation matrix\n");
    for (int i = 0; i < no_of_resources; i++)
    {
        printf(" %c", 'a' + i);
    }
    printf("\n");
    for (int i = 0; i < process; i++)
    {
        P[i] = i;
        printf("P[%d]  ", i);
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &allocated[i][j]);
            availability[j] += allocated[i][j];
        }
    }

    printf("\nEnter the MAX matrix\n");
    for (int i = 0; i < no_of_resources; i++)
    {
        printf(" %c", 'a' + i);
    }
    printf("\n");
    for (int i = 0; i < process; i++)
    {
        printf("P[%d]  ", i);
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &MAX[i][j]);
        }
    }
    printf("\n");

    a = -1;
    for (int i = 0; i < process; i++)
    {
        cnt = 0;  // Reset count
        b = P[i]; // Process ID
        for (int j = 0; j < no_of_resources; j++)
        {
            need[b][j] = MAX[b][j] - allocated[b][j];
            if (need[b][j] <= availability[j])
            {
                cnt++;
            }
        }

        if (cnt == no_of_resources)
        {
            op[k++] = P[i];
            for (int j = 0; j < no_of_resources; j++)
            {
                availability[j] += allocated[b][j];
            }
        }
        else
        {
            P[++a] = P[i];
        }
    }

    if (a != -1)
    {
        process = a + 1;
        main();
    }
    else
    {
        printf("\t <");
        for (int i = 0; i < k; i++)
        {
            printf(" P[%d] ", op[i]);
        }
        printf(">\n");
    }

    return 0;
}
