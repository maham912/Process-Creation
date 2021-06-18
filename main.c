#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables*/
struct node {
	int parent;
	int first_child;
	int older_sibling;
	int younger_sibling;
} *pcb = NULL;

int num_processes;

typedef struct node pcb_type;

/***************************************************************/
void parameter() {

	/* Declare local variables */

	/* Prompt for maximum number of processes */
	printf("Enter the maximum number of processes: ");
	scanf("%d", &num_processes);
	
	/* Allocate memory for dynamic array of PCB's */
	pcb = (pcb_type*)malloc(num_processes * sizeof(pcb_type));
	
	/* Initialize PCB[0] */
	pcb[0].parent = 0;
	pcb[0].first_child = -1;
	pcb[0].older_sibling = -1;
	pcb[0].younger_sibling = -1;
	
	/* Intitialize all other PCBs' parent, first_child, younger_sibiling, older_sibling */
	for (int i = 1; i < num_processes; i++)
	{
		pcb[i].parent = -1;
		pcb[i].first_child = -1;
		pcb[i].older_sibling = -1;
		pcb[i].younger_sibling = -1;
	}
	
  return;
}


/***************************************************************/
void printr() {
    
	/* Declare local variables */
	int i;

    printf("i\tParent\tFirst\tOlder\tYounger\n");
    printf("----------------------------------\n");


	/* For each existing PCB, print valid fields */
	for (i=0; i < num_processes; i++)
	{
	    
	    printf("%d", i);

		if (pcb[i].parent!= -1){
			printf("\t%d", pcb[i].parent);
		}
		else printf("\t");
		if (pcb[i].first_child != -1){
			printf("\t%d", pcb[i].first_child);
		}
		else printf("\t");

		if (pcb[i].older_sibling != -1){
			printf("\t%d", pcb[i].older_sibling);
		}
		else printf("\t");

		if (pcb[i].younger_sibling != -1){
			printf("\t%d", pcb[i].younger_sibling);
		}
		else printf("\t");

	    printf(" \n");

	}
	

  return;
}

/***************************************************************/
void create() {
  
	/* Declare local variables */
	int p;
	int q=1;
	int next_child;
	int num_children = 0;
	
	/* Prompt for the parent PCB index */
	printf("Enter the parent process index: ");
	scanf("%d", &p);
	
	/* Search for the next unused PCB index q */
  while (pcb[q].parent != -1){
	  q++;
  }
	/* Record the parent PCB index p in PCB[q] */
	pcb[q].parent = p;

	/* Initialize the first_child & younger_sibling of PCB[q] */ // ****************** NOT SURE IF THIS IS CORRECT BELOW
    pcb[q].first_child = -1;
    pcb[q].younger_sibling = -1;

	/* Check if parent PCB has no first child--is so, set fields appropriately */
	if (pcb[p].first_child == -1)
	{
		pcb[p].first_child = q;
		num_children = 1;
	}
	
	/* Else, search for appropriate available spot for next child, set fields appropriately */
	else {
		num_children = 2;
		next_child = pcb[p].first_child;
		while (pcb[next_child].younger_sibling != -1 )
		{
			next_child = pcb[next_child].younger_sibling;
			num_children++;
		}
		pcb[next_child].younger_sibling = q;
	pcb[q].older_sibling = next_child;
	}
	
	
	/* Print message indicating the creation of the ith child of process p at q */
	printf("cr[%d]:\tcreates the %dth child of PCB[%d] at PCB[%d]\n\n", p, num_children, p, q);
	/* NOTE: do not use the letters i,p,q directly, but the values of each variable */
   
	/* Print PCB table */
	printr();
  return;
}


/***************************************************************/
void destroy(int q) {

	/* If the formal parameter is -1, return */ 
	if(q == -1) return;
	/* Else:
		Call this procedure on the current PCB's younger sibling
		Call this procedure on the current PCB's first child
		Set all fields to invalid 
		Print current PCB to be destroyed
	*/
	else
	{
		destroy(pcb[q].younger_sibling);
		destroy(pcb[q].first_child);
		printf("PCB[%d]\t\n",q);
		pcb[q].parent = -1;
		pcb[q].first_child = -1;
		pcb[q].older_sibling = -1;
		pcb[q].younger_sibling = -1;
	}
	
	
  return;
}


/***************************************************************/
void destroyer() {
  
	/* Declare local variables */
	int p;
	
	/* Prompt for the parent PCB index p*/
	printf("Enter the process whose descendants are to be destoryed: ");
	scanf("%d", &p);

	/* Print message indicating the destruction of the descendants of PCB[p] */
	printf("de[%d]:\tdestroys all the descendants of PCB[%d] which includes: ", p, p);
	
	/* Call recursive procedure on PCB[p]'s first child */
	destroy(pcb[p].first_child);
	
	/* Set PCB[p]'s first child to invalid */
	pcb[p].first_child = -1;

	/* Print PCB table */
	printf("\n");
//	printr();
	
  return;
}


/***************************************************************/
void quit() {

	/* If the dynamic array "PCB" is not NULL, free the memory */
	if (pcb != NULL) free(pcb);
  return;
}

/***************************************************************/
int main() {

	/* Declare local variables */
	int choice;
	
	/* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
while ( choice != 4)
{
    printf("Process creation and destruction\n");
	printf("--------------------------------\n");
	printf("1) Enter parameters\n");
	printf("2) Create a new child process\n");
	printf("3) Destroy all descendants of a process\n");
	printf("4) Quit program and free memory\n\n");
	
	printf("Enter selection: ");
	scanf("%d", &choice);

	
	if (choice == 1)
	{
	   parameter();
	}
	
	else if (choice == 2)
	{
	   create();
//	   printr();
	}
	
	else if (choice == 3)
	{
	   destroyer();
	   	printr();
	}
	else if (choice == 4)
	{
	   quit();
	}
	
} //end while loop

  return 1;
}


