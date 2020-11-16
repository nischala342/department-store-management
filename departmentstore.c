#include <stdio.h>
#include<stdlib.h>
#include<string.h>
void MAINMENU();
void DISPLAYMENU();
void DISPLAYBILL();
void AddItemsFromCart();
void AddItemsFromMenu();
void DeleteItemsFromCart();
void DeeleteQuantityFromCart();
void userlogin();
struct cart{
    char ProductName[20];//i added product name here as well as we need it while displaying bill
    char ProductID[20];
    int Price;
    int Quantity;
    int discount;
    struct cart *next;
};
struct Menu{
    char ProductName[20];
    char ProductID[20];
    int Price;
    int ProductStock;
    int discount;
    struct Menu *leftChild;
    struct Menu *rightChild;  //while retriving menu from file we are making it in to a BST
};
struct user{
    char username[20];
    char password[20];
}*pUser;
void userlogin(void){
    FILE *fp;
    char uName[20], pwd[15];int i;char c;

    pUser=(struct user *)malloc(sizeof(struct user));
    Authentication:
    printf("1. Login Through An Existing Account\n2. Create New account\n");
    scanf("%d",& i);
    switch(i){
        case 1:
            if ( ( fp=fopen("UserInfo.txt", "r+")) == NULL) {
                if ( ( fp=fopen("UserInfo.txt", "w+")) == NULL) {
                    printf ("Could not open file\n");
                    exit ( 1);
                }
            }
            printf("Username: ");
            scanf("%s",uName);
            printf("Password: ");
            scanf("%s",pwd);
            while ( fread (pUser, sizeof(struct user), 1, fp) == 1) {
                if( strcmp ( pUser->username, uName) == 0) {
                    printf ("Match username\n");
                    if( strcmp ( pUser->password, pwd) == 0) {
                        printf ("Match password\n");
                        //accessUser();
                    }
                }
            }
            break;

        case 2:
            do
            {
                if ( ( fp=fopen("UserInfo.txt", "a+")) == NULL) {
                    if ( ( fp=fopen("UserInfo.txt", "w+")) == NULL) {
                        printf ("Could not open file\n");
                        exit (1);
                    }
                }
                printf("Choose A Username: ");
                scanf("%9s",pUser->username);
                printf("Choose A Password: ");
                scanf("%9s",pUser->password);
                fwrite (pUser, sizeof(struct user), 1, fp);
                printf("Add another account? (Y/N): ");
                scanf(" %c",&c);//skip leading whitespace
                fclose(fp);
            }while(c=='Y'||c=='y');
            goto Authentication;
            break;
    }
    free ( pUser);//free allocated memory
    fclose(fp);
}
void MAINMENU(){
    int mainmenu_choice;
    while(1){
        printf("1.Add\n2.Delete\n3.Display Menu\n4.Display bill\n5.Exit\n");
        scanf("%d",&mainmenu_choice);
        switch(mainmenu_choice){
            case 1: ADD();
                    break;
            case 2: DELETE();
                    break;
            case 3: DISPLAYMENU();
                    break;
            case 4 :DISPLAYBILL();
                    break;
            case 5: return 0;
                    break;
            default:printf("Invalid choice\n");
                    break;
        }
    DISPLAYBILL();
    }
}
void AddItemsFromCart(){
    //returning the updated cart 
}
void AddItemsFromMenu(){
    
}
void DeleteItemsFromCart(){
    
}
void DeeleteQuantityFromCart(){
    
}
void ADD(){
    while(1){
        int add_choice;
        printf("1.Add to cart by editing cart\n2.Add to cart by viewing menu\n3.exit from add funtion\n");
        scanf("%d",&add_choice);
        switch(add_choice){
            case 1: AddItemsFromCart();
                    break;
            case 2: AddItemsFromMenu();
                    break;
            case 3: return;
                    break;
            default: printf("Wrong Choice\n");
                    break;
        }
    }
}
void DELETE(){
    while(1){
        int delete_choice;
        printf("1.Deleting whole item\n2.Delete Quantity\n3.exit from delete funtion\n");
        scanf("%d",&delete_choice);
        switch(delete_choice){
            case 1: DeleteItemsFromCart();
                    break;
            case 2: DeeleteQuantityFromCart();
                    break;
            case 3: return;
                    break;
            default: printf("Wrong Choice\n");
                    break;
        }
    }
}
void DISPLAYMENU(){
    
}
void DISPLAYBILL(){
    
}
int main(){
    MAINMENU();
}