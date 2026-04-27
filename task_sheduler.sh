#!/bin/bash

taskSheduler()
{
    # Menu
    echo "1. List scheduled tasks"
    echo "2. Add a task"
    echo "3. Remove a task"
    echo "4. Exit"
    #Get choice in the option variable
    read -p "Choose an option: " option
    case $option in
        1)
            #Test if there are tasks or not
            if [[ -z "$(crontab -l |grep -v "^#" |grep -v "^$" 2>/dev/null)" ]]; then
                echo "There is no task"
            else
                echo "Scheduled tasks:"
                crontab -l |grep -v "^#" |grep -v "^$"
            fi
            ;;
        2)
            #Get the task to be sheduled
            echo "Enter the command or script to be executed:"
            read task
            echo "Enter the shedule *(minute 0-59) *(hour 0-23)  *(day of month 0-31) *(month 1-12) *(day of week 0-6):"
            read shedule
            #Test if the shedule is valid or not
            read -r min hour dom mon dow <<< "$shedule"
            if [[ $min -gt 59 || $hour -gt 23 || $dom -gt 31 || 
                $mon -gt 12 || 
                $dow -gt 6 ]]; then
                echo "Invalid Input"
            else
                while [ $(echo "$shedule" | wc -w) -lt 5 ]
                do
                    shedule="${shedule} *"
                done
                #Add new task in the crontab
                (crontab -l 2>/dev/null; echo "$shedule $task") | crontab -
            echo "Task sheduled successfully!" 
            fi  
            ;;
        3)
            if [[ -z "$(crontab -l |grep -v "^#" |grep -v "^$" 2>/dev/null)" ]]; then
                echo "There is not a sheduled task"
            else
                echo "Scheduled tasks:"
                crontab -l |grep -v "^#" |grep -v "^$"
                echo "Enter the name of the task to remove:"
                read taskName
                #Remove the task if it exists
                if ! crontab -l |grep -q "$taskName" ; then
                    echo "Task doesn't exist"
                else
                    crontab -l | grep -v "$taskName" | crontab -
                    echo "Task removed successfully!"
                fi
            fi
            ;;
        4)
            exit 0
            ;;
        *)
            echo "Invalid input"
            ;;
    esac
}
#Loop for menu
while [ true ]; do
        taskSheduler
done
