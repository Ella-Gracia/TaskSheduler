#include "task_sheduler.h"
void listOptions()
{
    printf("1. List scheduled tasks\n");
    printf( "2. Add a task\n");
    printf( "3. Remove a task\n");
    printf( "4. Exit\n");
}
int getChoice()
{
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    return choice;
}
void listTasks()
{
    FILE* fp;
    char buffer[100];
    system("crontab -l |grep -v \"^#\" |grep -v \"^$\" > crontab.txt");
    fp = fopen("crontab.txt", "r");
    if (fp == NULL) 
    {
        printf("Failed to open file\n");
    }
    int octect;
    octect = fgetc(fp);
    if (octect == EOF) 
    {
        printf("There is no task scheduled\n");
    }
    else
    {
        printf("Scheduled tasks:\n");
        while (fgets(buffer, sizeof(buffer), fp) != NULL) 
        {
            printf("%s", buffer);
        }
    }
}

void addTask() 
{
    char taskName[100];
    char shedule[100];
    char command[512];
    char task[250] = ""; 
    char *token;
    int count = 0;

    // enter the task to be scheduled
    printf("Enter the task to be scheduled: ");
    fgets(taskName, sizeof(taskName), stdin);
    //delete the \n at the end of variable task
    taskName[strcspn(taskName, "\n")] = '\0'; 

    //Enter the shedule for the task
    printf("Enter the schedule (ex: '30 12' or '0 5 * * *'): ");
    fgets(shedule, sizeof(shedule), stdin);
    shedule[strcspn(shedule, "\n")] = '\0';

    token = strtok(shedule, " ");
    while (token != NULL && count < 5) 
    {
        strcat(task, token);
        strcat(task, " ");
        token = strtok(NULL, " ");
        count++;
    }

    while (count < 5) 
    {
        strcat(task, "* ");
        count++;
    }
    //add task name 
    strcat(task, taskName);
    sprintf(command, "(crontab -l 2>/dev/null; echo \"%s\") | crontab -", task);
    if (system(command) == 0) 
    {
        printf("Task added successfully!\n");
    } 
    else 
    {
        printf("Error writing to crontab.\n");
    }

    printf("task added:\n%s\n", task);
}
void removeTask()
{
    char command[500];
    char taskName[100];
    listTasks();
    printf("Enter the name of task to be removed:");
    scanf("%s", taskName);
    snprintf(command, sizeof(command), "crontab -l 2>/dev/null | grep -q \"%s\"", taskName);
    if(system(command) == 0)
    {
        sprintf(command, "(crontab -l | grep -v \"%s\") | crontab -", taskName);
        if(system(command) == 0)
        {
            printf("Task removed successfully\n");
        }
    }
    else
    {
        printf("Task doesn't exist\n");
    }
}

