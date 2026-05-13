#include "TaskSheduler.hpp"
#include <cstdlib>
int main()
{
    TaskSheduler *p(0);
    p = new TaskSheduler;
    p->displayMenu();
    do
    {
          switch(p->getChoice())
        {
            case 1:
                p->listTasks();
                break;
            case 2:
                p->addTask();
                break;
            case 3:
                p->removeTask();
                break;
            case 4:
                exit(0);
        }
    }while(p->getChoice() != 4);
  
    return 0;
}