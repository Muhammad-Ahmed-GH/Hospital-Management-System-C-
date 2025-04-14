#include <stdio.h>
#include <windows.h>

void HomePage();
void BackHome();

enum enColors {White = 7, Red = 12, Yellow = 14};

typedef struct {
    int room;
    char name[18];
    char doctor[18];
} Patient;

typedef struct {
    int number;
    char name[18];
    char text[24];
} Appointment;

typedef struct {
    int number;
    char text[24];
} Slot;

typedef struct {
    int number;
    char doctor[18];
} Room;

HANDLE h;
void color(short n){
    SetConsoleTextAttribute(h, n);
}

void show(){
    color(Yellow);
    printf("\nWhat do you want to display: \n");
    printf("(1) Patients\n");
    printf("(2) Booked appointments\n");
    printf("(3) Available rooms\n");
    printf("(4) Available slots\n");
    
    color(White);
    char c;
    scanf(" %c", &c);
    switch (c){
    case '1':
        FILE *patients = fopen("PatientRecords.txt", "r");
        printf("\nRoom  Name              Doctor            \n");

        while((c = fgetc(patients))!=EOF){
            printf("%c", c);
        }
        printf("\n");
        fclose(patients);
        BackHome();
        break;
    
    case '2':
        FILE *appoints = fopen("AppointRecords.txt", "r");
        printf("\nSlot  Name              Time              \n");

        while((c = fgetc(appoints))!=EOF){
            printf("%c", c);
        }
        fclose(appoints);
        BackHome();
        break;
    
    case '3':
        FILE *avRooms = fopen("AvailRooms.txt", "r");
        printf("\nRoom  Doctor            \n");
        while((c = fgetc(avRooms))!=EOF){
            printf("%c", c);
        }
        fclose(avRooms);
        BackHome();
        break;
    
    case '4':
        FILE *avSlots = fopen("AvailSlots.txt", "r");
        printf("\nSlot  Doctor            \n");
        while((c = fgetc(avSlots))!=EOF){
            printf("%c", c);
        }
        fclose(avSlots);
        BackHome();
        break;
    
    default:
        color(Red);
        printf("Invalid Input\n");
        color(White);
        BackHome();
        break;
    }
}

void Remove_patient(){
    FILE *avRooms = fopen("AvailRooms.txt", "r+");
    FILE *patients = fopen("PatientRecords.txt", "r+");
    if((avRooms != NULL)&&(patients != NULL)){
        int room, i, found = 0;
        int patient_count = 0;

        char c;
        while ((c = fgetc(patients))!=EOF){
            if(c=='\n') patient_count++;
        }
        
        Patient patientsArr[patient_count];
        fseek(patients, 0, SEEK_SET);
        for(i = 0; i<patient_count; i++){
            fscanf(patients, "%d%s%s", &patientsArr[i].room, &patientsArr[i].name, &patientsArr[i].doctor);
        }

        color(Yellow);
        printf("\nEnter patient room to remove: ");
        color(White);
        scanf("%d", &room);

        int index;
        for (i = 0; i < patient_count; i++) {
            if (patientsArr[i].room == room) {
                found = 1;
                index = i;
                break;
            }
        }

        if (found) {
            fseek(avRooms, 0, SEEK_END);
            fprintf(avRooms, "%-6d%-18s\n", room, patientsArr[index].doctor);

            fclose(patients);
            FILE *patients = fopen("PatientRecords.txt", "w");
            for (int i = 0; i < patient_count; i++) {
                if(i==index)
                    continue;

                fprintf(patients, "%-6d%-18s%-18s\n", patientsArr[i].room, patientsArr[i].name, patientsArr[i].doctor);
            }
            printf("Patient removed successfully.\n");
        }
        else {
            printf("Patient not found.\n");
        }
        fclose(avRooms);
        fclose(patients);
    }
    else{
        color(Red);
        printf("Error.. wait until the system is fixed.\n");
        color(White);
    }
}

void Remove_appoint() {
    FILE *avSlots = fopen("AvailSlots.txt", "r+");
    FILE *appoints = fopen("AppointRecords.txt", "r+");
    if((avSlots != NULL)&&(appoints != NULL)){
        int nAppoint = 0;

        char c;
        while ((c = fgetc(appoints))!=EOF){
            if(c=='\n') nAppoint++;
        }

        Appointment appointArr[nAppoint];
        fseek(appoints, 0, SEEK_SET);

        for(int i = 0; i<nAppoint; i++){
            fscanf(appoints, "%d%s%s", &appointArr[i].number, &appointArr[i].name, &appointArr[i].text);
        }

        int slot;
        color(Yellow);
        printf("\nEnter patient slot number: ");
        color(White);
        scanf("%d", &slot);

        int index, found = 0;
        for (int i = 0; i < nAppoint; i++) {
            if (appointArr[i].number == slot) {
                found = 1;
                index = i;
                break;
            }
        }
        if (found){
            fseek(avSlots, 0, SEEK_END);
            fprintf(avSlots, "%-6d%-24s\n", slot, appointArr[index].text);

            fclose(appoints);
            FILE *appoints = fopen("AppointRecords.txt", "w");
            for (int i = 0; i < nAppoint; i++) {
                if(i==index)    continue;

                fprintf(appoints, "%-6d%-18s%-24s\n", appointArr[i].number, appointArr[i].name, appointArr[i].text);
            }
            printf("Appointment removed successfully.\n");
        }
        else {
            printf("Appointment not found.\n");
        }
        fclose(avSlots);
        fclose(appoints);
    }
    else{
        color(Red);
        printf("Error.. wait until the system is fixed.\n");
        color(White);
    }
}

