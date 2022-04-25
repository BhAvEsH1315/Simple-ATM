#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
struct details
{
     char nam[100];
     long long int mob;
     long long int acc;
     int bal;
     int pin;
     int exp_mon;
     int exp_yea;
     int pre;
     char history[10000][10000];
};
int no_2000, no_500, no_200, no_100, n, Amnt, Option, card2, no_lines;
struct details inf[6];

void OPTIONS();
void SELECT_Amnt();
void confirmation();
void delay();
int main();
void print_title()
{
     printf("                                                                                           WELCOME TO\n\n");
     printf("                                  ***       ***  ********         ***********  **************     *********            *          *****        ***  ***      ***\n");
     printf("                                  ***       ***  **********     ************   *************      ***********         ***         ******       ***  ***     ***\n");
     printf("                                  ***       ***  ***    *****  ***             ***                ***    *****       ** **        *** ***      ***  ***    ***\n");
     printf("                                  ***       ***  ***    ****   ***             ***                ***    ****       **   **       ***  ***     ***  ***   ***\n");
     printf("                                  *************  ********       ***********    *********          ********         *********      ***   ***    ***  *** ***\n");
     printf("                                  *************  ********        ***********   *********          ********        ***********     ***    ***   ***  *** ***\n");
     printf("                                  ***       ***  ***    ****              ***  ***                ***    ****    ***       ***    ***     ***  ***  ***   ***\n");
     printf("                                  ***       ***  ***    *****             ***  ***                ***    *****  ***         ***   ***      *** ***  ***    ***\n");
     printf("                                  ***       ***  **********     ************   *************      ***********  ***           ***  ***       ******  ***     ***\n");
     printf("                                  ***       ***  ********      ***********     **************     *********   ***             *** ***        *****  ***      ***\n\n");
     printf("                                                                                     ALWAYS THERE TO HELP YOU\n\n");
}
void Wish()
{
     printf("\n                                                                        IF YOU WANT TO CONTINUE FURTHER TRANSACTION\n                                                                        ENTER 'YES' AND IF NOT ENTER 'NO'\n                                                                        ");
     char Wished[20];
     scanf("%s", Wished);
     if (strcmp(Wished, "YES\0") == 0 || strcmp(Wished, "yes\0") == 0)
     {
          delay();
          system("cls");
          system("COLOR 8F");
          print_title();
          OPTIONS();
     }
     else if (strcmp(Wished, "NO\0") == 0 || strcmp(Wished, "no\0") == 0)
     {
          printf("\n                                                                        PLEASE COLLECT YOU CARD\n\n                                                                        THANK YOU!!!\n");
          delay();
          delay();
          delay();
          system("cls");
          main();
     }
}
void input(int c)
{

     int i, j = 0;
     no_lines = 0;
     FILE *cardi;
     char *tempc = "card";
     char tempf[20] = {0};
     char tempi[100][8];
     sprintf(tempf, "%s%d.txt", tempc, c);
     cardi = fopen(tempf, "r");
     fgets(inf[c].nam, 99, cardi);
     fscanf(cardi, "%lld\n%lld\n%d\n%d\n%d\n%d\n%d\n", &inf[c].mob, &inf[c].acc, &inf[c].bal, &inf[c].pin, &inf[c].exp_mon, &inf[c].exp_yea, &inf[c].pre);
     while (fgets(inf[c].history[no_lines], 9999, cardi) != NULL)
     {
          no_lines++;
     }
     fclose(cardi);

     return;
}
void atm_inp()
{
     FILE *atm_inv;
     atm_inv = fopen("atm.txt", "r");
     fscanf(atm_inv, "%d%d%d%d", &no_2000, &no_500, &no_200, &no_100);
     fclose(atm_inv);
     return;
}
void update(char which_info[5], int n, int new_info)
{
     input(n);
     int balance, pin, prem, j = 0;
     if (strcmp(which_info, "bal\0") == 0)
     {
          balance = new_info;
          pin = inf[n].pin;
          prem = inf[n].pre;
     }
     if (strcmp(which_info, "pin\0") == 0)
     {
          balance = inf[n].bal;
          pin = new_info;
          prem = inf[n].pre;

     }
     if (strcmp(which_info, "pre\0") == 0)
     {
          balance = inf[n].bal;
          pin = inf[n].pin;
          prem = new_info;

     }

     char *temc = "card";
     char tempn[10] = {0};
     sprintf(tempn, "%s%d.txt", temc, n);
     FILE *updet = fopen(tempn, "w");
     fprintf(updet, "%s%lld\n%lld\n%d\n%d\n%d\n%d\n%d\n", inf[n].nam, inf[n].mob, inf[n].acc, balance, pin, inf[n].exp_mon, inf[n].exp_yea, prem);
     while (j < no_lines)
     {
          fprintf(updet, "%s", inf[n].history[j]);
          j++;
     }
     fclose(updet);
     return;
}

