/* 
Synopsis:
The project aims to create a basic phone book directory with functionalities such as 
adding contacts, deleting contacts, displaying contacts, searching contacts, making calls, displaying call logs, and clearing call logs.
Data structures used: 
1. NODE structure - represents a contact in the book (contains name, number, rlink, and llink)
2. HEAD structure - represents the head of the linked list of contacts (contains noNodes and head)
3. Stack - Maintains call log
Functions used: 
init, new_node, insertEnd, insertFront, addContact, deleteFront, deleteContact, displayContacts, 
searchContact, callContact, displayCalls, clearCallLog.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
using namespace std;

typedef struct Node{
	int number;
    char name[30];
	struct Node* rlink;
	struct Node* llink;
}NODE;

typedef struct head{
    NODE* head;
    int noNodes;
}HEAD;

HEAD* init(){
    HEAD* temp = new HEAD;
    temp->head = NULL;
    temp->noNodes = 0;
    return temp;
}

NODE* new_node(int no, char name[]){
    NODE* temp = new NODE;
    if(temp != NULL){
        temp->number = no;
        strcpy(temp->name, name);
        temp->llink = NULL;
        temp->rlink = NULL;
    }
    return temp;
}

void insertEnd(HEAD* ptr, int no, char name[]){
    NODE* temp = new_node(no, name);

	if(ptr->head == NULL)
        ptr->head = temp;
    else{
        NODE* last = ptr->head;
        while(last->rlink != NULL)
            last = last->rlink;

        temp->llink = last;
        last->rlink = temp;
    }
    ptr->noNodes++;
}

void insertFront(HEAD* ptr, int no, char name[]){
    NODE* temp = new_node(no, name);

	if(ptr->head == NULL)
		ptr->head = temp;
    else{
        NODE* first = ptr->head;
        temp->rlink = first;
        first->llink = temp;
        ptr->head = temp;
    }
    ptr->noNodes++;
}

int check(HEAD* ptr, int no){
    NODE* cur = ptr->head;
    while(cur != NULL){
        if(cur->number == no)
            return 1;
        cur = cur->rlink;
    }
    return 0;
}

void addContact(HEAD* ptr, int no, char name[]){
    NODE* cur = ptr->head;
    if(ptr->head == NULL || strcmp(name, cur->name) < 0)
        insertFront(ptr, no, name);
    else if(strcmp(name, cur->name) == 0){
        cout << endl << "A contact with the same name already exists!" <<  endl;
        cout << "Please retry" <<  endl;
        return;
    }
    else{
        NODE* temp = new_node(no, name);
        NODE* prev = NULL;

        while(cur != NULL && strcmp(name, cur->name) > 0){
            prev = cur;
            cur = cur->rlink;
        }

        if(check(ptr, no)){
             cout << endl << "A contact with the same number already exists!" <<  endl;
            cout << "Please retry" <<  endl;
            return;
        }

        if(cur == NULL){
            if(strcmp(name, prev->name) == 0 ){
                cout << endl << "A contact with the same name already exists!" <<  endl;
                cout << "Please retry" <<  endl;
                return;
            }
            insertEnd(ptr, no, name);
        }
        else if(strcmp(name, cur->name) == 0){
            cout << endl << "A contact with the same name already exists!" <<  endl;
            cout << "Please retry" <<  endl;
            return;
        }
        else{
        prev->rlink = temp;
        temp->llink = prev;

        temp->rlink = cur;
        cur->llink = temp;
        }         
    }
    ptr->noNodes++;
}

void deleteFront(HEAD* ptr){
        NODE* cur = ptr->head;
        NODE* next = cur->rlink;

        if(next == NULL)
            ptr->head = NULL;
        else{
            ptr->head = next;
            next->llink = NULL;
        }
        delete cur;
        cout << "The contact has been deleted" << endl;
        ptr->noNodes--;
}

void deleteEnd(HEAD* ptr){
        NODE* cur = ptr->head;
        NODE* secondLast = NULL;

        while(cur->rlink->rlink != NULL)
            cur = cur->rlink;
        secondLast = cur;
        cur = cur->rlink;
    
        secondLast->rlink = NULL;
        delete cur;

        cout << "The contact has been deleted" << endl;
        ptr->noNodes--;
}

void deleteContact(HEAD* ptr, int no, char name[]){
    if(strcmp(name, "\0") == 0){
        NODE* prev = NULL;
        NODE* cur = ptr->head;
        NODE* next = NULL;
        while(cur != NULL){
            next = cur->rlink;
            if(no == cur->number){
                if(prev == NULL){
                    deleteFront(ptr);
                    ptr->noNodes--;
                    return;
                }
                else if(next == NULL){
                    deleteEnd(ptr);
                    ptr->noNodes--;
                    return;
                }
                else{
                    prev->rlink = next;
                    next->llink = prev;
                    delete cur;
                    cur = NULL;
                    cout << "The contact has been deleted" << endl;
                    ptr->noNodes--;
                    return;
                }
            }
            prev = cur;
            cur = cur->rlink;
        }
    }
    else{
        NODE* prev = NULL;
        NODE* cur = ptr->head;
        NODE* next = NULL;
        while(cur != NULL){
            next = cur->rlink;
            if(strcmp(cur->name, name) == 0){
                if(prev == NULL){
                    deleteFront(ptr);
                    ptr->noNodes--;
                    return;
                }
                else if(next == NULL){
                    deleteEnd(ptr);
                    ptr->noNodes--;
                    return;
                }
                else{
                    prev->rlink = next;
                    next->llink = prev;
                    delete cur;
                    cur = NULL;
                    cout << "The contact has been deleted" << endl;
                    ptr->noNodes--;
                    return;
                }
            }
            prev = cur;
            cur = cur->rlink;
        }
    }
    cout << "The contact is not present in your PhoneBook" << endl;
}

void displayContacts(){
    string myText;
    ifstream MyFile("Contacts.txt");
    while(getline(MyFile, myText))
        cout << "\t" << myText << endl;
    MyFile.close();
}

void updateFile(HEAD* ptr){
    ofstream MyFile("Contacts.txt");
    NODE* cur = ptr->head;
    int i = 1;
    while(cur != NULL){
        MyFile << i << ". Name: " << cur->name << "\t" << "Number: " << cur->number << endl;
        cur = cur->rlink;
        i++;
    }
    MyFile.close();
}

void searchContact(HEAD* ptr, int no, char name[]){
    if(strcmp(name, "\0") == 0){
        NODE* cur = ptr->head;
        while(cur != NULL){
            if(no == cur->number){
                cout << "The contact is present in your PhoneBook" << endl;
                cout << "Name: " << cur->name << endl << "Number: " << cur->number << endl << endl;
                return;
            }
            cur = cur->rlink;
        }
    }
    else{
        NODE* cur = ptr->head;
        while(cur != NULL){
            if(strcmp(name, cur->name) == 0){
                cout << "The contact is present in your PhoneBook" << endl;
                cout << "Name: " << cur->name << endl << "Number: " << cur->number << endl << endl;
                return;
            }
            cur = cur->rlink;
        }
    }
    cout << "The contact is not present in your PhoneBook" << endl;
}

NODE* callContact(HEAD* ptr, int no, char name[]){
    if(strcmp(name, "\0") == 0){
        NODE* cur = ptr->head;
        while(cur != NULL){
            if(no == cur->number){
                cout << cur->name << " is being called!" << endl;
                return cur;
            }
            cur = cur->rlink;
        }
    }
    else{
        NODE* cur = ptr->head;
        while(cur != NULL){
            if(strcmp(name, cur->name) == 0){
                cout << cur->name << " is being called!" << endl;
                return cur;
            }
            cur = cur->rlink;
        }
    }
    cout << "The contact is not present in your PhoneBook" << endl;
    return NULL;
}

void displayCalls(stack<NODE*> &calls){
    if(calls.empty())
        return;

    stack<NODE*> tempStack; 
    int j = 1;
    while(!calls.empty()){
        NODE* x = calls.top();
        cout << j << ". Name: " << calls.top()->name << endl << "Number: " << calls.top()->number << endl << endl;
        j++;
        tempStack.push(x); 
        calls.pop();
    }

    while(!tempStack.empty()){
        NODE* x = tempStack.top();
        calls.push(x);
        tempStack.pop();
    }
}

void clearCallLog(stack<NODE*> &calls){
    if(calls.empty()){
        return;
    }
    while (!calls.empty()) {
        NODE* topNode = calls.top();
        calls.pop();
        delete topNode;
    }
}

int main(){
    HEAD* Head = init();
    stack<NODE*> callLog;
    char nullString[] = "\0";
    cout << "---------------PhoneBook Directory---------------\n";
    while(1){
        int choice, no;
        char name[30];
        cout << "\t\t1. Add Contact\n\t\t2. Delete Contact\n\t\t3. Display Contacts\n\t\t4. Search Contact\n\t\t5. Call\n\t\t6. Display Call Log\n\t\t7. Clear call log\n\t\t8. Exit" << endl;
        cout << "-> What action would you like to perform? ";
        cin >> choice;
        switch(choice){
            case 1: cout << "-> Please enter the name: ";
                    cin >> name;
                    cout << "-> Please enter the number: ";
                    cin >> no;
                    addContact(Head, no, name);
                    updateFile(Head);
                    break;
            case 2: if(Head->head == NULL){
                        cout << "There are no saved contacts! Please try again" << endl;
                        break;
                    }
                    cout << "-> How would you like to delete your contact?" << endl << "1.Delete via Name\n2.Delete via Number" << endl;
                    cout << "-> Please enter your choice: ";
                    cin >> choice;
                    if(choice == 1){
                        cout << "-> Please enter the name: ";
                        cin >> name;
                        deleteContact(Head, -1, name);
                        updateFile(Head);
                    }
                    else if(choice == 2){
                        cout << "-> Please enter the number: ";
                        cin >> no;
                        deleteContact(Head, no, nullString);
                        updateFile(Head);
                    }
                    else
                        cout << "Invalid Choice!! Please try again" <<endl;
                    break;
            case 3: if(Head->head == NULL){
                        cout << "There are no saved contacts!" << endl;
                        break;
                    }
                    displayContacts();
                    break;
            case 4: if(Head->head == NULL){
                        cout << "There are no saved contacts! Please try again" << endl;
                        break;
                    }
                    cout << "-> How would you like to search for your contact?" << endl << "\t\t1. Search via Name\n\t\t2. Search via Number" << endl;
                    cout << "-> Please enter your choice: ";
                    cin >> choice;
                    if(choice == 1){
                        cout << "-> Please enter the name: ";
                        cin >> name;
                        searchContact(Head, -1, name);
                    }
                    else if(choice == 2){
                        cout << "-> Please enter the number: ";
                        cin >> no;
                        searchContact(Head, no, nullString);
                    }
                    else
                        cout << "Invalid Choice!! Please try again" <<endl;
                    break;
            case 5: if(Head->head == NULL){
                        cout << "There are no saved contacts! Please try again" << endl;
                        break;
                    }
                    cout << "-> How would you like to call your contact?" << endl << "\t\t1. Call via Name\n\t\t2. Call via Number" << endl;
                    cout << "-> Please enter your choice: ";
                    cin >> choice;
                    if(choice == 1){
                        cout << "-> Please enter the name: ";
                        cin >> name;
                        callLog.push(callContact(Head, -1, name));
                    }
                    else if(choice == 2){
                        cout << "-> Please enter the number: ";
                        cin >> no;
                        callLog.push(callContact(Head, no, nullString));
                    }
                    else
                        cout << "Invalid Choice!! Please try again" <<endl;
                    break;
            case 6: if(callLog.empty())
                        cout << "Call Log is empty!" << endl;
                    displayCalls(callLog);
                    break;
            case 7: if(callLog.empty())
                        cout << "Call Log is already empty!" << endl;
                    clearCallLog(callLog);
                    break;
            case 8: exit(-1);
            default: cout << "Invalid choice." << endl;
                     break;
        }
        cout << endl << "---------------PhoneBook Directory---------------" << endl;
    }
    return 0;
}
