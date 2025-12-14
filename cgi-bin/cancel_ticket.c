#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Content-type:text/html\n\n");

    /* -------- Login Check -------- */
    char current_user[50];
    FILE *cu = fopen("current_user.txt", "r");
    if (!cu || fgets(current_user, sizeof(current_user), cu) == NULL) {
        printf("<script>alert('Please login first!');window.location.href='../railway/login.html';</script>");
        return 0;
    }
    fclose(cu);

    /* -------- Read Ticket No -------- */
    char input[100];
    char ticket_no[20];
    fgets(input, sizeof(input), stdin);
    sscanf(input, "ticket_no=%[^&]", ticket_no);

    /* -------- Remove Cancelled Ticket -------- */
    FILE *fp = fopen("bookings.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[300];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char file_ticket[20];
        sscanf(line, "%[^,]", file_ticket);

        if (strcmp(file_ticket, ticket_no) != 0)
            fputs(line, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        remove("temp.txt");
        printf("<script>alert('Ticket not found!');window.location.href='../railway/cancel_ticket.html';</script>");
        return 0;
    }

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    /* -------- Promote From Waiting List -------- */
    FILE *wl = fopen("waiting_list.txt", "r");
    if (wl) {
        FILE *temp_wl = fopen("temp_wait.txt", "w");
        char first_wait[300];

        if (fgets(first_wait, sizeof(first_wait), wl)) {

            /* Parse waiting record */
            char t[20], n[50], src[50], dest[50], status[20];
            int age;

            sscanf(first_wait, "%[^,],%[^,],%d,%[^,],%[^,],%s",
                   t, n, &age, src, dest, status);

            /* Write promoted passenger as CONFIRMED */
            FILE *fp2 = fopen("bookings.txt", "a");
            fprintf(fp2, "%s,%s,%d,%s,%s,CONFIRMED\n",
                    t, n, age, src, dest);
            fclose(fp2);

            /* Copy remaining waiting list */
            while (fgets(line, sizeof(line), wl)) {
                fputs(line, temp_wl);
            }

            fclose(wl);
            fclose(temp_wl);

            remove("waiting_list.txt");
            rename("temp_wait.txt", "waiting_list.txt");

            printf("<script>");
            printf("alert('Ticket cancelled! Waiting passenger promoted to CONFIRMED.');");
            printf("window.location.href='../railway/thank_you.html';");
            printf("</script>");
            return 0;
        }

        fclose(wl);
        fclose(temp_wl);
        remove("temp_wait.txt");
    }

    /* -------- No Waiting Passenger -------- */
    printf("<script>");
    printf("alert('Ticket cancelled successfully! No passengers in waiting list.');");
    printf("window.location.href='../railway/thank_you.html';");
    printf("</script>");

    return 0;
}
