#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Task Class
class Task {
private:
    string name;
    string description;
    bool completed;

public:
    Task(const string& n, const string& desc) : name(n), description(desc), completed(false) {}

    void markCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    const string& getName() const {
        return name;
    }

    const string& getDescription() const {
        return description;
    }
};

// Task Manager Class
class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markCompleted();
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    void displayTasks() const {
        if (tasks.empty()) {
            cout << "No tasks." << endl;
        } else {
            cout << "Task List:" << endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << i+1 << ". " << tasks[i].getName() << " - " << tasks[i].getDescription();
                if (tasks[i].isCompleted()) {
                    cout << " [Completed]";
                }
                cout << endl;
            }
        }
    }

    void sortTasksByName() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.getName() < b.getName();
        });
    }

    void sortTasksByCompletion() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.isCompleted() > b.isCompleted();
        });
    }

    bool saveTasksToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file for writing: " << filename << endl;
            return false;
        }

        for (const auto& task : tasks) {
            file << task.getName() << "," << task.getDescription() << "," << task.isCompleted() << endl;
        }

        file.close();
        return true;
    }

    bool loadTasksFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file for reading: " << filename << endl;
            return false;
        }

        tasks.clear();
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, description, completedStr;
            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, completedStr, ',');
            bool completed = (completedStr == "1");
            tasks.push_back(Task(name, description));
            if (completed) {
                tasks.back().markCompleted();
            }
        }

        file.close();
        return true;
    }
};

// Main Program
int main() {
    TaskManager taskManager;

    // Load tasks from file (if exists)
    taskManager.loadTasksFromFile("tasks.txt");

    // Example: Adding tasks
    taskManager.addTask(Task("Task 1", "Description for Task 1"));
    taskManager.addTask(Task("Task 2", "Description for Task 2"));

    // Example: Displaying tasks
    taskManager.displayTasks();

    // Example: Marking task as completed
    taskManager.markTaskCompleted(0);

    // Example: Deleting task
    taskManager.deleteTask(1);

    // Displaying updated tasks
    taskManager.displayTasks();

    // Sorting tasks by name and displaying
    taskManager.sortTasksByName();
    taskManager.displayTasks();

    // Saving tasks to file
    taskManager.saveTasksToFile("tasks.txt");

    return 0;
}
