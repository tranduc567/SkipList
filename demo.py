import random
import tkinter as tk
from tkinter import messagebox

class Node:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.header = Node(None, self.max_level)
        self.level = 0
    
    def random_level(self):
        level = 0
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level
    
    def insert(self, value):
        update = [None] * (self.max_level + 1)
        current = self.header
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current
        level = self.random_level()
        if level > self.level:
            for i in range(self.level + 1, level + 1):
                update[i] = self.header
            self.level = level
        new_node = Node(value, level)
        for i in range(level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node
    
    def search(self, value):
        current = self.header
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
        current = current.forward[0]
        if current and current.value == value:
            return True
        return False
    
    def display_list(self):
        result = []
        current = self.header.forward[0]
        while current:
            result.append(str(current.value))
            current = current.forward[0]
        return " -> ".join(result)

# Mô phỏng giao diện người dùng
def run_visualization():
    root = tk.Tk()
    root.title("Skip List Visualization")
    root.geometry("600x400")
    root.configure(bg="#f0f0f0")
    
    skip_list = SkipList(4)

    # Hàm chèn phần tử
    def insert_action():
        try:
            value = int(entry_value.get())
            if value <= 0:
                raise ValueError("Value must be a positive integer.")
            skip_list.insert(value)
            display_list()
        except ValueError as e:
            messagebox.showerror("Invalid Input", str(e))

    # Hàm tìm kiếm phần tử
    def search_action():
        try:
            value = int(entry_value.get())
            result = skip_list.search(value)
            result_label.config(text=f"Found: {result}")
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter a valid integer.")
    
    # Cập nhật hiển thị danh sách
    def display_list():
        list_display.delete(1.0, tk.END)
        current_display = skip_list.display_list()
        list_display.insert(tk.END, current_display)
    
    # Tạo giao diện
    title_label = tk.Label(root, text="Skip List Visualization", font=("Arial", 16), bg="#f0f0f0", fg="#333")
    title_label.pack(pady=20)

    input_frame = tk.Frame(root, bg="#f0f0f0")
    input_frame.pack()

    entry_value = tk.Entry(input_frame, font=("Arial", 14), width=10, justify="center")
    entry_value.grid(row=0, column=0, padx=10)

    insert_button = tk.Button(input_frame, text="Insert", font=("Arial", 12), command=insert_action, bg="#4CAF50", fg="white", relief="solid")
    insert_button.grid(row=0, column=1, padx=10)

    search_button = tk.Button(input_frame, text="Search", font=("Arial", 12), command=search_action, bg="#008CBA", fg="white", relief="solid")
    search_button.grid(row=0, column=2, padx=10)

    result_label = tk.Label(root, text="Found: None", font=("Arial", 14), bg="#f0f0f0", fg="#333")
    result_label.pack(pady=10)

    list_display = tk.Text(root, height=8, width=50, font=("Courier", 12), bg="#f9f9f9", wrap=tk.WORD)
    list_display.pack(pady=10)

    root.mainloop()

run_visualization()
