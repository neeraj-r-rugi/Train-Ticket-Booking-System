/*

    @authors: Neeraj R Rugi, Neel Chandrakar, Joshua Jaison, K Devi Sai Charan
    @Team members SRN's: PES2UG24CS311, PES2UG24CS310, PES2UG24CS231, PES2UG24EC140
    @Project Name: Train Ticket Booking System
    @Type: Terminal Based Executable
    @brief: A terminal based train ticket booking system emulator.

    The team would like to express our sincere gratitude to our Professor Pranjali mam
    for their invaluable guidance, support, and encouragement throughout the course of this project. 
    Their insightful feedback, patience, and expertise were instrumental in helping us navigate
    challenges and deepen our understanding of the subject matter. 
    This mini project would not have been possible without their generous assistance.
*/

#include "defines.h"
#include "process.h"

int main(){
    enum STATE current_state = intial_display;
    int user_choice;
    int* train_nums;
    int user_train_num;
    int* booking_data;
    char user_route[2][512];
    struct user_booking_information booking_info;
    while(true){
        current_state = intial_display;
        user_choice = show_initial_display();
        switch (user_choice)
        {
        case 5:
            current_state = cancel_booking;
            break;
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
        if(current_state == cancel_booking){
            int id;
            printf("Enter the booking id you want to cancel\n");
            scanf("%d", &id);
            printf("--%d\n", id);
            delete_ticket(id);
            current_state = intial_display;
        }

        if(current_state == show_reservation){
            show_user_reservations();
            current_state = intial_display;
        }

        if(current_state == show_routes){
            show_avalaible_routes();
            current_state = intial_display;
        }

        if(current_state == book_tickets){
            //char user_route[2][512];
            get_booking_data(user_route);
            //printf("The User Choose: \n%s\n%s", user_route[0], user_route[1]);
            train_nums = (int*)load_data(user_route);
            if(!train_nums){
                printf("No Trains found between your routes!\n");
                current_state = intial_display;
            }else{
                printf("The Trains you can take are: \n\n");
                printf("-----------------------------------------------\n");
                for(int i = 0; train_nums[i] != -1; i++){
                    printf("Train no.: %d, Price: %d, Seats Left: %d\n", train_nums[i], load_price(train_nums[i]), get_seat_count(train_nums[i]));
                }
                printf("-----------------------------------------------\n");
                user_train_num = get_train_num();
                for(int i = 0; train_nums[i] != -1; i++){
                    if(train_nums[i] == user_train_num){
                        current_state = process_booking;
                        break;
                    }
                } 
                if(current_state == process_booking){
                    printf("Procedding with booking\n");
                    printf("You will be booked into the train: %d\n", user_train_num);
                    printf("Press Enter to continue...\n");
                    clear_buffer();
                    getchar();
                }else{
                    current_state = intial_display;
                    printf("No such train number exists, restarting booking process...\n");
                }
            }
        }


        if(current_state == process_booking){
            booking_data = (int*)begin_booking(user_train_num);
            get_date(&booking_info);
            printf("Total no. of berths booked: %d", booking_data[0]);
            printf("\nTotal Price: %d\n", booking_data[1]);
            printf("Press Enter to continue...\n");
            clear_buffer();
            getchar();

            booking_info.price = booking_data[1];
            booking_info.no_of_passangers = booking_data[0];
            strcpy(booking_info.source, user_route[0]);
            strcpy(booking_info.destination, user_route[1]);
            booking_info.train_num = user_train_num;

            int id = finalize_booking(&booking_info);
            current_state = intial_display;

            printf("Your Booking is Complete!\n");
            printf("Your booking id is: %d\n", id);
            printf("Press any key to continue.....\n");
            update_seat_count(booking_info.train_num, booking_info.no_of_passangers);
            clear_buffer();
            getchar();

        }


    }
    free(booking_data); booking_data = NULL;
    free(train_nums);train_nums = NULL;
    return 0;
}