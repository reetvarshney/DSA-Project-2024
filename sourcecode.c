#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure for queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Structure for student details
struct Student {
    int roll_number;
    char name[50];
    struct Student* next;
};

// Structure for room details
struct Room {
    int room_number;
    struct Student* students; // Linked list of students assigned to the room
    struct Room* next;
};

// Function prototypes
void push(struct Student** top, int roll_number, char name[]);
void pop(struct Student** top);
struct QueueNode* newNode(int data);
struct Queue* createQueue();
void enqueue(struct Queue* q, int data);
void dequeue(struct Queue* q);
void addStudentToRoom(struct Room* room, int roll_number, char name[]);
void displayRoomDetails(struct Room* room);
void displayMenu();

// Function implementations

void push(struct Student** top, int roll_number, char name[]) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    new_student->roll_number = roll_number;
    strcpy(new_student->name, name);
    new_student->next = *top;
    *top = new_student;
}

void pop(struct Student** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    struct Student* temp = *top;
    *top = (*top)->next;
    free(temp);
}

struct QueueNode* newNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, int data) {
    struct QueueNode* temp = newNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

void dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

void addStudentToRoom(struct Room* room, int roll_number, char name[]) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    new_student->roll_number = roll_number;
    strcpy(new_student->name, name);
    new_student->next = room->students;
    room->students = new_student;
}

void displayRoomDetails(struct Room* room) {
    printf("Room Number: %d\n", room->room_number);
    printf("Students:\n");
    struct Student* current = room->students;
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s\n", current->roll_number, current->name);
        current = current->next;
    }
}

void displayMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Push student onto stack\n");
    printf("2. Pop student from stack\n");
    printf("3. Enqueue student into queue\n");
    printf("4. Dequeue student from queue\n");
    printf("5. Add student to room\n");
    printf("6. Display room details\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Student* stack_top = NULL;
    struct Queue* meal_queue = createQueue();
    struct Room* room_list = NULL;

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int roll_number;
                char name[50];
                printf("Enter roll number and name of the student: ");
                scanf("%d %[^\n]s", &roll_number, name);
                push(&stack_top, roll_number, name);
                break;
            }
            case 2:
                pop(&stack_top);
                break;
            case 3: {
                int roll_number;
                printf("Enter roll number of the student to enqueue: ");
                scanf("%d", &roll_number);
                enqueue(meal_queue, roll_number);
                break;
            }
            case 4:
                dequeue(meal_queue);
                break;
            case 5: {
                int room_number, roll_number;
                char name[50];
                printf("Enter room number, roll number, and name of the student: ");
                scanf("%d %d %[^\n]s", &room_number, &roll_number, name);
                // Find the room
                struct Room* current_room = room_list;
                while (current_room != NULL && current_room->room_number != room_number) {
                    current_room = current_room->next;
                }
                if (current_room == NULL) {
                    printf("Room not found.\n");
                } else {
                    addStudentToRoom(current_room, roll_number, name);
                }
                break;
            }
            case 6:
                displayRoomDetails(room_list);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    // Free memory, if needed
    return 0;
}
