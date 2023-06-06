#include <iostream>
#include "clui.h"
using namespace std;

struct deadline{
    int year,month,day,time;
};

struct task{
    char* title = new char[100];
    char* description = new char[400];
    int priority;
    deadline Deadline;
};

void menu(int row,int cols){
    clear_screen();

    cursor_to_pos(1,cols-75);
    change_color_rgb(255,102,0);
    cout << "  Welcome to your tasks!" << endl << endl;
    change_color_rgb(0,0,0);

    cursor_to_pos(3,cols-74);
    cout << "   1) Create a new task. " << endl;

    cursor_to_pos(4,cols-74);
    cout << "   2) Show my tasks. " << endl;

    cursor_to_pos(5,cols-74);
    cout << "   0) Exit. " << endl;

    cursor_to_pos(row-3,1);
    for(int i=0; i<cols; i++)
       cout << "-";
    flush();

    cout << " Please enter your chosen number: ";
}

void menu_of_showing_task(int row,int cols){

     cursor_to_pos(row-5,1);
     for(int i=0; i<cols; i++)
        cout << "-";
    flush();

    change_color_rgb(0,0,255);
    cout << " Hints:" << endl;
    cout << " Press 1 to delete this task. " << endl;
    cout << " Press 0 to back menu. " << endl;
    change_color_rgb(0,0,0);

    cout << " Please enter your number: ";
}

void enterance(task *n, int &index){
     clear_screen();

     cout << " Enter the title: ";
     cin.ignore();
     cin.getline( n[index].title , 100); 
     cout << endl;
     
     cout << " Enter the description: ";
     cin.getline( n[index].description , 400);
     cout << endl;

     cout << " Enter the priority: ";
     cin >> n[index].priority;
     cout << endl;

     cout << " Enter the year of deadline: ";
     cin >> n[index].Deadline.year;
     cout << endl;

     cout << " Enter the month of deadline: ";
     cin >> n[index].Deadline.month;
     cout << endl;

     cout << " Enter the day of deadline: ";
     cin >> n[index].Deadline.day;
     cout << endl;

     cout << " Enter the accurate time of deadline: ";
     cin >> n[index].Deadline.time;
     cout << endl; 
     
     index++;
     clear_screen();
     
     change_color_rgb(0,120,0);
     cout << " Your task added successfully !" << endl;
     change_color_rgb(0,0,0);
}

void bubbleSort(task tasks[],int size){

    for(int i=0; i<size; i++)
       for(int j=0; j<size - i - 1; j++)
           if(tasks[j+1].priority > tasks[j].priority)
              swap(tasks[j] , tasks[j + 1]);
}

void print(task* tasks,int size,int index){
    clear_screen();

    bubbleSort(tasks , size);

    if(index==0){

       for(int i=0; i<size; i++){
           
           change_color_rgb(128,0,128);
           cout << " Task " << i+1 << endl;
           change_color_rgb(0,0,0);

           cout << '\t' << "Title: " << tasks[i].title << endl;
           cout << '\t' << "Priority: " << tasks[i].priority << endl;
           cout << '\t' << "Deadline: " << tasks[i].Deadline.year << "." << tasks[i].Deadline.month << "." << tasks[i].Deadline.day << " at " << tasks[i].Deadline.time << " o'clock" << endl;
           
           for(int j=0; j<50; j++)
              cout << ".";
           flush();
           cout << endl;
        }

    }
    else{
           change_color_rgb(128,0,128);
           cout << " Task " << index << endl;
           change_color_rgb(0,0,0);
           index--;

           cout << '\t' << "Title: " << tasks[index].title << endl;
           cout << '\t' << "Description: " << tasks[index].description << endl;
           cout << '\t' << "Priority: " << tasks[index].priority << endl;
           cout << '\t' << "Deadline: " << tasks[index].Deadline.year << "." << tasks[index].Deadline.month << "." << tasks[index].Deadline.day << " at " << tasks[index].Deadline.time << " o'clock" << endl;
    }
    
}

int main(){

    init_clui();
    
    system("color 70");

    change_color_rgb(0,0,0);

    int row = get_window_rows();
    int cols = get_window_cols();
    
    menu(row,cols);

    int n,size=0;

    task* tasks = new task[1000];

    while(true){

         cin >> n;

         switch(n){

               case 0: 
                      clear_screen(); 
                    break;

               case 1: 
                      enterance(tasks,size);

                      delay(3000);

                      menu(row,cols); 
                    break;

               case 2: 
                      print(tasks,size,0);

                      cursor_to_pos(row-4,cols);
                      for(int i=0; i<cols; i++)
                          cout << "-";
                      flush();

                      cout << " Enter the number of the task that you want to see more details about it: ";

                      save_cursor();

                      change_color_rgb(0,0,255);

                      cout << endl << "Note: If you want to go back to menu, enter 0 .";

                      change_color_rgb(0,0,0);

                      restore_cursor();

                      int task_num;
                      cin >> task_num;

                      if(task_num==0)
                         menu(row,cols);

                      else {

                          print(tasks,size,task_num);

                          menu_of_showing_task(row,cols);

                          int choice;
                          cin >> choice;

                          if(choice == 1){
                              size--;

                              for(int i=task_num-1; i<size; i++)
                                  tasks[i] = tasks[i+1];

                              clear_screen();

                              change_color_rgb(0,120,0);

                              cout << " The task deleted successfully!" << endl;

                              change_color_rgb(0,0,0);

                              delay(4000);
                           }
                          // choice == 0
                          menu(row,cols);
                       }
                    break;

                default:
                         clear_screen();

                         change_color_rgb(255,0,0);

                         cout << " You entered a wrong number!" << endl << endl;

                         change_color_rgb(0,0,0);

                         cout << " Please enter a number between 0 and 2." << endl << endl;

                         change_color_rgb(0,0,255);

                         cout << " Note: wait 7 seconds to go back to menu." << endl;

                         change_color_rgb(0,0,0);

                         delay(7000);

                         menu(row,cols);

                        break;

           } // end of switch

           if(n==0) break;

       } // end of while

   for(int i=0; i<size; i++){
       delete[] tasks[i].title;
       delete[] tasks[i].description;
    }

   delete[] tasks;

   quit();

   return 0;
   
}