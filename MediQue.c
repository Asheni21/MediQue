#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

// ===================== PATIENT MODULE =====================

int totalpatients = 0;
int queueCount = 3;
int emergencyCount = 2;

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char date[20];
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

void seedPatients();
void clearScreen();
void addPatient();
void deletePatient();
void updatePatient();
void patientRegistrationMenu();
struct PatientHistoryNode;
typedef struct PatientHistoryNode PatientHistoryNode;
typedef struct { PatientHistoryNode* head; PatientHistoryNode* tail; int size; } PatientHistoryList;
extern PatientHistoryList globalHistory;
void insertAtRear(PatientHistoryList* list, int id, char name[], int age, char gender[], char date[], char disease[]);

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void seedPatients() {
    patientCount = 3;
    patients[0] = (Patient){1, "John Doe",     30, "Male",   "Fever",    "01/01/2025"};
    patients[1] = (Patient){2, "Jane Silva",   25, "Female", "Cold",     "15/03/2025"};
    patients[2] = (Patient){3, "Kamal Perera", 40, "Male",   "Diabetes", "20/06/2025"};
    totalpatients = patientCount;
}


void printPatientRow(int pos, Patient* p) {
    printf("  [%d] ID:%-3d | %-18s | Age:%-3d | %-7s | %s\n",
           pos, p->id, p->name, p->age, p->gender, p->disease);
}


void displayPatients() {
    if (patientCount == 0) { printf("\n  No patient records available.\n"); return; }
    printf("\n  ==========================================\n");
    printf("    PATIENT LIST  (Original Order / Array)  \n");
    printf("  ==========================================\n");
    for (int i = 0; i < patientCount; i++) printPatientRow(i + 1, &patients[i]);
    printf("  ==========================================\n");
    printf("  Total: %d patient(s)\n", patientCount);
    printf("  ==========================================\n");
}


void searchPatient() {
    int option;
    printf("\n  Search by:  1. ID   2. Name   3. Disease\n  Choice: ");
    scanf("%d", &option); getchar();

    if (option == 1) {
        int id; printf("  Enter ID: "); scanf("%d", &id); getchar();
        int found = 0;
        for (int i = 0; i < patientCount; i++)
            if (patients[i].id == id) {
                printf("\n  [Linear Search] Found at index %d:\n", i);
                printPatientRow(i + 1, &patients[i]);
                found = 1; break;
            }
        if (!found) printf("\n  Not found.\n");

    } else if (option == 2) {
        char name[50]; printf("  Enter Name: "); fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < patientCount; i++)
            if (strcmp(patients[i].name, name) == 0) {
                printf("\n  [Linear Search] Found at index %d:\n", i);
                printPatientRow(i + 1, &patients[i]);
                found = 1;
            }
        if (!found) printf("\n  Not found.\n");

    } else if (option == 3) {
        char disease[50]; printf("  Enter Disease: "); fgets(disease, sizeof(disease), stdin);
        disease[strcspn(disease, "\n")] = 0;
        int found = 0;
        printf("\n  [Linear Search] Patients with disease '%s':\n", disease);
        for (int i = 0; i < patientCount; i++)
            if (strcmp(patients[i].disease, disease) == 0) {
                printPatientRow(i + 1, &patients[i]);
                found = 1;
            }
        if (!found) printf("  None found.\n");
    } else {
        printf("\n  Invalid option.\n");
    }
}


void addPatient() {
    if (patientCount >= MAX_PATIENTS) { printf("\n  Array is full! Max %d patients.\n", MAX_PATIENTS); return; }
    Patient p;
    p.id = totalpatients + 1;
    printf("\n  Generated ID  : %d\n", p.id);
    printf("  Enter Name    : "); fgets(p.name,    sizeof(p.name),    stdin); p.name[strcspn(p.name,"\n")]=0;
    printf("  Enter Age     : "); scanf("%d", &p.age); getchar();
    printf("  Enter Gender  : "); fgets(p.gender,  sizeof(p.gender),  stdin); p.gender[strcspn(p.gender,"\n")]=0;
    printf("  Enter Disease : "); fgets(p.disease, sizeof(p.disease), stdin); p.disease[strcspn(p.disease,"\n")]=0;
    printf("  Enter Date (DD/MM/YYYY) : "); fgets(p.date, sizeof(p.date), stdin); p.date[strcspn(p.date,"\n")]=0;
    patients[patientCount++] = p;
    totalpatients++;
    printf("\n  Patient added at array index [%d]. Total: %d\n", patientCount - 1, patientCount);
}


void updatePatient() {
    int id; printf("\n  Enter ID to update: "); scanf("%d", &id); getchar();
    for (int i = 0; i < patientCount; i++)
        if (patients[i].id == id) {
            printf("  Current record:\n");
            printPatientRow(i + 1, &patients[i]);
            printf("\n  Enter new Name    : "); fgets(patients[i].name,    sizeof(patients[i].name),    stdin); patients[i].name[strcspn(patients[i].name,"\n")]=0;
            printf("  Enter new Age     : "); scanf("%d", &patients[i].age); getchar();
            printf("  Enter new Gender  : "); fgets(patients[i].gender,  sizeof(patients[i].gender),  stdin); patients[i].gender[strcspn(patients[i].gender,"\n")]=0;
            printf("  Enter new Disease : "); fgets(patients[i].disease, sizeof(patients[i].disease), stdin); patients[i].disease[strcspn(patients[i].disease,"\n")]=0;
            printf("  Enter new Date (DD/MM/YYYY) : "); fgets(patients[i].date, sizeof(patients[i].date), stdin); patients[i].date[strcspn(patients[i].date,"\n")]=0;
            printf("\n  Patient updated successfully!\n");
            return;
        }
    printf("\n  Patient ID %d not found.\n", id);
}


void deletePatient() {
    int id; printf("\n  Enter ID to delete: "); scanf("%d", &id); getchar();
    for (int i = 0; i < patientCount; i++)
        if (patients[i].id == id) {

            for (int j = i; j < patientCount - 1; j++) patients[j] = patients[j + 1];
            patientCount--; totalpatients--;
            printf("\n  Deleted. Array shifted left. Total: %d\n", patientCount);
            return;
        }
    printf("\n  Patient ID %d not found.\n", id);
}


void sortByNameAZ() {
    if (patientCount == 0) { printf("\n  No records to sort.\n"); return; }
    Patient temp[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) temp[i] = patients[i];

    for (int i = 1; i < patientCount; i++) {
        Patient key = temp[i]; int j = i - 1;
        while (j >= 0 && strcmp(temp[j].name, key.name) > 0) { temp[j+1] = temp[j]; j--; }
        temp[j+1] = key;
    }
    printf("\n  ==========================================\n");
    printf("    SORTED BY NAME  (Insertion Sort A-Z)   \n");
    printf("  ==========================================\n");
    for (int i = 0; i < patientCount; i++) printPatientRow(i + 1, &temp[i]);
    printf("  ==========================================\n");
}


void sortByAgeBubble() {
    if (patientCount == 0) { printf("\n  No records to sort.\n"); return; }
    Patient temp[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) temp[i] = patients[i];

    for (int i = 0; i < patientCount - 1; i++)
        for (int j = 0; j < patientCount - i - 1; j++)
            if (temp[j].age > temp[j+1].age) {
                Patient t = temp[j]; temp[j] = temp[j+1]; temp[j+1] = t;
            }
    printf("\n  ==========================================\n");
    printf("    SORTED BY AGE   (Bubble Sort, Youngest) \n");
    printf("  ==========================================\n");
    for (int i = 0; i < patientCount; i++) printPatientRow(i + 1, &temp[i]);
    printf("  ==========================================\n");
}


void sortByIDSelection() {
    if (patientCount == 0) { printf("\n  No records to sort.\n"); return; }
    Patient temp[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) temp[i] = patients[i];

    for (int i = 0; i < patientCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < patientCount; j++)
            if (temp[j].id < temp[minIdx].id) minIdx = j;
        if (minIdx != i) { Patient t = temp[i]; temp[i] = temp[minIdx]; temp[minIdx] = t; }
    }
    printf("\n  ==========================================\n");
    printf("    SORTED BY ID    (Selection Sort)        \n");
    printf("  ==========================================\n");
    for (int i = 0; i < patientCount; i++) printPatientRow(i + 1, &temp[i]);
    printf("  ==========================================\n");
}


void countByGender() {
    int male = 0, female = 0, other = 0;
    for (int i = 0; i < patientCount; i++) {
        char g = patients[i].gender[0];
        if      (g == 'M' || g == 'm') male++;
        else if (g == 'F' || g == 'f') female++;
        else                            other++;
    }
    printf("\n  ==========================================\n");
    printf("    PATIENT COUNT BY GENDER                 \n");
    printf("  ==========================================\n");
    printf("  Male   : %d\n", male);
    printf("  Female : %d\n", female);
    printf("  Other  : %d\n", other);
    printf("  Total  : %d\n", patientCount);
    printf("  ==========================================\n");
}


void patientStatistics() {
    if (patientCount == 0) { printf("\n  No records available.\n"); return; }
    int totalAge = 0, minAge = patients[0].age, maxAge = patients[0].age;
    int minIdx = 0, maxIdx = 0;
    for (int i = 0; i < patientCount; i++) {
        totalAge += patients[i].age;
        if (patients[i].age < minAge) { minAge = patients[i].age; minIdx = i; }
        if (patients[i].age > maxAge) { maxAge = patients[i].age; maxIdx = i; }
    }
    printf("\n  ==========================================\n");
    printf("    PATIENT STATISTICS SUMMARY              \n");
    printf("  ==========================================\n");
    printf("  Total Patients  : %d\n", patientCount);
    printf("  Array Capacity  : %d  (slots used: %d/%d)\n", MAX_PATIENTS, patientCount, MAX_PATIENTS);
    printf("  Average Age     : %.1f\n", (float)totalAge / patientCount);
    printf("  Youngest        : %s (Age %d)\n", patients[minIdx].name, minAge);
    printf("  Oldest          : %s (Age %d)\n", patients[maxIdx].name, maxAge);
    printf("  ==========================================\n");

    int male = 0, female = 0, other = 0;
    for (int i = 0; i < patientCount; i++) {
        char g = patients[i].gender[0];
        if      (g == 'M' || g == 'm') male++;
        else if (g == 'F' || g == 'f') female++;
        else                            other++;
    }
    printf("  Male / Female / Other : %d / %d / %d\n", male, female, other);
    printf("  ==========================================\n");
}


void displayReverse() {
    if (patientCount == 0) { printf("\n  No records available.\n"); return; }
    printf("\n  ==========================================\n");
    printf("    PATIENT LIST  (Reverse / Last Added First)\n");
    printf("  ==========================================\n");
    for (int i = patientCount - 1; i >= 0; i--)
        printPatientRow(patientCount - i, &patients[i]);
    printf("  ==========================================\n");
}


void patientRegistrationMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n  +--------------------------------------------------+\n");
        printf("  |         PATIENT REGISTRATION  (Array)            |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  Array: fixed-size, index-based, O(1) access     |\n");
        printf("  |  Max capacity: %-3d patients                      |\n", MAX_PATIENTS);
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- DISPLAY -------------------------            |\n");
        printf("  |  1.  Display All  (Original Order)               |\n");
        printf("  |  2.  Display All  (Reverse Order)                |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- SEARCH --------------------------            |\n");
        printf("  |  3.  Linear Search (by ID / Name / Disease)      |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- INSERT / UPDATE / DELETE --------            |\n");
        printf("  |  4.  Add Patient                                  |\n");
        printf("  |  5.  Update Patient (All Fields)                  |\n");
        printf("  |  6.  Delete Patient (Shift Left)                  |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- SORT ----------------------------            |\n");
        printf("  |  7.  Sort by Name   (Insertion Sort A-Z)         |\n");
        printf("  |  8.  Sort by Age    (Bubble Sort)                 |\n");
        printf("  |  9.  Sort by ID     (Selection Sort)              |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- STATISTICS ----------------------            |\n");
        printf("  |  10. Count by Gender                              |\n");
        printf("  |  11. Statistics Summary                           |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                           |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  Patients registered: %-3d / %-3d                     \n", patientCount, MAX_PATIENTS);
        printf("  +--------------------------------------------------+\n");
        printf("  Enter your choice: "); scanf("%d", &choice); getchar();

        switch(choice) {
            case 1:  displayPatients();    break;
            case 2:  displayReverse();     break;
            case 3:  searchPatient();      break;
            case 4:
                addPatient();
                insertAtRear(&globalHistory,
                    patients[patientCount-1].id,
                    patients[patientCount-1].name,
                    patients[patientCount-1].age,
                    patients[patientCount-1].gender,
                    patients[patientCount-1].date,
                    patients[patientCount-1].disease);
                break;

            case 5:  updatePatient();      break;
            case 6:  deletePatient();      break;
            case 7:  sortByNameAZ();       break;
            case 8:  sortByAgeBubble();    break;
            case 9:  sortByIDSelection();  break;
            case 10: countByGender();      break;
            case 11: patientStatistics();  break;
            case 0:  break;
            default: printf("\n  Invalid choice. Enter 0-11.\n");
        }
        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }
    } while (choice != 0);
}

// ===================== DOCTOR MODULE =====================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct Doctor {
    int id;
    char name[50];
    int age;
    char gender[10];
    char specialization[50];
    int experience;
    char phone[15];
    struct Doctor* next;
};

struct Doctor* head = NULL;

 void insertDoctor(int id, char name[], int age, char gender[], char specialization[], int experience, char phone[]) {
    struct Doctor* newDoc = (struct Doctor*)malloc(sizeof(struct Doctor));

    newDoc->id = id;
    strcpy(newDoc->name, name);
    newDoc->age = age;
    strcpy(newDoc->gender, gender);
    strcpy(newDoc->specialization, specialization);
    newDoc->experience = experience;
    strcpy(newDoc->phone, phone);
    newDoc->next = NULL;

    if (head == NULL)
        head = newDoc;
    else {
        struct Doctor* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newDoc;
    }

    printf("\n   Doctor added successfully!\n");
}

 void displayDoctors() {
    struct Doctor* temp = head;

    if (!temp) {
        printf("\n  No doctors available.\n");
        return;
    }

    printf("\n  ==========================================\n");
    printf("    DOCTOR LIST (Linked List)               \n");
    printf("  ==========================================\n");

    while (temp) {
        printf("  ID:%-3d | %-18s | %-15s | Exp:%d\n",
               temp->id, temp->name,
               temp->specialization, temp->experience);
        temp = temp->next;
    }

    printf("  ==========================================\n");
}

 void searchDoctor() {
    int option;
    printf("\n  Search by: 1.ID  2.Name\n  Choice: ");
    scanf("%d", &option); getchar();

    struct Doctor* temp = head;
    int found = 0;

    if (option == 1) {
        int id;
        printf("  Enter ID: ");
        scanf("%d", &id); getchar();

        while (temp) {
            if (temp->id == id) {
                printf("\n  Found:\n");
                printf("  ID:%d | %s | %s\n", temp->id, temp->name, temp->specialization);
                found = 1;
                break;
            }
            temp = temp->next;
        }
    }
    else if (option == 2) {
        char name[50];
        printf("  Enter Name: ");
        fgets(name, 50, stdin);
        name[strcspn(name,"\n")] = 0;

        while (temp) {
            if (strcmp(temp->name, name) == 0) {
                printf("  ID:%d | %s | %s\n", temp->id, temp->name, temp->specialization);
                found = 1;
            }
            temp = temp->next;
        }
    }

    if (!found)
        printf("\n  Not found.\n");
}

 void deleteDoctor(int id) {
    struct Doctor *temp = head, *prev = NULL;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("\n  Doctor not found.\n");
        return;
    }

    if (!prev)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\n   Doctor deleted.\n");
}

 int countDoctors() {
    int count = 0;
    struct Doctor* temp = head;

    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

 void sortDoctors() {
    struct Doctor* sorted = NULL;
    struct Doctor* current = head;

    while (current) {
        struct Doctor* next = current->next;

        if (!sorted || strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Doctor* temp = sorted;

            while (temp->next && strcmp(temp->next->name, current->name) < 0)
                temp = temp->next;

            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    head = sorted;

    printf("\n   Doctors sorted by Name (A-Z)\n");

     displayDoctors();
}

 void countBySpecialization() {
    if (!head) {
        printf("\n  No doctors available.\n");
        return;
    }

    struct SpecCount {
        char specialization[50];
        int count;
    } specs[100];

    int specTotal = 0;
    struct Doctor* temp = head;

    while (temp) {
        int found = 0;
        for (int i = 0; i < specTotal; i++) {
            if (strcmp(specs[i].specialization, temp->specialization) == 0) {
                specs[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(specs[specTotal].specialization, temp->specialization);
            specs[specTotal].count = 1;
            specTotal++;
        }
        temp = temp->next;
    }

    printf("\n==========================================\n");
    printf("      DOCTOR COUNT BY SPECIALIZATION      \n");
    printf("==========================================\n");
    int totalDoctors = 0;
    for (int i = 0; i < specTotal; i++) {
        printf("%-15s : %d\n", specs[i].specialization, specs[i].count);
        totalDoctors += specs[i].count;
    }
    printf("Total           : %d\n", totalDoctors);
    printf("==========================================\n");
}

 void doctorStorageMenu() {
    int choice, id, age, exp;
    char name[50], gender[10], specialization[50], phone[15];

    do {
        printf("\n  +----------------------------------------+\n");
        printf("  |      DOCTOR MANAGEMENT SYSTEM          |\n");
        printf("  +----------------------------------------+\n");
        printf("  | 1. Add Doctor                         |\n");
        printf("  | 2. Display Doctors                    |\n");
        printf("  | 3. Search Doctor (ID / Name)          |\n");
        printf("  | 4. Delete Doctor                      |\n");
        printf("  | 5. Count Doctors                      |\n");
        printf("  | 6. Sort Doctors (Name A-Z)            |\n");
        printf("  | 7. Count by Specialization            |\n");
        printf("  | 0. Exit                               |\n");
        printf("  +----------------------------------------+\n");
        printf("  Enter choice: ");
        scanf("%d", &choice); getchar();

        switch(choice) {
            case 1:
                printf("  Enter ID: "); scanf("%d", &id); getchar();
                printf("  Enter Name: "); fgets(name, 50, stdin); name[strcspn(name,"\n")] = 0;
                printf("  Enter Age: "); scanf("%d", &age); getchar();
                printf("  Enter Gender: "); fgets(gender, 10, stdin); gender[strcspn(gender,"\n")] = 0;
                printf("  Enter Specialization: "); fgets(specialization, 50, stdin); specialization[strcspn(specialization,"\n")] = 0;
                printf("  Enter Experience: "); scanf("%d", &exp); getchar();
                printf("  Enter Phone: "); fgets(phone, 15, stdin); phone[strcspn(phone,"\n")] = 0;

                insertDoctor(id, name, age, gender, specialization, exp, phone);
                break;

            case 2:
                displayDoctors();
                break;

            case 3:
                searchDoctor();
                break;

            case 4:
                printf("  Enter ID to delete: ");
                scanf("%d", &id); getchar();
                deleteDoctor(id);
                break;

            case 5:
                printf("\n  Total Doctors: %d\n", countDoctors());
                break;

            case 6:
                sortDoctors();
                break;

            case 7:
                countBySpecialization();
                break;
        }

        if (choice != 0) {
            printf("\n  Press Enter...");
            getchar();
        }

    } while (choice != 0);
}



// ===================== PATIENT HISTORY MODULE (Doubly Linked List) =====================

typedef struct PatientHistoryNode {
    int  patientID;
    char patientName[50];
    int  age;
    char gender[10];
    char treatmentDate[20];
    char disease[100];
    struct PatientHistoryNode* prev;
    struct PatientHistoryNode* next;
} PatientHistoryNode;

PatientHistoryList globalHistory;
// ── Init ──────────────────────────────────────────────────────────────────────
void initializeHistory(PatientHistoryList* list) {
    list->head = list->tail = NULL;
    list->size = 0;
}

int isHistoryEmpty(PatientHistoryList* list) { return list->head == NULL; }

// ── Create node ───────────────────────────────────────────────────────────────
PatientHistoryNode* createHistoryNode(int id, char name[], int age, char gender[],
                                      char date[], char disease[]) {
    PatientHistoryNode* node = (PatientHistoryNode*)malloc(sizeof(PatientHistoryNode));
    node->patientID = id;
    strcpy(node->patientName, name);
    node->age = age;
    strcpy(node->gender,        gender);
    strcpy(node->treatmentDate, date);
    strcpy(node->disease,       disease);
    node->prev = node->next = NULL;
    return node;
}

// ── Insert at rear ────────────────────────────────────────────────────────────
void insertAtRear(PatientHistoryList* list, int id, char name[], int age,
                  char gender[], char date[], char disease[]) {
    PatientHistoryNode* node = createHistoryNode(id, name, age, gender, date, disease);
    if (list->tail == NULL) { list->head = list->tail = node; }
    else { list->tail->next = node; node->prev = list->tail; list->tail = node; }
    list->size++;
    printf("\n  [History] Record added at rear. Total records: %d\n", list->size);
}

// ── Insert in sorted order by patient ID ─────────────────────────────────────
void insertSorted(PatientHistoryList* list, int id, char name[], int age,
                  char gender[], char date[], char disease[]) {
    PatientHistoryNode* node = createHistoryNode(id, name, age, gender, date, disease);

    if (list->head == NULL) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
        list->size++;
        printf("\n  [History] Record added in sorted position. Total records: %d\n", list->size);
        return;
    }

    if (id <= list->head->patientID) {
        node->next       = list->head;
        node->prev       = NULL;          // new head has no prev
        list->head->prev = node;
        list->head       = node;
        list->size++;
        printf("\n  [History] Record added in sorted position. Total records: %d\n", list->size);
        return;
    }

    PatientHistoryNode* curr = list->head;
    while (curr->next != NULL && curr->next->patientID < id)
        curr = curr->next;

    node->next = curr->next;
    node->prev = curr;
    if (curr->next != NULL)
        curr->next->prev = node;
    else
        list->tail = node;
    curr->next = node;
    list->size++;
    printf("\n  [History] Record added in sorted position. Total records: %d\n", list->size);
}


// ── Traverse forward ──────────────────────────────────────────────────────────
// ── Traverse forward ──────────────────────────────────────────────────────────
void traverseForward(PatientHistoryList* list) {
    if (isHistoryEmpty(list)) { printf("\n  [History] No records found.\n"); return; }
    printf("  ===================================================================\n");
    printf("    Patient History (ID Ascending)\n");
    printf("  ===================================================================\n");
    printf("  %-4s  %-20s  %-4s  %-8s  %-12s  %s\n",
           "ID", "Name", "Age", "Gender", "Date", "Disease");
    printf("  -------------------------------------------------------------------\n");
    PatientHistoryNode* curr = list->head;
    int count = 1;
    while (curr) {
        printf("  %-4d  %-20s  %-4d  %-8s  %-12s  %s\n",
               curr->patientID, curr->patientName, curr->age,
               curr->gender, curr->treatmentDate, curr->disease);
        curr = curr->next;
        count++;
    }
    printf("  ===================================================================\n");
    printf("  Total Records : %d\n", list->size);
    printf("  ===================================================================\n");
}

// ── Traverse backward ─────────────────────────────────────────────────────────
void traverseBackward(PatientHistoryList* list) {
    if (isHistoryEmpty(list)) { printf("\n  [History] No records found.\n"); return; }
    printf("  ===================================================================\n");
    printf("    Patient History (ID Descending)\n");
    printf("  ===================================================================\n");
    printf("  %-4s  %-20s  %-4s  %-8s  %-12s  %s\n",
           "ID", "Name", "Age", "Gender", "Date", "Disease");
    printf("  -------------------------------------------------------------------\n");
    PatientHistoryNode* curr = list->tail;
    while (curr) {
        printf("  %-4d  %-20s  %-4d  %-8s  %-12s  %s\n",
               curr->patientID, curr->patientName, curr->age,
               curr->gender, curr->treatmentDate, curr->disease);
        curr = curr->prev;
    }
    printf("  ===================================================================\n");
    printf("  Total Records : %d\n", list->size);
    printf("  ===================================================================\n");
}

// ── Search by ID ──────────────────────────────────────────────────────────────
void searchByID(PatientHistoryList* list, int id) {
    PatientHistoryNode* curr = list->head;
    int found = 0, pos = 1;
    while (curr) {
        if (curr->patientID == id) {
            if (!found) {
                printf("\n  Results for Patient ID %d:\n", id);
                printf("  ===================================================================\n");
                printf("  %-4s  %-20s  %-4s  %-8s  %-12s  %s\n",
                       "ID", "Name", "Age", "Gender", "Date", "Disease");
                printf("  -------------------------------------------------------------------\n");
                found = 1;
            }
            printf("  %-4d  %-20s  %-4d  %-8s  %-12s  %s\n",
                   curr->patientID, curr->patientName, curr->age,
                   curr->gender, curr->treatmentDate, curr->disease);
        }
        curr = curr->next; pos++;
    }
    if (found) {
        printf("  ===================================================================\n");
    } else {
        printf("\n  [History] No record found with ID %d.\n", id);
    }
}

// ── Update record ─────────────────────────────────────────────────────────────
void updateRecord(PatientHistoryList* list, int id, char newDisease[], char newDate[]) {
    PatientHistoryNode* curr = list->head;
    int updated = 0;
    while (curr) {
        if (curr->patientID == id) {
            strcpy(curr->disease,       newDisease);
            strcpy(curr->treatmentDate, newDate);
            printf("\n  [History] Record ID %d updated.\n", id);
            updated = 1;
        }
        curr = curr->next;
    }

    // ── Also update the patients[] array ──────────────────────────────
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            strcpy(patients[i].disease, newDisease);
            strcpy(patients[i].date,    newDate);
            printf("\n  [History] patients[] array also updated for ID %d.\n", id);
            break;
        }
    }

    if (!updated) printf("\n  [History] No record found with ID %d.\n", id);
}

// ── Delete by patient ID ──────────────────────────────────────────────────────
void deleteByID(PatientHistoryList* list, int id) {
    PatientHistoryNode* curr = list->head;
    int deleted = 0;
    while (curr) {
        PatientHistoryNode* next = curr->next;
        if (curr->patientID == id) {
            if (curr->prev) curr->prev->next = curr->next; else list->head = curr->next;
            if (curr->next) curr->next->prev = curr->prev; else list->tail = curr->prev;
            free(curr); list->size--; deleted++;
        }
        curr = next;
    }
    if (deleted) {
        printf("\n  [History] %d record(s) with ID %d deleted.\n", deleted, id);

        // ── Also delete from patients[] array ──────────────────────────
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id == id) {
                for (int j = i; j < patientCount - 1; j++) patients[j] = patients[j + 1];
                patientCount--;
                totalpatients--;
                printf("\n  [History] patients[] array also updated.\n");
                break;
            }
        }
    }
    else printf("\n  [History] No record found with ID %d.\n", id);
}