int acc_tra = 0;
void Transaction(int card, int amount, long long int extra)
{
         SYSTEMTIME stime;
     GetSystemTime(&stime);
     char *temc = "card";
     char tempn[10] = {0};
     char cr_de;
     char to_fr[5];
     if (Option == 3)
     {
          cr_de = '+';
     }
     if (Option != 3 && acc_tra % 2 == 0)
     {
          cr_de = '-';
     }
     if (Option != 3 && acc_tra % 2 != 0)
     {
          cr_de = '+';
     }
     sprintf(tempn, "%s%d.txt", temc, card);
     FILE *updet = fopen(tempn, "a+");
     time_t t;
     time(&t);
     fprintf(updet, "\n------------------------------------------------------------------------------------------\n");
     fprintf(updet, "%s                       %c Rs.%d\n", ctime(&t), cr_de, amount);
     input(card);
     switch (Option)
     {
     case 1:
          fprintf(updet, "CASH WITHDRAWAL\nFROM ACC. NO.\n%lld\n", inf[card].acc);
          break;
     case 3:
          fprintf(updet, "CASH DEPOSIT\nTO ACC. NO.\n%lld\n", inf[card].acc);
          break;
     case 5:
          fprintf(updet, "IMT\nFROM ACC. NO.\n%lld\nTO MOBILE NO.\n%lld\n", inf[card].acc, extra);
          break;
     case 6:
          fprintf(updet, "MOBILE RECHARGE\nFROM ACC. NO.\n%lld\nTO MOBILE NO.\n%lld\n", inf[card].acc, extra);
          break;
     case 7:
          fprintf(updet, "PREMIUM PAYMENT FOR YEAR %d\nFROM ACC. NO.\n%lld\n", stime.wYear,inf[card].acc);
          break;
     case 8:
          input(card2);
          fprintf(updet, "ACCOUNT BASED TRANSFER\nFROM ACC. NO.\n%lld\nTO ACC. NO.\n%lld\n", inf[n].acc, inf[card2].acc);
          acc_tra++;
          break;
     }

     fprintf(updet, "Reference No.: HBSE%d%d%d%d%d%d", stime.wDay, stime.wMonth, stime.wYear, stime.wHour, stime.wMinute, stime.wSecond);
     fprintf(updet, "\nAVAILABLE BALANCE IS     Rs.%d", inf[card].bal);
     fclose(updet);
     return;
}
void update_atm(int new_2000, int new_500, int new_200, int new_100)
{
     FILE *upd_atm;
     upd_atm = fopen("atm.txt", "w");
     fprintf(upd_atm, "%d\n%d\n%d\n%d", new_2000, new_500, new_200, new_100);
     fclose(upd_atm);
     return;
}
void delay()
{
     int add, time, inc;
     time = 1000 * 100000;
     for (inc = 0; inc < time; inc++)
     {
          add *= inc;
          add++;
          add++;
     }
}
void Cash_Withdrawal()
{
     input(n);
     //function to print characters for displaying receipt with new line added
     void print_char_n(char ch, int n)
     {
          for (int j = 0; j < n; j++)
          {
               printf("%c", ch);
          }
          printf("\n                                                                        ");
          return;
     }
     void opt1()
     {
          float amt_to_be_withdrawn, total_amt_available, available_balance, balance;
          int notes_2000, notes_500, notes_200, notes_100, i = 0;
          char line[500], temp[500];
          printf("\n                                                                        PLEASE ENTER AMOUNT TO BE WITHDRAWN : \n                                                                        ");
          scanf("%f", &amt_to_be_withdrawn);
          atm_inp();
          input(n);

          balance = (float)inf[n].bal;
          //Opening card file for displaying balance after withdrawal
          available_balance = (balance - amt_to_be_withdrawn);
          //allocating number of notes to appropriate variables after function call
          total_amt_available = no_2000 * 2000 + no_500 * 500 + no_200 * 200 + no_100 * 100;

          if (amt_to_be_withdrawn > 15000.00)
          {

               SetColor(0);
               printf("                                                                        ---------------------------------------------------------\n                                                                        ");
               printf("PER DAY LIMIT TO WITHDRAW CASH IS Rs. 15000\n                                                                        ");
               printf("SORRY FOR THE INCONVENIENCE!\n                                                                        ");
               printf("---------------------------------------------------------\n                                                                        ");
               SetColor(31);
               Wish();
          }

          if (amt_to_be_withdrawn > total_amt_available && amt_to_be_withdrawn < balance)
          {
               SetColor(0);
               printf("                                                                        ------------------------------------------------------------\n                                                                        ");
               printf("THE CASH IS NOT AVAILABLE!\n                                                                        ");
               printf("SORRY FOR THE INCONVENIENCE!\n                                                                        ");
               printf("------------------------------------------------------------\n                                                                        ");
               SetColor(31);
               Wish();
          }
          else if (amt_to_be_withdrawn < total_amt_available && amt_to_be_withdrawn > balance)
          {
               SetColor(0);
               printf("                                                                        ------------------------------------------------------------\n                                                                        ");
               printf("ACCOUNT BALANCE IS LESS THAN AMOUNT TO BE WITHDRAWN!\n                                                                        ");
               printf("SORRY FOR THE INCONVENIENCE!\n                                                                        ");
               printf("------------------------------------------------------------\n                                                                        ");
               SetColor(31);
               Wish();
          }
          else if (amt_to_be_withdrawn > total_amt_available && amt_to_be_withdrawn > balance)
          {
               SetColor(0);
               printf("                                                                        ---------------------------------------------------------------------------------------------------------------------\n                                                                        ");
               printf("ACCOUNT BALANCE IS LESS THAN AMOUNT TO BE WITHDRAWN AND ENOUGH CASH IS NOT AVAILABLE IN THE ATM INVENTORY\n                                                                        ");
               printf("SORRY FOR THE INCONVENIENCE!\n                                                                        ");
               printf("---------------------------------------------------------------------------------------------------------------------\n                                                                        ");
               SetColor(31);
               Wish();
          }
          else
          {
               if ((int)amt_to_be_withdrawn % 100 != 0)
               {
                    SetColor(0);
                    printf("                                                                        ---------------------------------------------------\n                                                                        ");
                    printf(" PLEASE ENTER AMOUNT IN MULTIPLES OF 100!!!\n                                                                        ");
                    printf("---------------------------------------------------\n                                                                        ");
                    SetColor(31);
                    printf("DO YOU WISH TO CONTINUE CASH WITHDRAWAL?\n                                                                        TO CONTINUE ENTER 'YES', TO GO TO OPTIONS ENTER 'NO'\n                                                                        ");
                    char Wishes[20];
                    scanf("%s", Wishes);
                    if (strcmp(Wishes, "YES\0") == 0 || strcmp(Wishes, "yes\0") == 0)
                    {
                         delay();
                         opt1();
                    }
                    else if (strcmp(Wishes, "NO\0") == 0 || strcmp(Wishes, "no\0") == 0)
                    {
                         system("cls");
                         print_title();
                         delay(1000);
                         OPTIONS();
                    }
               }
               else
               {
                    char Wis[20];
                    printf("\n                                                                        DO YOU WISH TO WITHDRAW Rs. %d ?:\n                                                                        TYPE 'YES' FOR PROCEEDING OR 'NO' FOR RE-ENTERING AMOUNT \n                                                                        ", (int)amt_to_be_withdrawn);
                    scanf("%s", Wis);
                    if (strcmp(Wis, "YES\0") == 0 || strcmp(Wis, "yes\0") == 0)
                    {
                    }
                    else if (strcmp(Wis, "NO\0") == 0 || strcmp(Wis, "no\0") == 0)
                    {
                         opt1();
                    }
                    notes_2000 = (int)amt_to_be_withdrawn / 2000;
                    amt_to_be_withdrawn = (int)amt_to_be_withdrawn % 2000;
                    notes_500 = (int)amt_to_be_withdrawn / 500;
                    amt_to_be_withdrawn = (int)amt_to_be_withdrawn % 500;
                    notes_200 = (int)amt_to_be_withdrawn / 200;
                    amt_to_be_withdrawn = (int)amt_to_be_withdrawn % 200;
                    notes_100 = (int)amt_to_be_withdrawn / 100;
                    if (notes_2000 > no_2000)
                    {
                         notes_500 = notes_500 + 4 * (notes_2000);
                         notes_2000 = 0;
                    }

                    if (notes_500 > no_500)
                    {
                         notes_200 = notes_200 + 2 * (notes_500);
                         notes_100 = notes_100 + notes_500;
                         notes_500 = 0;
                    }

                    if (notes_200 > no_200)
                    {
                         notes_100 = notes_100 + 2 * (notes_200);
                         notes_200 = 0;
                    }

                    if (notes_100 > no_100)
                    {
                         SetColor(0);
                         printf("                                                                        ---------------------------------------------------\n                                                                        ");
                         printf("ENOUGH NOTES NOT AVAILABLE\n                                                                        ");
                         printf("SORRY FOR THE INCONVENIENCE!\n                                                                        ");
                         printf("---------------------------------------------------\n                                                                        ");
                         SetColor(31);
                         delay();
                         Wish();
                    }
                    printf("\n                                                                        PLEASE WAIT\n                                                                        ");
                    printf("TRANSACTION IS PROCESSING");
                    delay(1000);
                    printf(".");
                    delay(1000);
                    printf(".");
                    delay(1000);
                    printf(".\n                                                                        ");
                    print_char_n('-', 50);
                    printf("    PLEASE COLLECT YOUR CASH : \n                                                                        ");
                    printf("   ------------------------------------\n                                                                        ");
                    printf("   | DENOMINATION |  NUMBER OF NOTES  |\n                                                                        ");
                    printf("   ------------------------------------\n                                                                        ");
                    printf("   |2000          |   %d               |\n                                                                        ", notes_2000);
                    printf("   ------------------------------------\n                                                                        ");
                    printf("   |500           |   %d               |\n                                                                        ", notes_500);
                    printf("   ------------------------------------\n                                                                        ");
                    printf("   |200           |   %d               |\n                                                                        ", notes_200);
                    printf("   ------------------------------------\n                                                                        ");
                    printf("   |100           |   %d               |\n                                                                        ", notes_100);
                    printf("   ------------------------------------\n                                                                        ");
                    printf("    AVAILABLE BALANCE : Rs.%f\n                                                                        ", available_balance);
                    print_char_n('-', 50);
               }
          }
          //update inventory
          update_atm(no_2000 - notes_2000, no_500 - notes_500, no_200 - notes_200, no_100 - notes_100);
          //update available_balance of person in card file
          update("bal", n, (int)available_balance);
          Transaction(n, notes_2000 * 2000 + notes_500 * 500 + notes_200 * 200 + notes_100 * 100, 0);
          Wish();
          delay();
     }
     delay();
     opt1();
}
void Pin_Change()
{
     char new_pin[20];
     void check_pin(int check_new_pin, int countpn)
     {

          void re_enter()
          {
               printf("                                                                        PLEASE RE-ENTER PIN: ");
               char new_pin_enter[20];
               scanf("%s", new_pin_enter);
               int count_new_pin = strlen(new_pin_enter);
               int int_new_pin = atoi(new_pin_enter);
               check_pin(int_new_pin, count_new_pin);
               return;
          }

          if (countpn != 4)
          {
               SetColor(0);
               printf("                                                                        PLEASE ENTER FOUR DIGITS\n");
               SetColor(31);
               re_enter();
          }
          if (check_new_pin == inf[n].pin)
          {
               SetColor(0);
               printf("                                                                        NEW PIN IS SAME AS OLD PIN!\n");
               SetColor(31);
               re_enter();
          }
          if (check_new_pin == 1234 || check_new_pin % 1111 == 0 || check_new_pin == 0000)
          {
               SetColor(0);
               printf("                                                                        PIN IS TOO SIMPLE!\n");
               SetColor(31);
               re_enter();
          }
          while (1)
          {
               int confirm_new;
               printf("                                                                        PLEASE CONFIRM YOUR NEW PIN: ");
               scanf("%d", &confirm_new);
               if (confirm_new == check_new_pin)
               {
                    break;
               }
          }
          update("pin", n, check_new_pin);
          delay();
          printf("\n                                                                        -----PIN CHANGED SUCCESSFULLY!!-----\n                                                                        ");
          Wish();
     }
     void pin()
     {
          printf("                                                                        PLEASE ENTER NEW PIN:");
          scanf("%s", new_pin);
          int count_pin = strlen(new_pin);
          int int_new_pin = atoi(new_pin);
          check_pin(int_new_pin, count_pin);
     }
     pin();
}
void deposit();
void Cash_Deposit()
{
     int fin_100 = 0, fin_200 = 0, fin_500 = 0, fin_2000 = 0, total, dep_100, dep_200, dep_500, dep_2000;
     char con_add[20];
     void add()
     {
          printf("\n                                                                        PLEASE PLACE THE CASH IN THE TRAY PROVIDED:\n                                                                        ");
          printf("2000 500 200 100:");
          scanf("%d%d%d%d", &dep_2000, &dep_500, &dep_200, &dep_100);
          printf("\n                                                                        CALCULATING, PLEASE WAIT.....\n                                                                        ");
          delay();
          fin_100 = fin_100 + dep_100;
          fin_200 = fin_200 + dep_200;
          fin_500 = fin_500 + dep_500;
          fin_2000 = fin_2000 + dep_2000;
          total = fin_100 * 100 + fin_200 * 200 + fin_500 * 500 + fin_2000 * 2000;
          printf("--------------------------\n                                                                        ");
          printf("|DENOMINATION  |  NUMBER |\n                                                                        ");
          printf("--------------------------\n                                                                        ");
          printf("|2000          |   %d     |\n                                                                        ", fin_2000);
          printf("--------------------------\n                                                                        ");
          printf("|500           |   %d     |\n                                                                        ", fin_500);
          printf("--------------------------\n                                                                        ");
          printf("|200           |   %d     |\n                                                                        ", fin_200);
          printf("--------------------------\n                                                                        ");
          printf("|100           |   %d     |\n                                                                        ", fin_100);
          printf("--------------------------\n                                                                        ");
          printf("TOTAL = Rs.%d\n                                                                        \n                                                                        ", total);
          printf("DO YOU WISH TO 'CONFIRM' or 'ADD'?:\n                                                                        ");
          delay();
          scanf("%s", con_add);
          if (strcmp(con_add, "CONFIRM\0") == 0 || strcmp(con_add, "confirm\0") == 0)
          {
               return;
          }
          if (strcmp(con_add, "ADD\0") == 0 || strcmp(con_add, "add\0") == 0)
          {
               add();
          }
     }
     void deposit()
     {
          add();
          input(n);
          atm_inp();
          if (total > 200000)
          {
               SetColor(0);
               printf("                                                                        --------------------------------------------\n                                                                        ");
               printf("DAILY LIMIT FOR CASH DEPOSIT IS Rs.200000 \n                                                                        PLEASE TAKE THE CASH BACK FROM THE TRAY\n                                                                        ");
               printf("--------------------------------------------\n                                                                        ");
               SetColor(31);
               delay();
               delay();
               Wish();
          }
          update_atm(no_2000 + fin_2000, no_500 + fin_500, no_200 + fin_2000, no_100 + fin_100);
          update("bal", n, inf[n].bal + total);
          Transaction(n, total, 0);
          delay();
          printf("\n                                                                        ------------------------------------");
          printf("\n                                                                        YOUR TRANSACTION WAS SUCCESSFUL!!\n                                                                        YOUR AVAILABLE BALANCE IS Rs.%d\n                                                                        ", inf[n].bal);
          printf("------------------------------------\n                                                                        ");
          delay();
          Wish();
     }
     deposit();
}
void Balance_Inquiry()
{
     input(n);
     printf("\n                                                                        YOUR ACCOUNT BALANCE WILL BE DISPLAYED SHORTLY");
     delay();
     printf(".");
     delay();
     printf(".");
     delay();
     printf(".\n                                                                        ");
     printf("\n                                                                        ------------------------------");
     printf("\n                                                                        AVAILABLE BALANCE: Rs.%d\n                                                                        ", inf[n].bal);
     printf("------------------------------\n                                                                        ");
     delay();
     Wish();
}
void IMT()
{
     input(n);
     long long int mobno1, mobno2, mobno;
     while (1)
     {
          printf("\n                                                                        ENTER RECEIVER'S MOBILE NUMBER:\n                                                                        ");
          scanf("%lld", &mobno1);
          if (mobno1 < 1000000000 || mobno1 > 10000000000)
          {
               SetColor(0);
               printf("\n                                                                        ------------------------------");
               printf("\n                                                                        MOBILE NUMBER NOT VALID\n                                                                        ");
               printf("------------------------------\n                                                                        ");
               SetColor(31);
               continue;
          }
          else
          {
               break;
          }
     }
     while (1)
     {
          printf("\n                                                                        ENTER YOUR MOBILE NUMBER:\n                                                                        ");
          scanf("%lld", &mobno2);
          if (inf[n].mob == mobno2)
          {
               break;
          }
          else
          {
               SetColor(0);
               printf("                                                                        --------------------------------------------------------------");
               printf("\n                                                                        MOBILE NUMBER DOES NOT MATCH WITH REGISTERED MOBILE NUMBER\n                                                                        ");
               printf("--------------------------------------------------------------");
               SetColor(31);
               continue;
          }
     }
     int a, b;
     while (1)
     {
          printf("\n                                                                        ENTER 4 DIGIT SENDER CODE :\n                                                                        ");
          scanf("%d", &a);
          if (a / 1000 < 1 || a / 1000 > 9)
          {
               SetColor(0);
               printf("                                                                        -----------------------------------");
               printf("\n                                                                        THE CODE ENTERED IS NOT VALID!\n                                                                        ");
               printf("-----------------------------------");
               SetColor(31);
               continue;
          }
          printf("\n                                                                        ENTER 4 DIGIT SENDER CODE AGAIN :\n                                                                        ");
          scanf("%d", &b);
          if (a == b)
          {
               break;
          }
          else
          {
               SetColor(0);
               printf("                                                                        ------------------------------------");
               printf("\n                                                                        ENTERED CODE DOES NOT MATCH!\n                                                                        ");
               printf("------------------------------------");
               SetColor(31);
               continue;
          }
     }
     int amnt;
     while (1)
     {
          printf("\n                                                                        ENTER AMOUNT \n                                                                        ");
          scanf("%d", &amnt);
          if (inf[n].bal < amnt)
          {
               SetColor(0);
               printf("                                                                        ------------------------------------");
               printf("\n                                                                        NOT ENOUGH BALANCE AVAILABLE\n                                                                        ");
               printf("------------------------------------");
               SetColor(31);
               delay();
               delay();
               Wish();
          }
          else if (inf[n].bal >= amnt)
          {
               if (amnt % 100 != 0)
               {
                    SetColor(0);
                    printf("                                                                        -------------------------------------------");
                    printf("\n                                                                        PLEASE ENTER AMOUNT IN MULTIPLES OF 100\n                                                                        ");
                    printf("-------------------------------------------");
                    SetColor(31);
                    continue;
               }
               else
               {
                    break;
               }
          }
     }
     int x = amnt;
     delay(1000);
     printf("                                                                        --------------------------------------------------------------");
     printf("\n                                                                        ");
     printf("PLEASE CONFIRM YOUR IMT DETAILS\n                                                                        ");
     printf("--------------------------------------------------------------");
     printf("\n                                                                        ");
     printf("REMT MOB NO   :%lld\n                                                                        ", inf[n].mob);
     printf("BENF MOB NO   :%lld\n                                                                        ", mobno1);
     printf("OTP           :%d\n                                                                        ", a);
     printf("AMOUNT        :Rs.%d", amnt);
     printf("\n                                                                        ");
     printf("--------------------------------------------------------------");

     printf("\n                                                                        ");

     char choice[10];
     printf("DO YOU WISH TO CONFIRM ?........ENTER 'YES' AND IF NOT ENTER 'NO'\n                                                                        ");
     scanf("%s", choice);
     if (strcmp(choice, "YES\0") == 0 || strcmp(choice, "yes\0") == 0)
     {
          printf("\n                                                                        TRANSFER IS BEING PROCESSED");
          delay(1000);
          printf(".");
          delay(1000);
          printf(".");
          delay(1000);
          printf(".\n                                                                        ");
          printf("\n                                                                        TRANSFER PROCESSED SUCCESSFULLY!!\n                                                                        \n                                                                        ");
          int f = inf[n].bal;
          f = f - x;
          update("bal", n, f);
          Transaction(n, x, mobno1);
          time_t t;
          time(&t);
          SYSTEMTIME stime;
          GetSystemTime(&stime);
          printf("----------------------------------------------------------\n                                                                        ");
          printf("THE IMT IS VALID FOR 48 HOURS FROM %s                                                                        ", ctime(&t));
          printf("IMT ID               : 00100100000%d\n                                                                        ", stime.wSecond + stime.wMilliseconds);
          printf("ACCOUNT BALANCE      : Rs.%d\n                                                                        ", f);
          printf("----------------------------------------------------------\n                                                                        ");
          Wish();
     }
     else if (strcmp(choice, "NO\0") == 0 || strcmp(choice, "no\0") == 0)
     {
          system("cls");
          print_title();
          OPTIONS();
     }
}
void Recharge_Mobile()
{
     input(n);
     printf("\n                                                                        PLEASE ENTER 10-DIGIT MOBILE NUMBER\n                                                                        ");
     long long int mob_no;
     while (1)
     {
          scanf("%lld", &mob_no);
          if (mob_no < 1000000000 || mob_no > 10000000000)
          {
               SetColor(0);
               printf("\n                                                                        -------------------------\n                                                                        ");
               printf("INVALID MOBILE NUMBER\n                                                                        ");
               printf("-------------------------\n                                                                        ");
               SetColor(31);
               printf("\n                                                                        RE-ENTER MOBILE NUMBER\n                                                                        ");
               continue;
          }
          else
          {
               break;
          }
     }
     SELECT_Amnt();
     confirmation(mob_no);
}
void SELECT_Amnt()
{
     printf("\n                                                                        SELECT THE PLAN AMOUNT FOR RECHARGE\n                                                                        1. Rs.50\n                                                                        2. Rs.100\n                                                                        3. Rs.500\n                                                                        4. Rs.1000\n                                                                        ");
     int x;
     scanf("%d", &x);
     switch (x)
     {
     case 1:
          Amnt = 50;
          break;
     case 2:
          Amnt = 100;
          break;
     case 3:
          Amnt = 500;
          break;
     case 4:
          Amnt = 1000;
          break;
     default:
          break;
     }
}
void confirmation(long long int mobi_no)
{
     printf("\n                                                                        TO CONFIRM PRESS '1'\n                                                                        TO CHANGE CHOICE OF RECHARGE AMOUNT PRESS '2'\n                                                                        ");
     int y;
     scanf("%d", &y);
     switch (y)
     {
     case 1:
          if (inf[n].bal >= Amnt)
          {
               int f = inf[n].bal;
               f = f - Amnt;
               update("bal", n, f);
               Transaction(n, Amnt, mobi_no);
               delay();
               printf("\n                                                                        YOUR TRANSACTION IS UNDER PROCESS");
               delay();
               printf(".");
               delay();
               printf(".");
               delay();
               printf(".");
               printf("\n                                                                        \n                                                                        THE ENTERED MOBILE NUMBER HAS BEEN RECHARGED SUCCESSFULLY!!!\n                                                                        ACCOUNT BALANCE : Rs.%d\n                                                                        \n                                                                        ", f);
               delay();
               printf("--------------------------------------------------------------");
               printf("\n                                                                        ");
               printf("PLEASE CONFIRM MOBILE RECHARGE DETAILS\n                                                                        ");
               printf("--------------------------------------------------------------");
               printf("\n                                                                        ");
               printf("RECHARGED MOB NO   : %lld\n                                                                        ", mobi_no);
               printf("AMOUNT OF RECHARGE : Rs.%d", Amnt);
               printf("\n                                                                        ");
               printf("--------------------------------------------------------------");
               printf("\n                                                                        ");
               Wish();
               break;
          }
          else
          {
               SetColor(0);
               printf("\n                                                                        -------------------------------------------------\n                                                                        ");
               printf("ENOUGH BALANCE NOT AVAILABLE!!!\n                                                                        ");
               printf("SORRY FOR THE INCONVENIENCE\n                                                                        ");
               printf("-------------------------------------------------\n                                                                        ");
               SetColor(31);
               Amnt = 0;
               Wish();
          }
          break;
     case 2:
          SELECT_Amnt();
          confirmation(mobi_no);
          break;
     default:
          break;
     }
}

