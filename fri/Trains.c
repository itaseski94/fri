#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//@author:Ivica Taseski
struct vagon { 
  int vagonID;
  int teza;
  struct vagon* next;
};

struct vlak {
  int vlakID;
  struct vagon* headV; 
  struct vlak* next;
};

void Priklopi(struct vagon** headRef, int vagonID, int teza);
void Odklopi(struct vagon** headRef,int vagonID);
void izpisiStanje(struct vlak* head); 
struct vlak* dodajVlak(struct vlak** headRef, int vlakID);
int obstajaVlak(struct vlak *head,int vlakID);
int obstajaVagon(struct vagon* head, int vagonID);
int suma(struct vagon* head);

int main() { 

  char naloga;
  int vlakID, vagonID, teza;
  struct vlak* head = NULL;
  struct vlak* current;
  while (scanf(" (%c, %d, %d, %d)",&naloga,&vlakID,&vagonID,&teza) != EOF) { 
        current = dodajVlak(&head,vlakID);
        if (naloga == 'P') {
           Priklopi(&(current->headV),vagonID,teza);
        } else if (naloga == 'O') {
           Odklopi(&(current->headV),vagonID);
        }
  }
  struct vlak *iterator = head;
  while (iterator != NULL) {
        if (iterator->headV == NULL) {
           iterator->vlakID = -1;
        }
        iterator = iterator->next;
  }

  izpisiStanje(head);

  return 0;
}

void Priklopi(struct vagon** headRef, int vagonID, int teza) {
  if (obstajaVagon(*headRef,vagonID)) {
  	 return;
  } else {
     struct vagon* newVlak = (struct vagon*)malloc(sizeof(struct vagon));
     newVlak->vagonID = vagonID;
     newVlak->teza = teza;
     if (*headRef == NULL || (*headRef)->vagonID > newVlak->vagonID) { 
        newVlak->next = *headRef;
        *headRef = newVlak;
     } else {
        struct vagon* current = *headRef;
        while (current->next != NULL && current->next->vagonID < newVlak->vagonID) {
              current = current->next;
        }
        newVlak->next = current->next;
        current->next = newVlak;
    }
  }
}

void Odklopi(struct vagon** headRef,int vagonID) {
  if (!obstajaVagon(*headRef,vagonID)) {
     return;
  } else {
     struct vagon* current = *headRef;
     if (current->vagonID == vagonID) {
        *headRef = (*headRef)->next;
        free(current);
     } else {
        while (current->next->vagonID != vagonID) {
              current = current->next;
        }
        struct vagon* cnext = current->next;
        current->next = current->next->next;
        free(cnext);
     }
  }

}

void izpisiStanje(struct vlak* head) {
  struct vlak* current = head;
  while (current != NULL) {
  	    if (current->vlakID != -1) {
  	       printf("%d: ",current->vlakID);
  	       struct vagon* currentV = current->headV;
           while (currentV != NULL) {
        	     printf("%d ",currentV->vagonID);
        	     currentV = currentV->next;
           }
           printf("(%d)\n",suma(current->headV));
        }
        current = current->next;
  }
}

struct vlak* dodajVlak(struct vlak** headRef, int vlakID) {
  struct vlak* current = *headRef;
  if (obstajaVlak(*headRef,vlakID)) {
     while (current->vlakID != vlakID) {
           current = current->next;
     } 
  } else {
     struct vlak* newVlak = (struct vlak*)malloc(sizeof(struct vlak)); 	
     newVlak->vlakID = vlakID;
     newVlak->headV = NULL;
     if (*headRef == NULL || (*headRef)->vlakID > vlakID) {
        newVlak->next = *headRef;
        *headRef = newVlak;
        current = newVlak;
     } else {
        while (current->next != NULL && current->next->vlakID < vlakID) {
        	  current = current->next;
        } 
        newVlak->next = current->next;
        current->next = newVlak;   
        current = newVlak;
     }
  }
  return current;
}

int obstajaVlak(struct vlak* head,int vlakID) {
   struct vlak* current = head;
   while (current != NULL) {
         if (current->vlakID == vlakID) {
         	return 1;
         } 
         current = current->next;
   }
   return 0;
}

int obstajaVagon(struct vagon* head, int vagonID) {
  struct vagon* current = head;
  while (current != NULL) {
        if (current->vagonID == vagonID) {
           return 1;            
        }   
        current = current->next;
  }
  return 0;
}

int suma(struct vagon* head) {
  struct vagon* current = head;
  int sum = 0;
  while (current != NULL) {
  	    sum += current->teza;
        current = current->next;
  }
  return sum;
}

