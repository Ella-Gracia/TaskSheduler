#!/usr/bin/env python3
from crontab import CronTab
import sys
#List of options
def listOptions():
    print("1. List scheduled tasks")
    print("2. Add a task")
    print( "3. Remove a task")
    print("4. Exit")
#get the user's choice
def getChoice():
    choice = int(input("Enter your choice: "))
    return choice

def listTasks():
    #get the crontab of the current user
    cron = CronTab(user=True)
    for task in cron:
        print(f"{task.slices} {task.command}")
def addTask():
    cron = CronTab(user=True)
    taskName = input("Enter the name of the task : ")
    shedule = input("Enter the shedule: ")
    #add a new task
    job = cron.new(command = taskName)
    try:
        #add the shedule
        job.setall(shedule)
        #save the task to be sheduled
        cron.write()
        print("task added successfully")
    except(KeyError, ValueError):
        print("shedule invalid")
        print("Use '*' for empty fields ")

def removeTask():
    cron = CronTab(user=True)
    taskToRemove = input("Enter the task to be removed: ")
    jobs = list(cron.find_command(taskToRemove))
    if not jobs:
        print("task doesn't exist")
    else:
        for job in cron:
            #test if task exist
            if job.command == taskToRemove:
                #remove the task
                cron.remove_all(command = taskToRemove)
                print("Task removed successfully")
        cron.write()
    
def main():
    listOptions()
    while True:
        option = getChoice()
        match option:
            case 1:
                listTasks()
            case 2:
                addTask()
            case 3:
                removeTask()
            case 4:
                sys.exit(0)
        if option == 4:
            break

main()