// ── Sort by patient ID (insertion sort) ──────────────────────────────────────
void sortByPatientID(PatientHistoryList* list) {
    if (!list->head || !list->head->next) return;
    PatientHistoryNode* sorted = NULL;
    PatientHistoryNode* curr   = list->head;
    while (curr) {
        PatientHistoryNode* next = curr->next;
        curr->prev = curr->next = NULL;
        if (!sorted || curr->patientID <= sorted->patientID) {
            curr->next = sorted;
            if (sorted) sorted->prev = curr;
            sorted = curr;
        } else {
            PatientHistoryNode* t = sorted;
            while (t->next && t->next->patientID < curr->patientID) t = t->next;
            curr->next = t->next;
            if (t->next) t->next->prev = curr;
            t->next = curr; curr->prev = t;
        }
        curr = next;
    }
    list->head = sorted;
    PatientHistoryNode* tmp = list->head;
    while (tmp->next) tmp = tmp->next;
    list->tail = tmp;
    printf("\n  [History] Sorted by Patient ID.\n");
}

// ── Sort by date (insertion sort on DD/MM/YYYY strings) ──────────────────────
int compareDates(const char* a, const char* b) {
    // Compare YYYY then MM then DD
    int da,ma,ya, db,mb,yb;
    sscanf(a, "%d/%d/%d", &da, &ma, &ya);
    sscanf(b, "%d/%d/%d", &db, &mb, &yb);
    if (ya != yb) return ya - yb;
    if (ma != mb) return ma - mb;
    return da - db;
}

void sortByDate(PatientHistoryList* list) {
    if (!list->head || !list->head->next) return;

    PatientHistoryNode* sorted = NULL;
    PatientHistoryNode* curr   = list->head;

    while (curr) {
        PatientHistoryNode* next = curr->next;
        curr->prev = curr->next = NULL;

        if (!sorted || compareDates(curr->treatmentDate, sorted->treatmentDate) <= 0) {
            // curr is older or equal — insert at front
            curr->next = sorted;
            if (sorted) sorted->prev = curr;
            sorted = curr;
        } else {
            // find the right spot: walk while next node is still older than curr
            PatientHistoryNode* t = sorted;
            while (t->next && compareDates(t->next->treatmentDate, curr->treatmentDate) <= 0)
                t = t->next;
            // insert curr after t
            curr->next = t->next;
            curr->prev = t;
            if (t->next) t->next->prev = curr;
            t->next = curr;
        }
        curr = next;
    }

    list->head = sorted;
    list->head->prev = NULL;

    // Fix tail pointer
    PatientHistoryNode* tmp = list->head;
    while (tmp->next) tmp = tmp->next;
    list->tail = tmp;

    printf("\n  [History] Sorted by Date (Oldest to Newest).\n");
}

// ── Statistics ────────────────────────────────────────────────────────────────
void showStatistics(PatientHistoryList* list) {
    if (isHistoryEmpty(list)) { printf("\n  [History] No records.\n"); return; }

    int totalVisits = list->size;
    int uniqueCount = 0, males = 0, females = 0, others = 0, totalAge = 0;

    // Track seen IDs to avoid counting duplicates
    int seenIDs[MAX_PATIENTS];
    PatientHistoryNode* curr = list->head;
    while (curr) {
        int alreadySeen = 0;
        for (int i = 0; i < uniqueCount; i++)
            if (seenIDs[i] == curr->patientID) { alreadySeen = 1; break; }

        if (!alreadySeen) {
            seenIDs[uniqueCount++] = curr->patientID;
            totalAge += curr->age;
            if      (curr->gender[0]=='M' || curr->gender[0]=='m') males++;
            else if (curr->gender[0]=='F' || curr->gender[0]=='f') females++;
            else    others++;
        }
        curr = curr->next;
    }

    printf("\n  ==========================================\n");
    printf("    HISTORY STATISTICS                     \n");
    printf("  ==========================================\n");
    printf("  Total Visit Records : %d\n", totalVisits);
    printf("  Unique Patients     : %d\n", uniqueCount);
    printf("  Male Patients       : %d\n", males);
    printf("  Female Patients     : %d\n", females);
    printf("  Other/Unknown       : %d\n", others);
    printf("  Average Age         : %.1f\n", uniqueCount > 0 ? (float)totalAge / uniqueCount : 0);
    printf("  ==========================================\n");
}

// ── Print list helper (used after sort) ──────────────────────────────────────
void printHistoryList(PatientHistoryList* list) {
    printf("  %-4s  %-20s  %-4s  %-8s  %-12s  %s\n",
           "ID", "Name", "Age", "Gender", "Date", "Disease");
    printf("  -------------------------------------------------------------------\n");
    PatientHistoryNode* curr = list->head;
    while (curr) {
        printf("  %-4d  %-20s  %-4d  %-8s  %-12s  %s\n",
               curr->patientID, curr->patientName, curr->age,
               curr->gender, curr->treatmentDate, curr->disease);
        curr = curr->next;
    }
    printf("  ===================================================================\n");
    printf("  Total Records : %d\n", list->size);
    printf("  ===================================================================\n");
}

// ── Load patients from registration array into history ────────────────────────
void loadPatientsIntoHistory(PatientHistoryList* list) {
    // Clear existing history first
    PatientHistoryNode* curr = list->head;
    while (curr) {
        PatientHistoryNode* next = curr->next;
        free(curr);
        curr = next;
    }
    initializeHistory(list);

    for (int i = 0; i < patientCount; i++) {
        insertAtRear(list,
                     patients[i].id,
                     patients[i].name,
                     patients[i].age,
                     patients[i].gender,
                     patients[i].date,
                     patients[i].disease);
    }
    printf("\n  [History] Loaded %d patient(s) from registration.\n", patientCount);
}