void pre_update(int n, int year)
{
     char line[100];
     char *temc = "prem";
     char tempn[10] = {0};
     sprintf(tempn, "%s%d.txt", temc, n);
     FILE *updet = fopen(tempn, "a");
     fprintf(updet, "\n%d", year);
     fclose(updet);

}
void Pay_Premium(int n)
{
     SYSTEMTIME stime;
GetSystemTime(&stime);
int Present_Month = stime.wMonth;
int Present_Year = stime.wYear;
int Present_Day = stime.wDay;
     int i, j=0,k=0,acc_balance,available_balance,premium = 0;
     char line[100];
     char *temc = "prem";
     char tempn[10] = {0};
     int lineno = 0;
     sprintf(tempn, "%s%d.txt", temc, n);
     FILE *cardi = fopen(tempn, "r");
     int temp[10] = {0};
     while(fgets(line, 99, cardi) != NULL)
     {
          temp[lineno++] = atoi(line);

     }
         for(int i=0;i<10;i++)
         {
              if(temp[i] == Present_Year)
              {
                  j++;

              }
              else
              {
                  continue;
              }
         }
         for(int i=0;i<10;i++)
         {
              if(temp[i] == Present_Year-1)
              {
                  k++;


              }
              else
              {
                  continue;
              }
         }
         if(j>0 && k>0)
         {
                    SetColor(0);
                    printf("\n                                                                        ----------------------------------------------------------\n                                                                     ");
                    printf("   YOUR PREMIUM HAS BEEN PAID ALREADY FOR YEAR %d!!!\n                                                                        ",Present_Year);
                    printf("----------------------------------------------------------\n                                                                     ");
                    SetColor(31);
                    Wish();
         }
         else if((j>0 && k==0) || (j==0 && k==0))
         {
                    SetColor(0);
                   printf("\n                                                                        ----------------------------------------------------------------------------\n                                                                        ");
                    printf(" YOUR INSURANCE POLICY HAS EXPIRED AS YOU DID NOT PAY PREMIUM IN %d!!!\n                                                                        ",Present_Year-1);
                    printf("----------------------------------------------------------------------------\n                                                                        ");
                   SetColor(31);
                    Wish();
                    
         }
         else
         {

         }

          input(n);
     acc_balance = inf[n].bal;
     premium = inf[n].pre;
     char response[5];

          printf("\n                                                                        ARE YOU SURE TO PAY THE PREMIUM? ('YES' OR 'NO')\n                                                                        ");
          scanf("%s", response);
          if (strcmp(response, "YES") == 0 || strcmp(response, "yes") == 0)
          {
               if (premium > acc_balance)
               {
                    SetColor(0);
                    printf("\n                                                                        -------------------------------------------------\n                                                                        ");
                    printf("ENOUGH BALANCE NOT AVAILABLE!!!\n                                                                        ");
                    printf("SORRY FOR THE INCONVENIENCE\n                                                                        ");
                    printf("-------------------------------------------------\n                                                                        ");
                    SetColor(31);
                    delay(6000);
                    Wish();
               }

               else
               {
                    printf("\n                                                                        PLEASE WAIT TRANSACTION IS PROCESSING");
                    delay(1000);
                    printf(".");
                    delay(1000);
                    printf(".");
                    delay(1000);
                    printf(".\n                                                                        ");
                    printf("----------------------------------------------------------\n                                                                        ");
                    printf(" PREMIUM OF Rs.%d WAS SUCCESSFULLY PAID FOR YEAR %d!!! \n                                                                     ", premium,Present_Year);
                    pre_update(n, Present_Year);
                    available_balance = acc_balance - premium;
                    printf("    AVAILABLE BALANCE: Rs.%d \n                                                                        ", available_balance);
                    printf("----------------------------------------------------------\n                                                                     ");
                    update("bal", n, available_balance);
                    Transaction(n, premium, 0);
                    Wish();
               }
          }
          else if (strcmp(response, "NO") == 0 || strcmp(response, "no") == 0)
          {
               delay(3000);
               system("cls");
               print_title();
               OPTIONS();
          }
         pre_update(4, Present_Year);



     fclose(cardi);

}
long long int accnum;
void acc_check()
{

     printf("\n                                                                        ENTER ACCOUNT NUMBER: ");
     scanf("%lld", &accnum);
     if (inf[n].acc == accnum)
     {
          SetColor(0);
          printf("                                                                        ---------------------------------");
          printf("ACCOUNT NUMBER IS NOT VALID\n                                                                        ");
          printf("---------------------------------");
          SetColor(31);
          acc_check();
     }
     for (int i = 1; i <= 5; i++)
     {
          input(i);
          if (inf[i].acc == accnum)
          {
               card2 = i;

               break;
          }
          if (i == 5)
          {
               SetColor(0);
               printf("                                                                        ---------------------------------\n                                                                        ");
               printf("ACCOUNT NUMBER IS NOT VALID\n                                                                        ");
               printf("---------------------------------");
               SetColor(31);
               acc_check();
          }
          if (inf[i].acc != accnum)
          {
               continue;
          }
     }
}
void Account_Based_Transfer()
{
     input(n);
     int i = 1;
     acc_check();
     int amont;
     while (1)
     {
          printf("\n                                                                        ENTER AMOUNT\n                                                                        ");
          scanf("%d", &amont);
          if (inf[n].bal < amont)
          {
               SetColor(0);
               printf("                                                                        ------------------------------------\n                                                                        ");
               printf("NOT ENOUGH BALANCE AVAILABLE\n                                                                        ");
               printf("------------------------------------\n                                                                        ");
               SetColor(31);
               delay(5000);
               Wish();
          }
          else if (inf[n].bal >= amont)
          {
               break;
          }
     }
     int g = amont;
     printf("\n                                                                        ");
     printf("---------------------------------------------");
     printf("\n                                                                            CONFIRMATION SCREEN\n                                                                        ");
     printf("---------------------------------------------");
     printf("\n                                                                        ");
     printf("FROM ACCOUNT NUMBER    :%lld\n                                                                        ", inf[n].acc);
     printf("TO ACCOUNT NUMBER      :%lld\n                                                                        ", accnum);
     printf("AMOUNT                 :Rs.%d\n                                                                        ", g);
     printf("---------------------------------------------\n                                                                        ");
     printf("\n                                                                        ");
     printf("DO YOU WISH TO CONFIRM?....'YES' OR 'NO'\n                                                                        ");
     char wish[10];
     scanf("%s", wish);
     if (strcmp(wish, "YES\0") == 0 || strcmp(wish, "yes\0") == 0)
     {
          printf("\n                                                                        TRANSFER IS BEING PROCESSED");
          delay(1000);
          printf(".");
          delay(1000);
          printf(".");
          delay(1000);
          printf(".\n                                                                        ");
          printf("TRANSFER PROCESSED SUCCESSFULLY!!\n                                                                        \n                                                                        ");
          int u = inf[n].bal - g;
          update("bal", n, u);
          Transaction(n, g, 0);
          int o = inf[card2].bal + g;
          update("bal", card2, o);
          Transaction(card2, g, 0);
          printf("ACCOUNT BALANCE:  Rs.%d \n                                                                        ", u);
          Wish();
     }
     else if (strcmp(wish, "NO\0") == 0 || strcmp(wish, "no\0") == 0)
     {
          system("cls");
          print_title();
          OPTIONS();
     }
}

