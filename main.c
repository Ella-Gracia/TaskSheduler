#include "task_sheduler.h"
int main()
{
    int choice;
    listOptions();
    do
    {
        choice = getChoice();
        switch(choice)
        {
            case 1:
                listTasks();
                break;
            case 2:
                addTask();
                break;
            case 3:
                removeTask();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }while(choice != 4);
    return 0;
}