// ── History sub-menu ──────────────────────────────────────────────────────────
void patientHistoryMenu() {

    int  choice, id, age, position;
    char name[50], gender[10], date[20], disease[100];

    do {
        clearScreen();
        printf("\n  +------------------------------------------+\n");
        printf("  |      PATIENT HISTORY MANAGEMENT          |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- INSERT --------------------------    |\n");
        printf("  |  1.  Add Visit Record (by Patient ID)    |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- VIEW ----------------------------    |\n");
        printf("  |  2.  Patient History (ID Ascending)      |\n");
        printf("  |  3.  Patient History (ID Descending)     |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- SEARCH --------------------------    |\n");
        printf("  |  4.  Search by Patient ID                |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- EDIT ----------------------------    |\n");
        printf("  |  5.  Update Record                       |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- DELETE --------------------------    |\n");
        printf("  |  6.  Delete by Patient ID                |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- SORT (Insertion Sort) -----------    |\n");
        printf("  |  7. Sort by Patient ID                   |\n");
        printf("  |  8. Sort by Date                         |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  -- EXTRA ---------------------------    |\n");
        printf("  |  9. Show Statistics Summary              |\n");
        printf("  |  10. Reload from Patient Registration    |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                   |\n");
        printf("  +------------------------------------------+\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {

            case 1: {
                printf("\n  Enter Patient ID to add visit record: ");
                scanf("%d", &id); getchar();

                // Check if ID exists in patients[] array
                int found = 0;
                for (int i = 0; i < patientCount; i++) {
                    if (patients[i].id == id) {
                        found = 1;
                        printf("  Enter new Disease           : ");
                        fgets(disease, 100, stdin); disease[strcspn(disease,"\n")]=0;
                        printf("  Enter Date (DD/MM/YYYY)     : ");
                        fgets(date, 20, stdin); date[strcspn(date,"\n")]=0;
                        insertSorted(&globalHistory, patients[i].id, patients[i].name,
                            patients[i].age, patients[i].gender, date, disease);
                        printf("\n  [History] Visit record added for %s (ID:%d).\n",
                            patients[i].name, id);
                        break;
                    }
                }
                if (!found)
                    printf("\n  [History] ERROR: Patient ID %d is not registered. "
                        "Please register the patient first.\n", id);
                break;
            }

            case 2:  traverseForward(&globalHistory);  break;
            case 3:  traverseBackward(&globalHistory); break;

            case 4:
                printf("\n  Enter Patient ID to search: "); scanf("%d", &id); getchar();
                searchByID(&globalHistory, id);
                break;

            case 5:
                printf("\n  Enter Patient ID to update  : "); scanf("%d", &id); getchar();
                printf("  Enter new Disease           : "); fgets(disease, 100, stdin); disease[strcspn(disease,"\n")]=0;
                printf("  Enter new Date (DD/MM/YYYY) : "); fgets(date, 20, stdin); date[strcspn(date,"\n")]=0;
                updateRecord(&globalHistory, id, disease, date);
                break;

            case 6:
                printf("\n  Enter Patient ID to delete: "); scanf("%d", &id); getchar();
                deleteByID(&globalHistory, id);
                break;

            case 7:
                if (isHistoryEmpty(&globalHistory)) { printf("\n  [History] No records found.\n"); break; }
                sortByPatientID(&globalHistory);
                printf("\n  ==========================================\n");
                printf("    PATIENT HISTORY  (Sorted by ID)        \n");
                printf("  ==========================================\n");
                printHistoryList(&globalHistory);
                break;

            case 8:
                if (isHistoryEmpty(&globalHistory)) { printf("\n  [History] No records found.\n"); break; }
                sortByDate(&globalHistory);
                printf("\n  ==========================================\n");
                printf("    PATIENT HISTORY  (Sorted by Date)      \n");
                printf("  ==========================================\n");
                printHistoryList(&globalHistory);
                break;

            case 9:  showStatistics(&globalHistory); break;

            case 10: loadPatientsIntoHistory(&globalHistory); break;

            case 0: printf("\n  [History] Returning to Main Menu...\n"); break;

            default: printf("\n  Invalid choice. Enter 0-10.\n");
        }

        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }

    } while (choice != 0);
}

// ===================== EMERGENCY HANDLING MODULE (Linked List Priority Queue) =====================
//
//  A Priority Queue serves patients by URGENCY, not arrival order.
//  Higher priority number = treated FIRST  (higher value = more urgent).
//
//  Priority Levels (higher = more critical):
//    3 = CRITICAL   (life-threatening  — e.g. cardiac arrest, stroke)
//    2 = SERIOUS    (needs urgent care — e.g. fracture, high fever)
//    1 = MODERATE   (semi-urgent       — e.g. infection, sprain)
//
//  Structure: singly linked list sorted in descending priority order
//    Each new node is inserted at the correct position so that the
//    front of the list always holds the highest-priority patient.
//    No array indices — nodes are dynamically allocated with malloc().
//
//  Key difference from array-based min-heap (previous version):
//    Min-Heap:       O(log n) insert via heapifyUp, index-based
//    Linked List PQ: O(n) insert via sorted traversal, pointer-based
//    Both guarantee that SERVE always picks the most critical patient.
//
//  Operations: INSERT (enqueue), SERVE (dequeue), PEEK,
//              DISPLAY, SEARCH, SORT BY AGE, SORT BY ID

// ── Node definition ───────────────────────────────────────────────────────────
typedef struct EmergencyPatient {
    int  id;
    char name[50];
    int  age;
    char gender[10];
    char disease[50];
    int  priority;               // 3=CRITICAL, 2=SERIOUS, 1=MODERATE
    struct EmergencyPatient* next;
} EmergencyPatient;

// Global linked-list front pointer (highest priority always at front)
EmergencyPatient* epFront = NULL;

// ── Priority label helper ─────────────────────────────────────────────────────
static const char* epPriorityLabel(int p) {
    if (p == 3) return "CRITICAL";
    if (p == 2) return "SERIOUS";
    return "MODERATE";
}

// ── INSERT (Enqueue with Priority) ───────────────────────────────────────────
//  Allocate a new node and walk the list to find the correct insertion
//  position (descending priority). Higher priority jumps ahead of lower.
void insertEmergency(int id, char name[], int age,
                     char gender[], char disease[], int priority) {
    EmergencyPatient* newPt = (EmergencyPatient*)malloc(sizeof(EmergencyPatient));

    newPt->id       = id;
    newPt->age      = age;
    newPt->priority = priority;
    newPt->next     = NULL;
    strcpy(newPt->name,    name);
    strcpy(newPt->gender,  gender);
    strcpy(newPt->disease, disease);

    // Insert at front if list is empty OR new node has higher/equal priority
    if (epFront == NULL || priority > epFront->priority) {
        newPt->next = epFront;
        epFront     = newPt;
    } else {
        // Walk until we find the right spot (next node has lower priority)
        EmergencyPatient* temp = epFront;
        while (temp->next != NULL && temp->next->priority >= priority)
            temp = temp->next;
        newPt->next  = temp->next;
        temp->next   = newPt;
    }

    emergencyCount++;
    printf("\n  [Emergency] %s (ID:%d) added as [%s]. Emergency count: %d\n",
           name, id, epPriorityLabel(priority), emergencyCount);
}

// ── SERVE (Dequeue — highest priority = front of list) ───────────────────────
//  Remove and display the patient at the front (always the most critical).
void serveEmergency() {
    if (epFront == NULL) {
        printf("\n  [Emergency] No emergency patients waiting.\n");
        return;
    }

    EmergencyPatient* temp = epFront;

    printf("\n  ==========================================\n");
    printf("    EMERGENCY PATIENT NOW BEING SERVED     \n");
    printf("  ==========================================\n");
    printf("  ID       : %d\n",  temp->id);
    printf("  Name     : %s\n",  temp->name);
    printf("  Age      : %d\n",  temp->age);
    printf("  Gender   : %s\n",  temp->gender);
    printf("  Disease  : %s\n",  temp->disease);
    printf("  Priority : [%s] (Level %d)\n",
           epPriorityLabel(temp->priority), temp->priority);
    printf("  ==========================================\n");

    epFront = epFront->next;   // advance front pointer
    free(temp);                // release memory
    emergencyCount--;
    printf("  Emergency patients remaining: %d\n", emergencyCount);
}

// ── PEEK — view front patient without removing ────────────────────────────────
void peekEmergency() {
    if (epFront == NULL) {
        printf("\n  [Emergency] Queue is empty.\n");
        return;
    }

    printf("\n  [Emergency] Next to be served (highest priority):\n");
    printf("  ==========================================\n");
    printf("  ID       : %d\n",  epFront->id);
    printf("  Name     : %s\n",  epFront->name);
    printf("  Age      : %d\n",  epFront->age);
    printf("  Gender   : %s\n",  epFront->gender);
    printf("  Disease  : %s\n",  epFront->disease);
    printf("  Priority : [%s] (Level %d)\n",
           epPriorityLabel(epFront->priority), epFront->priority);
    printf("  ==========================================\n");
}

// ── DISPLAY — traverse and print entire queue ─────────────────────────────────
void displayEmergency() {
    if (epFront == NULL) {
        printf("\n  [Emergency] No emergency patients in queue.\n");
        return;
    }

    EmergencyPatient* temp = epFront;
    int pos = 1;

    printf("\n  ==========================================\n");
    printf("    EMERGENCY QUEUE  (Highest Priority First)\n");
    printf("  ==========================================\n");
    printf("  %-4s %-18s %-4s %-8s %-14s %s\n",
           "Pos", "Name", "Age", "Gender", "Disease", "Priority");
    printf("  ---------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("  %-4d %-18s %-4d %-8s %-14s [%s]\n",
               pos++, temp->name, temp->age, temp->gender,
               temp->disease, epPriorityLabel(temp->priority));
        temp = temp->next;
    }

    printf("  ==========================================\n");
    printf("  Total emergency patients: %d\n", emergencyCount);
    printf("  ==========================================\n");
}

// ── SEARCH — find patient by ID (linear scan) ────────────────────────────────
void searchEmergency(int id) {
    EmergencyPatient* temp = epFront;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\n  [Emergency] Patient found:\n");
            printf("  ID       : %d\n  Name     : %s\n  Age      : %d\n"
                   "  Gender   : %s\n  Disease  : %s\n  Priority : [%s] (Level %d)\n",
                   temp->id, temp->name, temp->age,
                   temp->gender, temp->disease,
                   epPriorityLabel(temp->priority), temp->priority);
            return;
        }
        temp = temp->next;
    }

    printf("\n  [Emergency] Patient ID %d not found in emergency queue.\n", id);
}

// ── SORT BY AGE (Bubble Sort on a temporary array copy) ──────────────────────
//  The linked list itself is NOT modified — we copy nodes into an array,
//  bubble-sort by age, then display. This leaves the priority order intact.
void sortEmergencyByAge() {
    if (epFront == NULL) {
        printf("\n  [Emergency] Queue is empty.\n");
        return;
    }

    // Copy linked list nodes into a local array for sorting
    EmergencyPatient arr[100];
    EmergencyPatient* temp = epFront;
    int n = 0;

    while (temp != NULL && n < 100) {
        arr[n++] = *temp;
        temp = temp->next;
    }

    // Bubble sort — O(n²) — ascending age
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].age > arr[j + 1].age) {
                EmergencyPatient t = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = t;
            }

    printf("\n  ==========================================\n");
    printf("    EMERGENCY QUEUE  (Sorted by Age)       \n");
    printf("  ==========================================\n");
    printf("  %-4s %-18s %-4s %-8s %-14s %s\n",
           "Pos", "Name", "Age", "Gender", "Disease", "Priority");
    printf("  ---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
        printf("  %-4d %-18s %-4d %-8s %-14s [%s]\n",
               i + 1, arr[i].name, arr[i].age, arr[i].gender,
               arr[i].disease, epPriorityLabel(arr[i].priority));

    printf("  ==========================================\n");
}

// ── SORT BY ID (Insertion Sort on linked list — returns new sorted head) ──────
//  Builds a brand-new sorted list by re-linking nodes in ascending ID order.
//  The global epFront is NOT modified; a local sorted pointer is used for display.
EmergencyPatient* sortEmergencyByIDHelper(EmergencyPatient* head) {
    EmergencyPatient* sorted = NULL;

    while (head != NULL) {
        EmergencyPatient* current = head;
        head = head->next;

        if (sorted == NULL || current->id < sorted->id) {
            current->next = sorted;
            sorted        = current;
        } else {
            EmergencyPatient* temp = sorted;
            while (temp->next != NULL && temp->next->id < current->id)
                temp = temp->next;
            current->next = temp->next;
            temp->next    = current;
        }
    }

    return sorted;
}

