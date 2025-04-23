#include "defines.h"
#include "process.h"

int main(){
    enum STATE current_state = intial_display;
    int user_choice;
    int* train_num;
    int user_train_num;
    int* booking_data;
    char user_route[2][512];
    struct user_booking_information booking_info;
    while(true){
        current_state = intial_display;
        user_choice = show_initial_display();
        switch (user_choice)
        {
        case 4:
            printf("Thank you for Visiting!\n");
            return 0;
            break;
        case 3:
            current_state = show_reservation;
            break;
        case 2:
            current_state = book_tickets;
            break;
        case 1:
            current_state = show_routes;
            break;
        default:
            break;
        }

        if(current_state == show_routes){
            show_avalaible_routes();
            current_state = intial_display;
        }

        if(current_state == book_tickets){
            //char user_route[2][512];
            get_booking_data(user_route);
            //printf("The User Choose: \n%s\n%s", user_route[0], user_route[1]);
            train_num = (int*)load_data(user_route);
            if(!train_num){
                printf("No Trains found between your routes!\n");
                current_state = intial_display;
            }else{
                printf("The Trains you can take are: \n");
                for(int i = 0; train_num[i] != -1; i++){
                    printf("Train no.: %d\n", train_num[i]);
                }
                user_train_num = get_train_num();
                for(int i = 0; train_num[i] != -1; i++){
                    printf("%d\n", user_train_num);
                    if(train_num[i] == user_train_num){
                        current_state = process_booking;
                    }
                }
                if(current_state == process_booking){
                    printf("Procedding with booking\n");
                }else{
                    current_state = intial_display;
                    printf("No such train number exists, restarting booking process...\n");
                }
            }
        }


        if(current_state == process_booking){
            booking_data = (int*)begin_booking(user_train_num);
            printf("Total no. of berths booked: %d", booking_data[0]);
            printf("\nTotal Price: %d\n", booking_data[1]);
            booking_info.price = booking_data[1];
            booking_info.no_of_passangers = booking_data[0];
            strcpy(booking_info.source, user_route[0]);
            strcpy(booking_info.destination, user_route[1]);

        }


    }
    free(booking_data); booking_data = NULL;
    free(train_num);train_num = NULL;
    return 0;
}