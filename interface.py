#!/usr/bin/env python3
import tkinter as tk
from tkinter import ttk, messagebox
from crontab import CronTab

def get_cron():
    return CronTab(user=True)

def load_tasks():
    task_tree.delete(*task_tree.get_children())

    for job in get_cron():
        task_tree.insert("", "end", values=(job.slices, job.command))

def add_task():
    command = cmd_entry.get()
    schedule = sch_entry.get()
    if not command or not schedule:
        messagebox.showerror("Error", "Fill all fields")
        return
    try:
        cron = get_cron()
        job = cron.new(command=command)
        job.setall(schedule)
        cron.write()
        cmd_entry.delete(0, tk.END)
        sch_entry.delete(0, tk.END)

        load_tasks()
    except:
        messagebox.showerror("Error", "Invalid cron expression")

def delete_task():
    users = get_cron()
    name = del_entry.get().strip()
    found = False
    if not name:
        messagebox.showerror("Error", "Enter command name")
        return
    for job in users:
        if job.command == name:
            found = True
            break
    if not found:
        messagebox.showerror("Error", "Tâche introuvable")
        return

    cron = get_cron()
    cron.remove_all(command=name)
    cron.write()
    del_entry.delete(0, tk.END)
    load_tasks()

root = tk.Tk()
root.title("Cron Manager")
root.geometry("900x500")
root.configure(bg="white")

sidebar = tk.Frame(root, bg="#111827", width=200)
sidebar.pack(side="left", fill="y")

tk.Label(
    sidebar,
    text="CRON",
    bg="#111827",
    fg="white",
    font=("Arial", 16, "bold")
).pack(pady=20)

def menu_button(text, command):
    btn = tk.Button(
        sidebar,
        text=text,
        command=command,
        bg="#111827",
        fg="white",
        activebackground="#1f2937",
        activeforeground="white",
        bd=0,
        relief="flat",
        anchor="w",
        padx=20,
        pady=15
    )
    btn.pack(fill="x")
    return btn

content = tk.Frame(root, bg="white")
content.pack(side="right", fill="both", expand=True)

tasks_view = tk.Frame(content, bg="white")
add_view = tk.Frame(content, bg="white")
delete_view = tk.Frame(content, bg="white")

for frame in (tasks_view, add_view, delete_view):
    frame.place(relwidth=1, relheight=1)

def show_frame(frame):
    frame.tkraise()

tk.Label(
    tasks_view,
    text="Tasks",
    bg="white",
    fg="#111827",
    font=("Arial", 18, "bold")
).pack(pady=10)

task_tree = ttk.Treeview(
    tasks_view,
    columns=("schedule", "command"),
    show="headings"
)

task_tree.heading("schedule", text="Schedule")
task_tree.heading("command", text="Command")

task_tree.column("schedule", width=200)
task_tree.column("command", width=600)
task_tree.pack(fill="both", expand=True, padx=20, pady=15)

tk.Label(
    add_view,
    text="Add Task",
    bg="white",
    font=("Arial", 18, "bold")
).pack(pady=10)

tk.Label(add_view, text="Command", bg="white").pack()

cmd_entry = tk.Entry(add_view, width=40)
cmd_entry.pack(pady=5)

tk.Label(add_view, text="Schedule (* * * * *)", bg="white").pack()

sch_entry = tk.Entry(add_view, width=40)
sch_entry.pack(pady=5)

tk.Button(
    add_view,
    text="Add Task",
    command=add_task,
    bg="#16a34a",
    fg="white",
    bd=0,
    padx=20,
    pady=8
).pack(pady=15)

tk.Label(
    delete_view,
    text="Delete Task",
    bg="white",
    font=("Arial", 18, "bold")
).pack(pady=10)

tk.Label(delete_view, text="Command name", bg="white").pack()

del_entry = tk.Entry(delete_view, width=40)
del_entry.pack(pady=5)

tk.Button(
    delete_view,
    text="Delete Task",
    command=delete_task,
    bg="#dc2626",
    fg="white",
    bd=0,
    padx=20,
    pady=8
).pack(pady=15)

def show_tasks():
    show_frame(tasks_view)
    load_tasks()

def show_add():
    show_frame(add_view)

def show_delete():
    show_frame(delete_view)

menu_button("📋 Tasks", show_tasks)
menu_button("➕ Add Task", show_add)
menu_button("🗑 Delete Task", show_delete)

show_tasks()
root.mainloop()