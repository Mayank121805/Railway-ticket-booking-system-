#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Content-type:text/html\n\n");

    /* ===== HTML + CSS HEADER ===== */
    printf("<!DOCTYPE html>");
    printf("<html><head><title>Booked Tickets</title>");

    printf("<style>");
    printf("body{margin:0;font-family:Poppins,Arial;"
           "background:linear-gradient(135deg,#0a0f1f,#111827,#1e293b);"
           "color:#f1f5f9;display:flex;flex-direction:column;align-items:center;}");

    printf("h2{margin:30px 0;font-size:26px;}");

    printf("table{border-collapse:collapse;"
           "background:rgba(17,24,39,0.9);"
           "border-radius:14px;overflow:hidden;"
           "box-shadow:0 0 25px rgba(59,130,246,0.25);}");

    printf("th,td{padding:12px 18px;text-align:center;}");

    printf("th{background:#0f172a;color:#60a5fa;font-weight:600;}");

    printf("tr:nth-child(even){background:rgba(255,255,255,0.04);}");

    printf("tr:hover{background:rgba(59,130,246,0.15);}");    

    printf("</style></head><body>");

    /* ===== FILE READ ===== */
    FILE *fp = fopen("bookings.txt", "r");
    if (!fp) {
        printf("<h3>No bookings yet.</h3>");
        printf("</body></html>");
        return 0;
    }

    printf("<h2>Booked Tickets</h2>");
    printf("<table>");
    printf("<tr>"
           "<th>Ticket No</th>"
           "<th>Name</th>"
           "<th>Age</th>"
           "<th>From</th>"
           "<th>To</th>"
           "</tr>");

    char line[256];
    char ticket[20], name[50], src[50], dst[50], status[20];
    int age;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%[^,],%[^,],%d,%[^,],%[^,],%s",
                   ticket, name, &age, src, dst, status) == 6) {

            printf("<tr>");
            printf("<td>%s</td>", ticket);
            printf("<td>%s</td>", name);
            printf("<td>%d</td>", age);
            printf("<td>%s</td>", src);
            printf("<td>%s</td>", dst);
            printf("</tr>");
        }
    }

    printf("</table>");
    fclose(fp);

    printf("</body></html>");
    return 0;
}
