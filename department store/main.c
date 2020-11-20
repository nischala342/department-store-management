#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct cart
{
  char ProductName[20];		//i added product name here as well as we need it while displaying bill
  int ProductID;
  int cost;
  int quantity;
  struct cart *link;
} *customer;
struct items
{
  int id;
  int cost;
  char name[10];
  int quantity;
  struct items *leftChild;
  struct items *rightChild;
};
struct user
{
  char username[20];
  char password[20];
} *pUser;
int MAINMENU ();
void ADD ();
void AddItemsFromCart ();
void AddItemsFromMenu (int, struct items *);
void traverse_to_add(int,int);
void insert_cart(int,char[],int,int);
void DELETE ();
void DeleteItemsFromCart (int);
void DeleteQuantityFromCart ();
void traverse_to_delete(int,int);
int getIndex(int);
void traverse ();
void DISPLAYMENU ();
struct items* InsertitemMenu(struct items*,int,char*,int,int);
void reverse_inorder(struct items*);
void inorder(struct items*);
struct items* inorder_cart(int,struct items*);
void range(int,int,struct items*);
struct items* newNode(int,char*,int,int);
void subcatmenu ();
void DISPLAYBILL ();
void userlogin ();
void ModifyFile(int,int,int);
void
ModifyFile (int findid, int modifyquantity, int flag)
{
  FILE *fp;
  int id, quantity;
  if (1 <= findid && findid <= 15)
    {
      fp = fopen ("fruits.txt", "r+");
    }
  else if (16 <= findid && findid <= 30)
    {
      fp = fopen ("vegetables.txt", "r+");
    }
  else if (31 <= findid && findid <= 45)
    {
      fp = fopen ("diary.txt", "r+");
    }
  else if (46 <= findid && findid <= 60)
    {
      fp = fopen ("stationary.txt", "r+");
    }
  int row, col;
  fscanf (fp, "%d %d", &row, &col);
  while (fp != NULL)
    {
      fscanf (fp, "%d %*s %*d %d", &id, &quantity);
      if (findid == id)
	{
	  if (flag == 1)
	    {
	      fseek (fp, -4, SEEK_CUR);
	      fprintf (fp, "%d\n", quantity + modifyquantity);
	      break;
	    }
	  else
	    {
	      fseek (fp, -4, SEEK_CUR);
	      fprintf (fp, "%d\n", quantity - modifyquantity);
	      break;
	    }
	}
    }
  fclose (fp);
  return;
}

void
userlogin (void)
{
  FILE *fp;
  char uName[20], pwd[20];
  int i;
  char c;

  pUser = (struct user *) malloc (sizeof (struct user));
Authentication:
  printf ("1. Login Through An Existing Account\n2. Create New account\n");
  scanf ("%d", &i);
  switch (i)
    {
    case 1:
      if ((fp = fopen ("UserInfo.txt", "r+")) == NULL)
	{
	  if ((fp = fopen ("UserInfo.txt", "w+")) == NULL)
	    {
	      printf ("Could not open file\n");
	      exit (1);
	    }
	}
      int flag_user = 0;
      int flag_pass = 0;
      printf ("Username: ");
      scanf ("%s", uName);
      printf ("Password: ");
      scanf ("%s", pwd);
      while (fread (pUser, sizeof (struct user), 1, fp) == 1)
	{
	  if (strcmp (pUser->username, uName) == 0)
	    {
	      flag_user = 1;
	      if (strcmp (pUser->password, pwd) == 0)
		{
		  flag_pass = 1;
		  //accessUser();
		}
	    }
	}
      if (flag_pass != 1 || flag_user != 1)
	{
	  printf ("INVALID USERNAME OR PASSWORD!! PLEASE TRY AGAIN!!");
	  goto Authentication;
	}
      break;

    case 2:
      do
	{
	  if ((fp = fopen ("UserInfo.txt", "a+")) == NULL)
	    {
	      if ((fp = fopen ("UserInfo.txt", "w+")) == NULL)
		{
		  printf ("Could not open file\n");
		  exit (1);
		}
	    }
	  printf ("Choose A Username: ");
	  scanf ("%s", pUser->username);
	  printf ("Choose A Password: ");
	  scanf ("%s", pUser->password);
	  fwrite (pUser, sizeof (struct user), 1, fp);
	  printf ("Add another account? (Y/N):");
	  scanf ("\n%c", &c);	//skip leading whitespace
	  fclose (fp);
	}
      while (c == 'Y' || c == 'y');
      goto Authentication;
      break;
    }
  free (pUser);			//free allocated memory
  fclose (fp);
}

void
reverse_inorder (struct items *root)
{

  if (root == NULL)
    {
      return;
    }
  reverse_inorder (root->rightChild);
  printf ("ID:%d NAME:%s COST:%d QUANTITY:%d\n", root->id, root->name,
	  root->cost, root->quantity);
  reverse_inorder (root->leftChild);
}

void
inorder (struct items *root)
{
  if (root != NULL)
    {
      inorder (root->leftChild);
      printf ("ID:%d NAME:%s COST:%d QUANTITY:%d\n", root->id, root->name,
	      root->cost, root->quantity);
      inorder (root->rightChild);
    }
}

