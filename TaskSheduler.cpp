#include "TaskSheduler.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib> 
#include <array>

using namespace std;
TaskSheduler::TaskSheduler(){} 
TaskSheduler::~TaskSheduler(){}
void TaskSheduler::displayMenu()
{
    cout << "1. List scheduled tasks" << endl;
    cout << "2. Add a task" << endl;
    cout << "3. Remove a task" << endl;
    cout <<  "4. Exit"<< endl;
}
int TaskSheduler::getChoice()
{
    int choice;
    cout << "Enter your choice between 1 and 4: ";
    cin >> choice;
    return(choice);
}
void TaskSheduler::listTasks()
{
    array<char , 250> buffer;
    string tasks;
    FILE* pipe;
    pipe = popen("crontab -l |grep -v \"^#\" |grep -v \"^$\" 2>/dev/null", "r");
    if(!pipe)
    {
        cerr << "Access denied" << endl;
    }
    while(fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        tasks += buffer.data();
    }
    if(tasks.empty())
    {
        cout << "No task found" << endl;
    }
    else
    {
        cout << "Scheduled tasks:" << endl;
        cout << tasks << endl;
    }
    pclose(pipe);

}
void TaskSheduler::addTask()
{
    int result;
    string taskName;
    string shedule;
    string cronTask;
    string command;

    cout << "Enter the name of the task: ";
    cin >> taskName;
    cin.ignore(10000, '\n');
    cout << "Enter the shedule: ";
    getline(cin , shedule);
    cronTask = shedule + " " + taskName;
    command = "(crontab -l 2>/dev/null; echo '" + cronTask + "') | crontab -";
    result = system(command.c_str());
    if(result == 0)
    {
        cout << "Task added successfully" << endl;
    }
    else
    {
        cout << "Error , check your shedule and use '*' for the empty fields" << endl;
    }
}
void TaskSheduler::removeTask()
{
    string taskToremove;
    string command;
    cout << "Enter the name of task to be removed: ";
    cin >> taskToremove;
    command = "crontab -l 2>/dev/null | grep -q \"" + taskToremove + "\"";
    
    if(system(command.c_str()) == 0)
    {
        command = "(crontab -l | grep -v " + taskToremove + ") | crontab -";
        if(system(command.c_str()) == 0)
        {
            cout << "Task removed successfully" << endl;
        }
    }
    else
    {
        cout << "Task doesn't exist" << endl;
    }
}

