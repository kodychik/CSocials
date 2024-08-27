#include "graffit.c"

// Some Basic Test Cases for our Functions

int main()
{
    User *u1 = create_user("User 1");
    User *u2 = create_user("User 2");
    User *u3 = create_user("User 3");
    User *u4 = create_user("User 4");
    User *u5 = create_user("User 5");

    populate_brand_matrix("brandtest.txt");

    // Testing add_suggested_friends()

    printf("Test 1.01 - Add Suggested Friends Basic Test\n\n");

    follow_brand(u1, "A");
    follow_brand(u1, "B");
    follow_brand(u1, "C");
    follow_brand(u1, "D");

    follow_brand(u2, "B");
    follow_brand(u2, "C");
    follow_brand(u2, "D");

    follow_brand(u3, "B");
    follow_brand(u3, "C");

    follow_brand(u4, "C");
    follow_brand(u4, "D");

    follow_brand(u5, "A");

    // int x = add_suggested_friends(u1, 2);
    // if (x == 2 && in_friend_list(u1->friends, u2) && in_friend_list(u1->friends, u4)) printf("Test 1.01 Passed\n");
    /*else printf("Test 1.01 Failed\n");

    //print_user_data(u1);

    printf("Test 1.02 - Adding all users in database\n\n");

    x = add_suggested_friends(u1, 1);
    print_user_data(u1);
   // if (x != 2) printf("Failed\n");
    printf("%d\n", x);

    //print_user_data(u1);

    printf("Test 1.03 - Adding too many users into Friend's List\n\n");
    //printf("***%d\n", largerThanCount(u1));
    //if (add_suggested_friends(u1, 10) != 0) printf("Failed\n");
    x = add_suggested_friends(u1, 5);

    print_user_data(u1);

    x = add_suggested_friends(u1, 10);
    printf("%d\n", x);
    print_user_data(u1);*/

    add_suggested_friends(u1, 10);
    print_user_data(u3);

    User *u6 = create_user("User 6");
    User *u7 = create_user("User 7");
    User *u8 = create_user("User 8");
    User *u9 = create_user("User 9");
    User *u10 = create_user("User 99");

    follow_brand(u6, "B");
    follow_brand(u6, "C");

    follow_brand(u7, "B");
    follow_brand(u7, "C");

    follow_brand(u8, "A");
    follow_brand(u8, "B");

    follow_brand(u9, "A");
    follow_brand(u9, "C");
    follow_brand(u9, "D");

    follow_brand(u10, "A");
    follow_brand(u10, "B");

    // printf("%d\n", add_suggested_friends(u3, 10));

    // printf("%d\n", add_suggested_friends(u1, 10));
    printf("*****\n");
    print_user_data(u3);
    print_user_data(u1);

    printf("%d\n", follow_suggested_brands(u1, 50));
    print_user_data(u1);

    remove_similar_brands("A", "GSAD");

    return 0;
}