void
range (int range_one, int range_two, struct items *root)
{
  if (root != NULL)
    {
      range (range_one, range_two, root->leftChild);
      if (root->cost >= range_one && root->cost <= range_two)
	{
	  printf ("%d %s %d %d\n", root->id, root->name, root->cost,
		  root->quantity);
	}
      range (range_one, range_two, root->rightChild);
    }
}

struct items *
newNode (int id, char name[], int cost, int quantity)
{
  struct items *temp = (struct items *) malloc (sizeof (struct items));
  temp->id = id;
  temp->cost = cost;
  temp->quantity = quantity;
  strcpy (temp->name, name);
  temp->leftChild = temp->rightChild = NULL;
  return temp;
}

struct items *
InsertitemMenu (struct items *node, int id, char name[], int cost,
		int quantity)
{
  if (node == NULL)
    return newNode (id, name, cost, quantity);
  if (cost < node->cost)
    node->leftChild =
      InsertitemMenu (node->leftChild, id, name, cost, quantity);
  else
    node->rightChild =
      InsertitemMenu (node->rightChild, id, name, cost, quantity);
  return node;
}

void
subcatmenu ()
{
  FILE *file;
  char ch;
  int cat_no[100];
  file = fopen ("subcategories.txt", "r");
  int count = 0;
  while ((ch = fgetc (file)) != EOF)
    {
      if (isdigit (ch))
	{
	  cat_no[count] = ch - '0';
	  count++;
	}
      printf ("%c", ch);
    }
  printf ("\nTO VIEW EACH CATEGORY ITEM PRESS CATEGORY NUMBER\n");
}

void
DISPLAYMENU ()
{
  int option, user_choice, range_one, range_two;
  while (1)
    {
      subcatmenu ();
      FILE *subcat;
      scanf ("%d", &option);
      switch (option)
	{
	case 1:
	  subcat = fopen ("fruits.txt", "r");
	  break;
	case 2:
	  subcat = fopen ("vegetables.txt", "r");
	  break;
	case 3:
	  subcat = fopen ("diary.txt", "r");
	  break;
	case 4:
	  subcat = fopen ("stationery.txt", "r");
	  break;
	default:
	  return;
	  break;
	}
      int cost, quan, id;
      char name[20];
      struct items *item = NULL;
      int row, col;
      fscanf (subcat, "%d%d", &row, &col);
      int j;
      for ( j = 0; j < row; j++)
	{
	  fscanf (subcat, "%d%s%d%d", &id, name, &cost, &quan);
	  item = InsertitemMenu (item, id, name, cost, quan);
	}
      do
	{
	  printf
	    ("TO VIEW COSTS FROM LOWEST TO HIGHEST PRESS 1\nTO VIEW COSTS FROM HIGHEST TO LOWEST PRESS 2\nTO VIEW WITHIN A RANGE PRESS 3\n");
	  scanf ("%d", &user_choice);
	  int id;
	  switch (user_choice)
	    {
	    case 1:
	      inorder (item);
	      printf ("Enter the id: ");
	      scanf ("%d", &id);
	      if (id > 0)
		{
		  AddItemsFromMenu (id, item);
		}
	      break;
	    case 2:
	      reverse_inorder (item);
	      printf ("Enter the id: ");
	      scanf ("%d", &id);
	      if (id > 0)
		{
		  AddItemsFromMenu (id, item);
		}
	      break;
	    case 3:
	      printf ("Enter lower limit\n");
	      scanf ("%d", &range_one);
	      printf ("Enter upper limit\n");
	      scanf ("%d", &range_two);
	      range (range_one, range_two, item);
	      printf ("Enter the id: ");
	      scanf ("%d", &id);
	      if (id > 0)
		{
		  AddItemsFromMenu (id, item);
		}
	      break;
	    }
	}
      while (user_choice != 4);
    }
}

int
MAINMENU ()
{
  int mainmenu_choice;
  while (1)
    {
      printf ("1.Add\n2.Delete\n3.Display Menu\n4.Display bill\n5.Exit\n");
      scanf ("%d", &mainmenu_choice);
      switch (mainmenu_choice)
	{
	case 1:
	  ADD ();
	  break;
	case 2:
	  DELETE ();
	  break;
	case 3:
	  DISPLAYMENU ();
	  break;
	case 4:
	  DISPLAYBILL ();
	  break;
	case 5:
	  return 0;
	  break;
	default:
	  printf ("Invalid choice\n");
	  break;
	}
    }
    DISPLAYBILL ();
  return 0;
}

void
traverse_to_add (int id, int add_quantity)
{
  struct cart *temp;
  temp = customer;
  while (temp != NULL)
    {
      if (temp->ProductID == id)
	{
	  temp->quantity += add_quantity;
	}
      temp = temp->link;
    }
}

void
AddItemsFromCart ()
{
  int add_quantity;
  int id;
  traverse ();
  printf ("Enter the ID of the product for which you want to add: ");
  scanf ("%d", &id);
  printf ("Enter the quantity to be added: ");
  scanf ("%d", &add_quantity);
  traverse_to_add (id, add_quantity);
  traverse ();
  ModifyFile (id, add_quantity, 0);
}