void displaySortedByID() {
    if (epFront == NULL) {
        printf("\n  [Emergency] Queue is empty.\n");
        return;
    }

    // Work on a shallow copy list — do NOT free these nodes (they belong to epFront chain)
    // We copy data into a local array then sort, to avoid corrupting the live queue
    EmergencyPatient arr[100];
    EmergencyPatient* temp = epFront;
    int n = 0;

    while (temp != NULL && n < 100) {
        arr[n++] = *temp;
        temp = temp->next;
    }

    // Insertion sort by ID
    for (int i = 1; i < n; i++) {
        EmergencyPatient key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    printf("\n  ==========================================\n");
    printf("    EMERGENCY QUEUE  (Sorted by ID)        \n");
    printf("  ==========================================\n");
    printf("  %-4s %-18s %-4s %-8s %-14s %s\n",
           "Pos", "Name", "Age", "Gender", "Disease", "Priority");
    printf("  ---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
        printf("  %-4d %-18s %-4d %-8s %-14s [%s]\n",
               i + 1, arr[i].name, arr[i].age, arr[i].gender,
               arr[i].disease, epPriorityLabel(arr[i].priority));

    printf("  ==========================================\n");
}

// ── Emergency sub-menu ────────────────────────────────────────────────────────
void emergencyMenu() {
    // Reset the global linked list and counter on each entry
    // (Free any leftover nodes from a previous session)
    while (epFront != NULL) {
        EmergencyPatient* tmp = epFront;
        epFront = epFront->next;
        free(tmp);
    }
    emergencyCount = 0;

    // Seed two emergency patients matching the initial emergencyCount display
    insertEmergency(101, "Nimal Fernando", 55, "Male",   "Cardiac Arrest", 3);
    insertEmergency(102, "Sithara Perera", 34, "Female", "Stroke",         2);

    int  choice, id, age, priority;
    char name[50], gender[10], disease[50];

    do {
        clearScreen();
        printf("\n  +----------------------------------------------------+\n");
        printf("  |  EMERGENCY HANDLING  (Linked List Priority Queue)  |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |                                                    |\n");
        printf("  |  Patients are served by URGENCY, not arrival order.|\n");
        printf("  |                                                    |\n");
        printf("  |  Priority Levels (higher number = more urgent):    |\n");
        printf("  |    3 = CRITICAL  (life-threatening)                |\n");
        printf("  |    2 = SERIOUS   (urgent care needed)              |\n");
        printf("  |    1 = MODERATE  (semi-urgent)                     |\n");
        printf("  |                                                    |\n");
        printf("  |  How the linked list PQ works:                     |\n");
        printf("  |    Insert: Kamal(1), Nimal(3), Sunil(2)            |\n");
        printf("  |    List:   [Nimal(3)] -> [Sunil(2)] -> [Kamal(1)]  |\n");
        printf("  |    Serve:  Nimal(3) -> Sunil(2) -> Kamal(1)        |\n");
        printf("  |    CRITICAL always jumps to the front!             |\n");
        printf("  |                                                    |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- CORE OPERATIONS ------------------             |\n");
        printf("  |  1.  INSERT  — Add Emergency Patient               |\n");
        printf("  |  2.  SERVE   — Treat Highest Priority Patient      |\n");
        printf("  |  3.  PEEK    — View Most Critical (No Remove)      |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- VIEW & SEARCH --------------------             |\n");
        printf("  |  4.  DISPLAY — Show All Emergency Patients         |\n");
        printf("  |  5.  SEARCH  — Find Patient by ID                  |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- SORT ----------------------------              |\n");
        printf("  |  6.  Sort by Age  (Bubble Sort)                    |\n");
        printf("  |  7.  Sort by ID   (Insertion Sort)                 |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                             |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  Emergency patients waiting: %-3d                      \n", emergencyCount);
        printf("  +----------------------------------------------------+\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {

            case 1:
                printf("\n  -- INSERT: Add Emergency Patient --\n");
                printf("  Enter Patient ID         : "); scanf("%d", &id); getchar();
                printf("  Enter Patient Name       : "); fgets(name, 50, stdin); name[strcspn(name,"\n")]=0;
                printf("  Enter Age                : "); scanf("%d", &age); getchar();
                printf("  Enter Gender (M/F/Other) : "); fgets(gender, 10, stdin); gender[strcspn(gender,"\n")]=0;
                printf("  Enter Disease            : "); fgets(disease, 50, stdin); disease[strcspn(disease,"\n")]=0;
                printf("  Enter Priority Level     :\n");
                printf("    3 = CRITICAL   2 = SERIOUS   1 = MODERATE\n");
                printf("  Choice: "); scanf("%d", &priority); getchar();
                if (priority < 1 || priority > 3)
                    printf("\n  Invalid priority! Must be 1, 2, or 3.\n");
                else
                    insertEmergency(id, name, age, gender, disease, priority);
                break;

            case 2: serveEmergency();   break;
            case 3: peekEmergency();    break;
            case 4: displayEmergency(); break;

            case 5:
                printf("\n  Enter Patient ID to search: "); scanf("%d", &id); getchar();
                searchEmergency(id);
                break;

            case 6: sortEmergencyByAge(); break;
            case 7: displaySortedByID();  break;

            case 0:
                printf("\n  [Emergency] Returning to Main Menu...\n");
                break;

            default:
                printf("\n  Invalid choice. Enter 0-7.\n");
        }

        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }

    } while (choice != 0);
}

// ===================== NORMAL QUEUE MODULE (FIFO) =====================

#define QUEUE_MAX 100

typedef struct {
    int  id;
    char name[50];
    int  age;
    char gender[10];
    char disease[50];
} QueuePatient;

typedef struct {
    QueuePatient data[QUEUE_MAX];
    int front;
    int rear;
    int size;
} NormalQueue;

void initQueue(NormalQueue* q) {
    q->front = 0;
    q->rear  = -1;
    q->size  = 0;
}

int isQueueEmpty(NormalQueue* q) { return q->size == 0; }
int isQueueFull (NormalQueue* q) { return q->size == QUEUE_MAX; }

// Enqueue — add patient to the rear of the waiting line
void enqueue(NormalQueue* q, int id, char name[], int age, char gender[], char disease[]) {
    if (isQueueFull(q)) { printf("\n  [Queue] Queue is full! Cannot admit more patients.\n"); return; }
    q->rear = (q->rear + 1) % QUEUE_MAX;
    q->data[q->rear].id  = id;
    strcpy(q->data[q->rear].name,    name);
    q->data[q->rear].age = age;
    strcpy(q->data[q->rear].gender,  gender);
    strcpy(q->data[q->rear].disease, disease);
    q->size++;
    queueCount++;
    printf("\n  [Queue] %s has joined the waiting line. Position: %d\n", name, q->size);
}

// Dequeue — serve the patient at the front (FIFO)
void dequeue(NormalQueue* q) {
    if (isQueueEmpty(q)) { printf("\n  [Queue] No patients waiting.\n"); return; }
    QueuePatient p = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    q->size--;
    queueCount--;
    printf("\n  ==========================================\n");
    printf("    PATIENT NOW BEING SERVED               \n");
    printf("  ==========================================\n");
    printf("  ID      : %d\n", p.id);
    printf("  Name    : %s\n", p.name);
    printf("  Age     : %d\n", p.age);
    printf("  Gender  : %s\n", p.gender);
    printf("  Disease : %s\n", p.disease);
    printf("  ==========================================\n");
    printf("  Patients remaining in queue: %d\n", q->size);
    printf("  ==========================================\n");
}

// Peek — view who is next without removing them
void peekQueue(NormalQueue* q) {
    if (isQueueEmpty(q)) { printf("\n  [Queue] Queue is empty.\n"); return; }
    QueuePatient p = q->data[q->front];
    printf("\n  [Queue] Next patient to be served:\n");
    printf("  >> ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
           p.id, p.name, p.age, p.gender, p.disease);
}

// Display all patients currently waiting
void displayQueue(NormalQueue* q) {
    if (isQueueEmpty(q)) { printf("\n  [Queue] No patients currently waiting.\n"); return; }
    printf("\n  ==========================================\n");
    printf("    CURRENT WAITING LINE (Front -> Rear)   \n");
    printf("  ==========================================\n");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % QUEUE_MAX;
        printf("  [%d] ID: %d | Name: %-15s | Age: %d | Gender: %-6s | Disease: %s\n",
               i + 1,
               q->data[idx].id,   q->data[idx].name,
               q->data[idx].age,  q->data[idx].gender,
               q->data[idx].disease);
    }
    printf("  ==========================================\n");
    printf("  Total waiting: %d\n", q->size);
    printf("  ==========================================\n");
}

// Load normal patients from the registration array into the queue
void loadPatientsIntoQueue(NormalQueue* q) {
    initQueue(q);
    queueCount = 0;
    for (int i = 0; i < patientCount; i++) {
        enqueue(q, patients[i].id, patients[i].name,
                patients[i].age, patients[i].gender, patients[i].disease);
    }
    printf("\n  [Queue] Loaded %d patient(s) from Patient Registration.\n", q->size);
}

void normalQueueMenu() {
    NormalQueue q;
    initQueue(&q);

    // Pre-load registered patients
    for (int i = 0; i < patientCount; i++) {
        enqueue(&q, patients[i].id, patients[i].name,
                patients[i].age, patients[i].gender, patients[i].disease);
    }

    int  choice, id, age;
    char name[50], gender[10], disease[50];

    do {
        clearScreen();
        printf("\n  +--------------------------------------------------+\n");
        printf("  |           NORMAL QUEUE  (FIFO)                   |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |                                                  |\n");
        printf("  |  Your queue is the waiting line for normal       |\n");
        printf("  |  patients — first come, first served.            |\n");
        printf("  |                                                  |\n");
        printf("  |  Flow:  Patient Registered -> IF Normal          |\n");
        printf("  |         -> Join Queue -> Doctor Free             |\n");
        printf("  |         -> Dequeue -> Send to Doctor             |\n");
        printf("  |                                                  |\n");
        printf("  |  Example:  Kamal -> Nimal -> Sunil               |\n");
        printf("  |            Queue: [ Kamal, Nimal, Sunil ]        |\n");
        printf("  |            Serve: Kamal first, then Nimal        |\n");
        printf("  |                                                  |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- ENQUEUE -------------------------            |\n");
        printf("  |  1.  Add Patient to Queue (Rear)                |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- DEQUEUE -------------------------            |\n");
        printf("  |  2.  Serve Next Patient (Front)                 |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- VIEW ----------------------------            |\n");
        printf("  |  3.  View Waiting Line                          |\n");
        printf("  |  4.  Peek at Next Patient                       |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- EXTRA ---------------------------            |\n");
        printf("  |  5.  Reload from Patient Registration           |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                          |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  Patients waiting: %-3d                              \n", q.size);
        printf("  +--------------------------------------------------+\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {

            case 1:
                printf("\n  -- Add Patient to Queue --\n");
                printf("  Enter Patient ID        : "); scanf("%d", &id); getchar();
                printf("  Enter Patient Name      : "); fgets(name, 50, stdin); name[strcspn(name,"\n")]=0;
                printf("  Enter Age               : "); scanf("%d", &age); getchar();
                printf("  Enter Gender (M/F/Other): "); fgets(gender, 10, stdin); gender[strcspn(gender,"\n")]=0;
                printf("  Enter Disease           : "); fgets(disease, 50, stdin); disease[strcspn(disease,"\n")]=0;
                enqueue(&q, id, name, age, gender, disease);
                break;

            case 2:
                dequeue(&q);
                break;

            case 3:
                displayQueue(&q);
                break;

            case 4:
                peekQueue(&q);
                break;

            case 5:
                loadPatientsIntoQueue(&q);
                break;

            case 0:
                printf("\n  [Queue] Returning to Main Menu...\n");
                break;

            default:
                printf("\n  Invalid choice. Enter 0-5.\n");
        }

        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }

    } while (choice != 0);
}

