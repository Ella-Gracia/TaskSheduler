#!/bin/sh
listOptions() 
{
    echo "1. List scheduled tasks"
    echo "2. Add a task"
    echo "3. Remove a task"
    echo "4. Exit"
}

listSheduledTask() 
{
    tasks=$(crontab -l 2>/dev/null | grep -v "^#" | grep -v "^$")
    if [ -z "$tasks" ]; then
        echo "There is no task"
    else
        echo "Scheduled tasks:"
        echo "$tasks"
    fi
}

addTask() 
{
    echo "Enter the command or script to be executed:"
    read task
    echo "Enter the schedule:"
    read shedule

    # Count elements
    count=0
    for word in $shedule; 
    do
        count=$((count + 1))
    done

    if [ "$count" -gt 5 ]; then
        echo "Invalid Input"
    else
        new_shedule="$shedule"
        i=$count
        while [ "$i" -lt 5 ]; 
        do
            new_shedule="$new_shedule *"
            i=$((i + 1))
        done
        (crontab -l 2>/dev/null; echo "$new_shedule $task") | crontab -
        if [ $? -eq 0 ]; then
            echo "Task scheduled successfully!"
        else
            echo "Error: Failed to install crontab."
        fi
    fi  
}

removeTask() 
{
    tasks=$(crontab -l 2>/dev/null | grep -v "^#" | grep -v "^$")
    if [ -z "$tasks" ]; then
        echo "There is not a scheduled task"
    else
        echo "Scheduled tasks:"
        echo "$tasks"
        echo "Enter the name of the task to remove:"
        read taskName
        
        if ! crontab -l | grep -q "$taskName"; then
            echo "Task doesn't exist"
        else
            # Remove a specific task
            (crontab -l | grep -v "$taskName") | crontab -
            echo "Task removed successfully!"
        fi
    fi
}
while true; 
do
    listOptions
    printf "Choose an option: "
    read option
    case "$option" in
        1) listSheduledTask ;;
        2) addTask ;;
        3) removeTask ;;
        4) exit 0 ;;
        *) echo "Invalid input" ;;
    esac
done