void BackHome(){
    char response;
    printf("\nBack Home? (y/n) ");
    scanf(" %c", &response);
    
    if (response == 'y' || response == 'Y'){
        color(Yellow);
        printf("\n\n--------------------------------------------------------------------------------------------------------\n");
        HomePage();
    }
        
    else if (response == 'n' || response == 'N') 
        printf("Program has terminated...\n");

    else{
        color(Red);
        printf("Invalid Input\n");
        color(White);
        printf("Program has terminated...");
    }
}

void AboutUS(){
    FILE *aboutUs = fopen("AboutUs.txt", "r");
    if(aboutUs!=NULL){
        color(Yellow);
        printf("\n\n\
--------------------------------------------------------------------------------------------------------\n\
                                         +---------------------+\n\
                                         |                     |\n\
                                         |      About Us       |\n\
                                         |                     |\n\
                                         +---------------------+\n\n");

        color(White);
        char c;
        while((c = fgetc(aboutUs)) != EOF){
            printf("%c", c);
        }
    }
    else{
        printf("Error.. wait until the system is fixed.\n");
    }
    fclose(aboutUs);
}

void payment(char *name, int room, char *doctor){
    char crdt_crd[17], CVV[5];
    color(Yellow);
    printf("Enter your credit card number: ");
    color(White);
    scanf("%s", &crdt_crd);

    color(Yellow);
    printf("Enter the CVV: ");
    color(White);
    scanf("%s", &CVV);

    printf("\nHere is the receipt!\n");
    color(Yellow);
    printf("\
+---------------------------------+\n\
|        PAYMENT RECEIPT          |\n\
|         CARE Hospital           |\n\
|                                 |\n\
| Name: %-18s        |\n\
|                                 |\n\
| Room: %-18d        |\n\
|                                 |\n\
| Doctor: %-18s      |\n\
|                                 |\n\
| Paid: 100 L.E.                  |\n\
|                                 |\n\
| Credit Card number:             |\n\
| %-18s              |\n\
|                                 |\n\
| CVV: %-18s         |\n\
|                                 |\n\
|                                 |\n\
+---------------------------------+\n\
", name, room, doctor, crdt_crd, CVV);
    color(White);
}

void payment2(char *name, int slot, char *slotTXT){
    char crdt_crd[17], CVV[5];
    color(Yellow);
    printf("Enter your credit card number: ");
    color(White);
    scanf("%s", &crdt_crd);

    color(Yellow);
    printf("Enter the CVV: ");
    color(White);
    scanf("%s", &CVV);
    
    printf("\nHere is the receipt!\n");
    color(Yellow);
    printf("\
+---------------------------------+\n\
|        PAYMENT RECEIPT          |\n\
|         CARE Hospital           |\n\
|                                 |\n\
| Name: %-18s        |\n\
|                                 |\n\
| Slot number: %-11d        |\n\
|                                 |\n\
| Slot: %-24s  |\n\
|                                 |\n\
| Paid: 100 L.E.                  |\n\
|                                 |\n\
| Credit Card number:             |\n\
| %-18s              |\n\
|                                 |\n\
| CVV: %-18s         |\n\
|                                 |\n\
|                                 |\n\
+---------------------------------+\n\
", name, slot, slotTXT, crdt_crd, CVV);
    color(White);
}

void NewPatient(){
    FILE *avRooms  = fopen("AvailRooms.txt", "r+");
    FILE *patients = fopen("PatientRecords.txt", "r+");
    if((avRooms != NULL) && (patients != NULL)){
        int nRooms = 0;

        //calc n of available rooms
        for (char c; (c = fgetc(avRooms)) != EOF ; ){
            if(c=='\n') nRooms++;
        }

        if(nRooms>0){
            color(Yellow);
            printf("\nName (separated with _ ): ");

            color(White);
            char name[18];
            scanf("%s", name);

            Room rooms[nRooms];
            fseek(avRooms, 0, SEEK_SET);
            for(int i = 0; i<nRooms; i++){
                fscanf(avRooms, "%d%s", &(rooms[i].number), &(rooms[i].doctor));
            }

            int room = rooms[0].number;
            char *doctor = rooms[0].doctor;
            fseek(patients, 0, SEEK_END);
            fprintf(patients, "%-6d%-18s%-18s\n", room, name, doctor);
            fclose(avRooms);

            FILE *avRooms = fopen("AvailRooms.txt", "w");

            // writing the new patients list
            for(int i = 1; i<nRooms; i++){
                fprintf(avRooms, "%-6d%-18s\n", rooms[i].number, rooms[i].doctor);
            }

            payment(name, room, doctor);
            printf("Room booked successfully.\n");
        }
        else{
            printf("Sorry, there are no available rooms.\n");
        }
    }
    else{ // Problem with the files
        color(Red);
        printf("Error.. wait until the system is fixed.\n");
        color(White);
    }
    fclose(avRooms);
    fclose(patients);
}

