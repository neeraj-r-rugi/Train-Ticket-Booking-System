#include "defines.h"
#include "process.h"

//#define MAX_FIELD_LEN 100


int finalize_booking(struct user_booking_information* info){
    FILE *fp = fopen(BOOKING_DATA_PATH, "a");
    if (fp == NULL) {
        printf("Failed to Book Ticket!\n");
        kill_program();
    }
    fprintf(fp, *info.)

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

int* begin_booking(int train_num){
    
    printf("NOTE: For security reasons you can only book a maximum of 6 tickets per booking\n");
    int no_of_passangers;
    int* p = (int*)malloc(2 * sizeof(int));
    while(true){
        printf("Please enter the number of travellers you are booking for or -1 if you want to cancel booking\n");
        scanf("%d", &no_of_passangers);
        if(no_of_passangers <= MAX_TICKET_LIMIT && no_of_passangers >= 1){
            //printf("YES\n");
            break;
        
        }else{
            printf("Inavalid no. of Passangers please try again: \n");
            printf("Please enter the number of travellers you are booking for or -1 if you want to stop booking\n");
            scanf("%d", &no_of_passangers);
            if(no_of_passangers == -1){
                printf("Cancelling booking\n");
                kill_program();
            }
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
        char *token = strtok(line, ",");
        token = strtok(NULL, ",");
        printf("%s", token);
        token = strtok(NULL, ",");
        printf("    ------------>   ");
        printf("%s\n", token);
    }
    fclose(fp);
}

int show_initial_display(){
    printf("Please Choose one of the following: \n");
    printf("Type 1: To see available routes\n");
    printf("Type 2: To book tickets\n");
    printf("Type 3: To see your reservations\n");
    printf("Type 4: To Terminate the program\n");
    char temp[1];

    printf("You Choose: ");
    scanf("%s", temp);
    printf("\n");
    int choice = atoi(temp);
    if(choice < 1 || choice > 4){
        printf("Invalid Choice, Please Choose again.\n\n");\
        clear_buffer();
        show_initial_display();
    }else{

        return choice;
    }

}


int* load_data(char user_route[2][512]){
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
        valid_train_num = realloc(valid_train_num, sizeof(int));
        valid_train_num[i] = -1; 
        return valid_train_num;
    }
}


// int* load_data(char const *DATA){
//     char line[MAX_LINE];
//     //Intialising file pointer.
//     FILE *fp = fopen(DATA, "r");
//     if(fp == NULL){
//         printf("An Error Occured while trying to load train database.\n");
//         return NULL;
//     }else{
//         printf("File Found\n");
//     }

//     char *token = strtok(line, ",");
//     while (fgets(line, MAX_LINE,fp))
//     {
//         char *token = strtok(line, ",");
//         while(token){
//             token = strtok(NULL,",");
//             printf("%s\n", token);
//             break;
//         }
//     }
//     printf("----------END OF FILE----------");
//     fclose(fp);
// }