void transaction_history()
{
     int j = 0;
     input(n);
     printf("\n                                                                        PLEASE WAIT WHILE WE COLLECT THE DATA");
     delay();
     printf(".");
     delay();
     printf(".");
     delay();
     printf(".\n                                                                        \n                                                                        ");
     while (j < no_lines)
     {
          printf("%s                                                                        ", inf[n].history[j]);
          j++;
     }
     printf("\n                                                                        ------------------------------------------------------------------------------------------\n                                                                        ");
     Wish();
}
void OPTIONS()
{
     printf("\n                                                                        WELCOME %s                                                                        PLEASE SELECT AN OPTION:\n                                                                        ", inf[n].nam);
     printf("1. CASH WITHDRAWAL\n                                                                        2. PIN CHANGE\n                                                                        3. CASH DEPOSIT\n                                                                        4. BALANCE INQUIRY\n                                                                        5. IMT\n                                                                        6. RECHARGE MOBILE\n                                                                        7. PAY PREMIUM\n                                                                        8. ACCOUNT BASED TRANSFER\n                                                                        9. SHOW TRANSACTION HISTORY\n                                                                        \n                                                                        ");
     printf("OPTION:");
     scanf("%d", &Option);
     switch (Option)
     {
     case 1:
          Cash_Withdrawal();
          break;
     case 2:
          Pin_Change();
          break;
     case 3:
          Cash_Deposit();
          break;
     case 4:
          Balance_Inquiry();
          break;
     case 5:
          IMT();
          break;
     case 6:
          Recharge_Mobile();
          break;
     case 7:
          Pay_Premium(n);
          break;
     case 8:
          Account_Based_Transfer();
          break;
     case 9:
          transaction_history();
          break;
     default:
          OPTIONS();
          break;
     }
}
int main()
{
    SYSTEMTIME stime;
GetSystemTime(&stime);
int Present_Month = stime.wMonth;
int Present_Year = stime.wYear;
int Present_Day = stime.wDay;
     system("COLOR 8F");
     print_title();
     delay();
     delay();
     printf("                                                                        PLEASE INSERT YOUR CARD AND ENTER YOUR 4-DIGIT PIN\n                                                                        ");
     printf("\n                                                                        CARD: ");
     scanf("%d", &n);
     if (n < 1 || n > 5)
     {
          SetColor(0);
          printf("\n                                                                        -------------------------");
          printf("\n                                                                        CARD DETAILS NOT FOUND!!!\n                                                                        ");
          printf("-------------------------");
          SetColor(31);
          delay(1000);
          delay(1000);
          delay(1000);
          system("cls");
          main();
     }
     input(n);
     if (inf[n].nam[0] == '0')
     {
          SetColor(0);
          printf("\n                                                                        -----------------------");
          printf("\n                                                                        YOUR CARD IS BLOCKED\n                                                                        ");
          printf("-----------------------\n                                                                        ");
          SetColor(31);
          delay(1000);
          delay(1000);
          delay(1000);
          system("cls");
          main();
          return 0;
     }

     if (Present_Year == inf[n].exp_yea)
     {
          if (Present_Month > inf[n].exp_mon)
          {
               SetColor(0);
               printf("\n                                                                        -----------------------------");
               printf("\n                                                                        SORRY YOUR CARD IS EXPIRED!\n                                                                        ");
               printf("-----------------------------\n                                                                        ");
               SetColor(31);
               delay(1000);
               delay(1000);
               delay(1000);
               system("cls");
               main();
          }
     }
     if (Present_Year > inf[n].exp_yea)
     {
          SetColor(0);
          printf("\n                                                                        -----------------------------");
          printf("\n                                                                        SORRY YOUR CARD IS EXPIRED!\n                                                                        ");
          printf("-----------------------------\n                                                                        ");
          SetColor(31);
          delay(1000);
          delay(1000);
          delay(1000);
          system("cls");
          main();
     }

     int Correct_PIN = inf[n].pin;
     /* value from the text file */
     int PIN;
     for (int j = 1; j <= 3; j++)
     {
          printf("                                                                        PIN: ");
          scanf("%d", &PIN);
          delay();
          if (Correct_PIN == PIN)
          {
               break;
          }
          else if (Correct_PIN != PIN && j <= 2)
          {
               SetColor(0);
               printf("                                                                        ---------------\n                                                                        ");
               printf("IN-VALID PIN\n                                                                        ");
               printf("----------------\n                                                                        ");
               SetColor(31);
               printf("\n                                                                        RE-ENTER PIN\n");
          }
          else if (Correct_PIN != PIN && j == 3)
          {
               SetColor(0);
               printf("\n                                                                        -----------------------");
               printf("\n                                                                        YOUR CARD IS BLOCKED\n                                                                        ");
               printf("-----------------------\n                                                                        ");
               SetColor(31);
               FILE *block;
               char *tempbi = "card";
               char tempb[20];
               sprintf(tempb, "%s%d.txt", tempbi, n);
               block = fopen(tempb, "w");
               fputc('0', block);
               fclose(block);
               delay(1000);
               delay(1000);
               delay(1000);
               system("cls");
               main();
               return 0;
          }
     }
     OPTIONS();
     return 0;
}
