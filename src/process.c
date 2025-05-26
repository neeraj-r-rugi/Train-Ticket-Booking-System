#include "defines.h"
#include "process.h"

//#define MAX_FIELD_LEN 100

void delete_ticket(int id){
    bool booking_found = false;
    FILE *fp_in = fopen(BOOKING_DATA_PATH, "r");
    FILE *fp_out = fopen(TEMP_PATH, "w");
    if (!fp_in || !fp_out) {
        printf("Could Not Load Seat Database\n");
        kill_program();
    }
    char line[512];
    while (fgets(line, sizeof(line), fp_in)) {
        char line_copy[512];
        strcpy(line_copy, line);
        char *token = strtok(line_copy, ",");
        if (id != atoi(token)) {
            fputs(line, fp_out);
        }else{
            printf("Booking Deleted!\n");
            booking_found = true;
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    remove(BOOKING_DATA_PATH);
    rename(TEMP_PATH, BOOKING_DATA_PATH);
    if(!booking_found){
        printf("No Booking ID Found\n");
    }
}


void update_seat_count(int train_num, int no_of_passangers){
    FILE *fp_in = fopen(SEAT_DATA_PATH, "r");
    FILE *fp_out = fopen(TEMP_PATH, "w");
    int reduced_seats = (get_seat_count(train_num)) - no_of_passangers;
    if (!fp_in || !fp_out) {
        printf("Could Not Load Seat Database\n");
        kill_program();
    }
    char line[64];
    while (fgets(line, sizeof(line), fp_in)) {
        char line_copy[64];
        strcpy(line_copy, line);
        char *token = strtok(line_copy, ",");
        if (train_num == atoi(token)) {
            fprintf(fp_out, "%d,%d,\n", train_num, reduced_seats);
        }else{
            fputs(line, fp_out);
        }
    }
    fclose(fp_in);
    fclose(fp_out);
    remove(SEAT_DATA_PATH);
    rename(TEMP_PATH, SEAT_DATA_PATH);
}

int get_seat_count(int train_num){
    char line[64];
    FILE *fp = fopen(SEAT_DATA_PATH, "r");
    if(fp == NULL){
        printf("An Error Occured while trying to seat train database.\n");
        kill_program();
    }
    while(fgets(line, 64, fp)){
        char * token = strtok(line, ",");
        if(train_num == atoi(token)){
            token = strtok(NULL, ",");
            fclose(fp);
            return atoi(token);
        }
    }

}

void get_date(struct user_booking_information * info){
    int i;
    printf("Enter the date: of your journey in the format: 'DD-MM-YYYY': \n");
    clear_buffer();
    fgets(info->date, 128, stdin);
    for(i = 0; info->date[i] != '\n'; i++);
    info->date[i] = '\0';

}

void to_upper(char str[512]){
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);  // Converts each character to uppercase
    }
}

void show_user_reservations(){
    FILE *fp = fopen(BOOKING_DATA_PATH, "r");
    char line[MAX_LINE];
    printf("Your Bookings are: \n\n");
    while (fgets(line, MAX_LINE,fp))
    {
        if(!strcmp(line, "\n")){
            printf("No Bookings yet!\n");
            break;
        }
        char *token = strtok(line, ",");

        printf("Booking id: %d\n", atoi(token));
        token = strtok(NULL, ",");

        printf("Source: %s\n", token);
        token = strtok(NULL, ",");

        printf("Destination: %s\n", token);
        token = strtok(NULL, ",");

        printf("Train No.: %d\n", atoi(token));
        token = strtok(NULL, ",");

        printf("Number of Passangers: %d\n", atoi(token));
        token = strtok(NULL, ",");

        printf("Total Price: %d\n", atoi(token));
        token = strtok(NULL, ",");

        printf("Journey date: %s\n", token);
        token = strtok(NULL, ",");
        printf("Booking date: %s\n", token);
        token = strtok(NULL, ",");
        printf("-----------------------------------------------\n\n");
    }
    printf("Press Enter to continue...\n");
    clear_buffer();
    getchar();
    fclose(fp);
}


int generate_booking_id(){
    srand(time(NULL));
    return (rand() % 90000 + 10000);
}

int finalize_booking(const struct user_booking_information * info){
    FILE *fp = fopen(BOOKING_DATA_PATH, "a");
    if (fp == NULL) {
        printf("Failed to Book Ticket!\n");
        kill_program();
    }
    int booking_id = generate_booking_id();
    char temp[512];
    char source[512];
    char destination[512];
    
    strcpy(temp, info->source);
    to_upper(temp);
    strcpy(source, temp);

    //printf("%s\n", temp);
    strcpy(temp, info->destination);
    to_upper(temp);
    strcpy(destination, temp);

    //printf("--%d\n", info->train_num);
    fprintf(fp, "%d,%s,%s,%d,%d,%d,%s,%s,\n", booking_id,source, destination, info->train_num, info->no_of_passangers, info->price, info->date,__DATE__);
    fclose(fp);
    return booking_id;

}


int load_price(int train_num){
    int price;
    char line[MAX_LINE];
    FILE *fp = load_file();
    while (fgets(line, MAX_LINE,fp))
    {
        char *token = strtok(line, ",");
        if(train_num == atoi(token)){
            //To get to price part of line in the CSV file
            for(int i = 1; i<= 3; i++){
                token = strtok(NULL, ",");
            }
            price = atoi(token);
        }
    }
    fclose(fp);
    return price;
}