// ===================== PATIENT FOLLOW-UP CYCLE MODULE (Circular Linked List) =====================
//
//  followup.c  -  Patient Follow-Up Cycle System
//  Member 5 | IN 1111 Data Structures & Algorithms I
//
//  KEY DIFFERENCE from lecture's singly linked list (slide 12):
//    Lecture:  WHILE temp != NULL DO
//    Ours:     do { ... } while (temp != head)
//
//  This is because the last node points BACK to head,
//  so NULL never exists — we stop when we lap back around.
//
//  A Circular Linked List has NO NULL end — the last node's next always
//  points back to head, forming a continuous loop.
//
//  Purpose in HMS: patients sit in a follow-up cycle. The system processes
//  the NEXT patient in round-robin rotation — fair scheduling.
//
//  Circle:  head -> [P1] -> [P2] -> [P3] -> (back to P1)
//  current pointer tracks whose follow-up is next.

#define PRIORITY_HIGH   1
#define PRIORITY_MEDIUM 2
#define PRIORITY_LOW    3

#define STATUS_PENDING   0
#define STATUS_COMPLETED 1
#define STATUS_MISSED    2

typedef struct FollowUp {
    int  patientId;
    char patientName[50];
    char condition[50];
    char followUpDate[12];
    int  priority;    // 1=HIGH, 2=MEDIUM, 3=LOW
    int  status;      // 0=PENDING, 1=COMPLETED, 2=MISSED
    int  visitCount;
    struct FollowUp* next;
} FollowUp;

// ── helpers ──────────────────────────────────────────────────────────────────
static const char* fuPriorityLabel(int p) {
    if (p == PRIORITY_HIGH)   return "HIGH  ";
    if (p == PRIORITY_MEDIUM) return "MEDIUM";
    return "LOW   ";
}

static const char* fuStatusLabel(int s) {
    if (s == STATUS_COMPLETED) return "Completed";
    if (s == STATUS_MISSED)    return "Missed   ";
    return "Pending  ";
}

// Find the last node whose next == head (needed for insert + delete)
static FollowUp* fuGetLastNode(FollowUp* head) {
    FollowUp* temp = head;
    while (temp->next != head)
        temp = temp->next;
    return temp;
}

// ── CREATE NODE ──────────────────────────────────────────────────────────────
//  Lecture ref: CREATE_NODE (slide 5)
//  Difference:  newNode->next = newNode  (circular from birth)
FollowUp* createFollowUp(int id, char* name, char* condition,
                          char* date, int priority) {
    FollowUp* node = (FollowUp*)malloc(sizeof(FollowUp));
    if (!node) { printf("  [ERROR] Memory allocation failed.\n"); exit(1); }
    node->patientId  = id;
    node->priority   = priority;
    node->status     = STATUS_PENDING;
    node->visitCount = 0;
    strcpy(node->patientName,  name);
    strcpy(node->condition,    condition);
    strcpy(node->followUpDate, date);
    node->next = node;    // points to itself — already circular
    return node;
}

// ── INSERT AT REAR ───────────────────────────────────────────────────────────
//  Lecture ref: INSERT_REAR (slide 11)
//  Difference:  last->next = head  instead of  last->next = NULL
void addFollowUp(FollowUp** head, int id, char* name,
                 char* condition, char* date, int priority) {
    // duplicate ID check
    if (*head != NULL) {
        FollowUp* t = *head;
        do {
            if (t->patientId == id) {
                printf("  [ERROR] Patient ID %d already in follow-up cycle.\n", id);
                return;
            }
            t = t->next;
        } while (t != *head);
    }

    FollowUp* node = createFollowUp(id, name, condition, date, priority);

    if (*head == NULL) {
        *head = node;               // first node points to itself
    } else {
        FollowUp* last = fuGetLastNode(*head);
        last->next  = node;         // old last points to new node
        node->next  = *head;        // new node points back to head — circle restored
    }
    printf("  Added: %-20s (ID:%d | %s | Priority:%s | Due:%s)\n",
           name, id, condition, fuPriorityLabel(priority), date);
}

// ── TRAVERSE ─────────────────────────────────────────────────────────────────
//  Lecture ref: TRAVERSE (slide 12)
//  Difference:  do-while (temp != head)  instead of  while (temp != NULL)
//  MUST use do-while — temp starts AT head, so plain while exits immediately
void traverseFollowUps(FollowUp* head) {
    if (head == NULL) {
        printf("  [INFO] Follow-up cycle is empty.\n");
        return;
    }
    printf("\n  %-5s %-20s %-16s %-12s %-8s %-10s %s\n",
           "ID", "Name", "Condition", "Due Date", "Priority", "Status", "Visits");
    printf("  %s\n",
           "--------------------------------------------------------------------------------");
    FollowUp* temp = head;
    do {
        printf("  %-5d %-20s %-16s %-12s %-8s %-10s %d\n",
               temp->patientId,
               temp->patientName,
               temp->condition,
               temp->followUpDate,
               fuPriorityLabel(temp->priority),
               fuStatusLabel(temp->status),
               temp->visitCount);
        temp = temp->next;
    } while (temp != head);    // stop when we lap back to head
    printf("  %s\n",
           "--------------------------------------------------------------------------------");
}

