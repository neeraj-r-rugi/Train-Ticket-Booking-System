#ifndef PROCESS_H
#define PROCESS_H
//Function prototypes for processing data

int * load_data(char user_route[2][512]);        //* Opens filestream and loads data from the database about train information;
int show_initial_display();
void show_avalaible_routes();
FILE *load_file();
void get_booking_data(char data[2][512]);
void clear_buffer();
int get_train_num();
int * begin_booking(int train_num);
int load_price(int train_num);
int finalize_booking(const struct user_booking_information*);
int generate_booking_id();
void show_user_reservations();
void to_upper(char*);
void get_date(struct user_booking_information *);
int get_seat_count(int);
void update_seat_count(int, int);

#endif