struct items *
inorder_cart (int id, struct items *root)
{
  if (root != NULL)
    {
      inorder_cart (id, root->leftChild);
      if (root->id == id)
	{
	  return root;
	}
      inorder_cart (id, root->rightChild);
    }
}

void
insert_cart (int id, char name[], int quantity, int cost)
{
  struct cart *temp = (struct cart *) malloc (sizeof (struct cart));
  if (customer == NULL)
    {
      temp->ProductID = id;
      strcpy (temp->ProductName, name);
      temp->cost = cost;
      temp->quantity = quantity;
      temp->link = NULL;
      customer = temp;
    }
  else
    {
      temp->ProductID = id;
      strcpy (temp->ProductName, name);
      temp->cost = cost;
      temp->quantity = quantity;
      temp->link = customer;
      customer = temp;
    }
  printf ("Product added to the cart successfully\n");
}

void
traverse ()
{
  struct cart *temp;
  temp = customer;
  printf ("Elements in the linked list are:\n");
  while (temp != NULL)
    {
      printf ("%d %s %d %d\n", temp->ProductID, temp->ProductName,
	      temp->quantity, temp->cost);
      temp = temp->link;
    }
}

void
AddItemsFromMenu (int id, struct items *item)
{
  int quantity;
  struct items *temp = inorder_cart (id, item);
  while (1)
    {
      printf ("Enter quantity of the item: ");
      scanf ("%d", &quantity);
      if (quantity > 0 && quantity < temp->quantity)
	{
	  break;
	}
    }
  insert_cart (temp->id, temp->name, quantity, temp->cost);
  ModifyFile (id, quantity, 0);
  traverse ();
}

int
getIndex (int ID)
{
  struct cart *q;
  q = customer;
  int count = 0;
  while (q != NULL)
    {
      count++;
      if (q->ProductID == ID)
	{
	  printf ("Yeah\n");
	  ModifyFile (ID, q->quantity, 1);
	  break;
	}
      q = q->link;
    }
  return count - 1;
}

void
DeleteItemsFromCart (int position)
{
  struct cart *temp = customer;
  if (customer == NULL)
    return;
  if (position == 0)
    {
      customer = temp->link;
      free (temp);
      return;
    }
  for (int i = 0; temp != NULL && i < position - 1; i++)
    temp = temp->link;
  if (temp == NULL || temp->link == NULL)
    return;
  struct cart *link = temp->link->link;
  free (temp->link);
  temp->link = link;
}

void
traverse_to_delete (int id, int del_quantity)
{
  struct cart *temp;
  temp = customer;
  while (temp != NULL)
    {
      if (temp->ProductID == id)
	{
	  if (temp->quantity > del_quantity)
	    temp->quantity -= del_quantity;
	  else
	    {
	      printf
		("Sorry! changes can not be made as you tried to delete more than you have!\n");
	    }
	}
      temp = temp->link;
    }
  ModifyFile (id, del_quantity, 1);
}

void
DeleteQuantityFromCart ()
{
  int del_quantity;
  int id;
  traverse ();
  printf ("Enter the ID of the product for which you want to delete: ");
  scanf ("%d", &id);
  printf ("Enter the quantity to be deleted: ");
  scanf ("%d", &del_quantity);
  traverse_to_delete (id, del_quantity);
  traverse ();
}

void
ADD ()
{
  while (1)
    {
      int add_choice;
      printf
	("1.Add to cart by editing cart\n2.Add to cart by viewing menu\n3.exit from add funtion\n");
      scanf ("%d", &add_choice);
      switch (add_choice)
	{
	case 1:
	  AddItemsFromCart ();
	  break;
	case 2:
	  DISPLAYMENU ();
	  break;
	case 3:
	  return;
	  break;
	default:
	  printf ("Wrong Choice\n");
	  break;
	}
    }
}

void
DELETE ()
{
  int ID;
  while (1)
    {
      int delete_choice;
      printf
	("1.Deleting whole item\n2.Delete Quantity\n3.exit from delete funtion\n");
      scanf ("%d", &delete_choice);
      switch (delete_choice)
	{
	case 1:
	  traverse ();
	  printf ("Enter the ID of the Product to be deleted: ");
	  scanf ("%d", &ID);
	  int id = getIndex (ID);
	  printf ("%d", id);
	  DeleteItemsFromCart (id);
	  traverse ();
	  break;
	case 2:
	  DeleteQuantityFromCart ();
	  break;
	case 3:
	  return;
	  break;
	default:
	  printf ("Wrong Choice\n");
	  break;
	}
    }
}

void
DISPLAYBILL ()
{
  struct cart *temp = customer;
  int total = 0;
  while (temp != NULL)
    {
      printf ("%d  %s  %d %d\n", temp->ProductID, temp->ProductName,
	      temp->cost, temp->quantity);
      total += (temp->cost * temp->quantity);
      temp = temp->link;
    }
  printf ("\n%d\n", total);
}

int
main ()
{
  userlogin ();
  MAINMENU ();
}