int * begin_booking(int train_num){
    
    printf("NOTE: For security reasons you can only book a maximum of 6 tickets per booking\n");
    int no_of_passangers = 0;
    int* p = (int*)malloc(2 * sizeof(int));
    int no_of_seats = get_seat_count(train_num);
    while(true){
        printf("Please enter the number of travellers you are booking for or -1 if you want to cancel booking\n");
        printf("Your Choice: ");
        scanf("%d", &no_of_passangers);
        printf("\n");
        if(no_of_passangers == -1){
            printf("Cancelling booking\n");
            kill_program();
        }
        if(no_of_passangers <= MAX_TICKET_LIMIT && no_of_passangers >= 1){
            //printf("YES\n");
            if(no_of_passangers <= no_of_seats){
                break;
            }
            else{
                printf("Required no. Seats Not Avalaible, Please reduce no. of passengers or cancel the booking\n");
            }
        }else{
            printf("Inavalid no. of Passangers please try again: \n");
        }
    }
    //printf("--YES\n");
    p[0] = no_of_passangers;
    p[1] = no_of_passangers * load_price(train_num);
    return p;

}

int get_train_num(){
    printf("Please enter the train that you want to take:\n");
    printf("Your choice: ");
    int temp;
    clear_buffer();
    scanf("%d", &temp);
    return temp;
}

void clear_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF );
}

void get_booking_data(char data[2][512]){
    
    clear_buffer();
    printf("Enter Source: \n");
    scanf("%[^\n]", data[0]);
    //fgets(data[0], 512, stdin);
    clear_buffer();
    printf("Enter Destiantion: \n");
    scanf("%[^\n]", data[1]);
    //fgets(data[1], 512, stdin);
}

FILE* load_file(){
    FILE *fp = fopen(DATA_PATH, "r");
    if(fp == NULL){
        printf("An Error Occured while trying to load train database.\n");
        kill_program();
    }
    return fp;

}

void show_avalaible_routes(){
    char line[MAX_LINE];
    FILE *fp = load_file();
    printf("Our routes are: \n");
    while (fgets(line, MAX_LINE,fp))
    {
        int train_num;
        char *token = strtok(line, ",");
        printf("No.: %s|| ", token);
        train_num = atoi(token);
        token = strtok(NULL, ",");
        printf("From: %s", token);
        token = strtok(NULL, ",");
        printf(" ------------> ");
        printf("To: %s ", token);
        token = strtok(NULL,",");
        printf("Price: %s ", token);
        printf("Seats left: %d\n", get_seat_count(train_num));
    }
    printf("Press any key to continue...\n");
    clear_buffer();
    getchar();
    fclose(fp);
}

int show_initial_display(){
    int choice = -1;
    while(true){
        printf("Please Choose one of the following: \n");
        printf("Type 1: To see available routes\n");
        printf("Type 2: To book tickets\n");
        printf("Type 3: To see your reservations\n");
        printf("Type 4: To Terminate the program\n");
        printf("Type 5: To Cancel a booking\n");
        char temp[2];
    
        printf("You Choose: ");
        scanf("%c", temp);
        printf("\n");
	temp[1] = '\0';
        choice = atoi(temp);
        if(choice < 1 || choice > 5){
            printf("Invalid Choice, Please Choose again.\n\n");\
            clear_buffer();
        }else{
    
            break;
        }
    }
    return choice;

}


int * load_data(char user_route[2][512]){
    char line[MAX_LINE];
    //Intialising file pointer.
    int temp;
    int *valid_train_num = NULL;
    int i = 0;
    int temp_train_num;
    FILE *fp = load_file();

    char source[512] ;
    char destination[512];
    strcpy(source, user_route[0]);
    strcpy(destination, user_route[1]);

    while(fgets(line, MAX_LINE, fp)){
        char* token = strtok(line, ",");
        temp_train_num = atoi(token);
        token = strtok(NULL, ",");

        //printf("\n%s, %d\n", token, strlen(token));
        //printf("%s, %d\n", source, strlen(source));
        //printf("%d\n\n", strcasecmp(token, source));
        temp = strcasecmp(token, source);
        if(temp == 0){
            //printf("%s\n", token);
            //printf("%s\n", user_route[0]);
            token = strtok(NULL, ",");
            // printf("--%s\n", source);
            // printf("--%s\n", destination);
            // printf("--%s\n", token);
            // printf("--%d, teken: --%d, dest --%d\n", strcasecmp(token, destination), strlen(token), strlen(destination));
            temp = strcasecmp(token, destination);
            // printf("-------%d\n", temp);
            if (temp == 0)
            {
                //printf("%s\n", token);
                //printf("%s\n", user_route[1]);
                //printf("Added: %d\n", temp_train_num);
                valid_train_num = realloc(valid_train_num, (i + 1) * sizeof(int));
                valid_train_num[i] = temp_train_num;
                // printf("----%d", valid_train_num[i]);
                i++;
            }
            
        }

    }
    fclose(fp);
    if(!valid_train_num){
        return NULL;
    }else{
        valid_train_num = realloc(valid_train_num, (i + 1) * sizeof(int));
        valid_train_num[i] = -1; 
        return valid_train_num;
    }
}

