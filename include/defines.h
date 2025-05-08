#ifndef DEFINES_H
#define DEFINES_H

//Header File Inclusions
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

//Macro Definitions
#define DATA_PATH "./data/train_data.csv"
#define BOOKING_DATA_PATH "./data/user_bookings.csv"
#define SEAT_DATA_PATH "./data/seat_count.csv"
#define TEMP_PATH "./data/temp.csv"

//Maxmimum characters a single line can be raed from in the .csv file.
extern const short int MAX_LINE;
extern const short int MAX_TICKET_LIMIT;  

//Defines the current state the user booking the ticket is in.
enum STATE {intial_display, book_tickets, show_routes, show_reservation, process_booking, cancel_booking};
void kill_program();
struct user_booking_information{
    int train_num;
    int price;
    int no_of_passangers;
    char source[512];
    char destination[512];
    char date[128];

};
#endif