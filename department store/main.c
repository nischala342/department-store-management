#include <stdio.h>
#include<stdlib.h>
#include<string.h>
void MAINMENU ();
void ADD ();
void DELETE ();
void DISPLAYMENU ();
void DISPLAYBILL ();
void AddItemsFromCart ();
void AddItemsFromMenu ();
void DeleteItemsFromCart ();
void DeeleteQuantityFromCart ();
void userlogin ();
void subcatmenu ();
struct cart
{
  char ProductName[20];		//i added product name here as well as we need it while displaying bill
  char ProductID[20];
  int Price;
  int Quantity;
  int discount;
  struct cart *next;
};
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
void
userlogin (void)
{
  FILE *fp;
  char uName[20], pwd[15];
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
      printf ("Username: ");
      scanf ("%s", uName);
      printf ("Password: ");
      scanf ("%s", pwd);
      while (fread (pUser, sizeof (struct user), 1, fp) == 1)
	{
	  if (strcmp (pUser->username, uName) == 0)
	    {
	      printf ("Match username\n");
	      if (strcmp (pUser->password, pwd) == 0)
		{
		  printf ("Match password\n");
		  //accessUser();
		}
	    }
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
	  scanf ("%9s", pUser->username);
	  printf ("Choose A Password: ");
	  scanf ("%9s", pUser->password);
	  fwrite (pUser, sizeof (struct user), 1, fp);
	  printf ("Add another account? (Y/N): ");
	  scanf (" %c", &c);	//skip leading whitespace
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
      for (int j = 0; j < row; j++)
	{
	  fscanf (subcat, "%d%s%d%d", &id, name, &cost, &quan);
	  item = InsertitemMenu (item, id, name, cost, quan);
	}
      do
	{
	  printf
	    ("TO VIEW COSTS FROM LOWEST TO HIGHEST PRESS 1\nTO VIEW COSTS FROM HIGHEST TO LOWEST PRESS 2\nTO VIEW WITHIN A RANGE PRESS 3\n");
	  scanf ("%d", &user_choice);
	  switch (user_choice)
	    {
	    case 1:
	      inorder (item);
	      break;
	    case 2:
	      reverse_inorder (item);
	      break;
	    case 3:
	      printf ("Enter lower limit\n");
	      scanf ("%d", &range_one);
	      printf ("Enter upper limit\n");
	      scanf ("%d", &range_two);
	      range (range_one, range_two, item);
	      break;
	    }
	}
      while (user_choice != 4);
    }
}

void
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
      DISPLAYBILL ();
    }
}

void
AddItemsFromCart ()
{
  //returning the updated cart 
}

void
AddItemsFromMenu ()
{

}

void
DeleteItemsFromCart ()
{

}

void
DeeleteQuantityFromCart ()
{

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
	  AddItemsFromMenu ();
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
  while (1)
    {
      int delete_choice;
      printf
	("1.Deleting whole item\n2.Delete Quantity\n3.exit from delete funtion\n");
      scanf ("%d", &delete_choice);
      switch (delete_choice)
	{
	case 1:
	  DeleteItemsFromCart ();
	  break;
	case 2:
	  DeeleteQuantityFromCart ();
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

}

int
main ()
{
  userlogin ();
  MAINMENU ();
}
