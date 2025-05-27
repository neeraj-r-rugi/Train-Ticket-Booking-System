#ifndef PROCESS_H
#define PROCESS_H
//Function prototypes for processing data


/******************************************************************************************* */
/*
    @brief: The function opens filestram and retrives train information and returns an array of train numbers.
    @param: A 2-D array containg sorce and destination
*/
int * load_data(char user_route[2][512]);
/*
    @brief: Thisfunctions prompts the user with CLI Menu and return the choice of the user
    @param: NULL
*/  
int show_initial_display();
/*
    @brief: Thisfunctions display all the avalaible routes and the information pertaining to the route
    @param: NULL
*/
void show_avalaible_routes();
/*
    @brief: This function returns a file pointer pointing to the file containing the train data.
    @param: A 2-D array containg sorce and destination
*/
FILE * load_file();
/*
    @brief: This function prompts the user to input source and destination and copies the same into the parameter passed
    @param: AA 2-D array where users choice of source and destination is copied
*/
void get_booking_data(char data[2][512]);
/*
    @brief: A helper function to clear/flush the standard input buffer
    @param: NULL
*/
void clear_buffer();
/*
    @brief: This function prompts the user for train number they choose and returns it.
    @param: NULL
*/
int get_train_num();
/*
    @brief: This function intiates the booking process and prompts the user for data related to the booking of the ticket
    @param: train number of the train to be booked
*/
int * begin_booking(int train_num);
/*
    @brief: This function loads the fare of the train number
    @param: Train number of whose fare is to be obtained
*/
int load_price(int train_num);
/*
    @brief: This function opens a filestream and writes to the user data file
    @param: struct containg user booking information
*/
int finalize_booking(const struct user_booking_information *);
/*
    @brief: Generates a Booking Id for the ticket as a unique identifier
    @param: NULL
*/
int generate_booking_id();
/*
    @brief: Displays all the tickets of the user
    @param: NULL
*/
void show_user_reservations();
/*
    @brief: THelper Function to upper-case a string
    @param: char pointer of the string whose is it be uppercased
*/
void to_upper(char *);
/*
    @brief: This function prompts the user for the journey date.
    @param: Struct containing booking information
*/
void get_date(struct user_booking_information *);
/*
    @brief: This function gets the no. of available seats for a given train number
    @param: the integer of the train number
*/
int get_seat_count(int);
/*
    @brief: The function opens filestram and updates the no. of available seats for a given train
    @param: an integer of the train number
    @param: an integer of the number of seats booked
*/
void update_seat_count(int, int);
/*
    @brief: This function retrives the train number and deletes the user booking
    @param: an integer of the train number
*/
void delete_ticket(int);
/******************************************************************************************* */

#endif