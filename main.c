#include <stdio.h>
#include <stdlib.h>

/* Defining structures and global variables*/
struct node {
	int parent;
	int first_child;
	int older_sibling;
	int younger_sibling;
} *pcb = NULL;

int num_processes;

typedef struct node pcb_type;

void parameter() {


	printf("Enter the maximum number of processes: ");
	scanf("%d", &num_processes);
	
	/* Allocating memory for dynamic array of Process control blocks (PCB's) */
	pcb = (pcb_type*)malloc(num_processes * sizeof(pcb_type));
	
	/* Initialize PCB[0] */
	pcb[0].parent = 0;
	pcb[0].first_child = -1;
	pcb[0].older_sibling = -1;
	pcb[0].younger_sibling = -1;
	
	/* Intitializing all other PCBs' parent, first_child, younger_sibiling, older_sibling */
	for (int i = 1; i < num_processes; i++)
	{
		pcb[i].parent = -1;
		pcb[i].first_child = -1;
		pcb[i].older_sibling = -1;
		pcb[i].younger_sibling = -1;
	}
	
  return;
}


void printr() {
    
	int i;
    printf("i\tParent\tFirst\tOlder\tYounger\n");
    printf("----------------------------------\n");

	/* For each existing PCB, we print valid fields */
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

void create() {
  
	int p;
	int q=1;
	int next_child;
	int num_children = 0;
	
	printf("Enter the parent process index: ");
	scanf("%d", &p);
	
	/* Searching for the next unused PCB index q */
  while (pcb[q].parent != -1){
	  q++;
  }
	/* Recording the parent PCB index p in PCB[q] */
	pcb[q].parent = p;

	/* Initializing the first_child & younger_sibling of PCB[q] */ // 
    pcb[q].first_child = -1;
    pcb[q].younger_sibling = -1;

	/* Checking to see if parent PCB has no first child--if so, setingt fields appropriately */
	if (pcb[p].first_child == -1)
	{
		pcb[p].first_child = q;
		num_children = 1;
	}
	
	/* Else, we are searching for appropriate available spot for next child, and setting fields appropriately */
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
	
	
	/* Printing message indicating the creation of the ith child of process p at q */
	printf("cr[%d]:\tcreates the %dth child of PCB[%d] at PCB[%d]\n\n", p, num_children, p, q);
   
	/* Printing the PCB table */
	printr();
	
  return;
}


void destroy(int q) {

	if(q == -1) return;
	
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
  
	int p;
	
	printf("Enter the process whose descendants are to be destoryed: ");
	scanf("%d", &p);

	printf("de[%d]:\tdestroys all the descendants of PCB[%d] which includes: ", p, p);
	
	/* Recursive call procedure on PCB[p]'s first child */
	destroy(pcb[p].first_child);
	
	/* Setting PCB[p]'s first child to invalid */
	pcb[p].first_child = -1;

	/* Printting PCB table */
	
	printf("\n");
	
  return;
}


void quit() {

	/* When the dynamic array "PCB" is not NULL, we are going to free the memory */
	if (pcb != NULL) free(pcb);
  return;
}

int main() {

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