void NewAppoint(){
    FILE *avSlots  = fopen("AvailSlots.txt", "r+");
    FILE *Appoints = fopen("AppointRecords.txt", "r+");
    if((avSlots != NULL) && (Appoints != NULL)){

        //calc n of available slots
        int nSlots = 0;
        char c;
        while ((c = fgetc(avSlots)) != EOF){
            if(c=='\n') nSlots++;
        }

        if(nSlots>0){
            color(Yellow);
            printf("\nName (separated with _ ): ");

            color(White);
            char name[18];
            scanf("%s", name);

            // which slot
            printf("Which slot do you perfer: \n");
            fseek(avSlots, 0, SEEK_SET);
            color(Yellow);

            Slot slots[nSlots];
            for(int i = 0; i<nSlots; i++){
                fscanf(avSlots, "%d%s", &slots[i].number, &slots[i].text);
                printf("%-6d %s\n", slots[i].number, slots[i].text);
            }

            color(White);
            int slot;
            scanf("%d", &slot);

            int index;
            char found = 0;
            // checking the slot
            for(int i = 0; i<nSlots; i++){
                if(slots[i].number == slot){
                    found = 1;
                    index = i;
                    break;
                }
            }
            if(found){
                fseek(Appoints, 0, SEEK_END);
                fprintf(Appoints, "%-6d%-18s%-24s\n", slot,  name, slots[index].text);
                fclose(avSlots);
                FILE *avSlots  = fopen("AvailSlots.txt", "w");
                for(int i = 0; i<nSlots; i++){
                    if(slots[i].number==slot){
                        continue;
                    }
                    fprintf(avSlots, "%-6d%-24s\n", slots[i].number, slots[i].text);
                }
                payment2(name, slot, slots[index].text);
                printf("Slot booked successfully.\n");
            }
            else{
                printf("Slot is not available.");
            }
        }
        else{
            printf("Sorry, there are no available slots.\n");
        }
    }
    else{ // Problem with the files
        color(Red);
        printf("Error.. wait until the system is fixed.\n");
        color(White);
    }
    fclose(avSlots);
    fclose(Appoints);
}

void HomePage(){
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    color(Yellow);

    char *homeText1 = "\
                          *           +--------------------------+           *  \n\
                                      |        Welcome to        |              \n\
                           *          |       CARE Hospital      |          *   \n\
                                      |    Management System!!   |              \n\
                          *           +--------------------------+           *  \n\n";
    char *homeText2 = "\
                                           What do you need:                    \n\
                             *              (1) New records               *     \n\
                                            (2) Remove records                  \n\
                             *              (3) Show data                 *     \n\
                                            (4) About us                        \n\
                              *             (5) Exit                     *      \n\
";
    printf("%s", homeText1);
    color(White);
    printf("%s", homeText2);

    char choice, choice2;
    scanf(" %c", &choice);
    switch (choice){
        case '1':
            ///   New   ///
            color(Yellow);
            printf("\nWhat do you want to insert:\n(1) Patient record\n(2) Appointment booking\n");

            color(White);
            scanf(" %c", &choice2);
            switch (choice2){
                case '1':
                    NewPatient();
                    BackHome();
                    break;
                case '2':
                    NewAppoint();
                    BackHome();
                    break;

                default:
                    color(Red);
                    printf("Invalid Input...\n");
                    color(White);
                    BackHome();
                    break;
                }
                break;

        case '2':
            ///   Remove   ///
            color(Yellow);
            printf("\nWhat do you want to remove:\n(1) Patient record\n(2) Appointment booking\n");
            color(White);

            scanf(" %c", &choice2);
            switch (choice2){
                case '1':
                    Remove_patient();
                    BackHome();
                    break;
                case '2':
                    Remove_appoint();
                    BackHome();
                    break;

                default:
                    color(Red);
                    printf("Invalid Input...\n");
                    color(White);
                    BackHome();
                    break;
            }
                break;

        case '3':
            show();
            break;

        case '4':
            AboutUS();
            BackHome();
            break;

        case '5':
            printf("Program has terminated...");
            break;

        default:
            color(Red);
            printf("Invalid Input\n");
            color(White);
            printf("Program has terminated...");
            break;
    }
}

int main(){
    HomePage();
    return 0;
}