// ── SEARCH ───────────────────────────────────────────────────────────────────
//  Lecture ref: SEARCH (slide 13)
//  Difference:  same do-while stop condition
void searchFollowUp(FollowUp* head, int id) {
    if (head == NULL) { printf("  [INFO] Cycle is empty.\n"); return; }
    FollowUp* temp = head;
    int pos = 1;
    do {
        if (temp->patientId == id) {
            printf("  Found at position %d:\n", pos);
            printf("  ID:%-5d | Name:%-20s | Condition:%-16s\n",
                   temp->patientId, temp->patientName, temp->condition);
            printf("  Date:%-12s | Priority:%-8s | Status:%-10s | Visits:%d\n",
                   temp->followUpDate, fuPriorityLabel(temp->priority),
                   fuStatusLabel(temp->status), temp->visitCount);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);
    printf("  [INFO] Patient ID %d not found in follow-up cycle.\n", id);
}

// ── UPDATE ───────────────────────────────────────────────────────────────────
//  Lecture ref: UPDATE (slide 14)
//  Use case: reschedule a follow-up date or change priority
void updateFollowUp(FollowUp* head, int id,
                    char* newDate, int newPriority) {
    if (head == NULL) { printf("  [INFO] Cycle is empty.\n"); return; }
    FollowUp* temp = head;
    do {
        if (temp->patientId == id) {
            strcpy(temp->followUpDate, newDate);
            temp->priority = newPriority;
            printf("  Updated Patient %d: new date=%s | priority=%s\n",
                   id, newDate, fuPriorityLabel(newPriority));
            return;
        }
        temp = temp->next;
    } while (temp != head);
    printf("  [INFO] Patient ID %d not found.\n", id);
}

// ── DELETE ───────────────────────────────────────────────────────────────────
//  Lecture ref: DELETE_FRONT/MIDDLE/REAR (slides 17-22)
//  Three cases handled: only node | head node | any other node
//  current pointer is kept valid after deletion
void deleteFollowUp(FollowUp** head, FollowUp** current, int id) {
    if (*head == NULL) { printf("  [INFO] Cycle is empty.\n"); return; }

    FollowUp* curr = *head;
    FollowUp* prev = NULL;
    FollowUp* last = fuGetLastNode(*head);

    // Case 1: only one node in the list
    if ((*head)->next == *head) {
        if ((*head)->patientId == id) {
            printf("  Removed: %s (ID:%d). Cycle is now empty.\n",
                   (*head)->patientName, id);
            free(*head);
            *head = NULL; *current = NULL;
        } else {
            printf("  [INFO] Patient ID %d not found.\n", id);
        }
        return;
    }

    // Find the node and its predecessor
    do {
        if (curr->patientId == id) break;
        prev = curr;
        curr = curr->next;
    } while (curr != *head);

    if (curr->patientId != id) {
        printf("  [INFO] Patient ID %d not found.\n", id);
        return;
    }

    // Case 2: deleting the head node
    if (curr == *head) {
        last->next = (*head)->next;       // last node skips to new head
        if (*current == *head) *current = (*head)->next;
        printf("  Removed: %s (ID:%d)\n", curr->patientName, id);
        *head = (*head)->next;
        free(curr);
        return;
    }

    // Case 3: middle or last node
    prev->next = curr->next;
    if (*current == curr) *current = curr->next;  // keep current valid
    printf("  Removed: %s (ID:%d)\n", curr->patientName, id);
    free(curr);
}

// ── PROCESS NEXT FOLLOW-UP (round-robin) ─────────────────────────────────────
//  Moves current to the next patient — the circular structure
//  wraps automatically with zero extra code (no boundary check).
void processNextFollowUp(FollowUp** current) {
    if (*current == NULL) {
        printf("  [ERROR] No patients in follow-up cycle.\n");
        return;
    }
    printf("  Processing follow-up:\n");
    printf("  Patient:  %s (ID:%d)\n", (*current)->patientName, (*current)->patientId);
    printf("  Due:      %s\n",          (*current)->followUpDate);
    printf("  Priority: %s\n",          fuPriorityLabel((*current)->priority));
    printf("  Condition:%s\n",          (*current)->condition);
    (*current)->visitCount++;
    *current = (*current)->next;    // advance — wraps to head automatically
    printf("  [Next up: %s]\n",         (*current)->patientName);
}

// ── MARK STATUS ──────────────────────────────────────────────────────────────
//  Lets user mark a follow-up as completed or missed
void fuMarkStatus(FollowUp* head, int id, int status) {
    if (head == NULL) { printf("  [INFO] Cycle is empty.\n"); return; }
    FollowUp* temp = head;
    do {
        if (temp->patientId == id) {
            temp->status = status;
            printf("  Patient %d status set to: %s\n", id, fuStatusLabel(status));
            return;
        }
        temp = temp->next;
    } while (temp != head);
    printf("  [INFO] Patient ID %d not found.\n", id);
}

// ── INSERTION SORT BY PRIORITY ────────────────────────────────────────────────
//  Sorting algorithm: Insertion Sort
//  Sort key: priority (1=High first, 3=Low last)
//  Strategy: swap DATA inside nodes (not pointers) — safe for CLL
void fuSortByPriority(FollowUp* head) {
    if (head == NULL || head->next == head) return;

    int n = 0;
    FollowUp* t = head;
    do { n++; t = t->next; } while (t != head);

    FollowUp* ptrs[n];
    t = head;
    for (int k = 0; k < n; k++) { ptrs[k] = t; t = t->next; }

    for (int i = 1; i < n; i++) {
        int  kId   = ptrs[i]->patientId;
        int  kPri  = ptrs[i]->priority;
        int  kStat = ptrs[i]->status;
        int  kVis  = ptrs[i]->visitCount;
        char kName[50], kCond[50], kDate[12];
        strcpy(kName, ptrs[i]->patientName);
        strcpy(kCond, ptrs[i]->condition);
        strcpy(kDate, ptrs[i]->followUpDate);

        int j = i - 1;
        while (j >= 0 && ptrs[j]->priority > kPri) {
            ptrs[j+1]->patientId  = ptrs[j]->patientId;
            ptrs[j+1]->priority   = ptrs[j]->priority;
            ptrs[j+1]->status     = ptrs[j]->status;
            ptrs[j+1]->visitCount = ptrs[j]->visitCount;
            strcpy(ptrs[j+1]->patientName,  ptrs[j]->patientName);
            strcpy(ptrs[j+1]->condition,    ptrs[j]->condition);
            strcpy(ptrs[j+1]->followUpDate, ptrs[j]->followUpDate);
            j--;
        }
        ptrs[j+1]->patientId  = kId;
        ptrs[j+1]->priority   = kPri;
        ptrs[j+1]->status     = kStat;
        ptrs[j+1]->visitCount = kVis;
        strcpy(ptrs[j+1]->patientName,  kName);
        strcpy(ptrs[j+1]->condition,    kCond);
        strcpy(ptrs[j+1]->followUpDate, kDate);
    }
    printf("  Sorted by priority: HIGH -> MEDIUM -> LOW\n");
}

// ── SORT BY DUE DATE (Insertion Sort) ────────────────────────────────────────
//  Date format: DD-MM-YYYY  converted to integer YYYYMMDD for comparison
static int fuDateToInt(const char* date) {
    int dd   = (date[0]-'0')*10 + (date[1]-'0');
    int mm   = (date[3]-'0')*10 + (date[4]-'0');
    int yyyy = (date[6]-'0')*1000 + (date[7]-'0')*100
             + (date[8]-'0')*10   + (date[9]-'0');
    return yyyy * 10000 + mm * 100 + dd;
}

void fuSortByDate(FollowUp* head) {
    if (head == NULL || head->next == head) {
        printf("  [INFO] Nothing to sort.\n");
        return;
    }

    int n = 0;
    FollowUp* t = head;
    do { n++; t = t->next; } while (t != head);

    FollowUp* ptrs[n];
    t = head;
    for (int k = 0; k < n; k++) { ptrs[k] = t; t = t->next; }

    for (int i = 1; i < n; i++) {
        int  kId      = ptrs[i]->patientId;
        int  kPri     = ptrs[i]->priority;
        int  kStat    = ptrs[i]->status;
        int  kVis     = ptrs[i]->visitCount;
        int  kDateInt = fuDateToInt(ptrs[i]->followUpDate);
        char kName[50], kCond[50], kDate[12];
        strcpy(kName, ptrs[i]->patientName);
        strcpy(kCond, ptrs[i]->condition);
        strcpy(kDate, ptrs[i]->followUpDate);

        int j = i - 1;
        while (j >= 0 && fuDateToInt(ptrs[j]->followUpDate) > kDateInt) {
            ptrs[j+1]->patientId  = ptrs[j]->patientId;
            ptrs[j+1]->priority   = ptrs[j]->priority;
            ptrs[j+1]->status     = ptrs[j]->status;
            ptrs[j+1]->visitCount = ptrs[j]->visitCount;
            strcpy(ptrs[j+1]->patientName,  ptrs[j]->patientName);
            strcpy(ptrs[j+1]->condition,    ptrs[j]->condition);
            strcpy(ptrs[j+1]->followUpDate, ptrs[j]->followUpDate);
            j--;
        }
        ptrs[j+1]->patientId  = kId;
        ptrs[j+1]->priority   = kPri;
        ptrs[j+1]->status     = kStat;
        ptrs[j+1]->visitCount = kVis;
        strcpy(ptrs[j+1]->patientName,  kName);
        strcpy(ptrs[j+1]->condition,    kCond);
        strcpy(ptrs[j+1]->followUpDate, kDate);
    }
    printf("  Sorted by due date: earliest first.\n");
}

// ── FILTER: PENDING ONLY ─────────────────────────────────────────────────────
void showPendingOnly(FollowUp* head) {
    if (head == NULL) { printf("  [INFO] Cycle is empty.\n"); return; }
    printf("\n  --- Pending Follow-Ups ---\n");
    FollowUp* temp = head;
    int found = 0;
    do {
        if (temp->status == STATUS_PENDING) {
            printf("  ID:%-5d %-20s Due:%-12s Priority:%s\n",
                   temp->patientId, temp->patientName,
                   temp->followUpDate, fuPriorityLabel(temp->priority));
            found++;
        }
        temp = temp->next;
    } while (temp != head);
    if (!found) printf("  No pending follow-ups.\n");
}

// ── REPORT ───────────────────────────────────────────────────────────────────
//  Sorts by priority then displays full table
void showFollowUpReport(FollowUp* head) {
    if (head == NULL) { printf("  [INFO] No data.\n"); return; }
    printf("\n  === Follow-Up Cycle Report (sorted by priority) ===\n");
    fuSortByPriority(head);
    traverseFollowUps(head);
}

// ── DOCTOR ASSIGNMENT MENU (now Follow-Up Cycle) ─────────────────────────────
void doctorAssignmentMenu() {
    FollowUp* fuHead    = NULL;
    FollowUp* fuCurrent = NULL;

    // Seed three follow-up records to match existing system status display
    addFollowUp(&fuHead, patients[0].id, patients[0].name, patients[0].disease, "10-04-2025", PRIORITY_HIGH);
    addFollowUp(&fuHead, patients[1].id, patients[1].name, patients[1].disease, "15-04-2025", PRIORITY_MEDIUM);
    addFollowUp(&fuHead, patients[2].id, patients[2].name, patients[2].disease, "20-04-2025", PRIORITY_LOW);
    fuCurrent = fuHead;

    int  choice, id, priority, status;
    char name[50], condition[50], date[12], newDate[12];

    do {
        clearScreen();
        printf("\n  +----------------------------------------------------+\n");
        printf("  |   PATIENT FOLLOW-UP CYCLE (Circular Linked List)  |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  Patients in a CIRCLE — no NULL end.               |\n");
        printf("  |  Each call processes the next patient in the loop. |\n");
        printf("  |                                                    |\n");
        printf("  |  KEY DIFFERENCE from lecture (slide 12):           |\n");
        printf("  |    Lecture:  WHILE temp != NULL DO                 |\n");
        printf("  |    Ours:     do { } while (temp != head)           |\n");
        printf("  |  (NULL never exists — last node points to head)    |\n");
        printf("  |                                                    |\n");
        printf("  |  Circle: P1 -> P2 -> P3 -> (back to P1)           |\n");
        printf("  |  Round-robin: P1 processed, then P2, then P3...    |\n");
        printf("  |                                                    |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- CORE OPERATIONS -----------------              |\n");
        printf("  |  1.  Add Patient to Follow-Up Cycle (Rear)        |\n");
        printf("  |  2.  Process Next Follow-Up (Round-Robin)         |\n");
        printf("  |  3.  Display Full Cycle                           |\n");
        printf("  |  4.  Search Patient by ID                         |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- EDIT / DELETE -------------------              |\n");
        printf("  |  5.  Update Follow-Up (Date & Priority)           |\n");
        printf("  |  6.  Mark Status (Completed / Missed)             |\n");
        printf("  |  7.  Remove Patient from Cycle                    |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  -- SORT & FILTER -------------------              |\n");
        printf("  |  8.  Sort by Priority (HIGH first)                |\n");
        printf("  |  9.  Sort by Due Date (Earliest first)            |\n");
        printf("  |  10. Show Pending Follow-Ups Only                 |\n");
        printf("  |  11. Full Report (sorted by priority)             |\n");
        printf("  +----------------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                            |\n");
        printf("  +----------------------------------------------------+\n");
        if (fuCurrent != NULL)
            printf("  Next follow-up : %-20s (ID:%d)         \n",
                   fuCurrent->patientName, fuCurrent->patientId);
        else
            printf("  Follow-up cycle is empty.                          \n");
        printf("  +----------------------------------------------------+\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {

            case 1:
                printf("\n  Enter Patient ID        : "); scanf("%d", &id); getchar();
                printf("  Enter Patient Name      : "); fgets(name, 50, stdin); name[strcspn(name,"\n")]=0;
                printf("  Enter Condition         : "); fgets(condition, 50, stdin); condition[strcspn(condition,"\n")]=0;
                printf("  Enter Due Date (DD-MM-YYYY): "); fgets(date, 12, stdin); date[strcspn(date,"\n")]=0;
                printf("  Priority: 1=HIGH  2=MEDIUM  3=LOW  > ");
                scanf("%d", &priority); getchar();
                if (priority < 1 || priority > 3) { printf("  Invalid priority.\n"); break; }
                addFollowUp(&fuHead, id, name, condition, date, priority);
                if (fuCurrent == NULL) fuCurrent = fuHead;
                break;

            case 2:
                processNextFollowUp(&fuCurrent);
                break;

            case 3:
                traverseFollowUps(fuHead);
                break;

            case 4:
                printf("\n  Enter Patient ID to search: "); scanf("%d", &id); getchar();
                searchFollowUp(fuHead, id);
                break;

            case 5:
                printf("\n  Enter Patient ID to update  : "); scanf("%d", &id); getchar();
                printf("  Enter new Due Date (DD-MM-YYYY): "); fgets(newDate, 12, stdin); newDate[strcspn(newDate,"\n")]=0;
                printf("  New Priority: 1=HIGH  2=MEDIUM  3=LOW  > ");
                scanf("%d", &priority); getchar();
                if (priority < 1 || priority > 3) { printf("  Invalid priority.\n"); break; }
                updateFollowUp(fuHead, id, newDate, priority);
                break;

            case 6:
                printf("\n  Enter Patient ID         : "); scanf("%d", &id); getchar();
                printf("  Status: 1=Completed  2=Missed  > ");
                scanf("%d", &status); getchar();
                if (status < 1 || status > 2) { printf("  Invalid status.\n"); break; }
                fuMarkStatus(fuHead, id, status);
                break;

            case 7:
                printf("\n  Enter Patient ID to remove: "); scanf("%d", &id); getchar();
                deleteFollowUp(&fuHead, &fuCurrent, id);
                break;

            case 8:
                fuSortByPriority(fuHead);
                traverseFollowUps(fuHead);
                break;

            case 9:
                fuSortByDate(fuHead);
                traverseFollowUps(fuHead);
                break;

            case 10:
                showPendingOnly(fuHead);
                break;

            case 11:
                showFollowUpReport(fuHead);
                break;

            case 0:
                printf("\n  [Follow-Up] Returning to Main Menu...\n");
                break;

            default:
                printf("\n  Invalid choice. Enter 0-11.\n");
        }

        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }

    } while (choice != 0);
}

