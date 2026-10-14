#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    int final_fee;
};

int main() {
    struct UserAccount accounts[100];
    int n, i;
    int total_revenue = 0;
    int downgraded_count = 0;

    do {
        printf("Nhap so luong tai khoan N (1 <= N <= 100): ");
        scanf("%d", &n);
        if (n < 1 || n > 100) {
            printf("Loi: N phai nam trong khoang [1, 100]. Vui long nhap lai!\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &accounts[i].user_id);
        
        printf("Ten tai khoan (username): ");
        scanf(" %[^\n]", accounts[i].username);

        do {
            printf("Loai goi hien tai (1=Free, 2=Personal, 3=Family): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
                printf("Loi: Loai goi khong hop le. Vui long nhap lai!\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do {
            printf("So ngay no cuoc: ");
            scanf("%d", &accounts[i].days_overdue);
            if (accounts[i].days_overdue < 0) {
                printf("Loi: So ngay no cuoc khong duoc am. Vui long nhap lai!\n");
            }
        } while (accounts[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi: ");
            scanf("%d", &accounts[i].active_devices);
            if (accounts[i].active_devices < 0) {
                printf("Loi: So thiet bi khong duoc am. Vui long nhap lai!\n");
            }
        } while (accounts[i].active_devices < 0);
    }

    for (i = 0; i < n; i++) {
        int base_fee = 0;
        int penalty_fee = 0;

        if (accounts[i].days_overdue >= 3) {
            if (accounts[i].plan_type == 2 || accounts[i].plan_type == 3) {
                downgraded_count++;
            }
            accounts[i].plan_type = 1;
        }

        if (accounts[i].plan_type == 1) {
            base_fee = 0;
        } else if (accounts[i].plan_type == 2) {
            base_fee = 120000;
        } else if (accounts[i].plan_type == 3) {
            base_fee = 250000;
        }

        if (accounts[i].plan_type == 2 && accounts[i].active_devices > 1) {
            penalty_fee = (accounts[i].active_devices - 1) * 30000;
        }

        accounts[i].final_fee = base_fee + penalty_fee;
        total_revenue += accounts[i].final_fee;
    }

    printf("\n=============================== BAO CAO SAU RA SOAT ===============================\n");
    printf("%-10s %-20s %-10s %-15s %-15s %-20s\n", 
           "MA TK", "TEN TK", "MA GOI", "SO THIET BI", "NO CUOC (NGAY)", "PHI THUC THU (VND)");
    printf("-----------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10d %-15d %-15d %-20d\n",
               accounts[i].user_id,
               accounts[i].username,
               accounts[i].plan_type,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               accounts[i].final_fee);
    }
    printf("-----------------------------------------------------------------------------------\n");
    printf("Tong doanh thu ky billing thuc te thu duoc: %d VND\n", total_revenue);
    printf("Tong so tai khoan da bi he thong ha cap ve Free: %d\n", downgraded_count);
    printf("===================================================================================\n");

    return 0;
}