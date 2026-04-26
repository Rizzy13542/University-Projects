#include <iostream>
#include <cstring>
#include "Source_Queue.h"
using namespace std;

struct Task{
    int id;
    char description[100];
    int priority;
};

void add_task(Queue<Task> &processed,Task t){

    Queue<Task> aux;
    aux.enqueue(t);

    while(!processed.isEmpty()){
        aux.enqueue(processed.dequeue());
    }
    while(!aux.isEmpty()){
        processed.enqueue(aux.dequeue());
    }
}
bool pop_task(Queue<Task> &processed, Task &t){
    if (processed.isEmpty()){
        return 0;
    }
    t = processed.dequeue();

    return 1;
}
void print_task(Task t){
    cout << "ID: " << t.id << ", Description: " <<  t.description << ", Priority: " <<t.priority << endl;
}
bool check_duplicates(Queue<Task> waiting, Queue<Task> processed, int id){
    while(!waiting.isEmpty()){
        Task t = waiting.dequeue();
        if(t.id == id) return 1;
    }
    while(!processed.isEmpty()){
        Task t = processed.dequeue();
        if(t.id == id) return 1;
    }

    return 0;
}

void display_tasks(Queue<Task> tasks){
    if(tasks.isEmpty()){
        cout << "No tasks." << endl;
        return;
    }
    while(!tasks.isEmpty()){
        print_task(tasks.dequeue());
    }
}
void add_option(Queue<Task> &waiting,Queue<Task> &processed){
    Task t;
    cout << "Enter ID:";
    cin >> t.id;

    if(check_duplicates(waiting,processed,t.id)){
        cout << "ID:" << t.id << " already exists in the system!" << endl;
        return;
    }

    cout << "Enter description:";
    cin >> t.description;

    cout << "Enter Priority:";
    cin >> t.priority;

    if(t.priority < 1 || t.priority > 5){
        cout << "Priority value out of range [1,5]"<< endl;
        return;
    }

    waiting.enqueue(t);
    cout << "Task succesfully added!"<< endl;
}
void next_task(Queue<Task> &waiting, Queue<Task> &processed){
    if(waiting.isEmpty()){
        cout << "No waiting tasks." << endl;
    }
    else{
        Task t = waiting.dequeue();
        add_task(processed,t);
        cout << "Processed:" << endl;
        print_task(t);
    }
}
void undo_task(Queue<Task> &waiting, Queue<Task> &processed,int &undo_count){
    Task t;
    if(!pop_task(processed,t)){
        cout << "No processed tasks." << endl;
    }
    else{
        waiting.enqueue(t);
        undo_count++;
        cout << "Succesfully undid task: "<< endl;
        print_task(t);
    }
}
void display_waiting(Queue<Task> &waiting){
    if(waiting.isEmpty()){
        cout <<"No waiting tasks."<< endl;
    }
    else{
        cout << "Waiting tasks:"<< endl;
        display_tasks(waiting);
    }
}
void display_history(Queue<Task> &processed){
    if(processed.isEmpty()){
        cout << "No processed tasks." << endl;
    }
    else{
        cout << "Processed history:" << endl;
        display_tasks(processed);
    }
}
void process_k(Queue<Task> &waiting, Queue<Task> &processed){
    int k;
    cin >> k;
    if(waiting.isEmpty()){
        cout << "No waiting tasks." <<endl;
        return;
    }
    for(int i = 0;i < k;i++){
        if(waiting.isEmpty()){
            cout << "No more tasks" << endl;
            break;
        }

        Task t = waiting.dequeue();
        add_task(processed,t);
        cout << "Processed:" << endl;
        print_task(t);
    }
}
void search_task(Queue<Task> &waiting, Queue<Task> &processed){
    int id;
    cin >> id;

    if(check_duplicates(waiting,processed,id)){
        cout << "Task exists!" << endl;
    }
    else cout << "Task not found" << endl;
}
void display_stats(Queue<Task> waiting, Queue<Task> processed, int undo_count){
    int waiting_tasks = 0, processed_tasks = 0;
    while(!waiting.isEmpty()){
        waiting_tasks++;
        waiting.dequeue();
    }
    while(!processed.isEmpty()){
        processed_tasks++;
        processed.dequeue();
    }
    cout << "STATS:" << endl;
    cout << "Undo operations: " << undo_count << endl;
    cout << "Waiting tasks: " << waiting_tasks << endl;
    cout << "Processed tasks: " << processed_tasks << endl;
}
void Display(){
        cout << "Interactive Task Flow Manager"<<endl;
        cout << "-----------------------------"<<endl;
        cout << "-          Options          -"<<endl;
        cout << "-1.Add Task                 -"<<endl;
        cout << "-2.Process Next Task        -"<<endl;
        cout << "-3.Undo Last Proc. Task     -"<<endl;
        cout << "-4.Display Waiting Task     -"<<endl;
        cout << "-5.Display Proc. History    -"<<endl;
        cout << "-6.Process Next k tasks     -"<<endl;
        cout << "-7.Search Task by ID        -"<<endl;
        cout << "-8.Display Stats            -"<<endl;
        cout << "-0.Exit                     -"<<endl;
        cout << "-                           -"<<endl;
        cout << "- Pick Option:              -"<<endl;
        cout << "-----------------------------"<<endl;
}
int main()
{
    Queue<Task> waiting,processed;
    int option=-1,undo_count = 0;
    Display();
    while(option!=0){
        cin >> option;
        switch(option){
            case 1:
                add_option(waiting,processed);
                break;
            case 2:
                next_task(waiting,processed);
                break;
            case 3:
                undo_task(waiting,processed,undo_count);
                break;
            case 4:
                display_waiting(waiting);
                break;
            case 5:
                display_history(processed);
                break;
            case 6:
                process_k(waiting,processed);
                break;
            case 7:
                search_task(waiting,processed);
                break;
            case 8:
                display_stats(waiting,processed,undo_count);
                break;
        }
    }
}