// ===================== TREATMENT STACK MODULE (Linked List Stack - LIFO) =====================
//
//  Based on IN 1111 Lecture 10 — Linked List implementation of a Stack.
//  Purpose in HMS: tracks the most recently treated patients so the doctor
//  can quickly review the last case, undo a discharge, or re-check records.
//  Operations: IS_EMPTY, PEEK, PUSH, POP, DISPLAY_STACK
//

// ── Node & Stack structs ──────────────────────────────────────────────────────
typedef struct StackNode {
    int  patientID;
    char patientName[50];
    int  age;
    char gender[10];
    char disease[50];
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;    // pointer to the top of the stack
    int size;
} PatientStack;

// ── INITIALIZED_STACK ─────────────────────────────────────────────────────────
void initStack(PatientStack* s) {
    s->top  = NULL;
    s->size = 0;
}

// ── IS_EMPTY ──────────────────────────────────────────────────────────────────
int isStackEmpty(PatientStack* s) {
    return s->top == NULL;   // returns TRUE if stack is empty
}

// ── CREATE_NODE ───────────────────────────────────────────────────────────────
StackNode* createStackNode(int id, char name[], int age, char gender[], char disease[]) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->patientID = id;
    strcpy(newNode->patientName, name);
    newNode->age = age;
    strcpy(newNode->gender,  gender);
    strcpy(newNode->disease, disease);
    newNode->next = NULL;
    return newNode;
}

// ── PEEK ──────────────────────────────────────────────────────────────────────
// Returns (prints) the top element without removing it
void peekStack(PatientStack* s) {
    if (isStackEmpty(s)) {
        printf("\n  [Stack] Empty Stack — nothing to peek at.\n");
        return;
    }
    // return stack.top.data  (as per lecture slide 10)
    printf("\n  [Stack] TOP of Stack:\n");
    printf("  ==========================================\n");
    printf("  ID      : %d\n",  s->top->patientID);
    printf("  Name    : %s\n",  s->top->patientName);
    printf("  Age     : %d\n",  s->top->age);
    printf("  Gender  : %s\n",  s->top->gender);
    printf("  Disease : %s\n",  s->top->disease);
    printf("  ==========================================\n");
}

// ── PUSH ──────────────────────────────────────────────────────────────────────
// Insert a new patient record onto the top of the stack
void pushStack(PatientStack* s, int id, char name[], int age, char gender[], char disease[]) {
    StackNode* newNode = createStackNode(id, name, age, gender, disease);

    if (isStackEmpty(s)) {
        // stack.top <- newNode  (empty case)
        s->top = newNode;
    } else {
        // newNode.next <- stack.top  then  stack.top <- newNode
        newNode->next = s->top;
        s->top = newNode;
    }
    s->size++;
    printf("\n  [Stack] PUSH — %s (ID:%d) pushed onto stack. Stack size: %d\n",
           name, id, s->size);
}

// ── POP ───────────────────────────────────────────────────────────────────────
// Remove and display the top element from the stack
void popStack(PatientStack* s) {
    if (isStackEmpty(s)) {
        printf("\n  [Stack] Empty Stack — nothing to pop.\n");
        return;
    }
    // temp <- stack.top
    StackNode* temp = s->top;

    printf("\n  [Stack] POP — Removing top record:\n");
    printf("  ==========================================\n");
    printf("  ID      : %d\n",  temp->patientID);
    printf("  Name    : %s\n",  temp->patientName);
    printf("  Age     : %d\n",  temp->age);
    printf("  Gender  : %s\n",  temp->gender);
    printf("  Disease : %s\n",  temp->disease);
    printf("  ==========================================\n");

    // stack.top <- stack.top.next  then  DEALLOCATE temp
    s->top = s->top->next;
    free(temp);
    s->size--;
    printf("  Stack size after pop: %d\n", s->size);
}

// ── DISPLAY_STACK ─────────────────────────────────────────────────────────────
// Print all elements from top to bottom
void displayStack(PatientStack* s) {
    if (isStackEmpty(s)) {
        printf("\n  [Stack] Empty Stack — no records to display.\n");
        return;
    }
    printf("\n  ==========================================\n");
    printf("    TREATMENT STACK  (Top -> Bottom / LIFO) \n");
    printf("  ==========================================\n");
    printf("  Last treated patient is at the TOP.\n");
    printf("  ------------------------------------------\n");
    StackNode* temp = s->top;   // temp <- stack.top
    int pos = 1;
    while (temp != NULL) {      // WHILE temp != NULL DO
        printf("  [%d] %s ID:%d | Age:%d | Gender:%s | Disease:%s\n",
               pos++, temp->patientName, temp->patientID,
               temp->age, temp->gender, temp->disease);
        temp = temp->next;      // temp <- temp.next
    }
    printf("  ==========================================\n");
    printf("  Total records in stack: %d\n", s->size);
    printf("  ==========================================\n");
}

// ── Load patients from registration into stack ────────────────────────────────
void loadPatientsIntoStack(PatientStack* s) {
    // Clear existing stack first
    while (!isStackEmpty(s)) popStack(s);
    printf("\n  [Stack] Loading patients from Patient Registration...\n");
    // Push each patient (first patient ends up at bottom, last at top — LIFO)
    for (int i = 0; i < patientCount; i++) {
        pushStack(s, patients[i].id, patients[i].name,
                  patients[i].age, patients[i].gender, patients[i].disease);
    }
    printf("\n  [Stack] Loaded %d patient(s). Most recently registered is now on top.\n",
           s->size);
}

// ── Stack sub-menu ────────────────────────────────────────────────────────────
void stackMenu() {
    PatientStack s;
    initStack(&s);

    // Pre-load registered patients
    for (int i = 0; i < patientCount; i++) {
        pushStack(&s, patients[i].id, patients[i].name,
                  patients[i].age, patients[i].gender, patients[i].disease);
    }

    int  choice, id, age;
    char name[50], gender[10], disease[50];

    do {
        clearScreen();
        printf("\n  +--------------------------------------------------+\n");
        printf("  |     TREATMENT STACK  (Linked List / LIFO)        |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |                                                  |\n");
        printf("  |  A stack stores patient treatment records in     |\n");
        printf("  |  LIFO order — Last In, First Out.                |\n");
        printf("  |                                                  |\n");
        printf("  |  Like a pile of plates:                          |\n");
        printf("  |   * PUSH  -> place new record on TOP             |\n");
        printf("  |   * POP   -> remove record from TOP              |\n");
        printf("  |   * PEEK  -> view TOP without removing           |\n");
        printf("  |                                                  |\n");
        printf("  |  Real-world use: undo last discharge,            |\n");
        printf("  |  review last treated patient instantly.          |\n");
        printf("  |                                                  |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- CORE OPERATIONS -----------------            |\n");
        printf("  |  1.  PUSH  — Add Patient Record (Top)           |\n");
        printf("  |  2.  POP   — Remove Top Record                  |\n");
        printf("  |  3.  PEEK  — View Top Record                    |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- DISPLAY -------------------------            |\n");
        printf("  |  4.  DISPLAY STACK (Top to Bottom)              |\n");
        printf("  |  5.  IS EMPTY Check                             |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  -- EXTRA ---------------------------            |\n");
        printf("  |  6.  Reload from Patient Registration           |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  |  0.  Back to Main Menu                          |\n");
        printf("  +--------------------------------------------------+\n");
        printf("  Stack size: %-3d  (top = most recently treated)     \n", s.size);
        printf("  +--------------------------------------------------+\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {

            case 1:
                printf("\n  -- PUSH: Add Patient Record to Stack --\n");
                printf("  Enter Patient ID        : "); scanf("%d", &id); getchar();
                printf("  Enter Patient Name      : "); fgets(name, 50, stdin); name[strcspn(name,"\n")]=0;
                printf("  Enter Age               : "); scanf("%d", &age); getchar();
                printf("  Enter Gender (M/F/Other): "); fgets(gender, 10, stdin); gender[strcspn(gender,"\n")]=0;
                printf("  Enter Disease           : "); fgets(disease, 50, stdin); disease[strcspn(disease,"\n")]=0;
                pushStack(&s, id, name, age, gender, disease);
                break;

            case 2:
                popStack(&s);
                break;

            case 3:
                peekStack(&s);
                break;

            case 4:
                displayStack(&s);
                break;

            case 5:
                if (isStackEmpty(&s))
                    printf("\n  [Stack] IS_EMPTY → TRUE  (Stack is empty)\n");
                else
                    printf("\n  [Stack] IS_EMPTY → FALSE (Stack has %d record(s))\n", s.size);
                break;

            case 6:
                loadPatientsIntoStack(&s);
                break;

            case 0:
                printf("\n  [Stack] Returning to Main Menu...\n");
                break;

            default:
                printf("\n  Invalid choice. Enter 0-6.\n");
        }

        if (choice != 0) { printf("\n  Press Enter..."); getchar(); }

    } while (choice != 0);
}

// ===================== MAIN MENU =====================

void displayMainMenu() {
    clearScreen();
    printf("+---------------------------------------------------------------+\n");
    printf("|                   HOSPITAL MANAGEMENT SYSTEM                  |\n");
    printf("|                       (HMS Console v1.0)                      |\n");
    printf("+---------------------------------------------------------------+\n");
    printf("|        Data Structures Project | Smart Patient Handling       |\n");
    printf("+---------------------------------------------------------------+\n\n");
    printf("+---------------------------------------------------------------+\n");
    printf("|                          SYSTEM STATUS                        |\n");
    printf("+---------------------------------------------------------------+\n");
    printf("|   Total Patients : %-4d  |  Queue : %-4d  |  Emergency : %-4d |\n",
           totalpatients, queueCount, emergencyCount);
    printf("+---------------------------------------------------------------+\n\n");
    printf("+---------------------------------------------------------------+\n");
    printf("|                        MAIN NAVIGATION                        |\n");
    printf("+===============================================================+\n");
    printf("|  1.  Patient Registration       (Array)                       |\n");
    printf("|  2.  Doctor Storage             (Linked List)                 |\n");
    printf("|  3.  Normal Queue               (FIFO)                        |\n");
    printf("|  4.  Emergency Handling         (Priority Queue)              |\n");
    printf("|  5.  Patient Follow-Up Cycle    (Circular List)               |\n");
    printf("|  6.  Patient History            (Doubly Linked List)          |\n");
    printf("|  7.  Treatment Stack            (Linked List Stack)           |\n");
    printf("+---------------------------------------------------------------+\n");
    printf("|  0.  Exit System                                              |\n");
    printf("+---------------------------------------------------------------+\n\n");
    printf("  Enter your choice: ");
}

// ===================== MAIN =====================

int main() {
    seedPatients();
    initializeHistory(&globalHistory);
    loadPatientsIntoHistory(&globalHistory);
    int choice;

    do {
        displayMainMenu();
        scanf("%d", &choice); getchar();

        switch(choice) {
            case 1: patientRegistrationMenu(); break;
            case 2: doctorStorageMenu();       break;
            case 3: normalQueueMenu();                                   break;
            case 4: emergencyMenu();                                  break;
            case 5: doctorAssignmentMenu();                            break;
            case 6: patientHistoryMenu();      break;
            case 7: stackMenu();            break;
            case 0: printf("Exiting...\n");    break;
            default: printf("Invalid choice!\n");
        }

        if (choice != 0 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) { printf("\nPress Enter..."); getchar(); }

    } while (choice != 0);

    return 0;
}
